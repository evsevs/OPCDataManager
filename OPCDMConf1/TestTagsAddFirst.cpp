// TestTagsAddFirst.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "TestTagsAddFirst.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestTagsAddFirst dialog


CTestTagsAddFirst::CTestTagsAddFirst(CWnd* pParent /*=NULL*/)
	: CDialog(CTestTagsAddFirst::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestTagsAddFirst)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestTagsAddFirst::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestTagsAddFirst)
	DDX_Control(pDX, IDC_LIST_ADDED_TAGS, m_ListCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestTagsAddFirst, CDialog)
//{{AFX_MSG_MAP(CTestTagsAddFirst)
ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_ADDHAND, OnButtonAddhand)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestTagsAddFirst message handlers

BOOL CTestTagsAddFirst::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ListCtrl.InsertColumn(0,"Название",LVCFMT_LEFT,130);
	m_ListCtrl.InsertColumn(1,"Название в устр.",LVCFMT_LEFT,100);
	m_ListCtrl.InsertColumn(2,"Активность",LVCFMT_LEFT,60);
	m_ListCtrl.InsertColumn(3,"Уведомления",LVCFMT_LEFT,60);
	m_ListCtrl.InsertColumn(4,"Период обн.",LVCFMT_LEFT,50);
	m_ListCtrl.InsertColumn(5,"Описание",LVCFMT_LEFT,80);
	m_ListCtrl.InsertColumn(6,"Тип данных",LVCFMT_LEFT,30);
	m_ListCtrl.InsertColumn(7,"Доступ",LVCFMT_LEFT,60);
	m_ListCtrl.SetImageList(m_iList,LVSIL_SMALL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTestTagsAddFirst::OnButtonAdd() 
{
	CTestTagsAdd dlg;
	dlg.m_pInfo = m_pInfo;
	dlg.m_iList = m_iList;
	dlg.m_pTagList = &m_TagList;
	dlg.DoModal();
	FillList();
	UpdateData(false);
}



void CTestTagsAddFirst::OnButtonAddhand() 
{
	CTestTagsBaseProps dlg;
	dlg.m_Access = 3;
	dlg.m_Type = 0;
	dlg.m_NotifyUpdate = 0;
	dlg.m_Active = 1;
	dlg.m_UpdsatePeriod = 200;
	if (dlg.DoModal()==IDOK)
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
		m_TagList.insert(m_TagList.end(),pTag);
	}

	FillList();
}

void CTestTagsAddFirst::FillList()
{
	m_ListCtrl.DeleteAllItems();
	std::list<CTagInfo*>::iterator itl;
	int i=0;
	for(itl=m_TagList.begin();itl!=m_TagList.end();++itl)
	{
		//заполним контрол
		int pos=0;
		CString x;
		char ch[10];
		pos=m_ListCtrl.InsertItem(LVIF_TEXT|LVIF_IMAGE,i,(*itl)->m_Name,0,0,1,(long)(*itl));
		m_ListCtrl.SetItem(pos,1,LVIF_TEXT,(*itl)->m_RealName,0,0,0,0);
		if ((*itl)->m_Active)
			x="Активен";
		else
			x="Не активен";
		m_ListCtrl.SetItem(pos,2,LVIF_TEXT,x,0,0,0,0);
		if ((*itl)->m_Active)
			x="Да";
		else
			x="Нет";
		m_ListCtrl.SetItem(pos,3,LVIF_TEXT,x,0,0,0,0);
		x = _itoa((*itl)->m_UpdateRate,ch,10);
		m_ListCtrl.SetItem(pos,4,LVIF_TEXT,x,0,0,0,0);
		m_ListCtrl.SetItem(pos,5,LVIF_TEXT,(*itl)->m_Description,0,0,0,0);
		x = _itoa((int)(*itl)->m_vtVarType,ch,10);
		m_ListCtrl.SetItem(pos,6,LVIF_TEXT,x,0,0,0,0);
		switch((*itl)->m_dwAccessRights)
		{
		case 0:x="Нет доступа";
			break;
		case 1:x="Чтение";
			break;
		case 2:x="Запись";
			break;
		default:x="Чтение/Запись";
		}
		m_ListCtrl.SetItem(pos,7,LVIF_TEXT,x,0,0,0,0);
		i++;
	}
}

void CTestTagsAddFirst::OnOK() 
{
	
	CDialog::OnOK();
}
