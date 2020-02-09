// CXMLPlug.cpp : Implementation of CCDDEPlug
#include "stdafx.h"
#include "DDE2OPCPlugin.h"
#include "CDDEPlug.h"
#include <comdef.h>
#include "spacebrowse_i.c"
#include "DMPluginIfs_i.c"
#include <atlcom.h>
//#include ".\asyncxmlread.h"
/////////////////////////////////////////////////////////////////////////////
// CCDDEPlug

//_ATL_FUNC_INFO OnEventInfo = {CC_STDCALL, VT_EMPTY, 0};

//void __stdcall CCDDEPlug::ondataavailable ( )
//{
//	//::PostMessage(m_hwndPostWindow, WM_DATA_AVAILABLE, 0, 0);
//	XMLAvail=true;
//}
//
//void __stdcall CCDDEPlug::onreadystatechange ( )
//{
////	::PostMessage(m_hwndPostWindow, WM_READYSTATE_CHANGE, 0, 0);
//	XMLReady=true;
//}


_variant_t CCDDEPlug::GetParameter(const _bstr_t ParamName,std::vector<ParametersVal> &ParVal)
{
	_variant_t val;
	std::vector<ParametersVal>::iterator itv;
	bool IsFlag=false;
	for(itv=ParVal.begin();itv!=ParVal.end();++itv)
	{
		if (itv->ParamName==ParamName)
		{
			val=itv->ParamValue;
			IsFlag=true;
			break;
		}
	}

	if (!IsFlag)
	{
		VariantInit(&val);//устанавливаем VT_EMPTY
	}

	return val;
}
bool CCDDEPlug::ParseInitializationString(const _bstr_t InitString,std::vector<ParametersVal> &ParamStruct)
{
	
	const char	Ex[]=";= \n\b\f\r\0";//символы для поиска
	std::string ConfStr=(char*)InitString;
//	std::string::iterator ItStrF,ItStrL;
	int x,x1,x2;
	while ((x=ConfStr.find_first_not_of(Ex))>=0)
	{
		ConfStr=ConfStr.substr(x);
		//Получение названия параметра
		x1=ConfStr.find_first_of(Ex);
		ParametersVal MyVal;
		if (x1!=-1)//npos
		{
			MyVal.ParamName=ConfStr.substr(0,x1).c_str();
			ConfStr=ConfStr.substr(x1);
		}	
		else break;
		
		x=ConfStr.find_first_of(';');
		//x2=ConfStr.length()-2;
		x2=ConfStr.find_first_of('=');
		if((x<x2)&&(x!=-1)) continue;
		//получение значения параметра
		if ((x=ConfStr.find_first_not_of(Ex))>=0)
		{
			ConfStr=ConfStr.substr(x);
			if((x1=ConfStr.find_first_of(Ex))>=0)
			{
				MyVal.ParamValue=ConfStr.substr(0,x1).c_str();
				ConfStr=ConfStr.substr(x1);
			}
			else 
				if (ConfStr.length()>0) {
					MyVal.ParamValue=ConfStr.substr(0).c_str();
					ConfStr="";
				}
				
		}
		ParamStruct.insert(ParamStruct.begin(),MyVal);
		
	}
	
	int l=ParamStruct.size();
	return true;
	
	
};




STDMETHODIMP CCDDEPlug::SetFullLogFileName(BSTR LogFileName)
{
	USES_CONVERSION;
	m_LogFile.SetNewFullLogName(W2A(LogFileName));
	
	return S_OK;
}
STDMETHODIMP CCDDEPlug::GetBrowser(IUnknown**pBrowUnk)
{
	if (!IsConfigured) return S_FALSE;

	CComObjectNoLock<CBrowseObj>* pBrowse=new CComObjectNoLock<CBrowseObj>;
	ATLTRACE("Вызов GetBrowser плагина\n");

//	pBrowse->m_XMLPath = m_XMLPath;
//	pBrowse->m_Doc=m_Doc;
	
//	_variant_t vout((bool)TRUE);
//	vout=pBrowse->m_Doc->load(_bstr_t(m_XMLPath.c_str()));
	pBrowse->FinalConstruct();
	*pBrowUnk=pBrowse->GetUnknown();

	return S_OK;
}

