#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTagPropEditDlg dialog

class CTagPropEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CTagPropEditDlg)

public:
	CTagPropEditDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTagPropEditDlg();

// Dialog Data
	enum { IDD = IDD_TAGPROP_EDIT_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_RealName;
	CEdit m_RealNameCtrl;
	int m_Access;
	UINT m_Type;
	CString m_Description;
	int m_Active;
	int m_NotifyUpdate;
	UINT m_UpsdatePeriod;
	CSpinButtonCtrl m_SpinStrl;
	CString m_FullName;
	afx_msg void OnBnClickedOk();
};
