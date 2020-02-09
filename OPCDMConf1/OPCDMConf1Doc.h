// OPCDMConf1Doc.h : interface of the COPCDMConf1Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCDMCONF1DOC_H__9A2FFAFF_7DC3_4304_8E56_EB6FE231286D__INCLUDED_)
#define AFX_OPCDMCONF1DOC_H__9A2FFAFF_7DC3_4304_8E56_EB6FE231286D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "WizardDlg.h"
#include "ChannelWizFirst.h"
#include "ChannelWizSecond.h"
#include "ChannelWizThird.h"
#include "ChannelWizFourth.h"
#include "ChannelWizResult.h"
#include "ChannelInfo.h"
#include "TestTagsAddFirst.h"
#include "TagsDelDlg.h"

class COPCDMConf1Doc : public CDocument
{
protected: // create from serialization only
	COPCDMConf1Doc();
	DECLARE_DYNCREATE(COPCDMConf1Doc)

// Attributes
public:
	bool m_bConnected;
//	bool m_OPCDMPaused;//true - running false-paused
	bool m_bPaused;
	CString m_SelectedItemShortName;
	CComPtr<IMyTestConf> m_pConf;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COPCDMConf1Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool m_bViewIsChannel;
	bool IsChannel;
	void ClearChannelMap();
	HRESULT FillChannelMap();
	CImageList m_imlistSmall;
	CImageList m_imlist;
	CImageList m_imlistSmallDisconnected;
	CImageList m_imlistDisconnected;
	std::map<long,CChannelInfo*> m_Channels;

	CChannelInfo * m_pSelectedChannel;//устанавливается при выборе записи в дереве
	CString		m_SelectedItemPath;//путь до итема

	virtual ~COPCDMConf1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COPCDMConf1Doc)
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonDisconnect();
	afx_msg void OnUpdateButtonConnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUpdateAllViews(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonProp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonChannelAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonChannelDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonTagAdd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonTagDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonAllPause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonAllContinue(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonSaveConfig(CCmdUI* pCmdUI);
	afx_msg void OnUpdateButtonSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnButtonProp();
	afx_msg void OnButtonChannelAdd();
	afx_msg void OnButtonChannelDel();
	afx_msg void OnButtonTagAdd();
	afx_msg void OnButtonTagDel();
	afx_msg void OnButtonAllPause();
	afx_msg void OnButtonAllContinue();
	afx_msg void OnButtonSaveConfig();
	afx_msg void OnSaveAs();
	afx_msg void OnEditRegistry();
	afx_msg void OnUpdateAllViews();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPCDMCONF1DOC_H__9A2FFAFF_7DC3_4304_8E56_EB6FE231286D__INCLUDED_)
