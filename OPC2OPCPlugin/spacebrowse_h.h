
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Sat Mar 15 02:38:43 2003
 */
/* Compiler settings for \Prj\VC++\OPC\OPCImpl\ForPlugin\spacebrowse.idl:
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

#ifndef __spacebrowse_h_h__
#define __spacebrowse_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
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

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

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
            /* [out][in] */ LPENUMSTRING *ppIEnumString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetItemID( 
            /* [in] */ LPCWSTR szItemDataID,
            /* [out][in] */ LPWSTR *szItemID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BrowseOPCItemIDs( 
            /* [in] */ OPCBROWSETYPE dwBrowseFilterType,
            /* [in] */ LPCWSTR szFilterCriteria,
            /* [in] */ VARTYPE vtDataTypeFilter,
            /* [in] */ DWORD dwAccessRightsFilter,
            /* [out][in] */ LPENUMSTRING *ppIEnumString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ChangeBrowsePosition( 
            /* [in] */ OPCBROWSEDIRECTION dwBrowseDirection,
            /* [in] */ LPCWSTR szString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE QueryAvailableProperties( 
            /* [in] */ BSTR ItemID,
            /* [out] */ DWORD *pdwCount,
            /* [size_is][size_is][out] */ DWORD **ppPropertyIDs,
            /* [size_is][size_is][out] */ BSTR **ppDescriptions,
            /* [size_is][size_is][out] */ VARTYPE **ppvtDataTypes) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetItemProperties( 
            /* [in] */ BSTR ItemID,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ DWORD *pdwPropertyIDs,
            /* [size_is][size_is][out] */ VARIANT **ppvData,
            /* [size_is][size_is][out] */ HRESULT **ppErrors) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ValidateItem( 
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCITEMDEF *pItemArray,
            /* [in] */ BOOL bBlobUpdate,
            /* [size_is][size_is][out] */ OPCITEMRESULT **ppValidationResults,
            /* [size_is][size_is][out] */ HRESULT **ppErrors) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISpaceBrowseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpaceBrowse * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpaceBrowse * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpaceBrowse * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BrowseAccessPaths )( 
            ISpaceBrowse * This,
            /* [in] */ LPCWSTR szItemID,
            /* [out][in] */ LPENUMSTRING *ppIEnumString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetItemID )( 
            ISpaceBrowse * This,
            /* [in] */ LPCWSTR szItemDataID,
            /* [out][in] */ LPWSTR *szItemID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BrowseOPCItemIDs )( 
            ISpaceBrowse * This,
            /* [in] */ OPCBROWSETYPE dwBrowseFilterType,
            /* [in] */ LPCWSTR szFilterCriteria,
            /* [in] */ VARTYPE vtDataTypeFilter,
            /* [in] */ DWORD dwAccessRightsFilter,
            /* [out][in] */ LPENUMSTRING *ppIEnumString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ChangeBrowsePosition )( 
            ISpaceBrowse * This,
            /* [in] */ OPCBROWSEDIRECTION dwBrowseDirection,
            /* [in] */ LPCWSTR szString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QueryAvailableProperties )( 
            ISpaceBrowse * This,
            /* [in] */ BSTR ItemID,
            /* [out] */ DWORD *pdwCount,
            /* [size_is][size_is][out] */ DWORD **ppPropertyIDs,
            /* [size_is][size_is][out] */ BSTR **ppDescriptions,
            /* [size_is][size_is][out] */ VARTYPE **ppvtDataTypes);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetItemProperties )( 
            ISpaceBrowse * This,
            /* [in] */ BSTR ItemID,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ DWORD *pdwPropertyIDs,
            /* [size_is][size_is][out] */ VARIANT **ppvData,
            /* [size_is][size_is][out] */ HRESULT **ppErrors);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ValidateItem )( 
            ISpaceBrowse * This,
            /* [in] */ DWORD dwCount,
            /* [size_is][in] */ OPCITEMDEF *pItemArray,
            /* [in] */ BOOL bBlobUpdate,
            /* [size_is][size_is][out] */ OPCITEMRESULT **ppValidationResults,
            /* [size_is][size_is][out] */ HRESULT **ppErrors);
        
        END_INTERFACE
    } ISpaceBrowseVtbl;

    interface ISpaceBrowse
    {
        CONST_VTBL struct ISpaceBrowseVtbl *lpVtbl;
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
    ISpaceBrowse * This,
    /* [in] */ LPCWSTR szItemID,
    /* [out][in] */ LPENUMSTRING *ppIEnumString);


void __RPC_STUB ISpaceBrowse_BrowseAccessPaths_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_GetItemID_Proxy( 
    ISpaceBrowse * This,
    /* [in] */ LPCWSTR szItemDataID,
    /* [out][in] */ LPWSTR *szItemID);


void __RPC_STUB ISpaceBrowse_GetItemID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_BrowseOPCItemIDs_Proxy( 
    ISpaceBrowse * This,
    /* [in] */ OPCBROWSETYPE dwBrowseFilterType,
    /* [in] */ LPCWSTR szFilterCriteria,
    /* [in] */ VARTYPE vtDataTypeFilter,
    /* [in] */ DWORD dwAccessRightsFilter,
    /* [out][in] */ LPENUMSTRING *ppIEnumString);


void __RPC_STUB ISpaceBrowse_BrowseOPCItemIDs_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_ChangeBrowsePosition_Proxy( 
    ISpaceBrowse * This,
    /* [in] */ OPCBROWSEDIRECTION dwBrowseDirection,
    /* [in] */ LPCWSTR szString);


void __RPC_STUB ISpaceBrowse_ChangeBrowsePosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_QueryAvailableProperties_Proxy( 
    ISpaceBrowse * This,
    /* [in] */ BSTR ItemID,
    /* [out] */ DWORD *pdwCount,
    /* [size_is][size_is][out] */ DWORD **ppPropertyIDs,
    /* [size_is][size_is][out] */ BSTR **ppDescriptions,
    /* [size_is][size_is][out] */ VARTYPE **ppvtDataTypes);


void __RPC_STUB ISpaceBrowse_QueryAvailableProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_GetItemProperties_Proxy( 
    ISpaceBrowse * This,
    /* [in] */ BSTR ItemID,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ DWORD *pdwPropertyIDs,
    /* [size_is][size_is][out] */ VARIANT **ppvData,
    /* [size_is][size_is][out] */ HRESULT **ppErrors);


void __RPC_STUB ISpaceBrowse_GetItemProperties_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring] */ HRESULT STDMETHODCALLTYPE ISpaceBrowse_ValidateItem_Proxy( 
    ISpaceBrowse * This,
    /* [in] */ DWORD dwCount,
    /* [size_is][in] */ OPCITEMDEF *pItemArray,
    /* [in] */ BOOL bBlobUpdate,
    /* [size_is][size_is][out] */ OPCITEMRESULT **ppValidationResults,
    /* [size_is][size_is][out] */ HRESULT **ppErrors);


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


