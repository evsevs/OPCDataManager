// OPCDMConf1Doc.cpp : implementation of the COPCDMConf1Doc class
//

#include "stdafx.h"
#include "OPCDMConf1.h"

#include "OPCDMConf1Doc.h"
#include "ChannelPropDlg1.h"
#include "TagPropDlg.h"
#include "RegidtryPropDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COPCDMConf1Doc

IMPLEMENT_DYNCREATE(COPCDMConf1Doc, CDocument)

BEGIN_MESSAGE_MAP(COPCDMConf1Doc, CDocument)
//{{AFX_MSG_MAP(COPCDMConf1Doc)
	ON_COMMAND(ID_BUTTON_CONNECT, OnButtonConnect)
	ON_COMMAND(ID_BUTTON_DISCONNECT, OnButtonDisconnect)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ALL_PAUSE, OnUpdateButtonAllPause)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_UPDATE_VIEWS, OnUpdateUpdateAllViews)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_ALL_CONTINUE, OnUpdateButtonAllContinue)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_SAVECONFIG, OnUpdateButtonSaveConfig)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateButtonSaveAs)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_PROP, OnUpdateButtonProp)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CHANNEL_ADD, OnUpdateButtonChannelAdd)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CHANNEL_DEL, OnUpdateButtonChannelDel)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TAG_ADD, OnUpdateButtonTagAdd)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_TAG_DEL, OnUpdateButtonTagDel)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_CONNECT, OnUpdateButtonConnect)
	ON_UPDATE_COMMAND_UI(ID_BUTTON_DISCONNECT, OnUpdateButtonDisconnect)
	ON_COMMAND(ID_BUTTON_PROP, OnButtonProp)
	ON_COMMAND(ID_BUTTON_CHANNEL_ADD, OnButtonChannelAdd)
	ON_COMMAND(ID_BUTTON_CHANNEL_DEL, OnButtonChannelDel)
	ON_COMMAND(ID_BUTTON_TAG_ADD, OnButtonTagAdd)
	ON_COMMAND(ID_BUTTON_TAG_DEL, OnButtonTagDel)
	ON_COMMAND(ID_BUTTON_ALL_PAUSE, OnButtonAllPause)
	ON_COMMAND(ID_BUTTON_ALL_CONTINUE, OnButtonAllContinue)
	ON_COMMAND(ID_BUTTON_SAVECONFIG,OnButtonSaveConfig)
	ON_COMMAND(ID_FILE_SAVE_AS,OnSaveAs)
	ON_COMMAND(ID_BUTTON_EDIT_BASE_SETTINGS,OnEditRegistry)
	ON_COMMAND(ID_BUTTON_UPDATE_VIEWS,OnUpdateAllViews)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COPCDMConf1Doc construction/destruction

COPCDMConf1Doc::COPCDMConf1Doc()
{
	// TODO: add one-time construction code here
	m_bPaused=false;
	m_imlist.Create(32,32,TRUE,1,3);
	m_imlistDisconnected.Create(32,32,TRUE,1,3);
	HICON hi = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	m_imlist.Add(hi);
	m_imlistDisconnected.Add(hi);
	hi = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_TAG));
	m_imlist.Add(hi);
	m_imlistDisconnected.Add(hi);
	hi = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_CHANNEL));
	m_imlist.Add(hi);
	hi = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_CHANNEL_DISCONNECTED));
	//m_imlist.Add(hi);
	m_imlistDisconnected.Add(hi);

	m_imlistSmall.Create(16,16,TRUE,1,3);
	m_imlistSmallDisconnected.Create(16,16,TRUE,1,3);
	hi = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	m_imlistSmall.Add(hi);
	m_imlistSmallDisconnected.Add(hi);
	hi = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_TAG));
	m_imlistSmall.Add(hi);
	m_imlistSmallDisconnected.Add(hi);
	hi = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_CHANNEL));
	m_imlistSmall.Add(hi);
	hi = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ICON_CHANNEL_DISCONNECTED));
	//m_imlistSmall.Add(hi);
	m_imlistSmallDisconnected.Add(hi);

	m_bConnected=false;
	m_pSelectedChannel=NULL;
}

COPCDMConf1Doc::~COPCDMConf1Doc()
{
	ClearChannelMap();
}

BOOL COPCDMConf1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COPCDMConf1Doc serialization

void COPCDMConf1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// COPCDMConf1Doc diagnostics

#ifdef _DEBUG
void COPCDMConf1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void COPCDMConf1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COPCDMConf1Doc commands

