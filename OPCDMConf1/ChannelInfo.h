// ChannelInfo.h: interface for the CChannelInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHANNELINFO_H__17D68A3B_3FD5_45D8_A0F0_646EA59209E5__INCLUDED_)
#define AFX_CHANNELINFO_H__17D68A3B_3FD5_45D8_A0F0_646EA59209E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "stdafx.h"
#include <comdef.h>
class CChannelInfo
{
public:
	CChannelInfo(ICChannelObj* pChan)
	{
		m_pChannel.Attach(pChan);
	}
	virtual ~CChannelInfo()
	{
		ClearArrays();
		if (m_pChannel.p)
		{
			m_pChannel.Release();
			m_pChannel=NULL;
		}
	}
CComPtr<ICChannelObj> m_pChannel;
std::vector<char*> m_StrArray;
std::vector<char*> m_ListStrArray;

//Информация для дерева
bool GetForTree(std::vector<TVITEM*> &vec)
{
	USES_CONVERSION;
	ClearArrays();
	bool res=true;
	//Формирвание узлов
	CComBSTR t;
	m_pChannel->get_ChannelName(&t);
	char * pCh=new char[t.Length()+1];
	strcpy(pCh,W2A(t.m_str));

	m_StrArray.insert(m_StrArray.end(),pCh);
	TVITEM *it =new TVITEM;
	it->mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
	it->pszText = pCh;
	it->cchTextMax = 4;
	it->iImage = 2;
	it->iSelectedImage = 3;
	it->lParam = (DWORD)this;
	
	vec.insert(vec.end(),it);
	//IUnknown
	IUnknown *pU;
	HRESULT hr=m_pChannel->GetBrowser(&pU);
	if (SUCCEEDED(hr))
	{
		pU->QueryInterface(IID_ISpaceBrowse,(void**)&m_pBrowser);
		pU->Release();
	}

	if (FAILED(hr)) return false;
	DWORD cCh=0;
	GetNodes("",vec,cCh);
	it->cChildren = cCh;
	//удалим после использования
	m_pBrowser.Release();
	return res;
}


//Информация для списка
bool GetForList(CString SubName,std::vector<LVITEM*> &vec)
{
	USES_CONVERSION;
	bool res=true;
	ClearArrays();
	//получение итемов
	IUnknown *pU;
	HRESULT hr=m_pChannel->GetBrowser(&pU);
	if (SUCCEEDED(hr))
	{
		pU->QueryInterface(IID_ISpaceBrowse,(void**)&m_pBrowser);
		pU->Release();
	}
	
	if (FAILED(hr)) return false;
	
	if (SubName!="")
		if(FAILED(hr=m_pBrowser->ChangeBrowsePosition(OPC_BROWSE_TO,A2W(SubName))))
		{
			m_pBrowser.Release();
			return false;
		}
	CComPtr<IEnumString> pEB;
//Проудемся по папкам
	hr=m_pBrowser->BrowseOPCItemIDs(OPC_BRANCH,A2W(""),0,0,&pEB);
	if (FAILED(hr)) 
	{
		m_pBrowser.Release();
		return false;
	}
	
	LPOLESTR pName=NULL;
	DWORD Fetched=0;
	int iti=0; 
	pEB->Next(1,&pName,&Fetched);
	while(pName)
	{	
		char * pCh = new char[strlen(W2A(pName))+1];
		strcpy(pCh,W2A(pName));
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);

		//Название
		LVITEM *  it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=0;
		it->mask = TVIF_TEXT|TVIF_IMAGE|TVIF_PARAM;
		it->pszText = pCh;
		it->iImage = 2;
		it->lParam = (DWORD)this;
		vec.insert(vec.end(),it);
		CoTaskMemFree(pName);
		
/*		//Идентификатор
		DWORD ChID=0;
		char ch[10];
		m_pChannel->get_ChannelID(&ChID);
		pCh=new char[strlen(_ltoa(ChID,ch,10))];
		strcpy(pCh,_ltoa(ChID,ch,10));
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);
		
		it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=1;
		it->mask = TVIF_TEXT|TVIF_IMAGE|TVIF_PARAM;
		it->pszText = pCh;
		//it->iImage = 2;
		it->lParam = (DWORD)this;
		vec.insert(vec.end(),it);
		CoTaskMemFree(pName);

		//Описание
		_bstr_t Descr;
		BSTR x;
		m_pChannel->get_Description(&x);
		Descr.Assign(x);
		pCh = new char[strlen((char*)Descr)+1];
		strcpy(pCh,(char*)Descr);
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);
		
		//Название
		it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=6;
		it->mask = TVIF_TEXT|TVIF_IMAGE|TVIF_PARAM;
		it->pszText = pCh;
		//it->iImage = 2;
		it->lParam = (DWORD)this;
		vec.insert(vec.end(),it);
		*/

		pName=NULL;
		pEB->Next(1,&pName,&Fetched);		
		iti++;
	}
	pEB.Release();

//Пройдемся именно по тегам

