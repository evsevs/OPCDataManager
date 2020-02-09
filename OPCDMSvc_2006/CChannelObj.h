// CChannelObj.h : Declaration of the CCChannelObj

#ifndef __CCHANNELOBJ_H_
#define __CCHANNELOBJ_H_

#include "resource.h"		// main symbols
//#include "Channel.h"
#include "Proxy_IChannelDataCallback.h"
#include <vector>
//#include "DBbase.h"
// Tag
#include "Tag.h"
// ObjectID
#include "ObjectID.h"
// _Message
#include "_Message.h"
// DataPlugin
#include "DataPlugin.h"
// Handlers
#include "Handlers.h"
// LocalNotify
#include "LocalNotify.h"
// CThread
#include "CThread.h"
#include "opcerror.h"
#include "simpleLogFile.h"
class CCChannelObj;
class CChannelBrowseObj;
class CCurrentBrowsePosition;




//Режимы канала
enum _ChannelMode {
	chmAutomatic,
	chmDisabled,
	chmEnabled
};
class CCurrentBrowsePosition  
{
public:
	short CurrentLevel;//счетчик текущей позиции (вверх-вниз)
	ISpaceBrowse* pSpaceBrowse;
	_ChannelID m_ChannelID;
	std::string m_CurrentPositionName;
	CCChannelObj* m_pCarrentChannel;
	CCurrentBrowsePosition()
	{
		pSpaceBrowse=NULL;
		CurrentLevel=0;//root
	}
	virtual ~CCurrentBrowsePosition()
	{
		if (pSpaceBrowse) pSpaceBrowse->Release();
	}
private:
	bool m_RootFlag;
};


