/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 01 15:56:21 2002
 */
/* Compiler settings for D:\Prj\VC++\OPC\OPCImpl\ForPlugin\DMPluginIfs.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 440
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif // __RPCPROXY_H_VERSION__


#include "DMPluginIfs.h"

#define TYPE_FORMAT_STRING_SIZE   1159                              
#define PROC_FORMAT_STRING_SIZE   103                               

typedef struct _MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } MIDL_TYPE_FORMAT_STRING;

typedef struct _MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } MIDL_PROC_FORMAT_STRING;


extern const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString;
extern const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString;


/* Standard interface: __MIDL_itf_DMPluginIfs_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IPluginConfig, ver. 0.0,
   GUID={0xEE33DD30,0x74D9,0x11d5,{0x9C,0xB4,0x00,0x40,0x05,0xA3,0x07,0x0A}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_AddNotifyTags_Proxy( 
    IPluginConfig __RPC_FAR * This,
    /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
    /* [in] */ DWORD dwCount,
    /* [in] */ DWORD dwUpdateRate,
    /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *pError)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pError)
        {
        *pError = 0;
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!ClientTagID)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pError)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 7U + 7U;
            _StubMsg.MaxCount = dwCount;
            
            NdrComplexArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)ClientTagID,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.MaxCount = dwCount;
            
            NdrComplexArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)ClientTagID,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54] );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = dwCount;
            
            *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = dwUpdateRate;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pError,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = dwCount;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[72],
                         ( void __RPC_FAR * )pError);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginConfig_AddNotifyTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ITEMID __RPC_FAR *ClientTagID;
    HRESULT __RPC_FAR *_M2;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    DWORD dwCount;
    DWORD dwUpdateRate;
    HRESULT __RPC_FAR *__RPC_FAR *pError;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( ITEMID __RPC_FAR * )ClientTagID = 0;
    ( HRESULT __RPC_FAR *__RPC_FAR * )pError = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&ClientTagID,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54],
                                   (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwCount = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
        
        dwUpdateRate = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
        
        pError = &_M2;
        _M2 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginConfig*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> AddNotifyTags(
                 (IPluginConfig *) ((CStdStubBuffer *)This)->pvServerObject,
                 ClientTagID,
                 dwCount,
                 dwUpdateRate,
                 pError);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 7U;
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)pError,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)pError,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ClientTagID,
                        &__MIDL_TypeFormatString.Format[2] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pError,
                        &__MIDL_TypeFormatString.Format[72] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_DelNotifyTags_Proxy( 
    IPluginConfig __RPC_FAR * This,
    /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
    /* [in] */ DWORD dwCount)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        if(!ClientTagID)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 7U;
            _StubMsg.MaxCount = dwCount;
            
            NdrComplexArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)ClientTagID,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.MaxCount = dwCount;
            
            NdrComplexArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)ClientTagID,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54] );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = dwCount;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginConfig_DelNotifyTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ITEMID __RPC_FAR *ClientTagID;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    DWORD dwCount;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( ITEMID __RPC_FAR * )ClientTagID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[14] );
        
        NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&ClientTagID,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54],
                                   (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwCount = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginConfig*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> DelNotifyTags(
                 (IPluginConfig *) ((CStdStubBuffer *)This)->pvServerObject,
                 ClientTagID,
                 dwCount);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ClientTagID,
                        &__MIDL_TypeFormatString.Format[2] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_Configure_Proxy( 
    IPluginConfig __RPC_FAR * This,
    /* [in] */ BSTR CnfgString)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&CnfgString,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&CnfgString,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginConfig_Configure_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR CnfgString;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_CnfgString;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_CnfgString = &CnfgString;
    MIDL_memset(
               _p_CnfgString,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_CnfgString,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginConfig*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Configure((IPluginConfig *) ((CStdStubBuffer *)This)->pvServerObject,CnfgString);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&CnfgString,
                            &__MIDL_TypeFormatString.Format[30] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_Reset_Proxy( 
    IPluginConfig __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      6);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginConfig_Reset_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginConfig*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> Reset((IPluginConfig *) ((CStdStubBuffer *)This)->pvServerObject);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_GetExampleCnfg_Proxy( 
    IPluginConfig __RPC_FAR * This,
    /* [out][in] */ BSTR __RPC_FAR *bstrExampleCnfg)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
        
        
        
        if(!bstrExampleCnfg)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)bstrExampleCnfg,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[98] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)bstrExampleCnfg,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[98] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[30] );
            
            NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&bstrExampleCnfg,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[98],
                                      (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[90],
                         ( void __RPC_FAR * )bstrExampleCnfg);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginConfig_GetExampleCnfg_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BSTR __RPC_FAR *bstrExampleCnfg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( BSTR __RPC_FAR * )bstrExampleCnfg = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[30] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&bstrExampleCnfg,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[98],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginConfig*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetExampleCnfg((IPluginConfig *) ((CStdStubBuffer *)This)->pvServerObject,bstrExampleCnfg);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 11U;
        NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)bstrExampleCnfg,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[98] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)bstrExampleCnfg,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[98] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)bstrExampleCnfg,
                        &__MIDL_TypeFormatString.Format[90] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_GetBrowser_Proxy( 
    IPluginConfig __RPC_FAR * This,
    /* [out] */ IUnknown __RPC_FAR *__RPC_FAR *pBrowUnk)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pBrowUnk)
        {
        MIDL_memset(
               pBrowUnk,
               0,
               sizeof( IUnknown __RPC_FAR *__RPC_FAR * ));
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      8);
        
        
        
        if(!pBrowUnk)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[36] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pBrowUnk,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[108],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[108],
                         ( void __RPC_FAR * )pBrowUnk);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginConfig_GetBrowser_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    IUnknown __RPC_FAR *_M4;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    IUnknown __RPC_FAR *__RPC_FAR *pBrowUnk;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( IUnknown __RPC_FAR *__RPC_FAR * )pBrowUnk = 0;
    RpcTryFinally
        {
        pBrowUnk = &_M4;
        _M4 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginConfig*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetBrowser((IPluginConfig *) ((CStdStubBuffer *)This)->pvServerObject,pBrowUnk);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)pBrowUnk,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[108] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)pBrowUnk,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[108] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pBrowUnk,
                        &__MIDL_TypeFormatString.Format[108] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginConfig_SetFullLogFileName_Proxy( 
    IPluginConfig __RPC_FAR * This,
    /* [in] */ BSTR LogFileName)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      9);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&LogFileName,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&LogFileName,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginConfig_SetFullLogFileName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR LogFileName;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_LogFileName;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_LogFileName = &LogFileName;
    MIDL_memset(
               _p_LogFileName,
               0,
               sizeof( BSTR  ));
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[22] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_LogFileName,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[30],
                                  (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginConfig*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetFullLogFileName((IPluginConfig *) ((CStdStubBuffer *)This)->pvServerObject,LogFileName);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&LogFileName,
                            &__MIDL_TypeFormatString.Format[30] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(10) _IPluginConfigProxyVtbl = 
{
    &IID_IPluginConfig,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IPluginConfig_AddNotifyTags_Proxy ,
    IPluginConfig_DelNotifyTags_Proxy ,
    IPluginConfig_Configure_Proxy ,
    IPluginConfig_Reset_Proxy ,
    IPluginConfig_GetExampleCnfg_Proxy ,
    IPluginConfig_GetBrowser_Proxy ,
    IPluginConfig_SetFullLogFileName_Proxy
};


static const PRPC_STUB_FUNCTION IPluginConfig_table[] =
{
    IPluginConfig_AddNotifyTags_Stub,
    IPluginConfig_DelNotifyTags_Stub,
    IPluginConfig_Configure_Stub,
    IPluginConfig_Reset_Stub,
    IPluginConfig_GetExampleCnfg_Stub,
    IPluginConfig_GetBrowser_Stub,
    IPluginConfig_SetFullLogFileName_Stub
};

const CInterfaceStubVtbl _IPluginConfigStubVtbl =
{
    &IID_IPluginConfig,
    0,
    10,
    &IPluginConfig_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IPluginData, ver. 0.0,
   GUID={0xEE33DD31,0x74D9,0x11d5,{0x9C,0xB4,0x00,0x40,0x05,0xA3,0x07,0x0A}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginData_GetTags_Proxy( 
    IPluginData __RPC_FAR * This,
    /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
    /* [in] */ DWORD dwCount,
    /* [size_is][size_is][out] */ OPCITEMSTATE __RPC_FAR *__RPC_FAR *pOutStruct,
    /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(pOutStruct)
        {
        *pOutStruct = 0;
        }
    if(ppErrors)
        {
        *ppErrors = 0;
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!ClientTagID)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pOutStruct)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppErrors)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 7U;
            _StubMsg.MaxCount = dwCount;
            
            NdrComplexArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)ClientTagID,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.MaxCount = dwCount;
            
            NdrComplexArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)ClientTagID,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54] );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = dwCount;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[42] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pOutStruct,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[130],
                                  (unsigned char)0 );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppErrors,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = dwCount;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[130],
                         ( void __RPC_FAR * )pOutStruct);
        _StubMsg.MaxCount = dwCount;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[72],
                         ( void __RPC_FAR * )ppErrors);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginData_GetTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ITEMID __RPC_FAR *ClientTagID;
    OPCITEMSTATE __RPC_FAR *_M8;
    HRESULT __RPC_FAR *_M9;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    DWORD dwCount;
    OPCITEMSTATE __RPC_FAR *__RPC_FAR *pOutStruct;
    HRESULT __RPC_FAR *__RPC_FAR *ppErrors;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( ITEMID __RPC_FAR * )ClientTagID = 0;
    ( OPCITEMSTATE __RPC_FAR *__RPC_FAR * )pOutStruct = 0;
    ( HRESULT __RPC_FAR *__RPC_FAR * )ppErrors = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[42] );
        
        NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&ClientTagID,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54],
                                   (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwCount = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
        
        pOutStruct = &_M8;
        _M8 = 0;
        ppErrors = &_M9;
        _M9 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginData*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetTags(
           (IPluginData *) ((CStdStubBuffer *)This)->pvServerObject,
           ClientTagID,
           dwCount,
           pOutStruct,
           ppErrors);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 14U + 7U;
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)pOutStruct,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[130] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppErrors,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)pOutStruct,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[130] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppErrors,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ClientTagID,
                        &__MIDL_TypeFormatString.Format[2] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pOutStruct,
                        &__MIDL_TypeFormatString.Format[130] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppErrors,
                        &__MIDL_TypeFormatString.Format[72] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginData_SetTags_Proxy( 
    IPluginData __RPC_FAR * This,
    /* [size_is][in] */ ITEMID __RPC_FAR *ClientTagID,
    /* [in] */ DWORD Count,
    /* [size_is][in] */ VARIANT __RPC_FAR *pItemValues,
    /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ppErrors)
        {
        *ppErrors = 0;
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        if(!ClientTagID)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pItemValues)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppErrors)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 7U + 7U;
            _StubMsg.MaxCount = Count;
            
            NdrComplexArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)ClientTagID,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54] );
            
            _StubMsg.MaxCount = Count;
            
            NdrComplexArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)pItemValues,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1124] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            _StubMsg.MaxCount = Count;
            
            NdrComplexArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)ClientTagID,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54] );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = Count;
            
            _StubMsg.MaxCount = Count;
            
            NdrComplexArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)pItemValues,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1124] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[58] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppErrors,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72],
                                  (unsigned char)0 );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _StubMsg.MaxCount = Count;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[72],
                         ( void __RPC_FAR * )ppErrors);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginData_SetTags_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    ITEMID __RPC_FAR *ClientTagID;
    DWORD Count;
    HRESULT __RPC_FAR *_M13;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    VARIANT __RPC_FAR *pItemValues;
    HRESULT __RPC_FAR *__RPC_FAR *ppErrors;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( ITEMID __RPC_FAR * )ClientTagID = 0;
    ( VARIANT __RPC_FAR * )pItemValues = 0;
    ( HRESULT __RPC_FAR *__RPC_FAR * )ppErrors = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[58] );
        
        NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&ClientTagID,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[54],
                                   (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        Count = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrComplexArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&pItemValues,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1124],
                                   (unsigned char)0 );
        
        ppErrors = &_M13;
        _M13 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginData*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> SetTags(
           (IPluginData *) ((CStdStubBuffer *)This)->pvServerObject,
           ClientTagID,
           Count,
           pItemValues,
           ppErrors);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 7U;
        _StubMsg.MaxCount = Count;
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppErrors,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = Count;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppErrors,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[72] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = Count;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ClientTagID,
                        &__MIDL_TypeFormatString.Format[2] );
        
        _StubMsg.MaxCount = Count;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pItemValues,
                        &__MIDL_TypeFormatString.Format[1106] );
        
        _StubMsg.MaxCount = Count;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppErrors,
                        &__MIDL_TypeFormatString.Format[72] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginData_GetState_Proxy( 
    IPluginData __RPC_FAR * This,
    DWORD State)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      5);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U;
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = State;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[74] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginData_GetState_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    DWORD State;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[74] );
        
        State = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginData*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetState((IPluginData *) ((CStdStubBuffer *)This)->pvServerObject,State);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

