#if !defined(AFX_NETBUTTON_H__7B694CB6_AEDC_11D1_8BF5_0000B43382FE__INCLUDED_)
#define AFX_NETBUTTON_H__7B694CB6_AEDC_11D1_8BF5_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// NetButton.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNetButton window

class CNetButton : public CButton
{
// Construction
public:
	CNetButton();
	COLORREF	crBack1, crBack2, crText;
	CFont		ftFont, * pFont;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNetButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNetButton)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETBUTTON_H__7B694CB6_AEDC_11D1_8BF5_0000B43382FE__INCLUDED_)
