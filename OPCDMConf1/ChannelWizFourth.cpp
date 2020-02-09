// ChannelWizFourth.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "ChannelWizFourth.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChannelWizFourth dialog


CChannelWizFourth::CChannelWizFourth(CWnd* pParent /*=NULL*/)
	: CDialog(CChannelWizFourth::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelWizFourth)
	m_Example = _T("");
	m_PluginCnfg = _T("");
	//}}AFX_DATA_INIT
	pInfo=NULL;
	m_Filled=false;
}


void CChannelWizFourth::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelWizFourth)
	DDX_Text(pDX, IDC_EDIT_EXAMPLE, m_Example);
	DDX_Text(pDX, IDC_EDIT_PLUGINCNFG, m_PluginCnfg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChannelWizFourth, CDialog)
	//{{AFX_MSG_MAP(CChannelWizFourth)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChannelWizFourth message handlers

void CChannelWizFourth::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	USES_CONVERSION;
	if (bShow )//первый раз показывается
	{
		CLSID clsid;
		BSTR pEx;
		HRESULT hr=CLSIDFromProgID(A2OLE((LPCSTR)pInfo->m_PluginProgID),&clsid);
		CComPtr<IPluginConfig> pPlugConf;
		hr=CoCreateInstance(clsid,0,CLSCTX_ALL,IID_IPluginConfig,(void**)&pPlugConf);
		if (SUCCEEDED(hr))
		{
			if (SUCCEEDED(pPlugConf->GetExampleCnfg(&pEx)))
				m_Example = W2A(pEx);

			SysFreeString(pEx);
		
		}
		pPlugConf.Release();
	}		
	UpdateData(false);
	if (m_Filled&&bShow)//показывать заполненное
	{
		//m_Name = pInfo->m_ChannelName;
		m_PluginCnfg = pInfo->m_PluginCnfg;
		UpdateData(false);
	}
	
	if (!bShow)//переход на другую страницу
	{
		UpdateData();
		pInfo->m_PluginCnfg = m_PluginCnfg;
	}
	m_Filled=true;	
	
}
