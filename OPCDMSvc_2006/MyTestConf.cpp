// MyTestConf.cpp : Implementation of CMyTestConf
#include "stdafx.h"
#include "OPCDMSvc_h.h"
#include "MyTestConf.h"
#include <time.h>
//#include <Sddl.h>
//#include <NETCONS.H>
#include <lm.h>
#include <lmerr.h>

//extern bool PhysicalCreatePath(std::string PathToCreate);
/////////////////////////////////////////////////////////////////////////////
// CMyTestConf
CMyTestConf* pMyTestConf;
//HANDLE ConfObjectInitEvent;

STDMETHODIMP CMyTestConf::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMyTestConf
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP CMyTestConf::SaveCurrentConfigToXML(BSTR secondCopyOfXML)
{
	HRESULT hr=E_NOTIMPL;
	//создание XML документа
	MSXML2::IXMLDOMDocumentPtr xmldoc;
	try{
		xmldoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));

		//загрузка шаблона основы документа из ресурсов
		CString OPCDMSvcXMLTemplate;
		OPCDMSvcXMLTemplate.LoadString(IDS_XMLTEMPLATE_SVC);
		//аттачим, что бы затем уничтожить автоматически
		_bstr_t tt(OPCDMSvcXMLTemplate.AllocSysString(),false);
		//загружаем XML из шаблона
		xmldoc->loadXML(tt);
		MSXML2::IXMLDOMNodePtr node=xmldoc->getElementsByTagName("OPCDMSvc")->item[0l];
		//добавление аттрибутов в узел OPCDMSvc документа
		//...
		//MSXML::IXMLDOMNodePtr node=xmldoc->getElementsByTagName("Profile")->item[0l];
		//пока пропустим дополнительные аттрибуты
		

		//добавление child'ов, т.е. каналов
		
		//теперь произведем загрузку всех тегов канала в XML
		std::map<_ChannelID,CCChannelObj*>::iterator itm;
		//цикл по всем тегам в карте канала
		for(itm=this->m_ChannelMap.begin();itm!=this->m_ChannelMap.end();++itm)
		{
			MSXML2::IXMLDOMNodePtr pN=itm->second->Save2XML();
			_bstr_t sss=pN->xml;
			if (!(pN==NULL))
				node->appendChild(pN);
		}
		xmldoc->save(this->m_XMLConfFile.c_str());
		if(! (_bstr_t(secondCopyOfXML)==_bstr_t("")))
			xmldoc->save(secondCopyOfXML);
	}catch(_com_error &e)
	{
		m_LogFile<<"ОШИБКА Ошибка при формированиии основного XML!!!";
		m_LogFile<<e.ErrorMessage();
		m_LogFile<<e.Description();
		hr=E_FAIL;
	}
	catch(...)
	{
		m_LogFile<<"ОШИБКА Неизвестная ошибка при формированиии основного XML!!!";
		hr=E_FAIL;
	}
	return hr;
}
//HRESULT CMyTestConf::GetDMStatus (OPCSERVERSTATUS* pOPCSERVERSTATUS, _ChannelID& pChannelID)
//{
//	return E_NOTIMPL;
//}

