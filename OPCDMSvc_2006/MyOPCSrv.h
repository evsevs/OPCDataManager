// MyOPCSrv.h : Declaration of the CMyOPCSrv

#ifndef __MYOPCSRV_H_
#define __MYOPCSRV_H_

#include "resource.h"		// main symbols
//#import "D:\DEVELOP\OPC\OPC2\OPCDA.TLB" raw_interfaces_only, raw_native_types, no_namespace, named_guids 

#include "OPCDataCallbackCP.h"
#include "OPCShutdownCP.h"
#include "MyTestConf.h"
#include <vector>
#include "cat_opc.h"
#include "CChannelObj.h"	// Added by ClassView
#include "opcerror.h"
#include <time.h>
#include "OPC_PACK.h"

#define _CHANNELMAP std::map<_ChannelID,CCChannelObj*>
//CHANGED
#define _OPCGROUPTAGMAP std::map<DWORD,COPCTag*> //std::map<_OPCTagID,COPCTag*>
class CMyOPCSrv;
extern std::list<CMyOPCSrv*> OPCServersList;



//класс для IDataObject
/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//class для хранения информации о соединении посредством IDataObject
/////////////////////////////////////////////////////////////////////////////////////


struct CEvsAdvise
{
	IAdviseSink* pAS;
	DWORD dwConnection;
	FORMATETC pFormatEtc;
};

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//class - шаблон для создания потока 
/////////////////////////////////////////////////////////////////////////////////////
template <class T>
class CEvsProxy_IAdviseSink
{
public:

	HRESULT CreateStreamWriteComplite(DWORD Count,std::list<COPCTag*> *pList,DWORD tid,DWORD dwConnection=0);
	HRESULT CreateStreamWithoutTime(DWORD Count,std::list<COPCTag*> *pList,DWORD DataSize,DWORD tid,DWORD dwConnection=0);
	HRESULT CreateStreamWithTime(DWORD Count,std::list<COPCTag*> *pList,DWORD DataSize,DWORD tid,DWORD dwConnection=0);

	void OnClose();
	void OnDataChange(
					FORMATETC * pFormatetc,  //Pointer to format information
					STGMEDIUM * pStgmed , //Pointer to storage medium
					DWORD dwConnection	);
	void OnRename( IMoniker * pmk  //Pointer to the new moniker of the object
						);
	void OnSave();
	void OnViewChange(
					DWORD dwAspect,  //Value specifying aspect of object
					LONG lindex 	 //Currently must be -1
						);
};

/////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
//class - шаблон для работы с IDataObject
/////////////////////////////////////////////////////////////////////////////////////

template <class T>
class ATL_NO_VTABLE evs_IDataObjectImpl : public IDataObject
{
	typedef CComEnum<IAdviseSink,
		&IID_IAdviseSink, IAdviseSink*,
		_CopyInterface<IAdviseSink> >
		CComEnumAviseSink;
public:

