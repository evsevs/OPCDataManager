/* this ALWAYS GENERATED file contains the proxy stub code */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Mar 13 14:51:17 2002
 */
/* Compiler settings for spacebrowse.idl:
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


#include "spacebrowse.h"

#define TYPE_FORMAT_STRING_SIZE   1357                              
#define PROC_FORMAT_STRING_SIZE   105                               

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


/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ISpaceBrowse, ver. 0.0,
   GUID={0x4913C2D1,0x04A6,0x41a0,{0x82,0x1F,0x3E,0x61,0xD7,0xA5,0x74,0x85}} */


extern const MIDL_STUB_DESC Object_StubDesc;


#pragma code_seg(".orpc")

/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_BrowseAccessPaths_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ LPCWSTR szItemID,
    /* [out][in] */ LPENUMSTRING __RPC_FAR *ppIEnumString)
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
        
        
        
        if(!szItemID)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppIEnumString)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 12U + 0U;
            NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)szItemID,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
            
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)ppIEnumString,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)szItemID,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
            
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)ppIEnumString,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppIEnumString,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[6],
                         ( void __RPC_FAR * )ppIEnumString);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpaceBrowse_BrowseAccessPaths_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LPENUMSTRING __RPC_FAR *ppIEnumString;
    LPCWSTR szItemID;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( LPCWSTR  )szItemID = 0;
    ( LPENUMSTRING __RPC_FAR * )ppIEnumString = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[0] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szItemID,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                       (unsigned char)0 );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&ppIEnumString,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6],
                              (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpaceBrowse*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> BrowseAccessPaths(
                     (ISpaceBrowse *) ((CStdStubBuffer *)This)->pvServerObject,
                     szItemID,
                     ppIEnumString);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppIEnumString,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppIEnumString,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppIEnumString,
                        &__MIDL_TypeFormatString.Format[6] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_GetItemID_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ LPCWSTR szItemDataID,
    /* [out][in] */ LPWSTR __RPC_FAR *szItemID)
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
        
        
        
        if(!szItemDataID)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!szItemID)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 12U + 24U;
            NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)szItemDataID,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
            
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)szItemID,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)szItemDataID,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
            
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)szItemID,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[10] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&szItemID,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[28],
                         ( void __RPC_FAR * )szItemID);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpaceBrowse_GetItemID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    LPCWSTR szItemDataID;
    LPWSTR __RPC_FAR *szItemID;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( LPCWSTR  )szItemDataID = 0;
    ( LPWSTR __RPC_FAR * )szItemID = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[10] );
        
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szItemDataID,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                       (unsigned char)0 );
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&szItemID,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28],
                              (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpaceBrowse*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetItemID(
             (ISpaceBrowse *) ((CStdStubBuffer *)This)->pvServerObject,
             szItemDataID,
             szItemID);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 16U + 10U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)szItemID,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)szItemID,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[28] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)szItemID,
                        &__MIDL_TypeFormatString.Format[28] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_BrowseOPCItemIDs_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ OPCBROWSETYPE dwBrowseFilterType,
    /* [in] */ LPCWSTR szFilterCriteria,
    /* [in] */ VARTYPE vtDataTypeFilter,
    /* [in] */ DWORD dwAccessRightsFilter,
    /* [out][in] */ LPENUMSTRING __RPC_FAR *ppIEnumString)
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
        
        
        
        if(!szFilterCriteria)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppIEnumString)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 2U + 12U + 4U + 10U + 0U;
            NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)szFilterCriteria,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
            
            NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR *)ppIEnumString,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&dwBrowseFilterType,
                         13);
            NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)szFilterCriteria,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
            
            *(( VARTYPE __RPC_FAR * )_StubMsg.Buffer)++ = vtDataTypeFilter;
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = dwAccessRightsFilter;
            
            NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                (unsigned char __RPC_FAR *)ppIEnumString,
                                (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppIEnumString,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[6],
                         ( void __RPC_FAR * )ppIEnumString);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpaceBrowse_BrowseOPCItemIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    DWORD dwAccessRightsFilter;
    OPCBROWSETYPE dwBrowseFilterType;
    LPENUMSTRING __RPC_FAR *ppIEnumString;
    LPCWSTR szFilterCriteria;
    VARTYPE vtDataTypeFilter;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( LPCWSTR  )szFilterCriteria = 0;
    ( LPENUMSTRING __RPC_FAR * )ppIEnumString = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[20] );
        
        NdrSimpleTypeUnmarshall(
                           ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                           ( unsigned char __RPC_FAR * )&dwBrowseFilterType,
                           13);
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szFilterCriteria,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                       (unsigned char)0 );
        
        vtDataTypeFilter = *(( VARTYPE __RPC_FAR * )_StubMsg.Buffer)++;
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwAccessRightsFilter = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR * __RPC_FAR *)&ppIEnumString,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6],
                              (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpaceBrowse*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> BrowseOPCItemIDs(
                    (ISpaceBrowse *) ((CStdStubBuffer *)This)->pvServerObject,
                    dwBrowseFilterType,
                    szFilterCriteria,
                    vtDataTypeFilter,
                    dwAccessRightsFilter,
                    ppIEnumString);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 0U + 4U;
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppIEnumString,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppIEnumString,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[6] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppIEnumString,
                        &__MIDL_TypeFormatString.Format[6] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_ChangeBrowsePosition_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ OPCBROWSEDIRECTION dwBrowseDirection,
    /* [in] */ LPCWSTR szString)
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
        
        
        
        if(!szString)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 2U + 12U;
            NdrConformantStringBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                           (unsigned char __RPC_FAR *)szString,
                                           (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrSimpleTypeMarshall(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( unsigned char __RPC_FAR * )&dwBrowseDirection,
                         13);
            NdrConformantStringMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                         (unsigned char __RPC_FAR *)szString,
                                         (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[36] );
            
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

void __RPC_STUB ISpaceBrowse_ChangeBrowsePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    OPCBROWSEDIRECTION dwBrowseDirection;
    LPCWSTR szString;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( LPCWSTR  )szString = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[36] );
        
        NdrSimpleTypeUnmarshall(
                           ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                           ( unsigned char __RPC_FAR * )&dwBrowseDirection,
                           13);
        NdrConformantStringUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                       (unsigned char __RPC_FAR * __RPC_FAR *)&szString,
                                       (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[4],
                                       (unsigned char)0 );
        
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpaceBrowse*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ChangeBrowsePosition(
                        (ISpaceBrowse *) ((CStdStubBuffer *)This)->pvServerObject,
                        dwBrowseDirection,
                        szString);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U;
        _StubMsg.BufferLength += 16;
        
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


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_QueryAvailableProperties_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ BSTR ItemID,
    /* [out] */ DWORD __RPC_FAR *pdwCount,
    /* [size_is][size_is][out] */ DWORD __RPC_FAR *__RPC_FAR *ppPropertyIDs,
    /* [size_is][size_is][out] */ BSTR __RPC_FAR *__RPC_FAR *ppDescriptions,
    /* [size_is][size_is][out] */ VARTYPE __RPC_FAR *__RPC_FAR *ppvtDataTypes)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ppPropertyIDs)
        {
        *ppPropertyIDs = 0;
        }
    if(ppDescriptions)
        {
        *ppDescriptions = 0;
        }
    if(ppvtDataTypes)
        {
        *ppvtDataTypes = 0;
        }
    RpcTryExcept
        {
        NdrProxyInitialize(
                      ( void __RPC_FAR *  )This,
                      ( PRPC_MESSAGE  )&_RpcMessage,
                      ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                      ( PMIDL_STUB_DESC  )&Object_StubDesc,
                      7);
        
        
        
        if(!pdwCount)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppPropertyIDs)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppDescriptions)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppvtDataTypes)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&ItemID,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[60] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&ItemID,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[60] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[44] );
            
            *pdwCount = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppPropertyIDs,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[74],
                                  (unsigned char)0 );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppDescriptions,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[92],
                                  (unsigned char)0 );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppvtDataTypes,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[132],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[70],
                         ( void __RPC_FAR * )pdwCount);
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[74],
                         ( void __RPC_FAR * )ppPropertyIDs);
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[92],
                         ( void __RPC_FAR * )ppDescriptions);
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[132],
                         ( void __RPC_FAR * )ppvtDataTypes);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpaceBrowse_QueryAvailableProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR ItemID;
    DWORD _M13;
    DWORD __RPC_FAR *_M14;
    BSTR __RPC_FAR *_M15;
    VARTYPE __RPC_FAR *_M16;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_ItemID;
    DWORD __RPC_FAR *pdwCount;
    BSTR __RPC_FAR *__RPC_FAR *ppDescriptions;
    DWORD __RPC_FAR *__RPC_FAR *ppPropertyIDs;
    VARTYPE __RPC_FAR *__RPC_FAR *ppvtDataTypes;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_ItemID = &ItemID;
    MIDL_memset(
               _p_ItemID,
               0,
               sizeof( BSTR  ));
    ( DWORD __RPC_FAR * )pdwCount = 0;
    ( DWORD __RPC_FAR *__RPC_FAR * )ppPropertyIDs = 0;
    ( BSTR __RPC_FAR *__RPC_FAR * )ppDescriptions = 0;
    ( VARTYPE __RPC_FAR *__RPC_FAR * )ppvtDataTypes = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[44] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_ItemID,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[60],
                                  (unsigned char)0 );
        
        pdwCount = &_M13;
        ppPropertyIDs = &_M14;
        _M14 = 0;
        ppDescriptions = &_M15;
        _M15 = 0;
        ppvtDataTypes = &_M16;
        _M16 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpaceBrowse*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> QueryAvailableProperties(
                            (ISpaceBrowse *) ((CStdStubBuffer *)This)->pvServerObject,
                            ItemID,
                            pdwCount,
                            ppPropertyIDs,
                            ppDescriptions,
                            ppvtDataTypes);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 4U + 8U + 14U + 13U + 10U;
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppPropertyIDs,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[74] );
        
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppDescriptions,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[92] );
        
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppvtDataTypes,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[132] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = *pdwCount;
        
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppPropertyIDs,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[74] );
        
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppDescriptions,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[92] );
        
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppvtDataTypes,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[132] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&ItemID,
                            &__MIDL_TypeFormatString.Format[60] );
        
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppPropertyIDs,
                        &__MIDL_TypeFormatString.Format[74] );
        
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppDescriptions,
                        &__MIDL_TypeFormatString.Format[92] );
        
        _StubMsg.MaxCount = pdwCount ? *pdwCount : 0;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppvtDataTypes,
                        &__MIDL_TypeFormatString.Format[132] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_GetItemProperties_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ BSTR ItemID,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ DWORD __RPC_FAR *pdwPropertyIDs,
    /* [size_is][size_is][out] */ VARIANT __RPC_FAR *__RPC_FAR *ppvData,
    /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ppvData)
        {
        *ppvData = 0;
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
                      8);
        
        
        
        if(!pdwPropertyIDs)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppvData)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppErrors)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 8U + 11U + 7U;
            NdrUserMarshalBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR *)&ItemID,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[60] );
            
            _StubMsg.MaxCount = dwCount;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR *)pdwPropertyIDs,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[154] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            NdrUserMarshalMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                    (unsigned char __RPC_FAR *)&ItemID,
                                    (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[60] );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = dwCount;
            
            _StubMsg.MaxCount = dwCount;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char __RPC_FAR *)pdwPropertyIDs,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[154] );
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[66] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppvData,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[164],
                                  (unsigned char)0 );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppErrors,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1146],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[164],
                         ( void __RPC_FAR * )ppvData);
        _StubMsg.MaxCount = dwCount;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1146],
                         ( void __RPC_FAR * )ppErrors);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpaceBrowse_GetItemProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    BSTR ItemID;
    VARIANT __RPC_FAR *_M20;
    HRESULT __RPC_FAR *_M21;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    void __RPC_FAR *_p_ItemID;
    DWORD dwCount;
    DWORD __RPC_FAR *pdwPropertyIDs;
    HRESULT __RPC_FAR *__RPC_FAR *ppErrors;
    VARIANT __RPC_FAR *__RPC_FAR *ppvData;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    _p_ItemID = &ItemID;
    MIDL_memset(
               _p_ItemID,
               0,
               sizeof( BSTR  ));
    ( DWORD __RPC_FAR * )pdwPropertyIDs = 0;
    ( VARIANT __RPC_FAR *__RPC_FAR * )ppvData = 0;
    ( HRESULT __RPC_FAR *__RPC_FAR * )ppErrors = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[66] );
        
        NdrUserMarshalUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&_p_ItemID,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[60],
                                  (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        dwCount = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pdwPropertyIDs,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[154],
                                      (unsigned char)0 );
        
        ppvData = &_M20;
        _M20 = 0;
        ppErrors = &_M21;
        _M21 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpaceBrowse*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> GetItemProperties(
                     (ISpaceBrowse *) ((CStdStubBuffer *)This)->pvServerObject,
                     ItemID,
                     dwCount,
                     pdwPropertyIDs,
                     ppvData,
                     ppErrors);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 14U + 7U;
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppvData,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[164] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppErrors,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1146] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppvData,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[164] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppErrors,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1146] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        NdrUserMarshalFree( &_StubMsg,
                            (unsigned char __RPC_FAR *)&ItemID,
                            &__MIDL_TypeFormatString.Format[60] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppvData,
                        &__MIDL_TypeFormatString.Format[164] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppErrors,
                        &__MIDL_TypeFormatString.Format[1146] );
        
        }
    RpcEndFinally
    _pRpcMessage->BufferLength = 
        (unsigned int)((long)_StubMsg.Buffer - (long)_pRpcMessage->Buffer);
    
}


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_ValidateItem_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ OPCITEMDEF __RPC_FAR *pItemArray,
    /* [in] */ BOOL bBlobUpdate,
    /* [size_is][size_is][out] */ OPCITEMRESULT __RPC_FAR *__RPC_FAR *ppValidationResults,
    /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors)
{

    HRESULT _RetVal;
    
    RPC_MESSAGE _RpcMessage;
    
    MIDL_STUB_MESSAGE _StubMsg;
    
    if(ppValidationResults)
        {
        *ppValidationResults = 0;
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
                      9);
        
        
        
        if(!pItemArray)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppValidationResults)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        if(!ppErrors)
            {
            RpcRaiseException(RPC_X_NULL_REF_POINTER);
            }
        RpcTryFinally
            {
            
            _StubMsg.BufferLength = 4U + 4U + 7U;
            _StubMsg.MaxCount = dwCount;
            
            NdrConformantArrayBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                          (unsigned char __RPC_FAR *)pItemArray,
                                          (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1214] );
            
            NdrProxyGetBuffer(This, &_StubMsg);
            *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++ = dwCount;
            
            _StubMsg.MaxCount = dwCount;
            
            NdrConformantArrayMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                                        (unsigned char __RPC_FAR *)pItemArray,
                                        (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1214] );
            
            _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
            *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++ = bBlobUpdate;
            
            NdrProxySendReceive(This, &_StubMsg);
            
            if ( (_RpcMessage.DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
                NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[86] );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppValidationResults,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1262],
                                  (unsigned char)0 );
            
            NdrPointerUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                  (unsigned char __RPC_FAR * __RPC_FAR *)&ppErrors,
                                  (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1338],
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
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1262],
                         ( void __RPC_FAR * )ppValidationResults);
        _StubMsg.MaxCount = dwCount;
        
        NdrClearOutParameters(
                         ( PMIDL_STUB_MESSAGE  )&_StubMsg,
                         ( PFORMAT_STRING  )&__MIDL_TypeFormatString.Format[1338],
                         ( void __RPC_FAR * )ppErrors);
        _RetVal = NdrProxyErrorHandler(RpcExceptionCode());
        }
    RpcEndExcept
    return _RetVal;
}