const CINTERFACE_PROXY_VTABLE(6) _IPluginDataProxyVtbl = 
{
    &IID_IPluginData,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IPluginData_GetTags_Proxy ,
    IPluginData_SetTags_Proxy ,
    IPluginData_GetState_Proxy
};


static const PRPC_STUB_FUNCTION IPluginData_table[] =
{
    IPluginData_GetTags_Stub,
    IPluginData_SetTags_Stub,
    IPluginData_GetState_Stub
};

const CInterfaceStubVtbl _IPluginDataStubVtbl =
{
    &IID_IPluginData,
    0,
    6,
    &IPluginData_table[-3],
    CStdStubBuffer_METHODS
};


/* Object interface: IPluginDataCallback, ver. 0.0,
   GUID={0xE9A79355,0x7442,0x11D5,{0x9C,0xB4,0x00,0x40,0x05,0xA3,0x07,0x0A}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginDataCallback_OnTagsChange_Proxy( 
    IPluginDataCallback __RPC_FAR * This,
    DWORD dwCount,
    DWORD __RPC_FAR *phClientItems,
    VARIANT __RPC_FAR *pvValues,
    WORD __RPC_FAR *pwQualities,
    FILETIME __RPC_FAR *pftTimeStamps,
    HRESULT __RPC_FAR *pErrors)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      3);
        
        
        
        if(!phClientItems)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pvValues)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pwQualities)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pftTimeStamps)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!pErrors)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U + 8U + 5U + 6U + 11U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)pvValues,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1114] );
            
            NdrSimpleStructBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR *)pftTimeStamps,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[138] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = dwCount;
            
            *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = *phClientItems;
            
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)pvValues,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1114] );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
            *(( WORD __RPC_FAR * )_StubMsg.Buffer)++ = *pwQualities;
            
            NdrSimpleStructMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                     (unsigned char __RPC_FAR *)pftTimeStamps,
                                     (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[138] );
            
            *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = *pErrors;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[78] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginDataCallback_OnTagsChange_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    DWORD dwCount;
    HRESULT __RPC_FAR *pErrors;
    FILETIME __RPC_FAR *pftTimeStamps;
    DWORD __RPC_FAR *phClientItems;
    VARIANT __RPC_FAR *pvValues;
    WORD __RPC_FAR *pwQualities;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( DWORD __RPC_FAR * )phClientItems = 0;
    ( VARIANT __RPC_FAR * )pvValues = 0;
    ( WORD __RPC_FAR * )pwQualities = 0;
    ( FILETIME __RPC_FAR * )pftTimeStamps = 0;
    ( HRESULT __RPC_FAR * )pErrors = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[78] );
        
        dwCount = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
        
        phClientItems = ( DWORD __RPC_FAR * )_StubMsg.Buffer;
        _StubMsg.Buffer += sizeof( DWORD  );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&pvValues,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1114],
                                  (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 1) & ~ 0x1);
        pwQualities = ( WORD __RPC_FAR * )_StubMsg.Buffer;
        _StubMsg.Buffer += sizeof( WORD  );
        
        NdrSimpleStructUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                   (unsigned char __RPC_FAR * __RPC_FAR *)&pftTimeStamps,
                                   (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[138],
                                   (unsigned char)0 );
        
        pErrors = ( HRESULT __RPC_FAR * )_StubMsg.Buffer;
        _StubMsg.Buffer += sizeof( HRESULT  );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginDataCallback*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> OnTagsChange(
                (IPluginDataCallback *) ((CStdStubBuffer *)This)->pvServerObject,
                dwCount,
                phClientItems,
                pvValues,
                pwQualities,
                pftTimeStamps,
                pErrors);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pvValues,
                        &__MIDL_TypeFormatString.Format[1146] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE IPluginDataCallback_OnDeviceNotAvailable_Proxy( 
    IPluginDataCallback __RPC_FAR * This)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      4);
        
        
        
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 0U;
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[28] );
            
            _RetVal = *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++;
            
            }
        RpcFinally
            {
            NdrProxyFreeBuffer(This, &_StubMsg);
            
            }
        RpcEndFinally
        
        }
    RpcExcept(_StubMsg.dwStubPhase != PROXY_SENDRECEIVE)
        {
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB IPluginDataCallback_OnDeviceNotAvailable_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    RpcTryFinally
        {
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((IPluginDataCallback*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> OnDeviceNotAvailable((IPluginDataCallback *) ((CStdStubBuffer *)This)->pvServerObject);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}

extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2];

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    __MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x20000, /* Ndr library version */
    0,
    0x50100a4, /* MIDL Version 5.1.164 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    1,  /* Flags */
    0,  /* Reserved3 */
    0,  /* Reserved4 */
    0   /* Reserved5 */
    };

