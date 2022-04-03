#pragma once
#include "stdafx.h"
#include "Common\d3dUtil.h"
#include <map>
#include <atlbase.h>

#ifndef _CHARTEXTURE_H_
#define _CHARTEXTURE_H_


struct CharTexture
{
	const char *	c;
	char			xByte;
	unsigned char	bm;
	POINT			origin;
	POINT			size;
	unsigned char	aw;
	unsigned char	lsb;
};

class TextWrapper
{
public:
	TextWrapper();
	~TextWrapper();

	LONG	getMaxWidth();
	LONG	getMaxHeight();

	void						SetDeviceContext(	ID3D11Device*			pDevice, 
													ID3D11DeviceContext*	pDeviceContext, 
													HINSTANCE				hinstance);
	void						CreateTextureArray();
	ID3D11ShaderResourceView*	getAlphabetShaderResourceView();
	void						AddText(unsigned long	_num);
	int							getCharPosition(char c);
	int							getCharPosition(const char c[2]);

private:

	void						LoadTextureData();

	std::vector<CharTexture>	m_listCharTexture;
	std::vector<std::string>	m_listLocationName;
	std::map<char, int>			m_mapCharTexture;

	LONG						m_maxWidth;
	LONG						m_maxHeight;

	ID3D11DeviceContext*		m_md3deviceContext;
	ID3D11Device*				m_md3device;

	ID3D11Texture2D *			m_pTextureAlphabet;
	ID3D11ShaderResourceView *	m_pShaderResourceView;

	HINSTANCE					m_hInstance;
};

#endif