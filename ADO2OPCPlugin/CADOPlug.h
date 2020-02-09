// CXMLPlug.h : Declaration of the CCADOPlug

#ifndef __CXMLPLUG_H_
#define __CXMLPLUG_H_

#include "resource.h"       // main symbols
#include "Proxy_IPluginDataCallback.h"
#include <vector>
#include "HelperFunc.h"
#include "SimpleLogFile.h"	// AADOd by ClassView
#import "msxml3.dll" 
#import "c:\\program files\\common files\\system\\ado\\msado27.tlb" raw_dispinterfaces no_namespace rename ( "EOF", "adoEOF" )
//#include <ADOml.h>

/////////////////////////////////////////////////////////////////////////////
// CCADOPlug

//using namespace MSXML2;



//extern _ATL_FUNC_INFO OnEventInfo;

static const GUID CATID_DataManagerPlugin = 
{ 0x53b5fc45, 0xc8cc, 0x4f4f, { 0x90, 0x9d, 0x35, 0xf, 0xb9, 0x17, 0x6d, 0x15 } };

class ATL_NO_VTABLE CCADOPlug : 
//	public IDispEventSimpleImpl</*nID =*/ 1, CCADOPlug, &__uuidof(MSXML2::XMLDOMDocumentEvents)>,
	public CComObjectRootEx<CComMultiThreadModelNoCS>,
	public CComCoClass<CCADOPlug, &CLSID_CADOPlug>,
	public IConnectionPointContainerImpl<CCADOPlug>,
	public IPluginConfig,
	public IPluginData,
	public CProxy_IPluginDataCallback<CCADOPlug>
{
private:

	struct MyData
	{
		_bstr_t fname;
		_variant_t dbdata;
	};

	MyData *pMyData;
	DWORD MyDataCount;

	void CheckAllErrors()
	{
		if ((++this->m_AllErrorsCount)==3)
		{
				CheckOnDisconnect();
				this->m_AllErrorsCount=0;
		}
	}
	
	void CheckOnDisconnect()
	{
		Reset();
		_bstr_t t(ConfigString,true);
		this->Configure(t);
	};
	DWORD m_AllErrorsCount;
	DWORD m_dwADOInst;
	bool m_Inited;
	HSZ m_ADOSvcName;
	HSZ m_ADOTopicName;
	HCONV m_hADOConv;
	_CommandPtr  spCom;
	_ConnectionPtr Con;
	bool Connected;
public:

	DWORD ADOConnect(_bstr_t UDLName)
	{
		Connected=false;
		char xs[255];
		HRESULT hr=NOERROR;
		if (FAILED(hr=Con.CreateInstance(__uuidof(Connection))))
		{
			sprintf(xs,"ERROR: ADOConnect. ErrorCode = 0x%x\n",hr);
			m_LogFile<<xs;
			return hr;
		}
	
		hr=spCom.CreateInstance(__uuidof(Command));
		if (FAILED(hr))
		{
			sprintf(xs,"ERROR: ADOConnect.CreateInstance. ErrorCode = 0x%x\n",hr);
			m_LogFile<<xs;
			return hr;
		}

	//соединяемся
		_bstr_t ConStr="File Name=";
		_variant_t fn;
		fn=GetParameter("FileName",MyParams);
		ConStr+=_bstr_t(fn);
		_bstr_t PWD="";
		_bstr_t UID="";
	
		try
		{
			Con->Open(ConStr,UID/*""*/,PWD/*""*/,-1);
		}catch(_com_error &er)
		{
			sprintf(xs,"ERROR: Open Connection. ErrorCode = 0x%x\n",er.Error());
			m_LogFile<<xs;
		}
		catch(...)
		{
			sprintf(xs,"ERROR: Con.Open.!\n");
			m_LogFile<<xs;
			Con.Release();
			spCom.Release();
		return E_FAIL;
		}
Connected=true;
	return S_OK;
}
DWORD GetDataFromDB()
{
	if (!Connected) 
	{
		ADOConnect("asd");
		return E_FAIL;
	}

	spCom->ActiveConnection=Con;	
	_variant_t cs;
	cs=GetParameter("Command",MyParams);
	spCom->CommandText=_bstr_t(cs);
	spCom->CommandType = adCmdText;
	//long ret=-1;
	//try
	//{
	//	spCom->ActiveConnection=Con;	
	//	char ccom[200];
	//	char ch[20];
	//	strcpy(ccom,"select nplv,nprt from  dbo.АСС450_Ф_Получить_НПЛВ_НПРТ_по_посаду(");
	//	strcat(ccom,_itoa(i_posad,ch,10));
	//	strcat(ccom,")");
	//	spCom->CommandText=ccom;
	//	spCom->CommandType = adCmdText;
	//
	//	
	//
	DWORD ret=0;
	char xs[300];
	try{
		_RecordsetPtr Rec;

	    Rec=spCom->Execute(&vtMissing,&vtMissing,adCmdText);

		Rec->MoveFirst();
		if (!pMyData)
		{
			pMyData= new MyData[Rec->Fields->Count];
		}

		MyDataCount=Rec->Fields->Count;
		for (int i=0;i<Rec->Fields->Count;i++)
		{
			pMyData[i].fname=Rec->Fields->Item[(long)i]->Name;
			pMyData[i].dbdata=Rec->Fields->Item[(long)i]->Value;
		}
		Rec->Close();		
	}
	catch(_com_error &er)
	{
		sprintf(xs,"Ошибка в получении данных из БД 0x%x %s\n",er.Error(), (char*)_bstr_t(er.Description()));
		m_LogFile<<xs;
		ret=er.Error();
	}
	catch(...)
	{
		m_LogFile<<"Неизвестная ошибка при получении данных из БД";
		ret  = E_FAIL;
	}
	//__NPLV = (long)Rec->Fields->Item[(long)0]->Value;
	//	__NPRT = (long)Rec->Fields->Item[(long)1]->Value;

	//	ret=0;
	
	//		
	//				
	//}	catch(_com_error &e)
	//{
	//	printf("Ошибка при вызове Execute или MoveFirst!");
	//	LogERROR(GLID,"Ошибка при вызове Execute или MoveFirst!",e.Error(),"ADOReceiveData");
	//	LogERROR(GLID,e.Description(),e.Error(),"ADOReceiveData");
	//	return -1;
	//}
	//catch(...)
	//{
	//	printf("Ошибка (не COM) при вызове Execute или MoveFirst!");
	//	LogERROR(GLID,"Ошибка (не COM) при вызове Execute или MoveFirst!",0,"ADOReceiveData");

	//	return -1;
	//}

	return ret;
}
	DWORD ADODisconnect()
{
	if (!Connected) return S_OK;
	char xs[255];
	if (spCom!=NULL)
	{	
		spCom.Release();
	}
	
	try
	{
		if (Con!=NULL)
		{
			if (Con->State!=0)
				Con->Close();
			Con.Release();
		}
	}
	catch(_com_error &er)
	{
		sprintf(xs,"ERROR: Close connection 0x%x\n",er.Error());
		m_LogFile<<xs;
	}
	catch (...)
	{
		sprintf(xs,"ERROR: Con.Close\n");
		m_LogFile<<xs;
	}
Connected=false;
	return S_OK;
}

//	static HADODATA CALLBACK ADOCallback(UINT uType,UINT uFmt,HCONV hconv,HADODATA hsz1,HADODATA hsz2,HADODATA hdata,HADODATA dwData1,HADODATA dwData2)
//		{	
//			ATLTRACE("sadddddddddddddddddddddddddddddddddddddddddddd\n");
//			Beep(100,100);
//			HADODATA xd;
//			if (uType==XTYP_DISCONNECT)
//			{
//				IsDISCONNECTED_EVENT =TRUE;
////				DISCONNECTED_SERVICE=hsz1;
////				DISCONNECTED_TOPIC=hsz2;
//				DISCONNECTED_CONV=hconv;
//			}
//
//			return 0;
//		};

	//DWORD InitADO()
	//{
	//	if (m_Inited)
	//		return S_OK;
	//	m_dwADOInst=0;
	//	DWORD Res=ADOInitialize(&m_dwADOInst,(PFNCALLBACK)ADOCallback,APPCMD_CLIENTONLY,0);
	//	if (DMLERR_NO_ERROR==Res)
	//	{
	//		ATLTRACE("ADOInitialization is OK. Return value is %d\n",Res);
	//		m_Inited=true;
	//	}
	//	else
	//		ATLTRACE("ADOInitialization is FAIL. Return value is %d\n",Res);
	//	
	//	return Res;
	//}
	//void DeInitADO()
	//{
	//	ADOUninitialize(m_dwADOInst);
	//	m_Inited=false;
	//}

public:


	CCADOPlug()
	{
	//	CCADOPlug::IsDISCONNECTED_EVENT=FALSE;
		IsConfigured=false;
		m_LogFile.SetNewFullLogName("c:\\ADO2OPCPluginDefault.log");
		AsyncTimeout=5000;//мс
		m_Inited=false;
		m_AllErrorsCount=0;
		pMyData=NULL;
	}

	long SendTimeCounter;//будет 97 секунд; 
	long AsyncTimeout;

DECLARE_REGISTRY_RESOURCEID(IDR_CADOPLUG)
DECLARE_NOT_AGGREGATABLE(CCADOPlug)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCADOPlug)
	COM_INTERFACE_ENTRY(IPluginConfig)
	COM_INTERFACE_ENTRY(IPluginData)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CCADOPlug)
	CONNECTION_POINT_ENTRY(IID_IPluginDataCallback)
