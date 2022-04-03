#include "StdAfx.h"
#include "WarehouseRoom.h"
#include "Effects.h"
#include "GeometryGenerator.h"
#include "WMSLocation.h"

const	float roomShift		= 10.0f;
const	float roomShiftHalf	= 5.0f;

WarehouseRoom::WarehouseRoom(ID3D11Device* device, WMSLocationWrapper*	pLocationWrapper):
	mCeilingVB(nullptr),
	mCeilingIB(nullptr),
	mWallVB(nullptr),
	mWallIB(nullptr),
	mFloorVB(nullptr),
	mFloorIB(nullptr),
	mCeilingSRV(nullptr),
	mWallSRV(nullptr),
	mFloorSRV(nullptr),
	m_pLocationWrapper(pLocationWrapper),
	FloorWorldMatrix(XMMatrixIdentity()),
	CeilingWorldMatrix(XMMatrixIdentity()),
	WallWorldMatrix(XMMatrixIdentity()),
	FloorTexMatrix(XMMatrixIdentity()),
	CeilingTexMatrix(XMMatrixIdentity()),
	WallTexMatrix(XMMatrixIdentity())
{
	HRWMS(D3DX11CreateShaderResourceViewFromFile(device, getFullFileName(TEXROOMTOP).c_str(), 0, 0, &mCeilingSRV, 0));
	HRWMS(D3DX11CreateShaderResourceViewFromFile(device, getFullFileName(TEXROOMSIDE).c_str(), 0, 0, &mWallSRV, 0));
	HRWMS(D3DX11CreateShaderResourceViewFromFile(device, getFullFileName(TEXROOMFLOOR).c_str(), 0, 0, &mFloorSRV, 0));

	GeometryGenerator::MeshData box;
	GeometryGenerator geoGen;

	geoGen.CreateBox(1.0f, 1.0f, 1.0f, box);

	std::vector<RoomVertex>	CeilingVertex(4);
	std::vector<UINT>		CeilingIndex(6);

	std::vector<RoomVertex>	FloorVertex(4);
	std::vector<UINT>		FloorIndex(6);

	std::vector<RoomVertex>	WallVertex(16);
	std::vector<UINT>		WallIndex(24);

	for(DWORD i = 0; i < box.Vertices.size(); ++i)	// 
	{
		if (i >= 8 && i < 12)
		{
			CeilingVertex[i - 8].Pos	= box.Vertices[i].Position;
			CeilingVertex[i - 8].Tex	= box.Vertices[i].TexC;
		}
		else if (i >= 12 && i < 16)
		{
			FloorVertex[i - 12].Pos		= box.Vertices[i].Position;
			FloorVertex[i - 12].Tex		= box.Vertices[i].TexC;
		} else
		{
			DWORD	index = ( i >= 16 ) ? (i - 8) : i;

			WallVertex[index].Pos			= box.Vertices[i].Position;
			WallVertex[index].Tex			= box.Vertices[i].TexC;
		}
	}

	for (DWORD	i = 0; i < box.Indices.size(); ++i)
	{
		if ( i >= 12 && i < 18)
		{
			CeilingIndex[i - 12]	= box.Indices[i] - 8;
		}
		else if (i >= 18 && i < 24)
		{
			FloorIndex[i - 18]		= box.Indices[i] - 12;
		} else
		{
			if ( i >= 24)
			{
				WallIndex[i - 12]		= box.Indices[i] - 8;
			} else
			{
				WallIndex[i]			= box.Indices[i];
			}
		}
	}

    D3D11_BUFFER_DESC vbdCeiling;
    vbdCeiling.Usage = D3D11_USAGE_IMMUTABLE;
	vbdCeiling.ByteWidth = sizeof(RoomVertex) * CeilingVertex.size();
    vbdCeiling.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbdCeiling.CPUAccessFlags = 0;
    vbdCeiling.MiscFlags = 0;
	vbdCeiling.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA vinitDataCeiling;
    vinitDataCeiling.pSysMem = &CeilingVertex[0];

    HRWMS(device->CreateBuffer(&vbdCeiling, &vinitDataCeiling, &mCeilingVB));

	D3D11_BUFFER_DESC ibdCeiling;
    ibdCeiling.Usage = D3D11_USAGE_IMMUTABLE;
	ibdCeiling.ByteWidth = sizeof(UINT) * CeilingIndex.size();
    ibdCeiling.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibdCeiling.CPUAccessFlags = 0;
	ibdCeiling.StructureByteStride = 0;
    ibdCeiling.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitDataCeiling;
    iinitDataCeiling.pSysMem = &CeilingIndex[0];

    HRWMS(device->CreateBuffer(&ibdCeiling, &iinitDataCeiling, &mCeilingIB));



    D3D11_BUFFER_DESC vbdFloor;
    vbdFloor.Usage = D3D11_USAGE_IMMUTABLE;
	vbdFloor.ByteWidth = sizeof(RoomVertex) * FloorVertex.size();
    vbdFloor.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbdFloor.CPUAccessFlags = 0;
    vbdFloor.MiscFlags = 0;
	vbdFloor.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA vinitDataFloor;
    vinitDataFloor.pSysMem = &FloorVertex[0];

    HRWMS(device->CreateBuffer(&vbdFloor, &vinitDataFloor, &mFloorVB));

	D3D11_BUFFER_DESC ibdFloor;
    ibdFloor.Usage = D3D11_USAGE_IMMUTABLE;
	ibdFloor.ByteWidth = sizeof(UINT) * FloorIndex.size();
    ibdFloor.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibdFloor.CPUAccessFlags = 0;
	ibdFloor.StructureByteStride = 0;
    ibdFloor.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitDataFloor;
    iinitDataFloor.pSysMem = &FloorIndex[0];

    HRWMS(device->CreateBuffer(&ibdFloor, &iinitDataFloor, &mFloorIB));


    D3D11_BUFFER_DESC vbdWall;
    vbdWall.Usage = D3D11_USAGE_IMMUTABLE;
	vbdWall.ByteWidth = sizeof(RoomVertex) * WallVertex.size();
    vbdWall.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vbdWall.CPUAccessFlags = 0;
    vbdWall.MiscFlags = 0;
	vbdWall.StructureByteStride = 0;

    D3D11_SUBRESOURCE_DATA vinitDataWall;
    vinitDataWall.pSysMem = &WallVertex[0];

    HRWMS(device->CreateBuffer(&vbdWall, &vinitDataWall, &mWallVB));

	D3D11_BUFFER_DESC ibdWall;
    ibdWall.Usage = D3D11_USAGE_IMMUTABLE;
	ibdWall.ByteWidth = sizeof(UINT) * WallIndex.size();
    ibdWall.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibdWall.CPUAccessFlags = 0;
	ibdWall.StructureByteStride = 0;
    ibdWall.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA iinitDataWall;
    iinitDataWall.pSysMem = &WallIndex[0];

    HRWMS(device->CreateBuffer(&ibdWall, &iinitDataWall, &mWallIB));

}

