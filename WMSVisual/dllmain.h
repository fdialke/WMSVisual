// dllmain.h : Declaration of module class.

class CWMSVisualModule : public ATL::CAtlDllModuleT< CWMSVisualModule >
{
public :
	DECLARE_LIBID(LIBID_WMSVisualLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_WMSVISUAL, "{4B7DBD9D-9329-4509-B859-D41D0EAFFFA5}")
};

extern class CWMSVisualModule _AtlModule;
