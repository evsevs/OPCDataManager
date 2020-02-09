// CXMLPlug.h : Declaration of the CCDDEPlug

#ifndef __CXMLPLUG_H_
#define __CXMLPLUG_H_

#include "resource.h"       // main symbols
#include "Proxy_IPluginDataCallback.h"
#include <vector>
#include "HelperFunc.h"
#include "SimpleLogFile.h"	// Added by ClassView
#import "msxml3.dll" 


#include <ddeml.h>

/////////////////////////////////////////////////////////////////////////////
// CCDDEPlug

//using namespace MSXML2;



	static BOOL IsDISCONNECTED_EVENT;
//	static HSZ DISCONNECTED_SERVICE;
//	static HSZ DISCONNECTED_TOPIC;
	static HCONV DISCONNECTED_CONV;



//extern _ATL_FUNC_INFO OnEventInfo;

static const GUID CATID_DataManagerPlugin = 
{ 0x53b5fc45, 0xc8cc, 0x4f4f, { 0x90, 0x9d, 0x35, 0xf, 0xb9, 0x17, 0x6d, 0x15 } };

class ATL_NO_VTABLE CCDDEPlug : 
//	public IDispEventSimpleImpl</*nID =*/ 1, CCDDEPlug, &__uuidof(MSXML2::XMLDOMDocumentEvents)>,
	public CComObjectRootEx<CComMultiThreadModelNoCS>,
	public CComCoClass<CCDDEPlug, &CLSID_CDDEPlug>,
	public IConnectionPointContainerImpl<CCDDEPlug>,
	public IPluginConfig,
	public IPluginData,
	public CProxy_IPluginDataCallback<CCDDEPlug>
{
private:

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
	DWORD m_dwDDEInst;
	bool m_Inited;
	HSZ m_DDESvcName;
	HSZ m_DDETopicName;
	HCONV m_hDDEConv;
public:

	static HDDEDATA CALLBACK DdeCallback(UINT uType,UINT uFmt,HCONV hconv,HDDEDATA hsz1,HDDEDATA hsz2,HDDEDATA hdata,HDDEDATA dwData1,HDDEDATA dwData2)
		{	
			ATLTRACE("sadddddddddddddddddddddddddddddddddddddddddddd\n");
			Beep(100,100);
			HDDEDATA xd;
			if (uType==XTYP_DISCONNECT)
			{
				IsDISCONNECTED_EVENT =TRUE;
//				DISCONNECTED_SERVICE=hsz1;
//				DISCONNECTED_TOPIC=hsz2;
				DISCONNECTED_CONV=hconv;
			}

			return 0;
		};

	DWORD InitDDE()
	{
		if (m_Inited)
			return S_OK;
		m_dwDDEInst=0;
		DWORD Res=DdeInitialize(&m_dwDDEInst,(PFNCALLBACK)DdeCallback,APPCMD_CLIENTONLY,0);
		if (DMLERR_NO_ERROR==Res)
		{
			ATLTRACE("DDEInitialization is OK. Return value is %d\n",Res);
			m_Inited=true;
		}
		else
			ATLTRACE("DDEInitialization is FAIL. Return value is %d\n",Res);
		
		return Res;
	}
	void DeInitDDE()
	{
		DdeUninitialize(m_dwDDEInst);
		m_Inited=false;
	}

public:


	CCDDEPlug()
	{
	//	CCDDEPlug::IsDISCONNECTED_EVENT=FALSE;
		IsConfigured=false;
		m_LogFile.SetNewFullLogName("c:\\DDE2OPCPluginDefault.log");
		AsyncTimeout=5000;//мс
		m_Inited=false;
		m_AllErrorsCount=0;
	}

	long SendTimeCounter;//будет 97 секунд; 
	long AsyncTimeout;

DECLARE_REGISTRY_RESOURCEID(IDR_CDDEPLUG)
DECLARE_NOT_AGGREGATABLE(CCDDEPlug)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCDDEPlug)
	COM_INTERFACE_ENTRY(IPluginConfig)
	COM_INTERFACE_ENTRY(IPluginData)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CCDDEPlug)
	CONNECTION_POINT_ENTRY(IID_IPluginDataCallback)
END_CONNECTION_POINT_MAP()

BEGIN_CATEGORY_MAP(CCDDEPlug)
	IMPLEMENTED_CATEGORY(CATID_DataManagerPlugin)
END_CATEGORY_MAP()

//BEGIN_SINK_MAP(CCDDEPlug)
   //SINK_ENTRY_INFO(/*nID =*/ 1, __uuidof(MSXML2::XMLDOMDocumentEvents), /*dispid =*/ 0xc6, ondataavailable, &OnEventInfo)
   //SINK_ENTRY_INFO(/*nID =*/ 1, __uuidof(MSXML2::XMLDOMDocumentEvents), /*dispid =*/ 0xfffffd9f, onreadystatechange, &OnEventInfo)
//END_SINK_MAP()

// ICXMLPlug
public:
	void __stdcall ondataavailable ( );

    void __stdcall onreadystatechange ( );
	
	bool XMLReady;
	bool XMLAvail;

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