/////////////////////////////////////////////////////////////////////////////
// CCChannelObj
class ATL_NO_VTABLE CCChannelObj :	virtual public CThread, 
									public _ChannelID, 
									virtual public CLocalNotify,
	public CComObjectRootEx<CComMultiThreadModel>,
	public IConnectionPointContainerImpl<CCChannelObj>,
	public CProxy_IChannelDataCallback<CCChannelObj>,
	public ICChannelObj,
	public ISupportErrorInfo,
	public IChannelTagDef
{
public:
	MSXML2::IXMLDOMNodePtr m_ChannelCnfgNode;
	  //	Возвращает количество тегов канала.
	  DWORD GetItemCount ();

	  //	Производится обработка очереди сообщений потока.
	  //	Сообщения посылаются методами с префиксом Out.
	  BOOL ClientMessageHandler ();
		
	  HANDLE m_hInitEvent;
	  
	  //	Возращает переменные со стереотипом стате, относящиеся к
	  //	каналу.
	  //	Должен быть защищен внутри.
	  HRESULT GetChannelStatus (FILETIME& ftLastUpdateTime, DWORD& dwBandWidth);

	  //	Переопределение функции, выполгняющейся в потоке, в
	  //	классе-наследнике.
	  virtual DWORD fbody ();

	  //	Вызывается после обновления тегов для извещения
	  //	клиентов.
	  void TagsUpdated (_UpdateNowMsg UpdateNowMsg	// Идентификаторы тегов, которые нужно обновить.
	  );

	  //	Функция обратного вызова.
	  virtual void Send_OnTagUpdate (_UpdateMsg* pUpdateMsg);

	  //	Метод производит изменения режима и состояния плагина.
	  //	return S_OK;
	  HRESULT SetChannelMode (_ChannelMode ChannelMode);

	  //	Метод производит инициализацию плагина.
	  HRESULT Initialize (_bstr_t bstrChannelString, _bstr_t bstrPluginString);

	  //	Метод производит деинициализацию канала.
	  bool Uninitialize ();

	//	const CTagStorage * get_m_TagStorage () const;

	  //	Время последнего обновления на сервере.
	  //	Переменная своя для каждого канала.
	  FILETIME m_ftLastUpdateTime;

	  //	Связано что-то с процентами изменения величины тега.
	  //	Переменная своя для каждого канала.
	  unsigned int m_dwBandWidth;
		
	  //	Частота внутреннего тактового генератора канала. (мс).
	  //	Параметр требуется для работы класса обновления кэша и
	  //	класса обновления данных в устройстве.
	  unsigned int m_ClockRate;
	  _ChannelMode m_ChannelMode;
	  _bstr_t m_bstrChannelString;
	  _bstr_t m_bstrPluginString;
	  _bstr_t m_Description;
	  //	Дата создания канала.
	  FILETIME m_CreateTime;
//	  CDBBase m_Server;
	  bool m_Init;
//	  DWORD m_DeviceUpdateMode;
	  std::string m_ConfigLogPath;//путь для хранения лог-ов
	  std::string m_UDLConfFile;
		
	  //Критические секции для изменения карты тегов.
	  CComCriticalSection	m_AddTagCS;

private:
	  //	Вызывается после обновления тегов. По приходй сообщения
		//	WM_TAGSUPDATED.
	
	  void OnTagsUpdated (MSG msg);
	  std::vector<CChannelBrowseObj*> m_Browsers;
	  CTagStorage *m_TagStorage;
	  //CDeviceUpdateHandler *m_Device;
public:	  CCacheUpdateHandler *m_Cache;
private:	  CDataPlugin *m_Plagin;
	  CLogFile_CS m_LogFile;

public:
	

	CCChannelObj()
	{
		m_Cache =NULL;
//		m_Device =NULL;
		m_Plagin=NULL;
		m_Init=false;
		m_dwBandWidth=0xFFFFFFFF;
		m_ClockRate=200;
		m_TagStorage=NULL;
		m_hInitEvent=0;
		//srand((unsigned)time( NULL ) );
		//m_LogFile=NULL;
	}
	void FinalRelease()
	{
		//	if (m_LogFile)
		//		delete m_LogFile;
		int x=0;x++;
	}
	//DECLARE_NO_REGISTRY()//DECLARE_REGISTRY_RESOURCEID(IDR_CCHANNELOBJ)
	DECLARE_NOT_AGGREGATABLE(CCChannelObj)
		
		//DECLARE_PROTECT_FINAL_CONSTRUCT()
		
		BEGIN_COM_MAP(CCChannelObj)
		COM_INTERFACE_ENTRY(ICChannelObj)
		COM_INTERFACE_ENTRY(IChannelTagDef)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
		COM_INTERFACE_ENTRY(IConnectionPointContainer)
		END_COM_MAP()
		BEGIN_CONNECTION_POINT_MAP(CCChannelObj)
		CONNECTION_POINT_ENTRY(IID_IChannelDataCallback)
		END_CONNECTION_POINT_MAP()
		
		
		// ICChannelObj
public:
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	void StartChannelHandler();
	void StopChannelHandler();
	STDMETHOD(DeleteTags)(/*[in]*/DWORD dwCount,/*[in,size_is(dwCount)]*/DWORD *dwHandles,/*[out,size_is(,dwCount)]*/HRESULT ** ppErrors);
	//	STDMETHOD(CreateTagDefEnum)(/*[in,out]*/ IEnumOPCDMTagDef**pTagDefEnum);
	//	STDMETHOD(GetTagByName)(/*[in]*/BSTR TagName,/*[in,out]*/ TagDefStruct *pTagDef);
	//	STDMETHOD(GetTagByID)(/*[in]*/ DWORD TagID, /*[in,out]*/  TagDefStruct* pTagDef);
	STDMETHOD(ChangeTagsDef)(DWORD dwCount,OPCHANDLE * pHandles,TagDefStruct *pNewDefs,HRESULT**ppErrors);
	STDMETHOD(CreateTags)(DWORD dwCount,TagDefStruct *pTagDefs,HRESULT**ppErrors);
	STDMETHOD(get_PluginProgID)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_PluginCnfgString)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ConfgStr)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_Description)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_Description)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_ChannelID)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(get_ChannelName)(/*[out, retval]*/ BSTR *pVal);
	void OnAsyncRead(_AsyncIORWMsg * mes);
	void OnAsyncWrite(_AsyncIORWMsg *mes);
	void AsWrite(_AsyncIORWMsg * mes);
	void AsRead(_AsyncIORWMsg * mes);
	CTag* GetTagRef(DWORD hServer);
	void OnSyncWrite(_SyncIORMsg* mes);
	void SWrite(_SyncIORMsg* mes);
	void OnSyncRead(_SyncIORMsg* mes);
	void SRead(_SyncIORMsg * mes);
	DWORD GetChannelID(DWORD hTag);
	STDMETHOD(WriteTags)(/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ OPCHANDLE * phServer,/*[in, size_is(dwCount)]*/ VARIANT * pItemValues, /*[out, size_is(,dwCount)]*/ HRESULT ** ppErrors);
	STDMETHOD(ReadTags)(/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ OPCHANDLE * phServer,/*[out, size_is(,dwCount)]*/ OPCITEMSTATE ** ppItemValues,/*[out, size_is(,dwCount)]*/ HRESULT ** ppErrors);
	STDMETHOD(GetBrowser)(/*[in,out]*/IUnknown ** pChannelBrowse);
	//STDMETHOD(get_DeviceUpdateMode)(/*[out, retval]*/ BOOL *pVal);
	//STDMETHOD(put_DeviceUpdateMode)(/*[in]*/ BOOL newVal);
	STDMETHOD(get_CreationTime)(/*[out, retval]*/ FILETIME *pVal);
	STDMETHOD(get_ClockRate)(/*[out, retval]*/ DWORD *pVal);
	STDMETHOD(put_ClockRate)(/*[in]*/ DWORD newVal);
	// инициализация тегов из XML
