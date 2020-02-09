// MyTestConf.h : Declaration of the CMyTestConf

#ifndef __MYTESTCONF_H_
#define __MYTESTCONF_H_

#include "resource.h"       // main symbols
//#include "DataManager.h"
#include "CChannelObj.h"
#include "SimpleLogFile.h"	// Added by ClassView

class CMyTestConf;
extern CMyTestConf* pMyTestConf;

// {53B5FC45-C8CC-4f4f-909D-350FB9176D15}
//Категории для плагинов
static const GUID CATID_DataManagerPlugin = 
{ 0x53b5fc45, 0xc8cc, 0x4f4f, { 0x90, 0x9d, 0x35, 0xf, 0xb9, 0x17, 0x6d, 0x15 } };
/////////////////////////////////////////////////////////////////////////////
// класс для копирования CMyGroup в IUknown для использования в IEnumUknown


template <class S,class D>
class _CopyXIUmap
{
public:
	static HRESULT copy(D* p1, const S* p2)
	{
		USES_CONVERSION;
		HRESULT hr = S_OK;
		hr=(p2->second)->QueryInterface(IID_IUnknown,(void**)p1);
		return hr;
	}
	static void init(LPUNKNOWN* p) {*p = NULL;}
	static void destroy(LPUNKNOWN* p) { (*p)->Release();}
};



/////////////////////////////////////////////////////////////////////////////
// CMyTestConf
//##ModelId=3B2979EF00B5
class ATL_NO_VTABLE CMyTestConf : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMyTestConf, &CLSID_MyTestConf>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CMyTestConf>,
	public IMyTestConf
{
public:

	OPCSERVERSTATE m_OPCServerState;
    //	Возвращает указатель на структуру OPCSERVERSTATE.
      //	Выделение памяти - CoTaskMemAlloc.
      //	Использует переменные со стереотипом State.
      //	Должен быть защищен внутри.
      //## Concurrency: Guarded
      //## Semantics:
      //	Выделение памяти CoTaskMemAlloc.
     // HRESULT GetDMStatus (OPCSERVERSTATUS* pOPCSERVERSTATUS, _ChannelID& pChannelID	// Идентификатор канала для получения специфичной
     // 	// информации.
     // );
     ////## Operation: Initialize%3B5B733A0257
      HRESULT Initialize (_bstr_t CnfgString);

      //## Operation: Uninitialize%3B5B86A102D2
      HRESULT Uninitialize ();
      //	Карта каналов
      std::map<_ChannelID,CCChannelObj*> m_ChannelMap;
	  
BOOL SearchTokenGroupsForSID (VOID) ;

private:
	std::vector<HANDLE> EventArray;
	std::string m_LogFilePath;//путь до лог-файла
	std::string m_XMLConfFile;
      WORD m_wMajorVersion;
      WORD m_wMinorVersion;
      WORD m_wBuildNumber;
      FILETIME m_ftStartTime;
      FILETIME m_ftCurrentTime;
      OPCSERVERSTATE m_dwServerState;
      DWORD m_dwReserved;
      std::string m_sVendorInfo;


//	  CDBBase m_Server;


public:
	std::vector<LPOLESTR> PlaginList;
	CMyTestConf()
	{
		m_wMajorVersion=1;
        m_wMinorVersion=1;
        m_wBuildNumber=1;
        m_dwServerState=OPC_STATUS_SUSPENDED;
        m_dwReserved=0;
        m_sVendorInfo="";
		pMyTestConf=this;
	}
DECLARE_CLASSFACTORY_SINGLETON(CMyTestConf)
DECLARE_REGISTRY_RESOURCEID(IDR_MYTESTCONF)
DECLARE_NOT_AGGREGATABLE(CMyTestConf)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMyTestConf)
	COM_INTERFACE_ENTRY(IMyTestConf)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CMyTestConf)
END_CONNECTION_POINT_MAP()

	
	//##ModelId=3B2979EF00FC
	HRESULT FinalConstruct()
	{
//	Error()

	HRESULT hr=Initialize("");
	//Beep(1000,1000);
		//SetEvent(ConfObjectInitEvent);
		
	//Создадим лог-файл для регистрации ошибок уровня инициализации
		CSimpleLogFile log;
		log.SetNewLogFile("OPCDMSvcInitLog","c:");
		log.GenerateLogFile(true,true);
	if (FAILED(hr))
	{
		char Mes[500];
		std::string ers="Ошибка инициализации объекта конфигурации  \n ";
		if(FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr,MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), Mes, sizeof(Mes), NULL))
			ers+=Mes;
		log<<ers.c_str();
	}
		m_OPCServerState=OPC_STATUS_RUNNING;
			//Beep(1000,1000);
		SetEvent(ConfObjectInitEvent);
		
		return hr;
		
	}
	void FinalRelease()
	{
		Uninitialize();
	}

// ISupportsErrorInfo
	//##ModelId=3B2979EF00F6
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMyTestConf
public:
	bool IsSuspended();
	STDMETHOD(ChangeState)(/*[in]*/ OPCSERVERSTATE newState);
	bool UserIsAdmin();
	//STDMETHOD(RestartChannel)(/*[in]*/ DWORD ChannelID);
	bool GetFromRegistry(std::string ValueName);
	CLogFile_CS m_LogFile;
//	CComObjectNoLock<CCChannelObj> * pCh;
//	CDataManager * m_pDataManager;
	STDMETHOD(get_ConfigXML)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_ConfigXML)(/*[in]*/ BSTR newVal);
	STDMETHOD(GetChannelByID)(/*[in]*/DWORD ChannelID,/*[out]*/ICChannelObj**pICChannelObj);
	STDMETHOD(GetChannelByName)(/*[in]*/BSTR ChannelName, /*[out]*/ ICChannelObj**pICChannelObj);
	STDMETHOD(GetStatus)(/*[out]*/DWORD *pStatus);
	STDMETHOD(ChangeChannelMode)(/*[in]*/ DWORD dwChannelID,/*[in]*/ WORD wNewMode);

	STDMETHOD(DeleteChannel)(/*[in]*/DWORD dwChannelID);
	STDMETHOD(CreateChannel)(/*[in]*/ChannelDef * pChannelDef,/*[out]*/ICChannelObj**pICChannelObj);

	STDMETHOD(EnumPlugins)(/*[in,out]*/IEnumString** pEnumString);
	STDMETHOD(EnumChannels)(/*[in,out]*/ IEnumUnknown** ppEnumChannel);
	STDMETHOD(SaveCurrentConfigToXML)(BSTR secondCopyOfXML);
	// новое значение конфигурационного файла
	bool SetXMLConfigPathToRegistry(std::string NewXMLConfigPath);
};
OBJECT_ENTRY_AUTO(__uuidof(MyTestConf), CMyTestConf)
#endif //__MYTESTCONF_H_
