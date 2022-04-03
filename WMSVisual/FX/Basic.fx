//=============================================================================
// Basic.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Basic effect that currently supports transformations, lighting, and texturing.
//=============================================================================

#include "LightHelper.fx"

cbuffer cbPerFrame
{
	DirectionalLight gDirLights[3];
	float3 gEyePosW;

	float  gFogStart;
	float  gFogRange;
	float4 gFogColor;
};

cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldInvTranspose;
	float4x4 gWorldViewProj;
	float4x4 gTexTransform;
	Material gMaterial;
}; 

// Nonnumeric values cannot be added to a cbuffer.
Texture2D		gLocationFurnitureMap;
Texture2D		gPalletMap;

Texture2D		gItemFaceMap;
Texture2D		gItemTopMap;
Texture2D		gItemSideMap;

Texture2DArray	gAlphabet;

Texture2D		gTransparentMap;

StructuredBuffer<uint> gArrayTexturePosition;

SamplerState samAnisotropic
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};

struct VertexIn
{
	float3 PosL    : POSITION;
	float3 NormalL : NORMAL;
	float2 Tex     : TEXCOORD;
	uint   TexNum  : TEXTURENUM;
	row_major float4x4 World  : WORLD;
	float4 Color    : COLOR;
	uint InstanceId : SV_InstanceID;
	uint faceTexNum : FACETEXNUM;

	/*
	float4 element0A : ELEMENT0A;
	float4 element1A : ELEMENT1A;
	float4 element2A : ELEMENT2A;
	*/

	row_major float4x4 WorldItem : WORLDITEM;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
    float3 PosW    : POSITION;
    float3 NormalW : NORMAL;
	float2 Tex     : TEXCOORD;
	uint   TexNum  : TEXTURENUM;
	uint faceTexNum : FACETEXNUM;

	/*
	float4 element0A : ELEMENT0A;
	float4 element1A : ELEMENT1A;
	float4 element2A : ELEMENT2A;
	*/

//	float2 offsetstep : OFFSETSTEP;
};

// roms ->
float4 PS_TransparentCube(VertexOut pin, uniform int gLightCount) : SV_Target
{
	// Interpolating normal can unnormalize it, so normalize it.
    pin.NormalW = normalize(pin.NormalW);

	// The toEye vector is used in lighting.
	float3 toEye = gEyePosW - pin.PosW;

	// Cache the distance to the eye from this surface point.
	float distToEye = length(toEye); 

	// Normalize.
	toEye /= distToEye;
	
    // Default to multiplicative identity.
    float4 texColor = float4(1, 1, 1, 1);

	// Sample texture.
	texColor = gTransparentMap.Sample( samAnisotropic, pin.Tex );

	/*
	if(gAlphaClip)
	{
		// Discard pixel if texture alpha < 0.1.  Note that we do this
		// test as soon as possible so that we can potentially exit the shader 
		// early, thereby skipping the rest of the shader code.
		clip(texColor.a - 0.1f);
	}
	*/
	//
	// Lighting.
	//

	float4 litColor = texColor;
	if( gLightCount > 0  )
	{  
		// Start with a sum of zero. 
		float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

		// Sum the light contribution from each light source.  
		[unroll]
		for(int i = 0; i < gLightCount; ++i)
		{
			float4 A, D, S;
			ComputeDirectionalLight(gMaterial, gDirLights[i], pin.NormalW, toEye, 
				A, D, S);

			ambient += A;
			diffuse += D;
			spec    += S;
		}

		// Modulate with late add.
		litColor = texColor*(ambient + diffuse) + spec;
	}

	// Common to take alpha from diffuse material and texture.
	litColor.a = gMaterial.Diffuse.a * texColor.a;

    return litColor;
}
VertexOut VS_TransparentCube(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to world space space.
	
	vout.PosW    = mul(float4(vin.PosL, 1.0f), gWorld).xyz;
	vout.NormalW = mul(vin.NormalL, (float3x3)gWorld);
		
	// Transform to homogeneous clip space.
	//vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	vout.PosH = mul(float4(vout.PosW, 1.0f), gWorldViewProj);
	
	// Output vertex attributes for interpolation across triangle.
	vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;

	vout.TexNum = vin.TexNum;
	/*
	vout.element0A = vin.element0A;
	vout.element1A = vin.element1A;
	vout.element2A = vin.element2A;
	*/

	vout.faceTexNum = vin.faceTexNum;

	return vout;
}
// roms <-

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to world space space.
	
	[branch]
	if (vin.TexNum >= 8)
	{
		vout.PosW    = mul(float4(vin.PosL, 1.0f), vin.WorldItem).xyz;
		vout.NormalW = mul(vin.NormalL, (float3x3)vin.WorldItem);
	} else
	{
		vout.PosW    = mul(float4(vin.PosL, 1.0f), vin.World).xyz;
		vout.NormalW = mul(vin.NormalL, (float3x3)vin.World);
	}
		
	// Transform to homogeneous clip space.
	//vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	vout.PosH = mul(float4(vout.PosW, 1.0f), gWorldViewProj);
	
	// Output vertex attributes for interpolation across triangle.
	vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;

	vout.TexNum = vin.TexNum;
	/*
	vout.element0A = vin.element0A;
	vout.element1A = vin.element1A;
	vout.element2A = vin.element2A;
	*/
	vout.faceTexNum = vin.faceTexNum;

	return vout;
}
 
