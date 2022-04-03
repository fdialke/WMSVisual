

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Apr 30 16:59:40 2016
 */
/* Compiler settings for WMSVisual.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __WMSVisual_i_h__
#define __WMSVisual_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IWMSVisualControl_FWD_DEFINED__
#define __IWMSVisualControl_FWD_DEFINED__
typedef interface IWMSVisualControl IWMSVisualControl;
#endif 	/* __IWMSVisualControl_FWD_DEFINED__ */


#ifndef ___IWMSVisualControlEvents_FWD_DEFINED__
#define ___IWMSVisualControlEvents_FWD_DEFINED__
typedef interface _IWMSVisualControlEvents _IWMSVisualControlEvents;
#endif 	/* ___IWMSVisualControlEvents_FWD_DEFINED__ */


#ifndef __WMSVisualControl_FWD_DEFINED__
#define __WMSVisualControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class WMSVisualControl WMSVisualControl;
#else
typedef struct WMSVisualControl WMSVisualControl;
#endif /* __cplusplus */

#endif 	/* __WMSVisualControl_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IWMSVisualControl_INTERFACE_DEFINED__
#define __IWMSVisualControl_INTERFACE_DEFINED__

/* interface IWMSVisualControl */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IWMSVisualControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("6B24A30F-75AF-4C2F-BCE4-D9C465D59FCF")
    IWMSVisualControl : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_HWND( 
            /* [retval][out] */ LONG_PTR *pHWND) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE DeleteAllLocations( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE AddLocation( 
            BSTR InventLocationName,
            BSTR WMSLocationName,
            ULONG ShiftX,
            ULONG ShiftY,
            ULONG ShiftZ,
            BYTE Rotation,
            FLOAT FillingPercent) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE BuildScene( void) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_pickedLocation( 
            /* [out] */ BSTR *pickingInventLocation,
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UpdateLocationFillingPercent( 
            /* [in] */ BSTR inventLocationName,
            /* [in] */ BSTR wmsLocationName,
            /* [in] */ FLOAT fillingPercent) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE UpdateScene( void) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_minFillPercent( 
            /* [retval][out] */ FLOAT *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_minFillPercent( 
            /* [in] */ FLOAT newVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_maxFillPercent( 
            /* [retval][out] */ FLOAT *pVal) = 0;
        
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_maxFillPercent( 
            /* [in] */ FLOAT newVal) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetLocationStatus( 
            /* [in] */ BSTR inventLocationName,
            /* [in] */ BSTR wmsLocationName,
            /* [in] */ SHORT bShow,
            /* [in] */ ULONG dwStatus) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetErrorDescription( 
            /* [out] */ BSTR *errorDescription) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetSourceLocation( 
            /* [in] */ BSTR InventLocationName,
            /* [in] */ BSTR WMSLocationName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetDestinationLocation( 
            /* [in] */ BSTR InventLocationName,
            /* [in] */ BSTR WMSLocationName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE ClearSourceDestLocation( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IWMSVisualControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IWMSVisualControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IWMSVisualControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IWMSVisualControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IWMSVisualControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IWMSVisualControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IWMSVisualControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IWMSVisualControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_HWND )( 
            IWMSVisualControl * This,
            /* [retval][out] */ LONG_PTR *pHWND);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *DeleteAllLocations )( 
            IWMSVisualControl * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *AddLocation )( 
            IWMSVisualControl * This,
            BSTR InventLocationName,
            BSTR WMSLocationName,
            ULONG ShiftX,
            ULONG ShiftY,
            ULONG ShiftZ,
            BYTE Rotation,
            FLOAT FillingPercent);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *BuildScene )( 
            IWMSVisualControl * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_pickedLocation )( 
            IWMSVisualControl * This,
            /* [out] */ BSTR *pickingInventLocation,
            /* [retval][out] */ BSTR *pVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UpdateLocationFillingPercent )( 
            IWMSVisualControl * This,
            /* [in] */ BSTR inventLocationName,
            /* [in] */ BSTR wmsLocationName,
            /* [in] */ FLOAT fillingPercent);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *UpdateScene )( 
            IWMSVisualControl * This);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_minFillPercent )( 
            IWMSVisualControl * This,
            /* [retval][out] */ FLOAT *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_minFillPercent )( 
            IWMSVisualControl * This,
            /* [in] */ FLOAT newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_maxFillPercent )( 
            IWMSVisualControl * This,
            /* [retval][out] */ FLOAT *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_maxFillPercent )( 
            IWMSVisualControl * This,
            /* [in] */ FLOAT newVal);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetLocationStatus )( 
            IWMSVisualControl * This,
            /* [in] */ BSTR inventLocationName,
            /* [in] */ BSTR wmsLocationName,
            /* [in] */ SHORT bShow,
            /* [in] */ ULONG dwStatus);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetErrorDescription )( 
            IWMSVisualControl * This,
            /* [out] */ BSTR *errorDescription);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetSourceLocation )( 
            IWMSVisualControl * This,
            /* [in] */ BSTR InventLocationName,
            /* [in] */ BSTR WMSLocationName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetDestinationLocation )( 
            IWMSVisualControl * This,
            /* [in] */ BSTR InventLocationName,
            /* [in] */ BSTR WMSLocationName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *ClearSourceDestLocation )( 
            IWMSVisualControl * This);
        
        END_INTERFACE
    } IWMSVisualControlVtbl;

    interface IWMSVisualControl
    {
        CONST_VTBL struct IWMSVisualControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IWMSVisualControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IWMSVisualControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IWMSVisualControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IWMSVisualControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IWMSVisualControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IWMSVisualControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IWMSVisualControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IWMSVisualControl_get_HWND(This,pHWND)	\
    ( (This)->lpVtbl -> get_HWND(This,pHWND) ) 

#define IWMSVisualControl_DeleteAllLocations(This)	\
    ( (This)->lpVtbl -> DeleteAllLocations(This) ) 

#define IWMSVisualControl_AddLocation(This,InventLocationName,WMSLocationName,ShiftX,ShiftY,ShiftZ,Rotation,FillingPercent)	\
    ( (This)->lpVtbl -> AddLocation(This,InventLocationName,WMSLocationName,ShiftX,ShiftY,ShiftZ,Rotation,FillingPercent) ) 

#define IWMSVisualControl_BuildScene(This)	\
    ( (This)->lpVtbl -> BuildScene(This) ) 

#define IWMSVisualControl_get_pickedLocation(This,pickingInventLocation,pVal)	\
    ( (This)->lpVtbl -> get_pickedLocation(This,pickingInventLocation,pVal) ) 

#define IWMSVisualControl_UpdateLocationFillingPercent(This,inventLocationName,wmsLocationName,fillingPercent)	\
    ( (This)->lpVtbl -> UpdateLocationFillingPercent(This,inventLocationName,wmsLocationName,fillingPercent) ) 

#define IWMSVisualControl_UpdateScene(This)	\
    ( (This)->lpVtbl -> UpdateScene(This) ) 

#define IWMSVisualControl_get_minFillPercent(This,pVal)	\
    ( (This)->lpVtbl -> get_minFillPercent(This,pVal) ) 

#define IWMSVisualControl_put_minFillPercent(This,newVal)	\
    ( (This)->lpVtbl -> put_minFillPercent(This,newVal) ) 

#define IWMSVisualControl_get_maxFillPercent(This,pVal)	\
    ( (This)->lpVtbl -> get_maxFillPercent(This,pVal) ) 

#define IWMSVisualControl_put_maxFillPercent(This,newVal)	\
    ( (This)->lpVtbl -> put_maxFillPercent(This,newVal) ) 

#define IWMSVisualControl_SetLocationStatus(This,inventLocationName,wmsLocationName,bShow,dwStatus)	\
    ( (This)->lpVtbl -> SetLocationStatus(This,inventLocationName,wmsLocationName,bShow,dwStatus) ) 

#define IWMSVisualControl_GetErrorDescription(This,errorDescription)	\
    ( (This)->lpVtbl -> GetErrorDescription(This,errorDescription) ) 

#define IWMSVisualControl_SetSourceLocation(This,InventLocationName,WMSLocationName)	\
    ( (This)->lpVtbl -> SetSourceLocation(This,InventLocationName,WMSLocationName) ) 

#define IWMSVisualControl_SetDestinationLocation(This,InventLocationName,WMSLocationName)	\
    ( (This)->lpVtbl -> SetDestinationLocation(This,InventLocationName,WMSLocationName) ) 

#define IWMSVisualControl_ClearSourceDestLocation(This)	\
    ( (This)->lpVtbl -> ClearSourceDestLocation(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IWMSVisualControl_INTERFACE_DEFINED__ */



#ifndef __WMSVisualLib_LIBRARY_DEFINED__
#define __WMSVisualLib_LIBRARY_DEFINED__

/* library WMSVisualLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_WMSVisualLib;

#ifndef ___IWMSVisualControlEvents_DISPINTERFACE_DEFINED__
#define ___IWMSVisualControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IWMSVisualControlEvents */
/* [uuid] */ 


EXTERN_C const IID DIID__IWMSVisualControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A518B4C4-253A-4BC4-8E64-F4C409E769BB")
    _IWMSVisualControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IWMSVisualControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IWMSVisualControlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IWMSVisualControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IWMSVisualControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IWMSVisualControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IWMSVisualControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IWMSVisualControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IWMSVisualControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IWMSVisualControlEventsVtbl;

    interface _IWMSVisualControlEvents
    {
        CONST_VTBL struct _IWMSVisualControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IWMSVisualControlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IWMSVisualControlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IWMSVisualControlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IWMSVisualControlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IWMSVisualControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IWMSVisualControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IWMSVisualControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IWMSVisualControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_WMSVisualControl;

#ifdef __cplusplus

class DECLSPEC_UUID("E81E219B-EB73-4A05-AAC8-8D1A77DD21D8")
WMSVisualControl;
#endif
#endif /* __WMSVisualLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


