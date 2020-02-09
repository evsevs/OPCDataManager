// ChannelWizResult.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "ChannelWizResult.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChannelWizResult dialog


CChannelWizResult::CChannelWizResult(CWnd* pParent /*=NULL*/)
	: CDialog(CChannelWizResult::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelWizResult)
	m_Descr = _T("");
	m_Name = _T("");
	m_DevMode = _T("");
	m_Mode = _T("");
	m_PlugCnfg = _T("");
	m_PlugName = _T("");
	m_UpPer = 0;
	//}}AFX_DATA_INIT
	pInfo=NULL;
}


void CChannelWizResult::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelWizResult)
	DDX_Text(pDX, IDC_EDIT_CHDESCR, m_Descr);
	DDX_Text(pDX, IDC_EDIT_CHNAME, m_Name);
	DDX_Text(pDX, IDC_EDIT_CHDUMODE, m_DevMode);
	DDX_Text(pDX, IDC_EDIT_CHMODE, m_Mode);
	DDX_Text(pDX, IDC_EDIT_PLUGINCNFG, m_PlugCnfg);
	DDX_Text(pDX, IDC_EDIT_PLUGINNAME, m_PlugName);
	DDX_Text(pDX, IDC_EDIT_CHUPDATEPERIOD, m_UpPer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChannelWizResult, CDialog)
	//{{AFX_MSG_MAP(CChannelWizResult)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChannelWizResult message handlers

void CChannelWizResult::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow)
	{
		m_Name=pInfo->m_ChannelName;
		m_Descr=pInfo->m_Description;
		if (pInfo->m_DeviceUpdateMode==0)// TODO: Посмотреть на соответствие реальности
			m_DevMode = "Авто";
		else
			m_DevMode = "По изм.";
	
		if (pInfo->m_ChannelMode==0)
			m_Mode = "Автомат";
		else 
			m_Mode = "XYZ";
		m_UpPer =pInfo->m_ChannelUpdateRate; 
		m_PlugName = pInfo->m_PluginProgID;
		m_PlugCnfg = pInfo->m_PluginCnfg;
		UpdateData(FALSE);
	}
	
}
