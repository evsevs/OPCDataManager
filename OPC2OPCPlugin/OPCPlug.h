// OPCPlug.h : Declaration of the COPCPlug

#ifndef __OPCPLUG_H_
#define __OPCPLUG_H_

#include "resource.h"       // main symbols
#include "Proxy_IPluginDataCallback.h"
#include "NotifyRecipients.h"
#include <vector>
#include "ControlThread.h"
//#include <comdef.h>
#include "HelperFunc.h"
#include "SimpleLogFile.h"	// Added by ClassView

static const GUID CATID_DataManagerPlugin = 
{ 0x53b5fc45, 0xc8cc, 0x4f4f, { 0x90, 0x9d, 0x35, 0xf, 0xb9, 0x17, 0x6d, 0x15 } };
/////////////////////////////////////////////////////////////////////////////
// COPCPlug
//##ModelId=3C4E3C78014A
class ATL_NO_VTABLE COPCPlug : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<COPCPlug, &CLSID_OPCPlug>,
	public IConnectionPointContainerImpl<COPCPlug>,
	public IPluginConfig,
	public IPluginData,
	public ISupportErrorInfo,
//	public ISpaceBrowse,
	public CProxy_IPluginDataCallback<COPCPlug>

{
public:
	//##ModelId=3C4E3C780355
	OPCHANDLE* m_xpHandles;
	COPCPlug()
	{
		m_xpHandles=NULL;
		m_xpSync=NULL;
	//	CoInitializeEx(NULL,COINIT_MULTITHREADED);
	m_GroupHandleServer=m_GroupHandleClient=1;
	//m_TagsIsInGroup=false;
	IsConfigured=false;
	IsDisconnected=false;
	m_ConfigCS.Init();
	m_pNotify=NULL;
	bStatus=false;
	m_LogFile.SetNewFullLogName("C:\\OPC2OPCPluginDefault.log");
	//m_pStreamOPCServer=NULL;
	//m_pStreamOPCGroup=NULL;
	}
	void FinalRelease()
	{
		DisconnectFromAll();
		if (m_xpHandles)
			CoTaskMemFree(m_xpHandles);
		m_ControlThread.Stop();
		// TODO: Очистить список итемов по выходу
		m_ConfigCS.Term();
		ATLTRACE("выгрузка канала\n");
	//	CoUninitialize();
	}
DECLARE_REGISTRY_RESOURCEID(IDR_OPCPLUG)
DECLARE_NOT_AGGREGATABLE(COPCPlug)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(COPCPlug)
	COM_INTERFACE_ENTRY(IPluginConfig)
	COM_INTERFACE_ENTRY(IPluginData)
//	COM_INTERFACE_ENTRY(ISpaceBrowse)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
END_COM_MAP()
BEGIN_CONNECTION_POINT_MAP(COPCPlug)
	CONNECTION_POINT_ENTRY(IID_IPluginDataCallback)
END_CONNECTION_POINT_MAP()

BEGIN_CATEGORY_MAP(COPCPlug)
	IMPLEMENTED_CATEGORY(CATID_DataManagerPlugin)
END_CATEGORY_MAP()


	//##ModelId=3C4E3C780356
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);
// IOPCPlug
private:
	//источник для чтения данных из группы
	OPCDATASOURCE m_GroupReadSource;
	bool ParseInitializationString(const _bstr_t InitString,std::vector<ParametersVal> &ParamStruct);
	_variant_t GetParameter(const _bstr_t ParamName,std::vector<ParametersVal> &ParVal);
	CNotifyBase<COPCPlug> * m_pNotify;//переменная класса для приема нотификаций
	//проверка какие нотификации использовать для сервера?
	bool IsServerVersion203();
	std::vector<ParametersVal> MyParams;
	std::string OPCServerName;
	std::string ServerProgID;
	std::string ComputerName;
	CLSID ServerGUID;
	_bstr_t ConfigString;
	//пока реализуем  только одну группу
	CControlThread<COPCPlug> m_ControlThread;
	OPCHANDLE m_GroupHandleClient,m_GroupHandleServer;
	//bool m_TagsIsInGroup; //для контроля, что группа уже сформировалась.
	NotifyItemMap m_ItemList;
	NotifyItemMap m_NotiItems;
	bool IsInGroup(OPCHANDLE handle,OPCHANDLE &hServer);
