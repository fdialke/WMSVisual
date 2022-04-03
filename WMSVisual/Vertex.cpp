#include "stdafx.h"
#include "Vertex.h"
#include "Effects.h"

#pragma region InputLayoutDesc

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::Room[2] = 
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0,	0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::Pos[1] = 
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

const D3D11_INPUT_ELEMENT_DESC InputLayoutDesc::Basic32[14] = 
{
	{"POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,	0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXTURENUM",	0, DXGI_FORMAT_R8_UINT,			0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ "WORLD",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "WORLD",		1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "WORLD",		2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "WORLD",		3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64,  D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "FACETEXNUM",	0, DXGI_FORMAT_R32_UINT,			1, 80, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
	{ "WORLDITEM",		0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 84, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "WORLDITEM",		1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 100, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "WORLDITEM",		2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 116, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
    { "WORLDITEM",		3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 132, D3D11_INPUT_PER_INSTANCE_DATA, 1 }
};

#pragma endregion

#pragma region InputLayouts

ID3D11InputLayout* InputLayouts::Basic32 = nullptr;
ID3D11InputLayout* InputLayouts::Pos = nullptr;
ID3D11InputLayout* InputLayouts::Room = nullptr;

void InputLayouts::InitAll(ID3D11Device* device)
{
	D3DX11_PASS_DESC passDesc;

	//
	// Basic32
	//

	Effects::BasicFX->Light1Tech->GetPassByIndex(0)->GetDesc(&passDesc);
	HRWMS(device->CreateInputLayout(InputLayoutDesc::Basic32, 14, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &Basic32));

	Effects::WMSEnvironmentFX->EnvironmentTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HRWMS(device->CreateInputLayout(InputLayoutDesc::Pos, 1, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &Pos));

	Effects::RoomFX->RoomTech->GetPassByIndex(0)->GetDesc(&passDesc);
	HRWMS(device->CreateInputLayout(InputLayoutDesc::Room, 2, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &Room));

}

void InputLayouts::DestroyAll()
{
	ReleaseCOM(Basic32);
	ReleaseCOM(Pos);
	ReleaseCOM(Room);
}

#pragma endregion