void COPCDMConf1Doc::OnButtonConnect() 
{
	// TODO: Add your command handler code he
//	AfxMessageBox("PPP");
	ClearChannelMap();

	HRESULT hr=m_pConf.CoCreateInstance(CLSID_MyTestConf);
	if (FAILED(hr))
	{
		CString Mes;
		char dddd[100];
		sprintf(dddd,"Не могу соединиться с объектом конфигурации, error= 0x%d ",hr);
		//Mes.FormatMessage("Не могу соединиться с объектом конфигурации, error= 0x%d ",hr);
		AfxMessageBox(dddd,MB_OK|MB_ICONEXCLAMATION);
		m_bConnected=false;
	}else
		m_bConnected=true;
	//получим состояние OPCDM
	m_pConf->GetStatus(&m_dwPausedGlobal);
	//заполним карту каналов
	//Sleep(2000);
	hr=FillChannelMap();
	m_pSelectedChannel =NULL;
	UpdateAllViews(NULL);
}

void COPCDMConf1Doc::OnButtonDisconnect() 
{
	m_pConf.Release();
	ClearChannelMap();
	
	m_pSelectedChannel=NULL;
	m_SelectedItemPath="";
	m_SelectedItemShortName="";
	m_bConnected=false;
	
	UpdateAllViews(NULL);
	

}

void COPCDMConf1Doc::OnUpdateButtonConnect(CCmdUI* pCmdUI) 
{
if (m_bConnected)
{
	pCmdUI->Enable(FALSE);
}
else
	pCmdUI->Enable(TRUE);
}

void COPCDMConf1Doc::OnUpdateUpdateAllViews(CCmdUI* pCmdUI)
{
	if (m_bConnected)
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}


void COPCDMConf1Doc::OnUpdateButtonDisconnect(CCmdUI* pCmdUI) 
{
	if (m_bConnected)
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
	
}

void COPCDMConf1Doc::OnUpdateButtonProp(CCmdUI* pCmdUI)
{
	if (m_bConnected)
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}
void COPCDMConf1Doc::OnUpdateButtonChannelAdd(CCmdUI* pCmdUI)
{
	if (m_bConnected&&(m_dwPausedGlobal==0))
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
	
}

void COPCDMConf1Doc::OnUpdateButtonChannelDel(CCmdUI* pCmdUI)
{
	if(m_bConnected&&(m_dwPausedGlobal==0))
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
	
}

void COPCDMConf1Doc::OnUpdateButtonTagAdd(CCmdUI* pCmdUI)
{
	if(m_bConnected&&(m_dwPausedGlobal==0))
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
	
}

void COPCDMConf1Doc::OnUpdateButtonTagDel(CCmdUI* pCmdUI)
{
	if (m_bConnected&&(m_dwPausedGlobal==0))
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
	
}
void COPCDMConf1Doc::OnUpdateButtonAllPause(CCmdUI* pCmdUI)
{
	if (m_bConnected&&(m_dwPausedGlobal!=0))
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}
void COPCDMConf1Doc::OnUpdateButtonAllContinue(CCmdUI* pCmdUI)
{
	if (m_bConnected&&(m_dwPausedGlobal==0))
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}
void COPCDMConf1Doc::OnUpdateButtonSaveConfig(CCmdUI* pCmdUI)
{
	if (m_bConnected)
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}
void COPCDMConf1Doc::OnUpdateButtonSaveAs(CCmdUI* pCmdUI)
{
	if (m_bConnected)
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);
}
HRESULT COPCDMConf1Doc::FillChannelMap()
{
	//Заполнение карты каналов
	DWORD m_ChannelsCount=m_Channels.size();
	IUnknown *pUnk=NULL;
	CComPtr<IEnumUnknown> pECH;
	HRESULT hr=m_pConf->EnumChannels(&pECH);
	if (FAILED(hr))
		return hr;
	DWORD Fetched=0;
	ICChannelObj *pCh=NULL;
	pECH->Next(1,&pUnk,&Fetched);
	while(pUnk)
	{
		pUnk->QueryInterface(IID_ICChannelObj,(void**)&pCh);
		CChannelInfo * pChIn=new CChannelInfo(pCh);
		pUnk=NULL;
		DWORD ChID=0;
		pCh->get_ChannelID(&ChID);
		m_Channels.insert(std::map<long,CChannelInfo*>::value_type(ChID,pChIn));
		pCh=NULL;
		pChIn=NULL;
		pECH->Next(1,&pUnk,&Fetched);
	}
	pECH.Release();
	return S_OK;
}

