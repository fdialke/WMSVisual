//***************************************************************************************
// Effects.h by Frank Luna (C) 2011 All Rights Reserved.
//
// Defines lightweight effect wrappers to group an effect and its variables.
// Also defines a static Effects class from which we can access all of our effects.
//***************************************************************************************

#ifndef EFFECTS_H
#define EFFECTS_H

#include "stdafx.h"
#include "Common\d3dUtil.h"

/*
struct	EffectParam
{
	EffectParam():pCode(nullptr),dwSize(0){}

	void*	pCode;
	DWORD	dwSize;
};
*/

#pragma region Effect
class Effect
{
public:
	Effect(ID3D11Device* device, const std::wstring& filename);
//	Effect(ID3D11Device* device, void * _pCode, DWORD	_size);
	virtual ~Effect();

private:
	Effect(const Effect& rhs);
	Effect& operator=(const Effect& rhs);

protected:
	ID3DX11Effect* mFX;
};
#pragma endregion

#pragma region BasicEffect
class BasicEffect : public Effect
{
public:
	BasicEffect(ID3D11Device* device, const std::wstring& filename);
	BasicEffect(ID3D11Device* device, void * _pCode, DWORD	_size);
	~BasicEffect();

	void InitAll();

	void SetWorldViewProj(CXMMATRIX M)                  { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorld(CXMMATRIX M)                          { World->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetWorldInvTranspose(CXMMATRIX M)              { WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetTexTransform(CXMMATRIX M)                   { TexTransform->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetEyePosW(const XMFLOAT3& v)                  { EyePosW->SetRawValue(&v, 0, sizeof(XMFLOAT3)); }
	void SetFogColor(const FXMVECTOR v)                 { FogColor->SetFloatVector(reinterpret_cast<const float*>(&v)); }
	void SetFogStart(float f)                           { FogStart->SetFloat(f); }
	void SetFogRange(float f)                           { FogRange->SetFloat(f); }
	void SetDirLights(const DirectionalLight* lights)   { DirLights->SetRawValue(lights, 0, 3*sizeof(DirectionalLight)); }
	void SetMaterial(const Material& mat)               { Mat->SetRawValue(&mat, 0, sizeof(Material)); }
	void SetLocationFurnitureMap(ID3D11ShaderResourceView* tex)   { LocationFurnitureMap->SetResource(tex); }
	void SetPalletMap(ID3D11ShaderResourceView* tex)	{ PalletMap->SetResource(tex); }
	void SetAlphabet(ID3D11ShaderResourceView* tex)		{ gAlphabet->SetResource(tex); }
	void SetItemFaceMap(ID3D11ShaderResourceView* tex)	{ ItemFaceMap->SetResource(tex);}
	void SetItemSideMap(ID3D11ShaderResourceView* tex)	{ ItemSideMap->SetResource(tex);}
	void SetItemTopMap(ID3D11ShaderResourceView* tex)	{ ItemTopMap->SetResource(tex);}
	void SetTransparentMap(ID3D11ShaderResourceView* tex)	{ TransparentMap->SetResource(tex);}
	void SetArrayTexturePosition(ID3D11ShaderResourceView* tex) {gArrayTexturePosition->SetResource(tex);}


	ID3DX11EffectTechnique* Light1Tech;
	ID3DX11EffectTechnique* Light2Tech;
	ID3DX11EffectTechnique* Light3Tech;

	ID3DX11EffectTechnique* Light0TexTech;
	ID3DX11EffectTechnique* Light1TexTech;
	ID3DX11EffectTechnique* Light2TexTech;
	ID3DX11EffectTechnique* Light3TexTech;

	ID3DX11EffectTechnique* Light1TexTransparent;	
	ID3DX11EffectTechnique* Light2TexTransparent;
	ID3DX11EffectTechnique* Light3TexTransparent;

	ID3DX11EffectTechnique* Light0TexAlphaClipTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipTech;

	ID3DX11EffectTechnique* Light1FogTech;
	ID3DX11EffectTechnique* Light2FogTech;
	ID3DX11EffectTechnique* Light3FogTech;

	ID3DX11EffectTechnique* Light0TexFogTech;
	ID3DX11EffectTechnique* Light1TexFogTech;
	ID3DX11EffectTechnique* Light2TexFogTech;
	ID3DX11EffectTechnique* Light3TexFogTech;

	ID3DX11EffectTechnique* Light0TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light1TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light2TexAlphaClipFogTech;
	ID3DX11EffectTechnique* Light3TexAlphaClipFogTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;
	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* WorldInvTranspose;
	ID3DX11EffectMatrixVariable* TexTransform;
	ID3DX11EffectVectorVariable* EyePosW;
	ID3DX11EffectVectorVariable* FogColor;
	ID3DX11EffectScalarVariable* FogStart;
	ID3DX11EffectScalarVariable* FogRange;
	ID3DX11EffectVariable* DirLights;
	ID3DX11EffectVariable* Mat;

	ID3DX11EffectShaderResourceVariable* LocationFurnitureMap;

	ID3DX11EffectShaderResourceVariable* PalletMap;

	ID3DX11EffectShaderResourceVariable* gAlphabet;

	ID3DX11EffectShaderResourceVariable* ItemFaceMap;
	ID3DX11EffectShaderResourceVariable* ItemSideMap;
	ID3DX11EffectShaderResourceVariable* ItemTopMap;

	ID3DX11EffectShaderResourceVariable* TransparentMap;
	ID3DX11EffectShaderResourceVariable* gArrayTexturePosition;

	ID3DX11EffectShaderResourceVariable* CubeMap;
};
#pragma endregion

#pragma region WarehouseRoom
class RoomEffect : public Effect
{
public:
	RoomEffect(ID3D11Device*	device, std::wstring&	fxFile);
	~RoomEffect();

	void	SetWorld(CXMMATRIX M)							{World->SetMatrix(reinterpret_cast<const float*>(&M));}
	void	SetWorldInvTranspose(CXMMATRIX M)				{WorldInvTranspose->SetMatrix(reinterpret_cast<const float*>(&M));}
	void	SetWorldViewProj(CXMMATRIX M)					{WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M));}
	void	SetTexTransform(CXMMATRIX M)					{TexTransform->SetMatrix(reinterpret_cast<const float*>(&M));}
	void	SetTextureMap(ID3D11ShaderResourceView* pSRV)	{TextureMap->SetResource(pSRV);}

	ID3DX11EffectTechnique*					RoomTech;

	ID3DX11EffectMatrixVariable*			World;
	ID3DX11EffectMatrixVariable*			WorldInvTranspose;
	ID3DX11EffectMatrixVariable*			WorldViewProj;
	ID3DX11EffectMatrixVariable*			TexTransform;

	ID3DX11EffectShaderResourceVariable*	TextureMap;
};
#pragma endregion

#pragma region WMSEnvironment
class WMSEnvironment : public Effect
{
public:
	WMSEnvironment(ID3D11Device*	device, std::wstring&	fxFile);
	~WMSEnvironment();

	void SetWorldViewProj(CXMMATRIX M)                  { WorldViewProj->SetMatrix(reinterpret_cast<const float*>(&M)); }
	void SetCubeMap(ID3D11ShaderResourceView* cubemap)  { CubeMap->SetResource(cubemap); }

	ID3DX11EffectTechnique* EnvironmentTech;

	ID3DX11EffectMatrixVariable* WorldViewProj;

	ID3DX11EffectShaderResourceVariable* CubeMap;
};

#pragma endregion

#pragma region Effects
class Effects
{
public:
	static void InitAll(ID3D11Device* device, std::vector<std::wstring>&	fxArray);

	static void DestroyAll();

	static BasicEffect*		BasicFX;
	static WMSEnvironment*	WMSEnvironmentFX;
	static RoomEffect*		RoomFX;
};

#endif // EFFECTS_H