#if !defined(AFX_CHANNELWIZRESULT_H__971FD8EB_F282_4251_9A6A_74FECFA9A0CE__INCLUDED_)
#define AFX_CHANNELWIZRESULT_H__971FD8EB_F282_4251_9A6A_74FECFA9A0CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelWizResult.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChannelWizResult dialog
#include "ChannelCreateInfo.h"
class CChannelWizResult : public CDialog
{
// Construction
public:
	bool m_Filled;
	CChannelWizResult(CWnd* pParent = NULL);   // standard constructor
	CChannelCreateInfo *pInfo;
// Dialog Data
	//{{AFX_DATA(CChannelWizResult)
	enum { IDD = IDD_CHANNELADD_RESULT };
	CString	m_Descr;
	CString	m_Name;
	CString	m_DevMode;
	CString	m_Mode;
	CString	m_PlugCnfg;
	CString	m_PlugName;
	UINT	m_UpPer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChannelWizResult)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChannelWizResult)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELWIZRESULT_H__971FD8EB_F282_4251_9A6A_74FECFA9A0CE__INCLUDED_)