void COPCDMConf1Doc::ClearChannelMap()
{
	std::map<long,CChannelInfo*>::iterator itm;
	for(itm=m_Channels.begin();itm!=m_Channels.end();++itm)
	{
		CChannelInfo* pI=itm->second;
		delete pI;
	}
	m_Channels.clear();
}

void COPCDMConf1Doc::OnButtonProp() 
{
	if (m_pSelectedChannel==NULL) 
	{
		AfxMessageBox("Не выбран канал!");
		return;
	}
		
		
	if (IsChannel||m_bViewIsChannel)
	{
		CChannelPropDlg ChDlg;
		ChDlg.m_pInfo = m_pSelectedChannel;
		ChDlg.DoModal();
	}else
	{
		if (m_SelectedItemShortName=="")
		{
			AfxMessageBox("Не выбран тэг!");
			return;
		}

		CTagPropDlg TDlg;
		TDlg.m_pInfo = m_pSelectedChannel;
		TDlg.m_SelectedItemPath = m_SelectedItemPath;
		TDlg.m_SelectedItemShortName = m_SelectedItemShortName;
		TDlg.DoModal();
		//TDlg
	}
	
}

void COPCDMConf1Doc::OnButtonChannelAdd() 
{
	if (!m_bConnected)
	{
		AfxMessageBox("Нет соединения с OPCDataManager!");
		return;
	}
	CWizardDlg dlg;
	dlg.csTitle = "Создание канала";
	CChannelCreateInfo * pChInfo = new CChannelCreateInfo;
	CChannelWizFirst d;
	d.pInfo = pChInfo;
	CChannelWizSecond d1;
	d1.pInfo = pChInfo;
	CChannelWizThird d2;
	d2.pInfo = pChInfo;
	d2.m_pConf = m_pConf;
	CChannelWizResult d3;
	d3.pInfo = pChInfo;
	CChannelWizFourth d4;
	d4.pInfo = pChInfo;
	dlg.AddPage("Шаг 1\tОбщие",&d,CChannelWizFirst::IDD);
	dlg.AddPage("Шаг 2\tКонфигурация",&d1,CChannelWizSecond::IDD);
	dlg.AddPage("Шаг 3\tПлагин",&d2,CChannelWizThird::IDD);
	dlg.AddPage("Шаг 4\tКонфигурация плагина",&d4,CChannelWizFourth::IDD);
	dlg.AddPage("Шаг 5\tРезультаты",&d3,CChannelWizResult::IDD);
	if (dlg.DoModal()==IDOK)
	{//здесь имеем заполненный класс с информацией о канале.
		//AfxMessageBox("Создается канал!");
		ChannelDef df;
		pChInfo->GetCreateStruct(df);
		CComPtr<ICChannelObj> pChan; 
		HRESULT hr=m_pConf->CreateChannel(&df,&pChan);
		if (FAILED(hr))
		{
		
			try{
			
			_com_issue_errorex(hr, (IUnknown*)m_pConf, __uuidof(m_pConf));

			}catch(_com_error &e)
			{
				
			AfxMessageBox((char*)e.Description());
			}
		}
		SysFreeString(df.ChannelCnfg);
		SysFreeString(df.ChannelName);
		SysFreeString(df.PluginCnfg);
		SysFreeString(df.PluginProgID);
		SysFreeString(df.ChannelDescription);


		hr=FillChannelMap();
		m_pSelectedChannel =NULL;
		UpdateAllViews(NULL);
	}
	else
		AfxMessageBox("НЕ создается канал!");

	
	delete pChInfo;
}

