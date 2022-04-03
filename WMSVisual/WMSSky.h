#ifndef WMSSKY_H
#define WMSSKY_H

#include "stdafx.h"
#include "WMSCamera.h"
#include <d3d11.h>
//#include <string>

class Sky
{
public:
	Sky(ID3D11Device* device, std::wstring& cubemapFilename, float skySphereRadius);
//	Sky(ID3D11Device* device, void * pData, DWORD	dwSize, float skySphereRadius);
	~Sky();

	ID3D11ShaderResourceView* CubeMapSRV();

	void Draw(ID3D11DeviceContext* dc, const WMSCamera& camera);

private:
	Sky(const Sky& rhs);
	Sky& operator=(const Sky& rhs);

private:
	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;

	ID3D11ShaderResourceView* mCubeMapSRV;

	UINT mIndexCount;
};

#endif // WMSSKY_H