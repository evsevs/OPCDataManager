// CXMLPlug.cpp : Implementation of CCXMLPlug
#include "stdafx.h"
#include "XML2OPCPlugin.h"
#include "CXMLPlug.h"
#include <comdef.h>
#include "spacebrowse_i.c"
#include "DMPluginIfs_i.c"
#include <atlcom.h>
/////////////////////////////////////////////////////////////////////////////
// CCXMLPlug

_ATL_FUNC_INFO OnEventInfo = {CC_STDCALL, VT_EMPTY, 0};

void __stdcall CCXMLPlug::ondataavailable ( )
{
	//::PostMessage(m_hwndPostWindow, WM_DATA_AVAILABLE, 0, 0);
	XMLAvail=true;
}

void __stdcall CCXMLPlug::onreadystatechange ( )
{
//	::PostMessage(m_hwndPostWindow, WM_READYSTATE_CHANGE, 0, 0);
	XMLReady=true;
}


_variant_t CCXMLPlug::GetParameter(const _bstr_t ParamName,std::vector<ParametersVal> &ParVal)
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
bool CCXMLPlug::ParseInitializationString(const _bstr_t InitString,std::vector<ParametersVal> &ParamStruct)
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




STDMETHODIMP CCXMLPlug::SetFullLogFileName(BSTR LogFileName)
{
	USES_CONVERSION;
	m_LogFile.SetNewFullLogName(W2A(LogFileName));
	
	return S_OK;
}
STDMETHODIMP CCXMLPlug::GetBrowser(IUnknown**pBrowUnk)
{
	if (!IsConfigured) return S_FALSE;

	CComObjectNoLock<CBrowseObj>* pBrowse=new CComObjectNoLock<CBrowseObj>;
	ATLTRACE("Вызов GetBrowser плагина\n");

	pBrowse->m_XMLPath = m_XMLPath;
	pBrowse->m_Doc=m_Doc;
	
	_variant_t vout((bool)TRUE);
	vout=pBrowse->m_Doc->load(_bstr_t(m_XMLPath.c_str()));
	pBrowse->FinalConstruct();
	*pBrowUnk=pBrowse->GetUnknown();

	return S_OK;
}

//##ModelId=3C4E3C7803E0
STDMETHODIMP CCXMLPlug::AddNotifyTags(ITEMID *ClientTagID, DWORD dwCount, DWORD dwUpdateRate, HRESULT **pError)
{
//return E_FAIL;
	if (!IsConfigured)//если не сконфигурирован
		return E_FAIL;
	HRESULT hr=S_OK;
	return hr;
}

//##ModelId=3C4E3C7803D5
STDMETHODIMP CCXMLPlug::DelNotifyTags(ITEMID *ClientTagID, DWORD dwCount)
{

	// TODO: Add your implementation code here
	if (!IsConfigured)//если не сконфигурирован
		return E_FAIL;
	
	return S_OK;
}

//##ModelId=3C4E3C7803C3
STDMETHODIMP CCXMLPlug::Configure(BSTR CnfgString)
{
	HRESULT hr=S_OK;
	USES_CONVERSION;
	m_LogFile.ChangeMode();
	m_LogFile<<"===============================";
	m_LogFile<<"Конфигурация плагина XML2OPC.";
	m_LogFile<<std::string(std::string("Строка конфигураци: ")+W2A(CnfgString)).c_str();
	m_LogFile.ChangeMode();
	


	ParseInitializationString(CnfgString,MyParams);
	_variant_t pathxml=GetParameter("XMLURL",MyParams);
	bSendDT=false;
	bSendDT = (long)GetParameter("SENDDT",MyParams);
	m_XMLPath=(char*)(_bstr_t)pathxml;
	hr=m_Doc.CreateInstance("msxml2.domdocument");
	if(SUCCEEDED(hr))
	{
		_variant_t varAsync((bool)FALSE);
		m_Doc->async=VARIANT_FALSE;//режим синхронной закачки XML документа.
		_variant_t outVal((bool)FALSE);
		try{
		
			outVal=m_Doc->load(m_XMLPath.c_str());
			
		}catch(_com_error &e)
		{
			hr=e.Error();
			std::string errs="ERROR: Ошибка при загрузке документа "+m_XMLPath;
			m_LogFile<<errs.c_str();
			m_LogFile<<e.Description();
			m_Doc.Release();
		}
		if (outVal==_variant_t((bool)FALSE))//если не закачал
		{
			hr=E_FAIL;
			m_LogFile<<"Не загрузили документ XML!";
			if (!(m_Doc==NULL))
				m_Doc.Release();
		}
		else
			IsConfigured=true;


	}else
	{
		m_LogFile<<hr;
		m_LogFile<<"Ошибка при создании экземпляра XMLParser.";
		IsConfigured=false;
	}

	return hr;
}

