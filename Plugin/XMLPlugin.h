// XMLPlugin.h : Declaration of the CXMLPlugin

#ifndef __XMLPLUGIN_H_
#define __XMLPLUGIN_H_

#include "resource.h"		// main symbols
#include <string>
#include <vector>
#include <list>
#include <comdef.h>
#include <atlwin.h>
#include "CThread.h"
#include "proxy_iplugindatacallback.h"
// {53B5FC45-C8CC-4f4f-909D-350FB9176D15}
//Категории для плагинов
static const GUID CATID_DataManagerPlugin = 
{ 0x53b5fc45, 0xc8cc, 0x4f4f, { 0x90, 0x9d, 0x35, 0xf, 0xb9, 0x17, 0x6d, 0x15 } };
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////ТЕСТ НАЧАЛО/////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//Временная структура и функция для тестирования связи плагина и DM
class CXMLPlugin;

class PLItem
{
public:
	OPCHANDLE	hClient;	
	OPCHANDLE	hServer;
	FILETIME	ftTimeStamp; 
	WORD		wQuality;
	_variant_t		vDataValue;
	_bstr_t ItemName;

	void ChangeItemValue(WORD wNewQuality,_variant_t wNewValue)
	{
		vDataValue = wNewValue;
		wQuality = wNewQuality;
		SYSTEMTIME now;
		GetSystemTime(&now);
		SystemTimeToFileTime(&now,&(ftTimeStamp));//установка времени;

	};
};

typedef std::vector<PLItem*> ItemVector;

void BeginItemsFilling();
void ReleaseItemsVector();

class MyThread :public CThread
{
 virtual DWORD fbody ()
 {
   SetTimer(NULL,12,10,0);
		srand((unsigned)1000 );//устанавливаем генератор
	MSG msg;
   ::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE) ;
	while(GetMessage(&msg,0,0,0))
	{
	   ::DispatchMessage(&msg);
	   switch(msg.message)
	   {
	   case WM_TIMER:
		   OnTimerMessage(msg);
		   break;
	   }
	 }
	KillTimer(NULL,12);
	return 0;
 }
 void OnTimerMessage(MSG msg);
public:
	CXMLPlugin * m_Owner;
};
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////ТЕСТ КОНЕЦ/////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

//структура для хранения параметров конфигурационной строки
struct ParametersVal
{
	_bstr_t ParamName;
	_variant_t ParamValue;
};
class ItemAssoc
{
public:
	ItemAssoc()
	{
		NotifyNow=false;
	}
	_bstr_t ItemName;
	OPCHANDLE hClient;
	OPCHANDLE hServer;
	bool NotifyNow;

	void Fill(ITEMID* pItemID)
	{
		hClient= pItemID->hClient;
		ItemName = _bstr_t(pItemID->ItemName);
	}
	PLItem m_it;
};

typedef std::list<ItemAssoc*> NotifyItemList;

bool ParseInitializationString(const _bstr_t InitString,std::vector<ParametersVal> &ParamStruct);

// CXMLPlugin
class ATL_NO_VTABLE CXMLPlugin : 
public CComObjectRootEx<CComMultiThreadModel>,
public CComCoClass<CXMLPlugin, &CLSID_XMLPlugin>,
public ISupportErrorInfo,
public IConnectionPointContainerImpl<CXMLPlugin>,
//	public IXMLPlugin,
public IPluginConfig,
public IPluginData,
//public ISpaceBrowse,
public CProxy_IPluginDataCallback<CXMLPlugin>
{
public:
	CXMLPlugin()
	{
	}
	
DECLARE_REGISTRY_RESOURCEID(IDR_XMLPLUGIN)
DECLARE_NOT_AGGREGATABLE(CXMLPlugin)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CXMLPlugin)
//	COM_INTERFACE_ENTRY(IXMLPlugin)
	COM_INTERFACE_ENTRY(IPluginData)
//	COM_INTERFACE_ENTRY(ISpaceBrowse)
	COM_INTERFACE_ENTRY(IPluginConfig)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)

END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(CXMLPlugin)
	CONNECTION_POINT_ENTRY(IID_IPluginDataCallback)
END_CONNECTION_POINT_MAP()

BEGIN_CATEGORY_MAP(CXMLPlugin)
	IMPLEMENTED_CATEGORY(CATID_DataManagerPlugin)
