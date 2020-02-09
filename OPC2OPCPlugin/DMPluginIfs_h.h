
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Tue Jun 24 23:54:08 2003
 */
/* Compiler settings for \prj\vc++\OPC\OPCImpl\ForPlugin\DMPluginIfs.idl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __DMPluginIfs_h_h__
#define __DMPluginIfs_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPluginConfig_FWD_DEFINED__
#define __IPluginConfig_FWD_DEFINED__
typedef interface IPluginConfig IPluginConfig;
#endif 	/* __IPluginConfig_FWD_DEFINED__ */


#ifndef __IPluginData_FWD_DEFINED__
#define __IPluginData_FWD_DEFINED__
typedef interface IPluginData IPluginData;
#endif 	/* __IPluginData_FWD_DEFINED__ */


#ifndef __IPluginDataCallback_FWD_DEFINED__
#define __IPluginDataCallback_FWD_DEFINED__
typedef interface IPluginDataCallback IPluginDataCallback;
#endif 	/* __IPluginDataCallback_FWD_DEFINED__ */


/* header files for imported files */
#include "spacebrowse.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

/* interface __MIDL_itf_DMPluginIfs_0000 */
/* [local] */ 

typedef /* [public][public][public][public][public] */ struct __MIDL___MIDL_itf_DMPluginIfs_0000_0001
    {
    DWORD hClient;
    BSTR ItemName;
    } 	ITEMID;



extern RPC_IF_HANDLE __MIDL_itf_DMPluginIfs_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_DMPluginIfs_0000_v0_0_s_ifspec;

#ifndef __IPluginConfig_INTERFACE_DEFINED__
#define __IPluginConfig_INTERFACE_DEFINED__