	std::list<CEvsAdvise*> AdviseMap;
	UINT fOPCSTMFORMATDATA;
	UINT fOPCSTMFORMATDATATIME;
	UINT fOPCSTMFORMATWRITECOMPLETE;
	evs_IDataObjectImpl()
	{
		fOPCSTMFORMATDATA=RegisterClipboardFormat("OPCSTMFORMATDATA");
		fOPCSTMFORMATDATATIME=RegisterClipboardFormat("OPCSTMFORMATDATATIME");
		fOPCSTMFORMATWRITECOMPLETE=RegisterClipboardFormat("OPCSTMFORMATWRITECOMPLETE");
	}
	STDMETHOD(GetData)(FORMATETC * pFormatetc,STGMEDIUM * pmedium)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetDataHere)(FORMATETC * pFormatetc,STGMEDIUM * pmedium)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetCanonicalFormatEtc)(FORMATETC * pFormatetcIn,FORMATETC * pFormatetcOut)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(QueryGetData)(FORMATETC * pFormatetc)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(SetData)( FORMATETC * pFormatetc,  //Pointer to the FORMATETC structure
						STGMEDIUM * pmedium,	 //Pointer to STGMEDIUM structure
						BOOL fRelease)			  //Indicates which object owns the storage 
						   // medium after the call is completed
	{
		return E_NOTIMPL;
	}

	STDMETHOD(EnumFormatEtc)(DWORD dwDirection,  //Specifies a value from the enumeration  // DATADIR
							IEnumFORMATETC ** ppenumFormatetc) //Address of output variable that receives the 
	{
		return E_NOTIMPL;
	}
	STDMETHOD(DAdvise)( FORMATETC * pFormatetc,  //Pointer to data of interest to the 
						   // advise sink
						DWORD advf, 			 //Flags that specify how the notification 
							// takes place
						IAdviseSink * pAdvSink,  //Pointer to the advise sink
						DWORD * pdwConnection	 //Pointer to a token that identifies this 
							  // connection
						)
	{

//		srand((unsigned)time( NULL ) );//устанавливаем генератор
s:		*pdwConnection=(DWORD)rand();
		std::list<CEvsAdvise*>::iterator itl;
		if (AdviseMap.size()!=0) 
		{
			for (itl=AdviseMap.begin();itl!=AdviseMap.end();++itl)
			{
				if(*pdwConnection==(*itl)->dwConnection)
					break;
			}
			if (itl==AdviseMap.end()) goto s;
		}
		//уникальный идентификатор соединения
				
		CEvsAdvise * pEvs = new CEvsAdvise;
		pEvs->dwConnection=*pdwConnection;
		pEvs->pFormatEtc=*pFormatetc;

		pEvs->pAS=pAdvSink;
		pEvs->pAS->AddRef();

		//Теперь нужно заносить в список
		AdviseMap.insert(AdviseMap.begin(),pEvs);
		return S_OK;
	}
	STDMETHOD(DUnadvise)(DWORD dwConnection  //Connection to remove
						)
	{
		std::list<CEvsAdvise*>::iterator itl;
		for (itl=AdviseMap.begin();itl!=AdviseMap.end();++itl)
		{
			if(dwConnection==(*itl)->dwConnection)
				break;
		}
		if (itl!=AdviseMap.end())
		{
			(*itl)->pAS->Release();
			delete (*itl);
			AdviseMap.erase(itl);
			return S_OK;
		}else
			return E_FAIL;
	}
	STDMETHOD(EnumDAdvise)( IEnumSTATDATA ** ppenumAdvise  //Address of output variable that 
								 // receives the IEnumSTATDATA 
								 // interface pointer
						)
	{
		return E_NOTIMPL;
	}
};


/////////////////////////////////////////////////////////////////////////////
// CMyOPCSrv
//##ModelId=3B2979EE0279

class CMyGroup;
class ATL_NO_VTABLE CMyOPCSrv : 
	public CComObjectRootEx<CComMultiThreadModel>,
	public CComCoClass<CMyOPCSrv, &CLSID_MyOPCSrv>,
	public IMyOPCSrv,
	public ISupportErrorInfo,
	public IOPCBrowseServerAddressSpace,
	public IOPCServer,
	public IConnectionPointContainerImpl<CMyOPCSrv>,
	public IOPCItemProperties,
//	public IOPCServerPublicGroups,
	public IOPCCommon,
	public CProxy_IOPCShutdown<CMyOPCSrv>,
	public CProxy_IOPCDataCallback<CMyOPCSrv>
{
public:
	//##ModelId=3B2979EE0370
	CMyOPCSrv()
	{
	//	CMyGroup * pMG;
	}
	~CMyOPCSrv()
	{
		OPCServersList.remove((CMyOPCSrv*)this);
	}

DECLARE_REGISTRY_RESOURCEID(IDR_MYOPCSRV)
DECLARE_NOT_AGGREGATABLE(CMyOPCSrv)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMyOPCSrv)
	COM_INTERFACE_ENTRY(IMyOPCSrv)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IOPCBrowseServerAddressSpace)
	COM_INTERFACE_ENTRY(IOPCServer)
	COM_INTERFACE_ENTRY(IOPCItemProperties)
//	COM_INTERFACE_ENTRY(IOPCServerPublicGroups)
	COM_INTERFACE_ENTRY(IOPCCommon)
END_COM_MAP()

