// TestTagsAdd.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "TestTagsAdd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestTagsAdd dialog


CTestTagsAdd::CTestTagsAdd(CWnd* pParent /*=NULL*/)
	: CDialog(CTestTagsAdd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestTagsAdd)
	m_Count = 0;
	m_Filter = "*";
	//}}AFX_DATA_INIT
	m_Connected=false;
}


void CTestTagsAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestTagsAdd)
	DDX_Control(pDX, IDC_TREE_TAGS, m_TreeCtrl);
	DDX_Control(pDX, IDC_LIST_TAGS, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT1, m_Count);
	DDX_Text(pDX, IDC_EDIT_TAGSFILTER, m_Filter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestTagsAdd, CDialog)
	//{{AFX_MSG_MAP(CTestTagsAdd)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_TAGS, OnSelchangedTreeTags)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_UPDATEBROWSE, OnBnClickedButtonUpdatebrowse)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestTagsAdd message handlers

BOOL CTestTagsAdd::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_ListCtrl.InsertColumn(0,"Название",LVCFMT_LEFT,80);
	m_ListCtrl.InsertColumn(1,"Полное название",LVCFMT_LEFT,150);
	LONG ST=GetWindowLong(m_TreeCtrl.m_hWnd,GWL_STYLE);
	SetWindowLong(m_TreeCtrl.m_hWnd,GWL_STYLE,ST|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT|TVS_SHOWSELALWAYS);
	//TC.ModifyStyle(TVS_EDITLABELS,0,0);
	//GetTreeCtrl().SetImageList(&GetDocument()->m_imlistSmall, TVSIL_NORMAL);
	m_TreeCtrl.SetImageList(m_iList,TVSIL_NORMAL);
	m_ListCtrl.SetImageList(m_iList,LVSIL_SMALL);
	//добавить заполнение дерева
//	Connect();
	FillTree("");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

bool CTestTagsAdd::FillTree(CString NodeName,HTREEITEM hRoot)
{
//заполним дерево
	if (FAILED(Connect())) return 0;

	USES_CONVERSION;
	HRESULT hr=S_OK;
	if (NodeName!="")
	{
		hr=m_pBrowse->ChangeBrowsePosition(OPC_BROWSE_DOWN,A2W((LPCSTR)NodeName));

	}

	
	if (FAILED(hr)) return 0;
	
	CComPtr<IEnumString> pEB;
	hr=m_pBrowse->BrowseOPCItemIDs(OPC_BRANCH,A2W(""),0,0,&pEB);
	if (FAILED(hr)) 
	{//восстановим состояние browser'a
		m_pBrowse->ChangeBrowsePosition(OPC_BROWSE_UP,A2W(""));
		return 0;
	}
	LPOLESTR pName=NULL;
	DWORD Fetched=0;
	
	
	pEB->Next(1,&pName,&Fetched);

	while(pName)
	{	
		DWORD dwcChildren=0;
		char * pCh = new char[strlen(W2A(pName))+1];
		strcpy(pCh,W2A(pName));
				
		HTREEITEM ii=m_TreeCtrl.InsertItem(pCh,2,2,hRoot);
		FillTree(pCh,ii);
		delete[] pCh;
		CoTaskMemFree(pName);
		pName=NULL;
		pEB->Next(1,&pName,&Fetched);		
	}
	
	pEB.Release();
	m_pBrowse->ChangeBrowsePosition(OPC_BROWSE_UP,A2W(""));	
	return 1;
}

HRESULT CTestTagsAdd::Connect()
{
	if (m_Connected) return S_OK;
	USES_CONVERSION;
	CLSID cl;
	_bstr_t t="",tcfg="";
	BSTR f,cfg;
	m_pInfo->m_pChannel->get_PluginProgID(&f);
	t.Assign(f);
	m_pInfo->m_pChannel->get_PluginCnfgString(&cfg);
	tcfg.Assign(cfg);
	
	HRESULT hr=CLSIDFromProgID(A2W((char*)t),&cl);
	
	if (FAILED(hr)) return hr;
	
	hr = CoCreateInstance(cl,0,CLSCTX_ALL,IID_IPluginConfig,(void**)&m_pConfig);
	
	IUnknown * pUnk;
	if ((hr=m_pConfig->GetBrowser(&pUnk))==S_FALSE)
	{
		hr=m_pConfig->Configure(cfg);
		if (SUCCEEDED(hr))
			hr=m_pConfig->GetBrowser(&pUnk);
		else
			AfxMessageBox("Не могу сконфигурировать плагин с установленной строкой конфигурации!");
	}
	if (SUCCEEDED(hr))
		hr=pUnk->QueryInterface(IID_ISpaceBrowse,(void**)&m_pBrowse);
	
	if (FAILED(hr))
	{
		m_pConfig.Release();
		return hr;
	}

	m_Connected=true;

	return S_OK;
}