	hr=m_pBrowser->BrowseOPCItemIDs(OPC_LEAF,A2W(""),0,0,&pEB);
	if (FAILED(hr)) 
	{
		m_pBrowser.Release();
		return false;
	}
	
	pEB->Next(1,&pName,&Fetched);
	while(pName)
	{	
		char * pCh = new char[strlen(W2A(pName))+1];
		strcpy(pCh,W2A(pName));
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);
/*	ml.InsertColumn(0,"Название",LVCFMT_LEFT,130);
	ml.InsertColumn(1,"ID",LVCFMT_LEFT,60); //5101
	ml.InsertColumn(2,"Название в устр.",LVCFMT_LEFT,100);//5100
	ml.InsertColumn(3,"Активность",LVCFMT_LEFT,60);//5102
	ml.InsertColumn(4,"Уведомления",LVCFMT_LEFT,60);//5103
	ml.InsertColumn(5,"Период обн.",LVCFMT_LEFT,50);//5104
	ml.InsertColumn(6,"Описание",LVCFMT_LEFT,80);//101
	ml.InsertColumn(7,"Тип данных",LVCFMT_LEFT,30);//1
	ml.InsertColumn(8,"Доступ",LVCFMT_LEFT,60);//5
*/
		//Название
		LVITEM *  it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=0;
		it->mask = TVIF_TEXT|TVIF_IMAGE|TVIF_PARAM;
		it->pszText = pCh;
		it->iImage = 1;
		it->lParam = NULL;
		vec.insert(vec.end(),it);

		LPWSTR FullName=NULL;
		m_pBrowser->GetItemID(pName,&FullName);
		CComBSTR tt=W2A(FullName);
		BSTR xN=tt.Copy();
		DWORD pID[8]={5101,5100,5102,5103,5104,101,1,5};
		VARIANT * pVarData=NULL;
		HRESULT *pE=NULL;
		hr=m_pBrowser->GetItemProperties(xN,8,&pID[0],&pVarData,&pE);
		if (FAILED(hr))
			AfxMessageBox("Не могу получить свойства!");
		else{
		
		//ID
		_variant_t test;
		test=(*(pVarData));
		char * pCh = new char[strlen((char*)(_bstr_t)*pVarData)+1];
		strcpy(pCh,(char*)(_bstr_t)*pVarData);
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);
	    it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=1;
		it->mask = TVIF_TEXT;
		it->pszText = pCh;
		vec.insert(vec.end(),it);