HRESULT CMyTestConf::Initialize (_bstr_t CnfgString)
{
	//настроим лог-файл
	//Sleep(3000);
	
	GlobalDebugLog.SetNewFullLogName("c:\\OPCDMGlobalDebugLog.log");
	GetFromRegistry("LogPath");//Должен уже быть там
	PhysicalCreatePath(m_LogFilePath);

	m_LogFile.SetNewLogFile("OPCDMSvc",m_LogFilePath);
	m_LogFile.GenerateLogFile(true,true);

	m_LogFile<<"\n=================Инициализация объекта конфигурации";

	GetFromRegistry("XMLConfFile");
	//_bstr_t ConfigFile="E:\\Prj\\VC++\\OPC\\OPCImpl\\OPCDMSvc\\XML\\OPCDMConfig.xml";
	HRESULT hr=S_OK;
	MSXML2::IXMLDOMDocumentPtr xmldoc;
	try{
		HRESULT hr=xmldoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));
		if (FAILED(hr))
			_com_issue_error(hr);

		xmldoc->async =VARIANT_FALSE;
		xmldoc->load(m_XMLConfFile.c_str());
		MSXML2::IXMLDOMNodeListPtr ChannelList=xmldoc->getElementsByTagName("Channel");

		for(long i=0;i<ChannelList->length;i++)
		{
			//пройдем по всем каналам в XML
			CComObjectNoLock<CCChannelObj> * pChan = new CComObjectNoLock<CCChannelObj>;
			pChan->AddRef();
			//присваеваем каналу его узел
			pChan->m_ChannelCnfgNode = ChannelList->item[i];
			//генерируем ему идентификатор (уникальный 16-битный)
			pChan->set_m_hObjectHandle((DWORD)rand());
			pChan->m_ConfigLogPath=m_LogFilePath;

			std::map<_ChannelID,CCChannelObj*>::iterator itm;
			_ChannelID tid(*pChan);
			//для теста
			m_LogFile<<tid.get_m_sObjectName().c_str();
			m_LogFile<<pChan->get_m_hObjectHandle();
			//добавляем в список каналов
			if ((itm=m_ChannelMap.find(tid))==m_ChannelMap.end())
				m_ChannelMap.insert(std::map<_ChannelID,CCChannelObj*>::value_type((_ChannelID)(*pChan),pChan));
			else
			{
				//если уже есть с таким идентификатором
				m_LogFile<<"!!!!Попытка инициализировать канал с неуникальным идентификатором - канал удаляется.";
				pChan->Release();
				continue;
			}
			m_LogFile<<(std::string("Стартуем канал ")+pChan->get_m_sObjectName()).c_str();
			
			//даем каналу событие для уведомления об инициализации
			pChan->m_hInitEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
			EventArray.insert(EventArray.end(),pChan->m_hInitEvent);

			//стартуем поток канала
			pChan->run();
		}
	}catch(_com_error &e)
	{
		m_LogFile<<(std::string("Error!!! ")+std::string(e.ErrorMessage())+std::string(" ")+(char*)e.Description()).c_str();
		hr=e.Error();
	}
	catch(...)
	{
		m_LogFile<<"Error!!! Неизвестная ошибка при инициализации каналов";
		hr=E_FAIL;
	}