BEGIN_CATEGORY_MAP(CMyOPCSrv)
	IMPLEMENTED_CATEGORY(CATID_OPCDAServer20)
END_CATEGORY_MAP()

BEGIN_CONNECTION_POINT_MAP(CMyOPCSrv)
	CONNECTION_POINT_ENTRY(IID_IOPCShutdown)
	CONNECTION_POINT_ENTRY(IID_IOPCDataCallback)
END_CONNECTION_POINT_MAP()

	//##ModelId=3B2979EE036C
	HRESULT virtual FinalConstruct()
	{
//	Error()	
	WaitForSingleObject(ConfObjectInitEvent,60000);
	//	pMyTestConf->m_LogFile<<"После проверки";
		ATLTRACE("Запускаем OPC server\n");
		m_pMyTestConf=pMyTestConf;
	//	m_pCurrentChannel = NULL;
			srand((unsigned)time( NULL ) );
		m_CurPos.m_pCarrentChannel=NULL;
		

		//Beep(200,1000);
	//	m_OPCServerState=OPC_STATUS_RUNNING
		if (m_pMyTestConf->IsSuspended())
		{
			return OPC_E_SUSPENDED;
		}
		OPCServersList.insert(OPCServersList.end(),this);
		return S_OK;
	}

// ISupportsErrorInfo
	//##ModelId=3B2979EE036A
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

	//##ModelId=3B2979EE0369
	void FinalRelease();
// IMyOPCSrv
public:
	void UpdateTagsRefs();
//	OPCSERVERSTATE m_OPCServerState;
	ULONG m_LocaleID;
	std::string m_ClientName;
	CCurrentBrowsePosition m_CurPos;
	//##ModelId=3B2979EE0304
	std::vector<CMyGroup*> m_Groups;
	CMyTestConf * m_pMyTestConf;
// IOPCBrowseServerAddressSpace
	//##ModelId=3B2979EE0367
	STDMETHOD(QueryOrganization)(OPCNAMESPACETYPE * pNameSpaceType);
	//##ModelId=3B2979EE0363
	STDMETHOD(ChangeBrowsePosition)(OPCBROWSEDIRECTION dwBrowseDirection, LPCWSTR szString);
	//##ModelId=3B2979EE035D
	STDMETHOD(BrowseOPCItemIDs)(OPCBROWSETYPE dwBrowseFilterType, LPCWSTR szFilterCriteria, USHORT vtDataTypeFilter, ULONG dwAccessRightsFilter, IEnumString * * ppIEnumString);
	//##ModelId=3B2979EE0359
	STDMETHOD(GetItemID)(LPWSTR szItemDataID, LPWSTR * szItemID);
	//##ModelId=3B2979EE0356
	STDMETHOD(BrowseAccessPaths)(LPCWSTR szItemID, IEnumString * * ppIEnumString);
// IOPCServer
	//##ModelId=3B2979EE034A
	STDMETHOD(AddGroup)(LPCWSTR szName, BOOL bActive, ULONG dwRequestedUpdateRate, OPCHANDLE hClientGroup, LONG * pTimeBias, FLOAT * pPercentDeadband, ULONG dwLCID, OPCHANDLE * phServerGroup, ULONG * pRevisedUpdateRate, REFIID riid, IUnknown * * ppUnk);
	//##ModelId=3B2979EE0342
	STDMETHOD(GetErrorString)(HRESULT dwError, ULONG dwLocale, LPWSTR * ppString);
	//##ModelId=3B2979EE033E
	STDMETHOD(GetGroupByName)(LPCWSTR szName, REFIID riid, IUnknown * * ppUnk);
	//##ModelId=3B2979EE033B
	STDMETHOD(GetStatus)(OPCSERVERSTATUS * * ppServerStatus);
	//##ModelId=3B2979EE0338
	STDMETHOD(RemoveGroup)(ULONG hServerGroup, BOOL bForce);
	//##ModelId=3B2979EE0334
	STDMETHOD(CreateGroupEnumerator)(OPCENUMSCOPE dwScope, REFIID riid, IUnknown * * ppUnk);