//##ModelId=3C4E3C7803E0
STDMETHODIMP CCDDEPlug::AddNotifyTags(ITEMID *ClientTagID, DWORD dwCount, DWORD dwUpdateRate, HRESULT **pError)
{
//return E_FAIL;
	if (!IsConfigured)//если не сконфигурирован
		return E_FAIL;
	HRESULT hr=E_NOTIMPL;
	return hr;
}

//##ModelId=3C4E3C7803D5
STDMETHODIMP CCDDEPlug::DelNotifyTags(ITEMID *ClientTagID, DWORD dwCount)
{

	// TODO: Add your implementation code here
	if (!IsConfigured)//если не сконфигурирован
		return E_FAIL;
	
	return E_NOTIMPL;
}

//##ModelId=3C4E3C7803C3
STDMETHODIMP CCDDEPlug::Configure(BSTR CnfgString)
{
	HRESULT hr=S_OK;
	USES_CONVERSION;
	m_LogFile.ChangeMode();
	m_LogFile<<"===============================";
	m_LogFile<<"Конфигурация плагина DDE2OPC.";
	m_LogFile<<std::string(std::string("Строка конфигураци: ")+W2A(CnfgString)).c_str();
	m_LogFile.ChangeMode();
	ConfigString = CnfgString;
	MyParams.clear();
	ParseInitializationString(CnfgString,MyParams);
	if (DMLERR_NO_ERROR!=InitDDE())
		return E_FAIL; //вываливаемся из программы, если не инифиализировали корректно

	_variant_t svcVAR=GetParameter("Service",MyParams);
	std::string Svc=(char*)(_bstr_t)svcVAR;
	_variant_t tpcVAR=GetParameter("Topic",MyParams);
	std::string Tpc=(char*)(_bstr_t)tpcVAR;
	HSZ m_DDESvcName=DdeCreateStringHandle(m_dwDDEInst,Svc.c_str(),CP_WINANSI);
	if (m_DDESvcName==0)
	{
		ATLTRACE("Error in create string handle for service.");
		goto exit_;
	}
	
	HSZ m_DDETopicName=DdeCreateStringHandle(m_dwDDEInst,Tpc.c_str(),CP_WINANSI);
	if (m_DDETopicName==0)
	{
		ATLTRACE("Error in create string handle for Topic.");
		goto exit_;
	}

	//ПОДКЛЮЧАЕМСЯ!
	m_hDDEConv=DdeConnect(m_dwDDEInst,m_DDESvcName,m_DDETopicName,NULL);
	if (m_hDDEConv==0)
	{
		ATLTRACE("Error in connect");
		goto exit_;
	} 
this->IsConfigured = true;
m_Inited=true;
	return S_OK;


	exit_:
	
	
		if (m_hDDEConv!=0)
			DdeDisconnect(m_hDDEConv);
		if (m_DDESvcName!=0)
			DdeFreeStringHandle(m_dwDDEInst,m_DDESvcName);

		if (m_DDETopicName!=0)
			DdeFreeStringHandle(m_dwDDEInst,m_DDETopicName);


		DeInitDDE();
	
		this->IsConfigured = false;
		m_Inited=false;
	//_variant_t pathxml=GetParameter("XMLURL",MyParams);
	//bSendDT=false;
	//bSendDT = (long)GetParameter("SENDDT",MyParams);
	//m_XMLPath=(char*)(_bstr_t)pathxml;
	//hr=m_Doc.CreateInstance("msxml2.domdocument");
	//if(SUCCEEDED(hr))
	//{
	//	_variant_t varAsync((bool)FALSE);
	//	m_Doc->async=VARIANT_FALSE;//режим синхронной закачки XML документа.
	//	_variant_t outVal((bool)FALSE);
	//	try{
	//	
	//		outVal=m_Doc->load(m_XMLPath.c_str());
	//		
	//	}catch(_com_error &e)
	//	{
	//		hr=e.Error();
	//		std::string errs="ERROR: Ошибка при загрузке документа "+m_XMLPath;
	//		m_LogFile<<errs.c_str();
	//		m_LogFile<<e.Description();
	//		m_Doc.Release();
	//	}
	//	if (outVal==_variant_t((bool)FALSE))//если не закачал
	//	{
	//		hr=E_FAIL;
	//		m_LogFile<<"Не загрузили документ XML!";
	//		if (!(m_Doc==NULL))
	//			m_Doc.Release();
	//	}
	//	else
	//		IsConfigured=true;


	//}else
	//{
	//	m_LogFile<<hr;
	//	m_LogFile<<"Ошибка при создании экземпляра XMLParser.";
	//	IsConfigured=false;
	//}

	return hr;
}