void __RPC_STUB ISpaceBrowse_ValidateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase)
{
    OPCITEMRESULT __RPC_FAR *_M25;
    HRESULT __RPC_FAR *_M26;
    HRESULT _RetVal;
    MIDL_STUB_MESSAGE _StubMsg;
    BOOL bBlobUpdate;
    DWORD dwCount;
    OPCITEMDEF __RPC_FAR *pItemArray;
    HRESULT __RPC_FAR *__RPC_FAR *ppErrors;
    OPCITEMRESULT __RPC_FAR *__RPC_FAR *ppValidationResults;
    
NdrStubInitialize(
                     _pRpcMessage,
                     &_StubMsg,
                     &Object_StubDesc,
                     _pRpcChannelBuffer);
    ( OPCITEMDEF __RPC_FAR * )pItemArray = 0;
    ( OPCITEMRESULT __RPC_FAR *__RPC_FAR * )ppValidationResults = 0;
    ( HRESULT __RPC_FAR *__RPC_FAR * )ppErrors = 0;
    RpcTryFinally
        {
        if ( (_pRpcMessage->DataRepresentation & 0X0000FFFFUL) != NDR_LOCAL_DATA_REPRESENTATION )
            NdrConvert( (PMIDL_STUB_MESSAGE) &_StubMsg, (PFORMAT_STRING) &__MIDL_ProcFormatString.Format[86] );
        
        dwCount = *(( DWORD __RPC_FAR * )_StubMsg.Buffer)++;
        
        NdrConformantArrayUnmarshall( (PMIDL_STUB_MESSAGE) &_StubMsg,
                                      (unsigned char __RPC_FAR * __RPC_FAR *)&pItemArray,
                                      (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1214],
                                      (unsigned char)0 );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        bBlobUpdate = *(( BOOL __RPC_FAR * )_StubMsg.Buffer)++;
        
        ppValidationResults = &_M25;
        _M25 = 0;
        ppErrors = &_M26;
        _M26 = 0;
        
        *_pdwStubPhase = STUB_CALL_SERVER;
        _RetVal = (((ISpaceBrowse*) ((CStdStubBuffer *)This)->pvServerObject)->lpVtbl) -> ValidateItem(
                (ISpaceBrowse *) ((CStdStubBuffer *)This)->pvServerObject,
                dwCount,
                pItemArray,
                bBlobUpdate,
                ppValidationResults,
                ppErrors);
        
        *_pdwStubPhase = STUB_MARSHAL;
        
        _StubMsg.BufferLength = 8U + 14U + 7U;
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppValidationResults,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1262] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerBufferSize( (PMIDL_STUB_MESSAGE) &_StubMsg,
                              (unsigned char __RPC_FAR *)ppErrors,
                              (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1338] );
        
        _StubMsg.BufferLength += 16;
        
        NdrStubGetBuffer(This, _pRpcChannelBuffer, &_StubMsg);
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppValidationResults,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1262] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerMarshall( (PMIDL_STUB_MESSAGE)& _StubMsg,
                            (unsigned char __RPC_FAR *)ppErrors,
                            (PFORMAT_STRING) &__MIDL_TypeFormatString.Format[1338] );
        
        _StubMsg.Buffer = (unsigned char __RPC_FAR *)(((long)_StubMsg.Buffer + 3) & ~ 0x3);
        *(( HRESULT __RPC_FAR * )_StubMsg.Buffer)++ = _RetVal;
        
        }
    RpcFinally
        {
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)pItemArray,
                        &__MIDL_TypeFormatString.Format[1154] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppValidationResults,
                        &__MIDL_TypeFormatString.Format[1262] );
        
        _StubMsg.MaxCount = dwCount;
        
        NdrPointerFree( &_StubMsg,
                        (unsigned char __RPC_FAR *)ppErrors,
                        &__MIDL_TypeFormatString.Format[1338] );
        
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

