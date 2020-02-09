#if !defined(AFX_CHANNELWIZFIRST_H__6E8CF698_0CA7_49CF_8A8C_22733377F97E__INCLUDED_)
#define AFX_CHANNELWIZFIRST_H__6E8CF698_0CA7_49CF_8A8C_22733377F97E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelWizFirst.h : header file
//
#include "ChannelCreateInfo.h"
/////////////////////////////////////////////////////////////////////////////
// CChannelWizFirst dialog

class CChannelWizFirst : public CDialog
{
// Construction
public:
	bool m_Filled;
	CChannelWizFirst(CWnd* pParent = NULL);   // standard constructor
	CChannelCreateInfo *pInfo;
// Dialog Data
	//{{AFX_DATA(CChannelWizFirst)
	enum { IDD = IDD_CHANNELADD_FIRST };
	CString	m_Descr;
	CString	m_Name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChannelWizFirst)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChannelWizFirst)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELWIZFIRST_H__6E8CF698_0CA7_49CF_8A8C_22733377F97E__INCLUDED_)
