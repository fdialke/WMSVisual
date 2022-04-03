// WMSVisualControl.h : Declaration of the CWMSVisualControl
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "WMSVisual_i.h"
#include "_IWMSVisualControlEvents_CP.h"
#include <vector>
#include <d3d11.h>
#include <xnamath.h>
//#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <comdef.h>

#include "MathHelper.h"

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dcompiler.lib")

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;
//using namespace DirectX;

class CWMSVisualControlLic
{
protected:
   static BOOL VerifyLicenseKey(BSTR bstr)
   {
      return !lstrcmpW(bstr, L"WMSVisualControl license");
   }

   static BOOL GetLicenseKey(DWORD dwReserved, BSTR* pBstr)
   {
   	  if( pBstr == NULL )
 		return FALSE;
      *pBstr = SysAllocString(L"WMSVisualControl license");
      return TRUE;
   }

   static BOOL IsLicenseValid()
   {
	   return TRUE;
   }
};


// CWMSVisualControl
class ATL_NO_VTABLE CWMSVisualControl :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CWMSVisualControl, IWMSVisualControl>,
	public IPersistStreamInitImpl<CWMSVisualControl>,
	public IOleControlImpl<CWMSVisualControl>,
	public IOleObjectImpl<CWMSVisualControl>,
	public IOleInPlaceActiveObjectImpl<CWMSVisualControl>,
	public IViewObjectExImpl<CWMSVisualControl>,
	public IOleInPlaceObjectWindowlessImpl<CWMSVisualControl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CWMSVisualControl>,
	public CProxy_IWMSVisualControlEvents<CWMSVisualControl>,
	public IObjectWithSiteImpl<CWMSVisualControl>,
	public IServiceProviderImpl<CWMSVisualControl>,
	public IPersistStorageImpl<CWMSVisualControl>,
	public ISpecifyPropertyPagesImpl<CWMSVisualControl>,
	public IQuickActivateImpl<CWMSVisualControl>,
#ifndef _WIN32_WCE
	public IDataObjectImpl<CWMSVisualControl>,
#endif
	public IProvideClassInfo2Impl<&CLSID_WMSVisualControl, &__uuidof(_IWMSVisualControlEvents), &LIBID_WMSVisualLib>,
	public IPropertyNotifySinkCP<CWMSVisualControl>,
	public IObjectSafetyImpl<CWMSVisualControl, INTERFACESAFE_FOR_UNTRUSTED_CALLER>,
	public CComCoClass<CWMSVisualControl, &CLSID_WMSVisualControl>,
	public CComControl<CWMSVisualControl>
{
public:


	CWMSVisualControl();
	~CWMSVisualControl();

DECLARE_CLASSFACTORY2(CWMSVisualControlLic)

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_INSIDEOUT |
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_WMSVISUALCONTROL)


BEGIN_COM_MAP(CWMSVisualControl)
	COM_INTERFACE_ENTRY(IWMSVisualControl)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
#ifndef _WIN32_WCE
	COM_INTERFACE_ENTRY(IDataObject)
#endif
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IServiceProvider)
	COM_INTERFACE_ENTRY_IID(IID_IObjectSafety, IObjectSafety)
END_COM_MAP()

BEGIN_PROP_MAP(CWMSVisualControl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY_TYPE("Property Name", dispid, clsid, vtType)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CWMSVisualControl)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
	CONNECTION_POINT_ENTRY(__uuidof(_IWMSVisualControlEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CWMSVisualControl)
	MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
	MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
	MESSAGE_HANDLER(WM_SIZE, OnSize)
//	MESSAGE_HANDLER(WM_TIMER, OnTimer)
	MESSAGE_HANDLER(WM_LBUTTONUP, OnMouseUp)
	MESSAGE_HANDLER(WM_MBUTTONUP, OnMouseUp)
	MESSAGE_HANDLER(WM_RBUTTONUP, OnMouseUp)
	MESSAGE_HANDLER(WM_LBUTTONDOWN, OnMouseDown)
	MESSAGE_HANDLER(WM_MBUTTONDOWN, OnMouseDown)
	MESSAGE_HANDLER(WM_RBUTTONDOWN, OnMouseDown)
	MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
	MESSAGE_HANDLER(WM_ACTIVATE, OnActivate)
	MESSAGE_HANDLER(WM_ENTERSIZEMOVE, OnEnterSizeMove)
	MESSAGE_HANDLER(WM_EXITSIZEMOVE, OnExitSizeMove)
	CHAIN_MSG_MAP(CComControl<CWMSVisualControl>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* const arr[] =
		{
			&IID_IWMSVisualControl,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IWMSVisualControl
public:
	HRESULT OnDrawAdvanced(ATL_DRAWINFO& di);

	STDMETHOD(_InternalQueryService)(REFGUID /*guidService*/, REFIID /*riid*/, void** /*ppvObject*/)
	{
		return E_NOTIMPL;
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

		class CWMSVisualControlImpl;
		CWMSVisualControlImpl *_impl;

	private:
		LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
		LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
		LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
		LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

		LRESULT OnMouseUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnMouseDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		LRESULT OnChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		LRESULT OnActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		LRESULT OnEnterSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnExitSizeMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

		CWMSVisualControl(const CWMSVisualControl& copy);
public:
	HRESULT DoVerbUIActivate(LPCRECT prcPosRect, HWND /* hwndParent */);

public:
	STDMETHOD(DeleteAllLocations)(void);
	STDMETHOD(AddLocation)(BSTR InventLocationName, BSTR WMSLocationName, ULONG ShiftX, ULONG ShiftY, ULONG ShiftZ, BYTE Rotation, FLOAT FillingPercent);
	STDMETHOD(BuildScene)(void);
	STDMETHOD(get_pickedLocation)(BSTR* pickingInventLocation, BSTR* pVal);
	STDMETHOD(UpdateLocationFillingPercent)(BSTR inventLocationName, BSTR wmsLocationName, FLOAT fillingPercent);
	STDMETHOD(UpdateScene)(void);
	STDMETHOD(get_minFillPercent)(FLOAT* pVal);
	STDMETHOD(put_minFillPercent)(FLOAT newVal);
	STDMETHOD(get_maxFillPercent)(FLOAT* pVal);
	STDMETHOD(put_maxFillPercent)(FLOAT newVal);
	STDMETHOD(SetLocationStatus)(BSTR inventLocationName, BSTR wmsLocationName, SHORT bShow, ULONG dwStatus);
	STDMETHOD(GetErrorDescription)(BSTR* errorDescription);
	STDMETHOD(SetSourceLocation)(BSTR InventLocationName, BSTR WMSLocationName);
	STDMETHOD(SetDestinationLocation)(BSTR InventLocationName, BSTR WMSLocationName);
	STDMETHOD(ClearSourceDestLocation)(void);
};

OBJECT_ENTRY_AUTO(__uuidof(WMSVisualControl), CWMSVisualControl)
