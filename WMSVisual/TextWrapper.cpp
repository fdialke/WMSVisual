#include "stdafx.h"
#include "TextWrapper.h"


TextWrapper::TextWrapper()
	:m_maxWidth(0), m_maxHeight(0),
	 m_pTextureAlphabet(nullptr),
	 m_pShaderResourceView(nullptr)
{
	LoadTextureData();
}

TextWrapper::~TextWrapper()
{
	if (m_pTextureAlphabet)
	{
		m_pTextureAlphabet->Release();
		m_pTextureAlphabet = nullptr;
	}

	if (m_pShaderResourceView)
	{
		m_pShaderResourceView->Release();
		m_pShaderResourceView = nullptr;
	}
}
LONG TextWrapper::getMaxWidth()
{
	return m_maxWidth;
}
LONG TextWrapper::getMaxHeight()
{
	return m_maxHeight;
}
void	TextWrapper::SetDeviceContext(	ID3D11Device*			pDevice, 
										ID3D11DeviceContext*	pDeviceContext,
										HINSTANCE				hInstance)
{
	m_md3device			= pDevice;
	m_md3deviceContext	= pDeviceContext;
	m_hInstance			= hInstance;
}
void	TextWrapper::CreateTextureArray()
{
	HRESULT hr = S_OK;

	D3DX11_IMAGE_LOAD_INFO loadInfo;

    loadInfo.Width  = D3DX11_FROM_FILE;
    loadInfo.Height = D3DX11_FROM_FILE;
    loadInfo.Depth  = D3DX11_FROM_FILE;
    loadInfo.FirstMipLevel = 0;
    loadInfo.MipLevels = D3DX11_FROM_FILE;
    loadInfo.Usage = D3D11_USAGE_STAGING;
    loadInfo.BindFlags = 0;
    loadInfo.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
    loadInfo.MiscFlags = 0;

	/*
	HRSRC hrsrc = FindResource(m_hInstance,MAKEINTRESOURCE(IDR_DEFAULT2), MAKEINTRESOURCE(256)); // “екстура всего алфавита
	DWORD dw = GetLastError();
	HGLOBAL res = LoadResource(m_hInstance, hrsrc);
	LPVOID code = LockResource(res);
	DWORD size = SizeofResource(m_hInstance, hrsrc);

	
	HR(D3DX11CreateTextureFromMemory(m_md3device, code, size, &loadInfo, nullptr, (ID3D11Resource**)&m_pTextureAlphabet, &hr));
	*/

	HRWMS(D3DX11CreateTextureFromFile(m_md3device, 
								getFullFileName(TEXALPHA).c_str(), 
								&loadInfo, 
								0, 
								(ID3D11Resource**)&m_pTextureAlphabet, &hr));

	D3D11_TEXTURE2D_DESC texElementDesc = {0};
	m_pTextureAlphabet->GetDesc(&texElementDesc);


	std::vector<ID3D11Texture2D*> srcTex(m_listCharTexture.size());

	for (ULONG	i = 0; i < m_listCharTexture.size(); i++)
	{
		D3D11_TEXTURE2D_DESC	textureDesc = {0};

		textureDesc.Width				= getMaxWidth();
		textureDesc.Height				= getMaxHeight();
		textureDesc.MipLevels			= 1;
		textureDesc.ArraySize			= 1;
		textureDesc.Format				= texElementDesc.Format;
		textureDesc.SampleDesc.Count	= 1;
		textureDesc.SampleDesc.Quality	= 0;
		textureDesc.Usage				= D3D11_USAGE_STAGING;
		textureDesc.CPUAccessFlags		= D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE; //D3D11_BIND_SHADER_RESOURCE;
		textureDesc.MiscFlags			= 0;
		textureDesc.BindFlags			= texElementDesc.BindFlags;

		HRWMS(m_md3device->CreateTexture2D(&textureDesc, nullptr, &srcTex[i]));

		CharTexture	tmp = m_listCharTexture[i];

		m_mapCharTexture.insert(std::pair<char, int>(tmp.xByte, i));

		D3D11_BOX sourceRegion;
		sourceRegion.left = tmp.origin.x - 2; // текстуры символов заход€т немного за край следующей текстуры => сдвигаю немного влево
		sourceRegion.right = tmp.origin.x + tmp.size.x - 2;
		sourceRegion.top = tmp.origin.y;
		sourceRegion.bottom = tmp.origin.y + tmp.size.y - 1;
		sourceRegion.front = 0;
		sourceRegion.back = 1;

		m_md3deviceContext->CopySubresourceRegion(srcTex[i], 0, 0 , 0, 0,  m_pTextureAlphabet, 0, &sourceRegion);
	}

	srcTex[0]->GetDesc(&texElementDesc);

	D3D11_TEXTURE2D_DESC texArrayDesc;
	texArrayDesc.Width              = texElementDesc.Width;
	texArrayDesc.Height             = texElementDesc.Height;
	texArrayDesc.MipLevels          = texElementDesc.MipLevels;
	texArrayDesc.ArraySize          = m_listCharTexture.size();
	texArrayDesc.Format             = texElementDesc.Format;
	texArrayDesc.SampleDesc.Count   = 1;
	texArrayDesc.SampleDesc.Quality = 0;
	texArrayDesc.Usage              = D3D11_USAGE_DEFAULT;
	texArrayDesc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
	texArrayDesc.CPUAccessFlags     = 0;
	texArrayDesc.MiscFlags          = 0;

	ID3D11Texture2D* texArray = nullptr;
	HRWMS(m_md3device->CreateTexture2D( &texArrayDesc, 0, &texArray));

	for(ULONG texElement = 0; texElement < m_listCharTexture.size(); ++texElement)
	{
		// for each mipmap level...
		for(ULONG mipLevel = 0; mipLevel < texElementDesc.MipLevels; ++mipLevel)
		{
			D3D11_MAPPED_SUBRESOURCE mappedTex2D;
			HRWMS(m_md3deviceContext->Map(srcTex[texElement], mipLevel, D3D11_MAP_READ, 0, &mappedTex2D));

			m_md3deviceContext->UpdateSubresource(texArray, 
				D3D11CalcSubresource(mipLevel, texElement, texElementDesc.MipLevels),
				0, mappedTex2D.pData, mappedTex2D.RowPitch, mappedTex2D.DepthPitch);

			m_md3deviceContext->Unmap(srcTex[texElement], mipLevel);
		}
	}	

	//
	// Create a resource view to the texture array.
	//
	
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	viewDesc.Format = texArrayDesc.Format;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	viewDesc.Texture2DArray.MostDetailedMip = 0;
	viewDesc.Texture2DArray.MipLevels = texArrayDesc.MipLevels;
	viewDesc.Texture2DArray.FirstArraySlice = 0;
	viewDesc.Texture2DArray.ArraySize = m_listCharTexture.size();

	ID3D11ShaderResourceView* texArraySRV = 0;
	HRWMS(m_md3device->CreateShaderResourceView(texArray, &viewDesc, &m_pShaderResourceView));

	//
	// Cleanup--we only need the resource view.
	//

	ReleaseCOM(texArray);


	for(ULONG i = 0; i < m_listCharTexture.size(); ++i)
		ReleaseCOM(srcTex[i]);

}
void TextWrapper::AddText(unsigned long _num)
{
	char		text[30] = {0};
	std::string	putElement;;

	sprintf_s(text, "%d", _num);
	putElement = text;

	m_listLocationName.push_back(putElement);
}
int TextWrapper::getCharPosition(char c)
{
	return m_mapCharTexture.find(c)->second;
}
int	TextWrapper::getCharPosition(const char c[2])
{
	return getCharPosition(c[0]);
}
ID3D11ShaderResourceView * TextWrapper::getAlphabetShaderResourceView()
{
	return m_pShaderResourceView;
}
void TextWrapper::LoadTextureData()
{
	CharTexture textureData[]=
	{
		{"-", 0x02D,0,{2,2},{34,129},30,6},
			{".", 0x02E,0,{109,2},{27,129},23,7},
			{"/", 0x02F,0,{216,2},{37,129},31,-1},
			{"0", 0x030,0,{323,2},{61,129},57,4},
			{"1", 0x031,0,{430,2},{57,129},53,8},
			{"2", 0x032,0,{537,2},{63,129},59,2},
			{"3", 0x033,0,{644,2},{61,129},57,4},
			{"4", 0x034,0,{751,2},{63,129},59,2},
			{"5", 0x035,0,{858,2},{60,129},56,5},
			{"6", 0x036,0,{965,2},{61,129},57,4},
			{"7", 0x037,0,{1072,2},{61,129},57,4},
			{"8", 0x038,0,{1179,2},{61,129},57,4},
			{"9", 0x039,0,{1286,2},{62,129},58,3},
			{":", 0x03A,0,{1393,2},{30,129},26,11},
			{";", 0x03B,0,{1500,2},{32,129},28,9},
			{"<", 0x03C,0,{1607,2},{63,129},59,5},
			{"=", 0x03D,0,{1714,2},{64,129},60,4},
			{">", 0x03E,0,{1821,2},{63,129},59,5},
			{"?", 0x03F,0,{1928,2},{66,129},62,5},
			{"@", 0x040,0,{2035,2},{107,129},103,3},
			{"A", 0x041,0,{2142,2},{80,129},75,0},
			{"B", 0x042,0,{2249,2},{75,129},71,8},
			{"C", 0x043,0,{2356,2},{78,129},74,5},
			{"D", 0x044,0,{2463,2},{75,129},71,8},
			{"E", 0x045,0,{2570,2},{69,129},65,8},
			{"F", 0x046,0,{2677,2},{63,129},59,8},
			{"G", 0x047,0,{2784,2},{84,129},80,5},
			{"H", 0x048,0,{2891,2},{75,129},71,8},
			{"I", 0x049,0,{2998,2},{27,129},23,7},
			{"J", 0x04A,0,{3105,2},{63,129},59,2},
			{"K", 0x04B,0,{3212,2},{75,129},71,8},
			{"L", 0x04C,0,{3319,2},{63,129},59,8},
			{"M", 0x04D,0,{3426,2},{88,129},84,7},
			{"N", 0x04E,0,{3533,2},{75,129},71,8},
			{"O", 0x04F,0,{3640,2},{85,129},81,4},
			{"P", 0x050,0,{3747,2},{69,129},65,8},
			{"Q", 0x051,0,{3854,2},{85,129},81,4},
			{"R", 0x052,0,{3961,2},{75,129},71,8},
			{"S", 0x053,0,{4068,2},{74,129},70,3},
			{"T", 0x054,0,{4175,2},{67,129},63,3},
			{"U", 0x055,0,{4282,2},{76,129},72,7},
			{"V", 0x056,0,{4389,2},{77,129},73,0},
			{"W", 0x057,0,{4496,2},{107,129},103,0},
			{"X", 0x058,0,{4603,2},{77,129},73,0},
			{"Y", 0x059,0,{4710,2},{79,129},74,-1},
			{"Z", 0x05A,0,{4817,2},{70,129},66,1},
			{" ", 0x020, 0, {4817 + 129,2},{70,129},66,0}
	};

	for (int i = 0; i < sizeof(textureData)/sizeof(CharTexture); i++)
	{
		m_listCharTexture.push_back(textureData[i]);

		if (textureData[i].size.x > m_maxWidth)
			m_maxWidth = textureData[i].size.x;

		if (textureData[i].size.y > m_maxHeight)
			m_maxHeight = textureData[i].size.y;
	}

}