// NetButton.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "NetButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNetButton

CNetButton::CNetButton()
{
	crBack1 = RGB(0,128,128);
	crBack2 = RGB(128,0,128);
	crText  = RGB(255,255,255);
	pFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	lf.lfWeight = 700;
	ftFont.CreateFontIndirect(&lf);
	//CreatePointFont(110,"Arial");
}

CNetButton::~CNetButton()
{
}


BEGIN_MESSAGE_MAP(CNetButton, CButton)
	//{{AFX_MSG_MAP(CNetButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNetButton message handlers

void CNetButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CString cs;
	GetWindowText(cs);
	CDC * pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc(lpDrawItemStruct->rcItem);
	if (cs == "")
	{
		pDC->FillSolidRect(rc, GetSysColor(COLOR_3DFACE));
	}
	else
	{
		double a1 = GetRValue(crBack1);
		double a2 = GetGValue(crBack1);
		double a3 = GetBValue(crBack1);

		double b1 = GetRValue(crBack2);
		double b2 = GetGValue(crBack2);
		double b3 = GetBValue(crBack2);

		double s1 = (b1 - a1)/rc.Width();
		double s2 = (b2 - a2)/rc.Width();
		double s3 = (b3 - a3)/rc.Width();

		for (int t = rc.left; t < rc.right; t++)
		{
			pDC->FillSolidRect(CRect(t,rc.top,t+1,rc.bottom), RGB((int)a1,(int)a2,(int)a3));
			a1 += s1; a2 += s2; a3 += s3;
		}

		int obk = pDC->SetBkMode(TRANSPARENT);
		CFont * of = pDC->SelectObject(&ftFont);
		COLORREF ocr = pDC->SetTextColor(crText);

		int iTab = cs.Find('\t');
		if (iTab > 0)
		{
			pDC->SelectObject(pFont);
			CString cs1 = cs.Right(cs.GetLength() - 1 - iTab);
			UINT oa = pDC->SetTextAlign(TA_RIGHT);
			pDC->TextOut(rc.right-2, rc.top + 1, cs1);
			pDC->SetTextAlign(oa);
			cs = cs.Left(iTab);
			pDC->SelectObject(&ftFont);
		}

		pDC->TextOut(rc.left+2, rc.top + 1, cs);

		pDC->SetTextColor(ocr);
		pDC->SelectObject(of);
		pDC->SetBkMode(obk);

	}
}
