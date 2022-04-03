//***************************************************************************************
// Effects.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "stdafx.h"
#include "Effects.h"
#include <atlcore.h>
#include "md5.h"

#pragma region Effect
Effect::Effect(ID3D11Device* device, const std::wstring& filename)
	: mFX(0)
{
	std::wstring	fullFileName = getFullFileName(filename);

	std::ifstream fin;
	fin.open(fullFileName, std::ios::binary);
	fin.seekg(0, std::ios_base::end);
	int size = (int)fin.tellg();
	fin.seekg(0, std::ios_base::beg);
	std::vector<char> compiledShader(size);

	fin.read(&compiledShader[0], size);
	fin.close();
	
	HRWMS(D3DX11CreateEffectFromMemory(&compiledShader[0], size, 
		0, device, &mFX));
}

/*
Effect::Effect(ID3D11Device* device, void * _pCode, DWORD	_size)
	: mFX(0)
{
	HR(D3DX11CreateEffectFromMemory(_pCode, _size, 
		0, device, &mFX));

	WCHAR	test[300] = {0};

	GetCurrentDirectory(300, test); 

	std::ifstream	file(L"D:/Users/shishkin/Документы/Visual Studio 2010/Projects/WMSVisual/Debug/Data/Shader.Room", std::ios::binary);

	MD5	md5calc = MD5(file);

	md5calc.finalize();

}
*/

Effect::~Effect()
{	/*
	ReleaseCOM(Light1Tech);
	ReleaseCOM(Light2Tech);
	ReleaseCOM(Light3Tech);

	ReleaseCOM(Light0TexTech);
	ReleaseCOM(Light1TexTech);
	ReleaseCOM(Light2TexTech);
	ReleaseCOM(Light3TexTech);

	ReleaseCOM(Light0TexAlphaClipTech);
	ReleaseCOM(Light1TexAlphaClipTech);
	ReleaseCOM(Light2TexAlphaClipTech);
	ReleaseCOM(Light3TexAlphaClipTech);

	ReleaseCOM(Light1FogTech);
	ReleaseCOM(Light2FogTech);
	ReleaseCOM(Light3FogTech);

	ReleaseCOM(Light0TexFogTech);
	ReleaseCOM(Light1TexFogTech);
	ReleaseCOM(Light2TexFogTech);
	ReleaseCOM(Light3TexFogTech);

	ReleaseCOM(Light0TexAlphaClipFogTech);
	ReleaseCOM(Light1TexAlphaClipFogTech);
	ReleaseCOM(Light2TexAlphaClipFogTech);
	ReleaseCOM(Light3TexAlphaClipFogTech);

	ReleaseCOM(WorldViewProj);
	ReleaseCOM(World);
	ReleaseCOM(WorldInvTranspose);
	ReleaseCOM(TexTransform);
	ReleaseCOM(EyePosW);
	ReleaseCOM(FogColor);
	ReleaseCOM(FogStart);
	ReleaseCOM(FogRange);
	ReleaseCOM(DirLights);
	ReleaseCOM(Mat);
	
	ReleaseCOM(DiffuseMap);
	*/

	ReleaseCOM(mFX);
}
#pragma endregion

#pragma region BasicEffect
BasicEffect::BasicEffect(ID3D11Device* device, const std::wstring& filename)
	: Effect(device, filename)
{
	InitAll();
}
/*
BasicEffect::BasicEffect(ID3D11Device* device, void * _pCode, DWORD	_size)
	: Effect(device, _pCode, _size)
{
	InitAll();	
}
*/

