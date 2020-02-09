#if !defined(AFX_WIZARDDLG_H__7B694CB1_AEDC_11D1_8BF5_0000B43382FE__INCLUDED_)
#define AFX_WIZARDDLG_H__7B694CB1_AEDC_11D1_8BF5_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// WizardDlg.h : header file
//
#include <afxcoll.h>
#include "NetButton.h"

/////////////////////////////////////////////////////////////////////////////
// CWizardDlg dialog

class CWizardDlg : public CDialog
{
// Construction
public:
	CDialog * GetDialog(const int idx);
	void ClosePages();
	virtual void SetCurSel(const int idx);
	void AddPage(const char * cText, CDialog * pDlg, const UINT id);
	CWizardDlg(CWnd* pParent = NULL);   // standard constructor
	CPtrArray pPages;
	CStringArray csText;
	CUIntArray csIds;
	virtual ~CWizardDlg();
	int	iCurIdx;
	CString csTitle;
	CComPtr<IMyTestConf> m_pConf;
// Dialog Data
	//{{AFX_DATA(CWizardDlg)
	enum { IDD = IDD_WIZARDBASE };
	CStatic	wndPicture;
	CStatic	wndFrame;
	CNetButton	wndTitle;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizardDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWizardDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnBack();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZARDDLG_H__7B694CB1_AEDC_11D1_8BF5_0000B43382FE__INCLUDED_)