/*	HRESULT hr=m_Server.Initialize();
	if (FAILED(hr))
	{
		char ch[10];
		std::string ers="Ошибка при инициализации объектов ADO. 0x";
			ers+=_itoa(hr,ch,16);
		m_LogFile<<ers.c_str();
	}

	USES_CONVERSION;
	_bstr_t ustr="File Name=";
	GetFromRegistry("UDLConfFile");
	hr=m_Server.OpenDatasource(ustr+m_UDLConfFile.c_str());
	if (FAILED(hr))
	{
		m_LogFile<<(std::string("Ошибка при открытии источника данных конфигурации\n") + (char*)m_Server.m_bstrLastErrorMessage).c_str();
		return hr;
	}
	hr=m_Server.OpenRecordset("select Channel.ChannelID,Channel.ChannelName,Channel.CnfgString,Channel.ChannelMode,Channel.ClockRate,Channel.DeviceUpdateMode,Channel.CreateTime,Plugin.CnfgString, Channel.Description from Channel,Plugin where Channel.ChannelID=Plugin.ChannelID");
	if (FAILED(hr))
	{
		m_LogFile<<(std::string("Ошибка при открытии таблицы Channel или Plugin \n") + (char*)m_Server.m_bstrLastErrorMessage).c_str();
		m_Server.CloseAll();
		return hr;
	}

	_variant_t RecAr;
	VARIANT HUGEP* pR;
	long index=0;
		srand((unsigned)time( NULL ) );//устанавливаем генератор
	VARIANT xtst; //нужен для преобразования
	VariantInit(&xtst);
	if (m_Server.LoadRecordsetArray(RecAr) >0) 
	{
		::SafeArrayAccessData(RecAr.parray,(void HUGEP* FAR*)&pR);
		ATLTRACE("Размер по 1 = %d \n",RecAr.parray->rgsabound[0].cElements);
		ATLTRACE("Размер по 2 = %d \n",RecAr.parray->rgsabound[1].cElements);
		for(ULONG i=0;i<(RecAr.parray->rgsabound[0].cElements*RecAr.parray->rgsabound[1].cElements);i+=RecAr.parray->rgsabound[1].cElements)
		{
			m_LogFile<<"XXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
			//создание экземпляров класса канала.
			CComObjectNoLock<CCChannelObj> * pChan = new CComObjectNoLock<CCChannelObj>;
			pChan->AddRef();

			VariantCopy(&xtst,pR+i);
			VariantChangeType(&xtst,pR+i,0,VT_I4);
			pChan->set_m_hObjectHandle(xtst.intVal);
			VariantClear(&xtst);

			VariantCopy(&xtst,pR+i+1);
			VariantChangeType(&xtst,pR+i+1,0,VT_BSTR);
			pChan->set_m_sObjectName(W2A(xtst.bstrVal));
			VariantClear(&xtst);

			VariantCopy(&xtst,pR+i+2);
			VariantChangeType(&xtst,pR+i+2,0,VT_BSTR);
			pChan->m_bstrChannelString = xtst.bstrVal;
			VariantClear(&xtst);

			VariantCopy(&xtst,pR+i+3);
			VariantChangeType(&xtst,pR+i+3,0,VT_I4);
			pChan->m_ChannelMode = (_ChannelMode)xtst.intVal;
			VariantClear(&xtst);

			VariantCopy(&xtst,pR+i+4);
			VariantChangeType(&xtst,pR+i+4,0,VT_I4);
			pChan->m_ClockRate = xtst.intVal;
			VariantClear(&xtst);

			VariantCopy(&xtst,pR+i+5);
			VariantChangeType(&xtst,pR+i+5,0,VT_I4);
			pChan->m_DeviceUpdateMode=xtst.intVal;
			VariantClear(&xtst);

			_variant_t t=pR[i+6];
			SYSTEMTIME st;
			VariantTimeToSystemTime(t,&st);
			SystemTimeToFileTime(&st,&pChan->m_CreateTime);

			VariantCopy(&xtst,pR+i+7);
			VariantChangeType(&xtst,pR+i+7,0,VT_BSTR);
			pChan->m_bstrPluginString = xtst.bstrVal;
			VariantClear(&xtst);

			VariantCopy(&xtst,pR+i+8);
			VariantChangeType(&xtst,pR+i+8,0,VT_BSTR);
			pChan->m_Description = xtst;
			VariantClear(&xtst);

			pChan->m_ConfigLogPath=m_LogFilePath;
			pChan->m_UDLConfFile = ustr+m_UDLConfFile.c_str();
			std::map<_ChannelID,CCChannelObj*>::iterator itm;
			_ChannelID tid(*pChan);
			m_LogFile<<tid.get_m_sObjectName().c_str();
			if ((itm=m_ChannelMap.find(tid))==m_ChannelMap.end())
				m_ChannelMap.insert(std::map<_ChannelID,CCChannelObj*>::value_type((_ChannelID)(*pChan),pChan));
			else
			{
				//если уже есть с таким идентификатором
				m_LogFile<<"!!!!Попытка инициализировать канал с неуникальным идентификатором - канал удаляется.";
				pChan->Release();
				continue;
			}
			m_LogFile.ChangeMode();
			m_LogFile<<(std::string("Стартуем канал ")+pChan->get_m_sObjectName()).c_str();
			m_LogFile.ChangeMode();
			pChan->m_hInitEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
			EventArray.insert(EventArray.end(),pChan->m_hInitEvent);

		/// pChan->Initialize("","");
			pChan->run();
		}
		::SafeArrayUnaccessData(RecAr.parray);
		
	}
*/	char ch[10];
	m_LogFile<<(std::string("Размер карты каналов ") + _itoa(m_ChannelMap.size(),ch,10)).c_str();
	
	::WaitForMultipleObjects(EventArray.size(),&EventArray[0],TRUE,60000);
	
	//Удалим EVENT'Ы
	for(UINT ie=0;ie<EventArray.size();ie++)
		CloseHandle(EventArray[ie]);
	xmldoc.Release();
	m_LogFile<<"Инициализация объекта конфигурации завершена\n";
	return S_OK;
}

HRESULT CMyTestConf::Uninitialize ()
{
	//m_Server.CloseAll();
	std::map<_ChannelID,CCChannelObj*>::iterator it;
	for (it=m_ChannelMap.begin();it!=m_ChannelMap.end();++it)
	{
		//	it->second->Stop();
		it->second->Uninitialize();
		delete (CCChannelObj*)it->second;
	}
	
	for (UINT i =0 ; i<PlaginList.size();i++)
	{
		CoTaskMemFree(PlaginList[i]);
	}
	PlaginList.clear();

m_LogFile<<"Деинициализация объекта конфигурации";

	
	m_ChannelMap.clear();
	return S_OK;
}

