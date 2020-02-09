// OPCDMConf1View.h : interface of the COPCDMConf1View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCDMCONF1VIEW_H__120BACF3_75D0_49A9_AC9C_B52E9D84CF34__INCLUDED_)
#define AFX_OPCDMCONF1VIEW_H__120BACF3_75D0_49A9_AC9C_B52E9D84CF34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COPCDMConf1View : public CListView
{
protected: // create from serialization only
	COPCDMConf1View();
	DECLARE_DYNCREATE(COPCDMConf1View)

// Attributes
public:
	COPCDMConf1Doc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COPCDMConf1View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COPCDMConf1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COPCDMConf1View)
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OPCDMConf1View.cpp
inline COPCDMConf1Doc* COPCDMConf1View::GetDocument()
   { return (COPCDMConf1Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPCDMCONF1VIEW_H__120BACF3_75D0_49A9_AC9C_B52E9D84CF34__INCLUDED_)
