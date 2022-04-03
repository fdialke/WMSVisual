

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IWMSVisualControl,0x6B24A30F,0x75AF,0x4C2F,0xBC,0xE4,0xD9,0xC4,0x65,0xD5,0x9F,0xCF);


MIDL_DEFINE_GUID(IID, LIBID_WMSVisualLib,0x010B5F2E,0x4C26,0x47D4,0x94,0x72,0x49,0xB1,0xB9,0x67,0xD7,0xE8);


MIDL_DEFINE_GUID(IID, DIID__IWMSVisualControlEvents,0xA518B4C4,0x253A,0x4BC4,0x8E,0x64,0xF4,0xC4,0x09,0xE7,0x69,0xBB);


MIDL_DEFINE_GUID(CLSID, CLSID_WMSVisualControl,0xE81E219B,0xEB73,0x4A05,0xAA,0xC8,0x8D,0x1A,0x77,0xDD,0x21,0xD8);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