// IOPCItemProperties
	//##ModelId=3B2979EE032E
	STDMETHOD(QueryAvailableProperties)(LPWSTR szItemID, ULONG * pdwCount, ULONG * * ppPropertyIDs, LPWSTR * * ppDescriptions, USHORT * * ppvtDataTypes);
	//##ModelId=3B2979EE0328
	STDMETHOD(GetItemProperties)(LPWSTR szItemID, ULONG dwCount, ULONG * pdwPropertyIDs, VARIANT * * ppvData, HRESULT * * ppErrors);
	//##ModelId=3B2979EE0322
	STDMETHOD(LookupItemIDs)(LPWSTR szItemID, ULONG dwCount, ULONG * pdwPropertyIDs, LPWSTR * * ppszNewItemIDs, HRESULT * * ppErrors);
// IOPCServerPublicGroups
	//##ModelId=3B2979EE031C
//	STDMETHOD(GetPublicGroupByName)(LPCWSTR szName, REFIID riid, IUnknown * * ppUnk);
	//##ModelId=3B2979EE0319
//	STDMETHOD(RemovePublicGroup)(ULONG hServerGroup, BOOL bForce);
// IOPCCommon
	//##ModelId=3B2979EE0317
	STDMETHOD(SetLocaleID)(ULONG dwLcid);
	//##ModelId=3B2979EE0311
	STDMETHOD(GetLocaleID)(ULONG * pdwLcid);
	//##ModelId=3B2979EE030E
	STDMETHOD(QueryAvailableLocaleIDs)(ULONG * pdwCount, ULONG * * pdwLcid);
	//##ModelId=3B2979EE0346
	STDMETHOD(GetErrorString)(HRESULT dwError, LPWSTR * ppString);
	//##ModelId=3B2979EE030C
	STDMETHOD(SetClientName)(LPCWSTR szName);
};

// MyOPCSrv.h : Declaration of the CMyGroup

/////////////////////////////////////////////////////////////////////////////
//Приемник нотификаций для группы от канала
/////////////////////////////////////////////////////////////////////////////
// CMyGroup
//##ModelId=3B2979F002C9
class ATL_NO_VTABLE CMyGroup : virtual public _GroupID,
	public CComObjectRootEx</*CComMultiThreadModel*/CComMultiThreadModelNoCS>,
//	public CComCoClass<CMyGroup, &CLSID_MyGroup>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CMyGroup>,
	public IMyGroup,
	public IOPCAsyncIO,
	public IOPCAsyncIO2,
	public IOPCGroupStateMgt,
/*	public IOPCPublicGroupStateMgt,*/
	public IOPCItemMgt,
	public IOPCSyncIO,