void CTestTagsAdd::Disconnect()
{
	if (!m_Connected)
		return ;
	m_pConfig.Release();
}


CString CTestTagsAdd::GetPath(HTREEITEM hItem)
{

//поиск пути
HTREEITEM hParent=hItem;
CString Path;
CString Path1=m_TreeCtrl.GetItemText(hItem);
while ((hParent=m_TreeCtrl.GetParentItem(hParent))!=NULL)
{
	Path=Path1;//для удаления имени канала (не нужно)
	Path1=m_TreeCtrl.GetItemText(hParent)+"."+Path1;
}
 return Path1;

}

void CTestTagsAdd::OnSelchangedTreeTags(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CString path =GetPath(pNMTreeView->itemNew.hItem);
	m_CurrentPath=path;
	FillList(path);
	*pResult = 0;
}

void CTestTagsAdd::FillList(CString Path)
{
	//заполним дерево
	UpdateData();
	USES_CONVERSION;
	HRESULT hr=S_OK;
	if (Path!="")
	{
		hr=m_pBrowse->ChangeBrowsePosition(OPC_BROWSE_TO,A2W((LPCSTR)Path));
		
	}
	
	m_ListCtrl.DeleteAllItems();
	if (FAILED(hr)) return;
	
	CComPtr<IEnumString> pEB;
	hr=m_pBrowse->BrowseOPCItemIDs(OPC_LEAF,A2W((LPCSTR)m_Filter),0,0,&pEB);
	if (FAILED(hr)) 
	{//восстановим состояние browser'a
		m_pBrowse->ChangeBrowsePosition(OPC_BROWSE_TO,A2W(""));
		return;
	}
	LPOLESTR pName=NULL;
	DWORD Fetched=0;
	
	
		pEB->Next(1,&pName,&Fetched);
	
	  while(pName)
	  {	
	  DWORD dwcChildren=0;
	  char * pCh = new char[strlen(W2A(pName))+1];
	  strcpy(pCh,W2A(pName));
	  LPWSTR pFullName;
	  int df;
	  df=m_ListCtrl.InsertItem(LVIF_TEXT|LVIF_IMAGE,0,pCh,0,0,1,0);
	  
		m_pBrowse->GetItemID(pName,&pFullName);
		m_ListCtrl.SetItem(df,1,LVIF_TEXT,W2A(pFullName),0,0,0,0);
		CoTaskMemFree(pName);
		CoTaskMemFree(pFullName);
		//FillTree(pCh,ii);
		delete[] pCh;
		
		  pName=NULL;
		  pEB->Next(1,&pName,&Fetched);		
		  }
	
	
/*	LPOLESTR * pName = (LPOLESTR*)CoTaskMemAlloc(sizeof(LPOLESTR)*100);
	pEB->Next(100,pName,&Fetched);
	
	while(Fetched)
	{	
/*		DWORD dwcChildren=0;
		char * pCh = new char[strlen(W2A(pName))+1];
		strcpy(pCh,W2A(pName));
*/
/*		for(int ini=0;ini<Fetched;ini++)
		{
		LPWSTR pFullName;
		int df;
		df=m_ListCtrl.InsertItem(LVIF_TEXT|LVIF_IMAGE,0,W2A(*(pName+ini)),0,0,1,0);
		
		m_pBrowse->GetItemID(*(pName+ini),&pFullName);
		m_ListCtrl.SetItem(df,1,LVIF_TEXT,W2A(pFullName),0,0,0,0);
		CoTaskMemFree(*(pName+ini));
		CoTaskMemFree(pFullName);
		//FillTree(pCh,ii);
//		delete[] pCh;
		}
		CoTaskMemFree(pName);
		pName=NULL;
		pName = (LPOLESTR*)CoTaskMemAlloc(sizeof(LPOLESTR)*100);
		pEB->Next(1,pName,&Fetched);		
	}
	CoTaskMemFree(pName);
	pName=NULL;
	*/


	pEB.Release();
	m_pBrowse->ChangeBrowsePosition(OPC_BROWSE_TO,A2W(""));	
}

