// ChannelPropDlg1.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "ChannelPropDlg1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChannelPropDlg dialog


CChannelPropDlg::CChannelPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChannelPropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChannelPropDlg)
	m_ChannelName = _T("");
	m_ChannelDescription = _T("");
	m_ChannelConfigString = _T("");
	m_ChannelMode = _T("");
	m_ChannelDeviceMode = _T("");
	m_ChannelID = 0;
	m_ChannelDate = COleDateTime::GetCurrentTime();
	m_ChannelUpdatePeriod = 0;
	m_PluginProgID = _T("");
	m_PluginCnfg = _T("");
	//}}AFX_DATA_INIT
	m_pInfo=NULL;
	m_bEdit=false;
}


void CChannelPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChannelPropDlg)
	DDX_Control(pDX, IDC_EDIT_PLUGINCNFG, m_PluginCnfgCtrl);
	DDX_Control(pDX, IDC_EDIT_PLUGINPROGID, m_PluginProgIDCtrl);
	DDX_Control(pDX, IDC_EDIT_CHDESCR, m_DescrCtrl);
	DDX_Control(pDX, IDC_SPIN1, m_spin);
	DDX_Control(pDX, IDC_COMBO_CHDEVICEUPDATE, m_DUMode);
	DDX_Control(pDX, IDC_COMBO_CHMODE, m_CMode);
	DDX_Text(pDX, IDC_EDIT_CHNAME, m_ChannelName);
	DDX_Text(pDX, IDC_EDIT_CHDESCR, m_ChannelDescription);
	DDX_Text(pDX, IDC_EDIT_CHCONFIGSTRING, m_ChannelConfigString);
	DDX_CBString(pDX, IDC_COMBO_CHMODE, m_ChannelMode);
	DDX_CBString(pDX, IDC_COMBO_CHDEVICEUPDATE, m_ChannelDeviceMode);
	DDX_Text(pDX, IDC_EDIT_CHID, m_ChannelID);
	DDX_Text(pDX, IDC_EDIT_CHDATE, m_ChannelDate);
	DDX_Text(pDX, IDC_EDIT_CHUPDATEPERIOD, m_ChannelUpdatePeriod);
	DDV_MinMaxLong(pDX, m_ChannelUpdatePeriod, 50, 60000);
	DDX_Text(pDX, IDC_EDIT_PLUGINPROGID, m_PluginProgID);
	DDX_Text(pDX, IDC_EDIT_PLUGINCNFG, m_PluginCnfg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChannelPropDlg, CDialog)
	//{{AFX_MSG_MAP(CChannelPropDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChannelPropDlg message handlers

BOOL CChannelPropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_CMode.ResetContent();
	m_DUMode.ResetContent();
	if(!m_bEdit)//просто просмотр
	{
		//отключим все
		HWND hw;
		CWnd s; //(hw);
		DWORD style;
		CEdit d;
		CComboBox dcb;
		hw=::GetDlgItem(this->m_hWnd,IDC_EDIT_CHNAME);
		d.Attach(hw);
		d.SetReadOnly();
		d.Detach();
		
		hw=::GetDlgItem(this->m_hWnd,IDC_EDIT_CHUPDATEPERIOD);
		d.Attach(hw);
		if (m_dwPausedGlobal)
			d.SetReadOnly();
		d.Detach();

		hw=::GetDlgItem(this->m_hWnd,IDC_EDIT_CHDESCR);
		if (m_dwPausedGlobal)
			::EnableWindow(hw,FALSE);
		
	//	m_DescrCtrl.SetReadOnly();
		hw=::GetDlgItem(this->m_hWnd,IDC_EDIT_CHCONFIGSTRING);
		d.Attach(hw);
		d.SetReadOnly();
		d.Detach();		
		
		if (m_dwPausedGlobal)
			m_spin.EnableWindow(FALSE);
		else
			m_spin.EnableWindow(TRUE);
		m_PluginProgIDCtrl.SetReadOnly();
		m_PluginCnfgCtrl.SetReadOnly();
		//m_DUMode.ShowDropDown(FALSE);
	//	hw=::GetDlgItem(this->m_hWnd,IDC_COMBO_CHMODE);
	//	dcb.Attach(hw);
	//	dcb.ShowDropDown(FALSE);
	//	dcb.Detach();
		//m_CMode.SetDroppedWidth(0);
		//m_CMode.ModifyStyleEx(0,);


	}

	m_spin.SetRange32(50,60000);
	m_spin.SetBase(200);
	if (m_pInfo)
	{
		USES_CONVERSION;
		BSTR bName;
		m_pInfo->m_pChannel->get_ChannelName(&bName);
		m_ChannelName = W2A(bName);
		SysFreeString(bName);

		DWORD cID=0;
		m_pInfo->m_pChannel->get_ChannelID(&cID);
		m_ChannelID = cID;

		m_pInfo->m_pChannel->get_Description(&bName);
		m_ChannelDescription = W2A(bName);
		SysFreeString(bName);
		
		FILETIME ft;
		m_pInfo->m_pChannel->get_CreationTime(&ft);
		m_ChannelDate=ft;
		
		//m_pInfo->m_pChannel->get
		// TODO: Посмотреть, что можно сделать на сегодня.
		m_CMode.AddString("Автозапуск");
		m_ChannelMode = "Автозапуск";

		m_pInfo->m_pChannel->get_ClockRate(&cID);
		m_ChannelUpdatePeriod =cID;

		m_pInfo->m_pChannel->get_PluginProgID(&bName);
		m_PluginProgID = W2A(bName);
		SysFreeString(bName);

		m_pInfo->m_pChannel->get_PluginCnfgString(&bName);
		m_PluginCnfg = W2A(bName);
		SysFreeString(bName);
		

		BOOL b;
//		m_pInfo->m_pChannel->get_DeviceUpdateMode(&b);
		//if (b)
		//{
			m_DUMode.AddString("Авто");
			m_ChannelDeviceMode="Авто";
		//}
		//else
			m_DUMode.AddString("По изм.");
			m_ChannelDeviceMode="По изм.";
		m_pInfo->m_pChannel->get_ConfgStr(&bName);
		m_ChannelConfigString = W2A(bName);
		SysFreeString(bName);
		

		
	}
	UpdateData(false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChannelPropDlg::OnOK() 
{
		UpdateData();
	if (!m_dwPausedGlobal)
	{
		m_pInfo->m_pChannel->put_ClockRate(m_ChannelUpdatePeriod);
        _bstr_t d=(LPCSTR)m_ChannelDescription;
		BSTR s=d.copy();
		m_pInfo->m_pChannel->put_Description(s);
		SysFreeString(s);
	}
	CDialog::OnOK();
}