/* interface IPluginConfig */
/* [helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPluginConfig;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EE33DD30-74D9-11d5-9CB4-004005A3070A")
    IPluginConfig : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddNotifyTags( 
            /* [size_is][in] */ ITEMID *ClientTagID,
            /* [in] */ DWORD dwCount,
            /* [in] */ DWORD dwUpdateRate,
            /* [size_is][size_is][out] */ HRESULT **pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DelNotifyTags( 
            /* [size_is][in] */ ITEMID *ClientTagID,
            /* [in] */ DWORD dwCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Configure( 
            /* [in] */ BSTR CnfgString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetExampleCnfg( 
            /* [out][in] */ BSTR *bstrExampleCnfg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBrowser( 
            /* [out] */ IUnknown **pBrowUnk) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFullLogFileName( 
            /* [in] */ BSTR LogFileName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPluginConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPluginConfig * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPluginConfig * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPluginConfig * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddNotifyTags )( 
            IPluginConfig * This,
            /* [size_is][in] */ ITEMID *ClientTagID,
            /* [in] */ DWORD dwCount,
            /* [in] */ DWORD dwUpdateRate,
            /* [size_is][size_is][out] */ HRESULT **pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DelNotifyTags )( 
            IPluginConfig * This,
            /* [size_is][in] */ ITEMID *ClientTagID,
            /* [in] */ DWORD dwCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Configure )( 
            IPluginConfig * This,
            /* [in] */ BSTR CnfgString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Reset )( 
            IPluginConfig * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetExampleCnfg )( 
            IPluginConfig * This,
            /* [out][in] */ BSTR *bstrExampleCnfg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetBrowser )( 
            IPluginConfig * This,
            /* [out] */ IUnknown **pBrowUnk);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetFullLogFileName )( 
            IPluginConfig * This,
            /* [in] */ BSTR LogFileName);
        
        END_INTERFACE
    } IPluginConfigVtbl;

    interface IPluginConfig
    {
        CONST_VTBL struct IPluginConfigVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPluginConfig_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPluginConfig_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPluginConfig_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPluginConfig_AddNotifyTags(This,ClientTagID,dwCount,dwUpdateRate,pError)	\
    (This)->lpVtbl -> AddNotifyTags(This,ClientTagID,dwCount,dwUpdateRate,pError)

#define IPluginConfig_DelNotifyTags(This,ClientTagID,dwCount)	\
    (This)->lpVtbl -> DelNotifyTags(This,ClientTagID,dwCount)

#define IPluginConfig_Configure(This,CnfgString)	\
    (This)->lpVtbl -> Configure(This,CnfgString)

#define IPluginConfig_Reset(This)	\
    (This)->lpVtbl -> Reset(This)

#define IPluginConfig_GetExampleCnfg(This,bstrExampleCnfg)	\
    (This)->lpVtbl -> GetExampleCnfg(This,bstrExampleCnfg)

#define IPluginConfig_GetBrowser(This,pBrowUnk)	\
    (This)->lpVtbl -> GetBrowser(This,pBrowUnk)

#define IPluginConfig_SetFullLogFileName(This,LogFileName)	\
    (This)->lpVtbl -> SetFullLogFileName(This,LogFileName)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_AddNotifyTags_Proxy( 
    IPluginConfig * This,
    /* [size_is][in] */ ITEMID *ClientTagID,
    /* [in] */ DWORD dwCount,
    /* [in] */ DWORD dwUpdateRate,
    /* [size_is][size_is][out] */ HRESULT **pError);


void __RPC_STUB IPluginConfig_AddNotifyTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_DelNotifyTags_Proxy( 
    IPluginConfig * This,
    /* [size_is][in] */ ITEMID *ClientTagID,
    /* [in] */ DWORD dwCount);


void __RPC_STUB IPluginConfig_DelNotifyTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_Configure_Proxy( 
    IPluginConfig * This,
    /* [in] */ BSTR CnfgString);


void __RPC_STUB IPluginConfig_Configure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_Reset_Proxy( 
    IPluginConfig * This);


void __RPC_STUB IPluginConfig_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_GetExampleCnfg_Proxy( 
    IPluginConfig * This,
    /* [out][in] */ BSTR *bstrExampleCnfg);


void __RPC_STUB IPluginConfig_GetExampleCnfg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_GetBrowser_Proxy( 
    IPluginConfig * This,
    /* [out] */ IUnknown **pBrowUnk);


void __RPC_STUB IPluginConfig_GetBrowser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_SetFullLogFileName_Proxy( 
    IPluginConfig * This,
    /* [in] */ BSTR LogFileName);


void __RPC_STUB IPluginConfig_SetFullLogFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPluginConfig_INTERFACE_DEFINED__ */


#ifndef __IPluginData_INTERFACE_DEFINED__
#define __IPluginData_INTERFACE_DEFINED__

/* interface IPluginData */
/* [helpstring][uuid][object] */ 


EXTERN_C const IID IID_IPluginData;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("EE33DD31-74D9-11d5-9CB4-004005A3070A")
    IPluginData : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetTags( 
            /* [size_is][in] */ ITEMID *ClientTagID,
            /* [in] */ DWORD dwCount,
            /* [size_is][size_is][out] */ OPCITEMSTATE **pOutStruct,
            /* [size_is][size_is][out] */ HRESULT **ppErrors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTags( 
            /* [size_is][in] */ ITEMID *ClientTagID,
            /* [in] */ DWORD Count,
            /* [size_is][in] */ VARIANT *pItemValues,
            /* [size_is][size_is][out] */ HRESULT **ppErrors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetState( 
            DWORD State) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPluginDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPluginData * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPluginData * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPluginData * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetTags )( 
            IPluginData * This,
            /* [size_is][in] */ ITEMID *ClientTagID,
            /* [in] */ DWORD dwCount,
            /* [size_is][size_is][out] */ OPCITEMSTATE **pOutStruct,
            /* [size_is][size_is][out] */ HRESULT **ppErrors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetTags )( 
            IPluginData * This,
            /* [size_is][in] */ ITEMID *ClientTagID,
            /* [in] */ DWORD Count,
            /* [size_is][in] */ VARIANT *pItemValues,
            /* [size_is][size_is][out] */ HRESULT **ppErrors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetState )( 
            IPluginData * This,
            DWORD State);
        
        END_INTERFACE
    } IPluginDataVtbl;

    interface IPluginData
    {
        CONST_VTBL struct IPluginDataVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPluginData_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPluginData_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPluginData_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPluginData_GetTags(This,ClientTagID,dwCount,pOutStruct,ppErrors)	\
    (This)->lpVtbl -> GetTags(This,ClientTagID,dwCount,pOutStruct,ppErrors)

#define IPluginData_SetTags(This,ClientTagID,Count,pItemValues,ppErrors)	\
    (This)->lpVtbl -> SetTags(This,ClientTagID,Count,pItemValues,ppErrors)

#define IPluginData_GetState(This,State)	\
    (This)->lpVtbl -> GetState(This,State)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginData_GetTags_Proxy( 
    IPluginData * This,
    /* [size_is][in] */ ITEMID *ClientTagID,
    /* [in] */ DWORD dwCount,
    /* [size_is][size_is][out] */ OPCITEMSTATE **pOutStruct,
    /* [size_is][size_is][out] */ HRESULT **ppErrors);


void __RPC_STUB IPluginData_GetTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginData_SetTags_Proxy( 
    IPluginData * This,
    /* [size_is][in] */ ITEMID *ClientTagID,
    /* [in] */ DWORD Count,
    /* [size_is][in] */ VARIANT *pItemValues,
    /* [size_is][size_is][out] */ HRESULT **ppErrors);


void __RPC_STUB IPluginData_SetTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginData_GetState_Proxy( 
    IPluginData * This,
    DWORD State);


void __RPC_STUB IPluginData_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPluginData_INTERFACE_DEFINED__ */


#ifndef __IPluginDataCallback_INTERFACE_DEFINED__
#define __IPluginDataCallback_INTERFACE_DEFINED__

/* interface IPluginDataCallback */
/* [object][helpstring][uuid] */ 


EXTERN_C const IID IID_IPluginDataCallback;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E9A79355-7442-11D5-9CB4-004005A3070A")
    IPluginDataCallback : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnTagsChange( 
            DWORD dwCount,
            DWORD *phClientItems,
            VARIANT *pvValues,
            WORD *pwQualities,
            FILETIME *pftTimeStamps,
            HRESULT *pErrors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDeviceNotAvailable( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPluginDataCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPluginDataCallback * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPluginDataCallback * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPluginDataCallback * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnTagsChange )( 
            IPluginDataCallback * This,
            DWORD dwCount,
            DWORD *phClientItems,
            VARIANT *pvValues,
            WORD *pwQualities,
            FILETIME *pftTimeStamps,
            HRESULT *pErrors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnDeviceNotAvailable )( 
            IPluginDataCallback * This);
        
        END_INTERFACE
    } IPluginDataCallbackVtbl;

    interface IPluginDataCallback
    {
        CONST_VTBL struct IPluginDataCallbackVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPluginDataCallback_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IPluginDataCallback_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IPluginDataCallback_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IPluginDataCallback_OnTagsChange(This,dwCount,phClientItems,pvValues,pwQualities,pftTimeStamps,pErrors)	\
    (This)->lpVtbl -> OnTagsChange(This,dwCount,phClientItems,pvValues,pwQualities,pftTimeStamps,pErrors)

#define IPluginDataCallback_OnDeviceNotAvailable(This)	\
    (This)->lpVtbl -> OnDeviceNotAvailable(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginDataCallback_OnTagsChange_Proxy( 
    IPluginDataCallback * This,
    DWORD dwCount,
    DWORD *phClientItems,
    VARIANT *pvValues,
    WORD *pwQualities,
    FILETIME *pftTimeStamps,
    HRESULT *pErrors);


void __RPC_STUB IPluginDataCallback_OnTagsChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginDataCallback_OnDeviceNotAvailable_Proxy( 
    IPluginDataCallback * This);


void __RPC_STUB IPluginDataCallback_OnDeviceNotAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPluginDataCallback_INTERFACE_DEFINED__ */


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


