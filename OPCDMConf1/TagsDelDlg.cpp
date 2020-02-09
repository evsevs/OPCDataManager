// TagsDelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "TagsDelDlg.h"


// CTagsDelDlg dialog

IMPLEMENT_DYNAMIC(CTagsDelDlg, CDialog)
CTagsDelDlg::CTagsDelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTagsDelDlg::IDD, pParent)
	, m_Filter(_T(""))
{
}

CTagsDelDlg::~CTagsDelDlg()
{
}
BOOL CTagsDelDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_Filter="*";//��� ���� ������
	IUnknown *pUnk=NULL;
	if (FAILED(m_pInfo->m_pChannel->GetBrowser((IUnknown**)&pUnk)))
	{
		AfxMessageBox("�� ������� �������� ��������� ��� ��������� ������������ ���� ������!!!");
		return TRUE;
	}
	pUnk->QueryInterface(IID_ISpaceBrowse,(void**)&m_pBrowse);
	pUnk->Release();
	GenerateTagList();
	UpdateData(FALSE);
	return TRUE;
}
BOOL CTagsDelDlg::GenerateTagList()
{
	m_TagList.ResetContent();
	USES_CONVERSION;
	CComPtr<IEnumString> pEnum;
	if (FAILED(m_pBrowse->BrowseOPCItemIDs(OPC_FLAT,A2W(m_Filter),VT_EMPTY,0,&pEnum)))
	{
		AfxMessageBox("�� ������� �������� ������ ����� ������!!!");
		m_pBrowse.Release();
		return TRUE;
	}
	// �������� ������ ����� - ������ ����� ��� �������� � ������ �������

	LPOLESTR pName=NULL;
	DWORD Fetched=0;
	int iti=0; 
	pEnum->Next(1,&pName,&Fetched);
	while(pName)
	{	
	//	char * pCh = new char[strlen(W2A(pName))+1];
		//strcpy(pCh,);
		m_TagList.AddString(W2A(pName));
		CoTaskMemFree(pName);
		
		pName=NULL;
		pEnum->Next(1,&pName,&Fetched);		
		iti++;
	}
	pEnum.Release();

	return TRUE;
}
void CTagsDelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TAGSFILTER, m_Filter);
	DDX_Control(pDX, IDC_LIST_TAGSFORDEL, m_TagList);
}


BEGIN_MESSAGE_MAP(CTagsDelDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_UPDATEBROWSE, OnBnClickedButtonUpdatebrowse)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CTagsDelDlg message handlers

void CTagsDelDlg::OnBnClickedButtonUpdatebrowse()
{
	UpdateData();
GenerateTagList();
};
void CTagsDelDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if  (AfxMessageBox("�� ������� ��� ������ ������� ��������� ����?",MB_YESNO|MB_ICONEXCLAMATION)!=IDYES)
		return OnCancel();

	//����� ����� ���� ��������������� ���������� � �������� � ��������
	//������� ������ ��������������� ��� ��������� �����
	std::vector<DWORD> vHand;
	GetTagsHandlesVector(vHand);
	CComPtr<IChannelTagDef> pTDef;
	if (FAILED(m_pInfo->m_pChannel->QueryInterface(IID_IChannelTagDef,(void**)&pTDef)))
	{
		AfxMessageBox("�� ���� �������� ��������� ��� �������� �����!!!");
		OnCancel();
    }
	HRESULT *pErr=NULL;
	HRESULT hr=S_OK;
	if (FAILED(hr=pTDef->DeleteTags(vHand.size(),&vHand[0],&pErr)))
	{
		AfxMessageBox("�� ������� ������� ����!!!");
		OnCancel();
	}

	//������� ������ ����� � �������� - ��� �� � ������� � ��������?
	if (hr==S_FALSE)
	{
		for(int i=0; i<vHand.size();i++)
		{
			if (*(pErr+i)!=S_OK)
			{
				char ch[20];
				CString mes="�� ������� ������� ��� ID=";
				mes+=_ltoa(vHand[i],ch,10);
				AfxMessageBox(mes);
			}
		}
	}
	if (pErr)
		CoTaskMemFree(pErr);

	OnOK();
}

long CTagsDelDlg::GetTagsHandlesVector(std::vector<DWORD> &vecHand)
{
	long Count=0;
	int *MyArray=new int[m_TagList.GetCount()];
	Count=m_TagList.GetSelItems(m_TagList.GetCount(),&MyArray[0]);
	//������� �� ����� �������
	for (int i=0; i<Count;i++)
	{
		//�������� �������� ����
		CString TName;
		m_TagList.GetText(MyArray[i],TName);
		//�������� ������������� ����
		_bstr_t MyB=TName;
		DWORD pID=5101;//������������� ��������
		VARIANT *pPropData=NULL;
		HRESULT *pErr=NULL;
		if (FAILED(m_pBrowse->GetItemProperties(MyB.GetBSTR(),1,&pID,&pPropData,&pErr)))
			continue;//���� �������
		if (pErr!=NULL)
			if (FAILED(*pErr))
			{
				CoTaskMemFree(pErr);
				if (pPropData)
				{
					VariantClear(pPropData);
					CoTaskMemFree(pPropData);
				}
				continue;//���� �������
			}

		//������� �������������
		_variant_t t(*pPropData,false);
		vecHand.push_back((long)t);
	//	AfxMessageBox((char*)_bstr_t(t));
		if (pErr)
			CoTaskMemFree(pErr);
        if (pPropData)
			{
				t.Clear();
				CoTaskMemFree(pPropData);
			}

	}
	return Count;
}