#if !defined(AFX_TAGPROPDLG_H__3F14644E_1852_4ADA_8593_F75DABFAD6DD__INCLUDED_)
#define AFX_TAGPROPDLG_H__3F14644E_1852_4ADA_8593_F75DABFAD6DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TagPropDlg.h : header file
//
#include "ChannelInfo.h"
/////////////////////////////////////////////////////////////////////////////
// CTagPropDlg dialog

class CTagPropDlg : public CDialog
{
// Construction
public:
	bool m_bEdit;
	void FillPropList();
	CString m_SelectedItemShortName;
	CString m_SelectedItemPath;
	CChannelInfo * m_pInfo;
	CTagPropDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTagPropDlg)
	enum { IDD = IDD_TAGPROP_DLG };
	CListCtrl	m_TagPropCtrl;
	UINT	m_TagID;
	CString	m_FullTagName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTagPropDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTagPropDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TAGPROPDLG_H__3F14644E_1852_4ADA_8593_F75DABFAD6DD__INCLUDED_)