float4 PS(VertexOut pin, uniform int gLightCount, uniform bool gUseTexure) : SV_Target
{
	// Interpolating normal can unnormalize it, so normalize it.
    pin.NormalW = normalize(pin.NormalW);

	// The toEye vector is used in lighting.
	float3 toEye = gEyePosW - pin.PosW;

	// Cache the distance to the eye from this surface point.
	float distToEye = length(toEye); 

	// Normalize.
	toEye /= distToEye;
	
    // Default to multiplicative identity.
    float4 texColor = float4(1, 1, 1, 1);

    if(gUseTexure)
	{
		// Sample texture
		float4 fDiffuseMapColor = gLocationFurnitureMap.Sample( samAnisotropic, pin.Tex );
		float4 fPalletMapColor = gPalletMap.Sample( samAnisotropic, pin.Tex );

		texColor = gLocationFurnitureMap.Sample(samAnisotropic, pin.Tex)	*(pin.TexNum & 1) +
				   gPalletMap.Sample(samAnisotropic, pin.Tex)				*((pin.TexNum & 2) >> 1) +
				   gLocationFurnitureMap.Sample(samAnisotropic, pin.Tex)	*((pin.TexNum & 4) >> 2) +
				   gItemFaceMap.Sample(samAnisotropic, pin.Tex)				*((pin.TexNum & 8) >> 3) +
				   gItemSideMap.Sample(samAnisotropic, pin.Tex)				*((pin.TexNum & 16) >> 4) +
				   gItemTopMap.Sample(samAnisotropic, pin.Tex)				*((pin.TexNum & 32) >> 5);

		if (pin.TexNum&4 && pin.Tex.y >= 0.9f && pin.Tex.y <= 1.0f && pin.Tex.x >= 0.1f && pin.Tex.x <= 0.9f)
		{
			int		array_position;
			float3	tmpTex;

			tmpTex.x = modf((pin.Tex.x - 0.1f) * 10.0f / 0.8f, array_position);
			tmpTex.y = (pin.Tex.y - 0.9f) / 0.1f;
			tmpTex.z = gArrayTexturePosition[(10 * pin.faceTexNum) + array_position];

            float4 tmpColor= gAlphabet.Sample( samAnisotropic, tmpTex);

            if (tmpColor.a)
                texColor = tmpColor;
		}
		
		clip(texColor.a - 0.25f);
	}
	 
	//
	// Lighting.
	//

	float4 litColor = texColor;
	if( gLightCount > 0  )
	{  
		// Start with a sum of zero. 
		float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

		// Sum the light contribution from each light source.  
		[unroll]
		for(int i = 0; i < gLightCount; ++i)
		{
			float4 A, D, S;
			ComputeDirectionalLight(gMaterial, gDirLights[i], pin.NormalW, toEye, 
				A, D, S);

			ambient += A;
			diffuse += D;
			spec    += S;
		}

		// Modulate with late add.
		litColor = texColor*(ambient + diffuse) + spec;
	}

	// Common to take alpha from diffuse material and texture.
	litColor.a = gMaterial.Diffuse.a * texColor.a;

    return litColor;
}

technique11 Light1
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(1, false) ) );
    }
}

technique11 Light2
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(2, false) ) );
    }
}

technique11 Light3
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(3, false) ) );
    }
}

technique11 Light0Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(0, true) ) );
    }
}

technique11 Light1Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(1, true) ) );
    }
}

technique11 Light2Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(2, true) ) );
    }
}

technique11 Light2TexTransparent
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS_TransparentCube() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS_TransparentCube(2) ) );
    }
}


technique11 Light3Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(3, true) ) );
    }
}