void COPCDMConf1Doc::OnButtonChannelDel() 
{
	DWORD Iid=AfxMessageBox("Удаление текущего канала!",MB_YESNO |MB_ICONEXCLAMATION);
	//Удаление
	if (Iid==IDNO) return;

	DWORD ChID=0;
	m_pSelectedChannel->m_pChannel->get_ChannelID(&ChID);
	m_Channels.erase(ChID);
	delete m_pSelectedChannel;
	//m_pSelectedChannel->m_pChannel.Release();
	m_pSelectedChannel=NULL;

	try{
	
	HRESULT hr=m_pConf->DeleteChannel(ChID);
	if (FAILED(hr))
		_com_issue_errorex(hr,(IUnknown*)m_pConf,IID_IMyTestConf);

	}
	catch(_com_error &e)
	{
		AfxMessageBox(e.Description(),MB_OK|MB_ICONERROR);
	}
//	ClearChannelMap();
//	m_pSelectedChannel =NULL;
//		m_SelectedItemPath="";
//	m_SelectedItemShortName="";

//	UpdateAllViews(NULL);

	//m_pSelectedChannel =NULL;
	FillChannelMap();
	m_pSelectedChannel=NULL;
	UpdateAllViews(NULL);

//	FillChannelMap();
//	m_pSelectedChannel =NULL;
//		m_SelectedItemPath="";
//	m_SelectedItemShortName="";
	
//	UpdateAllViews(NULL);
}
void COPCDMConf1Doc::OnSaveAs()
{
	CString newName;
	bool bReplace =true;
	/*		if (!AfxGetApp()->DoPromptFileName(newName,
		  bReplace ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY,
		  OFN_HIDEREADONLY | OFN_PATHMUSTEXIST, FALSE, pTemplate))
			return FALSE;    */

	CFileDialog dlgFile(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL, NULL, 0);
	dlgFile.m_ofn.Flags |=true ? AFX_IDS_SAVEFILE : AFX_IDS_SAVEFILECOPY;
	CString strFilter;
	CString allFilter;
	CString fileName="CopyOfOPCDMSettings.xml";
	VERIFY(allFilter.LoadString(AFX_IDS_ALLFILTER));
	strFilter += allFilter;
	strFilter += (TCHAR)'\0';   // next string please
	strFilter += _T("*.xml");
	strFilter += (TCHAR)'\0';   // last string
	dlgFile.m_ofn.nMaxCustFilter++;

	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = "Выберимте файл для сохранения копии настроек OPC DM";
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	INT_PTR nResult = dlgFile.DoModal();
	fileName.ReleaseBuffer();
	if (nResult == IDOK)
	{
			//сохраним
		_bstr_t st=dlgFile.m_pOFN->lpstrFile; ;
		BSTR sb=st.Detach();
		m_pConf->SaveCurrentConfigToXML(sb);
		st.Attach(sb);
	}


}
void COPCDMConf1Doc::OnButtonSaveConfig() 
{
	//просто сохраним в конфигурационный файл
	_bstr_t st="";
	BSTR sb=st.Detach();
	m_pConf->SaveCurrentConfigToXML(sb);
	st.Attach(sb);

}

void COPCDMConf1Doc::OnButtonTagAdd() 
{
//	AfxMessageBox("Добавление тегов в выделенный канал!");	
	CTestTagsAddFirst dlg;
	dlg.m_pInfo = m_pSelectedChannel;
	dlg.m_iList = &m_imlistSmall;
	dlg.m_SelectedItemPath = m_SelectedItemPath;
	//dlg.m_TreeCtrl.SetImageList(&m_imlistSmall, TVSIL_NORMAL);
	dlg.DoModal();
	std::list<CTagInfo*>::iterator itl;
	TagDefStruct *pTagDef = new TagDefStruct[dlg.m_TagList.size()];
	int ic=0;
	for(itl=dlg.m_TagList.begin();itl!=dlg.m_TagList.end();++itl)
	{
		(*itl)->GetTagDef(pTagDef+ic,m_SelectedItemPath+".");
		ic++;
	}
	IChannelTagDef * pTD;
	m_pSelectedChannel->m_pChannel->QueryInterface(IID_IChannelTagDef,(void**)&pTD);
	HRESULT *PPP=NULL;
	pTD->CreateTags(ic,pTagDef,&PPP);
	if (PPP)
		CoTaskMemFree(PPP);
	delete[] pTagDef;
	UpdateAllViews(NULL);
}

void COPCDMConf1Doc::OnButtonTagDel() 
{
	//AfxMessageBox("Удаление тегов выделенного канала!");	
	CTagsDelDlg dlg;
	dlg.m_pInfo = m_pSelectedChannel;
	if (dlg.DoModal()==IDOK)
		UpdateAllViews(NULL);
	
}

void COPCDMConf1Doc::OnButtonAllPause() 
{
	if (!m_bConnected) 
		AfxMessageBox("Не подключены к серверу!");

	m_pConf->ChangeState(OPC_STATUS_SUSPENDED);
	m_bPaused=true;
//	SetPaneText (4, "My New Status Bar Text", TRUE)
	m_dwPausedGlobal=0;
}

void COPCDMConf1Doc::OnButtonAllContinue() 
{
	if (!m_bConnected) 
		AfxMessageBox("Не подключены к серверу!");

	m_pConf->ChangeState(OPC_STATUS_RUNNING);
	m_dwPausedGlobal=1;
	
}
void COPCDMConf1Doc::OnEditRegistry()
{
	CRegidtryPropDlg dlg;
	dlg.DoModal();
}

void COPCDMConf1Doc::OnUpdateAllViews()
{
	UpdateAllViews(NULL);
}