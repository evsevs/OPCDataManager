#if !defined(AFX_CHANNELPROPDLG1_H__9596C4DD_2537_4855_BF1F_626BACCC88F9__INCLUDED_)
#define AFX_CHANNELPROPDLG1_H__9596C4DD_2537_4855_BF1F_626BACCC88F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelPropDlg1.h : header file
//
#include "ChannelInfo.h"
/////////////////////////////////////////////////////////////////////////////
// CChannelPropDlg dialog

class CChannelPropDlg : public CDialog
{
// Construction
public:
	bool m_bEdit;
	CChannelInfo * m_pInfo;
	CChannelPropDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CChannelPropDlg)
	enum { IDD = IDD_CHANNELPROP_DLG };
	CEdit	m_PluginCnfgCtrl;
	CEdit	m_PluginProgIDCtrl;
	CEdit	m_DescrCtrl;
	CSpinButtonCtrl	m_spin;
	CComboBox	m_DUMode;
	CComboBox	m_CMode;
	CString	m_ChannelName;
	CString	m_ChannelDescription;
	CString	m_ChannelConfigString;
	CString	m_ChannelMode;
	CString	m_ChannelDeviceMode;
	UINT	m_ChannelID;
	COleDateTime	m_ChannelDate;
	long	m_ChannelUpdatePeriod;
	CString	m_PluginProgID;
	CString	m_PluginCnfg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChannelPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChannelPropDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELPROPDLG1_H__9596C4DD_2537_4855_BF1F_626BACCC88F9__INCLUDED_)
