//***************************************************************************************
// RenderStates.cpp by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#include "stdafx.h"
#include "RenderStates.h"

ID3D11RasterizerState* RenderStates::WireframeRS = nullptr;
ID3D11RasterizerState* RenderStates::NoCullRS    = nullptr;
	 
ID3D11BlendState*      RenderStates::AlphaToCoverageBS = nullptr;
ID3D11BlendState*      RenderStates::TransparentBS     = nullptr;

ID3D11DepthStencilState* RenderStates::LessEqualDSS = nullptr;

ID3D11RasterizerState* RenderStates::CCWcullMode = nullptr;
ID3D11RasterizerState* RenderStates::CWcullMode = nullptr;


void RenderStates::InitAll(ID3D11Device * device)
{
	//
	// WireframeRS
	//
	D3D11_RASTERIZER_DESC wireframeDesc;
	ZeroMemory(&wireframeDesc, sizeof(D3D11_RASTERIZER_DESC));
	wireframeDesc.FillMode = D3D11_FILL_WIREFRAME;
	wireframeDesc.CullMode = D3D11_CULL_BACK;
	wireframeDesc.FrontCounterClockwise = false;
	wireframeDesc.DepthClipEnable = true;

	HRWMS(device->CreateRasterizerState(&wireframeDesc, &WireframeRS));

	//
	// NoCullRS
	//

	#define 	F2DW(x)   (*(DWORD*)(&x))
	
	float g_fDepthBias				= -0.0005f;

	D3D11_RASTERIZER_DESC noCullDesc;
	ZeroMemory(&noCullDesc, sizeof(D3D11_RASTERIZER_DESC));
	noCullDesc.FillMode = D3D11_FILL_SOLID;
	noCullDesc.CullMode = D3D11_CULL_NONE;
	noCullDesc.FrontCounterClockwise = false;
	noCullDesc.DepthClipEnable = true;
//	noCullDesc.DepthBias = F2DW(g_fDepthBias);

	HRWMS(device->CreateRasterizerState(&noCullDesc, &NoCullRS));

	//
	// AlphaToCoverageBS
	//

	D3D11_BLEND_DESC alphaToCoverageDesc = {0};
	alphaToCoverageDesc.AlphaToCoverageEnable = true;
	alphaToCoverageDesc.IndependentBlendEnable = false;
	alphaToCoverageDesc.RenderTarget[0].BlendEnable = false;
	alphaToCoverageDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRWMS(device->CreateBlendState(&alphaToCoverageDesc, &AlphaToCoverageBS));

	//
	// TransparentBS
	//

	D3D11_BLEND_DESC transparentDesc = {0};
	transparentDesc.AlphaToCoverageEnable = false;
	transparentDesc.IndependentBlendEnable = false;

	transparentDesc.RenderTarget[0].BlendEnable = true;
	transparentDesc.RenderTarget[0].SrcBlend       = D3D11_BLEND_SRC_ALPHA;
	transparentDesc.RenderTarget[0].DestBlend      = D3D11_BLEND_INV_SRC_ALPHA;
	transparentDesc.RenderTarget[0].BlendOp        = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].SrcBlendAlpha  = D3D11_BLEND_ONE;
	transparentDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	transparentDesc.RenderTarget[0].BlendOpAlpha   = D3D11_BLEND_OP_ADD;
	transparentDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRWMS(device->CreateBlendState(&transparentDesc, &TransparentBS));

	//
	// LessEqualDSS
	//

	D3D11_DEPTH_STENCIL_DESC lessEqualDesc;
	lessEqualDesc.DepthEnable      = true;
	lessEqualDesc.DepthWriteMask   = D3D11_DEPTH_WRITE_MASK_ALL;
    lessEqualDesc.DepthFunc        = D3D11_COMPARISON_LESS_EQUAL; 
    lessEqualDesc.StencilEnable    = false;

	HRWMS(device->CreateDepthStencilState(&lessEqualDesc, &LessEqualDSS));

	D3D11_RASTERIZER_DESC cmdesc;
	ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
    
	cmdesc.FillMode = D3D11_FILL_SOLID;
	cmdesc.CullMode = D3D11_CULL_BACK;
    
	cmdesc.FrontCounterClockwise = true;
	HRWMS(device->CreateRasterizerState(&cmdesc, &CCWcullMode));

	cmdesc.FrontCounterClockwise = false;
	HRWMS(device->CreateRasterizerState(&cmdesc, &CWcullMode));
}

void RenderStates::DestroyAll()
{
	ReleaseCOM(CCWcullMode);
	ReleaseCOM(CWcullMode);
	ReleaseCOM(WireframeRS);
	ReleaseCOM(NoCullRS);
	ReleaseCOM(AlphaToCoverageBS);
	ReleaseCOM(TransparentBS);
	ReleaseCOM(LessEqualDSS);
}