//##ModelId=3C4E3C7803C1
STDMETHODIMP CCDDEPlug::Reset()
{
	if (!IsConfigured) return S_OK;
	m_LogFile<<"Сброс конфигурации плагина!";
	//todo: Реализовать сброс конфигурации
		if (m_hDDEConv!=0)
			DdeDisconnect(m_hDDEConv);
		if (m_DDESvcName!=0)
			DdeFreeStringHandle(m_dwDDEInst,m_DDESvcName);

		if (m_DDETopicName!=0)
			DdeFreeStringHandle(m_dwDDEInst,m_DDETopicName);


		DeInitDDE();

	//	Configure(ConfigString.GetBSTR());

	return S_OK;
}



//##ModelId=3C4E3C7803A3
STDMETHODIMP CCDDEPlug::GetTags(ITEMID *ClientTagID, DWORD dwCount, OPCITEMSTATE **pOutStruct, HRESULT **ppErrors)
{
	
	//void * d=CoTaskMemAlloc(100000);
	HRESULT hr=S_OK;
	try{
	USES_CONVERSION;
	std::string EN;
	if (dwCount>0)
	{
		char bbf[30];
		EN=_ltoa((long)ClientTagID->hClient,bbf,10);
	}else
	{
		EN="UNKNOWN_TAG_ID";
	}
	m_LogFile<<EN.c_str();


	if (!IsConfigured)//если не сконфигурирован
	{
		if (ConfigString!=_bstr_t(""))
		{
			CheckAllErrors();
		}
		return E_FAIL;
	}
		
	


	
	//здесь уже разбирать будем
	try{

	SYSTEMTIME st;
	FILETIME ft;
	GetLocalTime(&st);
	SystemTimeToFileTime(&st,&ft);
	*pOutStruct=(OPCITEMSTATE*)CoTaskMemAlloc(sizeof(OPCITEMSTATE)*dwCount);
	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	_bstr_t sss;
	BOOL AllError=FALSE;
	for(int i=0;i<dwCount;i++)
	{	
		DWORD x=0;
		BYTE *pB=NULL;
		bool isNormal=true;
		bool IsError=true;
		HDDEDATA xdata=0;
	
	//	try{
	
		_bstr_t vn((ClientTagID+i)->ItemName,true);
		HSZ ValName=DdeCreateStringHandle(m_dwDDEInst,(char*)vn,CP_WINANSI);
		if (ValName!=0)
		{
			
			//continue;
			xdata=DdeClientTransaction(NULL,0,m_hDDEConv,ValName,CF_TEXT,XTYP_REQUEST,1000,&x);
			if (xdata==0)
			{
				DWORD code=DdeGetLastError(m_dwDDEInst);
				ATLTRACE("Error in DATA! 0x%xh\n",code);
			}
			else
			{
				pB= DdeAccessData(  xdata,&x);
				if (pB==NULL)
				{
					DWORD xx=DdeGetLastError(m_dwDDEInst);
				}
				

			}
		}else
		{
			ATLTRACE("Error in create string handle for value.");
			DWORD ret=DdeGetLastError(m_dwDDEInst);
		}

	
		
		
		bool IsERROR = false;
		if (pB)
		{
			try{
					((*pOutStruct)+i)->hClient=(ClientTagID+i)->hClient;
					///*_bstr_t sss(*/ml->item[0l]->text/*)*/;
					std::string vvv= this->ChangeFloatString(/*(char*)sss*/(char*)pB);
					sss = (char *)vvv.c_str();
					((*pOutStruct)+i)->vDataValue =_variant_t( sss).Detach();
					//SysFreeString(sss.Detach());
					((*pOutStruct)+i)->ftTimeStamp=ft;
					((*pOutStruct)+i)->wQuality=OPC_QUALITY_GOOD;
					((*pOutStruct)+i)->wReserved=0;
					*((*ppErrors)+i)=S_OK;
					AllError|=TRUE;
			}catch(...)
			{
				IsERROR=true;
				ATLTRACE("ERROR in data conversation!");
				m_LogFile<<"ERROR in data conversation!";
			}

			DdeUnaccessData( xdata);
			DdeFreeDataHandle(xdata);
		}
		else
		{
			IsERROR=true;
		}

		if (IsERROR)
		{
			VariantInit(&((*pOutStruct)+i)->vDataValue);
			hr=S_FALSE;
			*((*ppErrors)+i)=E_FAIL;

		}
		DdeFreeStringHandle(m_dwDDEInst,ValName);

	}

	if (!AllError)
	{
		if ((++this->m_AllErrorsCount)==3)
		{
				CheckOnDisconnect();
				this->m_AllErrorsCount=0;
		}
	}
	}catch(...)
	{
		ATLTRACE("ERROR Ошибка в функции чтения тегов!");
        m_LogFile<<"ERROR: Ошибка в функции чтения тегов!";
		if (*pOutStruct)
		{
			CoTaskMemFree(*pOutStruct);
			*pOutStruct=NULL;
		}
		if (*ppErrors)
		{
			CoTaskMemFree(*ppErrors);
			*ppErrors=NULL;
		}
	}
	//xxxDD.Release();
	//m_LogFile<<"О";
	}catch(...)
	{
		if (*pOutStruct)
		{
			CoTaskMemFree(*pOutStruct);
			*pOutStruct=NULL;
		}
		if (*ppErrors)
		{
			CoTaskMemFree(*ppErrors);
			*ppErrors=NULL;
		}
			m_LogFile<<" ERROR:	Глобальная неопознанная ошибка!!!";
				hr=E_FAIL;
	}
	return hr;
}