//	public IDataObject,
	public CProxy_IOPCDataCallback<CMyGroup>,
	public evs_IDataObjectImpl<CMyGroup>,
	public CEvsProxy_IAdviseSink<CMyGroup>,
	public IChannelDataCallback
{
public:
	struct UpdateStruct
	{
		OPCHANDLE RealHandle;
		OPCHANDLE InterpretHandle;
		COPCTag* m_Iam;
	};
	//класс для хранения транзакции (у нас-то распределяется по каналам)
	class CTransactionWrapper:public _ObjectID
	{
	public:
		DWORD m_GlobalTagCount;
		bool m_bSended;
		CCChannelObj* m_pChannel;
	private:		ULONG m_InMessageCount;
					bool m_Configured;//сигнал об окончании конфигурации
					bool m_bCanceled;//говорит о том, что транзакция прервана
	public:
		void CancelTransaction()
		{
			m_bCanceled=true;
		}
		bool IsConfigured()
		{
			return m_Configured;
		}
		bool IsCanceled()
		{
			return m_bCanceled;
		}
		void ConfigComplite()
		{
			m_Configured=true;
		}
		DWORD IncMessageCount();
		bool IsTransactionComplite();
		std::vector<_AsyncIORWMsg*> m_MessageVector;//список сообщений,
													//отосланных для выполнения данной транзакции
		DWORD m_dwTransactionID;
		DWORD m_dwTransactionID2;
		DWORD m_dwCancelID;
		bool bActived;
		CTransactionWrapper()
		{
			bActived=true;
			m_bSended=false;
			m_pChannel=NULL;
			m_dwCancelID=0;
			m_dwTransactionID=0;
			m_Configured = false;
			m_InMessageCount=0;
			m_bSended=false;
			m_GlobalTagCount=0;
			m_dwTransactionID2=0;
			m_dwCancelID=0;
			m_bCanceled=false;
		}
		~CTransactionWrapper()
		{
			//Удаление сообщений
			for(UINT i=0;i<m_MessageVector.size();i++)
				delete m_MessageVector[i];
			m_MessageVector.clear();
		}

		bool operator==(const CTransactionWrapper &right) const
		{
			return m_dwTransactionID==right.m_dwTransactionID;
 		}
		bool operator==(const DWORD dwTransactionID) const
		{
			return m_dwTransactionID==dwTransactionID;
		}
		protected:
		
		private:
	};
	
	class CControlThread :public CThread
	{
	
		 virtual DWORD fbody ();
							//здесь будет производится проверка
							// на изменения и отсылка нотификаций
		 HRESULT OnTimerMessage(MSG msg,DWORD dwConnection=0,bool IsRefresh=false,DWORD dwTransactionID=0,DWORD dwTransactionID2=0);
		 void OnTransactionRead(MSG msg,bool ConfigComplite=false);
		 void OnTransactionWrite(MSG msg,bool ConfigComplite=false);
		 void OnChangeStateInactive2Active(MSG msg);
		 void OnSetNewState();
		 void OnCancel2(MSG msg);
		 
	public:
		void AsRead(_AsyncIORWMsg* msg);
		void AsRefresh(_AsyncIORWMsg*msg);
		void AsCancel(DWORD dwTransactionID);
		void SendInactive2Active(_AsyncIORWMsg * pAs);
		DWORD m_TimerID;
		CMyGroup * m_Owner;

	protected:
		// метод для обновления ссылок на РЕАЛЬНЫЕ теги каналов
		HRESULT OnUpdateTagRefs(void);
	};

	std::vector<CTransactionWrapper*> m_TransactionVector;//список транзакций
	CControlThread m_ControlThread;
	//##ModelId=3B2979F00397
	CMyGroup()
	{
		m_Enabled=true;
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_MYGROUP)
DECLARE_NOT_AGGREGATABLE(CMyGroup)

//DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CMyGroup)
	COM_INTERFACE_ENTRY(IMyGroup)
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IOPCAsyncIO)
	COM_INTERFACE_ENTRY(IOPCAsyncIO2)
	COM_INTERFACE_ENTRY(IOPCGroupStateMgt)
/*	COM_INTERFACE_ENTRY(IOPCPublicGroupStateMgt)*/
	COM_INTERFACE_ENTRY(IOPCItemMgt)
	COM_INTERFACE_ENTRY(IOPCSyncIO)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IChannelDataCallback)
END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CMyGroup)
	CONNECTION_POINT_ENTRY(IID_IOPCDataCallback)
END_CONNECTION_POINT_MAP()



	//##ModelId=3B2979F00396
	HRESULT FinalConstruct()
	{
		m_DelAddItemsCS.Init();
		m_TransactionAccessCS.Init();
		m_AsyncReadCS.Init();
		m_AsyncWriteCS.Init();
		m_pMyTestConf = pMyTestConf;
		m_ControlThread.Stop();
		srand(1);
  //  	CLogFile_CS GGG;
		//GGG.SetNewFullLogName("c:\\PETRENKO.log");
		//GGG<<"Create";
		return S_OK;
	
	}