const CINTERFACE_PROXY_VTABLE(5) _IPluginDataCallbackProxyVtbl = 
{
    &IID_IPluginDataCallback,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    IPluginDataCallback_OnTagsChange_Proxy ,
    IPluginDataCallback_OnDeviceNotAvailable_Proxy
};


static const PRPC_STUB_FUNCTION IPluginDataCallback_table[] =
{
    IPluginDataCallback_OnTagsChange_Stub,
    IPluginDataCallback_OnDeviceNotAvailable_Stub
};

const CInterfaceStubVtbl _IPluginDataCallbackStubVtbl =
{
    &IID_IPluginDataCallback,
    0,
    5,
    &IPluginDataCallback_table[-3],
    CStdStubBuffer_METHODS
};

#pragma data_seg(".rdata")

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[2] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            },
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT40_OR_LATER)
#error You need a Windows NT 4.0 or later to run this stub because it uses these features:
#error   [wire_marshal] or [user_marshal] attribute.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will die there with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const MIDL_PROC_FORMAT_STRING __MIDL_ProcFormatString =
    {
        0,
        {
			
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  2 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/*  4 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  6 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/*  8 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 10 */	NdrFcShort( 0x48 ),	/* Type Offset=72 */
/* 12 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 14 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 16 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/* 18 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 20 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 22 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 24 */	NdrFcShort( 0x1e ),	/* Type Offset=30 */
/* 26 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 28 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 30 */	
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 32 */	NdrFcShort( 0x5a ),	/* Type Offset=90 */
/* 34 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 36 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 38 */	NdrFcShort( 0x6c ),	/* Type Offset=108 */
/* 40 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 42 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 44 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/* 46 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 48 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 50 */	NdrFcShort( 0x82 ),	/* Type Offset=130 */
/* 52 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 54 */	NdrFcShort( 0x48 ),	/* Type Offset=72 */
/* 56 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 58 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 60 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/* 62 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 64 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 66 */	NdrFcShort( 0x452 ),	/* Type Offset=1106 */
/* 68 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 70 */	NdrFcShort( 0x48 ),	/* Type Offset=72 */
/* 72 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 74 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 76 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 78 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 80 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 82 */	NdrFcShort( 0x476 ),	/* Type Offset=1142 */
/* 84 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 86 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */
/* 88 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 90 */	NdrFcShort( 0x47e ),	/* Type Offset=1150 */
/* 92 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 94 */	NdrFcShort( 0x482 ),	/* Type Offset=1154 */
/* 96 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 98 */	NdrFcShort( 0x476 ),	/* Type Offset=1142 */
/* 100 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */

			0x0
        }
    };