const CINTERFACE_PROXY_VTABLE(10) _ISpaceBrowseProxyVtbl = 
{
    &IID_ISpaceBrowse,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    ISpaceBrowse_BrowseAccessPaths_Proxy ,
    ISpaceBrowse_GetItemID_Proxy ,
    ISpaceBrowse_BrowseOPCItemIDs_Proxy ,
    ISpaceBrowse_ChangeBrowsePosition_Proxy ,
    ISpaceBrowse_QueryAvailableProperties_Proxy ,
    ISpaceBrowse_GetItemProperties_Proxy ,
    ISpaceBrowse_ValidateItem_Proxy
};


static const PRPC_STUB_FUNCTION ISpaceBrowse_table[] =
{
    ISpaceBrowse_BrowseAccessPaths_Stub,
    ISpaceBrowse_GetItemID_Stub,
    ISpaceBrowse_BrowseOPCItemIDs_Stub,
    ISpaceBrowse_ChangeBrowsePosition_Stub,
    ISpaceBrowse_QueryAvailableProperties_Stub,
    ISpaceBrowse_GetItemProperties_Stub,
    ISpaceBrowse_ValidateItem_Stub
};

const CInterfaceStubVtbl _ISpaceBrowseStubVtbl =
{
    &IID_ISpaceBrowse,
    0,
    10,
    &ISpaceBrowse_table[-3],
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
/*  4 */	
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/*  6 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */
/*  8 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 10 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 12 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/* 14 */	
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 16 */	NdrFcShort( 0x1c ),	/* Type Offset=28 */
/* 18 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 20 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 22 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 24 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/* 26 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x6,		/* FC_SHORT */
/* 28 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 30 */	
			0x50,		/* FC_IN_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 32 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */
/* 34 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 36 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0xd,		/* FC_ENUM16 */
/* 38 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 40 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */
/* 42 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 44 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 46 */	NdrFcShort( 0x3c ),	/* Type Offset=60 */
/* 48 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 50 */	NdrFcShort( 0x46 ),	/* Type Offset=70 */
/* 52 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 54 */	NdrFcShort( 0x4a ),	/* Type Offset=74 */
/* 56 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 58 */	NdrFcShort( 0x5c ),	/* Type Offset=92 */
/* 60 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 62 */	NdrFcShort( 0x84 ),	/* Type Offset=132 */
/* 64 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 66 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 68 */	NdrFcShort( 0x3c ),	/* Type Offset=60 */
/* 70 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 72 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 74 */	NdrFcShort( 0x96 ),	/* Type Offset=150 */
/* 76 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 78 */	NdrFcShort( 0xa4 ),	/* Type Offset=164 */
/* 80 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 82 */	NdrFcShort( 0x47a ),	/* Type Offset=1146 */
/* 84 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 86 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 88 */	
			0x4d,		/* FC_IN_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 90 */	NdrFcShort( 0x482 ),	/* Type Offset=1154 */
/* 92 */	0x4e,		/* FC_IN_PARAM_BASETYPE */
			0x8,		/* FC_LONG */
/* 94 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 96 */	NdrFcShort( 0x4ee ),	/* Type Offset=1262 */
/* 98 */	
			0x51,		/* FC_OUT_PARAM */
#ifndef _ALPHA_
			0x1,		/* x86, MIPS & PPC Stack size = 1 */
#else
			0x2,		/* Alpha Stack size = 2 */
#endif
/* 100 */	NdrFcShort( 0x53a ),	/* Type Offset=1338 */
/* 102 */	0x53,		/* FC_RETURN_PARAM_BASETYPE */
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
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/*  4 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x10,	/* FC_RP */
/*  8 */	NdrFcShort( 0x2 ),	/* Offset= 2 (10) */
/* 10 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 12 */	NdrFcLong( 0x101 ),	/* 257 */
/* 16 */	NdrFcShort( 0x0 ),	/* 0 */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 22 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 24 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 26 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 28 */	
			0x11, 0x10,	/* FC_RP */
/* 30 */	NdrFcShort( 0x2 ),	/* Offset= 2 (32) */
/* 32 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 34 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 36 */	
			0x12, 0x0,	/* FC_UP */
/* 38 */	NdrFcShort( 0xc ),	/* Offset= 12 (50) */
/* 40 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 42 */	NdrFcShort( 0x2 ),	/* 2 */
/* 44 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 46 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 48 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 50 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 52 */	NdrFcShort( 0x8 ),	/* 8 */
/* 54 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (40) */
/* 56 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 58 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 60 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0x4 ),	/* 4 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (36) */
/* 70 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 72 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 74 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 76 */	NdrFcShort( 0x2 ),	/* Offset= 2 (78) */
/* 78 */	
			0x13, 0x0,	/* FC_OP */
/* 80 */	NdrFcShort( 0x2 ),	/* Offset= 2 (82) */
/* 82 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 84 */	NdrFcShort( 0x4 ),	/* 4 */
/* 86 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
#ifndef _ALPHA_
/* 88 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 90 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 92 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 94 */	NdrFcShort( 0x2 ),	/* Offset= 2 (96) */
/* 96 */	
			0x13, 0x0,	/* FC_OP */
/* 98 */	NdrFcShort( 0x10 ),	/* Offset= 16 (114) */
/* 100 */	
			0x13, 0x0,	/* FC_OP */
/* 102 */	NdrFcShort( 0xffffffcc ),	/* Offset= -52 (50) */
/* 104 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 106 */	NdrFcShort( 0x0 ),	/* 0 */
/* 108 */	NdrFcShort( 0x4 ),	/* 4 */
/* 110 */	NdrFcShort( 0x0 ),	/* 0 */
/* 112 */	NdrFcShort( 0xfffffff4 ),	/* Offset= -12 (100) */
/* 114 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 116 */	NdrFcShort( 0x0 ),	/* 0 */
/* 118 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
#ifndef _ALPHA_
/* 120 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 122 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 126 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 128 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (104) */
/* 130 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 132 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 134 */	NdrFcShort( 0x2 ),	/* Offset= 2 (136) */
/* 136 */	
			0x13, 0x0,	/* FC_OP */
/* 138 */	NdrFcShort( 0x2 ),	/* Offset= 2 (140) */
/* 140 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 142 */	NdrFcShort( 0x2 ),	/* 2 */
/* 144 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x54,		/* FC_DEREFERENCE */
#ifndef _ALPHA_
/* 146 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 148 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 150 */	
			0x11, 0x0,	/* FC_RP */
/* 152 */	NdrFcShort( 0x2 ),	/* Offset= 2 (154) */
/* 154 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 156 */	NdrFcShort( 0x4 ),	/* 4 */
/* 158 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 160 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 162 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 164 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 166 */	NdrFcShort( 0x2 ),	/* Offset= 2 (168) */
/* 168 */	
			0x13, 0x0,	/* FC_OP */
/* 170 */	NdrFcShort( 0x3be ),	/* Offset= 958 (1128) */
/* 172 */	
			0x13, 0x0,	/* FC_OP */
/* 174 */	NdrFcShort( 0x39c ),	/* Offset= 924 (1098) */
/* 176 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 178 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 180 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 182 */	NdrFcShort( 0x2 ),	/* Offset= 2 (184) */
/* 184 */	NdrFcShort( 0x10 ),	/* 16 */
/* 186 */	NdrFcShort( 0x2b ),	/* 43 */
/* 188 */	NdrFcLong( 0x3 ),	/* 3 */
/* 192 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 194 */	NdrFcLong( 0x11 ),	/* 17 */
/* 198 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 200 */	NdrFcLong( 0x2 ),	/* 2 */
/* 204 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 206 */	NdrFcLong( 0x4 ),	/* 4 */
/* 210 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 212 */	NdrFcLong( 0x5 ),	/* 5 */
/* 216 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 218 */	NdrFcLong( 0xb ),	/* 11 */
/* 222 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 224 */	NdrFcLong( 0xa ),	/* 10 */
/* 228 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 230 */	NdrFcLong( 0x6 ),	/* 6 */
/* 234 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (448) */
/* 236 */	NdrFcLong( 0x7 ),	/* 7 */
/* 240 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 242 */	NdrFcLong( 0x8 ),	/* 8 */
/* 246 */	NdrFcShort( 0xffffff6e ),	/* Offset= -146 (100) */
/* 248 */	NdrFcLong( 0xd ),	/* 13 */
/* 252 */	NdrFcShort( 0xca ),	/* Offset= 202 (454) */
/* 254 */	NdrFcLong( 0x9 ),	/* 9 */
/* 258 */	NdrFcShort( 0xd6 ),	/* Offset= 214 (472) */
/* 260 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 264 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (490) */
/* 266 */	NdrFcLong( 0x24 ),	/* 36 */
/* 270 */	NdrFcShort( 0x2f4 ),	/* Offset= 756 (1026) */
/* 272 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 276 */	NdrFcShort( 0x2ee ),	/* Offset= 750 (1026) */
/* 278 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 282 */	NdrFcShort( 0x2ec ),	/* Offset= 748 (1030) */
/* 284 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 288 */	NdrFcShort( 0x2ea ),	/* Offset= 746 (1034) */
/* 290 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 294 */	NdrFcShort( 0x2e8 ),	/* Offset= 744 (1038) */
/* 296 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 300 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (1042) */
/* 302 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 306 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (1046) */
/* 308 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 312 */	NdrFcShort( 0x2d2 ),	/* Offset= 722 (1034) */
/* 314 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 318 */	NdrFcShort( 0x2d0 ),	/* Offset= 720 (1038) */
/* 320 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 324 */	NdrFcShort( 0x2d6 ),	/* Offset= 726 (1050) */
/* 326 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 330 */	NdrFcShort( 0x2cc ),	/* Offset= 716 (1046) */
/* 332 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 336 */	NdrFcShort( 0x2ce ),	/* Offset= 718 (1054) */
/* 338 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 342 */	NdrFcShort( 0x2cc ),	/* Offset= 716 (1058) */
/* 344 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 348 */	NdrFcShort( 0x2ca ),	/* Offset= 714 (1062) */
/* 350 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 354 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (1066) */
/* 356 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 360 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (1070) */
/* 362 */	NdrFcLong( 0x10 ),	/* 16 */
/* 366 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 368 */	NdrFcLong( 0x12 ),	/* 18 */
/* 372 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 374 */	NdrFcLong( 0x13 ),	/* 19 */
/* 378 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 380 */	NdrFcLong( 0x16 ),	/* 22 */
/* 384 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 386 */	NdrFcLong( 0x17 ),	/* 23 */
/* 390 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 392 */	NdrFcLong( 0xe ),	/* 14 */
/* 396 */	NdrFcShort( 0x2aa ),	/* Offset= 682 (1078) */
/* 398 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 402 */	NdrFcShort( 0x2b0 ),	/* Offset= 688 (1090) */
/* 404 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 408 */	NdrFcShort( 0x2ae ),	/* Offset= 686 (1094) */
/* 410 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 414 */	NdrFcShort( 0x26c ),	/* Offset= 620 (1034) */
/* 416 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 420 */	NdrFcShort( 0x26a ),	/* Offset= 618 (1038) */
/* 422 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 426 */	NdrFcShort( 0x264 ),	/* Offset= 612 (1038) */
/* 428 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 432 */	NdrFcShort( 0x25e ),	/* Offset= 606 (1038) */
/* 434 */	NdrFcLong( 0x0 ),	/* 0 */
/* 438 */	NdrFcShort( 0x0 ),	/* Offset= 0 (438) */
/* 440 */	NdrFcLong( 0x1 ),	/* 1 */
/* 444 */	NdrFcShort( 0x0 ),	/* Offset= 0 (444) */
/* 446 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (445) */
/* 448 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 450 */	NdrFcShort( 0x8 ),	/* 8 */
/* 452 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 454 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 456 */	NdrFcLong( 0x0 ),	/* 0 */
/* 460 */	NdrFcShort( 0x0 ),	/* 0 */
/* 462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 464 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 466 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 468 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 470 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 472 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 474 */	NdrFcLong( 0x20400 ),	/* 132096 */
/* 478 */	NdrFcShort( 0x0 ),	/* 0 */
/* 480 */	NdrFcShort( 0x0 ),	/* 0 */
/* 482 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 484 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 486 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 488 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 490 */	
			0x13, 0x10,	/* FC_OP */
/* 492 */	NdrFcShort( 0x2 ),	/* Offset= 2 (494) */
/* 494 */	
			0x13, 0x0,	/* FC_OP */
/* 496 */	NdrFcShort( 0x200 ),	/* Offset= 512 (1008) */
/* 498 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x49,		/* 73 */
/* 500 */	NdrFcShort( 0x18 ),	/* 24 */
/* 502 */	NdrFcShort( 0xa ),	/* 10 */
/* 504 */	NdrFcLong( 0x8 ),	/* 8 */
/* 508 */	NdrFcShort( 0x58 ),	/* Offset= 88 (596) */
/* 510 */	NdrFcLong( 0xd ),	/* 13 */
/* 514 */	NdrFcShort( 0x78 ),	/* Offset= 120 (634) */
/* 516 */	NdrFcLong( 0x9 ),	/* 9 */
/* 520 */	NdrFcShort( 0x94 ),	/* Offset= 148 (668) */
/* 522 */	NdrFcLong( 0xc ),	/* 12 */
/* 526 */	NdrFcShort( 0xbc ),	/* Offset= 188 (714) */
/* 528 */	NdrFcLong( 0x24 ),	/* 36 */
/* 532 */	NdrFcShort( 0x118 ),	/* Offset= 280 (812) */
/* 534 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 538 */	NdrFcShort( 0x134 ),	/* Offset= 308 (846) */
/* 540 */	NdrFcLong( 0x10 ),	/* 16 */
/* 544 */	NdrFcShort( 0x14c ),	/* Offset= 332 (876) */
/* 546 */	NdrFcLong( 0x2 ),	/* 2 */
/* 550 */	NdrFcShort( 0x164 ),	/* Offset= 356 (906) */
/* 552 */	NdrFcLong( 0x3 ),	/* 3 */
/* 556 */	NdrFcShort( 0x17c ),	/* Offset= 380 (936) */
/* 558 */	NdrFcLong( 0x14 ),	/* 20 */
/* 562 */	NdrFcShort( 0x194 ),	/* Offset= 404 (966) */
/* 564 */	NdrFcShort( 0xffffffff ),	/* Offset= -1 (563) */
/* 566 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 568 */	NdrFcShort( 0x4 ),	/* 4 */
/* 570 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 576 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 578 */	NdrFcShort( 0x4 ),	/* 4 */
/* 580 */	NdrFcShort( 0x0 ),	/* 0 */
/* 582 */	NdrFcShort( 0x1 ),	/* 1 */
/* 584 */	NdrFcShort( 0x0 ),	/* 0 */
/* 586 */	NdrFcShort( 0x0 ),	/* 0 */
/* 588 */	0x13, 0x0,	/* FC_OP */
/* 590 */	NdrFcShort( 0xfffffde4 ),	/* Offset= -540 (50) */
/* 592 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 594 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 596 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 598 */	NdrFcShort( 0x8 ),	/* 8 */
/* 600 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 602 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 604 */	NdrFcShort( 0x4 ),	/* 4 */
/* 606 */	NdrFcShort( 0x4 ),	/* 4 */
/* 608 */	0x11, 0x0,	/* FC_RP */
/* 610 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (566) */
/* 612 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 614 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 616 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 618 */	NdrFcShort( 0x0 ),	/* 0 */
/* 620 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 622 */	NdrFcShort( 0x0 ),	/* 0 */
/* 624 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 628 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 630 */	NdrFcShort( 0xffffff50 ),	/* Offset= -176 (454) */
/* 632 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 634 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 636 */	NdrFcShort( 0x8 ),	/* 8 */
/* 638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 640 */	NdrFcShort( 0x6 ),	/* Offset= 6 (646) */
/* 642 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 644 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 646 */	
			0x11, 0x0,	/* FC_RP */
/* 648 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (616) */
/* 650 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 652 */	NdrFcShort( 0x0 ),	/* 0 */
/* 654 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 658 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 662 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 664 */	NdrFcShort( 0xffffff40 ),	/* Offset= -192 (472) */
/* 666 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 668 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 670 */	NdrFcShort( 0x8 ),	/* 8 */
/* 672 */	NdrFcShort( 0x0 ),	/* 0 */
/* 674 */	NdrFcShort( 0x6 ),	/* Offset= 6 (680) */
/* 676 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 678 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 680 */	
			0x11, 0x0,	/* FC_RP */
/* 682 */	NdrFcShort( 0xffffffe0 ),	/* Offset= -32 (650) */
/* 684 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 686 */	NdrFcShort( 0x4 ),	/* 4 */
/* 688 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 690 */	NdrFcShort( 0x0 ),	/* 0 */
/* 692 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 694 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 696 */	NdrFcShort( 0x4 ),	/* 4 */
/* 698 */	NdrFcShort( 0x0 ),	/* 0 */
/* 700 */	NdrFcShort( 0x1 ),	/* 1 */
/* 702 */	NdrFcShort( 0x0 ),	/* 0 */
/* 704 */	NdrFcShort( 0x0 ),	/* 0 */
/* 706 */	0x13, 0x0,	/* FC_OP */
/* 708 */	NdrFcShort( 0xfffffd3c ),	/* Offset= -708 (0) */
/* 710 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 712 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 714 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 716 */	NdrFcShort( 0x8 ),	/* 8 */
/* 718 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 720 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 722 */	NdrFcShort( 0x4 ),	/* 4 */
/* 724 */	NdrFcShort( 0x4 ),	/* 4 */
/* 726 */	0x11, 0x0,	/* FC_RP */
/* 728 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (684) */
/* 730 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 732 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 734 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 736 */	NdrFcLong( 0x2f ),	/* 47 */
/* 740 */	NdrFcShort( 0x0 ),	/* 0 */
/* 742 */	NdrFcShort( 0x0 ),	/* 0 */
/* 744 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 746 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 748 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 750 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 752 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 754 */	NdrFcShort( 0x1 ),	/* 1 */
/* 756 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 758 */	NdrFcShort( 0x4 ),	/* 4 */
/* 760 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 762 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 764 */	NdrFcShort( 0x10 ),	/* 16 */
/* 766 */	NdrFcShort( 0x0 ),	/* 0 */
/* 768 */	NdrFcShort( 0xa ),	/* Offset= 10 (778) */
/* 770 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 772 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 774 */	NdrFcShort( 0xffffffd8 ),	/* Offset= -40 (734) */
/* 776 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 778 */	
			0x13, 0x0,	/* FC_OP */
/* 780 */	NdrFcShort( 0xffffffe4 ),	/* Offset= -28 (752) */
/* 782 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 784 */	NdrFcShort( 0x4 ),	/* 4 */
/* 786 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 788 */	NdrFcShort( 0x0 ),	/* 0 */
/* 790 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 792 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 794 */	NdrFcShort( 0x4 ),	/* 4 */
/* 796 */	NdrFcShort( 0x0 ),	/* 0 */
/* 798 */	NdrFcShort( 0x1 ),	/* 1 */
/* 800 */	NdrFcShort( 0x0 ),	/* 0 */
/* 802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 804 */	0x13, 0x0,	/* FC_OP */
/* 806 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (762) */
/* 808 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 810 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 812 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 814 */	NdrFcShort( 0x8 ),	/* 8 */
/* 816 */	NdrFcShort( 0x0 ),	/* 0 */
/* 818 */	NdrFcShort( 0x6 ),	/* Offset= 6 (824) */
/* 820 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 822 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 824 */	
			0x11, 0x0,	/* FC_RP */
/* 826 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (782) */
/* 828 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 830 */	NdrFcShort( 0x8 ),	/* 8 */
/* 832 */	0x2,		/* FC_CHAR */
			0x5b,		/* FC_END */
/* 834 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 836 */	NdrFcShort( 0x10 ),	/* 16 */
/* 838 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 840 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 842 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffff1 ),	/* Offset= -15 (828) */
			0x5b,		/* FC_END */
/* 846 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 848 */	NdrFcShort( 0x18 ),	/* 24 */
/* 850 */	NdrFcShort( 0x0 ),	/* 0 */
/* 852 */	NdrFcShort( 0xa ),	/* Offset= 10 (862) */
/* 854 */	0x8,		/* FC_LONG */
			0x36,		/* FC_POINTER */
/* 856 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 858 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (834) */
/* 860 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 862 */	
			0x11, 0x0,	/* FC_RP */
/* 864 */	NdrFcShort( 0xffffff08 ),	/* Offset= -248 (616) */
/* 866 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 868 */	NdrFcShort( 0x1 ),	/* 1 */
/* 870 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 872 */	NdrFcShort( 0x0 ),	/* 0 */
/* 874 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 876 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 878 */	NdrFcShort( 0x8 ),	/* 8 */
/* 880 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 882 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 884 */	NdrFcShort( 0x4 ),	/* 4 */
/* 886 */	NdrFcShort( 0x4 ),	/* 4 */
/* 888 */	0x13, 0x0,	/* FC_OP */
/* 890 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (866) */
/* 892 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 894 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 896 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 898 */	NdrFcShort( 0x2 ),	/* 2 */
/* 900 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 902 */	NdrFcShort( 0x0 ),	/* 0 */
/* 904 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 906 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 908 */	NdrFcShort( 0x8 ),	/* 8 */
/* 910 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 912 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 914 */	NdrFcShort( 0x4 ),	/* 4 */
/* 916 */	NdrFcShort( 0x4 ),	/* 4 */
/* 918 */	0x13, 0x0,	/* FC_OP */
/* 920 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (896) */
/* 922 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 924 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 926 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 928 */	NdrFcShort( 0x4 ),	/* 4 */
/* 930 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 932 */	NdrFcShort( 0x0 ),	/* 0 */
/* 934 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 936 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 938 */	NdrFcShort( 0x8 ),	/* 8 */
/* 940 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 942 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 944 */	NdrFcShort( 0x4 ),	/* 4 */
/* 946 */	NdrFcShort( 0x4 ),	/* 4 */
/* 948 */	0x13, 0x0,	/* FC_OP */
/* 950 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (926) */
/* 952 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 954 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 956 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 958 */	NdrFcShort( 0x8 ),	/* 8 */
/* 960 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 964 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 966 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 968 */	NdrFcShort( 0x8 ),	/* 8 */
/* 970 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 972 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 974 */	NdrFcShort( 0x4 ),	/* 4 */
/* 976 */	NdrFcShort( 0x4 ),	/* 4 */
/* 978 */	0x13, 0x0,	/* FC_OP */
/* 980 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (956) */
/* 982 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 984 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 986 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 988 */	NdrFcShort( 0x8 ),	/* 8 */
/* 990 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 992 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 994 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 996 */	NdrFcShort( 0x8 ),	/* 8 */
/* 998 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 1000 */	NdrFcShort( 0xffd8 ),	/* -40 */
/* 1002 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1004 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (986) */
/* 1006 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1008 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 1010 */	NdrFcShort( 0x28 ),	/* 40 */
/* 1012 */	NdrFcShort( 0xffffffee ),	/* Offset= -18 (994) */
/* 1014 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1014) */
/* 1016 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1018 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 1020 */	0x8,		/* FC_LONG */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1022 */	0x0,		/* 0 */
			NdrFcShort( 0xfffffdf3 ),	/* Offset= -525 (498) */
			0x5b,		/* FC_END */
/* 1026 */	
			0x13, 0x0,	/* FC_OP */
/* 1028 */	NdrFcShort( 0xfffffef6 ),	/* Offset= -266 (762) */
/* 1030 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1032 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 1034 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1036 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 1038 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1040 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 1042 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1044 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 1046 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1048 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 1050 */	
			0x13, 0x0,	/* FC_OP */
/* 1052 */	NdrFcShort( 0xfffffda4 ),	/* Offset= -604 (448) */
/* 1054 */	
			0x13, 0x10,	/* FC_OP */
/* 1056 */	NdrFcShort( 0xfffffc44 ),	/* Offset= -956 (100) */
/* 1058 */	
			0x13, 0x10,	/* FC_OP */
/* 1060 */	NdrFcShort( 0xfffffda2 ),	/* Offset= -606 (454) */
/* 1062 */	
			0x13, 0x10,	/* FC_OP */
/* 1064 */	NdrFcShort( 0xfffffdb0 ),	/* Offset= -592 (472) */
/* 1066 */	
			0x13, 0x10,	/* FC_OP */
/* 1068 */	NdrFcShort( 0xfffffdbe ),	/* Offset= -578 (490) */
/* 1070 */	
			0x13, 0x10,	/* FC_OP */
/* 1072 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1074) */
/* 1074 */	
			0x13, 0x0,	/* FC_OP */
/* 1076 */	NdrFcShort( 0xfffffbcc ),	/* Offset= -1076 (0) */
/* 1078 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 1080 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1082 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 1084 */	0x1,		/* FC_BYTE */
			0x38,		/* FC_ALIGNM4 */
/* 1086 */	0x8,		/* FC_LONG */
			0x39,		/* FC_ALIGNM8 */
/* 1088 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 1090 */	
			0x13, 0x0,	/* FC_OP */
/* 1092 */	NdrFcShort( 0xfffffff2 ),	/* Offset= -14 (1078) */
/* 1094 */	
			0x13, 0x8,	/* FC_OP [simple_pointer] */
/* 1096 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 1098 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 1100 */	NdrFcShort( 0x20 ),	/* 32 */
/* 1102 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1104 */	NdrFcShort( 0x0 ),	/* Offset= 0 (1104) */
/* 1106 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1108 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1110 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1112 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1114 */	NdrFcShort( 0xfffffc56 ),	/* Offset= -938 (176) */
/* 1116 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1118 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 1120 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1122 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1126 */	NdrFcShort( 0xfffffc46 ),	/* Offset= -954 (172) */
/* 1128 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 1130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1132 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 1134 */	NdrFcShort( 0x8 ),	/* x86, MIPS, PPC Stack size/offset = 8 */
#else
			NdrFcShort( 0x10 ),	/* Alpha Stack size/offset = 16 */
#endif
/* 1136 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 1140 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 1142 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (1118) */
/* 1144 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1146 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 1148 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1150) */
/* 1150 */	
			0x13, 0x0,	/* FC_OP */
/* 1152 */	NdrFcShort( 0xfffffc1a ),	/* Offset= -998 (154) */
/* 1154 */	
			0x11, 0x0,	/* FC_RP */
/* 1156 */	NdrFcShort( 0x3a ),	/* Offset= 58 (1214) */
/* 1158 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1160 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1162 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1164 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1166 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1168 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1170 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1172 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1174 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1176 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1178 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1180 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1182 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 1184 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1186 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1188 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1190 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1192 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 1194 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1196 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1198 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1200 */	0x12, 0x0,	/* FC_UP */
/* 1202 */	NdrFcShort( 0xffffffd4 ),	/* Offset= -44 (1158) */
/* 1204 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1206 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1208 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1210 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 1212 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 1214 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1216 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1218 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 1220 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1222 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1224 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 1226 */	NdrFcShort( 0x1c ),	/* 28 */
/* 1228 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1230 */	NdrFcShort( 0x3 ),	/* 3 */
/* 1232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1236 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1238 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 1240 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1242 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1244 */	0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 1246 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 1248 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1250 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1252 */	0x12, 0x0,	/* FC_UP */
/* 1254 */	NdrFcShort( 0xffffffa0 ),	/* Offset= -96 (1158) */
/* 1256 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1258 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffa5 ),	/* Offset= -91 (1168) */
			0x5b,		/* FC_END */
/* 1262 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 1264 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1266) */
/* 1266 */	
			0x13, 0x0,	/* FC_OP */
/* 1268 */	NdrFcShort( 0x26 ),	/* Offset= 38 (1306) */
/* 1270 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 1272 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1274 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 1276 */	NdrFcShort( 0xc ),	/* 12 */
/* 1278 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 1280 */	
			0x16,		/* FC_PSTRUCT */
			0x3,		/* 3 */
/* 1282 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1284 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1286 */	
			0x46,		/* FC_NO_REPEAT */
			0x5c,		/* FC_PAD */
/* 1288 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1290 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1292 */	0x13, 0x0,	/* FC_OP */
/* 1294 */	NdrFcShort( 0xffffffe8 ),	/* Offset= -24 (1270) */
/* 1296 */	
			0x5b,		/* FC_END */

			0x8,		/* FC_LONG */
/* 1298 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 1300 */	0x38,		/* FC_ALIGNM4 */
			0x8,		/* FC_LONG */
/* 1302 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 1304 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 1306 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1308 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1310 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 1312 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1314 */	
			0x4b,		/* FC_PP */
			0x5c,		/* FC_PAD */
/* 1316 */	
			0x48,		/* FC_VARIABLE_REPEAT */
			0x49,		/* FC_FIXED_OFFSET */
/* 1318 */	NdrFcShort( 0x14 ),	/* 20 */
/* 1320 */	NdrFcShort( 0x0 ),	/* 0 */
/* 1322 */	NdrFcShort( 0x1 ),	/* 1 */
/* 1324 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1326 */	NdrFcShort( 0x10 ),	/* 16 */
/* 1328 */	0x13, 0x0,	/* FC_OP */
/* 1330 */	NdrFcShort( 0xffffffc4 ),	/* Offset= -60 (1270) */
/* 1332 */	
			0x5b,		/* FC_END */

			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 1334 */	0x0,		/* 0 */
			NdrFcShort( 0xffffffc9 ),	/* Offset= -55 (1280) */
			0x5b,		/* FC_END */
/* 1338 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] */
/* 1340 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1342) */
/* 1342 */	
			0x13, 0x0,	/* FC_OP */
/* 1344 */	NdrFcShort( 0x2 ),	/* Offset= 2 (1346) */
/* 1346 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 1348 */	NdrFcShort( 0x4 ),	/* 4 */
/* 1350 */	0x29,		/* Corr desc:  parameter, FC_ULONG */
			0x0,		/*  */
#ifndef _ALPHA_
/* 1352 */	NdrFcShort( 0x4 ),	/* x86, MIPS, PPC Stack size/offset = 4 */
#else
			NdrFcShort( 0x8 ),	/* Alpha Stack size/offset = 8 */
#endif
/* 1354 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */

			0x0
        }
    };

const CInterfaceProxyVtbl * _spacebrowse_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ISpaceBrowseProxyVtbl,
    0
};

const CInterfaceStubVtbl * _spacebrowse_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ISpaceBrowseStubVtbl,
    0
};

PCInterfaceName const _spacebrowse_InterfaceNamesList[] = 
{
    "ISpaceBrowse",
    0
};


#define _spacebrowse_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _spacebrowse, pIID, n)

int __stdcall _spacebrowse_IID_Lookup( const IID * pIID, int * pIndex )
{
    
    if(!_spacebrowse_CHECK_IID(0))
        {
        *pIndex = 0;
        return 1;
        }

    return 0;
}

const ExtendedProxyFileInfo spacebrowse_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _spacebrowse_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _spacebrowse_StubVtblList,
    (const PCInterfaceName * ) & _spacebrowse_InterfaceNamesList,
    0, // no delegation
    & _spacebrowse_IID_Lookup, 
    1,
    1,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
