#if !defined(AFX_TESTTAGSADD_H__34F7602D_70B4_4CB0_9890_599A577EC8AA__INCLUDED_)
#define AFX_TESTTAGSADD_H__34F7602D_70B4_4CB0_9890_599A577EC8AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestTagsAdd.h : header file
//
#include "ChannelInfo.h"
#include "TestTagsBaseProps.h"
/////////////////////////////////////////////////////////////////////////////
// CTestTagsAdd dialog

class CTestTagsAdd : public CDialog
{
// Construction
public:
	//virtual ~CTestTagsAdd()
	//{
	//	std::list<CTagInfo*>::iterator itl;
	//	for(itl=m_pTagList->
	//}
	bool IsNameInList(CString Name);
	CString m_CurrentPath;
	CImageList * m_iList;
	CString GetPath(HTREEITEM hItem);
	void Disconnect();
	bool m_Connected;
	HRESULT Connect();
	CTestTagsAdd(CWnd* pParent = NULL);   // standard constructor
	CChannelInfo * m_pInfo;
	CComPtr<IPluginConfig> m_pConfig;
	CComPtr<ISpaceBrowse> m_pBrowse;
	std::list<CTagInfo*> *m_pTagList;
// Dialog Data
	//{{AFX_DATA(CTestTagsAdd)
	enum { IDD = IDD_DIALOG_TEST_ADDTAG };
	CTreeCtrl	m_TreeCtrl;
	CListCtrl	m_ListCtrl;
	CString m_Filter;
	UINT	m_Count;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestTagsAdd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	bool FillTree(CString NodeName,HTREEITEM hRoot=TVI_ROOT);
	void FillList(CString Path);
	// Generated message map functions
	//{{AFX_MSG(CTestTagsAdd)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTreeTags(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonUpdatebrowse();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTTAGSADD_H__34F7602D_70B4_4CB0_9890_599A577EC8AA__INCLUDED_)
