// TagPropEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "TagPropEditDlg.h"


// CTagPropEditDlg dialog

IMPLEMENT_DYNAMIC(CTagPropEditDlg, CDialog)
CTagPropEditDlg::CTagPropEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTagPropEditDlg::IDD, pParent)
	, m_RealName(_T(""))
	, m_Access(0)
	, m_Type(0)
	, m_Description(_T(""))
	, m_Active(0)
	, m_NotifyUpdate(0)
	, m_UpsdatePeriod(0)
	, m_FullName(_T(""))
{
}

CTagPropEditDlg::~CTagPropEditDlg()
{
}

void CTagPropEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_RealName, m_RealName);
	DDX_Control(pDX, IDC_EDIT_RealName, m_RealNameCtrl);
	DDX_CBIndex(pDX, IDC_COMBO_ACCESS, m_Access);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_Type);
	DDX_Text(pDX, IDC_EDIT_DESCR, m_Description);
	DDX_CBIndex(pDX, IDC_COMBO_ACTIVE, m_Active);
	DDX_CBIndex(pDX, IDC_COMBO_NOTIFYUPDATE, m_NotifyUpdate);
	DDX_Text(pDX, IDC_EDIT_UpdatePeriod, m_UpsdatePeriod);
	DDX_Control(pDX, IDC_SPIN1, m_SpinStrl);
	DDX_Text(pDX, IDC_EDIT_TAGNAME, m_FullName);
}


BEGIN_MESSAGE_MAP(CTagPropEditDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CTagPropEditDlg message handlers

void CTagPropEditDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}
