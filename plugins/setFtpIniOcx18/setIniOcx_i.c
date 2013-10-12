

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Thu May 09 11:10:51 2013
 */
/* Compiler settings for setIniOcx.odl:
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

MIDL_DEFINE_GUID(IID, LIBID_SETINIOCXLib,0x16551F99,0x27ED,0x433D,0x9E,0x36,0x57,0xCF,0x1E,0xD5,0x87,0xAB);


MIDL_DEFINE_GUID(IID, DIID__DSetIniOcx,0x20731CB3,0x91F9,0x48B2,0x87,0x85,0xD9,0xF2,0x92,0x44,0xFE,0xA9);


MIDL_DEFINE_GUID(IID, DIID__DSetIniOcxEvents,0x38AD2A45,0xF642,0x47AA,0xA6,0x48,0xDC,0x5E,0xBC,0xC0,0x91,0x85);


MIDL_DEFINE_GUID(CLSID, CLSID_SetIniOcx,0x7C723A0A,0xEAC5,0x4163,0x8B,0x09,0xAD,0x6E,0x15,0x94,0xF7,0xF5);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



