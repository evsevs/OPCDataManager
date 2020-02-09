#if !defined(AFX_CHANNELWIZTHIRD_H__A045ECCA_A8B1_4720_9694_1F03152C3F83__INCLUDED_)
#define AFX_CHANNELWIZTHIRD_H__A045ECCA_A8B1_4720_9694_1F03152C3F83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChannelWizThird.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChannelWizThird dialog
#include "ChannelCreateInfo.h"
class CChannelWizThird : public CDialog
{
// Construction
public:
	bool m_Filled;
	CChannelWizThird(CWnd* pParent = NULL);   // standard constructor
	CComPtr<IMyTestConf> m_pConf;
	CChannelCreateInfo *pInfo;
// Dialog Data
	//{{AFX_DATA(CChannelWizThird)
	enum { IDD = IDD_CHANNELADD_THIRD };
	CComboBox	m_Combo;
	int		m_ComboIdx;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChannelWizThird)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CChannelWizThird)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHANNELWIZTHIRD_H__A045ECCA_A8B1_4720_9694_1F03152C3F83__INCLUDED_)