		//Название в устр.
//		_variant_t test;
		test=(*(pVarData+1));
		pCh = new char[strlen((char*)(_bstr_t)*(pVarData+1))+1];
		strcpy(pCh,(char*)(_bstr_t)*(pVarData+1));
		
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);
	    it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=2;
		it->mask = TVIF_TEXT;
		it->pszText = pCh;
		vec.insert(vec.end(),it);

		//Активность
		test=(*(pVarData+2));
		pCh = new char[strlen((char*)(_bstr_t)*(pVarData+2))+1];
		strcpy(pCh,(char*)(_bstr_t)*(pVarData+2));
		
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);
		it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=3;
		it->mask = TVIF_TEXT;
		it->pszText = pCh;
		vec.insert(vec.end(),it);

		//Уведомления
		test=(*(pVarData+3));
		pCh = new char[strlen((char*)(_bstr_t)*(pVarData+3))+1];
		strcpy(pCh,(char*)(_bstr_t)*(pVarData+3));
		
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);
		it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=4;
		it->mask = TVIF_TEXT;
		it->pszText = pCh;
		vec.insert(vec.end(),it);
		
		//Период обн.
		test=(*(pVarData+4));
		pCh = new char[strlen((char*)(_bstr_t)*(pVarData+4))+1];
		strcpy(pCh,(char*)(_bstr_t)*(pVarData+4));
		
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);
		it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=5;
		it->mask = TVIF_TEXT;
		it->pszText = pCh;
		vec.insert(vec.end(),it);

		//Описание
		test=(*(pVarData+5));
		pCh = new char[strlen((char*)(_bstr_t)*(pVarData+5))+1];
		strcpy(pCh,(char*)(_bstr_t)*(pVarData+5));
		
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);
		it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=6;
		it->mask = TVIF_TEXT;
		it->pszText = pCh;
		vec.insert(vec.end(),it);

		//Тип данных
		test=(*(pVarData+6));
		pCh = new char[strlen((char*)(_bstr_t)*(pVarData+6))+1];
		strcpy(pCh,(char*)(_bstr_t)*(pVarData+6));
		
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);
		it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=7;
		it->mask = TVIF_TEXT;
		it->pszText = pCh;
		vec.insert(vec.end(),it);
		
		//Доступ
		test=(*(pVarData+7));
		pCh = new char[strlen((char*)(_bstr_t)*(pVarData+7))+1];
		strcpy(pCh,(char*)(_bstr_t)*(pVarData+7));
		
		m_ListStrArray.insert(m_ListStrArray.end(),pCh);
		it = new LVITEM;
		it->iItem=iti;
		it->iSubItem=8;
		it->mask = TVIF_TEXT;
		it->pszText = pCh;
		vec.insert(vec.end(),it);
		
		}
		CoTaskMemFree(pName);
		pName=NULL;
		pEB->Next(1,&pName,&Fetched);		
		iti++;
	}
	pEB.Release();


	m_pBrowser.Release();
	return res;
}

protected:
void ClearArrays()
{
	for(int i=0;i<m_StrArray.size();i++)
		delete[] m_StrArray[i];
	for(int y=0;y<m_ListStrArray.size();y++)
		delete[] m_ListStrArray[y];
	m_StrArray.clear();
	m_ListStrArray.clear();
}
CComPtr<ISpaceBrowse> m_pBrowser;
void GetNodes(CString NodeName,std::vector<TVITEM*> &vec,DWORD &cChildren)
{
	USES_CONVERSION;
	HRESULT hr=S_OK;
	if (NodeName!="")
		hr=m_pBrowser->ChangeBrowsePosition(OPC_BROWSE_DOWN,A2W((LPCSTR)NodeName));

	if (FAILED(hr)) return;

	CComPtr<IEnumString> pEB;
	hr=m_pBrowser->BrowseOPCItemIDs(OPC_BRANCH,A2W(""),0,0,&pEB);
	if (FAILED(hr)) 
	{//восстановим состояние browser'a
		m_pBrowser->ChangeBrowsePosition(OPC_BROWSE_UP,A2W(""));
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
		m_StrArray.insert(m_StrArray.end(),pCh);

		TVITEM *  it = new TVITEM;
		it->mask = TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM;
		it->pszText = pCh;
		it->cchTextMax = 4;
		it->iImage = 2;
		it->iSelectedImage = 2;
		it->lParam = (DWORD)this;

		vec.insert(vec.end(),it);
		cChildren++;//для верхнего уровня
		GetNodes(W2A(pName),vec,dwcChildren);
		it->cChildren=dwcChildren;
		CoTaskMemFree(pName);
		pName=NULL;
		pEB->Next(1,&pName,&Fetched);		
	}
	
	pEB.Release();
	m_pBrowser->ChangeBrowsePosition(OPC_BROWSE_UP,A2W(""));	
}

//void GetItems()
};




class CTagInfo
{
public:
	void GetTagDef(TagDefStruct * pTagDef,CString Path="");//положить как структурку по указателю

	CTagInfo(){};
	~CTagInfo(){};

	CString m_Name;
	CString m_RealName;
	CString m_Description;
	VARTYPE m_vtVarType;
	DWORD	m_dwAccessRights;
	bool	m_Active;
	DWORD	m_UpdateRate;
	bool	m_NotifyUpdate;
protected:
	
private:
};

#endif // !defined(AFX_CHANNELINFO_H__17D68A3B_3FD5_45D8_A0F0_646EA59209E5__INCLUDED_)
