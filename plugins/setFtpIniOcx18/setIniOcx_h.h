

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __setIniOcx_h_h__
#define __setIniOcx_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DSetIniOcx_FWD_DEFINED__
#define ___DSetIniOcx_FWD_DEFINED__
typedef interface _DSetIniOcx _DSetIniOcx;
#endif 	/* ___DSetIniOcx_FWD_DEFINED__ */


#ifndef ___DSetIniOcxEvents_FWD_DEFINED__
#define ___DSetIniOcxEvents_FWD_DEFINED__
typedef interface _DSetIniOcxEvents _DSetIniOcxEvents;
#endif 	/* ___DSetIniOcxEvents_FWD_DEFINED__ */


#ifndef __SetIniOcx_FWD_DEFINED__
#define __SetIniOcx_FWD_DEFINED__

#ifdef __cplusplus
typedef class SetIniOcx SetIniOcx;
#else
typedef struct SetIniOcx SetIniOcx;
#endif /* __cplusplus */

#endif 	/* __SetIniOcx_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __SETINIOCXLib_LIBRARY_DEFINED__
#define __SETINIOCXLib_LIBRARY_DEFINED__

/* library SETINIOCXLib */
/* [control][helpstring][helpfile][version][uuid] */ 


DEFINE_GUID(LIBID_SETINIOCXLib,0x16551F99,0x27ED,0x433D,0x9E,0x36,0x57,0xCF,0x1E,0xD5,0x87,0xAB);

#ifndef ___DSetIniOcx_DISPINTERFACE_DEFINED__
#define ___DSetIniOcx_DISPINTERFACE_DEFINED__

/* dispinterface _DSetIniOcx */
/* [hidden][helpstring][uuid] */ 


DEFINE_GUID(DIID__DSetIniOcx,0x20731CB3,0x91F9,0x48B2,0x87,0x85,0xD9,0xF2,0x92,0x44,0xFE,0xA9);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("20731CB3-91F9-48B2-8785-D9F29244FEA9")
    _DSetIniOcx : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSetIniOcxVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSetIniOcx * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSetIniOcx * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSetIniOcx * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSetIniOcx * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSetIniOcx * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSetIniOcx * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSetIniOcx * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DSetIniOcxVtbl;

    interface _DSetIniOcx
    {
        CONST_VTBL struct _DSetIniOcxVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSetIniOcx_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSetIniOcx_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSetIniOcx_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSetIniOcx_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSetIniOcx_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSetIniOcx_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSetIniOcx_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSetIniOcx_DISPINTERFACE_DEFINED__ */


#ifndef ___DSetIniOcxEvents_DISPINTERFACE_DEFINED__
#define ___DSetIniOcxEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DSetIniOcxEvents */
/* [helpstring][uuid] */ 


DEFINE_GUID(DIID__DSetIniOcxEvents,0x38AD2A45,0xF642,0x47AA,0xA6,0x48,0xDC,0x5E,0xBC,0xC0,0x91,0x85);

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("38AD2A45-F642-47AA-A648-DC5EBCC09185")
    _DSetIniOcxEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DSetIniOcxEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DSetIniOcxEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DSetIniOcxEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DSetIniOcxEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DSetIniOcxEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DSetIniOcxEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DSetIniOcxEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DSetIniOcxEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DSetIniOcxEventsVtbl;

    interface _DSetIniOcxEvents
    {
        CONST_VTBL struct _DSetIniOcxEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DSetIniOcxEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DSetIniOcxEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DSetIniOcxEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DSetIniOcxEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DSetIniOcxEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DSetIniOcxEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DSetIniOcxEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DSetIniOcxEvents_DISPINTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_SetIniOcx,0x7C723A0A,0xEAC5,0x4163,0x8B,0x09,0xAD,0x6E,0x15,0x94,0xF7,0xF5);

#ifdef __cplusplus

class DECLSPEC_UUID("7C723A0A-EAC5-4163-8B09-AD6E1594F7F5")
SetIniOcx;
#endif
#endif /* __SETINIOCXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


