// TestTagsBaseProps.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "TestTagsBaseProps.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestTagsBaseProps dialog


CTestTagsBaseProps::CTestTagsBaseProps(CWnd* pParent /*=NULL*/)
	: CDialog(CTestTagsBaseProps::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestTagsBaseProps)
	m_TagCount = 0;
	m_Access = -1;
	m_Active = -1;
	m_NotifyUpdate = -1;
	m_Description = _T("");
	m_Name = _T("");
	m_PostName = _T("");
	m_PrefName = _T("");
	m_Type = 0;
	m_UpdsatePeriod = 0;
	m_RealName = _T("");
	//}}AFX_DATA_INIT
}


void CTestTagsBaseProps::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestTagsBaseProps)
	DDX_Control(pDX, IDC_EDIT_RealName, m_RealNameCtrl);
	DDX_Control(pDX, IDC_EDIT_NAME, m_NameCtrl);
	DDX_Control(pDX, IDC_SPIN1, m_SpinStrl);
	DDX_Text(pDX, IDC_EDIT_TAGSCOUNT, m_TagCount);
	DDX_CBIndex(pDX, IDC_COMBO_ACCESS, m_Access);
	DDX_CBIndex(pDX, IDC_COMBO_ACTIVE, m_Active);
	DDX_CBIndex(pDX, IDC_COMBO_NOTIFYUPDATE, m_NotifyUpdate);
	DDX_Text(pDX, IDC_EDIT_DESCR, m_Description);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_POST, m_PostName);
	DDX_Text(pDX, IDC_EDIT_PREF, m_PrefName);
	DDX_Text(pDX, IDC_EDIT_TYPE, m_Type);
	DDX_Text(pDX, IDC_EDIT_UpdatePeriod, m_UpdsatePeriod);
	DDX_Text(pDX, IDC_EDIT_RealName, m_RealName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestTagsBaseProps, CDialog)
	//{{AFX_MSG_MAP(CTestTagsBaseProps)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestTagsBaseProps message handlers

BOOL CTestTagsBaseProps::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_TagCount>1)
		m_NameCtrl.SetReadOnly();
	else if (m_TagCount==0)
		m_RealNameCtrl.SetReadOnly(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