public:	CComCriticalSection m_ConfigCS;
public:
	//IStream * m_pStreamOPCServer;
	//IStream * m_pStreamOPCGroup;
	CLogFile_CS m_LogFile;
	IOPCSyncIO *m_xpSync;
	void OwnerOnDataChange(DWORD dwTransid,OPCHANDLE hGroup,HRESULT hrMasterquality,HRESULT hrMastererror,DWORD dwCount,OPCHANDLE* phClientItems,VARIANT*pvValues,WORD * pwQualities,FILETIME *pftTimeStamps,HRESULT *pErrors);
	void OwnerOnDataChange(LPFORMATETC pFE, LPSTGMEDIUM pSTM);
	HRESULT ReAddToNotify();
	bool FlagLocal;
	HRESULT ReInit();
	bool bStatus;//true - активен
	HRESULT GetOPCServerState(DWORD &dwStatus);
	DWORD m_ControlThreadPeriod; //уже в милисекундах
	DWORD m_ControlThreadErCount;

	void SetControlThreadSettings(std::vector<ParametersVal> &ParVal);
	
	bool IsDisconnected;
	bool IsConfigured;
	HRESULT DisconnectFromAll();
//	DWORD m_ControlThreadRate;
	CComPtr<IOPCServer> m_pServer;//указатель на интерфейс сервера

	//CComPtr<IOPCServer> m_pServerForControl;//для потока контроля
	//CComPtr<IOPCItemMgt> m_pGroupForControl;//для потока контроля
	
	CComPtr<IOPCCommon> m_pCommon;
	CComPtr<IOPCBrowseServerAddressSpace> m_pOPCBrow;
		//для хранения указателей на группы
	//std::vector< CAdapt< CComPtr< IOPCItemMgt > > > m_Groups;
	CComPtr<IOPCItemMgt> m_Group;
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
	///ISpaceBrowse
	//##ModelId=3C4E3C79000D
//	STDMETHOD(ValidateItem)(/*[in]*/DWORD dwCount,/*[in, size_is(dwCount)]*/ OPCITEMDEF * pItemArray,/*[in]*/ BOOL bBlobUpdate,/*[out, size_is(,dwCount)]*/ OPCITEMRESULT ** ppValidationResults,/*[out, size_is(,dwCount)]*/ HRESULT** ppErrors);
	//##ModelId=3C4E3C79002A
//	STDMETHOD(BrowseAccessPaths)(/*[in]*/LPCWSTR szItemID,/*[out]*/ LPENUMSTRING *ppIEnumString);
	//##ModelId=3C4E3C79003D
//	STDMETHOD(GetItemID)(/*[in]*/LPCWSTR szItemDataID, /*[out]*/LPWSTR *szItemID);
	//##ModelId=3C4E3C790051
//	STDMETHOD(BrowseOPCItemIDs)(/*[in]*/OPCBROWSETYPE  dwBrowseFilterType,/*[in]*/ LPCWSTR	szFilterCriteria, /*[in]*/ VARTYPE	 vtDataTypeFilter, /*[in]*/ DWORD	 dwAccessRightsFilter,	  /*[out]*/ LPENUMSTRING  * ppIEnumString);
	//##ModelId=3C4E3C790066
//	STDMETHOD(ChangeBrowsePosition)(/*[in]*/ OPCBROWSEDIRECTION dwBrowseDirection,/*[in]*/ LPCWSTR	szString);
	//##ModelId=3C4E3C790083
//	STDMETHOD(QueryAvailableProperties)(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR **ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes);
	//##ModelId=3C4E3C790099
//	STDMETHOD(GetItemProperties)(/*[in]*/ BSTR ItemID,/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ DWORD * pdwPropertyIDs,/*[out, size_is(,dwCount)] */VARIANT ** ppvData,/*[out, size_is(,dwCount)]*/ HRESULT **ppErrors);

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

#endif //__OPCPLUG_H_
