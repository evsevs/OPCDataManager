#if !defined(AFX_CHANNELWIZFOURTH_H__AB616D35_D4DE_4E99_B383_0A569378D707__INCLUDED_)
#define AFX_CHANNELWIZFOURTH_H__AB616D35_D4DE_4E99_B383_0A569378D707__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelWizFourth.h : header file
//
#include "ChannelCreateInfo.h"
/////////////////////////////////////////////////////////////////////////////
// CChannelWizFourth dialog

class CChannelWizFourth : public CDialog
{
// Construction
public:
	bool m_Filled;
	CChannelWizFourth(CWnd* pParent = NULL);   // standard constructor
	CChannelCreateInfo *pInfo;
// Dialog Data
	//{{AFX_DATA(CChannelWizFourth)
	enum { IDD = IDD_CHANNELADD_FOURTH };
	CString	m_Example;
	CString	m_PluginCnfg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChannelWizFourth)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChannelWizFourth)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELWIZFOURTH_H__AB616D35_D4DE_4E99_B383_0A569378D707__INCLUDED_)
