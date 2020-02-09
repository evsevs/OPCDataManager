// OPCDMConf1.h : main header file for the OPCDMCONF1 application
//

#if !defined(AFX_OPCDMCONF1_H__E479EF4B_8284_406C_A1EA_8CE52DA594FB__INCLUDED_)
#define AFX_OPCDMCONF1_H__E479EF4B_8284_406C_A1EA_8CE52DA594FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COPCDMConf1App:
// See OPCDMConf1.cpp for the implementation of this class
//

class COPCDMConf1App : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	COPCDMConf1App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COPCDMConf1App)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COPCDMConf1App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPCDMCONF1_H__E479EF4B_8284_406C_A1EA_8CE52DA594FB__INCLUDED_)
