// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef STRICT
#define STRICT
#endif

#include "targetver.h"

#define _ATL_APARTMENT_THREADED

#define _ATL_NO_AUTOMATIC_NAMESPACE

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit


#define ATL_NO_ASSERT_ON_DESTROY_NONEXISTENT_WINDOW


#include "resource.h"
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <map>
#include <string>

struct MD5Digit
{
	unsigned char	hex[16];

	MD5Digit(unsigned char c1,
			 unsigned char c2,
			 unsigned char c3,
			 unsigned char c4,
			 unsigned char c5,
			 unsigned char c6,
			 unsigned char c7,
			 unsigned char c8,
			 unsigned char c9,
			 unsigned char c10,
			 unsigned char c11,
			 unsigned char c12,
			 unsigned char c13,
			 unsigned char c14,
			 unsigned char c15,
			 unsigned char c16)
	{
		hex[0] = c1;
		hex[1] = c2;
		hex[2] = c3;
		hex[3] = c4;
		hex[4] = c5;
		hex[5] = c6;
		hex[6] = c7;
		hex[7] = c8;
		hex[8] = c9;
		hex[9] = c10;
		hex[10] = c11;
		hex[11] = c12;
		hex[12] = c13;
		hex[13] = c14;
		hex[14] = c15;
		hex[15] = c16;
	}
};

extern "C"	std::map<std::wstring, MD5Digit>	mapFileMD5;
extern "C"	std::wstring						dllDirectoryData;
extern "C"	HINSTANCE							globalHinstance;
extern "C"	HANDLE								hEventHandle;

#define	SHADERMAIN			L"Shader.Main"
#define SHADERROOM			L"Shader.Room"
#define	SHADERENVIRONMENT	L"Shader.Environment"
#define	TEXALPHA			L"Tex.Alpha"
#define TEXENVIRONMENT		L"Tex.Environment"
#define TEXLOCATION			L"Tex.Location"
#define TEXPALLET			L"Tex.Pallet"
#define TEXBOXTOP			L"Tex.BoxTop"
#define TEXBOXFACE			L"Tex.BoxFace"
#define TEXBOXSIDE			L"Tex.BoxSide"
#define TEXSELECT			L"Tex.Select"
#define TEXROOMTOP			L"Tex.RoomTop"
#define TEXROOMSIDE			L"Tex.RoomSide"
#define TEXROOMFLOOR		L"Tex.RoomFloor"

#define ERRORMESSAGE	L"You are using NOT licensed Columbus WMS 3D"
#define	ERRMESSAGEBOX	MessageBox(nullptr, (LPCWSTR)ERRORMESSAGE, L"Error", 0)

std::wstring	getFullFileName(const std::wstring	fileName);


/*
#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HRWMS
	#define HRWMS(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			ATLTRACE(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
	#endif

#else
	*/
	#ifndef HRWMS
	#define HRWMS(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			WCHAR	lineStr[20] = {0}, hrStr[20] = {0}, fileStr[_MAX_PATH]={0};	\
			swprintf_s(lineStr, 20, L"%d", (DWORD)__LINE__);				\
			swprintf_s(hrStr, 20, L"0x%X", hr);								\
			swprintf_s(fileStr, _MAX_PATH, L"%hs", __FILE__);						\
			LPCTSTR ppParams[5] = {_T("\n"), fileStr, lineStr, hrStr, L#x};	\
			ReportEvent(hEventHandle, EVENTLOG_ERROR_TYPE, 0, 0, nullptr, 5, 0, ppParams, NULL); \
		}                                                      \
	}
	#endif
//#endif 