//##ModelId=3C4E3C780386
STDMETHODIMP CCDDEPlug::SetTags(ITEMID *ClientTagID, DWORD Count, VARIANT *pItemValues, HRESULT **ppErrors)
{
	USES_CONVERSION;
	if (!IsConfigured)//если не сконфигурирован
		return E_FAIL;
	HRESULT hr=E_NOTIMPL;
	return hr;
}

//##ModelId=3C4E3C78037C
STDMETHODIMP CCDDEPlug::GetState(DWORD State)
{
	// TODO: Add your implementation code here
	if (!IsConfigured)//если не сконфигурирован
		return E_FAIL;

	return S_OK;
}


//##ModelId=3C4E3C780371
STDMETHODIMP CCDDEPlug::GetExampleCnfg(BSTR *bstrExampleCnfg)
{
	_bstr_t x;
	//x="XMLURL=http://asu-meteo/users.xml;SENDDT=0";
	x="Service=Excel;Topic=[Bok_My.xls]LIST;";
	*bstrExampleCnfg=x.copy();

	return S_OK;
}


	STDMETHODIMP CBrowseObj::BrowseAccessPaths(/*[in]*/LPCWSTR szItemID,/*[out]*/ LPENUMSTRING *ppIEnumString)
	{
		return E_NOTIMPL;
	}
	STDMETHODIMP CBrowseObj::GetItemID(/*[in]*/LPCWSTR szItemDataID, /*[out]*/LPWSTR *szItemID)
	{
		//пока работаем только с узлами
//	USES_CONVERSION;
//		std::string xid=W2A(szItemDataID);
//		int pos=xid.find("_x@x_");
//		if (pos!=-1)
//		{
//			xid.replace(pos,5,"/@",2);
//		}
//		std::string x=m_CurPath;
//		x+=std::string("/")+/*W2A(szItemDataID)*/xid;
	//	*szItemID =(LPWSTR)CoTaskMemAlloc(0); 
//		wcscpy(*szItemID,A2W(x.c_str()));
return E_NOTIMPL;

//return S_OK;
	}
	STDMETHODIMP CBrowseObj::BrowseOPCItemIDs(/*[in]*/ OPCBROWSETYPE  dwBrowseFilterType,/*[in]*/ LPCWSTR  szFilterCriteria, /*[in]*/ VARTYPE   vtDataTypeFilter, /*[in]*/ DWORD    dwAccessRightsFilter,	/*[out]*/ LPENUMSTRING	* ppIEnumString)
	{
		if (ppIEnumString == NULL)
			return E_POINTER;
		return E_NOTIMPL;
	//	std::vector<LPOLESTR> strvec;
		
//	USES_CONVERSION;
//	long i=0;
//	MSXML2::IXMLDOMNodeListPtr m_nodel;
//	MSXML2::IXMLDOMNamedNodeMapPtr m_attnodel;
//	LPOLESTR olestr;
//	typedef CComObjectNoLock<CComEnum<IEnumString,&IID_IEnumString,LPOLESTR,_Copy<LPOLESTR> > > Enum;
//	Enum * p = new Enum;
//	HRESULT hr=S_OK;
//	std::string xx;
//		switch(dwBrowseFilterType)
///		{
//		case OPC_BRANCH://ищем узлы
//
//	
//			
//			if (m_CurNode==NULL) 
//			{
//				m_Element=m_Doc->documentElement;
//				_bstr_t txml=m_Doc->xml;
//				try{
//				
//				m_nodel=m_Doc->childNodes;
//				}catch(_com_error &e)
//				{
//					int x=0;
//				}
//			}
//			else
//			{
//				m_nodel=m_CurNode->childNodes;
//				
//			}
//			
//			for( i=0;i<m_nodel->length;i++)
		//	{
		//		
		//		if (m_nodel->item[i]->childNodes->length>0)
		//		{
		//			if (m_nodel->item[i]->childNodes->item[0]->nodeType==MSXML2::NODE_ELEMENT)
		//			{
		//				_bstr_t x=m_nodel->item[i]->nodeName;
		//				bool Is=false;
		//				for(int xyz=0;xyz!=strvec.size();xyz++)
		//					if (x==_bstr_t(W2A(strvec[xyz])))
		//					{
		//						Is=true;
		//						break;
		//					}
		//					
		//					if (Is) continue;
		//					
		//				olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((x.length()+1)));
		//				wcscpy(olestr,A2W(x));
		//				strvec.insert(strvec.end(),olestr);
		//			}
		//		}
		//	}
		//	if (p==NULL) hr= E_OUTOFMEMORY;
		//	else
		//	{
		//		hr=p->FinalConstruct();
		//		if (hr==S_OK)
		//		{
		//			hr=p->Init(&strvec[0],&strvec[strvec.size()],NULL,AtlFlagCopy);
		//			if (hr==S_OK)
		//			{
		//				hr=p->QueryInterface(IID_IUnknown,(void**)ppIEnumString);
		//			}
		//		}
		//	}
		//	if (hr!=S_OK)
		//		delete p;
		//										
		//	break;
		//case OPC_LEAF://ищем листья
		//	
		//	
		//	
		//	if (m_CurNode==NULL) 
		//	{
		//		m_Element=m_Doc->documentElement;
		//		
		//		m_nodel=m_Doc->childNodes;
		//	}
		//	else
		//	{
		//		m_nodel=m_CurNode->childNodes;
		//	}
		//	
		//	for( i=0;i<m_nodel->length;i++)
		//	{
		//		
		//		if (m_nodel->item[i]->childNodes->length>0)
		//		{
		//			if (m_nodel->item[i]->childNodes->item[0]->nodeType!=MSXML2::NODE_ELEMENT)
		//			{
		//				_bstr_t x=m_nodel->item[i]->nodeName;
		//				
		//				bool Is=false;
		//				for(int xyz=0;xyz!=strvec.size();xyz++)
		//					if (x==_bstr_t(W2A(strvec[xyz])))
		//					{
		//						Is=true;
		//						break;
		//					}
		//					
		//					if (Is) continue;
		//					
		//				
		//					olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((x.length()+1)));
		//					wcscpy(olestr,A2W(x));
		//					strvec.insert(strvec.end(),olestr);
		//			}
		//		}else //если последний в иерархии
		//		{
		//			m_attnodel=m_nodel->item[i]->attributes;
		//			for(long ii=0;ii<m_attnodel->length;ii++)
		//			{
		//				
		//				_bstr_t x=m_nodel->item[i]->nodeName;
		//				x=x+"_x@x_"+m_attnodel->item[ii]->nodeName;

		//				bool Is=false;

		//				for(int xyz=0;xyz!=strvec.size();xyz++)
		//					if (x==_bstr_t(W2A(strvec[xyz])))
		//					{
		//						Is=true;
		//						break;
		//					}
		//					
		//				if (Is) break;
		//					
		//				olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((x.length()+1)));
		//				wcscpy(olestr,A2W(x));
		//				strvec.insert(strvec.end(),olestr);
		//			}
		//			
		//		}

		//	}


		//	//теперь добавим свойства
		//	m_attnodel=m_CurNode->attributes;
		//	for( i=0;i<m_attnodel->length;i++)
		//	{
		//		
		//		_bstr_t x="@";
		//			x=x+m_attnodel->item[i]->nodeName;
		//						
		//		olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((x.length()+1)));
		//		wcscpy(olestr,A2W(x));
		//		strvec.insert(strvec.end(),olestr);
		//	}
		//	
		//	if (p==NULL) hr= E_OUTOFMEMORY;
		//	else
		//	{
		//		hr=p->FinalConstruct();
		//		if (hr==S_OK)
		//		{
		//			hr=p->Init(&strvec[0],&strvec[strvec.size()],NULL,AtlFlagCopy);
		//			if (hr==S_OK)
		//			{
		//				hr=p->QueryInterface(IID_IUnknown,(void**)ppIEnumString);
		//			}
		//		}
		//	}
		//	if (hr!=S_OK)
		//		delete p;
		//	break;
		//case OPC_FLAT://все вместе
		//	break;// TODO: Реализовать
		//default:
		//	return E_INVALIDARG;
		//}
		return S_OK;
	}
	STDMETHODIMP CBrowseObj::ChangeBrowsePosition(/*[in]*/ OPCBROWSEDIRECTION dwBrowseDirection,/*[in]*/ LPCWSTR  szString)
	{
		return E_NOTIMPL;
		
//		USES_CONVERSION;
//		std::string str,curstr;
//		int pos=-1;
//		MSXML2::IXMLDOMNodeListPtr m_nodel;
	//	MSXML2::IXMLDOMNodePtr Nod;
	//	std::string x;
	//	switch(dwBrowseDirection)
	//	{
	//	case OPC_BROWSE_UP://подняться на одну ступень вверх
	//		if (m_CurPath=="")	return E_FAIL;
	//		if (m_CurNode==NULL) return E_FAIL;
	//		x=(char*)m_CurNode->nodeName;
	//		if ((pos=m_CurPath.rfind("/"))!=-1)
	//			m_CurPath.replace(pos,x.length()+1,"");
	//		
	//		Nod=m_CurNode->parentNode;
	//		m_CurNode=Nod;//переместили, теперь нужно 

	//		break;
	//	case OPC_BROWSE_DOWN:
	//		if (std::string(W2A(szString))!="")
	//		{
	//			x=m_CurPath;
	//			if (x!="")	x=x+"/"+W2A(szString);
	//			else
	//				x=x+W2A(szString);
	//			m_nodel=m_Doc->getElementsByTagName(_bstr_t(x.c_str()));
	//			if (m_nodel->length>0l)
	//			{
	//				m_CurNode=m_nodel->item[0];
	//				m_CurPath=x;
	//			}
	//		}
	//		break;
	//	case OPC_BROWSE_TO:
	//		//Выделим путь
	//		if (std::string(W2A(szString))!="")
	//		{
	//			std::string xs=W2A(szString);
	//			int pos=-1;
	//			while ((pos=xs.find("."))!=-1)
	//				xs.replace(pos,1,sizeof(char),'/');
	//			
	//			m_nodel=m_Doc->getElementsByTagName(xs.c_str());
	//			if (m_nodel->length>0l)
	//			{
	//				m_CurNode=m_nodel->item[0l];
	//				m_CurPath=xs;
	//			}
	//		}
	//		
	//		break;
	//	default:
	//		return E_INVALIDARG;
	//	}

	//return S_OK;
	}
	STDMETHODIMP CBrowseObj::QueryAvailableProperties(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR **ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes)
	{//доступные свойства итемов

		//USES_CONVERSION;
		return E_NOTIMPL;
	}
	STDMETHODIMP CBrowseObj::GetItemProperties(/*[in]*/ BSTR ItemID,/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ DWORD * pdwPropertyIDs,/*[out, size_is(,dwCount)] */VARIANT ** ppvData,/*[out, size_is(,dwCount)]*/ HRESULT **ppErrors)
	{
		return /*OPC_E_UNKNOWNITEMID*/E_NOTIMPL;
	}


STDMETHODIMP CBrowseObj::ValidateItem(DWORD dwCount, OPCITEMDEF *pItemArray, BOOL bBlobUpdate, OPCITEMRESULT **ppValidationResults, HRESULT **ppErrors)
{
	
	return E_NOTIMPL;
}

