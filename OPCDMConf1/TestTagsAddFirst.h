#if !defined(AFX_TESTTAGSADDFIRST_H__1B93CDF4_88C9_4CBA_AE3F_AEFBB21E0EB7__INCLUDED_)
#define AFX_TESTTAGSADDFIRST_H__1B93CDF4_88C9_4CBA_AE3F_AEFBB21E0EB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestTagsAddFirst.h : header file
//
#include "ChannelInfo.h"
#include "TestTagsAdd.h"
/////////////////////////////////////////////////////////////////////////////
// CTestTagsAddFirst dialog

class CTestTagsAddFirst : public CDialog
{
// Construction
public:
	virtual ~CTestTagsAddFirst()
	{
		std::list<CTagInfo*>::iterator itl;
		for(itl=m_TagList.begin();itl!=m_TagList.end();++itl)
		{
			CTagInfo* pT=*itl;
			delete pT;
		}
	}
	CString m_SelectedItemPath;
	void FillList();
	CChannelInfo * m_pInfo;
	CImageList *m_iList;
	std::list<CTagInfo*> m_TagList;
	CTestTagsAddFirst(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTestTagsAddFirst)
	enum { IDD = IDD_TAGADD_FIRST };
	CListCtrl	m_ListCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestTagsAddFirst)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTestTagsAddFirst)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonAddhand();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTTAGSADDFIRST_H__1B93CDF4_88C9_4CBA_AE3F_AEFBB21E0EB7__INCLUDED_)
