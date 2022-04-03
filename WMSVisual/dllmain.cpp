// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "WMSVisual_i.h"
#include "dllmain.h"

CWMSVisualModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	hInstance;
	
	globalHinstance = hInstance;

	return _AtlModule.DllMain(dwReason, lpReserved); 
}
