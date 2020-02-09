// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__06CB654C_9DD3_449B_93B4_C4AE5A19B0C8__INCLUDED_)
#define AFX_STDAFX_H__06CB654C_9DD3_449B_93B4_C4AE5A19B0C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxcview.h>
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <atlbase.H>
#include <atlconv.h>
#include "..\OPCDMSVC\opcdmsvc_h.h"
#include "spacebrowse.h"
#include "DMPluginIfs.h"
#include <map>
#include <list>
#include <vector>
extern DWORD m_dwPausedGlobal;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__06CB654C_9DD3_449B_93B4_C4AE5A19B0C8__INCLUDED_)
