#pragma once
#include "ChannelInfo.h"
#include "afxwin.h"

// CTagsDelDlg dialog

class CTagsDelDlg : public CDialog
{
	DECLARE_DYNAMIC(CTagsDelDlg)

public:
	BOOL OnInitDialog();
	CChannelInfo * m_pInfo;
	CComPtr<ISpaceBrowse> m_pBrowse;
	BOOL GenerateTagList();
	long GetTagsHandlesVector(std::vector<DWORD> &vetHand);

//	CComPtr<ICChannelObj> m_pChannel;

	CTagsDelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTagsDelDlg();

// Dialog Data
	enum { IDD = IDD_TAGSDEL_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	// Фильтрация тегов для отображения в списке тегов
	CString m_Filter;
	// список тегов для выбора 
	CListBox m_TagList;
	afx_msg void OnBnClickedButtonUpdatebrowse();
	afx_msg void OnBnClickedOk();
};
