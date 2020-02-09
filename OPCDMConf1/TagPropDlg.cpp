// TagPropDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "TagPropDlg.h"
#include "TagPropEditDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTagPropDlg dialog


CTagPropDlg::CTagPropDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTagPropDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTagPropDlg)
	m_TagID = 0;
	m_FullTagName = _T("");
	//}}AFX_DATA_INIT
	m_bEdit=false;
}


void CTagPropDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTagPropDlg)
	DDX_Control(pDX, IDC_LIST_TAGPROP, m_TagPropCtrl);
	DDX_Text(pDX, IDC_EDIT_TAGID, m_TagID);
	DDX_Text(pDX, IDC_EDIT_TAGNAME, m_FullTagName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTagPropDlg, CDialog)
	//{{AFX_MSG_MAP(CTagPropDlg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTagPropDlg message handlers

BOOL CTagPropDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(!m_bEdit)//������ ��������
	{
		//�������� ���
		HWND hw;
		CWnd s; //(hw);
		DWORD style;
		CEdit d;
		CComboBox dcb;
		hw=::GetDlgItem(this->m_hWnd,IDC_EDIT_TAGNAME);
		d.Attach(hw);
		d.SetReadOnly();
		d.Detach();

	//	m_TagPropCtrl.S
		
	}
	

	m_TagPropCtrl.SetExtendedStyle(LVS_EX_GRIDLINES );
	m_TagPropCtrl.InsertColumn(0,"�������� ��-��",LVCFMT_LEFT,250);
	m_TagPropCtrl.InsertColumn(1,"��������",LVCFMT_LEFT,280);
	m_FullTagName = m_SelectedItemPath+"."+m_SelectedItemShortName;
	
	FillPropList();
	//m_TagID = 
	UpdateData(false);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTagPropDlg::FillPropList()
{

	ISpaceBrowse *pBrow=NULL;
	IUnknown* pU;
	HRESULT hh=m_pInfo->m_pChannel->GetBrowser(&pU);
	if (SUCCEEDED(hh))
	{
		pU->QueryInterface(IID_ISpaceBrowse,(void**)&pBrow);
		pU->Release();
	}
	
	
	USES_CONVERSION;
	BSTR * pB;
	DWORD * pD;
	DWORD Count;
	VARTYPE *pV;
	HRESULT *pEe;
	VARIANT *pVv;
	BSTR f=A2BSTR(m_FullTagName.GetBuffer(500));
		
	HRESULT hr=pBrow->QueryAvailableProperties(f,&Count,&pD,&pB,&pV);
	
	if (SUCCEEDED(hr))
	{
		hr=pBrow->GetItemProperties(f,Count,pD,&pVv,&pEe);
		if (SUCCEEDED(hr))
		{
		//������� ��� ��������� ��������
		for(int i=0;i<Count;i++)
		{
			_bstr_t x(*(pB+i),false);
			int pos=m_TagPropCtrl.InsertItem(i,(char*)x);
			if (*(pEe+i)!=S_OK)
				continue;
			_variant_t t(*(pVv+i),false);
			if (*(pD+i)==5101)//ID
				m_TagID = (long)t;
				
			char ch[20];
			m_TagPropCtrl.SetItem(i,1,TVIF_TEXT,(char*)(_bstr_t)t,0,0,0,0);
			
		}
		CoTaskMemFree(pVv);
		CoTaskMemFree(pEe);
		}
		CoTaskMemFree(pB);
		CoTaskMemFree(pV);
		CoTaskMemFree(pD);
	}
	SysFreeString(f);
}

