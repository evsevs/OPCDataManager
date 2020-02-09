/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 01 15:56:21 2002
 */
/* Compiler settings for D:\Prj\VC++\OPC\OPCImpl\ForPlugin\DMPluginIfs.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
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

#ifndef __DMPluginIfs_h__
#define __DMPluginIfs_h__

#ifdef __cplusplus
extern "C"{
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

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

/* interface __MIDL_itf_DMPluginIfs_0000 */
/* [local] */ 

typedef /* [public][public][public][public][public] */ struct  __MIDL___MIDL_itf_DMPluginIfs_0000_0001
    {
    DWORD hClient;
    BSTR ItemName;
    }	ITEMID;



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
            /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
            /* [in] */ DWORD dwCount,
            /* [in] */ DWORD dwUpdateRate,
            /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *pError) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DelNotifyTags( 
            /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
            /* [in] */ DWORD dwCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Configure( 
            /* [in] */ BSTR CnfgString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Reset( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetExampleCnfg( 
            /* [out][in] */ BSTR __RPC_FAR *bstrExampleCnfg) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetBrowser( 
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *pBrowUnk) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFullLogFileName( 
            /* [in] */ BSTR LogFileName) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPluginConfigVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPluginConfig __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPluginConfig __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPluginConfig __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *AddNotifyTags )( 
            IPluginConfig __RPC_FAR * This,
            /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
            /* [in] */ DWORD dwCount,
            /* [in] */ DWORD dwUpdateRate,
            /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *pError);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DelNotifyTags )( 
            IPluginConfig __RPC_FAR * This,
            /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
            /* [in] */ DWORD dwCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Configure )( 
            IPluginConfig __RPC_FAR * This,
            /* [in] */ BSTR CnfgString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Reset )( 
            IPluginConfig __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetExampleCnfg )( 
            IPluginConfig __RPC_FAR * This,
            /* [out][in] */ BSTR __RPC_FAR *bstrExampleCnfg);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetBrowser )( 
            IPluginConfig __RPC_FAR * This,
            /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *pBrowUnk);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFullLogFileName )( 
            IPluginConfig __RPC_FAR * This,
            /* [in] */ BSTR LogFileName);
        
        END_INTERFACE
    } IPluginConfigVtbl;

    interface IPluginConfig
    {
        CONST_VTBL struct IPluginConfigVtbl __RPC_FAR *lpVtbl;
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
    IPluginConfig __RPC_FAR * This,
    /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
    /* [in] */ DWORD dwCount,
    /* [in] */ DWORD dwUpdateRate,
    /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *pError);


void __RPC_STUB IPluginConfig_AddNotifyTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_DelNotifyTags_Proxy( 
    IPluginConfig __RPC_FAR * This,
    /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
    /* [in] */ DWORD dwCount);


void __RPC_STUB IPluginConfig_DelNotifyTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_Configure_Proxy( 
    IPluginConfig __RPC_FAR * This,
    /* [in] */ BSTR CnfgString);


void __RPC_STUB IPluginConfig_Configure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_Reset_Proxy( 
    IPluginConfig __RPC_FAR * This);


void __RPC_STUB IPluginConfig_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_GetExampleCnfg_Proxy( 
    IPluginConfig __RPC_FAR * This,
    /* [out][in] */ BSTR __RPC_FAR *bstrExampleCnfg);


void __RPC_STUB IPluginConfig_GetExampleCnfg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_GetBrowser_Proxy( 
    IPluginConfig __RPC_FAR * This,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *pBrowUnk);


void __RPC_STUB IPluginConfig_GetBrowser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_SetFullLogFileName_Proxy( 
    IPluginConfig __RPC_FAR * This,
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
            /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
            /* [in] */ DWORD dwCount,
            /* [size_is][size_is][out] */ OPCITEMSTATE __RPC_FAR *__RPC_FAR *pOutStruct,
            /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetTags( 
            /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
            /* [in] */ DWORD Count,
            /* [size_is][in] */ VARIANT __RPC_FAR *pItemValues,
            /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetState( 
            DWORD State) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPluginDataVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPluginData __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPluginData __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPluginData __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTags )( 
            IPluginData __RPC_FAR * This,
            /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
            /* [in] */ DWORD dwCount,
            /* [size_is][size_is][out] */ OPCITEMSTATE __RPC_FAR *__RPC_FAR *pOutStruct,
            /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetTags )( 
            IPluginData __RPC_FAR * This,
            /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
            /* [in] */ DWORD Count,
            /* [size_is][in] */ VARIANT __RPC_FAR *pItemValues,
            /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetState )( 
            IPluginData __RPC_FAR * This,
            DWORD State);
        
        END_INTERFACE
    } IPluginDataVtbl;

    interface IPluginData
    {
        CONST_VTBL struct IPluginDataVtbl __RPC_FAR *lpVtbl;
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
    IPluginData __RPC_FAR * This,
    /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
    /* [in] */ DWORD dwCount,
    /* [size_is][size_is][out] */ OPCITEMSTATE __RPC_FAR *__RPC_FAR *pOutStruct,
    /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors);


void __RPC_STUB IPluginData_GetTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginData_SetTags_Proxy( 
    IPluginData __RPC_FAR * This,
    /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
    /* [in] */ DWORD Count,
    /* [size_is][in] */ VARIANT __RPC_FAR *pItemValues,
    /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors);


void __RPC_STUB IPluginData_SetTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginData_GetState_Proxy( 
    IPluginData __RPC_FAR * This,
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
            DWORD __RPC_FAR *phClientItems,
            VARIANT __RPC_FAR *pvValues,
            WORD __RPC_FAR *pwQualities,
            FILETIME __RPC_FAR *pftTimeStamps,
            HRESULT __RPC_FAR *pErrors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnDeviceNotAvailable( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IPluginDataCallbackVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IPluginDataCallback __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IPluginDataCallback __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IPluginDataCallback __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnTagsChange )( 
            IPluginDataCallback __RPC_FAR * This,
            DWORD dwCount,
            DWORD __RPC_FAR *phClientItems,
            VARIANT __RPC_FAR *pvValues,
            WORD __RPC_FAR *pwQualities,
            FILETIME __RPC_FAR *pftTimeStamps,
            HRESULT __RPC_FAR *pErrors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OnDeviceNotAvailable )( 
            IPluginDataCallback __RPC_FAR * This);
        
        END_INTERFACE
    } IPluginDataCallbackVtbl;

    interface IPluginDataCallback
    {
        CONST_VTBL struct IPluginDataCallbackVtbl __RPC_FAR *lpVtbl;
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
    IPluginDataCallback __RPC_FAR * This,
    DWORD dwCount,
    DWORD __RPC_FAR *phClientItems,
    VARIANT __RPC_FAR *pvValues,
    WORD __RPC_FAR *pwQualities,
    FILETIME __RPC_FAR *pftTimeStamps,
    HRESULT __RPC_FAR *pErrors);


void __RPC_STUB IPluginDataCallback_OnTagsChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginDataCallback_OnDeviceNotAvailable_Proxy( 
    IPluginDataCallback __RPC_FAR * This);


void __RPC_STUB IPluginDataCallback_OnDeviceNotAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IPluginDataCallback_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long __RPC_FAR *, unsigned long            , VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  VARIANT_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, VARIANT __RPC_FAR * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long __RPC_FAR *, VARIANT __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
