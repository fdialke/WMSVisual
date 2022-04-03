#include "stdafx.h"
#include "WMSVisualControl.h"
#include "WMSVisualControlImpl.h"

CWMSVisualControl::CWMSVisualControl()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	hEventHandle = nullptr;
	hEventHandle = OpenEventLog(nullptr, L"ColumbusWMS3D");

	m_bWindowOnly = TRUE;

	_impl = new CWMSVisualControlImpl(this);
}

CWMSVisualControl::~CWMSVisualControl()
{
	delete _impl;

	CloseEventLog(hEventHandle);

#if defined(DEBUG) | defined(_DEBUG)
	_CrtCheckMemory();
#endif
}
HRESULT CWMSVisualControl::OnDrawAdvanced(ATL_DRAWINFO & di)
{
	return _impl->OnDraw(di);
}
LRESULT CWMSVisualControl::OnCreate(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
	return _impl->OnCreate(msg, wParam, lParam, handled);
}

LRESULT CWMSVisualControl::OnDestroy(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
	return _impl->OnDestroy(msg, wParam, lParam, handled);
}

LRESULT CWMSVisualControl::OnSize(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
	return _impl->OnSize(msg, wParam, lParam, handled);
}

LRESULT CWMSVisualControl::OnTimer(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& handled)
{
	return _impl->OnTimer(msg, wParam, lParam, handled);
}
LRESULT CWMSVisualControl::OnMouseUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return _impl->OnMouseUp(uMsg, wParam, lParam, bHandled);
}
LRESULT CWMSVisualControl::OnMouseDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return _impl->OnMouseDown(uMsg, wParam, lParam, bHandled);
}
LRESULT CWMSVisualControl::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return _impl->OnMouseMove(uMsg, wParam, lParam, bHandled);
}
LRESULT CWMSVisualControl::OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return _impl->OnChar(uMsg, wParam, lParam,  bHandled);
}
LRESULT CWMSVisualControl::OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return _impl->OnKeyUp( uMsg,  wParam,  lParam,  bHandled);
}
LRESULT CWMSVisualControl::OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return _impl->OnActivate( uMsg,  wParam,  lParam,  bHandled);
}
LRESULT CWMSVisualControl::OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return _impl->OnSetFocus( uMsg,  wParam,  lParam,  bHandled);
}
LRESULT CWMSVisualControl::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return _impl->OnKillFocus( uMsg,  wParam,  lParam,  bHandled);
}
LRESULT CWMSVisualControl::OnEnterSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return _impl->OnEnterSizeMove(uMsg,  wParam,  lParam,  bHandled);
}
LRESULT CWMSVisualControl::OnExitSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return _impl->OnExitSizeMove(uMsg,  wParam,  lParam,  bHandled);
}
STDMETHODIMP CWMSVisualControl::DeleteAllLocations(void)
{
	return _impl->DeleteAllLocations();
}
STDMETHODIMP CWMSVisualControl::AddLocation(BSTR InventLocationName, BSTR WMSLocationName, ULONG ShiftX, ULONG ShiftY, ULONG ShiftZ, BYTE Rotation, FLOAT FillingPercent)
{
	std::string	stdStringInventLocationName = _bstr_t(InventLocationName),
				stdStringWMSLocationName = _bstr_t(WMSLocationName);

	HRESULT	hResult = S_OK;

	try
	{
		hResult = _impl->AddLocation(	stdStringInventLocationName,
									stdStringWMSLocationName,
									ShiftX, ShiftY, ShiftZ, Rotation, FillingPercent);
	}
	catch(...)
	{
		HRWMS(hResult);
	}

	return hResult;
}


STDMETHODIMP CWMSVisualControl::BuildScene(void)
{
	HRESULT	hResult = S_OK;

	try
	{
		hResult = _impl->BuildScene();
	}
	catch(...)
	{
		HRWMS(hResult);
	}

	return hResult;
}


STDMETHODIMP CWMSVisualControl::get_pickedLocation(BSTR* pickingInventLocation, BSTR* pVal)
{
	std::string	inventLocation, wmsLocation;
	
	_impl->GetPickedLocation(inventLocation, wmsLocation);

	*pickingInventLocation	= CComBSTR(inventLocation.c_str()).Detach();
	*pVal					= CComBSTR(wmsLocation.c_str()).Detach();

	return S_OK;
}
HRESULT CWMSVisualControl::DoVerbUIActivate(LPCRECT prcPosRect, HWND hWnd)
{
	_impl->mAppPaused = false;

	return IOleObjectImpl<CWMSVisualControl>::DoVerbUIActivate(prcPosRect, hWnd);
}
STDMETHODIMP CWMSVisualControl::UpdateLocationFillingPercent(BSTR inventLocationName, BSTR wmsLocationName, FLOAT fillingPercent)
{
	std::string		il = _bstr_t(inventLocationName), wl = _bstr_t(wmsLocationName);

	return _impl->UpdateLocationFill(il, wl, fillingPercent);
}


STDMETHODIMP CWMSVisualControl::UpdateScene(void)
{	
	return _impl->UpdateSceneFill();
}


STDMETHODIMP CWMSVisualControl::get_minFillPercent(FLOAT* pVal)
{
	return _impl->locationWrapper.get_minFillPercent(pVal);
}


STDMETHODIMP CWMSVisualControl::put_minFillPercent(FLOAT newVal)
{
	return _impl->locationWrapper.put_minFillPercent(newVal);
}


STDMETHODIMP CWMSVisualControl::get_maxFillPercent(FLOAT* pVal)
{
	return _impl->locationWrapper.get_maxFillPercent(pVal);
}


STDMETHODIMP CWMSVisualControl::put_maxFillPercent(FLOAT newVal)
{
	return _impl->locationWrapper.put_maxFillPercent(newVal);
}


STDMETHODIMP CWMSVisualControl::SetLocationStatus(BSTR inventLocationName, BSTR wmsLocationName, SHORT bShow, ULONG dwStatus)
{
	std::string	il = _bstr_t(inventLocationName), wl = _bstr_t(wmsLocationName);

	return _impl->SetLocationStatus(il, wl, bShow, dwStatus);
}


STDMETHODIMP CWMSVisualControl::GetErrorDescription(BSTR* errorDescription)
{
	IErrorInfo*	pErrorInfo = nullptr;

	GetErrorInfo(0, &pErrorInfo);

	if (pErrorInfo != nullptr)
	{
		pErrorInfo->GetDescription(errorDescription);

		pErrorInfo->Release();

		return S_OK;
	}

	return S_FALSE;
}


STDMETHODIMP CWMSVisualControl::SetSourceLocation(BSTR InventLocationName, BSTR WMSLocationName)
{
	std::string	il = _bstr_t(InventLocationName), wl = _bstr_t(WMSLocationName);

	return _impl->SetSourceLocation(il, wl);
}


STDMETHODIMP CWMSVisualControl::SetDestinationLocation(BSTR InventLocationName, BSTR WMSLocationName)
{
	std::string	il = _bstr_t(InventLocationName), wl = _bstr_t(WMSLocationName);

	return _impl->SetDestinationLocation(il, wl);
}


STDMETHODIMP CWMSVisualControl::ClearSourceDestLocation(void)
{
	return _impl->ClearSourceDestLocation();
}
