// WizardDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "WizardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define END_BTN_TEXT	"&End"
#define BACK_BTN_TEXT	"<< &Back"
#define NEXT_BTN_TEXT	"&Next >>"
#define CANCEL_BTN_TEXT	"&Cancel"

/*
#define END_BTN_TEXT	"&Fine"
#define BACK_BTN_TEXT	"<< &Indietro"
#define NEXT_BTN_TEXT	"&Avanti >>"
#define CANCEL_BTN_TEXT	"Annulla"
*/

/////////////////////////////////////////////////////////////////////////////
// CWizardDlg dialog
//IMPLEMENT_DYNAMIC(CWizPage, CObject)

CWizardDlg::CWizardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWizardDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWizardDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	iCurIdx = -1;
	csTitle = "Wizard";
}


void CWizardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWizardDlg)
	DDX_Control(pDX, IDC_PICTURE, wndPicture);
	DDX_Control(pDX, IDC_PAGEFRAME, wndFrame);
	DDX_Control(pDX, IDC_BT_TITLE, wndTitle);
	//}}AFX_DATA_MAP
}

CWizardDlg::~CWizardDlg()
{
	pPages.RemoveAll();
	csText.RemoveAll();
	csIds.RemoveAll();
}

BEGIN_MESSAGE_MAP(CWizardDlg, CDialog)
	//{{AFX_MSG_MAP(CWizardDlg)
	ON_BN_CLICKED(IDC_BACK, OnBack)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWizardDlg message handlers

BOOL CWizardDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetIcon(AfxGetApp()->LoadIcon(IDI_ICON_CHWIZARD), FALSE);
	
	if (pPages.GetSize() > 0)
	{
		CRect rc;
		wndFrame.GetWindowRect(rc);
		ScreenToClient(rc);
		for (int t = 0; t < pPages.GetSize(); t++)
		{
			CDialog * pDlg1 = GetDialog(t);
			if (pDlg1)
			{
				pDlg1->Create(csIds.GetAt(t), this);
				pDlg1->SetWindowPos(0,rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER);
			}			
		}
		SetCurSel(0);
	}
	SetWindowText(csTitle);
	SetDlgItemText(IDC_BACK, BACK_BTN_TEXT);
	if (pPages.GetSize() > 1) SetDlgItemText(IDOK, NEXT_BTN_TEXT);
	else SetDlgItemText(IDOK, END_BTN_TEXT);

	SetDlgItemText(IDCANCEL, CANCEL_BTN_TEXT);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWizardDlg::OnCancel() 
{
	ClosePages();
	CDialog::OnCancel();
}

void CWizardDlg::OnOK() 
{
	if (iCurIdx < pPages.GetSize() - 1) 
	{
		SetCurSel(iCurIdx+1);
		if (iCurIdx == pPages.GetSize() - 1) SetDlgItemText(IDOK, END_BTN_TEXT);
		GetDlgItem(IDC_BACK)->EnableWindow(TRUE);
	}
	else 
	{
		for (int t = 0; t < pPages.GetSize(); t++)
		{
			CDialog * pDlg1 = GetDialog(t);
			if (pDlg1) 
			{
				pDlg1->UpdateData();
			}
		}
		ClosePages();
		CDialog::OnOK();
	}
}

void CWizardDlg::OnBack() 
{
	if (iCurIdx > 0)
	{
		if (iCurIdx == pPages.GetSize() - 1) SetDlgItemText(IDOK, NEXT_BTN_TEXT);
		SetCurSel(iCurIdx-1);
	}
	if (iCurIdx <= 0) GetDlgItem(IDC_BACK)->EnableWindow(FALSE);
}

void CWizardDlg::AddPage(const char * cText, CDialog * pDlg, const UINT id)
{
	pPages.Add((void *) pDlg);
	csText.Add(CString(cText));
	csIds.Add(id);
}

void CWizardDlg::SetCurSel(const int idx)
{
	if (iCurIdx >= 0)
	{
		CDialog * pDlg1 = GetDialog(iCurIdx);
		if (pDlg1) 
		{
			if (!pDlg1->UpdateData()) return;
			pDlg1->ShowWindow(SW_HIDE);
		}
	}
	iCurIdx = idx;
	CDialog * pDlg2 = GetDialog(iCurIdx);
	if (pDlg2) 
	{
		pDlg2->ShowWindow(SW_SHOW);
		wndTitle.SetWindowText(csText[iCurIdx]);
		wndTitle.Invalidate();
	}
}

void CWizardDlg::ClosePages()
{
	for (int t = 0; t < pPages.GetSize(); t++)
	{
		CDialog * pDlg1 = GetDialog(iCurIdx);
		if (pDlg1) pDlg1->DestroyWindow();
	}
}

CDialog * CWizardDlg::GetDialog(const int idx)
{
	ASSERT(idx >= 0 && idx < pPages.GetSize());
	return (CDialog *) pPages.GetAt(idx);
}