void CTestTagsAdd::OnButtonAdd() 
{
	//сначала узнаем - сколько тегов добавим
			
	CTestTagsBaseProps dlg;
	dlg.m_TagCount=m_ListCtrl.GetSelectedCount();
	//m_ListCtrl
	if (dlg.m_TagCount==1)
	{
		POSITION pos=m_ListCtrl.GetFirstSelectedItemPosition();
		int iii=m_ListCtrl.GetNextSelectedItem(pos);
		dlg.m_Name=m_ListCtrl.GetItemText(iii,0);
		dlg.m_RealName = /*m_CurrentPath +"." +dlg.m_Name;*/m_ListCtrl.GetItemText(iii,1);
	}
	dlg.m_Access = 3;
	dlg.m_Type = 0;
	dlg.m_NotifyUpdate = 0;
	dlg.m_Active = 1;
	dlg.m_UpdsatePeriod = 200;
	if (dlg.DoModal()==IDOK)
	{
		
		long SelCount;
		if((SelCount=m_ListCtrl.GetSelectedCount())>1)
		{
			int nItem;
			POSITION pos=m_ListCtrl.GetFirstSelectedItemPosition();
			while (SelCount)  {
				nItem=m_ListCtrl.GetNextSelectedItem(pos);
				//заполним свойства ПО всем итемам
				CTagInfo* pTag = new CTagInfo;
				
				pTag->m_Name = m_ListCtrl.GetItemText(nItem,0);
				pTag->m_RealName = m_ListCtrl.GetItemText(nItem,1);
				
				pTag->m_Active = dlg.m_Active;
				pTag->m_Description = dlg.m_Description;
				pTag->m_dwAccessRights = dlg.m_Access;
				pTag->m_Name = dlg.m_PrefName+pTag->m_Name+dlg.m_PostName;
				pTag->m_NotifyUpdate = dlg.m_NotifyUpdate;
				pTag->m_UpdateRate = dlg.m_UpdsatePeriod;
				pTag->m_vtVarType = dlg.m_Type;
				//проверка на наличие такого имени
				if (IsNameInList(pTag->m_Name))
				{
					CString Msg;
					Msg.Format("Тег с именем %s уже выбран для вставки",(LPCSTR)pTag->m_Name);
					AfxMessageBox(Msg);
					delete pTag;
				}
				else
					m_pTagList->insert(m_pTagList->end(),pTag);
				SelCount--;
			}
		}
		else
		{
			CTagInfo* pTag = new CTagInfo;
			
			pTag->m_Name = dlg.m_Name;
			pTag->m_RealName = dlg.m_RealName;
			pTag->m_Active = dlg.m_Active;
			pTag->m_Description = dlg.m_Description;
			pTag->m_dwAccessRights = dlg.m_Access;
			pTag->m_Name = dlg.m_PrefName+pTag->m_Name+dlg.m_PostName;
			pTag->m_NotifyUpdate = dlg.m_NotifyUpdate;
			pTag->m_UpdateRate = dlg.m_UpdsatePeriod;
			pTag->m_vtVarType = dlg.m_Type;
			if (IsNameInList(pTag->m_Name))
			{
				CString Msg;
				Msg.Format("Тег с именем %s уже выбран для вставки",(LPCSTR)pTag->m_Name);
				AfxMessageBox(Msg);
				delete pTag;
			}
			else
				m_pTagList->insert(m_pTagList->end(),pTag);
			
		}
		
	}
	m_Count=m_pTagList->size();
	UpdateData(false);
}

bool CTestTagsAdd::IsNameInList(CString Name)
{
	//ищем вставленное имя.
	std::list<CTagInfo*>::iterator itl;
	for(itl=m_pTagList->begin();itl!=m_pTagList->end();++itl)
	{
		if ((*itl)->m_Name==Name) 
		{
			return true;//да такое уже есть
		}
	}
	return false;//нет такого
}

void CTestTagsAdd::OnBnClickedButtonUpdatebrowse()
{
	FillList(m_CurrentPath);
	// TODO: Add your control notification handler code here
}