BasicEffect::~BasicEffect()
{
}
void BasicEffect::InitAll()
{
	Light1Tech    = mFX->GetTechniqueByName("Light1");
	Light2Tech    = mFX->GetTechniqueByName("Light2");
	Light3Tech    = mFX->GetTechniqueByName("Light3");

	Light0TexTech = mFX->GetTechniqueByName("Light0Tex");
	Light1TexTech = mFX->GetTechniqueByName("Light1Tex");
	Light2TexTech = mFX->GetTechniqueByName("Light2Tex");
	Light3TexTech = mFX->GetTechniqueByName("Light3Tex");

	Light0TexAlphaClipTech = mFX->GetTechniqueByName("Light0TexAlphaClip");
	Light1TexAlphaClipTech = mFX->GetTechniqueByName("Light1TexAlphaClip");
	Light2TexAlphaClipTech = mFX->GetTechniqueByName("Light2TexAlphaClip");
	Light3TexAlphaClipTech = mFX->GetTechniqueByName("Light3TexAlphaClip");

	Light1FogTech    = mFX->GetTechniqueByName("Light1Fog");
	Light2FogTech    = mFX->GetTechniqueByName("Light2Fog");
	Light3FogTech    = mFX->GetTechniqueByName("Light3Fog");

	Light0TexFogTech = mFX->GetTechniqueByName("Light0TexFog");
	Light1TexFogTech = mFX->GetTechniqueByName("Light1TexFog");
	Light2TexFogTech = mFX->GetTechniqueByName("Light2TexFog");
	Light3TexFogTech = mFX->GetTechniqueByName("Light3TexFog");

	Light0TexAlphaClipFogTech = mFX->GetTechniqueByName("Light0TexAlphaClipFog");
	Light1TexAlphaClipFogTech = mFX->GetTechniqueByName("Light1TexAlphaClipFog");
	Light2TexAlphaClipFogTech = mFX->GetTechniqueByName("Light2TexAlphaClipFog");
	Light3TexAlphaClipFogTech = mFX->GetTechniqueByName("Light3TexAlphaClipFog");

	WorldViewProj     = mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	World             = mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldInvTranspose = mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	TexTransform      = mFX->GetVariableByName("gTexTransform")->AsMatrix();
	EyePosW           = mFX->GetVariableByName("gEyePosW")->AsVector();
	FogColor          = mFX->GetVariableByName("gFogColor")->AsVector();
	FogStart          = mFX->GetVariableByName("gFogStart")->AsScalar();
	FogRange          = mFX->GetVariableByName("gFogRange")->AsScalar();
	DirLights         = mFX->GetVariableByName("gDirLights");
	Mat               = mFX->GetVariableByName("gMaterial");
	
	LocationFurnitureMap	= mFX->GetVariableByName("gLocationFurnitureMap")->AsShaderResource();
	PalletMap				= mFX->GetVariableByName("gPalletMap")->AsShaderResource();
	gAlphabet				= mFX->GetVariableByName("gAlphabet")->AsShaderResource();
	ItemFaceMap				= mFX->GetVariableByName("gItemFaceMap")->AsShaderResource();
	ItemSideMap				= mFX->GetVariableByName("gItemSideMap")->AsShaderResource();
	ItemTopMap				= mFX->GetVariableByName("gItemTopMap")->AsShaderResource();
	TransparentMap			= mFX->GetVariableByName("gTransparentMap")->AsShaderResource();
	gArrayTexturePosition	= mFX->GetVariableByName("gArrayTexturePosition")->AsShaderResource();

	Light1TexTransparent	= mFX->GetTechniqueByName("Light1TexTransparent");
	Light2TexTransparent	= mFX->GetTechniqueByName("Light2TexTransparent");
	Light3TexTransparent	= mFX->GetTechniqueByName("Light3TexTransparent");

	CubeMap					= mFX->GetVariableByName("gCubeMap")->AsShaderResource();
}

#pragma endregion

#pragma region WarehouseRoom
RoomEffect::RoomEffect(ID3D11Device*	device, std::wstring&	fxFile):
	Effect(device, fxFile)
{
	RoomTech			= mFX->GetTechniqueByName("WarehouseRoomTech");
	World				= mFX->GetVariableByName("gWorld")->AsMatrix();
	WorldInvTranspose	= mFX->GetVariableByName("gWorldInvTranspose")->AsMatrix();
	WorldViewProj		= mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	TexTransform		= mFX->GetVariableByName("gTexTransform")->AsMatrix();
	
	TextureMap			= mFX->GetVariableByName("gTextureMap")->AsShaderResource();
}
RoomEffect::~RoomEffect()
{
}
#pragma endregion

#pragma region WMSEnvironment
WMSEnvironment::WMSEnvironment(ID3D11Device*	device, std::wstring&	fxFile)
	: Effect(device, fxFile)
{
	EnvironmentTech	= mFX->GetTechniqueByName("SkyTech");
	WorldViewProj	= mFX->GetVariableByName("gWorldViewProj")->AsMatrix();
	CubeMap			= mFX->GetVariableByName("gCubeMap")->AsShaderResource();
}

WMSEnvironment::~WMSEnvironment()
{
}
#pragma endregion

#pragma region Effects

BasicEffect*	Effects::BasicFX			= nullptr;
WMSEnvironment* Effects::WMSEnvironmentFX   = nullptr;
RoomEffect*		Effects::RoomFX				= nullptr;

void Effects::InitAll(ID3D11Device* device, std::vector<std::wstring>&	fxArray)
{
	//BasicFX = new BasicEffect(device, L"FX/Basic.fxo");
	//BasicFX = new BasicEffect(device, L"D:/Users/shishkin/Документы/Visual Studio 2010/Projects/WMSVisual/WMSVisual/FX/Basic_Crate.fxo");
	//BasicFX = new BasicEffect(device, L"D:/WebService/test/Basic.fxo");

	BasicFX				= new BasicEffect(device,		fxArray[0]);
	WMSEnvironmentFX	= new WMSEnvironment(device,	fxArray[1]);
	RoomFX				= new RoomEffect(device,		fxArray[2]);
}

void Effects::DestroyAll()
{
	SafeDelete(BasicFX);
	SafeDelete(WMSEnvironmentFX);
	SafeDelete(RoomFX);
}
#pragma endregion