void FinalRelease()
{
ATLTRACE ("Удаление группы (реальное)\n");
	m_ControlThread.Stop();
	m_TransactionAccessCS.Term();
	m_DelAddItemsCS.Term();
	m_AsyncReadCS.Term();
	m_AsyncWriteCS.Term();

	//удаление тегов
	_OPCGROUPTAGMAP::iterator itm;
	for(itm=m_Tags.begin();itm!=m_Tags.end();++itm)
	{
		delete itm->second;
	}
	m_Tags.clear();
}
// ISupportsErrorInfo
	//##ModelId=3B2979F00394
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// IMyGroup
public:
	void UpdateRealTagReferences();
	HRESULT CacheASyncRead(ULONG dwConnection, OPCDATASOURCE dwSource, ULONG dwCount, ULONG * phServer, ULONG * pTransactionID, HRESULT * * ppErrors);
	HRESULT CacheSyncRead(OPCDATASOURCE dwSource, ULONG dwCount, ULONG * phServer, OPCITEMSTATE * * ppItemValues, HRESULT * * ppErrors);
	HRESULT CacheRefresh(ULONG dwConnection, OPCDATASOURCE dwSource,DWORD dwTransactionID2, ULONG * pTransactionID);
	CComCriticalSection m_DelAddItemsCS;
	CComCriticalSection m_TransactionAccessCS;
	CComCriticalSection m_AsyncReadCS;
	CComCriticalSection m_AsyncWriteCS;
	bool m_Enabled;
	void GetTagRef(DWORD Count,OPCITEMRESULT *pItemArray, CTag **Tags);
	DWORD GetChannelID(DWORD hTag);
	//##ModelId=3B2979F00311LPCWSTR szName, 
	BOOL m_bActive;
			bool AsyncCacheFlag;//используется для указания, что асинхронное ЧТЕНИЕ производится из кэша.
	//DWORD dwRequestedUpdateRate,
	OPCHANDLE m_hClientGroup; //клиентский хендл для группы
	LONG m_TimeBias;	//добавка наверное к локальному времени
	FLOAT m_PercentDeadband;//отклонение в процентах (только для dwEUType)
	DWORD m_dwLCID; //локал ид
	DWORD m_UpdateRate; //принятый UpdateRate

	CMyTestConf * m_pMyTestConf;
	CMyOPCSrv * m_pOPCSrv;
	_OPCGROUPTAGMAP m_Tags;
	typedef std::map<OPCHANDLE/*Interpret*/,OPCHANDLE/*Server*/> INTERPRET2SERVERMap;
	INTERPRET2SERVERMap  m_InterpretHandleMap;//используется для неоднократного добавления тегов в группу
// IOPCAsyncIO
	//##ModelId=3B2979F00381
	STDMETHOD(Read)(ULONG dwConnection, OPCDATASOURCE dwSource, ULONG dwCount, ULONG * phServer, ULONG * pTransactionID, HRESULT * * ppErrors);
	//##ModelId=3B2979F0036D
	STDMETHOD(Write)(ULONG dwConnection, ULONG dwCount, ULONG * phServer, VARIANT * pItemValues, ULONG * pTransactionID, HRESULT * * ppErrors);
	//##ModelId=3B2979F00369
	STDMETHOD(Refresh)(ULONG dwConnection, OPCDATASOURCE dwSource, ULONG * pTransactionID);
	//##ModelId=3B2979F00365
	STDMETHOD(Cancel)(ULONG dwTransactionID);
// IOPCAsyncIO2
	//##ModelId=3B2979F00388
	STDMETHOD(Read)(ULONG dwCount, ULONG * phServer, ULONG dwTransactionID, ULONG * pdwCancelID, HRESULT * * ppErrors);
	//##ModelId=3B2979F00375
	STDMETHOD(Write)(ULONG dwCount, ULONG * phServer, VARIANT * pItemValues, ULONG dwTransactionID, ULONG * pdwCancelID, HRESULT * * ppErrors);
	//##ModelId=3B2979F00361
	STDMETHOD(Refresh2)(OPCDATASOURCE dwSource, ULONG dwTransactionID, ULONG * pdwCancelID);
	//##ModelId=3B2979F0035F
	STDMETHOD(Cancel2)(ULONG dwCancelID);
	//##ModelId=3B2979F0035C
	STDMETHOD(SetEnable)(BOOL bEnable);
	//##ModelId=3B2979F0035A
	STDMETHOD(GetEnable)(BOOL * pbEnable);
