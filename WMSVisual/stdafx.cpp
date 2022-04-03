// stdafx.cpp : source file that includes just the standard includes
// WMSVisual.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"

std::map<std::wstring, MD5Digit>	mapFileMD5;
std::wstring								dllDirectoryData;
HINSTANCE							globalHinstance;
HANDLE								hEventHandle;

std::wstring	getFullFileName(const std::wstring	fileName)
{
	return dllDirectoryData + fileName;
}
