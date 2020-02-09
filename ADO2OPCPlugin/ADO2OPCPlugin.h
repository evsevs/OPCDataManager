

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0595 */
/* at Sun Feb 09 21:05:59 2020
 */
/* Compiler settings for ADO2OPCPlugin.idl:
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


#ifndef __ADO2OPCPlugin_h__
#define __ADO2OPCPlugin_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __CADOPlug_FWD_DEFINED__
#define __CADOPlug_FWD_DEFINED__

#ifdef __cplusplus
typedef class CADOPlug CADOPlug;
#else
typedef struct CADOPlug CADOPlug;
#endif /* __cplusplus */

#endif 	/* __CADOPlug_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "DMPluginIfs.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ADO2OPCPLUGINLib_LIBRARY_DEFINED__
#define __ADO2OPCPLUGINLib_LIBRARY_DEFINED__

/* library ADO2OPCPLUGINLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ADO2OPCPLUGINLib;

EXTERN_C const CLSID CLSID_CADOPlug;

#ifdef __cplusplus

class DECLSPEC_UUID("8F413B29-2389-47ba-A8D6-F429E34B28A1")
CADOPlug;
#endif
#endif /* __ADO2OPCPLUGINLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


