// ChannelWizThird.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "ChannelWizThird.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChannelWizThird dialog


CChannelWizThird::CChannelWizThird(CWnd* pParent /*=NULL*/)
	: CDialog(CChannelWizThird::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelWizThird)
	m_ComboIdx = -1;
	//}}AFX_DATA_INIT
	pInfo=NULL;
	m_Filled =false;
}


void CChannelWizThird::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelWizThird)
	DDX_Control(pDX, IDC_COMBO_PLUGIN, m_Combo);
	DDX_CBIndex(pDX, IDC_COMBO_PLUGIN, m_ComboIdx);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChannelWizThird, CDialog)
//{{AFX_MSG_MAP(CChannelWizThird)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChannelWizThird message handlers

BOOL CChannelWizThird::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CChannelWizThird::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow && !m_Filled)
	{
	//	Beep(500,500);
		USES_CONVERSION;
		IEnumString * pES=NULL;
		HRESULT hr=m_pConf->EnumPlugins(&pES);
		if (FAILED(hr)) 

		{
			char ch[10];
			 ltoa(hr,ch,10);
			AfxMessageBox(ch);
			AfxMessageBox("Не могу получить доступные плагины!");
			return ;
		}
		LPOLESTR pName=NULL;
		DWORD Fetched=0;
		int iti=0; 
		pES->Next(1,&pName,&Fetched);
		while(pName)
		{	
			m_Combo.InsertString(iti,W2A(pName));
			CoTaskMemFree(pName);
			pName=NULL;
			pES->Next(1,&pName,&Fetched);
			
			iti++;
		}
		pES->Release();	//здесь заполним вып. список
	}
	
	if (m_Filled&&bShow)//показывать заполненное
	{
		CString Fs = pInfo->m_PluginProgID;
		m_ComboIdx=m_Combo.FindString(-1,Fs);
		UpdateData(false);
	}
	
	if (!bShow)//переход на другую страницу
	{
		UpdateData();
		if (m_ComboIdx!=-1)
			m_Combo.GetLBText(m_ComboIdx,pInfo->m_PluginProgID);
	}	
	m_Filled=true;	
}