//##ModelId=3C4E3C7803C1
STDMETHODIMP CCXMLPlug::Reset()
{
	if (!IsConfigured) return S_OK;
	m_LogFile<<"Сброс конфигурации плагина!";
	return S_OK;
}



//##ModelId=3C4E3C7803A3
STDMETHODIMP CCXMLPlug::GetTags(ITEMID *ClientTagID, DWORD dwCount, OPCITEMSTATE **pOutStruct, HRESULT **ppErrors)
{
	m_LogFile<<"Запрос";
	USES_CONVERSION;
	HRESULT hr=S_OK;
	MSXML2::IXMLDOMDocumentPtr xxxDD;

	//m_LogFile<<"!";
	bool isNormalLoaded=true;
	try{

	if (!IsConfigured)//если не сконфигурирован
		return E_FAIL;
	
	_variant_t outVal((bool)FALSE);
	try{
		hr=xxxDD.CreateInstance("Msxml2.DOMDocument.3.0");//("msxml2.domdocument");
		std::string newpath;
	if ((bSendDT)&&(this->SendTimeCounter==97))
	{
		//DDMMYYYYHHIISS 
		SYSTEMTIME st;
		GetLocalTime(&st);
		char yx[20];
		char xy[20];
		::GetDateFormat( LOCALE_USER_DEFAULT,0,&st,"ddMMyyyy",yx,20);
		::GetTimeFormat( LOCALE_USER_DEFAULT,0,&st,"HHmmss",xy,20);
		newpath=m_XMLPath + "/?time=";
		newpath+=std::string(yx)+std::string(xy);
		SendTimeCounter	=0;
	}else
		newpath = m_XMLPath;

	//m_Doc->async=VARIANT_FALSE;
//===================================================================================
//===================================================================================
//===============АСИНХРОННАЯ ЗАГРУЗКА ДОКУМЕТА===========================
//===================================================================================
//===================================================================================
	{
	//xxxDD->async=(bool)true;
	//	m_Doc->async=VARIANT_TRUE;
	//outVal=m_Doc->load(newpath.c_str());
	xxxDD->async=VARIANT_TRUE;
	XMLReady=false;
	DWORD m_dwAdviseCookie=0;
	IUnknown * pUnkX = NULL;
	this->QueryInterface(IID_IUnknown,(void**)&pUnkX);
	AtlAdvise(xxxDD,pUnkX , __uuidof(MSXML2::XMLDOMDocumentEvents), &m_dwAdviseCookie);
	outVal=xxxDD->load(newpath.c_str());

	long AsyncResult=0l;
	//1 - LOADING
	//2- LOADED
	//3- INTERACTIVE
	//4-COMPLETED
	//m_LogFile<<outVal;
	bool isTimeout=false;
	long xCount=0;
	//HRESULT hr=xxxDD->get_readyState(&AsyncResult);
	 

	while (!XMLReady)//AsyncResult!=(long)4)
	{   hr=xxxDD->get_readyState(&AsyncResult);
		Sleep(100);
		xCount+=100;
		if (xCount>=AsyncTimeout*10)
		{
			isTimeout=true;
			break;
		}
		char buf[300];
		sprintf(buf,"%s %s=%d","WARNING!: В цикле. Состояние ",newpath.c_str(),(long)AsyncResult);
		m_LogFile<<buf;
	}

	if (isTimeout)
	{
		xxxDD->abort();
		m_LogFile<<"ERROR: Таймаут при асинхронном чтении.";
		outVal=VARIANT_FALSE;
		isNormalLoaded=false;
	}

	}
//===================================================================================
//===================================================================================
//===================================================================================
//===================================================================================
//===================================================================================
		
	SendTimeCounter++;
	}catch(...)
	{
		//ATLTRACE("ERROR1 %s\n",m_XMLPath.c_str());
	//	return E_FAIL;
		isNormalLoaded=false;
		outVal=VARIANT_FALSE;
	}

	if ((outVal==_variant_t((bool)FALSE))&&(!isNormalLoaded))
	{
		HRESULT xxf=E_FAIL;
		try{
			_com_issue_error(xxf);
			//_com_error(xxf);
		}
		catch(_com_error &e)
		{
			std::string erstr="ERROR: Ошибка при загрузке документа "+m_XMLPath;
			m_LogFile<<e.ErrorMessage();
			m_LogFile<<e.Description();

			*pOutStruct=NULL;
			this->m_LogFile<<erstr.c_str();
			*ppErrors=NULL;
		}
	//	m_LogFile<<"Ответ (error)";
		return E_FAIL;
	}

	
	//здесь уже разбирать будем
	SYSTEMTIME st;
	FILETIME ft;
	GetLocalTime(&st);
	SystemTimeToFileTime(&st,&ft);
	MSXML2::IXMLDOMNodeListPtr ml;
	*pOutStruct=(OPCITEMSTATE*)CoTaskMemAlloc(sizeof(OPCITEMSTATE)*dwCount);
	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	for(int i=0;i<dwCount;i++)
	{
		bool isNormal=true;

		try{
		//	ml=m_Doc->getElementsByTagName((ClientTagID+i)->ItemName);
			ml=xxxDD->getElementsByTagName((ClientTagID+i)->ItemName);

		}catch(...)
		{
			isNormal=false;
			_bstr_t tb((ClientTagID+i)->ItemName,true);
			_bstr_t errs="ERROR: Не найден тег с именем "+tb;
			m_LogFile<<(char*)errs;
		}
		if ((ml->length>0l)&&(isNormal))
		{
			((*pOutStruct)+i)->hClient=(ClientTagID+i)->hClient;
			_bstr_t sss(ml->item[0l]->text);
			std::string vvv= this->ChangeFloatString((char*)sss);
			sss = (char *)vvv.c_str();
			((*pOutStruct)+i)->vDataValue =_variant_t( sss).Detach();
			((*pOutStruct)+i)->ftTimeStamp=ft;
			((*pOutStruct)+i)->wQuality=OPC_QUALITY_GOOD;
			((*pOutStruct)+i)->wReserved=0;
			*((*ppErrors)+i)=S_OK;
		}
		else
		{
			VariantInit(&((*pOutStruct)+i)->vDataValue);
			hr=S_FALSE;
			*((*ppErrors)+i)=E_FAIL;
		}
	}
	}catch(...)
	{
		ATLTRACE("ERROR %s\n",m_XMLPath.c_str());
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
	xxxDD.Release();
	m_LogFile<<"Ответ";
	return hr;
}

//##ModelId=3C4E3C780386
STDMETHODIMP CCXMLPlug::SetTags(ITEMID *ClientTagID, DWORD Count, VARIANT *pItemValues, HRESULT **ppErrors)
{
	USES_CONVERSION;
	if (!IsConfigured)//если не сконфигурирован
		return E_FAIL;
	HRESULT hr=E_NOTIMPL;
	return hr;
}

//##ModelId=3C4E3C78037C
STDMETHODIMP CCXMLPlug::GetState(DWORD State)
{
	// TODO: Add your implementation code here
	if (!IsConfigured)//если не сконфигурирован
		return E_FAIL;

	return S_OK;
}


//##ModelId=3C4E3C780371
STDMETHODIMP CCXMLPlug::GetExampleCnfg(BSTR *bstrExampleCnfg)
{
	_bstr_t x;
	x="XMLURL=http://asu-meteo/users.xml;SENDDT=0";
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
	USES_CONVERSION;
		std::string xid=W2A(szItemDataID);
		int pos=xid.find("_x@x_");
		if (pos!=-1)
		{
			xid.replace(pos,5,"/@",2);
		}
		std::string x=m_CurPath;
		x+=std::string("/")+/*W2A(szItemDataID)*/xid;
		*szItemID =(LPWSTR)CoTaskMemAlloc(sizeof(wchar_t)*(x.size()+1)); 
		wcscpy(*szItemID,A2W(x.c_str()));


return S_OK;
	}
	STDMETHODIMP CBrowseObj::BrowseOPCItemIDs(/*[in]*/ OPCBROWSETYPE  dwBrowseFilterType,/*[in]*/ LPCWSTR  szFilterCriteria, /*[in]*/ VARTYPE   vtDataTypeFilter, /*[in]*/ DWORD    dwAccessRightsFilter,	/*[out]*/ LPENUMSTRING	* ppIEnumString)
	{
		if (ppIEnumString == NULL)
			return E_POINTER;
		std::vector<LPOLESTR> strvec;
		
	USES_CONVERSION;
	long i=0;
	MSXML2::IXMLDOMNodeListPtr m_nodel;
	MSXML2::IXMLDOMNamedNodeMapPtr m_attnodel;
	LPOLESTR olestr;
	typedef CComObjectNoLock<CComEnum<IEnumString,&IID_IEnumString,LPOLESTR,_Copy<LPOLESTR> > > Enum;
	Enum * p = new Enum;
	HRESULT hr=S_OK;
	std::string xx;
		switch(dwBrowseFilterType)
		{
		case OPC_BRANCH://ищем узлы

	
			
			if (m_CurNode==NULL) 
			{
				m_Element=m_Doc->documentElement;
				_bstr_t txml=m_Doc->xml;
				try{
				
				m_nodel=m_Doc->childNodes;
				}catch(_com_error &e)
				{
					int x=0;
				}
			}
			else
			{
				m_nodel=m_CurNode->childNodes;
				
			}
			
			for( i=0;i<m_nodel->length;i++)
			{
				
				if (m_nodel->item[i]->childNodes->length>0)
				{
					if (m_nodel->item[i]->childNodes->item[0]->nodeType==MSXML2::NODE_ELEMENT)
					{
						_bstr_t x=m_nodel->item[i]->nodeName;
						bool Is=false;
						for(int xyz=0;xyz!=strvec.size();xyz++)
							if (x==_bstr_t(W2A(strvec[xyz])))
							{
								Is=true;
								break;
							}
							
							if (Is) continue;
							
						olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((x.length()+1)));
						wcscpy(olestr,A2W(x));
						strvec.insert(strvec.end(),olestr);
					}
				}
			}
			if (p==NULL) hr= E_OUTOFMEMORY;
			else
			{
				hr=p->FinalConstruct();
				if (hr==S_OK)
				{
					hr=p->Init(&strvec[0],&strvec[strvec.size()],NULL,AtlFlagCopy);
					if (hr==S_OK)
					{
						hr=p->QueryInterface(IID_IUnknown,(void**)ppIEnumString);
					}
				}
			}
			if (hr!=S_OK)
				delete p;
												
			break;
		case OPC_LEAF://ищем листья
			
			
			
			if (m_CurNode==NULL) 
			{
				m_Element=m_Doc->documentElement;
				
				m_nodel=m_Doc->childNodes;
			}
			else
			{
				m_nodel=m_CurNode->childNodes;
			}
			
			for( i=0;i<m_nodel->length;i++)
			{
				
				if (m_nodel->item[i]->childNodes->length>0)
				{
					if (m_nodel->item[i]->childNodes->item[0]->nodeType!=MSXML2::NODE_ELEMENT)
					{
						_bstr_t x=m_nodel->item[i]->nodeName;
						
						bool Is=false;
						for(int xyz=0;xyz!=strvec.size();xyz++)
							if (x==_bstr_t(W2A(strvec[xyz])))
							{
								Is=true;
								break;
							}
							
							if (Is) continue;
							
						
							olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((x.length()+1)));
							wcscpy(olestr,A2W(x));
							strvec.insert(strvec.end(),olestr);
					}
				}else //если последний в иерархии
				{
					m_attnodel=m_nodel->item[i]->attributes;
					for(long ii=0;ii<m_attnodel->length;ii++)
					{
						
						_bstr_t x=m_nodel->item[i]->nodeName;
						x=x+"_x@x_"+m_attnodel->item[ii]->nodeName;

						bool Is=false;

						for(int xyz=0;xyz!=strvec.size();xyz++)
							if (x==_bstr_t(W2A(strvec[xyz])))
							{
								Is=true;
								break;
							}
							
						if (Is) break;
							
						olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((x.length()+1)));
						wcscpy(olestr,A2W(x));
						strvec.insert(strvec.end(),olestr);
					}
					
				}

			}


			//теперь добавим свойства
			m_attnodel=m_CurNode->attributes;
			for( i=0;i<m_attnodel->length;i++)
			{
				
				_bstr_t x="@";
					x=x+m_attnodel->item[i]->nodeName;
								
				olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((x.length()+1)));
				wcscpy(olestr,A2W(x));
				strvec.insert(strvec.end(),olestr);
			}
			
			if (p==NULL) hr= E_OUTOFMEMORY;
			else
			{
				hr=p->FinalConstruct();
				if (hr==S_OK)
				{
					hr=p->Init(&strvec[0],&strvec[strvec.size()],NULL,AtlFlagCopy);
					if (hr==S_OK)
					{
						hr=p->QueryInterface(IID_IUnknown,(void**)ppIEnumString);
					}
				}
			}
			if (hr!=S_OK)
				delete p;
			break;
		case OPC_FLAT://все вместе
			break;// TODO: Реализовать
		default:
			return E_INVALIDARG;
		}
		return S_OK;
	}
	STDMETHODIMP CBrowseObj::ChangeBrowsePosition(/*[in]*/ OPCBROWSEDIRECTION dwBrowseDirection,/*[in]*/ LPCWSTR  szString)
	{
		
		
		USES_CONVERSION;
		std::string str,curstr;
		int pos=-1;
		MSXML2::IXMLDOMNodeListPtr m_nodel;
		MSXML2::IXMLDOMNodePtr Nod;
		std::string x;
		switch(dwBrowseDirection)
		{
		case OPC_BROWSE_UP://подняться на одну ступень вверх
			if (m_CurPath=="")	return E_FAIL;
			if (m_CurNode==NULL) return E_FAIL;
			x=(char*)m_CurNode->nodeName;
			if ((pos=m_CurPath.rfind("/"))!=-1)
				m_CurPath.replace(pos,x.length()+1,"");
			
			Nod=m_CurNode->parentNode;
			m_CurNode=Nod;//переместили, теперь нужно 

			break;
		case OPC_BROWSE_DOWN:
			if (std::string(W2A(szString))!="")
			{
				x=m_CurPath;
				if (x!="")	x=x+"/"+W2A(szString);
				else
					x=x+W2A(szString);
				m_nodel=m_Doc->getElementsByTagName(_bstr_t(x.c_str()));
				if (m_nodel->length>0l)
				{
					m_CurNode=m_nodel->item[0];
					m_CurPath=x;
				}
			}
			break;
		case OPC_BROWSE_TO:
			//Выделим путь
			if (std::string(W2A(szString))!="")
			{
				std::string xs=W2A(szString);
				int pos=-1;
				while ((pos=xs.find("."))!=-1)
					xs.replace(pos,1,sizeof(char),'/');
				
				m_nodel=m_Doc->getElementsByTagName(xs.c_str());
				if (m_nodel->length>0l)
				{
					m_CurNode=m_nodel->item[0l];
					m_CurPath=xs;
				}
			}
			
			break;
		default:
			return E_INVALIDARG;
		}

	return S_OK;
	}
	STDMETHODIMP CBrowseObj::QueryAvailableProperties(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR **ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes)
	{//доступные свойства итемов

		USES_CONVERSION;
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

