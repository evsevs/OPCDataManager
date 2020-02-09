// ChannelWizSecond.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "ChannelWizSecond.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChannelWizSecond dialog


CChannelWizSecond::CChannelWizSecond(CWnd* pParent /*=NULL*/)
	: CDialog(CChannelWizSecond::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelWizSecond)
	m_CnfgString = _T("");
	m_UpPer = 0;
	m_Mode = -1;
	m_DevMode = -1;
	//}}AFX_DATA_INIT
	pInfo=NULL;
	m_Filled=false;
}


void CChannelWizSecond::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelWizSecond)
	DDX_Control(pDX, IDC_SPIN1, m_SpinCtrl);
	DDX_Text(pDX, IDC_EDIT_CNFGSTRING, m_CnfgString);
	DDV_MaxChars(pDX, m_CnfgString, 900);
	DDX_Text(pDX, IDC_EDIT_CHUPDATEPERIOD, m_UpPer);
	DDX_CBIndex(pDX, IDC_COMBO_CHMODE, m_Mode);
	DDX_CBIndex(pDX, IDC_COMBO_CHDEVICEUPDATE, m_DevMode);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChannelWizSecond, CDialog)
	//{{AFX_MSG_MAP(CChannelWizSecond)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChannelWizSecond message handlers

BOOL CChannelWizSecond::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_CnfgString = "—трока конфигурации в данной \r\n";
	m_CnfgString += "реализации не используетс€!";
	m_SpinCtrl.SetRange32(50,60000);
	m_SpinCtrl.SetBase(200);
	m_UpPer=200;
	m_Mode=0;//авто

	m_DevMode = 0;//авто

	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChannelWizSecond::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (m_Filled&&bShow)//показывать заполненное
	{
		m_Mode =pInfo->m_ChannelMode;
		m_DevMode =pInfo->m_DeviceUpdateMode;
		m_UpPer = pInfo->m_ChannelUpdateRate;
		m_CnfgString = pInfo->m_ChannelCnfg;
		UpdateData(false);
	}
	
	if (!bShow)//переход на другую страницу
	{
		UpdateData();
		pInfo->m_ChannelMode=m_Mode;
		pInfo->m_DeviceUpdateMode=m_DevMode;
		pInfo->m_ChannelUpdateRate=m_UpPer;
		pInfo->m_ChannelCnfg=m_CnfgString;
	}
	m_Filled=true;
	
}
