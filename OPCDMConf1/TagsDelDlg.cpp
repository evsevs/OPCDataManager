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
	m_Filter="*";//все теги канала
	IUnknown *pUnk=NULL;
	if (FAILED(m_pInfo->m_pChannel->GetBrowser((IUnknown**)&pUnk)))
	{
		AfxMessageBox("Ќе удалось получить интерфейс дл€ просмотра пространства имен канала!!!");
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
		AfxMessageBox("Ќе удалось получить список тегов канала!!!");
		m_pBrowse.Release();
		return TRUE;
	}
	// получили список тегов - теперь нужно его запихать в список диалога

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
	if  (AfxMessageBox("¬ы уверены что хотите удалить выбранные теги?",MB_YESNO|MB_ICONEXCLAMATION)!=IDYES)
		return OnCancel();

	//здесь будет жить непосредственно подготовка к удалению и удаление
	//получим массив идентификаторов дл€ выбранных тегов
	std::vector<DWORD> vHand;
	GetTagsHandlesVector(vHand);
	CComPtr<IChannelTagDef> pTDef;
	if (FAILED(m_pInfo->m_pChannel->QueryInterface(IID_IChannelTagDef,(void**)&pTDef)))
	{
		AfxMessageBox("Ќе могу получить интерфейс дл€ удалени€ тегов!!!");
		OnCancel();
    }
	HRESULT *pErr=NULL;
	HRESULT hr=S_OK;
	if (FAILED(hr=pTDef->DeleteTags(vHand.size(),&vHand[0],&pErr)))
	{
		AfxMessageBox("Ќе удалось удалить теги!!!");
		OnCancel();
	}

	//пройдем повсем тегам и проверим - все ли в пор€дке с ошибками?
	if (hr==S_FALSE)
	{
		for(int i=0; i<vHand.size();i++)
		{
			if (*(pErr+i)!=S_OK)
			{
				char ch[20];
				CString mes="Ќе удалось удалить тег ID=";
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
	//тепепрь по всему массиву
	for (int i=0; i<Count;i++)
	{
		//получить название тега
		CString TName;
		m_TagList.GetText(MyArray[i],TName);
		//получить идентификатор тега
		_bstr_t MyB=TName;
		DWORD pID=5101;//идентификатор свойства
		VARIANT *pPropData=NULL;
		HRESULT *pErr=NULL;
		if (FAILED(m_pBrowse->GetItemProperties(MyB.GetBSTR(),1,&pID,&pPropData,&pErr)))
			continue;//пока надеюсь
		if (pErr!=NULL)
			if (FAILED(*pErr))
			{
				CoTaskMemFree(pErr);
				if (pPropData)
				{
					VariantClear(pPropData);
					CoTaskMemFree(pPropData);
				}
				continue;//пока надеюсь
			}

		//получим идентификатор
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