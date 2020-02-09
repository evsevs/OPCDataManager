// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "OPCDMConf1.h"

#include "OPCDMConf1Doc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here

}

CLeftView::~CLeftView()
{
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	COPCDMConf1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
//	if (&GetDocument()->m_bPaused)
//		GetTreeCtrl().SetImageList(&GetDocument()->m_imlistSmallDisconnected, TVSIL_NORMAL);
//	else
		GetTreeCtrl().SetImageList(&GetDocument()->m_imlistSmall, TVSIL_NORMAL);

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

COPCDMConf1Doc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COPCDMConf1Doc)));
	return (COPCDMConf1Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers
long CLeftView::AddNode(std::vector<TVITEM*> vec,HTREEITEM hRoot,HTREEITEM hLast,DWORD &Count,DWORD ChildrenCount)
{
	CTreeCtrl & pT=GetTreeCtrl();
	TVINSERTSTRUCT tvis;
	tvis.hParent = hRoot;
	tvis.hInsertAfter = hLast;
	tvis.item = *vec[Count];
	
		/*while(vec.size()-Count)*/
	
	while(ChildrenCount)
	{
		hRoot=pT.InsertItem(&tvis);
		Count++;
		int chii=vec[Count-1]->cChildren;
		if (chii)
		{
			delete[] vec[Count-1];
			AddNode(vec,hRoot,TVI_LAST,Count,chii);
		}else
			delete[] vec[Count-1];

		ChildrenCount--;
		if (ChildrenCount)
			tvis.item = *vec[Count];
	}

	return Count;
}
void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	COPCDMConf1Doc* pDoc = GetDocument();	
	CTreeCtrl& refCtrl = GetTreeCtrl();
	refCtrl.DeleteAllItems();
	std::map<long,CChannelInfo*>::iterator itm;
	for(itm=pDoc->m_Channels.begin();itm!=pDoc->m_Channels.end();++itm)
	{ //по каждому каналу в карте...
		std::vector<TVITEM*> vec;
		itm->second->GetForTree(vec);
		DWORD Count=0;
		AddNode(vec,TVI_ROOT,TVI_FIRST,Count,1);
	}

/*	CTreeCtrl& refCtrl = GetTreeCtrl();
	TVITEM tvit;
	TVINSERTSTRUCT tvins;
	HTREEITEM hroot1, hroot2, hroot3;
	CString str1, str2;
	DWORD addr = 256;
	POSITION pos;
	DWORD dv, md, tg;
	DWORD dwh = 1;
	
	str1="Локальный OPC DM";
	tvit.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvit.pszText = str1.GetBuffer(4);
	tvit.cchTextMax = 4;
	tvit.iImage = 2;
	tvit.iSelectedImage = 2;
	tvins.hParent = TVI_ROOT;
	tvins.hInsertAfter = TVI_FIRST;
	tvins.item = tvit;
	hroot1 = refCtrl.InsertItem(&tvins);
	
	str2="Child Item";
	tvit.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvit.pszText = str2.GetBuffer(4);
	tvit.cchTextMax = 4;
	tvit.iImage = 2;
	tvit.iSelectedImage = 2;
	tvins.hParent = hroot1;
	tvins.hInsertAfter = TVI_LAST;
	tvins.item = tvit;
	hroot1 = refCtrl.InsertItem(&tvins);	

	str2="Child Child Item";
	tvit.mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvit.pszText = str2.GetBuffer(4);
	tvit.cchTextMax = 4;
	tvit.iImage = 2;
	tvit.iSelectedImage = 2;
	tvins.hParent = hroot1;
	tvins.hInsertAfter = TVI_LAST;
	tvins.item = tvit;
	hroot1 = refCtrl.InsertItem(&tvins);	
	
//	refCtrl.SetItemData(h
*/	
}

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	COPCDMConf1Doc * pDoc=GetDocument();
	pDoc->m_pSelectedChannel = (CChannelInfo*)pNMTreeView->itemNew.lParam;
	CTreeCtrl & refTree =GetTreeCtrl();

	//поиск пути
	HTREEITEM hParent=pNMTreeView->itemNew.hItem;
	CString Path;
	CString Path1=refTree.GetItemText(pNMTreeView->itemNew.hItem);
	while ((hParent=refTree.GetParentItem(hParent))!=NULL)
	{
		Path=Path1;//для удаления имени канала (не нужно)
		Path1=refTree.GetItemText(hParent)+"."+Path1;
	}
	pDoc->m_SelectedItemPath = Path1;
	pDoc->m_bViewIsChannel= true;
	pDoc->UpdateAllViews(this);
		
	*pResult = 0;
}

//DEL void CLeftView::AddNode(HTREEITEM hroot, HTREEITEM last)
//DEL {
//DEL 	CTreeCtrl & pTree=GetTreeCtrl();
//DEL 
//DEL }

/*void CLeftView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CTreeView::OnActivate(nState, pWndOther, bMinimized);
	
//	Beep(500,500);
	// TODO: Add your message handler code here
	
}*/

void CLeftView::OnSetFocus(CWnd* pOldWnd) 
{
	CTreeView::OnSetFocus(pOldWnd);
	
	COPCDMConf1Doc * pDoc= GetDocument();
	pDoc->IsChannel = true;
}