WarehouseRoom::~WarehouseRoom()
{
	ReleaseCOM(mCeilingVB);
	ReleaseCOM(mCeilingIB);
	ReleaseCOM(mWallVB);
	ReleaseCOM(mWallIB);
	ReleaseCOM(mFloorVB);
	ReleaseCOM(mFloorIB);
	ReleaseCOM(mCeilingSRV);
	ReleaseCOM(mWallSRV);
	ReleaseCOM(mFloorSRV);
}
void WarehouseRoom::Draw(ID3D11DeviceContext* dc, const WMSCamera& camera)
{
	MinMax		minMax[3];
	m_pLocationWrapper->GetMinMax(&minMax[0], &minMax[1], &minMax[2]);

	XMMATRIX viewProj	= camera.ViewProj();
	
	XMMATRIX	world = FloorWorldMatrix;

	XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);


	// Floor
									 
	UINT stride = sizeof(RoomVertex);
    UINT offset = 0;

    dc->IASetVertexBuffers(0, 1, &mFloorVB, &stride, &offset);
	dc->IASetIndexBuffer(mFloorIB, DXGI_FORMAT_R32_UINT, 0);
	dc->IASetInputLayout(InputLayouts::Room);
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Effects::RoomFX->SetWorld(world);
	Effects::RoomFX->SetTexTransform(FloorTexMatrix);

	Effects::RoomFX->SetTextureMap(mFloorSRV);
	Effects::RoomFX->SetWorldInvTranspose(worldInvTranspose);
	Effects::RoomFX->SetWorldViewProj(world * viewProj);

	D3DX11_TECHNIQUE_DESC techDesc;
	Effects::RoomFX->RoomTech->GetDesc( &techDesc );

    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
		ID3DX11EffectPass* pass = Effects::RoomFX->RoomTech->GetPassByIndex(p);

		pass->Apply(0, dc);

		dc->DrawIndexed(6, 0, 0);
	}

	// CEILING
	world = CeilingWorldMatrix;

	worldInvTranspose = MathHelper::InverseTranspose(world);


	stride = sizeof(RoomVertex);
    offset = 0;

    dc->IASetVertexBuffers(0, 1, &mCeilingVB, &stride, &offset);
	dc->IASetIndexBuffer(mCeilingIB, DXGI_FORMAT_R32_UINT, 0);
	dc->IASetInputLayout(InputLayouts::Room);
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Effects::RoomFX->SetWorld(world);
	Effects::RoomFX->SetTexTransform(CeilingTexMatrix);

	Effects::RoomFX->SetTextureMap(mCeilingSRV);
	Effects::RoomFX->SetWorldInvTranspose(worldInvTranspose);
	Effects::RoomFX->SetWorldViewProj(world * viewProj);

	Effects::RoomFX->RoomTech->GetDesc( &techDesc );

    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
		ID3DX11EffectPass* pass = Effects::RoomFX->RoomTech->GetPassByIndex(p);

		pass->Apply(0, dc);

		dc->DrawIndexed(6, 0, 0);
	}



	// WALLS

	world = WallWorldMatrix;

	worldInvTranspose = MathHelper::InverseTranspose(world);
									 
	stride = sizeof(RoomVertex);
    offset = 0;

    dc->IASetVertexBuffers(0, 1, &mWallVB, &stride, &offset);
	dc->IASetIndexBuffer(mWallIB, DXGI_FORMAT_R32_UINT, 0);
	dc->IASetInputLayout(InputLayouts::Room);
	dc->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	Effects::RoomFX->SetWorld(world);
	Effects::RoomFX->SetTexTransform(WallTexMatrix);

	Effects::RoomFX->SetTextureMap(mWallSRV);
	Effects::RoomFX->SetWorldInvTranspose(worldInvTranspose);
	Effects::RoomFX->SetWorldViewProj(world * viewProj);

	Effects::RoomFX->RoomTech->GetDesc( &techDesc );

    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
		ID3DX11EffectPass* pass = Effects::RoomFX->RoomTech->GetPassByIndex(p);

		pass->Apply(0, dc);

		dc->DrawIndexed(24, 0, 0);
	}

}
void	WarehouseRoom::ComputeInnerMatrix(WMSCamera&	mCam)
{
	MinMax		minMax[3];
	m_pLocationWrapper->GetMinMax(&minMax[0], &minMax[1], &minMax[2]);

	FloorWorldMatrix	=	XMMatrixIdentity() *
							XMMatrixScaling((minMax[0].max - minMax[0].min + roomShift) * dx, 1.0f, (minMax[2].max - minMax[2].min + roomShift) * dz) * 
							XMMatrixTranslation(xSize+(minMax[0].max - minMax[0].min)*0.5f*dx, 
											ySize+minMax[1].min*dy, 
											zSize+(minMax[2].max - minMax[2].min + 1) *0.5f*dz);


	float				scaleMin = min(minMax[0].max - minMax[0].min + roomShift, minMax[2].max - minMax[2].min + roomShift);

	FloorTexMatrix		=	XMMatrixIdentity() * 
							XMMatrixScaling(scaleMin, scaleMin, 0);

	CeilingWorldMatrix	=	XMMatrixIdentity() *
							XMMatrixScaling((minMax[0].max - minMax[0].min + roomShift) * dx, 1.0f, (minMax[2].max - minMax[2].min + roomShift) * dz) * 
							XMMatrixTranslation(xSize+(minMax[0].max - minMax[0].min)*0.5f*dx, 
												ySize+(minMax[1].max + roomShift)*dy, 
												zSize+(minMax[2].max - minMax[2].min + 1) *0.5f*dz);

	CeilingTexMatrix	=	XMMatrixIdentity() * 
							XMMatrixScaling(scaleMin, scaleMin, 0);


	WallWorldMatrix		=	XMMatrixIdentity() *
							XMMatrixScaling((minMax[0].max - minMax[0].min + roomShift) * dx, 
											(minMax[1].max + minMax[1].min + roomShift + 1) * dy, 
											(minMax[2].max - minMax[2].min + roomShift) * dz) * 
							XMMatrixTranslation(xSize+(minMax[0].max - minMax[0].min)*0.5f*dx, 
												ySize + (minMax[1].max + minMax[1].min + roomShift) * dy * 0.5f , 
												zSize+(minMax[2].max - minMax[2].min + 1) *0.5f*dz);
	scaleMin			=	min(min(minMax[0].max - minMax[0].min + roomShift, minMax[1].max - minMax[1].min + roomShift), minMax[2].max - minMax[2].min + roomShift);

	WallTexMatrix		=	XMMatrixIdentity() * 
							XMMatrixScaling(scaleMin, scaleMin, 0);


	XMFLOAT4	v1 = XMFLOAT4(-0.5f, -0.5f, -0.5f, 1.0f),
				v2 = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f),
				v3, v4;

	XMFLOAT4X4	storeMatrix;
	
	XMStoreFloat4x4(&storeMatrix, FloorWorldMatrix);
	v3.x	= storeMatrix._11 * v1.x + storeMatrix._21 * v1.y + storeMatrix._31 * v1.z + storeMatrix._41 * v1.w;
	v3.y	= storeMatrix._12 * v1.x + storeMatrix._22 * v1.y + storeMatrix._32 * v1.z + storeMatrix._42 * v1.w;
	v3.z	= storeMatrix._13 * v1.x + storeMatrix._23 * v1.y + storeMatrix._33 * v1.z + storeMatrix._43 * v1.w;
	v3.w	= storeMatrix._14 * v1.x + storeMatrix._24 * v1.y + storeMatrix._34 * v1.z + storeMatrix._44 * v1.w;

	XMStoreFloat4x4(&storeMatrix, CeilingWorldMatrix);
	v4.x	= storeMatrix._11 * v2.x + storeMatrix._21 * v2.y + storeMatrix._31 * v2.z + storeMatrix._41 * v2.w;
	v4.y	= storeMatrix._12 * v2.x + storeMatrix._22 * v2.y + storeMatrix._32 * v2.z + storeMatrix._42 * v2.w;
	v4.z	= storeMatrix._13 * v2.x + storeMatrix._23 * v2.y + storeMatrix._33 * v2.z + storeMatrix._43 * v2.w;
	v4.w	= storeMatrix._14 * v2.x + storeMatrix._24 * v2.y + storeMatrix._34 * v2.z + storeMatrix._44 * v2.w;

	mCam.SetMinMax(	v3.x + 0.1f, v4.x - 0.1f, 
					v3.y + 0.1f, v4.y - 0.1f,
					v3.z + 0.1f, v4.z - 0.1f);
}
