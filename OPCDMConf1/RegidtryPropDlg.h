#pragma once


// CRegidtryPropDlg dialog

class CRegidtryPropDlg : public CDialog
{
	DECLARE_DYNAMIC(CRegidtryPropDlg)

public:
	CRegidtryPropDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRegidtryPropDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_EDIT_REGISTRY_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CRegKey rk;
	CString m_EditConfXML;
	CString m_EditLogPath;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
