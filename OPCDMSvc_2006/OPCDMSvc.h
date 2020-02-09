

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Jun 30 11:16:16 2006
 */
/* Compiler settings for .\OPCDMSvc.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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

#ifndef __OPCDMSvc_h__
#define __OPCDMSvc_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEnumOPCDMTagDef_FWD_DEFINED__
#define __IEnumOPCDMTagDef_FWD_DEFINED__
typedef interface IEnumOPCDMTagDef IEnumOPCDMTagDef;
#endif 	/* __IEnumOPCDMTagDef_FWD_DEFINED__ */


#ifndef __IChannelDataCallback_FWD_DEFINED__
#define __IChannelDataCallback_FWD_DEFINED__
typedef interface IChannelDataCallback IChannelDataCallback;
#endif 	/* __IChannelDataCallback_FWD_DEFINED__ */


#ifndef __IMyOPCSrv_FWD_DEFINED__
#define __IMyOPCSrv_FWD_DEFINED__
typedef interface IMyOPCSrv IMyOPCSrv;
#endif 	/* __IMyOPCSrv_FWD_DEFINED__ */


#ifndef __IChannelTagDef_FWD_DEFINED__
#define __IChannelTagDef_FWD_DEFINED__
typedef interface IChannelTagDef IChannelTagDef;
#endif 	/* __IChannelTagDef_FWD_DEFINED__ */


#ifndef __ICChannelObj_FWD_DEFINED__
#define __ICChannelObj_FWD_DEFINED__
typedef interface ICChannelObj ICChannelObj;
#endif 	/* __ICChannelObj_FWD_DEFINED__ */


#ifndef __IMyTestConf_FWD_DEFINED__
#define __IMyTestConf_FWD_DEFINED__
typedef interface IMyTestConf IMyTestConf;
#endif 	/* __IMyTestConf_FWD_DEFINED__ */


#ifndef __MyOPCSrv_FWD_DEFINED__
#define __MyOPCSrv_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyOPCSrv MyOPCSrv;
#else
typedef struct MyOPCSrv MyOPCSrv;
#endif /* __cplusplus */

#endif 	/* __MyOPCSrv_FWD_DEFINED__ */


#ifndef __IMyTestConfCallback_FWD_DEFINED__
#define __IMyTestConfCallback_FWD_DEFINED__
typedef interface IMyTestConfCallback IMyTestConfCallback;
#endif 	/* __IMyTestConfCallback_FWD_DEFINED__ */


#ifndef __IMyGroup_FWD_DEFINED__
#define __IMyGroup_FWD_DEFINED__
typedef interface IMyGroup IMyGroup;
#endif 	/* __IMyGroup_FWD_DEFINED__ */


#ifndef __MyTestConf_FWD_DEFINED__
#define __MyTestConf_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyTestConf MyTestConf;
#else
typedef struct MyTestConf MyTestConf;
#endif /* __cplusplus */

#endif 	/* __MyTestConf_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "spacebrowse.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_OPCDMSvc_0000 */
/* [local] */ 

typedef /* [public][public] */ struct __MIDL___MIDL_itf_OPCDMSvc_0000_0001
    {
    BSTR ChannelName;
    BSTR PluginProgID;
    BSTR PluginCnfg;
    BSTR ChannelCnfg;
    WORD ChannelMode;
    DWORD UpdateRate;
    BSTR ChannelDescription;
    WORD DeviceUpdateMode;
    } 	ChannelDef;

typedef /* [public][public][public][public] */ struct __MIDL___MIDL_itf_OPCDMSvc_0000_0002
    {
    VARTYPE vtTagType;
    DWORD dwUpdateRateMS;
    BOOL bNotifyUpdate;
    BOOL bActive;
    BSTR bstrTagDescription;
    BSTR bstrTagName;
    BSTR bstrRealName;
    DWORD dwAccessRight;
    } 	TagDefStruct;



extern RPC_IF_HANDLE __MIDL_itf_OPCDMSvc_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_OPCDMSvc_0000_v0_0_s_ifspec;

#ifndef __IEnumOPCDMTagDef_INTERFACE_DEFINED__
#define __IEnumOPCDMTagDef_INTERFACE_DEFINED__

/* interface IEnumOPCDMTagDef */
/* [unique][uuid][object] */ 


