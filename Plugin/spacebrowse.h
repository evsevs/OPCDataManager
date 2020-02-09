/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Mar 13 14:51:17 2002
 */
/* Compiler settings for spacebrowse.idl:
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

#ifndef __spacebrowse_h__
#define __spacebrowse_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __ISpaceBrowse_FWD_DEFINED__
#define __ISpaceBrowse_FWD_DEFINED__
typedef interface ISpaceBrowse ISpaceBrowse;
#endif 	/* __ISpaceBrowse_FWD_DEFINED__ */


#ifndef __ISpaceBrowse_FWD_DEFINED__
#define __ISpaceBrowse_FWD_DEFINED__
typedef interface ISpaceBrowse ISpaceBrowse;
#endif 	/* __ISpaceBrowse_FWD_DEFINED__ */


/* header files for imported files */
#include "opccomn.h"
#include "opcda.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __ISpaceBrowse_INTERFACE_DEFINED__
#define __ISpaceBrowse_INTERFACE_DEFINED__

/* interface ISpaceBrowse */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISpaceBrowse;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("4913C2D1-04A6-41a0-821F-3E61D7A57485")
    ISpaceBrowse : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BrowseAccessPaths( 
            /* [in] */ LPCWSTR szItemID,
            /* [out][in] */ LPENUMSTRING __RPC_FAR *ppIEnumString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetItemID( 
            /* [in] */ LPCWSTR szItemDataID,
            /* [out][in] */ LPWSTR __RPC_FAR *szItemID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BrowseOPCItemIDs( 
            /* [in] */ OPCBROWSETYPE dwBrowseFilterType,
            /* [in] */ LPCWSTR szFilterCriteria,
            /* [in] */ VARTYPE vtDataTypeFilter,
            /* [in] */ DWORD dwAccessRightsFilter,
            /* [out][in] */ LPENUMSTRING __RPC_FAR *ppIEnumString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ChangeBrowsePosition( 
            /* [in] */ OPCBROWSEDIRECTION dwBrowseDirection,
            /* [in] */ LPCWSTR szString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE QueryAvailableProperties( 
            /* [in] */ BSTR ItemID,
            /* [out] */ DWORD __RPC_FAR *pdwCount,
            /* [size_is][size_is][out] */ DWORD __RPC_FAR *__RPC_FAR *ppPropertyIDs,
            /* [size_is][size_is][out] */ BSTR __RPC_FAR *__RPC_FAR *ppDescriptions,
            /* [size_is][size_is][out] */ VARTYPE __RPC_FAR *__RPC_FAR *ppvtDataTypes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetItemProperties( 
            /* [in] */ BSTR ItemID,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ DWORD __RPC_FAR *pdwPropertyIDs,
            /* [size_is][size_is][out] */ VARIANT __RPC_FAR *__RPC_FAR *ppvData,
            /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ValidateItem( 
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCITEMDEF __RPC_FAR *pItemArray,
            /* [in] */ BOOL bBlobUpdate,
            /* [size_is][size_is][out] */ OPCITEMRESULT __RPC_FAR *__RPC_FAR *ppValidationResults,
            /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpaceBrowseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            ISpaceBrowse __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            ISpaceBrowse __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            ISpaceBrowse __RPC_FAR * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BrowseAccessPaths )( 
            ISpaceBrowse __RPC_FAR * This,
            /* [in] */ LPCWSTR szItemID,
            /* [out][in] */ LPENUMSTRING __RPC_FAR *ppIEnumString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItemID )( 
            ISpaceBrowse __RPC_FAR * This,
            /* [in] */ LPCWSTR szItemDataID,
            /* [out][in] */ LPWSTR __RPC_FAR *szItemID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *BrowseOPCItemIDs )( 
            ISpaceBrowse __RPC_FAR * This,
            /* [in] */ OPCBROWSETYPE dwBrowseFilterType,
            /* [in] */ LPCWSTR szFilterCriteria,
            /* [in] */ VARTYPE vtDataTypeFilter,
            /* [in] */ DWORD dwAccessRightsFilter,
            /* [out][in] */ LPENUMSTRING __RPC_FAR *ppIEnumString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ChangeBrowsePosition )( 
            ISpaceBrowse __RPC_FAR * This,
            /* [in] */ OPCBROWSEDIRECTION dwBrowseDirection,
            /* [in] */ LPCWSTR szString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryAvailableProperties )( 
            ISpaceBrowse __RPC_FAR * This,
            /* [in] */ BSTR ItemID,
            /* [out] */ DWORD __RPC_FAR *pdwCount,
            /* [size_is][size_is][out] */ DWORD __RPC_FAR *__RPC_FAR *ppPropertyIDs,
            /* [size_is][size_is][out] */ BSTR __RPC_FAR *__RPC_FAR *ppDescriptions,
            /* [size_is][size_is][out] */ VARTYPE __RPC_FAR *__RPC_FAR *ppvtDataTypes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetItemProperties )( 
            ISpaceBrowse __RPC_FAR * This,
            /* [in] */ BSTR ItemID,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ DWORD __RPC_FAR *pdwPropertyIDs,
            /* [size_is][size_is][out] */ VARIANT __RPC_FAR *__RPC_FAR *ppvData,
            /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ValidateItem )( 
            ISpaceBrowse __RPC_FAR * This,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCITEMDEF __RPC_FAR *pItemArray,
            /* [in] */ BOOL bBlobUpdate,
            /* [size_is][size_is][out] */ OPCITEMRESULT __RPC_FAR *__RPC_FAR *ppValidationResults,
            /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors);
        
        END_INTERFACE
    } ISpaceBrowseVtbl;

    interface ISpaceBrowse
    {
        CONST_VTBL struct ISpaceBrowseVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpaceBrowse_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define ISpaceBrowse_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define ISpaceBrowse_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define ISpaceBrowse_BrowseAccessPaths(This,szItemID,ppIEnumString)	\
    (This)->lpVtbl -> BrowseAccessPaths(This,szItemID,ppIEnumString)

#define ISpaceBrowse_GetItemID(This,szItemDataID,szItemID)	\
    (This)->lpVtbl -> GetItemID(This,szItemDataID,szItemID)

#define ISpaceBrowse_BrowseOPCItemIDs(This,dwBrowseFilterType,szFilterCriteria,vtDataTypeFilter,dwAccessRightsFilter,ppIEnumString)	\
    (This)->lpVtbl -> BrowseOPCItemIDs(This,dwBrowseFilterType,szFilterCriteria,vtDataTypeFilter,dwAccessRightsFilter,ppIEnumString)

#define ISpaceBrowse_ChangeBrowsePosition(This,dwBrowseDirection,szString)	\
    (This)->lpVtbl -> ChangeBrowsePosition(This,dwBrowseDirection,szString)

#define ISpaceBrowse_QueryAvailableProperties(This,ItemID,pdwCount,ppPropertyIDs,ppDescriptions,ppvtDataTypes)	\
    (This)->lpVtbl -> QueryAvailableProperties(This,ItemID,pdwCount,ppPropertyIDs,ppDescriptions,ppvtDataTypes)

#define ISpaceBrowse_GetItemProperties(This,ItemID,dwCount,pdwPropertyIDs,ppvData,ppErrors)	\
    (This)->lpVtbl -> GetItemProperties(This,ItemID,dwCount,pdwPropertyIDs,ppvData,ppErrors)

#define ISpaceBrowse_ValidateItem(This,dwCount,pItemArray,bBlobUpdate,ppValidationResults,ppErrors)	\
    (This)->lpVtbl -> ValidateItem(This,dwCount,pItemArray,bBlobUpdate,ppValidationResults,ppErrors)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_BrowseAccessPaths_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ LPCWSTR szItemID,
    /* [out][in] */ LPENUMSTRING __RPC_FAR *ppIEnumString);


void __RPC_STUB ISpaceBrowse_BrowseAccessPaths_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_GetItemID_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ LPCWSTR szItemDataID,
    /* [out][in] */ LPWSTR __RPC_FAR *szItemID);


void __RPC_STUB ISpaceBrowse_GetItemID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_BrowseOPCItemIDs_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ OPCBROWSETYPE dwBrowseFilterType,
    /* [in] */ LPCWSTR szFilterCriteria,
    /* [in] */ VARTYPE vtDataTypeFilter,
    /* [in] */ DWORD dwAccessRightsFilter,
    /* [out][in] */ LPENUMSTRING __RPC_FAR *ppIEnumString);


void __RPC_STUB ISpaceBrowse_BrowseOPCItemIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_ChangeBrowsePosition_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ OPCBROWSEDIRECTION dwBrowseDirection,
    /* [in] */ LPCWSTR szString);


void __RPC_STUB ISpaceBrowse_ChangeBrowsePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_QueryAvailableProperties_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ BSTR ItemID,
    /* [out] */ DWORD __RPC_FAR *pdwCount,
    /* [size_is][size_is][out] */ DWORD __RPC_FAR *__RPC_FAR *ppPropertyIDs,
    /* [size_is][size_is][out] */ BSTR __RPC_FAR *__RPC_FAR *ppDescriptions,
    /* [size_is][size_is][out] */ VARTYPE __RPC_FAR *__RPC_FAR *ppvtDataTypes);


void __RPC_STUB ISpaceBrowse_QueryAvailableProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_GetItemProperties_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ BSTR ItemID,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ DWORD __RPC_FAR *pdwPropertyIDs,
    /* [size_is][size_is][out] */ VARIANT __RPC_FAR *__RPC_FAR *ppvData,
    /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors);


void __RPC_STUB ISpaceBrowse_GetItemProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_ValidateItem_Proxy( 
    ISpaceBrowse __RPC_FAR * This,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ OPCITEMDEF __RPC_FAR *pItemArray,
    /* [in] */ BOOL bBlobUpdate,
    /* [size_is][size_is][out] */ OPCITEMRESULT __RPC_FAR *__RPC_FAR *ppValidationResults,
    /* [size_is][size_is][out] */ HRESULT __RPC_FAR *__RPC_FAR *ppErrors);


void __RPC_STUB ISpaceBrowse_ValidateItem_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __ISpaceBrowse_INTERFACE_DEFINED__ */



#ifndef __SpaceBrowseLib_LIBRARY_DEFINED__
#define __SpaceBrowseLib_LIBRARY_DEFINED__

/* library SpaceBrowseLib */
/* [helpstring][version][uuid] */ 



EXTERN_C const IID LIBID_SpaceBrowseLib;
#endif /* __SpaceBrowseLib_LIBRARY_DEFINED__ */

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
