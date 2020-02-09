// ChannelWizFirst.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "ChannelWizFirst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChannelWizFirst dialog


CChannelWizFirst::CChannelWizFirst(CWnd* pParent /*=NULL*/)
	: CDialog(CChannelWizFirst::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelWizFirst)
	m_Descr = _T("");
	m_Name = _T("");
	//}}AFX_DATA_INIT
	pInfo=NULL;
	m_Filled=false;
}


void CChannelWizFirst::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelWizFirst)
	DDX_Text(pDX, IDC_EDIT_DESCR, m_Descr);
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChannelWizFirst, CDialog)
	//{{AFX_MSG_MAP(CChannelWizFirst)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChannelWizFirst message handlers

void CChannelWizFirst::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	
	if (m_Filled&&bShow)//показывать заполненное
	{
		m_Name = pInfo->m_ChannelName;
		m_Descr = pInfo->m_Description;
		UpdateData(false);
	}

	if (!bShow)//переход на другую страницу
	{
		UpdateData();
		pInfo->m_ChannelName = m_Name;
		pInfo->m_Description = m_Descr;
	}
	m_Filled=true;
}