private:
	int InitializeTagFromXML(void);
public:
	// Функция для инициализации канала через CreateChannel объекта конфигурации
	HRESULT InitNoytFromXML(ChannelDef* pChannelDef);
	// сохранение атрибутов канала в XML. возвращает сформированный узел канала
	MSXML2::IXMLDOMNodePtr Save2XML();
};

/////////////////////////////////////////////////////////////////////////////
// CChannelBrowseObj
class ATL_NO_VTABLE CChannelBrowseObj ://:public virtual CBrowse ,
	public CComObjectRootEx<CComMultiThreadModel>,
	public ISpaceBrowse
{
public:


	CCurrentBrowsePosition m_CurPos;

	  CTagStorage *m_TagStorage;
//	  CExternalInfoHandler *m_ExternalInfo;
	CChannelBrowseObj()
	{
//		m_CurrentPositionName = "";
	  m_TagStorage = NULL;
//	  m_ExternalInfo = NULL;
		ATLTRACE("Создали объект Browser\n");
	}
	void FinalRelease()
	{
		int x=0;x++;
		ATLTRACE("Удалили объект Browser\n");
	}
//DECLARE_NO_REGISTRY()//DECLARE_REGISTRY_RESOURCEID(IDR_CCHANNELOBJ)
DECLARE_NOT_AGGREGATABLE(CChannelBrowseObj)

//DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CChannelBrowseObj)
	COM_INTERFACE_ENTRY(ISpaceBrowse)
END_COM_MAP()

public:
	STDMETHOD(ValidateItem)(/*[in]*/DWORD dwCount,/*[in, size_is(dwCount)]*/ OPCITEMDEF * pItemArray,/*[in]*/ BOOL bBlobUpdate,/*[out, size_is(,dwCount)]*/ OPCITEMRESULT ** ppValidationResults,/*[out, size_is(,dwCount)]*/ HRESULT** ppErrors);
	STDMETHOD(BrowseAccessPaths)(/*[in]*/LPCWSTR szItemID,/*[out]*/ LPENUMSTRING *ppIEnumString);
	STDMETHOD(GetItemID)(/*[in]*/LPCWSTR szItemDataID, /*[out]*/LPWSTR *szItemID);
	STDMETHOD(BrowseOPCItemIDs)(/*[in]*/OPCBROWSETYPE  dwBrowseFilterType,/*[in]*/ LPCWSTR	szFilterCriteria, /*[in]*/ VARTYPE	 vtDataTypeFilter, /*[in]*/ DWORD	 dwAccessRightsFilter,	  /*[out]*/ LPENUMSTRING  * ppIEnumString);
	STDMETHOD(ChangeBrowsePosition)(/*[in]*/ OPCBROWSEDIRECTION dwBrowseDirection,/*[in]*/ LPCWSTR	szString);
	STDMETHOD(QueryAvailableProperties)(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR **ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes);
	STDMETHOD(GetItemProperties)(/*[in]*/ BSTR ItemID,/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ DWORD * pdwPropertyIDs,/*[out, size_is(,dwCount)] */VARIANT ** ppvData,/*[out, size_is(,dwCount)]*/ HRESULT **ppErrors);
//	STDMETHOD(put_ClockRate)(/*[in]*/ DWORD newVal);
};
//OBJECT_ENTRY_NON_CREATEABLE_EX_AUTO(CLSID_CChannelObj,CCChannelObj)
#endif //__CCHANNELOBJ_H_
