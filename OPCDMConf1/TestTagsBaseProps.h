#if !defined(AFX_TESTTAGSBASEPROPS_H__E32172EC_51CE_4D22_9524_9F910EC442E1__INCLUDED_)
#define AFX_TESTTAGSBASEPROPS_H__E32172EC_51CE_4D22_9524_9F910EC442E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestTagsBaseProps.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTestTagsBaseProps dialog

class CTestTagsBaseProps : public CDialog
{
// Construction
public:
	CTestTagsBaseProps(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestTagsBaseProps)
	enum { IDD = IDD_DIALOG_TEST_ADDTAGS_BASEPROP };
	CEdit	m_RealNameCtrl;
	CEdit	m_NameCtrl;
	CSpinButtonCtrl	m_SpinStrl;
	UINT	m_TagCount;
	int		m_Access;
	int		m_Active;
	int		m_NotifyUpdate;
	CString	m_Description;
	CString	m_Name;
	CString	m_PostName;
	CString	m_PrefName;
	UINT	m_Type;
	UINT	m_UpdsatePeriod;
	CString	m_RealName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestTagsBaseProps)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestTagsBaseProps)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTTAGSBASEPROPS_H__E32172EC_51CE_4D22_9524_9F910EC442E1__INCLUDED_)