EXTERN_C const IID IID_IEnumOPCDMTagDef;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5A48C1BF-08A6-4807-AED1-B9AA8783D7E4")
    IEnumOPCDMTagDef : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Next( 
            /* [in] */ ULONG celt,
            /* [size_is][size_is][out] */ TagDefStruct **ppItemArray,
            /* [out] */ ULONG *pceltFetched) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Skip( 
            /* [in] */ ULONG celt) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Clone( 
            /* [out] */ IEnumOPCDMTagDef **ppEnumTagDef) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IEnumOPCDMTagDefVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumOPCDMTagDef * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumOPCDMTagDef * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumOPCDMTagDef * This);
        
        HRESULT ( STDMETHODCALLTYPE *Next )( 
            IEnumOPCDMTagDef * This,
            /* [in] */ ULONG celt,
            /* [size_is][size_is][out] */ TagDefStruct **ppItemArray,
            /* [out] */ ULONG *pceltFetched);
        
        HRESULT ( STDMETHODCALLTYPE *Skip )( 
            IEnumOPCDMTagDef * This,
            /* [in] */ ULONG celt);
        
        HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IEnumOPCDMTagDef * This);
        
        HRESULT ( STDMETHODCALLTYPE *Clone )( 
            IEnumOPCDMTagDef * This,
            /* [out] */ IEnumOPCDMTagDef **ppEnumTagDef);
        
        END_INTERFACE
    } IEnumOPCDMTagDefVtbl;

    interface IEnumOPCDMTagDef
    {
        CONST_VTBL struct IEnumOPCDMTagDefVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumOPCDMTagDef_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IEnumOPCDMTagDef_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IEnumOPCDMTagDef_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IEnumOPCDMTagDef_Next(This,celt,ppItemArray,pceltFetched)	\
    (This)->lpVtbl -> Next(This,celt,ppItemArray,pceltFetched)

#define IEnumOPCDMTagDef_Skip(This,celt)	\
    (This)->lpVtbl -> Skip(This,celt)

#define IEnumOPCDMTagDef_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IEnumOPCDMTagDef_Clone(This,ppEnumTagDef)	\
    (This)->lpVtbl -> Clone(This,ppEnumTagDef)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IEnumOPCDMTagDef_Next_Proxy( 
    IEnumOPCDMTagDef * This,
    /* [in] */ ULONG celt,
    /* [size_is][size_is][out] */ TagDefStruct **ppItemArray,
    /* [out] */ ULONG *pceltFetched);


void __RPC_STUB IEnumOPCDMTagDef_Next_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumOPCDMTagDef_Skip_Proxy( 
    IEnumOPCDMTagDef * This,
    /* [in] */ ULONG celt);


void __RPC_STUB IEnumOPCDMTagDef_Skip_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumOPCDMTagDef_Reset_Proxy( 
    IEnumOPCDMTagDef * This);


void __RPC_STUB IEnumOPCDMTagDef_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IEnumOPCDMTagDef_Clone_Proxy( 
    IEnumOPCDMTagDef * This,
    /* [out] */ IEnumOPCDMTagDef **ppEnumTagDef);


void __RPC_STUB IEnumOPCDMTagDef_Clone_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IEnumOPCDMTagDef_INTERFACE_DEFINED__ */


#ifndef __IChannelDataCallback_INTERFACE_DEFINED__
#define __IChannelDataCallback_INTERFACE_DEFINED__

/* interface IChannelDataCallback */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID_IChannelDataCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B5311029-081F-40F0-8BC2-C3F4AAE7F34D")
    IChannelDataCallback : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE OnChannelDataChange( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeletedTags( 
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCHANDLE *hSrvHandles) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IChannelDataCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IChannelDataCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IChannelDataCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IChannelDataCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *OnChannelDataChange )( 
            IChannelDataCallback * This);
        
        HRESULT ( STDMETHODCALLTYPE *DeletedTags )( 
            IChannelDataCallback * This,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCHANDLE *hSrvHandles);
        
        END_INTERFACE
    } IChannelDataCallbackVtbl;

    interface IChannelDataCallback
    {
        CONST_VTBL struct IChannelDataCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChannelDataCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IChannelDataCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IChannelDataCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IChannelDataCallback_OnChannelDataChange(This)	\
    (This)->lpVtbl -> OnChannelDataChange(This)

#define IChannelDataCallback_DeletedTags(This,dwCount,hSrvHandles)	\
    (This)->lpVtbl -> DeletedTags(This,dwCount,hSrvHandles)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IChannelDataCallback_OnChannelDataChange_Proxy( 
    IChannelDataCallback * This);


void __RPC_STUB IChannelDataCallback_OnChannelDataChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IChannelDataCallback_DeletedTags_Proxy( 
    IChannelDataCallback * This,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ OPCHANDLE *hSrvHandles);


void __RPC_STUB IChannelDataCallback_DeletedTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IChannelDataCallback_INTERFACE_DEFINED__ */


#ifndef __IMyOPCSrv_INTERFACE_DEFINED__
#define __IMyOPCSrv_INTERFACE_DEFINED__

/* interface IMyOPCSrv */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMyOPCSrv;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4D9B1548-9D04-4657-9C49-2150B207D311")
    IMyOPCSrv : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IMyOPCSrvVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyOPCSrv * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyOPCSrv * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyOPCSrv * This);
        
        END_INTERFACE
    } IMyOPCSrvVtbl;

    interface IMyOPCSrv
    {
        CONST_VTBL struct IMyOPCSrvVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyOPCSrv_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyOPCSrv_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyOPCSrv_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyOPCSrv_INTERFACE_DEFINED__ */


#ifndef __IChannelTagDef_INTERFACE_DEFINED__
#define __IChannelTagDef_INTERFACE_DEFINED__

/* interface IChannelTagDef */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IChannelTagDef;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("2A0C652F-4833-43c9-B5B2-F0C7E32B6615")
    IChannelTagDef : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateTags( 
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ TagDefStruct *pTagDefs,
            /* [size_is][size_is][out] */ HRESULT **ppErrors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ChangeTagsDef( 
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCHANDLE *pHandles,
            /* [size_is][in] */ TagDefStruct *pNewDefs,
            /* [size_is][size_is][out] */ HRESULT **ppErrors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteTags( 
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ DWORD *dwHandles,
            /* [size_is][size_is][out] */ HRESULT **ppErrors) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IChannelTagDefVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IChannelTagDef * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IChannelTagDef * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IChannelTagDef * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateTags )( 
            IChannelTagDef * This,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ TagDefStruct *pTagDefs,
            /* [size_is][size_is][out] */ HRESULT **ppErrors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ChangeTagsDef )( 
            IChannelTagDef * This,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCHANDLE *pHandles,
            /* [size_is][in] */ TagDefStruct *pNewDefs,
            /* [size_is][size_is][out] */ HRESULT **ppErrors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteTags )( 
            IChannelTagDef * This,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ DWORD *dwHandles,
            /* [size_is][size_is][out] */ HRESULT **ppErrors);
        
        END_INTERFACE
    } IChannelTagDefVtbl;

    interface IChannelTagDef
    {
        CONST_VTBL struct IChannelTagDefVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IChannelTagDef_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IChannelTagDef_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IChannelTagDef_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IChannelTagDef_CreateTags(This,dwCount,pTagDefs,ppErrors)	\
    (This)->lpVtbl -> CreateTags(This,dwCount,pTagDefs,ppErrors)

#define IChannelTagDef_ChangeTagsDef(This,dwCount,pHandles,pNewDefs,ppErrors)	\
    (This)->lpVtbl -> ChangeTagsDef(This,dwCount,pHandles,pNewDefs,ppErrors)

#define IChannelTagDef_DeleteTags(This,dwCount,dwHandles,ppErrors)	\
    (This)->lpVtbl -> DeleteTags(This,dwCount,dwHandles,ppErrors)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IChannelTagDef_CreateTags_Proxy( 
    IChannelTagDef * This,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ TagDefStruct *pTagDefs,
    /* [size_is][size_is][out] */ HRESULT **ppErrors);


void __RPC_STUB IChannelTagDef_CreateTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IChannelTagDef_ChangeTagsDef_Proxy( 
    IChannelTagDef * This,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ OPCHANDLE *pHandles,
    /* [size_is][in] */ TagDefStruct *pNewDefs,
    /* [size_is][size_is][out] */ HRESULT **ppErrors);


void __RPC_STUB IChannelTagDef_ChangeTagsDef_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IChannelTagDef_DeleteTags_Proxy( 
    IChannelTagDef * This,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ DWORD *dwHandles,
    /* [size_is][size_is][out] */ HRESULT **ppErrors);


void __RPC_STUB IChannelTagDef_DeleteTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IChannelTagDef_INTERFACE_DEFINED__ */


#ifndef __ICChannelObj_INTERFACE_DEFINED__
#define __ICChannelObj_INTERFACE_DEFINED__

/* interface ICChannelObj */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ICChannelObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E92E6541-F496-4DA9-B819-1F0BD50774C3")
    ICChannelObj : public IUnknown
    {
    public:
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ClockRate( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ClockRate( 
            /* [in] */ DWORD newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_CreationTime( 
            /* [retval][out] */ FILETIME *pVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBrowser( 
            /* [out] */ IUnknown **pChannelBrowse) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReadTags( 
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCHANDLE *phServer,
            /* [size_is][size_is][out] */ OPCITEMSTATE **ppItemValues,
            /* [size_is][size_is][out] */ HRESULT **ppErrors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE WriteTags( 
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCHANDLE *phServer,
            /* [size_is][in] */ VARIANT *pItemValues,
            /* [size_is][size_is][out] */ HRESULT **ppErrors) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ChannelName( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ChannelID( 
            /* [retval][out] */ DWORD *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_Description( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_Description( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ConfgStr( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PluginCnfgString( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_PluginProgID( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ICChannelObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICChannelObj * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICChannelObj * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICChannelObj * This);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ClockRate )( 
            ICChannelObj * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ClockRate )( 
            ICChannelObj * This,
            /* [in] */ DWORD newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_CreationTime )( 
            ICChannelObj * This,
            /* [retval][out] */ FILETIME *pVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBrowser )( 
            ICChannelObj * This,
            /* [out] */ IUnknown **pChannelBrowse);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReadTags )( 
            ICChannelObj * This,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCHANDLE *phServer,
            /* [size_is][size_is][out] */ OPCITEMSTATE **ppItemValues,
            /* [size_is][size_is][out] */ HRESULT **ppErrors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *WriteTags )( 
            ICChannelObj * This,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCHANDLE *phServer,
            /* [size_is][in] */ VARIANT *pItemValues,
            /* [size_is][size_is][out] */ HRESULT **ppErrors);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChannelName )( 
            ICChannelObj * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ChannelID )( 
            ICChannelObj * This,
            /* [retval][out] */ DWORD *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Description )( 
            ICChannelObj * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_Description )( 
            ICChannelObj * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConfgStr )( 
            ICChannelObj * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PluginCnfgString )( 
            ICChannelObj * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PluginProgID )( 
            ICChannelObj * This,
            /* [retval][out] */ BSTR *pVal);
        
        END_INTERFACE
    } ICChannelObjVtbl;

    interface ICChannelObj
    {
        CONST_VTBL struct ICChannelObjVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICChannelObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ICChannelObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ICChannelObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ICChannelObj_get_ClockRate(This,pVal)	\
    (This)->lpVtbl -> get_ClockRate(This,pVal)

#define ICChannelObj_put_ClockRate(This,newVal)	\
    (This)->lpVtbl -> put_ClockRate(This,newVal)

#define ICChannelObj_get_CreationTime(This,pVal)	\
    (This)->lpVtbl -> get_CreationTime(This,pVal)

#define ICChannelObj_GetBrowser(This,pChannelBrowse)	\
    (This)->lpVtbl -> GetBrowser(This,pChannelBrowse)

#define ICChannelObj_ReadTags(This,dwCount,phServer,ppItemValues,ppErrors)	\
    (This)->lpVtbl -> ReadTags(This,dwCount,phServer,ppItemValues,ppErrors)

#define ICChannelObj_WriteTags(This,dwCount,phServer,pItemValues,ppErrors)	\
    (This)->lpVtbl -> WriteTags(This,dwCount,phServer,pItemValues,ppErrors)

#define ICChannelObj_get_ChannelName(This,pVal)	\
    (This)->lpVtbl -> get_ChannelName(This,pVal)

#define ICChannelObj_get_ChannelID(This,pVal)	\
    (This)->lpVtbl -> get_ChannelID(This,pVal)

#define ICChannelObj_get_Description(This,pVal)	\
    (This)->lpVtbl -> get_Description(This,pVal)

#define ICChannelObj_put_Description(This,newVal)	\
    (This)->lpVtbl -> put_Description(This,newVal)

#define ICChannelObj_get_ConfgStr(This,pVal)	\
    (This)->lpVtbl -> get_ConfgStr(This,pVal)

#define ICChannelObj_get_PluginCnfgString(This,pVal)	\
    (This)->lpVtbl -> get_PluginCnfgString(This,pVal)

#define ICChannelObj_get_PluginProgID(This,pVal)	\
    (This)->lpVtbl -> get_PluginProgID(This,pVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ICChannelObj_get_ClockRate_Proxy( 
    ICChannelObj * This,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB ICChannelObj_get_ClockRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ICChannelObj_put_ClockRate_Proxy( 
    ICChannelObj * This,
    /* [in] */ DWORD newVal);


void __RPC_STUB ICChannelObj_put_ClockRate_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ICChannelObj_get_CreationTime_Proxy( 
    ICChannelObj * This,
    /* [retval][out] */ FILETIME *pVal);


void __RPC_STUB ICChannelObj_get_CreationTime_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICChannelObj_GetBrowser_Proxy( 
    ICChannelObj * This,
    /* [out] */ IUnknown **pChannelBrowse);


void __RPC_STUB ICChannelObj_GetBrowser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICChannelObj_ReadTags_Proxy( 
    ICChannelObj * This,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ OPCHANDLE *phServer,
    /* [size_is][size_is][out] */ OPCITEMSTATE **ppItemValues,
    /* [size_is][size_is][out] */ HRESULT **ppErrors);


void __RPC_STUB ICChannelObj_ReadTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ICChannelObj_WriteTags_Proxy( 
    ICChannelObj * This,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ OPCHANDLE *phServer,
    /* [size_is][in] */ VARIANT *pItemValues,
    /* [size_is][size_is][out] */ HRESULT **ppErrors);


void __RPC_STUB ICChannelObj_WriteTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ICChannelObj_get_ChannelName_Proxy( 
    ICChannelObj * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ICChannelObj_get_ChannelName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ICChannelObj_get_ChannelID_Proxy( 
    ICChannelObj * This,
    /* [retval][out] */ DWORD *pVal);


void __RPC_STUB ICChannelObj_get_ChannelID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ICChannelObj_get_Description_Proxy( 
    ICChannelObj * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ICChannelObj_get_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE ICChannelObj_put_Description_Proxy( 
    ICChannelObj * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB ICChannelObj_put_Description_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ICChannelObj_get_ConfgStr_Proxy( 
    ICChannelObj * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ICChannelObj_get_ConfgStr_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ICChannelObj_get_PluginCnfgString_Proxy( 
    ICChannelObj * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ICChannelObj_get_PluginCnfgString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE ICChannelObj_get_PluginProgID_Proxy( 
    ICChannelObj * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB ICChannelObj_get_PluginProgID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ICChannelObj_INTERFACE_DEFINED__ */


#ifndef __IMyTestConf_INTERFACE_DEFINED__
#define __IMyTestConf_INTERFACE_DEFINED__

/* interface IMyTestConf */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMyTestConf;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("78F8CD45-30A5-4000-B57C-6EC9E2C90380")
    IMyTestConf : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CreateChannel( 
            /* [in] */ ChannelDef *pChannelDef,
            /* [out][in] */ ICChannelObj **pICChannelObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteChannel( 
            /* [in] */ DWORD dwChannelID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ChangeChannelMode( 
            /* [in] */ DWORD dwChannelID,
            /* [in] */ WORD wNewMode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetChannelByName( 
            /* [in] */ BSTR ChannelName,
            /* [out][in] */ ICChannelObj **pICChannelObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetChannelByID( 
            /* [in] */ DWORD ChannelID,
            /* [out][in] */ ICChannelObj **pICChannelObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumChannels( 
            /* [out][in] */ IEnumUnknown **ppEnumChannel) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetStatus( 
            /* [out] */ DWORD *pStatus) = 0;
        
        virtual /* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE get_ConfigXML( 
            /* [retval][out] */ BSTR *pVal) = 0;
        
        virtual /* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE put_ConfigXML( 
            /* [in] */ BSTR newVal) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnumPlugins( 
            /* [out][in] */ IEnumString **pEnumString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ChangeState( 
            /* [in] */ OPCSERVERSTATE newState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveCurrentConfigToXML( 
            /* [in] */ BSTR secondCopyOfXML) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyTestConfVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyTestConf * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyTestConf * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyTestConf * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CreateChannel )( 
            IMyTestConf * This,
            /* [in] */ ChannelDef *pChannelDef,
            /* [out][in] */ ICChannelObj **pICChannelObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteChannel )( 
            IMyTestConf * This,
            /* [in] */ DWORD dwChannelID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ChangeChannelMode )( 
            IMyTestConf * This,
            /* [in] */ DWORD dwChannelID,
            /* [in] */ WORD wNewMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetChannelByName )( 
            IMyTestConf * This,
            /* [in] */ BSTR ChannelName,
            /* [out][in] */ ICChannelObj **pICChannelObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetChannelByID )( 
            IMyTestConf * This,
            /* [in] */ DWORD ChannelID,
            /* [out][in] */ ICChannelObj **pICChannelObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumChannels )( 
            IMyTestConf * This,
            /* [out][in] */ IEnumUnknown **ppEnumChannel);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetStatus )( 
            IMyTestConf * This,
            /* [out] */ DWORD *pStatus);
        
        /* [helpstring][propget] */ HRESULT ( STDMETHODCALLTYPE *get_ConfigXML )( 
            IMyTestConf * This,
            /* [retval][out] */ BSTR *pVal);
        
        /* [helpstring][propput] */ HRESULT ( STDMETHODCALLTYPE *put_ConfigXML )( 
            IMyTestConf * This,
            /* [in] */ BSTR newVal);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnumPlugins )( 
            IMyTestConf * This,
            /* [out][in] */ IEnumString **pEnumString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ChangeState )( 
            IMyTestConf * This,
            /* [in] */ OPCSERVERSTATE newState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SaveCurrentConfigToXML )( 
            IMyTestConf * This,
            /* [in] */ BSTR secondCopyOfXML);
        
        END_INTERFACE
    } IMyTestConfVtbl;

    interface IMyTestConf
    {
        CONST_VTBL struct IMyTestConfVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyTestConf_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyTestConf_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyTestConf_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyTestConf_CreateChannel(This,pChannelDef,pICChannelObj)	\
    (This)->lpVtbl -> CreateChannel(This,pChannelDef,pICChannelObj)

#define IMyTestConf_DeleteChannel(This,dwChannelID)	\
    (This)->lpVtbl -> DeleteChannel(This,dwChannelID)

#define IMyTestConf_ChangeChannelMode(This,dwChannelID,wNewMode)	\
    (This)->lpVtbl -> ChangeChannelMode(This,dwChannelID,wNewMode)

#define IMyTestConf_GetChannelByName(This,ChannelName,pICChannelObj)	\
    (This)->lpVtbl -> GetChannelByName(This,ChannelName,pICChannelObj)

#define IMyTestConf_GetChannelByID(This,ChannelID,pICChannelObj)	\
    (This)->lpVtbl -> GetChannelByID(This,ChannelID,pICChannelObj)

#define IMyTestConf_EnumChannels(This,ppEnumChannel)	\
    (This)->lpVtbl -> EnumChannels(This,ppEnumChannel)

#define IMyTestConf_GetStatus(This,pStatus)	\
    (This)->lpVtbl -> GetStatus(This,pStatus)

#define IMyTestConf_get_ConfigXML(This,pVal)	\
    (This)->lpVtbl -> get_ConfigXML(This,pVal)

#define IMyTestConf_put_ConfigXML(This,newVal)	\
    (This)->lpVtbl -> put_ConfigXML(This,newVal)

#define IMyTestConf_EnumPlugins(This,pEnumString)	\
    (This)->lpVtbl -> EnumPlugins(This,pEnumString)

#define IMyTestConf_ChangeState(This,newState)	\
    (This)->lpVtbl -> ChangeState(This,newState)

#define IMyTestConf_SaveCurrentConfigToXML(This,secondCopyOfXML)	\
    (This)->lpVtbl -> SaveCurrentConfigToXML(This,secondCopyOfXML)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyTestConf_CreateChannel_Proxy( 
    IMyTestConf * This,
    /* [in] */ ChannelDef *pChannelDef,
    /* [out][in] */ ICChannelObj **pICChannelObj);


void __RPC_STUB IMyTestConf_CreateChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyTestConf_DeleteChannel_Proxy( 
    IMyTestConf * This,
    /* [in] */ DWORD dwChannelID);


void __RPC_STUB IMyTestConf_DeleteChannel_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyTestConf_ChangeChannelMode_Proxy( 
    IMyTestConf * This,
    /* [in] */ DWORD dwChannelID,
    /* [in] */ WORD wNewMode);


void __RPC_STUB IMyTestConf_ChangeChannelMode_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyTestConf_GetChannelByName_Proxy( 
    IMyTestConf * This,
    /* [in] */ BSTR ChannelName,
    /* [out][in] */ ICChannelObj **pICChannelObj);


void __RPC_STUB IMyTestConf_GetChannelByName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyTestConf_GetChannelByID_Proxy( 
    IMyTestConf * This,
    /* [in] */ DWORD ChannelID,
    /* [out][in] */ ICChannelObj **pICChannelObj);


void __RPC_STUB IMyTestConf_GetChannelByID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyTestConf_EnumChannels_Proxy( 
    IMyTestConf * This,
    /* [out][in] */ IEnumUnknown **ppEnumChannel);


void __RPC_STUB IMyTestConf_EnumChannels_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyTestConf_GetStatus_Proxy( 
    IMyTestConf * This,
    /* [out] */ DWORD *pStatus);


void __RPC_STUB IMyTestConf_GetStatus_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propget] */ HRESULT STDMETHODCALLTYPE IMyTestConf_get_ConfigXML_Proxy( 
    IMyTestConf * This,
    /* [retval][out] */ BSTR *pVal);


void __RPC_STUB IMyTestConf_get_ConfigXML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][propput] */ HRESULT STDMETHODCALLTYPE IMyTestConf_put_ConfigXML_Proxy( 
    IMyTestConf * This,
    /* [in] */ BSTR newVal);


void __RPC_STUB IMyTestConf_put_ConfigXML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyTestConf_EnumPlugins_Proxy( 
    IMyTestConf * This,
    /* [out][in] */ IEnumString **pEnumString);


void __RPC_STUB IMyTestConf_EnumPlugins_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyTestConf_ChangeState_Proxy( 
    IMyTestConf * This,
    /* [in] */ OPCSERVERSTATE newState);


void __RPC_STUB IMyTestConf_ChangeState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyTestConf_SaveCurrentConfigToXML_Proxy( 
    IMyTestConf * This,
    /* [in] */ BSTR secondCopyOfXML);


void __RPC_STUB IMyTestConf_SaveCurrentConfigToXML_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyTestConf_INTERFACE_DEFINED__ */



#ifndef __OPCDMSVCLib_LIBRARY_DEFINED__
#define __OPCDMSVCLib_LIBRARY_DEFINED__

/* library OPCDMSVCLib */
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_OPCDMSVCLib;

EXTERN_C const CLSID CLSID_MyOPCSrv;

#ifdef __cplusplus

class DECLSPEC_UUID("3254F88B-341A-4252-AA1D-E2FFD6CE069C")
MyOPCSrv;
#endif

#ifndef __IMyTestConfCallback_INTERFACE_DEFINED__
#define __IMyTestConfCallback_INTERFACE_DEFINED__

/* interface IMyTestConfCallback */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID_IMyTestConfCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B915BFA8-0CEE-43CC-9068-E6E355C6B412")
    IMyTestConfCallback : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDataChange( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMyTestConfCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyTestConfCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyTestConfCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyTestConfCallback * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDataChange )( 
            IMyTestConfCallback * This);
        
        END_INTERFACE
    } IMyTestConfCallbackVtbl;

    interface IMyTestConfCallback
    {
        CONST_VTBL struct IMyTestConfCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyTestConfCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyTestConfCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyTestConfCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMyTestConfCallback_OnDataChange(This)	\
    (This)->lpVtbl -> OnDataChange(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IMyTestConfCallback_OnDataChange_Proxy( 
    IMyTestConfCallback * This);


void __RPC_STUB IMyTestConfCallback_OnDataChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMyTestConfCallback_INTERFACE_DEFINED__ */


#ifndef __IMyGroup_INTERFACE_DEFINED__
#define __IMyGroup_INTERFACE_DEFINED__

/* interface IMyGroup */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IMyGroup;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("13764883-5E6B-4173-B447-A4322E996B1B")
    IMyGroup : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct IMyGroupVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMyGroup * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMyGroup * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMyGroup * This);
        
        END_INTERFACE
    } IMyGroupVtbl;

    interface IMyGroup
    {
        CONST_VTBL struct IMyGroupVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMyGroup_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMyGroup_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMyGroup_Release(This)	\
    (This)->lpVtbl -> Release(This)


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMyGroup_INTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MyTestConf;

#ifdef __cplusplus

class DECLSPEC_UUID("0FD6A06B-4EBB-49BD-903D-4E125B14ED3E")
MyTestConf;
#endif
#endif /* __OPCDMSVCLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