END_CONNECTION_POINT_MAP()

BEGIN_CATEGORY_MAP(CCADOPlug)
	IMPLEMENTED_CATEGORY(CATID_DataManagerPlugin)
END_CATEGORY_MAP()

//BEGIN_SINK_MAP(CCADOPlug)
   //SINK_ENTRY_INFO(/*nID =*/ 1, __uuidof(MSXML2::XMLDOMDocumentEvents), /*dispid =*/ 0xc6, ondataavailable, &OnEventInfo)
   //SINK_ENTRY_INFO(/*nID =*/ 1, __uuidof(MSXML2::XMLDOMDocumentEvents), /*dispid =*/ 0xfffffd9f, onreadystatechange, &OnEventInfo)
//END_SINK_MAP()

// ICXMLPlug
public:
//	void __stdcall ondataavailable ( );

//    void __stdcall onreadystatechange ( );
	
//	bool XMLReady;
//	bool XMLAvail;

	bool bSendDT;//посылать-ли время с запросом?
	CLogFile_CS m_LogFile;
	bool ParseInitializationString(const _bstr_t InitString,std::vector<ParametersVal> &ParamStruct);
	_variant_t GetParameter(const _bstr_t ParamName,std::vector<ParametersVal> &ParVal);
	std::vector<ParametersVal> MyParams;
	_bstr_t ConfigString;

	std::string m_XMLPath;
	MSXML2::IXMLDOMDocumentPtr m_Doc;
	
	bool IsConfigured;
	//##ModelId=3C4E3C780371
	STDMETHOD(GetExampleCnfg)(/*[in,out]*/ BSTR * bstrExampleCnfg);
	//##ModelId=3C4E3C78037C
	STDMETHOD(GetState)(DWORD State);
	//##ModelId=3C4E3C780386
	STDMETHOD(SetTags)(/*[in]*/ITEMID*ClientTagID ,/*[in]*/DWORD Count,/*[in]*/ VARIANT *pItemValues,/*[out]*/HRESULT** ppErrors);
	//##ModelId=3C4E3C7803A3
	STDMETHOD(GetTags)(/*[in]*/ITEMID*ClientTagID ,/*[in]*/DWORD dwCount, /*[out]*/ OPCITEMSTATE **pOutStruct,/*[out]*/HRESULT** ppErrors);
	//	STDMETHOD(GetItemProperties)(/*[in]*/ BSTR ItemID,/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ DWORD * pdwPropertyIDs,/*[out, size_is(,dwCount)]*/ VARIANT ** ppvData,/*[out, size_is(,dwCount)]*/ HRESULT **ppErrors);
	//	STDMETHOD(QueryAvailableProperties)(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR *ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes);
	//##ModelId=3C4E3C7803C1
	STDMETHOD(Reset)();
	//##ModelId=3C4E3C7803C3
	STDMETHOD(Configure)(/*[in]*/BSTR CnfgString);
	//##ModelId=3C4E3C7803D5
	STDMETHOD(DelNotifyTags)(/*[in]*/ITEMID*ClientTagID, /*[in]*/DWORD dwCount);
	//##ModelId=3C4E3C7803E0
	STDMETHOD(AddNotifyTags)(/*[in]*/ITEMID*ClientTagID, /*[in]*/DWORD dwCount, /*[in]*/DWORD dwUpdateRate, /*[out]*/HRESULT **pError);
	
	STDMETHOD(GetBrowser)(IUnknown**pBrowUnk);
	STDMETHOD(SetFullLogFileName)(BSTR LogFileName);
	std::string ChangeFloatString(std::string src)
		{
			//найдем все точки и заменим их запятыми если символы - цифры перед и после запятой.
			std::string res;

			std::basic_string <char>::size_type npos=-1;
			npos=src.find('.',1);//стоять на первом месте не может.

			if (-1!=npos) 
			{
				if (!(src.size()>npos+1))
					return src;
				//что-то нашли. Меняем только 1 раз в строке (значении)
				char befch,aftch;
				befch=src.at(npos-1);
				aftch=src.at(npos+1);
				
				if (isdigit(aftch)&&isdigit(befch))
				{
						//осталось скопировать строку
						res=src;
						res.at(npos)=',';
						return res;
				}
				
			}
			return src;
			
		};	
};

	
	class ATL_NO_VTABLE CBrowseObj ://:public virtual CBrowse ,
	public CComObjectRootEx<CComMultiThreadModel>,
		public ISpaceBrowse
	{
	public:
		//std::string m_XMLPath;
		//std::string m_CurPath;//до узла
		//MSXML2::IXMLDOMDocumentPtr m_Doc;
		//MSXML2::IXMLDOMNodePtr	m_CurNode;
		//MSXML2::IXMLDOMElementPtr	m_Element;
		
		//	CCurrentBrowsePosition m_CurPos;
		
		//	CTagStorage *m_TagStorage;
		//	CExternalInfoHandler *m_ExternalInfo;
		CBrowseObj()
		{
			//		m_CurrentPositionName = "";
			//		m_TagStorage = NULL;
			//		m_ExternalInfo = NULL;
			ATLTRACE("Создали объект Browser плагина\n");
		}
		void FinalRelease()
		{
			int x=0;x++;
			ATLTRACE("Удалили объект Browser плагина\n");
		}
		//DECLARE_NO_REGISTRY()//DECLARE_REGISTRY_RESOURCEID(IDR_CCHANNELOBJ)
		//	DECLARE_NOT_AGGREGATABLE(CChannelBrowseObj)
		
		//DECLARE_PROTECT_FINAL_CONSTRUCT()
		
		BEGIN_COM_MAP(CBrowseObj)
			COM_INTERFACE_ENTRY(ISpaceBrowse)
			END_COM_MAP()
			
	public:
//		CComPtr<IOPCBrowseServerAddressSpace> pBrowse;
		STDMETHOD(ValidateItem)(/*[in]*/DWORD dwCount,/*[in, size_is(dwCount)]*/ OPCITEMDEF * pItemArray,/*[in]*/ BOOL bBlobUpdate,/*[out, size_is(,dwCount)]*/ OPCITEMRESULT ** ppValidationResults,/*[out, size_is(,dwCount)]*/ HRESULT** ppErrors);
		STDMETHOD(BrowseAccessPaths)(/*[in]*/LPCWSTR szItemID,/*[out]*/ LPENUMSTRING *ppIEnumString);
		STDMETHOD(GetItemID)(/*[in]*/LPCWSTR szItemDataID, /*[out]*/LPWSTR *szItemID);
		STDMETHOD(BrowseOPCItemIDs)(/*[in]*/OPCBROWSETYPE  dwBrowseFilterType,/*[in]*/ LPCWSTR	szFilterCriteria, /*[in]*/ VARTYPE	 vtDataTypeFilter, /*[in]*/ DWORD	 dwAccessRightsFilter,	  /*[out]*/ LPENUMSTRING  * ppIEnumString);
		STDMETHOD(ChangeBrowsePosition)(/*[in]*/ OPCBROWSEDIRECTION dwBrowseDirection,/*[in]*/ LPCWSTR	szString);
		STDMETHOD(QueryAvailableProperties)(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR **ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes);
		STDMETHOD(GetItemProperties)(/*[in]*/ BSTR ItemID,/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ DWORD * pdwPropertyIDs,/*[out, size_is(,dwCount)] */VARIANT ** ppvData,/*[out, size_is(,dwCount)]*/ HRESULT **ppErrors);
		//	STDMETHOD(put_ClockRate)(/*[in]*/ DWORD newVal);

	public:

	
	};
#endif //__CXMLPLUG_H_
