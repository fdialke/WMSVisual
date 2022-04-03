//***************************************************************************************
// Vertex.h by Frank Luna (C) 2011 All Rights Reserved.
//
// Defines vertex structures and input layouts.
//***************************************************************************************

#ifndef VERTEX_H
#define VERTEX_H

#include "stdafx.h"
#include "Common\d3dUtil.h"

struct InstancedData
{
	XMFLOAT4X4	World;
	XMFLOAT4	Color;
	ULONG		faceTexNum;
	XMFLOAT4X4	WorldItem;
};
struct ArrayTextPosition
{
	ULONG	iPosition;
};
struct RoomVertex
{
	XMFLOAT3	Pos;
	XMFLOAT2	Tex;
};

namespace Vertex
{
	// Basic 32-byte vertex structure.
	struct Basic32
	{
		XMFLOAT3 Pos;
		XMFLOAT3 Normal;
		XMFLOAT2 Tex;
		unsigned char texNum;
	};
}

class InputLayoutDesc
{
public:
	// Init like const int A::a[4] = {0, 1, 2, 3}; in .cpp file.
	static const D3D11_INPUT_ELEMENT_DESC Basic32[14];
	static const D3D11_INPUT_ELEMENT_DESC Pos[1];
	static const D3D11_INPUT_ELEMENT_DESC Room[2];
};

class InputLayouts
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static ID3D11InputLayout* Basic32;
	static ID3D11InputLayout* Pos;
	static ID3D11InputLayout* Room;
};

#endif // VERTEX_H
