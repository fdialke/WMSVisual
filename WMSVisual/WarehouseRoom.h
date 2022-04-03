#ifndef WarehouseRoom_H
#define WarehouseRoom_H

#pragma once

#include "stdafx.h"
#include "WMSCamera.h"
#include <d3d11.h>
#include "WMSLocation.h"

class WarehouseRoom
{
public:
	WarehouseRoom(ID3D11Device* device, WMSLocationWrapper*	pLocationWrapper);
	~WarehouseRoom();

	ID3D11ShaderResourceView* CeilingSRV();
	ID3D11ShaderResourceView* WallSRV();
	ID3D11ShaderResourceView* FloorSRV();

	void Draw(ID3D11DeviceContext* dc, const WMSCamera& camera);
	void	ComputeInnerMatrix(WMSCamera& camera);

	void* operator new(size_t i)
	{
		return _aligned_malloc(i, 16);
	}

	void operator delete(void* p)
	{
		_aligned_free(p);
	}

private:
	WarehouseRoom(const WarehouseRoom& rhs);
	WarehouseRoom& operator=(const WarehouseRoom& rhs);

private:
	ID3D11Buffer* mCeilingVB;
	ID3D11Buffer* mCeilingIB;

	ID3D11Buffer* mWallVB;
	ID3D11Buffer* mWallIB;

	ID3D11Buffer* mFloorVB;
	ID3D11Buffer* mFloorIB;

	ID3D11ShaderResourceView* mCeilingSRV;
	ID3D11ShaderResourceView* mWallSRV;
	ID3D11ShaderResourceView* mFloorSRV;

	WMSLocationWrapper*		m_pLocationWrapper;

	XMMATRIX				FloorWorldMatrix;
	XMMATRIX				CeilingWorldMatrix;
	XMMATRIX				WallWorldMatrix;

	XMMATRIX				FloorTexMatrix;
	XMMATRIX				CeilingTexMatrix;
	XMMATRIX				WallTexMatrix;
};

#endif

