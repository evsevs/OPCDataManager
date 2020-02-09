// RegidtryPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "RegidtryPropDlg.h"


// CRegidtryPropDlg dialog

IMPLEMENT_DYNAMIC(CRegidtryPropDlg, CDialog)
CRegidtryPropDlg::CRegidtryPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegidtryPropDlg::IDD, pParent)
	, m_EditConfXML(_T(""))
	, m_EditLogPath(_T(""))
{
}

CRegidtryPropDlg::~CRegidtryPropDlg()
{
}

void CRegidtryPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CONF_FILE, m_EditConfXML);
	DDX_Text(pDX, IDC_EDIT_LOGPATH, m_EditLogPath);
}


BEGIN_MESSAGE_MAP(CRegidtryPropDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CRegidtryPropDlg message handlers

void CRegidtryPropDlg::OnBnClickedOk()
{
	UpdateData();
	//�������� ���
	rk.SetStringValue("XMLConfFile",m_EditConfXML);
	rk.SetStringValue("LogPath",m_EditLogPath);

	AfxMessageBox("��� ����, ����� ��������� �������� � ���� ���������\n������������� OPCDM (��� ������������� ������ OPC DM)!",MB_OK|MB_ICONASTERISK,0);
	OnOK();
}
BOOL CRegidtryPropDlg::OnInitDialog()
{
	//��������� ��������� �� �������
	
	//������� ���� �������
	if (ERROR_SUCCESS==rk.Open(HKEY_LOCAL_MACHINE,"SOFTWARE\\CAPCS\\OPCDM\\OPCDMSvc"))
	{
		//���������������� ����
		char x[500];
		DWORD nch=499;
		rk.QueryStringValue("XMLConfFile",&x[0],&nch);
		this->m_EditConfXML = x;

		//���������������� ����
		nch=499;
		rk.QueryStringValue("LogPath",&x[0],&nch);
		this->m_EditLogPath  = x;
	}
		UpdateData(FALSE);
		
	return TRUE;
}
