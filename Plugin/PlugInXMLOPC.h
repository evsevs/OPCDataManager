

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Sun Feb 09 22:09:20 2020
 */
/* Compiler settings for PlugInXMLOPC.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0595 
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


#ifndef __PlugInXMLOPC_h__
#define __PlugInXMLOPC_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __XMLPlugin_FWD_DEFINED__
#define __XMLPlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class XMLPlugin XMLPlugin;
#else
typedef struct XMLPlugin XMLPlugin;
#endif /* __cplusplus */

#endif 	/* __XMLPlugin_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "DMPluginIfs.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __PLUGINXMLOPCLib_LIBRARY_DEFINED__
#define __PLUGINXMLOPCLib_LIBRARY_DEFINED__

/* library PLUGINXMLOPCLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_PLUGINXMLOPCLib;

EXTERN_C const CLSID CLSID_XMLPlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("E9A79354-7442-11D5-9CB4-004005A3070A")
XMLPlugin;
#endif
#endif /* __PLUGINXMLOPCLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