STDMETHODIMP CMyTestConf::CreateChannel(/*[in]*/ChannelDef* pChannelDef,/*[out]*/ICChannelObj**pICChannelObj)
{	
	if (!UserIsAdmin()) //не админ - нечего делать!
		return E_FAIL;
	if (m_OPCServerState==OPC_STATUS_RUNNING)
		return Error(IDS_ERROR_OPC_E_RUNNING,IID_IMyTestConf,OPC_E_RUNNING);
	//проверка на имя (есть-ли такое?)
	//проходим по всем каналам и смотрим названия
	//формирование идентификатора - MAX+1;
	USES_CONVERSION;
	std::map<_ChannelID,CCChannelObj*>::iterator itm;
	bool IsNameFlag=false;
	HRESULT hr=S_OK;
	DWORD ChannelID=0;
	for(itm=m_ChannelMap.begin();itm!=m_ChannelMap.end();++itm)
	{
		if (itm->second->get_m_sObjectName()==W2A(pChannelDef->ChannelName))
		{
			IsNameFlag=true;
			break;
		}else
		{
			if (ChannelID=itm->second->get_m_hObjectHandle()>ChannelID)
				ChannelID=ChannelID=itm->second->get_m_hObjectHandle();
		}
	}
	
	if (IsNameFlag)
		return E_FAIL;//просто ошибка (опять-же пока)
	
	ChannelID++;//увеличиваем идентификатор на 1
	
	
	//2 создаем канал

	CComObjectNoLock<CCChannelObj> * pChan = new CComObjectNoLock<CCChannelObj>;
	pChan->AddRef();
	pChan->set_m_hObjectHandle(ChannelID);
	pChan->set_m_sObjectName(W2A(pChannelDef->ChannelName));
	pChan->m_bstrChannelString = pChannelDef->ChannelCnfg;
	pChan->m_ChannelMode = (_ChannelMode) pChannelDef->ChannelMode;
	pChan->m_ClockRate = pChannelDef->UpdateRate;
//	pChan->m_DeviceUpdateMode=pChannelDef->DeviceUpdateMode;
	SYSTEMTIME st;
	GetLocalTime(&st);
	SystemTimeToFileTime(&st,&pChan->m_CreateTime);
	pChan->m_bstrPluginString = pChannelDef->PluginCnfg;
	pChan->m_Description = pChannelDef->ChannelDescription;
	pChan->m_ConfigLogPath=m_LogFilePath;
	//pChan->m_UDLConfFile = std::string("File Name=")+m_UDLConfFile.c_str();

	m_ChannelMap.insert(std::map<_ChannelID,CCChannelObj*>::value_type((_ChannelID)(*pChan),pChan));

	m_LogFile<<(std::string("Добавлен канал ")+pChan->get_m_sObjectName()).c_str();
	m_LogFile<<(std::string("Стартуем канал ")+pChan->get_m_sObjectName()).c_str();
	
	HANDLE InitEvent = CreateEvent(NULL,TRUE,FALSE,NULL);
	pChan->m_hInitEvent=InitEvent;
	pChan->InitNoytFromXML(pChannelDef);
	pChan->run();
	::WaitForSingleObject(InitEvent,60000);
	CloseHandle(InitEvent);
	return S_OK;
}

