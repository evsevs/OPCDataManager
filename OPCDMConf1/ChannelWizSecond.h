#if !defined(AFX_CHANNELWIZSECOND_H__DBAACC2F_03FB_4CCC_B83F_7E2573772123__INCLUDED_)
#define AFX_CHANNELWIZSECOND_H__DBAACC2F_03FB_4CCC_B83F_7E2573772123__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelWizSecond.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChannelWizSecond dialog
#include "ChannelCreateInfo.h"
class CChannelWizSecond : public CDialog
{
// Construction
public:
	bool m_Filled;
	CChannelWizSecond(CWnd* pParent = NULL);   // standard constructor
	CChannelCreateInfo *pInfo;
// Dialog Data
	//{{AFX_DATA(CChannelWizSecond)
	enum { IDD = IDD_CHANNELADD_SECOND };
	CSpinButtonCtrl	m_SpinCtrl;
	CString	m_CnfgString;
	UINT	m_UpPer;
	int		m_Mode;
	int		m_DevMode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChannelWizSecond)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChannelWizSecond)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELWIZSECOND_H__DBAACC2F_03FB_4CCC_B83F_7E2573772123__INCLUDED_)