void CTagPropDlg::OnBnClickedButton1()
{
	CTagPropEditDlg dlg;
	//����� ��������� ���� ������� �� ����� �������� �������

	//���
	CString s=m_TagPropCtrl.GetItemText(0,1);
	char ch[20];
	dlg.m_Type=atoi(s);
	
	//�����
	s=m_TagPropCtrl.GetItemText(4,1);
	dlg.m_Access=atoi(s);

	//������
	s=m_TagPropCtrl.GetItemText(5,1);
	dlg.m_UpsdatePeriod=atoi(s);

	//��������
	dlg.m_Description=m_TagPropCtrl.GetItemText(6,1);

	//�������� � ����
	dlg.m_RealName=m_TagPropCtrl.GetItemText(7,1);

	//ID

	//����������
	s=m_TagPropCtrl.GetItemText(9,1);
	dlg.m_Active=atoi(s);

	//�����������
	s=m_TagPropCtrl.GetItemText(10,1);
	dlg.m_NotifyUpdate=atoi(s);

	//� ����� ����� �������� � ������ �����
	dlg.m_FullName=this->m_FullTagName.Right(this->m_FullTagName.GetLength()-this->m_FullTagName.FindOneOf(".")-1);
	CString ChannelNameStr=this->m_FullTagName.Left(this->m_FullTagName.FindOneOf("."));
	dlg.DoModal();

	//����� ������� ���������?
	CComPtr<IChannelTagDef> pTagDef;
	if (FAILED(m_pInfo->m_pChannel->QueryInterface(IID_IChannelTagDef,(void**)&pTagDef)))
	{
		AfxMessageBox("�� ������� �������� ��������� ��� ��������� ������� ����!");
		return;
	}
	//������� ������������� 
	char xxx[300];
	OPCHANDLE itemH=0;
	int nchch=299;
	if (::GetDlgItemText(this->m_hWnd,IDC_EDIT_TAGID,&xxx[0],nchch)>0)
	{
		itemH=(OPCHANDLE)atoi(xxx);
	}
	else
	{
		AfxMessageBox("�� ������� �������� ������������� ���� ��� ��������� �������!", MB_ICONEXCLAMATION|MB_OK,0);
		return;
	}

	//������������ ��������� � ����� ������ ��� ���������

	OPCHANDLE oh[1];
	oh[0]=itemH;
	TagDefStruct st[1];
	/*		VARTYPE vtTagType; //��� ������ ����
		DWORD	dwUpdateRateMS;//������ ����������
		BOOL	bNotifyUpdate;//���������� �� �����������
		BOOL	bActive;//���������� ����
		BSTR	bstrTagDescription;
		BSTR	bstrTagName;
		BSTR	bstrRealName;
		DWORD	dwAccessRight;
*/
	st[0].vtTagType=(VARTYPE)dlg.m_Type;
	st[0].dwUpdateRateMS = dlg.m_UpsdatePeriod;
	st[0].bNotifyUpdate = dlg.m_NotifyUpdate ;
	st[0].bActive = dlg.m_Active;
	_bstr_t tdesc= (LPCTSTR)dlg.m_Description;
	_bstr_t tname = (LPCTSTR)dlg.m_FullName;
	_bstr_t trname = (LPCTSTR)dlg.m_RealName ;
	st[0].bstrTagDescription = tdesc.GetBSTR();
	st[0].bstrRealName = trname.GetBSTR();
	st[0].bstrTagName = tname.GetBSTR();
	st[0].dwAccessRight = dlg.m_Access;

	HRESULT *pErr=NULL;
	HRESULT hr=S_OK;
	if (FAILED(hr=pTagDef->ChangeTagsDef(1,oh,st,&pErr)))
	{
		AfxMessageBox("�� ������� �������� �������� ����!", MB_ICONEXCLAMATION|MB_OK,0);
		if (pErr)
			CoTaskMemFree(pErr);
		return;
	}
	else if (hr==S_FALSE) 
	{
		//�������������� ��������� ������ ������
		char strerr[300];
		sprintf(strerr," ����� ��������� ������� ���� ������ ������ � ����� %d. ��������� �� �����������!",*pErr);
		AfxMessageBox(strerr,MB_ICONEXCLAMATION|MB_OK,0);
	}


}