static const MIDL_TYPE_FORMAT_STRING __MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x0,	/* FC_RP */
/*  4 */	NdrFcShort( 0x32 ),	/* Offset= 50 (54) */
/*  6 */	
			0x12, 0x0,	/* FC_UP */
/*  8 */	NdrFcShort( 0xc ),	/* Offset= 12 (20) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 20 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 22 */	NdrFcShort( 0x8 ),	/* 8 */
/* 24 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (10) */
/* 26 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 28 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 30 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 32 */	NdrFcShort( 0x0 ),	/* 0 */
/* 34 */	NdrFcShort( 0x4 ),	/* 4 */
/* 36 */	NdrFcShort( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (6) */
/* 40 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 42 */	NdrFcShort( 0x8 ),	/* 8 */
/* 44 */	NdrFcShort( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x0 ),	/* Offset= 0 (46) */
/* 48 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 50 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffeb ),	/* Offset= -21 (30) */
			0x5b,		/* FC_END */
/* 54 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 60 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 62 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 66 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 68 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (40) */
/* 70 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 72 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 74 */	NdrFcShort( 0x2 ),	/* Offset= 2 (76) */
/* 76 */	
			0x13, 0x0,	/* FC_OP */
/* 78 */	NdrFcShort( 0x2 ),	/* Offset= 2 (80) */
/* 80 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 82 */	NdrFcShort( 0x4 ),	/* 4 */
/* 84 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 86 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 88 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 90 */	
			0x11, 0x0,	/* FC_RP */
/* 92 */	NdrFcShort( 0x6 ),	/* Offset= 6 (98) */
/* 94 */	
			0x13, 0x0,	/* FC_OP */
/* 96 */	NdrFcShort( 0xffffffb4 ),	/* Offset= -76 (20) */
/* 98 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */
/* 102 */	NdrFcShort( 0x4 ),	/* 4 */
/* 104 */	NdrFcShort( 0x0 ),	/* 0 */
/* 106 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (94) */
/* 108 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 110 */	NdrFcShort( 0x2 ),	/* Offset= 2 (112) */
/* 112 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 114 */	NdrFcLong( 0x0 ),	/* 0 */
/* 118 */	NdrFcShort( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 122 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 124 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 126 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 128 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 130 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 132 */	NdrFcShort( 0x2 ),	/* Offset= 2 (134) */
/* 134 */	
			0x13, 0x0,	/* FC_OP */
/* 136 */	NdrFcShort( 0x3b8 ),	/* Offset= 952 (1088) */
/* 138 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 140 */	NdrFcShort( 0x8 ),	/* 8 */
/* 142 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 144 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 146 */	
			0x13, 0x0,	/* FC_OP */
/* 148 */	NdrFcShort( 0x37a ),	/* Offset= 890 (1038) */
/* 150 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 152 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 154 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 156 */	NdrFcShort( 0x2 ),	/* Offset= 2 (158) */
/* 158 */	NdrFcShort( 0x10 ),	/* 16 */
/* 160 */	NdrFcShort( 0x2b ),	/* 43 */
/* 162 */	NdrFcLong( 0x3 ),	/* 3 */
/* 166 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 168 */	NdrFcLong( 0x11 ),	/* 17 */
/* 172 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 174 */	NdrFcLong( 0x2 ),	/* 2 */
/* 178 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 180 */	NdrFcLong( 0x4 ),	/* 4 */
/* 184 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 186 */	NdrFcLong( 0x5 ),	/* 5 */
/* 190 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 192 */	NdrFcLong( 0xb ),	/* 11 */
/* 196 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 198 */	NdrFcLong( 0xa ),	/* 10 */
/* 202 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 204 */	NdrFcLong( 0x6 ),	/* 6 */
/* 208 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (422) */
/* 210 */	NdrFcLong( 0x7 ),	/* 7 */
/* 214 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 216 */	NdrFcLong( 0x8 ),	/* 8 */
/* 220 */	NdrFcShort( 0xffffff82 ),	/* Offset= -126 (94) */
/* 222 */	NdrFcLong( 0xd ),	/* 13 */
/* 226 */	NdrFcShort( 0xffffff8e ),	/* Offset= -114 (112) */
/* 228 */	NdrFcLong( 0x9 ),	/* 9 */
/* 232 */	NdrFcShort( 0xc4 ),	/* Offset= 196 (428) */
/* 234 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 238 */	NdrFcShort( 0xd0 ),	/* Offset= 208 (446) */
/* 240 */	NdrFcLong( 0x24 ),	/* 36 */
/* 244 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (970) */
/* 246 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 250 */	NdrFcShort( 0x2d0 ),	/* Offset= 720 (970) */
/* 252 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 256 */	NdrFcShort( 0x2ce ),	/* Offset= 718 (974) */
/* 258 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 262 */	NdrFcShort( 0x2cc ),	/* Offset= 716 (978) */
/* 264 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 268 */	NdrFcShort( 0x2ca ),	/* Offset= 714 (982) */
/* 270 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 274 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (986) */
/* 276 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 280 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (990) */
/* 282 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 286 */	NdrFcShort( 0x2b4 ),	/* Offset= 692 (978) */
/* 288 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 292 */	NdrFcShort( 0x2b2 ),	/* Offset= 690 (982) */
/* 294 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 298 */	NdrFcShort( 0x2b8 ),	/* Offset= 696 (994) */
/* 300 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 304 */	NdrFcShort( 0x2ae ),	/* Offset= 686 (990) */
/* 306 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 310 */	NdrFcShort( 0x2b0 ),	/* Offset= 688 (998) */
/* 312 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 316 */	NdrFcShort( 0x2ae ),	/* Offset= 686 (1002) */
/* 318 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 322 */	NdrFcShort( 0x2ac ),	/* Offset= 684 (1006) */
/* 324 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 328 */	NdrFcShort( 0x2aa ),	/* Offset= 682 (1010) */
/* 330 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 334 */	NdrFcShort( 0x2a8 ),	/* Offset= 680 (1014) */
/* 336 */	NdrFcLong( 0x10 ),	/* 16 */
/* 340 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 342 */	NdrFcLong( 0x12 ),	/* 18 */
/* 346 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 348 */	NdrFcLong( 0x13 ),	/* 19 */
/* 352 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 354 */	NdrFcLong( 0x16 ),	/* 22 */
/* 358 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 360 */	NdrFcLong( 0x17 ),	/* 23 */
/* 364 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 366 */	NdrFcLong( 0xe ),	/* 14 */
/* 370 */	NdrFcShort( 0x28c ),	/* Offset= 652 (1022) */
/* 372 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 376 */	NdrFcShort( 0x292 ),	/* Offset= 658 (1034) */
/* 378 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 382 */	NdrFcShort( 0x250 ),	/* Offset= 592 (974) */
/* 384 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 388 */	NdrFcShort( 0x24e ),	/* Offset= 590 (978) */
/* 390 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 394 */	NdrFcShort( 0x24c ),	/* Offset= 588 (982) */
/* 396 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 400 */	NdrFcShort( 0x246 ),	/* Offset= 582 (982) */
/* 402 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 406 */	NdrFcShort( 0x240 ),	/* Offset= 576 (982) */
/* 408 */	NdrFcLong( 0x0 ),	/* 0 */
/* 412 */	NdrFcShort( 0x0 ),	/* Offset= 0 (412) */
/* 414 */	NdrFcLong( 0x1 ),	/* 1 */
/* 418 */	NdrFcShort( 0x0 ),	/* Offset= 0 (418) */
/* 420 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (419) */
/* 422 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 424 */	NdrFcShort( 0x8 ),	/* 8 */
/* 426 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 428 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 430 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 434 */	NdrFcShort( 0x0 ),	/* 0 */
/* 436 */	NdrFcShort( 0x0 ),	/* 0 */
/* 438 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 440 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 442 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 444 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 446 */	
			0x13, 0x0,	/* FC_OP */
/* 448 */	NdrFcShort( 0x1f8 ),	/* Offset= 504 (952) */
/* 450 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 452 */	NdrFcShort( 0x18 ),	/* 24 */
/* 454 */	NdrFcShort( 0xa ),	/* 10 */
/* 456 */	NdrFcLong( 0x8 ),	/* 8 */
/* 460 */	NdrFcShort( 0x58 ),	/* Offset= 88 (548) */
/* 462 */	NdrFcLong( 0xd ),	/* 13 */
/* 466 */	NdrFcShort( 0x78 ),	/* Offset= 120 (586) */
/* 468 */	NdrFcLong( 0x9 ),	/* 9 */
/* 472 */	NdrFcShort( 0x94 ),	/* Offset= 148 (620) */
/* 474 */	NdrFcLong( 0xc ),	/* 12 */
/* 478 */	NdrFcShort( 0xbc ),	/* Offset= 188 (666) */
/* 480 */	NdrFcLong( 0x24 ),	/* 36 */
/* 484 */	NdrFcShort( 0x118 ),	/* Offset= 280 (764) */
/* 486 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 490 */	NdrFcShort( 0x134 ),	/* Offset= 308 (798) */
/* 492 */	NdrFcLong( 0x10 ),	/* 16 */
/* 496 */	NdrFcShort( 0x14c ),	/* Offset= 332 (828) */
/* 498 */	NdrFcLong( 0x2 ),	/* 2 */
/* 502 */	NdrFcShort( 0x164 ),	/* Offset= 356 (858) */
/* 504 */	NdrFcLong( 0x3 ),	/* 3 */
/* 508 */	NdrFcShort( 0x17c ),	/* Offset= 380 (888) */
/* 510 */	NdrFcLong( 0x14 ),	/* 20 */
/* 514 */	NdrFcShort( 0x194 ),	/* Offset= 404 (918) */
/* 516 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (515) */
/* 518 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 520 */	NdrFcShort( 0x4 ),	/* 4 */
/* 522 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 524 */	NdrFcShort( 0x0 ),	/* 0 */
/* 526 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 528 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 530 */	NdrFcShort( 0x4 ),	/* 4 */
/* 532 */	NdrFcShort( 0x0 ),	/* 0 */
/* 534 */	NdrFcShort( 0x1 ),	/* 1 */
/* 536 */	NdrFcShort( 0x0 ),	/* 0 */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 540 */	0x13, 0x0,	/* FC_OP */
/* 542 */	NdrFcShort( 0xfffffdf6 ),	/* Offset= -522 (20) */
/* 544 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 546 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 548 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 550 */	NdrFcShort( 0x8 ),	/* 8 */
/* 552 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 554 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 556 */	NdrFcShort( 0x4 ),	/* 4 */
/* 558 */	NdrFcShort( 0x4 ),	/* 4 */
/* 560 */	0x11, 0x0,	/* FC_RP */
/* 562 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (518) */
/* 564 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 566 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 568 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 570 */	NdrFcShort( 0x0 ),	/* 0 */
/* 572 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 574 */	NdrFcShort( 0x0 ),	/* 0 */
/* 576 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 580 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 582 */	NdrFcShort( 0xfffffe2a ),	/* Offset= -470 (112) */
/* 584 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 586 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 588 */	NdrFcShort( 0x8 ),	/* 8 */
/* 590 */	NdrFcShort( 0x0 ),	/* 0 */
/* 592 */	NdrFcShort( 0x6 ),	/* Offset= 6 (598) */
/* 594 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 596 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 598 */	
			0x11, 0x0,	/* FC_RP */
/* 600 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (568) */
/* 602 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 604 */	NdrFcShort( 0x0 ),	/* 0 */
/* 606 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 608 */	NdrFcShort( 0x0 ),	/* 0 */
/* 610 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 614 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 616 */	NdrFcShort( 0xffffff44 ),	/* Offset= -188 (428) */
/* 618 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 620 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 622 */	NdrFcShort( 0x8 ),	/* 8 */
/* 624 */	NdrFcShort( 0x0 ),	/* 0 */
/* 626 */	NdrFcShort( 0x6 ),	/* Offset= 6 (632) */
/* 628 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 630 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 632 */	
			0x11, 0x0,	/* FC_RP */
/* 634 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (602) */
/* 636 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 638 */	NdrFcShort( 0x4 ),	/* 4 */
/* 640 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 642 */	NdrFcShort( 0x0 ),	/* 0 */
/* 644 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 646 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 648 */	NdrFcShort( 0x4 ),	/* 4 */
/* 650 */	NdrFcShort( 0x0 ),	/* 0 */
/* 652 */	NdrFcShort( 0x1 ),	/* 1 */
/* 654 */	NdrFcShort( 0x0 ),	/* 0 */
/* 656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 658 */	0x13, 0x0,	/* FC_OP */
/* 660 */	NdrFcShort( 0x17a ),	/* Offset= 378 (1038) */
/* 662 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 664 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 666 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 668 */	NdrFcShort( 0x8 ),	/* 8 */
/* 670 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 672 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 674 */	NdrFcShort( 0x4 ),	/* 4 */
/* 676 */	NdrFcShort( 0x4 ),	/* 4 */
/* 678 */	0x11, 0x0,	/* FC_RP */
/* 680 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (636) */
/* 682 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 684 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 686 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 688 */	NdrFcLong( 0x2f ),	/* 47 */
/* 692 */	NdrFcShort( 0x0 ),	/* 0 */
/* 694 */	NdrFcShort( 0x0 ),	/* 0 */
/* 696 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 698 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 700 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 702 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 704 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 706 */	NdrFcShort( 0x1 ),	/* 1 */
/* 708 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 710 */	NdrFcShort( 0x4 ),	/* 4 */
/* 712 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 714 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 716 */	NdrFcShort( 0x10 ),	/* 16 */
/* 718 */	NdrFcShort( 0x0 ),	/* 0 */
/* 720 */	NdrFcShort( 0xa ),	/* Offset= 10 (730) */
/* 722 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 724 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 726 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (686) */
/* 728 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 730 */	
			0x13, 0x0,	/* FC_OP */
/* 732 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (704) */
/* 734 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 736 */	NdrFcShort( 0x4 ),	/* 4 */
/* 738 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 742 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 744 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 746 */	NdrFcShort( 0x4 ),	/* 4 */
/* 748 */	NdrFcShort( 0x0 ),	/* 0 */
/* 750 */	NdrFcShort( 0x1 ),	/* 1 */
/* 752 */	NdrFcShort( 0x0 ),	/* 0 */
/* 754 */	NdrFcShort( 0x0 ),	/* 0 */
/* 756 */	0x13, 0x0,	/* FC_OP */
/* 758 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (714) */
/* 760 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 762 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 764 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 766 */	NdrFcShort( 0x8 ),	/* 8 */
/* 768 */	NdrFcShort( 0x0 ),	/* 0 */
/* 770 */	NdrFcShort( 0x6 ),	/* Offset= 6 (776) */
/* 772 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 774 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 776 */	
			0x11, 0x0,	/* FC_RP */
/* 778 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (734) */
/* 780 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 782 */	NdrFcShort( 0x8 ),	/* 8 */
/* 784 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 786 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 788 */	NdrFcShort( 0x10 ),	/* 16 */
/* 790 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 792 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 794 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (780) */
			0x5b,		/* FC_END */
/* 798 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 800 */	NdrFcShort( 0x18 ),	/* 24 */
/* 802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0xa ),	/* Offset= 10 (814) */
/* 806 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 808 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 810 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (786) */
/* 812 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 814 */	
			0x11, 0x0,	/* FC_RP */
/* 816 */	NdrFcShort( 0xffffff08 ),	/* Offset= -248 (568) */
/* 818 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 820 */	NdrFcShort( 0x1 ),	/* 1 */
/* 822 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 824 */	NdrFcShort( 0x0 ),	/* 0 */
/* 826 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 828 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 830 */	NdrFcShort( 0x8 ),	/* 8 */
/* 832 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 834 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 836 */	NdrFcShort( 0x4 ),	/* 4 */
/* 838 */	NdrFcShort( 0x4 ),	/* 4 */
/* 840 */	0x13, 0x0,	/* FC_OP */
/* 842 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (818) */
/* 844 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 846 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 848 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 850 */	NdrFcShort( 0x2 ),	/* 2 */
/* 852 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 854 */	NdrFcShort( 0x0 ),	/* 0 */
/* 856 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 858 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 860 */	NdrFcShort( 0x8 ),	/* 8 */
/* 862 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 864 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 866 */	NdrFcShort( 0x4 ),	/* 4 */
/* 868 */	NdrFcShort( 0x4 ),	/* 4 */
/* 870 */	0x13, 0x0,	/* FC_OP */
/* 872 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (848) */
/* 874 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 876 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 878 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 880 */	NdrFcShort( 0x4 ),	/* 4 */
/* 882 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 884 */	NdrFcShort( 0x0 ),	/* 0 */
/* 886 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 888 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 890 */	NdrFcShort( 0x8 ),	/* 8 */
/* 892 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 894 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 896 */	NdrFcShort( 0x4 ),	/* 4 */
/* 898 */	NdrFcShort( 0x4 ),	/* 4 */
/* 900 */	0x13, 0x0,	/* FC_OP */
/* 902 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (878) */
/* 904 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 906 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 908 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 910 */	NdrFcShort( 0x8 ),	/* 8 */
/* 912 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 914 */	NdrFcShort( 0x0 ),	/* 0 */
/* 916 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 918 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 920 */	NdrFcShort( 0x8 ),	/* 8 */
/* 922 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 924 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 926 */	NdrFcShort( 0x4 ),	/* 4 */
/* 928 */	NdrFcShort( 0x4 ),	/* 4 */
/* 930 */	0x13, 0x0,	/* FC_OP */
/* 932 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (908) */
/* 934 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 936 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 938 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 940 */	NdrFcShort( 0x8 ),	/* 8 */
/* 942 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 944 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 946 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 948 */	NdrFcShort( 0xfffffcd6 ),	/* Offset= -810 (138) */
/* 950 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 952 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 954 */	NdrFcShort( 0x28 ),	/* 40 */
/* 956 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (938) */
/* 958 */	NdrFcShort( 0x0 ),	/* Offset= 0 (958) */
/* 960 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 962 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 964 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 966 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffdfb ),	/* Offset= -517 (450) */
			0x5b,		/* FC_END */
/* 970 */	
			0x13, 0x0,	/* FC_OP */
/* 972 */	NdrFcShort( 0xfffffefe ),	/* Offset= -258 (714) */
/* 974 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 976 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 978 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 980 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 982 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 984 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 986 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 988 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 990 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 992 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 994 */	
			0x13, 0x0,	/* FC_OP */
/* 996 */	NdrFcShort( 0xfffffdc2 ),	/* Offset= -574 (422) */
/* 998 */	
			0x13, 0x10,	/* FC_OP */
/* 1000 */	NdrFcShort( 0xfffffc76 ),	/* Offset= -906 (94) */
/* 1002 */	
			0x13, 0x10,	/* FC_OP */
/* 1004 */	NdrFcShort( 0xfffffc84 ),	/* Offset= -892 (112) */
/* 1006 */	
			0x13, 0x10,	/* FC_OP */
/* 1008 */	NdrFcShort( 0xfffffdbc ),	/* Offset= -580 (428) */
/* 1010 */	
			0x13, 0x10,	/* FC_OP */
/* 1012 */	NdrFcShort( 0xfffffdca ),	/* Offset= -566 (446) */
/* 1014 */	
			0x13, 0x10,	/* FC_OP */
/* 1016 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1018) */
/* 1018 */	
			0x13, 0x0,	/* FC_OP */
/* 1020 */	NdrFcShort( 0xfffffc04 ),	/* Offset= -1020 (0) */
/* 1022 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1024 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1026 */	0x6,		/* FC_SHORT */
			0x2,		/* FC_CHAR */
/* 1028 */	0x2,		/* FC_CHAR */
			0x38,		/* FC_ALIGNM4 */
/* 1030 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 1032 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1034 */	
			0x13, 0x0,	/* FC_OP */
/* 1036 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (1022) */
/* 1038 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1040 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1042 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1044 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1044) */
/* 1046 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1048 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1050 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1052 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1054 */	NdrFcShort( 0xfffffc78 ),	/* Offset= -904 (150) */
/* 1056 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1058 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1060 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1062 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1064 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1066 */	NdrFcShort( 0xfffffc68 ),	/* Offset= -920 (146) */
/* 1068 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1070 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1072 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1074 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1074) */
/* 1076 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1078 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffc53 ),	/* Offset= -941 (138) */
			0x6,		/* FC_SHORT */
/* 1082 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1084 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffe5 ),	/* Offset= -27 (1058) */
			0x5b,		/* FC_END */
/* 1088 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1090 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1092 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 1094 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1096 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1100 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1102 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (1068) */
/* 1104 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1106 */	
			0x11, 0x0,	/* FC_RP */
/* 1108 */	NdrFcShort( 0x10 ),	/* Offset= 16 (1124) */
/* 1110 */	
			0x12, 0x0,	/* FC_UP */
/* 1112 */	NdrFcShort( 0xffffffb6 ),	/* Offset= -74 (1038) */
/* 1114 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1116 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1118 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1120 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1122 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (1110) */
/* 1124 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1126 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1128 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 1130 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1132 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1136 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1138 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (1114) */
/* 1140 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1142 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 1144 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1146 */	
			0x11, 0x0,	/* FC_RP */
/* 1148 */	NdrFcShort( 0xffffffde ),	/* Offset= -34 (1114) */
/* 1150 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 1152 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1154 */	
			0x11, 0x0,	/* FC_RP */
/* 1156 */	NdrFcShort( 0xfffffc06 ),	/* Offset= -1018 (138) */

			0x0
        }
    };

const CInterfaceProxyVtbl * _DMPluginIfs_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IPluginConfigProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPluginDataProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IPluginDataCallbackProxyVtbl,
    0
};

const CInterfaceStubVtbl * _DMPluginIfs_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IPluginConfigStubVtbl,
    ( CInterfaceStubVtbl *) &_IPluginDataStubVtbl,
    ( CInterfaceStubVtbl *) &_IPluginDataCallbackStubVtbl,
    0
};

PCInterfaceName const _DMPluginIfs_InterfaceNamesList[] = 
{
    "IPluginConfig",
    "IPluginData",
    "IPluginDataCallback",
    0
};


#define _DMPluginIfs_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _DMPluginIfs, pIID, n)

int __stdcall _DMPluginIfs_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _DMPluginIfs, 3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _DMPluginIfs, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _DMPluginIfs, 3, *pIndex )
    
}

const ExtendedProxyFileInfo DMPluginIfs_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _DMPluginIfs_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _DMPluginIfs_StubVtblList,
    (const PCInterfaceName * ) & _DMPluginIfs_InterfaceNamesList,
    0, // no delegation
    & _DMPluginIfs_IID_Lookup, 
    3,
    1,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