// IOPCGroupStateMgt
	//##ModelId=3B2979F0034F
	STDMETHOD(GetState)(ULONG * pUpdateRate, BOOL * pActive, LPWSTR * ppName, LONG * pTimeBias, FLOAT * pPercentDeadband, ULONG * pLCID, ULONG * phClientGroup, ULONG * phServerGroup);
	//##ModelId=3B2979F00346
	STDMETHOD(SetState)(ULONG * pRequestedUpdateRate, ULONG * pRevisedUpdateRate, BOOL* pActive, LONG * pTimeBias, FLOAT * pPercentDeadband, ULONG * pLCID, ULONG * phClientGroup);
	//##ModelId=3B2979F00344
	STDMETHOD(SetName)(LPCWSTR szName);
	//##ModelId=3B2979F0033D
	STDMETHOD(CloneGroup)(LPCWSTR szName, REFIID riid, IUnknown * * ppUnk);
// IOPCPublicGroupStateMgt
	//##ModelId=3B2979F00358
/*	STDMETHOD(GetState)(LONG * pPublic);
	//##ModelId=3B2979F0033C
	STDMETHOD(MoveToPublic)();
*/// IOPCItemMgt
	//##ModelId=3B2979F00337
	STDMETHOD(AddItems)(ULONG dwCount, OPCITEMDEF * pItemArray, OPCITEMRESULT * * ppAddResults, HRESULT * * ppErrors);
	//##ModelId=3B2979F00330
	STDMETHOD(ValidateItems)(ULONG dwCount, OPCITEMDEF * pItemArray, BOOL bBlobUpdate, OPCITEMRESULT * * ppValidationResults, HRESULT * * ppErrors);
	//##ModelId=3B2979F0032C
	STDMETHOD(RemoveItems)(ULONG dwCount, ULONG * phServer, HRESULT * * ppErrors);
	//##ModelId=3B2979F00327
	STDMETHOD(SetActiveState)(ULONG dwCount, ULONG * phServer, BOOL bActive, HRESULT * * ppErrors);
	//##ModelId=3B2979F00321
	STDMETHOD(SetClientHandles)(ULONG dwCount, ULONG * phServer, ULONG * phClient, HRESULT * * ppErrors);
	//##ModelId=3B2979F0031C
	STDMETHOD(SetDatatypes)(ULONG dwCount, ULONG * phServer, USHORT * pRequestedDatatypes, HRESULT * * ppErrors);
	//##ModelId=3B2979F00319
	STDMETHOD(CreateEnumerator)(REFIID riid, IUnknown * * ppUnk);
// IOPCSyncIO
	//##ModelId=3B2979F0038E
	STDMETHOD(Read)(OPCDATASOURCE dwSource, ULONG dwCount, ULONG * phServer, OPCITEMSTATE * * ppItemValues, HRESULT * * ppErrors);
	//##ModelId=3B2979F0037C
	STDMETHOD(Write)(ULONG dwCount, ULONG * phServer, VARIANT * pItemValues, HRESULT * * ppErrors);
// IDataObject
//	HRESULT GetData(FORMATETC * pFormatetc,STGMEDIUM * pmedium);
//	HRESULT GetDataHere(FORMATETC * pFormatetc, STGMEDIUM * pmedium );
	STDMETHOD (OnChannelDataChange)();
	STDMETHOD (DeletedTags)(DWORD dwCount,OPCHANDLE *hSrvHandles);


//НОТИФИКАЦИЯ 2.03
	HRESULT CreateReadOrChangeNotify(DWORD Count,std::list<COPCTag*> *pList,DWORD dwTransactionID);
	HRESULT CreateWriteNotify(DWORD Count,std::list<COPCTag*> *pList,DWORD dwTransactionID);
///Асинхронное чтение
	HRESULT AsyncReadInMass(ULONG dwConnection, OPCDATASOURCE dwSource, ULONG dwCount, ULONG * phServer, ULONG * pTransactionID,DWORD dwTransactionID2,ULONG *pdwCancelID, HRESULT * * ppErrors);
///Асинхронная запись
	HRESULT AsyncWriteInMass(ULONG dwConnection, ULONG dwCount, ULONG * phServer, VARIANT * pItemValues, ULONG * pTransactionID,DWORD dwTransactionID2,ULONG *pdwCancelID, HRESULT * * ppErrors);

};
OBJECT_ENTRY_AUTO(CLSID_MyOPCSrv, CMyOPCSrv)
#endif //__MYOPCSRV_H_
