// WMSVisual.cpp : Implementation of DLL Exports.


#include "stdafx.h"
#include "resource.h"
#include "WMSVisual_i.h"
#include "dllmain.h"
#include "md5.h"


// Used to determine whether the DLL can be unloaded by OLE.
STDAPI DllCanUnloadNow(void)
{
			return _AtlModule.DllCanUnloadNow();
	}

// Returns a class factory to create an object of the requested type.
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	WCHAR	dllDirectoryTmp[MAX_PATH] = {0};
	GetModuleFileName((HMODULE)globalHinstance, dllDirectoryTmp, MAX_PATH);
	PathRemoveFileSpec(dllDirectoryTmp);

	dllDirectoryData	= std::wstring(dllDirectoryTmp) + std::wstring(L"\\Data\\");

	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(SHADERMAIN,			MD5Digit(137, 149, 246, 162, 28, 151, 139, 40, 228, 101, 88, 149, 121, 202, 102, 53)));
	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(SHADERENVIRONMENT,	MD5Digit(31, 238, 108, 239, 15, 204, 234, 95, 66, 201, 212, 243, 149, 64, 98, 79)));
	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(SHADERROOM,			MD5Digit(13, 117, 5, 232, 88, 172, 217, 157,19, 244, 13, 215, 225, 145, 90, 236)));
	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(TEXALPHA,			MD5Digit(38, 90, 10, 215, 122, 143, 41, 178, 30, 179, 51, 22, 228, 56, 48, 111)));
	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(TEXENVIRONMENT,		MD5Digit(126, 28, 246, 120, 184, 198, 187, 98, 181, 33, 166, 59, 167, 208, 152, 67)));
	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(TEXLOCATION,		MD5Digit(208, 11, 155, 87, 141, 23, 152, 7, 169, 81, 13, 105, 22, 6, 41, 141)));
	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(TEXPALLET,			MD5Digit(71, 103, 84, 28, 6, 217, 47, 18, 255, 51, 224, 241, 207, 163, 150, 129)));

	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(TEXBOXTOP,			MD5Digit(25, 2, 236, 177, 136, 66, 169, 27, 132, 128, 197, 68, 24, 219, 105, 90)));
	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(TEXBOXFACE,			MD5Digit(161, 230, 179, 199, 251, 147, 6, 209, 25, 127, 32, 153, 180, 59, 115, 248))); 
	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(TEXBOXSIDE,			MD5Digit(63, 2, 121, 71, 183, 206, 161, 248, 199, 14, 181, 122, 173, 206, 225, 53)));

	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(TEXSELECT,			MD5Digit(1, 54, 34, 13, 11, 25, 14, 168, 21, 155, 244, 236, 129, 128, 207, 168)));
	
	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(TEXROOMTOP,			MD5Digit(194, 195, 204, 238, 221, 12, 202, 75, 28, 186, 94, 196, 187, 30, 0, 53)));
	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(TEXROOMSIDE,		MD5Digit(25, 172, 204, 31, 190, 191, 83, 244, 164, 203, 191, 96, 190, 118, 72, 59)));
	mapFileMD5.insert(std::pair<std::wstring, MD5Digit>(TEXROOMFLOOR,		MD5Digit(160, 144, 113, 59, 196, 243, 127, 31, 137, 229, 149, 206, 25, 185, 198, 185)));


	for (auto it = mapFileMD5.begin(); it != mapFileMD5.end(); ++it)	
	{
		std::wstring	fullFileName = getFullFileName(it->first);

		std::ifstream fin(fullFileName, std::ios::binary);

		if (fin.is_open())
		{
			MD5	md5Check = MD5(fin);
			md5Check.finalize();
			unsigned char* raw_digest = md5Check.raw_digest();

			if (it == mapFileMD5.end())
			{
				return CLASS_E_NOTLICENSED;
			}

			for (int	i = 0; i < 16; i++)
			{
				if (raw_digest[i] != it->second.hex[i])
				{
					delete[] raw_digest;

					std::wstring	msg;
					msg =	L"Данное программное обеспечение модифицировано";

					MessageBox(nullptr, msg.c_str(), L"Error", MB_ICONERROR);

					return CLASS_E_NOTLICENSED;
				}
			}

			delete[] raw_digest;
		} else
		{
			std::wstring	msg;
			msg =	L"Файл ";
			msg	+=	fullFileName;
			msg	+=	L" не найден";

			MessageBox(nullptr, msg.c_str(), L"Error", MB_ICONERROR);

			return CLASS_E_CLASSNOTAVAILABLE;
		}
	}


	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}

// DllRegisterServer - Adds entries to the system registry.
STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	HRESULT hr = _AtlModule.DllRegisterServer();
		return hr;
}

// DllUnregisterServer - Removes entries from the system registry.
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
		return hr;
}

// DllInstall - Adds/Removes entries to the system registry per user per machine.
STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
	HRESULT hr = E_FAIL;
	static const wchar_t szUserSwitch[] = L"user";

	if (pszCmdLine != NULL)
	{
		if (_wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0)
		{
			ATL::AtlSetPerUserRegistration(true);
		}
	}

	if (bInstall)
	{	
		hr = DllRegisterServer();
		if (FAILED(hr))
		{
			DllUnregisterServer();
		}
	}
	else
	{
		hr = DllUnregisterServer();
	}

	return hr;
}