END_CATEGORY_MAP()


// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IXMLPlugin
public:
	HRESULT NotifyTagsChange();
	MyThread m_th;
	NotifyItemList NotiItems;


	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	void FinalRelease()
	{
		m_th.Stop();
		ReleaseItemsVector();
		
	}
	//	LRESULT OnMyTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	//	{
	//		MessageBox(NULL,"asdfsdf","adsfadsf",MB_OK);
	//	}
	STDMETHOD(GetExampleCnfg)(/*[in,out]*/ BSTR * bstrExampleCnfg);
	STDMETHOD(GetState)(DWORD State);
	STDMETHOD(SetTags)(/*[in]*/ITEMID*ClientTagID ,/*[in]*/DWORD Count,/*[in]*/ VARIANT *pItemValues,/*[out]*/HRESULT** ppErrors);
	STDMETHOD(GetTags)(/*[in]*/ITEMID*ClientTagID ,/*[in]*/DWORD dwCount, /*[out]*/ OPCITEMSTATE **pOutStruct,/*[out]*/HRESULT** ppErrors);
	//	STDMETHOD(GetItemProperties)(/*[in]*/ BSTR ItemID,/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ DWORD * pdwPropertyIDs,/*[out, size_is(,dwCount)]*/ VARIANT ** ppvData,/*[out, size_is(,dwCount)]*/ HRESULT **ppErrors);
	//	STDMETHOD(QueryAvailableProperties)(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR *ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes);
	STDMETHOD(Reset)();
	STDMETHOD(Configure)(/*[in]*/BSTR CnfgString);
	STDMETHOD(DelNotifyTags)(/*[in]*/ITEMID*ClientTagID, /*[in]*/DWORD dwCount);
	STDMETHOD(AddNotifyTags)(/*[in]*/ITEMID*ClientTagID, /*[in]*/DWORD dwCount, /*[in]*/DWORD dwUpdateRate, /*[out]*/HRESULT **pError);
	STDMETHOD(GetBrowser)(IUnknown**pBrowUnk);
	STDMETHOD(SetFullLogFileName)(BSTR LogFileName);

};


class ATL_NO_VTABLE CBrowseObj ://:public virtual CBrowse ,
public CComObjectRootEx<CComMultiThreadModel>,
public ISpaceBrowse
{
public:
	
	
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
	CComPtr<IOPCBrowseServerAddressSpace> pBrowse;
	STDMETHOD(ValidateItem)(/*[in]*/DWORD dwCount,/*[in, size_is(dwCount)]*/ OPCITEMDEF * pItemArray,/*[in]*/ BOOL bBlobUpdate,/*[out, size_is(,dwCount)]*/ OPCITEMRESULT ** ppValidationResults,/*[out, size_is(,dwCount)]*/ HRESULT** ppErrors);
	STDMETHOD(BrowseAccessPaths)(/*[in]*/LPCWSTR szItemID,/*[out]*/ LPENUMSTRING *ppIEnumString);
	STDMETHOD(GetItemID)(/*[in]*/LPCWSTR szItemDataID, /*[out]*/LPWSTR *szItemID);
	STDMETHOD(BrowseOPCItemIDs)(/*[in]*/OPCBROWSETYPE  dwBrowseFilterType,/*[in]*/ LPCWSTR	szFilterCriteria, /*[in]*/ VARTYPE	 vtDataTypeFilter, /*[in]*/ DWORD	 dwAccessRightsFilter,	  /*[out]*/ LPENUMSTRING  * ppIEnumString);
	STDMETHOD(ChangeBrowsePosition)(/*[in]*/ OPCBROWSEDIRECTION dwBrowseDirection,/*[in]*/ LPCWSTR	szString);
	STDMETHOD(QueryAvailableProperties)(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR **ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes);
	STDMETHOD(GetItemProperties)(/*[in]*/ BSTR ItemID,/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ DWORD * pdwPropertyIDs,/*[out, size_is(,dwCount)] */VARIANT ** ppvData,/*[out, size_is(,dwCount)]*/ HRESULT **ppErrors);
	//	STDMETHOD(put_ClockRate)(/*[in]*/ DWORD newVal);
};



#endif //__XMLPLUGIN_H_
