// OPCDMConf1View.cpp : implementation of the COPCDMConf1View class
//

#include "stdafx.h"
#include "OPCDMConf1.h"

#include "OPCDMConf1Doc.h"
#include "OPCDMConf1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COPCDMConf1View

IMPLEMENT_DYNCREATE(COPCDMConf1View, CListView)

BEGIN_MESSAGE_MAP(COPCDMConf1View, CListView)
	//{{AFX_MSG_MAP(COPCDMConf1View)
	ON_WM_SETFOCUS()
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COPCDMConf1View construction/destruction

COPCDMConf1View::COPCDMConf1View()
{
	// TODO: add construction code here

}

COPCDMConf1View::~COPCDMConf1View()
{
}

BOOL COPCDMConf1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COPCDMConf1View drawing

void COPCDMConf1View::OnDraw(CDC* pDC)
{
	COPCDMConf1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//CListCtrl& refCtrl = GetListCtrl();
	//refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

void COPCDMConf1View::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl &ml=GetListCtrl();
	ml.SetImageList(&GetDocument()->m_imlist, LVSIL_NORMAL);
	ml.SetImageList(&GetDocument()->m_imlistSmall,LVSIL_SMALL);

	ml.InsertColumn(0,"Название",LVCFMT_LEFT,130);
	ml.InsertColumn(1,"ID",LVCFMT_LEFT,60);
	ml.InsertColumn(2,"Название в устр.",LVCFMT_LEFT,100);
	ml.InsertColumn(3,"Активность",LVCFMT_LEFT,60);
	ml.InsertColumn(4,"Уведомления",LVCFMT_LEFT,60);
	ml.InsertColumn(5,"Период обн.",LVCFMT_LEFT,50);
	ml.InsertColumn(6,"Описание",LVCFMT_LEFT,80);
	ml.InsertColumn(7,"Тип данных",LVCFMT_LEFT,30);
	ml.InsertColumn(8,"Доступ",LVCFMT_LEFT,60);
}

/////////////////////////////////////////////////////////////////////////////
// COPCDMConf1View diagnostics

#ifdef _DEBUG
void COPCDMConf1View::AssertValid() const
{
	CListView::AssertValid();
}

void COPCDMConf1View::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

COPCDMConf1Doc* COPCDMConf1View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COPCDMConf1Doc)));
	return (COPCDMConf1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COPCDMConf1View message handlers
//DEL void COPCDMConf1View::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
//DEL {
//DEL 	//TODO: add code to react to the user changing the view style of your window
//DEL }

void COPCDMConf1View::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CListCtrl& ml=this->GetListCtrl();
	COPCDMConf1Doc * pDoc=this->GetDocument();
	//удалим все
	ml.DeleteAllItems();
	
	if(!pDoc->m_pSelectedChannel) return ;
	if (!pDoc->m_bConnected) return ;
	std::vector<LVITEM*> vec;
	pDoc->m_pSelectedChannel->GetForList(pDoc->m_SelectedItemPath,vec);

	//теперь заполним из массива
	for(int i=0;i<vec.size();i++)
	{
		if (vec[i]->iSubItem==0)
		{//вставляем
			int df=ml.InsertItem(vec[i]);
			delete vec[i];
		}else
		{
			ml.SetItem(vec[i]);
			delete vec[i];
		}
	}
	
	//	if (GetDocument()->m_TetsFlag)
	//	{
	//		ml.InsertColumn(0,"Название",LVCFMT_LEFT,100);
	//		ml.InsertColumn(1,"Тип",LVCFMT_LEFT,50);
	//	}
	//	else
	//	{
	//		int x=ml.InsertItem(LVIF_TEXT|LVIF_IMAGE,0,"adsfasdfasdfa",0,0,1,0);
	//ml.SetItem(x,1,LVIF_TEXT|LVIF_IMAGE,"no type",1,0,0,0);
	//		ml.InsertItem(1,"adsfasdfasdfa",3);
	
	//	}
	
}

void COPCDMConf1View::OnSetFocus(CWnd* pOldWnd) 
{
	CListView::OnSetFocus(pOldWnd);
	
	COPCDMConf1Doc * pDoc= GetDocument();
	pDoc->IsChannel = false;
	
}

void COPCDMConf1View::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
//	Beep(700,100);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	COPCDMConf1Doc *pDoc = GetDocument();

	CListCtrl &pView = GetListCtrl();
	pDoc->m_SelectedItemShortName = pView.GetItemText(pNMListView->iItem,0);


	if (pView.GetItemData(pNMListView->iItem))//канал
		pDoc->m_bViewIsChannel= true;
	else
		pDoc->m_bViewIsChannel=false;


	*pResult = 0;
}
/*
void COPCDMConf1View::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//	Beep(100,400);
	*pResult = 0;
}

void COPCDMConf1View::OnItemdblclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
*/
/*
void COPCDMConf1View::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	Beep(100,100);
	*pResult = 0;
}
*/