STDMETHODIMP CMyTestConf::DeleteChannel(DWORD dwChannelID)
{
	if (!UserIsAdmin()) //не админ - нечего делать!
		return E_FAIL;
	if (m_OPCServerState==OPC_STATUS_RUNNING)
		return Error(IDS_ERROR_OPC_E_RUNNING,IID_IMyTestConf,OPC_E_RUNNING);
	
	//вторая фаза удаления - удаление экземпляра запущенного класса
	try{
		_ChannelID mch;	
		mch.set_m_hObjectHandle(dwChannelID);
		std::map<_ChannelID,CCChannelObj*>::iterator itm;
		itm=m_ChannelMap.find(mch);
		if (itm==m_ChannelMap.end())
			return Error(IDS_ERROR_CONF_E_CHANNELNOTFOUND,IID_IMyTestConf,CONF_E_CHANNELNOTFOUND);
		CCChannelObj *pCh=itm->second;
		
		m_ChannelMap.erase(mch);
		pCh->Uninitialize();
		pCh->FinalRelease();
		delete pCh;
	}catch(...)
	{
		m_LogFile<<"Неизвестная ошибка при удалении канала!";
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CMyTestConf::ChangeChannelMode(DWORD dwChannelID, WORD wNewMode)
{
	if (!UserIsAdmin()) //не админ - нечего делать!
		return E_FAIL;
	if (m_OPCServerState==OPC_STATUS_RUNNING)
		return Error(IDS_ERROR_OPC_E_RUNNING,IID_IMyTestConf,OPC_E_RUNNING);

//	chmAutomatic
//		_ChannelMode::chmDisabled
	return E_NOTIMPL;
}

STDMETHODIMP CMyTestConf::GetChannelByName(BSTR ChannelName,ICChannelObj**pICChannelObj)
{
	if (!UserIsAdmin()) //не админ - нечего делать!
		return E_FAIL;
	
	m_LogFile<<"Мы в перечислителе";
	USES_CONVERSION;
	std::map<_ChannelID,CCChannelObj*>::iterator itm;
	HRESULT hr=S_FALSE;

	for(itm=m_ChannelMap.begin();itm!=m_ChannelMap.end();++itm)
	{
		if (itm->second->get_m_sObjectName()==W2A(ChannelName))
		{
			hr=itm->second->QueryInterface(IID_ICChannelObj,(void**)pICChannelObj);
			return hr;
			break;
		}
	}
	
	*pICChannelObj=NULL;
	return hr;


}
#define MAX_NAME 256

BOOL CMyTestConf::SearchTokenGroupsForSID (VOID) 
{
DWORD i, dwSize = 0, dwResult = 0;
HANDLE hToken;
PTOKEN_GROUPS pGroupInfo;
SID_NAME_USE SidType;
char lpName[MAX_NAME];
char lpDomain[MAX_NAME];
BYTE sidBuffer[100];
PSID pSID = (PSID)&sidBuffer;
SID_IDENTIFIER_AUTHORITY SIDAuth = SECURITY_NT_AUTHORITY;
   
// Open a handle to the access token for the calling process.

if (!OpenProcessToken( GetCurrentProcess(), TOKEN_QUERY, &hToken )) {
    m_LogFile<<"OpenProcessToken Error " ;
    return FALSE;
}

// Call GetTokenInformation to get the buffer size.

if(!GetTokenInformation(hToken, TokenGroups, NULL, dwSize, &dwSize)) {
    dwResult = GetLastError();
    if( dwResult != ERROR_INSUFFICIENT_BUFFER ) {
        m_LogFile<<"GetTokenInformation Error ";
        return FALSE;
    }
}

// Allocate the buffer.

pGroupInfo = (PTOKEN_GROUPS) GlobalAlloc( GPTR, dwSize );

// Call GetTokenInformation again to get the group information.

if(! GetTokenInformation(hToken, TokenGroups, pGroupInfo, 
                        dwSize, &dwSize ) ) {
    m_LogFile<<"GetTokenInformation Error ";
    return FALSE;
   }

// Create a SID for the BUILTIN\Administrators group.

if(! AllocateAndInitializeSid( &SIDAuth, 2,
                 SECURITY_BUILTIN_DOMAIN_RID,
                 DOMAIN_ALIAS_RID_ADMINS,
                 0, 0, 0, 0, 0, 0,
                 &pSID) ) {
    m_LogFile<<"AllocateAndInitializeSid Error ";
    return FALSE;
   }

// Loop through the group SIDs looking for the administrator SID.

for(i=0; i<pGroupInfo->GroupCount; i++) {
    if ( EqualSid(pSID, pGroupInfo->Groups[i].Sid) ) {

        // Lookup the account name and print it.

        dwSize = MAX_NAME;
        if( !LookupAccountSid( NULL, pGroupInfo->Groups[i].Sid,
                              lpName, &dwSize, lpDomain, 
                              &dwSize, &SidType ) ) {
            dwResult = GetLastError();
            if( dwResult == ERROR_NONE_MAPPED )
                strcpy( lpName, "NONE_MAPPED" );
            else {
                m_LogFile<<"LookupAccountSid Error ";
                return FALSE;
            }
        }
        m_LogFile<< "Current user is a member of the group";

        // Find out if the SID is enabled in the token
        if (pGroupInfo->Groups[i].Attributes & SE_GROUP_ENABLED)
            m_LogFile<<"The group SID is enabled.";
         else if (pGroupInfo->Groups[i].Attributes & 
                          SE_GROUP_USE_FOR_DENY_ONLY)
            m_LogFile<<"The group SID is a deny-only SID.";
         else 
            m_LogFile<<"The group SID is not enabled.";
    }
}

if (pSID)
    FreeSid(pSID);
if ( pGroupInfo )
    GlobalFree( pGroupInfo );
return TRUE;
}


STDMETHODIMP CMyTestConf::EnumChannels(IEnumUnknown** ppEnumChannel)
{

	if (!UserIsAdmin()) //не админ - нечего делать!
		return E_FAIL;
//Нужно создать и заполнить перечислитель
ATLTRACE("Вызов EnumChannels\n");
if (ppEnumChannel == NULL)
return E_POINTER;


	HRESULT hr;
	typedef CComObjectNoLock<CComEnumOnSTL<IEnumUnknown,&IID_IEnumUnknown,IUnknown*,_CopyXIUmap<std::map<_ChannelID,CCChannelObj*>::value_type,IUnknown*>,std::map<_ChannelID,CCChannelObj*> > > Enum;
	Enum * p = new Enum;
	
	if (p==NULL) hr= E_OUTOFMEMORY;
	else
	{
		hr=p->FinalConstruct();
		if (hr==S_OK)
		{	
			hr=p->Init(NULL,m_ChannelMap);
			if (hr==S_OK)
			{
				hr=p->QueryInterface(IID_IUnknown,(void**)ppEnumChannel);
			}
		}
	}
	if (hr!=S_OK)
		delete p;
	
	
	return hr;
}

STDMETHODIMP CMyTestConf::GetStatus(DWORD *pStatus)
{
	*pStatus=(DWORD)GlobalServerState;
	return S_OK;
}

STDMETHODIMP CMyTestConf::GetChannelByID(DWORD ChannelID, ICChannelObj **pICChannelObj)
{
	if (!UserIsAdmin()) //не админ - нечего делать!
		return E_FAIL;
	
	std::map<_ChannelID,CCChannelObj*>::iterator itm;

	HRESULT hr=S_FALSE;
	_ChannelID chid;
	chid.set_m_hObjectHandle(ChannelID);
	itm=m_ChannelMap.find(chid);
	if (itm!=m_ChannelMap.end())
	{
		hr=itm->second->QueryInterface(IID_ICChannelObj,(void**)pICChannelObj);
		return hr;
	}

	*pICChannelObj=NULL;
	return hr;
}

STDMETHODIMP CMyTestConf::get_ConfigXML(BSTR *pVal)
{
	*pVal=_bstr_t(m_XMLConfFile.c_str()).copy();
	return S_OK;
}

STDMETHODIMP CMyTestConf::put_ConfigXML(BSTR newVal)
{
	
	if (!UserIsAdmin()) //не админ - нечего делать!
		return E_FAIL;
	
	if (SetXMLConfigPathToRegistry((char*)_bstr_t(newVal)))
		return S_OK;
	else
		return E_FAIL;
}

STDMETHODIMP CMyTestConf::EnumPlugins(IEnumString **pEnumString)
{

  CComPtr<ICatInformation> pCatInfo;
  CComPtr<IEnumGUID> pEnumCLSID;
	GUID clsid=GUID_NULL;
	//std::vector<LPOLESTR> PlaginList;
	for (UINT i =0 ; i<PlaginList.size();i++)
	{
		CoTaskMemFree(PlaginList[i]);
	}
	PlaginList.clear();
	m_LogFile<<"Зашли!!!!";
	typedef CComObjectNoLock<CComEnumOnSTL< IEnumString,&IID_IEnumString,LPOLESTR,_Copy<LPOLESTR> , std::vector<LPOLESTR> > > Enum;
	Enum * p = new Enum;
	
	   HRESULT hr=NOERROR;
	   
		 if ((hr=CoCreateInstance(CLSID_StdComponentCategoriesMgr,NULL,CLSCTX_INPROC_SERVER,
		 IID_ICatInformation,(void**)&pCatInfo))!=S_OK)
		 return hr;
		 m_LogFile<<"Зашли2222";
		   //Для плагинов событий
		   CATID PlaginCatID=CATID_DataManagerPlugin;
		   USES_CONVERSION;			
		   if (pCatInfo.p)
		   {
				hr=pCatInfo->EnumClassesOfCategories( 1,&PlaginCatID,0,NULL,(IEnumGUID**)&pEnumCLSID);
				if (hr==S_OK)
				{
					ULONG Fetched;
					if (pEnumCLSID.p)
					{
						pEnumCLSID->Reset();//установка на начало
						while( pEnumCLSID->Next(1,&clsid,&Fetched)==S_OK)
						{
							LPOLESTR strProgID=NULL;
							ProgIDFromCLSID(clsid,&strProgID);

							PlaginList.insert(PlaginList.begin(),strProgID);
						}
		   
						pEnumCLSID.Release();
						pEnumCLSID=NULL;
					}
				} else
					goto cleanup;
			 }
	   
		  // HRESULT hr;
		   
		   if (p==NULL) hr= E_OUTOFMEMORY;
		   else
		   {
			   hr=p->FinalConstruct();
			   if (hr==S_OK)
			   {	
				   hr=p->Init(NULL,PlaginList);
				   if (hr==S_OK)
				   {
					   hr=p->QueryInterface(IID_IEnumString,(void**)pEnumString);
				   }
			   }
		   }
		   if (hr!=S_OK)
		   delete p;

	//http://meteo/users.xml	
cleanup://очистка
/*	for (int i =0 ; i<PlaginList.size();i++)
	{
		CoTaskMemFree(PlaginList[i]);
	}
	PlaginList.clear();*/
	return hr;
}

bool CMyTestConf::GetFromRegistry(std::string ValueName)
{
	CRegKey rkey;
	bool bres=false;
	char *buf=new char[300];
	ZeroMemory(buf,sizeof(char)*300);
	if(rkey.Open(HKEY_LOCAL_MACHINE,"SOFTWARE\\CAPCS\\OPCDM\\OPCDMSvc")==ERROR_SUCCESS)
	{ 
		bres=true;
		DWORD dwCount=300;
		if (rkey.QueryValue(buf,ValueName.c_str(),&dwCount)==ERROR_SUCCESS)
		{	
			if(ValueName=="LogPath")
				m_LogFilePath=buf;
			else if (ValueName=="XMLConfFile")
				m_XMLConfFile=buf;
			bres=true;
		}else
			bres=false;
	}
	if (!bres)
	{//Умолчания
		if(ValueName=="LogPath")
			m_LogFilePath="C:";
		else if (ValueName=="UDLConfFile")
			m_XMLConfFile="";
	}
	delete[] buf;
	return bres;
}

//STDMETHODIMP CMyTestConf::RestartChannel(DWORD ChannelID)
//{
//	if (!UserIsAdmin()) //не админ - нечего делать!
//	return E_FAIL;
//
//	if (m_OPCServerState==OPC_STATUS_RUNNING)
//		return Error(IDS_ERROR_OPC_E_RUNNING,IID_IMyTestConf,OPC_E_RUNNING);
//	// TODO: Add your implementation code here
//
//	return S_OK;
//}

bool CMyTestConf::UserIsAdmin()
{
	//Проверим - какой пользователь нас вызывает!
//	HRESULT hre=CoImpersonateClient();

 return true;
	bool RetVal=false;

	RPC_AUTHZ_HANDLE ha;
	USES_CONVERSION;
	//LookupAccountName
	HRESULT hhh=CoQueryClientBlanket(NULL,NULL,NULL,NULL,NULL,&ha,NULL);
	OLECHAR * ppp=(OLECHAR*)ha;
	m_LogFile<<W2A(ppp);
	
	//теперь нужно проверить принадлежность пользователя к группе администраторов
	//ищем SID
	DWORD cbSID=1024,cchDomainName=80;
    PSID pSID = (PSID) LocalAlloc(LPTR, cbSID); 
    PSID_NAME_USE psnuType = (PSID_NAME_USE) LocalAlloc(LPTR, 1024); 
    LPSTR lpszDomain = (LPSTR) LocalAlloc(LPTR, cchDomainName); 
	DWORD cbDom=321;

    if (!LookupAccountName((LPSTR) NULL, // local name  
		(LPCSTR)W2A(ppp), 
		pSID, 
		&cbSID, 
		lpszDomain, 
		&cchDomainName, 
		psnuType)) { 
		DWORD ee=GetLastError();
    } 
	
	LocalFree(lpszDomain);
	LocalFree(psnuType);
	
	LPBYTE pBuf=(LPBYTE)LocalAlloc(LPTR,1024);
	DWORD Cou,CouCur;
	NET_API_STATUS x= NetLocalGroupGetMembers (
		NULL,        
		LPCWSTR A2W("Администраторы"),    
		2,//все               
		&pBuf,            
		1024,          
		&Cou,       
		&CouCur,      
		NULL    
		);
	PLOCALGROUP_MEMBERS_INFO_2 lmi=(PLOCALGROUP_MEMBERS_INFO_2)pBuf;
	
	if (x==NERR_Success)
	{
		m_LogFile<<"Нормально получили членов";
	}
	
	//пройдемся по SIDам группы
	for(UINT i=0;i<Cou;i++)
	{
		
		if (!EqualSid(pSID,(lmi+i)->lgrmi2_sid))
			m_LogFile<<"Тю-тю";
		else
		{
			m_LogFile<<"Есть!!!!!!!!!!!!!";
			RetVal=true;
		}
	}

	LocalFree(pBuf);
	LocalFree(pSID);
/*
//	if (!IsValidSid(pSID))
//		m_LogFile<<"SID не правильный";

	
	PSID pSID2=(PSID)LocalAlloc(LPTR,1024);
	//проверка на админа
	SID_IDENTIFIER_AUTHORITY SIDAuth = SECURITY_NT_AUTHORITY;
	if(! AllocateAndInitializeSid( &SIDAuth, 2,	SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,
		0, 0, 0, 0, 0, 0,
		&pSID2) )
	
//	if (!IsValidSid(pSID2))
//			m_LogFile<<"SID не правильный админа";
		
	if (!EqualSid(pSID2,pSID))
		m_LogFile<<"Нет такого";
	else
		m_LogFile<<"Есть такой в группе админов";
	
	
*/
	return RetVal;

}

STDMETHODIMP CMyTestConf::ChangeState(OPCSERVERSTATE newState)
{
//	CComCriticalSection mycs;
//	mycs.Lock();
	std::map<_ChannelID,CCChannelObj*>::iterator it;

	if (newState==OPC_STATUS_RUNNING)
	{

		//Обновить все ссылки в ОРС группах на реальные теги
		std::list<CMyOPCSrv*>::iterator itl;

		
//		unsigned long* l = new unsigned long[OPCServersList.size()];
//		int y=0;
		for (itl=OPCServersList.begin();itl!=OPCServersList.end();++itl)
		{

		//	(*itl)->FinalRelease();
		//	delete itl;
//			l[0]=(unsigned long)*itl;			
			// пока выгружать будем все ОРС сервера (тоже как вариант)
			
			//здесь нужно разослать сообщения о смене ссылок на реальные теги каналов
//			Beep(1000,1000);
//			Sleep(500);
			//CMyOPCSrv::Update
			(*itl)->UpdateTagsRefs();
		}
//		DWORD count=OPCServersList.size();
//		//удаление/отключение ОРС серверов
//		for (int ii=0;ii<count;ii++)
//		{
//			((CMyOPCSrv*)l[ii])->FinalRelease();
//			delete ((CMyOPCSrv*)l[ii]);
//		}

		for (it=m_ChannelMap.begin();it!=m_ChannelMap.end();++it)
		{
			::PostThreadMessage(it->second->get_m_ThreadID(),WM_CHANNEL_START,0,0);
		}
	}
	else
	{
		for (it=m_ChannelMap.begin();it!=m_ChannelMap.end();++it)
		{

			::PostThreadMessage(it->second->get_m_ThreadID(),WM_CHANNEL_STOP,0,0);
		}
	}

	GlobalServerState=newState;
	m_OPCServerState=newState;
	return S_OK;
}

bool CMyTestConf::IsSuspended()
{

	if (m_OPCServerState==OPC_STATUS_RUNNING)
		return false;
	else 
		return true;
}

// новое значение конфигурационного файла
bool CMyTestConf::SetXMLConfigPathToRegistry(std::string NewXMLConfigPath)
{
	CRegKey rkey;
	bool bres=false;
	if(rkey.Open(HKEY_LOCAL_MACHINE,"SOFTWARE\\CAPCS\\OPCDM\\OPCDMSvc")==ERROR_SUCCESS)
	{ 
		bres=true;
		if (rkey.SetStringValue("XMLConfFile",NewXMLConfigPath.c_str())==ERROR_SUCCESS)
		{	
			m_XMLConfFile=NewXMLConfigPath;
			bres=true;
		}else
			bres=false;
	}
	return bres;
}

