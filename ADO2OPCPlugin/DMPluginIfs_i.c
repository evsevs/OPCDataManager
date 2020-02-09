/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Apr 01 15:56:21 2002
 */
/* Compiler settings for D:\Prj\VC++\OPC\OPCImpl\ForPlugin\DMPluginIfs.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_IPluginConfig = {0xEE33DD30,0x74D9,0x11d5,{0x9C,0xB4,0x00,0x40,0x05,0xA3,0x07,0x0A}};


const IID IID_IPluginData = {0xEE33DD31,0x74D9,0x11d5,{0x9C,0xB4,0x00,0x40,0x05,0xA3,0x07,0x0A}};


const IID IID_IPluginDataCallback = {0xE9A79355,0x7442,0x11D5,{0x9C,0xB4,0x00,0x40,0x05,0xA3,0x07,0x0A}};


#ifdef __cplusplus
}
#endif

