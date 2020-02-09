// MyOPCSrv.cpp : Implementation of CMyOPCSrv
#include "stdafx.h"
#include "OPCDMSvc_h.h"
#include "MyOPCSrv.h"
#include "opccomn_i.c"
#include "opcda_i.c"
#include <algorithm>
// DONE: Переделать асинхронныеметоды (и сообщения) для работы не по событиям
// DONE: а по сообщениям, которые будут приходтиь в ControlThread группы.
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//Вспомогательные классы 
/////////////////////////////////////////////////////////////////////////////
// класс для копирования CMyGroup (имени) в OLECHAR для использования в IEnumString

template <class S,class D>
class _CopyXSTR
{
public:
	static HRESULT copy(D* p1, const S* p2)
	{
		USES_CONVERSION;
		HRESULT hr = S_OK;
		(*p1) = (LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((*p2)->get_m_sObjectName().length()+1));
		if (*p1 == NULL)
			hr = E_OUTOFMEMORY;
		else
			ocscpy(*p1,A2OLE((*p2)->get_m_sObjectName().c_str()));
		return hr;
	}
	static void init(LPOLESTR* p) {*p = NULL;}
	static void destroy(LPOLESTR* p) { CoTaskMemFree(*p);}
};

/////////////////////////////////////////////////////////////////////////////
// класс для копирования CMyGroup в IUknown для использования в IEnumUknown
template <class S,class D>
class _CopyXIU
{
public:
	static HRESULT copy(D* p1, const S* p2)
	{
		USES_CONVERSION;
		HRESULT hr = S_OK;
		hr=(*p2)->QueryInterface(IID_IUnknown,(void**)p1);
		return hr;
	}
	static void init(LPUNKNOWN* p) {*p = NULL;}
	static void destroy(LPUNKNOWN* p) { (*p)->Release();}
};

template <class S,class D>

class _CopyOPCITEMATTRIBUTES
{
	public:
		static HRESULT copy(D* pD,const S* pS)
		{
			USES_CONVERSION;
			HRESULT hr=S_OK;
			//Выделение памяти
			*pD=(OPCITEMATTRIBUTES*)CoTaskMemAlloc(sizeof(OPCITEMATTRIBUTES));
			hr=pS->second->get_pOPCITEMATTRIBUTES(*pD);
			
			//(*pD)->bActive = pS->second->m_OPCActive;
			//(*pD)->hClient=pS->second->get_ClientHandle();
			return hr;
		}
		static void init(OPCITEMATTRIBUTES** p) {*p=NULL;}
		static void destroy(OPCITEMATTRIBUTES** p)
		{
			CoTaskMemFree((*p)->szAccessPath);
			CoTaskMemFree((*p)->szItemID);
			VariantClear(&(*p)->vEUInfo);
			CoTaskMemFree(*p);
		}
};
///////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
//IAdviseSink
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
template <class T>
HRESULT CEvsProxy_IAdviseSink<T>::CreateStreamWriteComplite(DWORD Count,std::list<COPCTag*> *pList,DWORD tid,DWORD dwConnection)
	{
/*		OPCGROUPHEADERWRITE
OPCITEMHEADERWRITE[hdr.dwItemCount]
*/	
		int  HdrSize, TotalSize;
		T* pT= static_cast<T*>(this);
		std::list<COPCTag*>::iterator itl;
		// Allocate the Data Stream
		//
		HdrSize = sizeof(OPCGROUPHEADERWRITE) + Count * sizeof(OPCITEMHEADERWRITE);
		TotalSize = HdrSize ;

		char * gp;
		HGLOBAL gh;

		gh = GlobalAlloc( GMEM_FIXED, TotalSize );
		if(gh == NULL)
		{
			// If no memory, For now we just give up and return;
			// But a better error handler would be nice
			//
			return S_OK;
		}
		gp = (char*)GlobalLock(gh);

		OPCGROUPHEADERWRITE * GrpPtr;
		OPCITEMHEADERWRITE * ItemHdr1;

		GrpPtr = (OPCGROUPHEADERWRITE *) gp;
		ItemHdr1 = (OPCITEMHEADERWRITE *) (gp + sizeof(OPCGROUPHEADERWRITE));

		// Fill in the Group header
		//
		GrpPtr->dwItemCount = Count;
		GrpPtr->hClientGroup = pT->m_hClientGroup;//	m_ClientGroupHandle;
		GrpPtr->hrStatus = S_OK;
		GrpPtr->dwTransactionID = tid;

		// Now fill in the Item Information
		//
		
//		for(j=0; j<Count; j++)
		for(itl=pList->begin();itl!=pList->end();++itl)
		{
			// Get serverhandle of items to send
			// We are be in a critical seciton here
			//
			//i = ItemHandleList[j];

			// Get the ItemHeader info
			//
			//ItemPtr(i)->CheckDeviceWrite( &ItemHdr1->dwError);

			ItemHdr1->dwError = (*itl)->get_m_LastError();
			if (FAILED(ItemHdr1->dwError))
				GrpPtr->hrStatus=S_FALSE ;
			ItemHdr1->hClient = (*itl)->get_ClientHandle();//ItemPtr(i)->GetHandle();
					
			// The update the pointers
			//
			ItemHdr1++;
		}

		// And invoke the callback
		//
		STGMEDIUM stm;
		FORMATETC fe;

		fe.cfFormat = pT->fOPCSTMFORMATWRITECOMPLETE;
		fe.ptd = NULL;
		fe.dwAspect = DVASPECT_CONTENT;
		fe.lindex = -1;
		fe.tymed = TYMED_HGLOBAL;

		stm.tymed = TYMED_HGLOBAL;
		stm.hGlobal = gh;
		stm.pUnkForRelease = NULL;

		OnDataChange(&fe, &stm,dwConnection);

		// And free the storage
		//
		GlobalFree(gh);

		return S_OK;
	}
template <class T>
HRESULT CEvsProxy_IAdviseSink<T>::CreateStreamWithoutTime(DWORD Count,std::list<COPCTag*> *pList,DWORD DataSize,DWORD tid,DWORD dwConnection)
	{
		T* pT= static_cast<T*>(this);
		int  HdrSize, TotalSize;
		std::list<COPCTag*>::iterator itl;
		HdrSize = sizeof(OPCGROUPHEADER) + Count * sizeof(OPCITEMHEADER2);	// with time
		TotalSize = HdrSize + DataSize;
		char * gp;
		HGLOBAL gh;

		gh = GlobalAlloc( GMEM_FIXED, TotalSize );
		if(gh == NULL)
		{
			// If no memory, For now we just give up and return;
			// But a better error handler would be nice
			//
			return S_OK;
		}
		gp = (char*)GlobalLock(gh);

		OPCGROUPHEADER * GrpPtr;
		OPCITEMHEADER2 * ItemHdr1;	// With Time
		char * DataPtr;

		GrpPtr = (OPCGROUPHEADER *) gp;
		ItemHdr1 = (OPCITEMHEADER2 *) (gp + sizeof(OPCGROUPHEADER));	//With Time
		DataPtr = gp + HdrSize;

		// Fill in the Group header
		//
		GrpPtr->dwSize = TotalSize;
		GrpPtr->dwItemCount = Count;
		GrpPtr->hClientGroup =	pT->m_hClientGroup;
		GrpPtr->hrStatus = S_OK;
		GrpPtr->dwTransactionID = tid;

		// Now fill in the Item Information
		//

		/*for(j=0; j<Count; j++)*/
		//_variant_t x;
		VARIANT x;
		VariantInit(&x);
		FILETIME ftx;
		HRESULT hrrr;
		for(itl=pList->begin();itl!=pList->end();++itl)
		{
			int vsize;
			
			(*itl)->ReadBaseValues(x,ItemHdr1->wQuality,hrrr,ftx);
			
			if (FAILED(hrrr))
				GrpPtr->hrStatus=S_FALSE ;

			if (pT->AsyncCacheFlag)
				if (!(pT->m_bActive&&(*itl)->m_OPCActive))
				{ //если что-то неактивно...
					ItemHdr1->wQuality =OPC_QUALITY_OUT_OF_SERVICE;
				}

			ItemHdr1->hClient = (*itl)->get_ClientHandle();//ItemPtr(i)->GetHandle();
			ItemHdr1->dwValueOffset = DataPtr - gp;
			ItemHdr1->wReserved = 0;
					
			// Plus the variant
			// Note that any 'pointer' in the variant will be meaningless
			//
			vsize = OPCVariantPack(DataPtr, &x);

			// The update the pointers
			//
			ItemHdr1++;
			DataPtr += vsize;
		}
		VariantClear(&x);

		// And invoke the callback
		//
		STGMEDIUM stm;
		FORMATETC fe;

		fe.cfFormat = pT->fOPCSTMFORMATDATA;		// with time
		fe.ptd = NULL;
		fe.dwAspect = DVASPECT_CONTENT;
		fe.lindex = -1;
		fe.tymed = TYMED_HGLOBAL;

		stm.tymed = TYMED_HGLOBAL;
		stm.hGlobal = gh;
		stm.pUnkForRelease = NULL;
		OnDataChange(&fe, &stm,dwConnection);
		// And free the storage
		GlobalFree(gh);
		return S_OK;

	}
template <class T>
HRESULT CEvsProxy_IAdviseSink<T>::CreateStreamWithTime(DWORD Count,std::list<COPCTag*> *pList,DWORD DataSize,DWORD tid,DWORD dwConnection)
	{
		T* pT= static_cast<T*>(this);
		int HdrSize, TotalSize;
		std::list<COPCTag*>::iterator itl;
		HdrSize = sizeof(OPCGROUPHEADER) + Count * sizeof(OPCITEMHEADER1);	// with time
		TotalSize = HdrSize + DataSize;

		char * gp;
		HGLOBAL gh;

		gh = GlobalAlloc( GMEM_FIXED, TotalSize );
		if(gh == NULL)
		{
			// If no memory, For now we just give up and return;
			// But a better error handler would be nice
			//
			return S_OK;
		}
		gp = (char*)GlobalLock(gh);

		OPCGROUPHEADER * GrpPtr;
		OPCITEMHEADER1 * ItemHdr1;	// With Time
		char * DataPtr;

		GrpPtr = (OPCGROUPHEADER *) gp;
		ItemHdr1 = (OPCITEMHEADER1 *) (gp + sizeof(OPCGROUPHEADER));	//With Time
		DataPtr = gp + HdrSize;

		// Fill in the Group header
		//
		GrpPtr->dwSize = TotalSize;
		GrpPtr->dwItemCount = Count;
		GrpPtr->hClientGroup =	pT->m_hClientGroup;
		GrpPtr->hrStatus = S_OK;
		GrpPtr->dwTransactionID = tid;

		// Now fill in the Item Information
		//

		/*for(j=0; j<Count; j++)*/
		//_variant_t x;
		VARIANT x;
		VariantInit(&x);
		HRESULT hrrr;
		for(itl=pList->begin();itl!=pList->end();++itl)
		{
			int vsize;
			(*itl)->ReadBaseValues(x,ItemHdr1->wQuality,hrrr,ItemHdr1->ftTimeStampItem);
			if (FAILED(hrrr))
				GrpPtr->hrStatus=S_FALSE ;
			ItemHdr1->hClient = (*itl)->get_ClientHandle();//ItemPtr(i)->GetHandle();
			ItemHdr1->dwValueOffset = DataPtr - gp;
			ItemHdr1->wReserved = 0;
			if (pT->AsyncCacheFlag)
				if (!(pT->m_bActive&&(*itl)->m_OPCActive))
				{ //если что-то неактивно...
					ItemHdr1->wQuality =OPC_QUALITY_OUT_OF_SERVICE;
				}		
			// Plus the variant
			// Note that any 'pointer' in the variant will be meaningless
			//
			vsize = OPCVariantPack(DataPtr, &x);

			// The update the pointers
			//
			ItemHdr1++;
			DataPtr += vsize;
		}
		VariantClear(&x);

		// And invoke the callback
		//
		STGMEDIUM stm;
		FORMATETC fe;

		fe.cfFormat = pT->fOPCSTMFORMATDATATIME;		// with time
		fe.ptd = NULL;
		fe.dwAspect = DVASPECT_CONTENT;
		fe.lindex = -1;
		fe.tymed = TYMED_HGLOBAL;

		stm.tymed = TYMED_HGLOBAL;
		stm.hGlobal = gh;
		stm.pUnkForRelease = NULL;
		OnDataChange(&fe, &stm,dwConnection);
		// And free the storage
		GlobalFree(gh);
		return S_OK;
	}


template <class T>
void CEvsProxy_IAdviseSink<T>::OnClose()
	{
	}
template <class T>
void CEvsProxy_IAdviseSink<T>::OnDataChange(
					FORMATETC * pFormatetc,  //Pointer to format information
					STGMEDIUM * pStgmed,  //Pointer to storage medium
					DWORD dwConnection	)
	{
		HRESULT hr=S_OK;
		T* pT= static_cast<T*>(this);
	//	int nConnectionIndex;
		std::list<CEvsAdvise*>::iterator itl;
		for (itl=pT->AdviseMap.begin();itl!=pT->AdviseMap.end();++itl)			
		{
			if (dwConnection)
				if ((*itl)->dwConnection!=dwConnection)
					continue;
			if ((pFormatetc->cfFormat !=(*itl)->pFormatEtc.cfFormat))
				continue;
			
			
			pT->Lock();
			CComPtr<IUnknown> sp = (*itl)->pAS;
			pT->Unlock();
			IAdviseSink* pChan = reinterpret_cast<IAdviseSink*>(sp.p);
			
			if (pChan!=NULL)
				pChan->OnDataChange(pFormatetc,pStgmed);
		}
		return;
	}
template <class T>
void CEvsProxy_IAdviseSink<T>::OnRename( IMoniker * pmk  //Pointer to the new moniker of the object
						)
	{
	}
template <class T>
void CEvsProxy_IAdviseSink<T>::OnSave()
	{
	}
template <class T>
void CEvsProxy_IAdviseSink<T>::OnViewChange(
					DWORD dwAspect,  //Value specifying aspect of object
					LONG lindex 	 //Currently must be -1
						)
	{
	}


/////////////////////////////////////////////////////////////////////////////
// CMyOPCSrv

STDMETHODIMP CMyOPCSrv::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMyOPCSrv
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
STDMETHODIMP CMyOPCSrv::QueryOrganization(OPCNAMESPACETYPE * pNameSpaceType)
{
m_pMyTestConf->m_LogFile<<"Вызов QueryOrganization\n";
	if (pNameSpaceType == NULL)
		return E_POINTER;
	*pNameSpaceType = OPC_NS_HIERARCHIAL;//иерархическое пространоство сервера
	
	return S_OK;
}
STDMETHODIMP CMyOPCSrv::ChangeBrowsePosition(OPCBROWSEDIRECTION dwBrowseDirection, LPCWSTR szString)
{
	m_pMyTestConf->m_LogFile<<"Вызов ChangeBrowsePosition";// Direction= %d\n",dwBrowseDirection);
//	return S_OK;
	USES_CONVERSION;
	std::string str;
	_CHANNELMAP::iterator itm;

	if (szString) str = W2A(szString);
	else str="";

	int pos=-1;
//	dwBrowseDirection = OPC_BROWSE_UP;
	switch(dwBrowseDirection)
	{
	case OPC_BROWSE_UP:
		//szString - ignore
		if (m_CurPos.m_ChannelID.get_m_hObjectHandle()==0) return E_FAIL;
		if (m_CurPos.pSpaceBrowse)
		{
			if (m_CurPos.pSpaceBrowse->ChangeBrowsePosition(dwBrowseDirection,szString)!=S_OK)
			{
				m_CurPos.m_CurrentPositionName="";
				m_CurPos.m_ChannelID.set_m_hObjectHandle(0);
				m_CurPos.m_pCarrentChannel = NULL;
				if (m_CurPos.pSpaceBrowse) m_CurPos.pSpaceBrowse->Release();
				m_CurPos.pSpaceBrowse=NULL;
				m_CurPos.CurrentLevel=0;//root
			}else
			{
				m_CurPos.CurrentLevel--;
				if (m_CurPos.CurrentLevel==0)
				{
					m_CurPos.m_CurrentPositionName="";
					m_CurPos.m_ChannelID.set_m_hObjectHandle(0);
					m_CurPos.m_pCarrentChannel = NULL;
					if (m_CurPos.pSpaceBrowse) m_CurPos.pSpaceBrowse->Release();
					m_CurPos.pSpaceBrowse=NULL;
				}
			}
			return S_OK;
			
		}
		return E_FAIL;
		break;
	case OPC_BROWSE_DOWN:
		//szString - куда?
		if (str=="") return E_FAIL;
		if (m_CurPos.m_ChannelID.get_m_hObjectHandle()==0)
		{
			//проходим по карте каналов
			for(itm=m_pMyTestConf->m_ChannelMap.begin();itm!=m_pMyTestConf->m_ChannelMap.end();++itm)
			{
				if (itm->second->get_m_sObjectName()==str)
				{
					m_CurPos.m_ChannelID.set_m_hObjectHandle(itm->second->get_m_hObjectHandle());
					m_CurPos.m_pCarrentChannel = itm->second;
					IUnknown *pU;
					HRESULT hhh=itm->second->GetBrowser(&pU);
					if (SUCCEEDED(hhh))
					{
						hhh=pU->QueryInterface(IID_ISpaceBrowse,(void**)&m_CurPos.pSpaceBrowse);
						if (SUCCEEDED(hhh))
							m_CurPos.CurrentLevel++;
						pU->Release();
					}
						
					return hhh;
				}
			}
		}
		else if (m_CurPos.pSpaceBrowse)
		{
			HRESULT hr=S_OK;
			hr=m_CurPos.pSpaceBrowse->ChangeBrowsePosition(dwBrowseDirection,szString);
			if (SUCCEEDED(hr))
				m_CurPos.CurrentLevel++;
			return hr;
		}
		return E_FAIL;
		break;
	case OPC_BROWSE_TO:
		//szString - full item name
		if (str=="")
		{
			m_CurPos.m_CurrentPositionName="";
			m_CurPos.m_ChannelID.set_m_hObjectHandle(0);
			m_CurPos.m_pCarrentChannel = NULL;
			if (m_CurPos.pSpaceBrowse) m_CurPos.pSpaceBrowse->Release();
			m_CurPos.pSpaceBrowse=NULL;
			m_CurPos.CurrentLevel=0;//root
			return S_OK;
		}
		//найдем количество разделителей - точек в адресе перпеременной.
		long DotCount;
		DotCount=std::count(str.begin(),str.end(),'.');
		DotCount+=1;
		if (m_CurPos.m_pCarrentChannel)
			if ((pos=str.find(m_CurPos.m_pCarrentChannel->get_m_sObjectName()))==0)
			{
				//ищем в текущем канале
				if (m_CurPos.pSpaceBrowse)
				{
					HRESULT hr=S_OK;
					hr=m_CurPos.pSpaceBrowse->ChangeBrowsePosition(dwBrowseDirection,szString);
					if (SUCCEEDED(hr))
						m_CurPos.CurrentLevel=DotCount;
					return hr;
				}
				return E_FAIL;
			}

		//поищем канал
		for(itm=m_pMyTestConf->m_ChannelMap.begin();itm!=m_pMyTestConf->m_ChannelMap.end();++itm)
		{
			if ((pos=str.find(itm->second->get_m_sObjectName()))==0)
			{
				m_CurPos.m_ChannelID.set_m_hObjectHandle(itm->second->get_m_hObjectHandle());
				m_CurPos.m_pCarrentChannel = itm->second;
				if (m_CurPos.pSpaceBrowse)
				{
					m_CurPos.pSpaceBrowse->Release();
					m_CurPos.pSpaceBrowse=NULL;
				}
				IUnknown *pU;
				itm->second->GetBrowser(&pU);
				pU->QueryInterface(IID_ISpaceBrowse,(void**)&m_CurPos.pSpaceBrowse);
				pU->Release();
				break;
			}
		}
		//теперь опять попробуем искать в канале
		if ((m_CurPos.m_ChannelID.get_m_hObjectHandle()!=0)&&(m_CurPos.pSpaceBrowse))
		{
			HRESULT hr=S_OK;
			hr=m_CurPos.pSpaceBrowse->ChangeBrowsePosition(dwBrowseDirection,szString);
			if (SUCCEEDED(hr))
				m_CurPos.CurrentLevel=DotCount;
			return hr;

		}
		return E_FAIL;

		break;
	default:
		return E_INVALIDARG;
	}


//	return S_OK;
}
STDMETHODIMP CMyOPCSrv::BrowseOPCItemIDs(OPCBROWSETYPE dwBrowseFilterType, LPCWSTR szFilterCriteria, USHORT vtDataTypeFilter, ULONG dwAccessRightsFilter, IEnumString * * ppIEnumString)
{
m_pMyTestConf->m_LogFile<<"Вызов BrowseOPCItemIDs\n";//);
	if (ppIEnumString == NULL)
		return E_POINTER;
	std::vector<LPOLESTR> strvec;
	_CHANNELMAP::iterator itm;
	LPOLESTR olestr=NULL;
	typedef CComObjectNoLock<CComEnum<IEnumString,&IID_IEnumString,LPOLESTR,_Copy<LPOLESTR> > > Enum;
	Enum * p = new Enum;
	HRESULT hr;
	USES_CONVERSION;
	IEnumString * pMyEnum;
	switch(dwBrowseFilterType)
	{
	case OPC_BRANCH:
		if (m_CurPos.m_ChannelID.get_m_hObjectHandle()==0) //если в самом верху
		{
			for (itm=m_pMyTestConf->m_ChannelMap.begin();itm!=m_pMyTestConf->m_ChannelMap.end();++itm)
			{
				long s;
				olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((s=itm->second->get_m_sObjectName().size()+1)));
				wcscpy(olestr,A2W(itm->second->get_m_sObjectName().c_str()));
				//добавить фильтр треба...
				strvec.insert(strvec.end(),olestr);
			}
			//формируем интерфейс
			if (p==NULL) hr= E_OUTOFMEMORY;
			else
			{
				hr=p->FinalConstruct();
				if (hr==S_OK)
				{
					LPOLESTR *mas = new LPOLESTR[strvec.size()];
					for (int i=0;i<strvec.size();i++)
					{
						mas[i]=strvec[i];
					}

					long fd;
					hr=p->Init(mas,mas+strvec.size(),NULL,AtlFlagCopy);
					if (hr==S_OK)
					{
						hr=p->QueryInterface(IID_IUnknown,(void**)ppIEnumString);
					}
					delete[] mas;
				}
			}
			if (hr!=S_OK)
				delete p;
			if ((strvec.size()==0)&&SUCCEEDED(hr)) hr=S_FALSE;
			return hr;
			
		}else
			return m_CurPos.pSpaceBrowse->BrowseOPCItemIDs(dwBrowseFilterType,szFilterCriteria,vtDataTypeFilter,dwAccessRightsFilter,ppIEnumString);

		break;
	case OPC_LEAF:
		if (m_CurPos.m_ChannelID.get_m_hObjectHandle()==0) //если в самом верху
		{
			//формируем интерфейс
			if (p==NULL) hr= E_OUTOFMEMORY;
			else
			{
				hr=p->FinalConstruct();
				if (hr==S_OK)
				{
					LPOLESTR *mas = new LPOLESTR[strvec.size()];
					for (int i=0;i<strvec.size();i++)
					{
						mas[i]=strvec[i];
					}
					hr=p->Init(mas,mas+strvec.size(),NULL,AtlFlagCopy);
					if (hr==S_OK)
					{
						hr=p->QueryInterface(IID_IUnknown,(void**)ppIEnumString);
					}
					delete[] mas;
				}
			}
			if (hr!=S_OK)
				delete p;
		}else
			return m_CurPos.pSpaceBrowse->BrowseOPCItemIDs(dwBrowseFilterType,szFilterCriteria,vtDataTypeFilter,dwAccessRightsFilter,ppIEnumString);
		break;
	case OPC_FLAT:
		//ну-у, началось самое ^#@&^$#&$E*!@%R&#^$%!!!!!!!!
		for (itm=m_pMyTestConf->m_ChannelMap.begin();itm!=m_pMyTestConf->m_ChannelMap.end();++itm)
		{
//
			IUnknown *pU;
			hr=itm->second->GetBrowser(&pU);
			if (SUCCEEDED(hr))
			{
				hr=pU->QueryInterface(IID_ISpaceBrowse,(void**)&m_CurPos.pSpaceBrowse);
				pU->Release();
			}

			//hr=itm->second->QueryInterface(IID_ISpaceBrowse,(void**)&m_CurPos.pSpaceBrowse);
			if (SUCCEEDED(hr))
			{
				//получение ItemIDs
				if (SUCCEEDED(m_CurPos.pSpaceBrowse->BrowseOPCItemIDs(dwBrowseFilterType,szFilterCriteria,vtDataTypeFilter,dwAccessRightsFilter,&pMyEnum)))
				{
					if(pMyEnum)
					{
						pMyEnum->Reset();
						ULONG pCelt=0;
						LPOLESTR mystr[10000];
						if (SUCCEEDED(pMyEnum->Next(10000,mystr,&pCelt)))
						{
							if (pCelt)
								strvec.insert(strvec.end(),&mystr[0],&mystr[pCelt]);
						}
					}
					pMyEnum->Release();
					pMyEnum=NULL;
				}
				m_CurPos.pSpaceBrowse->Release();
			}
			m_CurPos.pSpaceBrowse=NULL;
		}

		if (p==NULL) hr= E_OUTOFMEMORY;
		else
		{
			hr=p->FinalConstruct();
			if (hr==S_OK)
			{
				LPOLESTR *mas = new LPOLESTR[strvec.size()];
				for (int i=0;i<strvec.size();i++)
				{
					mas[i]=strvec[i];
				}
				hr=p->Init(mas,mas+strvec.size(),NULL,AtlFlagCopy);
				if (hr==S_OK)
				{
					hr=p->QueryInterface(IID_IUnknown,(void**)ppIEnumString);
				}
				delete[] mas;
			}
		}
		if (hr!=S_OK)
			delete p;


		return hr;
		break;
	default:
		return E_NOTIMPL;
	}
	return S_OK;
}
STDMETHODIMP CMyOPCSrv::GetItemID(LPWSTR szItemDataID, LPWSTR * szItemID)
{
	m_pMyTestConf->m_LogFile<<"Вызов GetItemID\n";//);
	if (szItemID == NULL)
		return E_POINTER;
	if (m_CurPos.m_ChannelID.get_m_hObjectHandle()==0)
	{
		*szItemID=(LPWSTR)CoTaskMemAlloc(sizeof(wchar_t)*(wcslen(szItemDataID)+1));
		wcscpy(*szItemID,szItemDataID);
		return S_OK;
	}
	else
		if (m_CurPos.pSpaceBrowse)
		{
			return m_CurPos.pSpaceBrowse->GetItemID(szItemDataID,szItemID);
		}

	return S_OK;
}
STDMETHODIMP CMyOPCSrv::BrowseAccessPaths(LPCWSTR szItemID, IEnumString * * ppIEnumString)
{
m_pMyTestConf->m_LogFile<<"Вызов BrowseAccessPaths\n";//);
	if (ppIEnumString == NULL)
		return E_POINTER;
	*ppIEnumString=NULL;
		
	return E_NOTIMPL;
}
// IOPCServer
// IOPCServer
STDMETHODIMP CMyOPCSrv::AddGroup(LPCWSTR szName, BOOL bActive, ULONG dwRequestedUpdateRate, OPCHANDLE hClientGroup, LONG * pTimeBias, FLOAT * pPercentDeadband, ULONG dwLCID, OPCHANDLE * phServerGroup, ULONG * pRevisedUpdateRate, REFIID riid, IUnknown * * ppUnk)
{
		//CLogFile_CS GGG;
		//GGG.SetNewFullLogName("c:\\PETRENKO222.log");
		//GGG<<"TEST Добавление группы!";

//m_pMyTestConf->m_LogFile<<"Вызов AddGroup\n";//);
	if (phServerGroup == NULL)
		return E_POINTER;

	if (pRevisedUpdateRate == NULL)
		return E_POINTER;
		
	if (ppUnk == NULL)
		return E_POINTER;

	if (m_pMyTestConf->IsSuspended())
	{
	//установим возвращаемые значения в NULL
		*ppUnk=NULL;
		return OPC_E_SUSPENDED;
	}
		//GGG.SetNewFullLogName("c:\\PETRENKO222.log");
		//GGG<<"TEST Добавление группы!";
		

	HRESULT hr=S_OK;
	USES_CONVERSION;
	CComObjectNoLock<CMyGroup> * pGroup = new CComObjectNoLock<CMyGroup>;
	if (!pGroup) return E_OUTOFMEMORY;
	pGroup->FinalConstruct();
	pGroup->AddRef();
	m_Groups.insert(m_Groups.begin(),pGroup);

	pGroup->m_bActive = bActive;
	
	pGroup->set_m_sObjectName(W2A(szName));
	m_pMyTestConf->m_LogFile<<dwRequestedUpdateRate;
	m_pMyTestConf->m_LogFile<<W2A(szName);
	if (dwRequestedUpdateRate<150) dwRequestedUpdateRate=150;
	pGroup->m_UpdateRate=dwRequestedUpdateRate;
	pGroup->m_dwLCID=dwLCID;
	if (pTimeBias) pGroup->m_TimeBias= *pTimeBias;
	if (pPercentDeadband) pGroup->m_PercentDeadband = *pPercentDeadband;
	pGroup->GenerateNewID(NULL);
	*phServerGroup=pGroup->get_m_hObjectHandle();
	*pRevisedUpdateRate=pGroup->m_UpdateRate;
	pGroup->m_ControlThread.m_Owner=pGroup;

	pGroup->m_pOPCSrv=this;
	pGroup->m_hClientGroup = hClientGroup;
	//подписаться на нотификации от каналов
	
	pGroup->m_ControlThread.run();
//	RemoveGroup(pGroup->get_m_hObjectHandle(),0);
	return pGroup->QueryInterface(riid,(void**)ppUnk);
}
STDMETHODIMP CMyOPCSrv::GetErrorString(HRESULT dwError, ULONG dwLocale, LPWSTR * ppString)
{
m_pMyTestConf->m_LogFile<<"Вызов GetErrorString\n";//); 
	if (ppString == NULL)
		return E_POINTER;
	return E_NOTIMPL;
}
STDMETHODIMP CMyOPCSrv::GetGroupByName(LPCWSTR szName, REFIID riid, IUnknown * * ppUnk)
{
m_pMyTestConf->m_LogFile<<"Вызов GetGroupByName\n";//);
	if (ppUnk == NULL)
		return E_POINTER;
	HRESULT hr=S_OK;
	USES_CONVERSION;
	std::vector<CMyGroup*>::iterator itv;	
	for (itv=m_Groups.begin();itv!=m_Groups.end();++itv)
	{
		if((*itv)->get_m_sObjectName()==W2A(szName))
		{
			return (*itv)->QueryInterface(riid,(void**)ppUnk);
		}
	}
	return E_FAIL;
}
STDMETHODIMP CMyOPCSrv::GetStatus(OPCSERVERSTATUS * * ppServerStatus)
{
m_pMyTestConf->m_LogFile<<"Вызов GetStatus\n";//);
	OPCSERVERSTATUS *pOPCSS;
	if (ppServerStatus == NULL)
	return E_POINTER;
	wchar_t * mystr=static_cast<wchar_t*>(CoTaskMemAlloc(sizeof(wchar_t)*(strlen("ZSMK,CAPCS,EVS")+1)));
	USES_CONVERSION;
	wcscpy(mystr,A2W("ZSMK,CAPCS,EVS")); 
	pOPCSS=(OPCSERVERSTATUS*)CoTaskMemAlloc(sizeof(OPCSERVERSTATUS));
	pOPCSS->szVendorInfo = mystr;
	pOPCSS->dwServerState = m_pMyTestConf->m_OPCServerState;//OPC_STATUS_RUNNING;
	pOPCSS->dwBandWidth = 0;
	pOPCSS->dwGroupCount =m_Groups.size();
	CoFileTimeNow(&(pOPCSS->ftCurrentTime));
	CoFileTimeNow(&(pOPCSS->ftLastUpdateTime));
	CoFileTimeNow(&(pOPCSS->ftStartTime));

	*ppServerStatus=pOPCSS;

	return S_OK;
}


STDMETHODIMP CMyOPCSrv::RemoveGroup(ULONG hServerGroup, BOOL bForce)
{
m_pMyTestConf->m_LogFile<<"Вызов RemoveGroup\n";//);
	std::vector<CMyGroup*>::iterator it;

	for(it=m_Groups.begin();it!=m_Groups.end();++it)
	{
		if ((*it)->get_m_hObjectHandle()==hServerGroup) 
		{
			(*it)->m_ControlThread.Stop();
			(*it)->Release();
			//(*it)->FinalRelease();
		//	delete (CMyGroup*)*it;
			
			m_Groups.erase(it);

			break;
		}
	}
	return S_OK;
}
STDMETHODIMP CMyOPCSrv::CreateGroupEnumerator(OPCENUMSCOPE dwScope, REFIID riid, IUnknown * * ppUnk)
{
m_pMyTestConf->m_LogFile<<"Вызов CreateGroupEnumerator\n";//);
	if (ppUnk == NULL)
		return E_POINTER;
		HRESULT hr;
	if (IsEqualIID(IID_IEnumString,riid))
	{
		typedef CComObjectNoLock<CComEnumOnSTL<IEnumString,&IID_IEnumString,LPOLESTR,_CopyXSTR<CMyGroup*,LPOLESTR>, std::vector<CMyGroup*> > > Enum;
		Enum * p = new Enum;
		if (p==NULL) hr= E_OUTOFMEMORY;
		else
		{
			hr=p->FinalConstruct();
			if (hr==S_OK)
			{
				hr=p->Init(NULL,m_Groups);
				if (hr==S_OK)
				{
					hr=p->QueryInterface(IID_IUnknown,(void**)ppUnk);
				}
			}
		}
		if (hr!=S_OK)
			delete p;

	}else if (IsEqualIID(IID_IEnumUnknown,riid))
	{
		typedef CComObjectNoLock<CComEnumOnSTL<IEnumUnknown,&IID_IEnumUnknown,IUnknown*,_CopyXIU<CMyGroup*,IUnknown*>,std::vector<CMyGroup*> > > Enum;
		Enum * p = new Enum;

		if (p==NULL) hr= E_OUTOFMEMORY;
		else
		{
			hr=p->FinalConstruct();
			if (hr==S_OK)
			{	
				hr=p->Init(NULL,m_Groups);
				if (hr==S_OK)
				{
					hr=p->QueryInterface(IID_IUnknown,(void**)ppUnk);
				}
			}
		}
		if (hr!=S_OK)
			delete p;
	}
		
	return hr;
}
STDMETHODIMP CMyOPCSrv::QueryAvailableProperties(LPWSTR szItemID, ULONG * pdwCount, ULONG * * ppPropertyIDs, LPWSTR * * ppDescriptions, USHORT * * ppvtDataTypes)
{
m_pMyTestConf->m_LogFile<<"Вызов QueryAvailableProperties\n";//);
	if (pdwCount == NULL)
		return E_POINTER;
		
	if (ppPropertyIDs == NULL)
		return E_POINTER;
		
	if (ppDescriptions == NULL)
		return E_POINTER;
		
	if (ppvtDataTypes == NULL)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CMyOPCSrv::GetItemProperties(LPWSTR szItemID, ULONG dwCount, ULONG * pdwPropertyIDs, VARIANT * * ppvData, HRESULT * * ppErrors)
{
m_pMyTestConf->m_LogFile<<"Вызов GetItemProperties\n";//);
	if (ppvData == NULL)
		return E_POINTER;
		
	if (ppErrors == NULL)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CMyOPCSrv::LookupItemIDs(LPWSTR szItemID, ULONG dwCount, ULONG * pdwPropertyIDs, LPWSTR * * ppszNewItemIDs, HRESULT * * ppErrors)
{
m_pMyTestConf->m_LogFile<<"Вызов LookupItemIDs\n";//);
	if (ppszNewItemIDs == NULL)
		return E_POINTER;
		
	if (ppErrors == NULL)
		return E_POINTER;
		
	return E_NOTIMPL;
}
// IOPCServerPublicGroups
/*STDMETHODIMP CMyOPCSrv::GetPublicGroupByName(LPCWSTR szName, REFIID riid, IUnknown * * ppUnk)
{
	if (ppUnk == NULL)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CMyOPCSrv::RemovePublicGroup(ULONG hServerGroup, BOOL bForce)
{
	return E_NOTIMPL;
}
*/STDMETHODIMP CMyOPCSrv::SetLocaleID(ULONG dwLcid)
{
m_pMyTestConf->m_LogFile<<"Вызов SetLocaleID\n";//);
	m_LocaleID=dwLcid;
	return S_OK;
}
STDMETHODIMP CMyOPCSrv::GetLocaleID(ULONG * pdwLcid)
{
m_pMyTestConf->m_LogFile<<"Вызов GetLocaleID\n";//);
	if (pdwLcid == NULL)
	return E_POINTER;		
	*pdwLcid=m_LocaleID;
	return S_OK;
}
STDMETHODIMP CMyOPCSrv::QueryAvailableLocaleIDs(ULONG * pdwCount, ULONG * * pdwLcid)
{
m_pMyTestConf->m_LogFile<<"Вызов QueryAvailableLocaleIDs\n";//);
	if (pdwCount == NULL)
		return E_POINTER;
		
	if (pdwLcid == NULL)
		return E_POINTER;
	
	return E_NOTIMPL;
}
STDMETHODIMP CMyOPCSrv::GetErrorString(HRESULT dwError, LPWSTR * ppString)
{
m_pMyTestConf->m_LogFile<<"Вызов GetErrorString\n";//);
	if (ppString == NULL)
		return E_POINTER;
		
	return E_NOTIMPL;
}
STDMETHODIMP CMyOPCSrv::SetClientName(LPCWSTR szName)
{
m_pMyTestConf->m_LogFile<<"Вызов SetClientName\n";//);
	USES_CONVERSION;
	m_ClientName=W2A(szName);
	return S_OK;
}
/////////////////////////////////////////////////////////////////////////////
// CMyGroup
STDMETHODIMP CMyGroup::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IMyGroup
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
// IOPCAsyncIO
HRESULT CMyGroup::AsyncWriteInMass(ULONG dwConnection, ULONG dwCount, ULONG * phServer, VARIANT * pItemValues, ULONG * pTransactionID,DWORD dwTransactionID2,ULONG *pdwCancelID, HRESULT * * ppErrors)
{
	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
    //srand(1);
	_OPCGROUPTAGMAP::iterator itx;
	bool ErFlag=false;
	DWORD RealCount=0;
	OPCHANDLE * pMyhServer= new OPCHANDLE[dwCount];
	HRESULT GlobalHr=S_OK;
	
	for(UINT yi=0;yi<dwCount;yi++)
	{
		//_OPCTagID id;
		//id.set_m_hObjectHandle(*(phServer+yi));
		itx=m_Tags.find(*(phServer+yi));
		if (itx==m_Tags.end())
		{
			*(*ppErrors+yi)=OPC_E_INVALIDHANDLE;
			ErFlag=true;
		}
		else
		{
			if (!dwConnection)//проверка для второй версии
			{
				if (itx->second->m_dwAccessRights&OPC_WRITEABLE)
				{
					*(*ppErrors+yi)=S_OK;
					*(pMyhServer+RealCount)=*(phServer+yi);
					RealCount++;
				}
				else
				{
					*(*ppErrors+yi)=OPC_E_BADRIGHTS;
					ErFlag=true;
				}
			}
			else
			{
				*(*ppErrors+yi)=S_OK;
				*(pMyhServer+RealCount)=*(phServer+yi);
				RealCount++;
			}
		}

	}

	if (!dwConnection)	//проверка для второй версии
		if (ErFlag)
		{
			delete[] pMyhServer;
			return S_FALSE;
		}
	else
		if (RealCount==0)
			return E_FAIL;

	if (ErFlag)
		GlobalHr=S_FALSE;

	m_AsyncWriteCS.Lock();
	_CHANNELMAP::iterator itm;

	//Создаем новую транзакцию
	CTransactionWrapper * pTWrap=new CTransactionWrapper;
	//Генерируем идентификатор
	pTWrap->m_dwTransactionID=GenerateNewID(NULL);
	m_pMyTestConf->m_LogFile<<"Транзакция = %d";//,pTWrap->m_dwTransactionID);

	if(dwConnection==0) //значит используем для версии 2
	{
		*pdwCancelID=pTWrap->m_dwTransactionID;
		pTWrap->m_dwTransactionID2=dwTransactionID2;
	}
	else
	{
		*pTransactionID = pTWrap->m_dwTransactionID;
	}
	//Заносим ее в вектор активных транзакций
	m_TransactionAccessCS.Lock();
	m_TransactionVector.insert(m_TransactionVector.end(),pTWrap);
	m_TransactionAccessCS.Unlock();	
	//наплевать на источник данных
	//надо разобрать по каналам и разослать по ним же
		ULONG* pL=new ULONG[RealCount];
		memcpy(pL,pMyhServer,sizeof(ULONG)*RealCount);

		//Создаем контэйнер для интерпретации
		ULONG * pIhL=new ULONG[RealCount];
		ZeroMemory(pIhL,sizeof(ULONG)*RealCount);

		std::sort(pL,pL+RealCount);
		delete[] pMyhServer;

		//заполним интерпретации
		INTERPRET2SERVERMap::iterator ii2s;
		for(UINT hi=0;hi<RealCount;hi++)
		{
			ii2s=m_InterpretHandleMap.find(*(pL+hi));//ищем интерпретер
			if (ii2s!=m_InterpretHandleMap.end())//если есть
			{
				*(pIhL+hi)=*(pL+hi);//устанавливаем интерпретатор
				*(pL+hi)=ii2s->second;//заменяем на реальный
			}
		}

	
		DWORD *pFirst=pL,Count=1;
		UINT i=1;
		bool Flag;
		
		do
		{
			if (i>RealCount) break;
			if (i==RealCount) 
			{
				Flag=true;
				//Count++;
			}
			else
			{
				if (!(Flag=(GetChannelID(*(pL+i))!=GetChannelID(*pFirst))))
				//	Count++;
				Flag=false;
			}

			if (Flag)
			{
				_ChannelID ch;
				ch.set_m_hObjectHandle(GetChannelID(*pFirst));
				itm=m_pMyTestConf->m_ChannelMap.find(ch);
				if (itm==m_pMyTestConf->m_ChannelMap.end())
				{
					;
					//забиваем ошибками все это;
				}
				else
				{
					//Создаем структуру для передачи
					_AsyncIORWMsg * pmes = new _AsyncIORWMsg;
					pmes->m_dwConnection = dwConnection;
					pmes->m_dwNumItems = Count;
					pTWrap->m_GlobalTagCount+=Count;
				//	pmes->m_dwSource=dwSource;
					pmes->m_pItemValues = (VARIANT*)CoTaskMemAlloc(sizeof(VARIANT)*Count);
					for(UINT iv=0;iv<Count;iv++)
					{
						VariantInit(pmes->m_pItemValues+iv);
						VariantCopy(pmes->m_pItemValues+iv,pItemValues+(pFirst-pL));
					}
					
					pmes->m_phServerHandle = new OPCHANDLE[Count] ;
					memcpy(pmes->m_phServerHandle,pFirst,sizeof(OPCHANDLE)*Count);
					pmes->m_phInterpretHandle=new OPCHANDLE[Count];
					memcpy(pmes->m_phInterpretHandle,pIhL+(pFirst-pL),sizeof(OPCHANDLE)*Count);
					pmes->set_m_TransactionID(pTWrap->m_dwTransactionID);//сменить
					pmes->m_DestThreadID = m_ControlThread.get_m_ThreadID();
					pmes->m_Message=AsyncWrite;
			
					//Добавили сообщение в транзакцию
					pTWrap->m_MessageVector.insert(pTWrap->m_MessageVector.end(),pmes);
					//отослали
					itm->second->AsWrite(pmes);
				}
				
				Count=0;
				pFirst=pL+i;
			}
	
			i++;
			Count++;
		}while(true);

		pTWrap->ConfigComplite();
		m_AsyncWriteCS.Unlock();
		_AsyncIORWMsg * pCC = new _AsyncIORWMsg;
		pCC->set_m_TransactionID(pTWrap->m_dwTransactionID);
		::PostThreadMessage(m_ControlThread.get_m_ThreadID(),WM_CONTROLTHREAD_TRANSACTION_CONFIG_COMPLITE_WRITE,0,(long)pCC);

//		*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
//		for (int y=0;y<dwCount;y++)
//			*((*ppErrors)+y)=S_OK;

		delete[] pL;	
		delete[] pIhL;
m_pMyTestConf->m_LogFile<<"Ушли WriteAsync\n";//);
		return GlobalHr;


}
HRESULT CMyGroup::AsyncReadInMass(ULONG dwConnection, OPCDATASOURCE dwSource, ULONG dwCount, ULONG * phServer, ULONG * pTransactionID,DWORD dwTransactionID2,ULONG *pdwCancelID2, HRESULT * * ppErrors)
{
//		if (m_Owner->m_pOPCSrv->m_pMyTestConf->m_OPCServerState==OPC_STATUS_SUSPENDED)	
			//перенаправляем запрос в кэш, а там уже и требуемое качество проставим
//			dwSource=OPC_DS_CACHE;

		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
			dwSource=OPC_DS_CACHE;
		
		if (pTransactionID == NULL)
			return E_POINTER;
			
		if (ppErrors == NULL)
			return E_POINTER;
		ATLTRACE ("dwConnection %d, dwSource %d,dwCount %d\n",dwConnection,dwSource,dwCount);
		if (dwSource==OPC_DS_CACHE)
			return CacheASyncRead(dwConnection,dwSource,dwCount,phServer,pTransactionID,ppErrors);


	HRESULT GlobalHr=S_OK;
	//Проверим если есть INVALIDHANDLE - выходим с ошибкой
	_OPCGROUPTAGMAP::iterator itx;
	bool ErFlag=false;
	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);


	DWORD RealCount=0;
	OPCHANDLE * pMyhServer= new OPCHANDLE[dwCount];

	for(UINT yi=0;yi<dwCount;yi++)
	{
		//_OPCTagID id;
		//id.set_m_hObjectHandle(*(phServer+yi));
		itx=m_Tags.find(*(phServer+yi));
		if (itx==m_Tags.end())
		{
			*(*ppErrors+yi)=OPC_E_INVALIDHANDLE;
			ErFlag=true;
		}
		else
		{
			if (!dwConnection)//проверка для второй версии
			{
				if (itx->second->m_dwAccessRights&OPC_READABLE)
				{
					*(*ppErrors+yi)=S_OK;
					*(pMyhServer+RealCount)=*(phServer+yi);
					RealCount++;
				}
				else
				{
					*(*ppErrors+yi)=OPC_E_BADRIGHTS;
					ErFlag=true;
				}
			}
			else
			{
				*(pMyhServer+RealCount)=*(phServer+yi);
				RealCount++;
				*(*ppErrors+yi)=S_OK;
			}
		}

	}

	if (!dwConnection)	//проверка для второй версии
		if (ErFlag)
		{
			delete[] pMyhServer;
		//	m_AsyncReadCS.Unlock();
			return S_FALSE;
		}
	else
		if (RealCount==0)
		{
	//	m_AsyncReadCS.Unlock();
			return E_FAIL;
		}
	if (ErFlag)
		GlobalHr=S_FALSE;

    m_AsyncReadCS.Lock();
	_CHANNELMAP::iterator itm;

	//Создаем новую транзакцию
	CTransactionWrapper * pTWrap=new CTransactionWrapper;
	//Генерируем идентификатор
	pTWrap->m_dwTransactionID=GenerateNewID(NULL);
	if(dwConnection==0) //значит используем для версии 2
	{
		*pdwCancelID2=pTWrap->m_dwTransactionID;
		pTWrap->m_dwTransactionID2=dwTransactionID2;
	}
	else
	{
		*pTransactionID = pTWrap->m_dwTransactionID;
	}

	//Заносим ее в вектор активных транзакций
	m_TransactionAccessCS.Lock();
	m_TransactionVector.insert(m_TransactionVector.end(),pTWrap);
	m_TransactionAccessCS.Unlock();	
	//наплевать на источник данных
	//надо разобрать по каналам и разослать по ним же
			
		
		

		ULONG* pL=new ULONG[RealCount];
		memcpy(pL,pMyhServer,sizeof(ULONG)*RealCount);

		//Создаем контэйнер для интерпретации
		ULONG * pIhL=new ULONG[RealCount];
		ZeroMemory(pIhL,sizeof(ULONG)*RealCount);

		std::sort(pL,pL+RealCount);
		delete[] pMyhServer;

		//заполним интерпретации
		INTERPRET2SERVERMap::iterator ii2s;
		for(UINT hi=0;hi<RealCount;hi++)
		{
			ii2s=m_InterpretHandleMap.find(*(pL+hi));//ищем интерпретер
			if (ii2s!=m_InterpretHandleMap.end())//если есть
			{
				*(pIhL+hi)=*(pL+hi);//устанавливаем интерпретатор
				*(pL+hi)=ii2s->second;//заменяем на реальный
			}
		}

		DWORD *pFirst=pL,Count=1;
		UINT i=1;
		bool Flag;
		
		do
		{
			if (i>RealCount) break;
			if (i==RealCount) 
			{
				Flag=true;
				//Count++;
			}
			else
			{ 
				if (!(Flag=(GetChannelID(*(pL+i))!=GetChannelID(*pFirst))))
				//	Count++;
				Flag=false;
			}

			if (Flag)
			{
				_ChannelID ch;
				ch.set_m_hObjectHandle(GetChannelID(*pFirst));
				itm=m_pMyTestConf->m_ChannelMap.find(ch);
				if (itm==m_pMyTestConf->m_ChannelMap.end())
				{
					
				
				}
				else
				{
					//Создаем структуру для передачи
					_AsyncIORWMsg * pmes = new _AsyncIORWMsg;
					pmes->m_dwConnection = dwConnection;
					pmes->m_dwNumItems = Count;
					pTWrap->m_GlobalTagCount+=Count;
					pmes->m_dwSource=dwSource;
					pmes->m_phServerHandle = new OPCHANDLE[Count] ;
					memcpy(pmes->m_phServerHandle,pFirst,sizeof(OPCHANDLE)*Count);
					pmes->m_phInterpretHandle=new OPCHANDLE[Count];
					memcpy(pmes->m_phInterpretHandle,pIhL+(pFirst-pL),sizeof(OPCHANDLE)*Count);
					pmes->set_m_TransactionID(pTWrap->m_dwTransactionID);//сменить
					pmes->m_DestThreadID = m_ControlThread.get_m_ThreadID();
					pmes->m_Message=AsyncRead;
			
					//Добавили сообщение в транзакцию
					pTWrap->m_MessageVector.insert(pTWrap->m_MessageVector.end(),pmes);
					m_pMyTestConf->m_LogFile<<"Добавлена транзакция %d \n";//,pTWrap->m_dwTransactionID);
					//отослали
						itm->second->AsRead(pmes);
				}
				
				Count=0;
				pFirst=pL+i;
			}
	
			i++;
			Count++;
		}while(true);

		pTWrap->ConfigComplite();
		m_AsyncReadCS.Unlock();
		_AsyncIORWMsg * pCC = new _AsyncIORWMsg;
		pCC->set_m_TransactionID(pTWrap->m_dwTransactionID);
		::PostThreadMessage(m_ControlThread.get_m_ThreadID(),WM_CONTROLTHREAD_TRANSACTION_CONFIG_COMPLITE_READ,0,(long)pCC);
		delete[] pL;
		delete[] pIhL;
m_pMyTestConf->m_LogFile<<"Ушли ReadAsync\n";//);
		return GlobalHr;
}

STDMETHODIMP CMyGroup::Read(ULONG dwConnection, OPCDATASOURCE dwSource, ULONG dwCount, ULONG * phServer, ULONG * pTransactionID, HRESULT * * ppErrors)
	{
m_pMyTestConf->m_LogFile<<"Вызов ReadAsync\n";//);
		//Вставим проверку на callback
	    //переинициаоизация генератора
//		srand(1);
		std::list<CEvsAdvise*>::iterator conit;
		bool IsCon=false;

		for(conit=AdviseMap.begin();conit!=AdviseMap.end();++conit)
		{
			if ((*conit)->dwConnection==dwConnection)
			{
				IsCon=true;
				break;
			}
		}

		if (!IsCon) 
		{
			*ppErrors=NULL;
			return CONNECT_E_NOCONNECTION;
		}

//		DWORD x;
	return AsyncReadInMass(dwConnection,dwSource,dwCount,phServer,pTransactionID,0,NULL,ppErrors);
}

STDMETHODIMP CMyGroup::Write(ULONG dwConnection, ULONG dwCount, ULONG * phServer, VARIANT * pItemValues, ULONG * pTransactionID, HRESULT * * ppErrors)
{
m_pMyTestConf->m_LogFile<<"Вызов AsyncWrite\n";//);
		if (pTransactionID == NULL)
			return E_POINTER;
		if (ppErrors == NULL)
			return E_POINTER;


		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
		{
			//установим возвращаемые значения в NULL
			*pTransactionID=0;
			*ppErrors=NULL;
			return OPC_E_SUSPENDED;
		}

		//Вставим проверку на callback

		std::list<CEvsAdvise*>::iterator conit;
		bool IsCon=false;

		for(conit=AdviseMap.begin();conit!=AdviseMap.end();++conit)
		{
			if ((*conit)->dwConnection==dwConnection)
			{
				IsCon=true;
				break;
			}
		}

		if (!IsCon) 
		{
			*ppErrors=NULL;
			return CONNECT_E_NOCONNECTION;
		}



return AsyncWriteInMass(dwConnection,dwCount,phServer,pItemValues,pTransactionID,0,NULL,ppErrors);



}
STDMETHODIMP CMyGroup::Refresh(ULONG dwConnection, OPCDATASOURCE dwSource, ULONG * pTransactionID)
{
m_pMyTestConf->m_LogFile<<"Вызов Refresh\n";//);
		if (pTransactionID == NULL)
			return E_POINTER;
		//Вставим проверку на callback
		std::list<CEvsAdvise*>::iterator conit;
		bool IsCon=false;

		for(conit=AdviseMap.begin();conit!=AdviseMap.end();++conit)
		{
			if ((*conit)->dwConnection==dwConnection)
			{
				IsCon=true;
				break;
			}
		}

		if (!IsCon) 
		{
			return CONNECT_E_NOCONNECTION;
		}
		
return CacheRefresh(dwConnection,dwSource,0,pTransactionID);
}
STDMETHODIMP CMyGroup::Cancel(ULONG dwTransactionID)
{
		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
		{
			return OPC_E_SUSPENDED;
		}
	m_pMyTestConf->m_LogFile<<"Вызов Cancel\n";//);
	HRESULT hr=S_OK;
	m_TransactionAccessCS.Lock();
		//есть такая транзакция?
	std::vector<CTransactionWrapper*>::iterator itv;
	bool flag=false;//нет
	for(itv=m_TransactionVector.begin();itv!=m_TransactionVector.end();++itv)
	{	
		if ((*itv)->m_dwTransactionID==dwTransactionID)
		{
			flag=true;//есть
			break;
		}

	}
	if (flag)
	{
		if (!(*itv)->IsTransactionComplite()) //если не закончена
		{
			(*itv)->CancelTransaction();
		}
		else
		{
			hr=E_FAIL;
		}
	}
	else
	{
		hr=E_FAIL;
	}
	m_TransactionAccessCS.Unlock();
		return hr;
}
// IOPCAsyncIO2
STDMETHODIMP CMyGroup::Read(ULONG dwCount, ULONG * phServer, ULONG dwTransactionID, ULONG * pdwCancelID, HRESULT * * ppErrors)
	{
m_pMyTestConf->m_LogFile<<"Вызов ReadAsync2\n";//);
		if (pdwCancelID == NULL)
			return E_POINTER;
			
		if (ppErrors == NULL)
			return E_POINTER;
			
	    //переинициаоизация генератора
//		srand(1);
		HRESULT hr=S_OK;
		
		//Проверка на callback для v2
		if (!m_vec.GetSize())
		{
			*ppErrors=NULL;
			return CONNECT_E_NOCONNECTION;
		}
		
	//	return Read(0,OPC_DS_DEVICE,dwCount,phServer,pTransactionID,ppErrors);

DWORD x;
	return AsyncReadInMass(0,OPC_DS_DEVICE,dwCount,phServer,&x,dwTransactionID,pdwCancelID,ppErrors);
	}

STDMETHODIMP CMyGroup::Write(ULONG dwCount, ULONG * phServer, VARIANT * pItemValues, ULONG dwTransactionID, ULONG * pdwCancelID, HRESULT * * ppErrors)
	{
m_pMyTestConf->m_LogFile<<"Вызов AsyncWrite\n";//);
		if (pdwCancelID == NULL)
			return E_POINTER;
			
		if (ppErrors == NULL)
			return E_POINTER;

		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
		{
			//установим возвращаемые значения в NULL
			pdwCancelID=0;
			*ppErrors=NULL;
			return OPC_E_SUSPENDED;
		}

		HRESULT hr=S_OK;
		
		//Проверка на callback для v2
		if (!m_vec.GetSize())		{
			*ppErrors=NULL;
			return CONNECT_E_NOCONNECTION;
		}
DWORD x;
		return AsyncWriteInMass(0,dwCount,phServer,pItemValues,&x,dwTransactionID,pdwCancelID,ppErrors);
	}
STDMETHODIMP CMyGroup::Refresh2(OPCDATASOURCE dwSource, ULONG dwTransactionID, ULONG * pdwCancelID)
	{
m_pMyTestConf->m_LogFile<<"Вызов Refresh2\n";//);
		if (pdwCancelID == NULL)
			return E_POINTER;

		HRESULT hr=S_OK;
		
		//Проверка на callback для v2
		if (!m_vec.GetSize())
		{
			return CONNECT_E_NOCONNECTION;
		}

		return CacheRefresh(0,dwSource,dwTransactionID,pdwCancelID);
	}
STDMETHODIMP CMyGroup::Cancel2(ULONG dwCancelID)
	{
m_pMyTestConf->m_LogFile<<"Вызов Cancel2\n";//);
		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
		{
			return OPC_E_SUSPENDED;
		}

		HRESULT hr=S_OK;
	m_TransactionAccessCS.Lock();
		//есть такая транзакция?
	std::vector<CTransactionWrapper*>::iterator itv;
	bool flag=false;//нет
	for(itv=m_TransactionVector.begin();itv!=m_TransactionVector.end();++itv)
	{	
		if ((*itv)->m_dwTransactionID==dwCancelID)
		{
			flag=true;//есть
			break;
		}

	}
	if (flag)
	{
		if (!(*itv)->IsTransactionComplite()) //если не закончена
		{
			(*itv)->CancelTransaction();
		}
		else
		{
			hr=E_FAIL;
		}
	}
	else
	{
		hr=E_FAIL;
	}
	m_TransactionAccessCS.Unlock();		
		return hr;
	}
STDMETHODIMP CMyGroup::SetEnable(BOOL bEnable)
	{
m_pMyTestConf->m_LogFile<<"Вызов SetEnable\n";//);
		m_Enabled=(bool)bEnable;
		return S_OK;
	}
STDMETHODIMP CMyGroup::GetEnable(BOOL * pbEnable)
	{
m_pMyTestConf->m_LogFile<<"Вызов GetEnable\n";//);
		if (pbEnable == NULL)
			return E_POINTER;
		*pbEnable=(BOOL)m_Enabled;
		return S_OK;
	}
// IOPCGroupStateMgt
STDMETHODIMP CMyGroup::GetState(ULONG * pUpdateRate, BOOL * pActive, LPWSTR * ppName, LONG * pTimeBias, FLOAT * pPercentDeadband, ULONG * pLCID, ULONG * phClientGroup, ULONG * phServerGroup)
	{
m_pMyTestConf->m_LogFile<<"Вызов GetState\n";//);
		if (pUpdateRate == NULL)
			return E_POINTER;
			
		if (pActive == NULL)
			return E_POINTER;
			
		if (ppName == NULL)
			return E_POINTER;
			
		if (pTimeBias == NULL)
			return E_POINTER;
			
		if (pPercentDeadband == NULL)
			return E_POINTER;
			
		if (pLCID == NULL)
			return E_POINTER;
			
		if (phClientGroup == NULL)
			return E_POINTER;
			
		if (phServerGroup == NULL)
			return E_POINTER;
	*pUpdateRate = m_UpdateRate;
	*pActive=m_bActive;
	wchar_t * mystr=static_cast<wchar_t*>(CoTaskMemAlloc(sizeof(wchar_t)*(get_m_sObjectName().length()+1)));
	USES_CONVERSION;
	wcscpy(mystr,A2W(get_m_sObjectName().c_str())); 
	*ppName=mystr;
	*pTimeBias	=m_TimeBias;
	*pPercentDeadband=m_PercentDeadband;
	*pLCID=m_dwLCID;
	*phClientGroup=m_hClientGroup;
	*phServerGroup=get_m_hObjectHandle();

		return S_OK;
	}
STDMETHODIMP CMyGroup::SetState(ULONG * pRequestedUpdateRate, ULONG * pRevisedUpdateRate, BOOL * pActive, LONG * pTimeBias, FLOAT * pPercentDeadband, ULONG * pLCID, ULONG * phClientGroup)
	{
m_pMyTestConf->m_LogFile<<"Вызов SetState\n";//);
		if (pRevisedUpdateRate == NULL)
			return E_POINTER;
	HRESULT hRes=S_OK;
	bool Changed=false,Changed2=false;	
		if (pTimeBias)
			m_TimeBias=*pTimeBias;
		
		if (pPercentDeadband)
			m_PercentDeadband=*pPercentDeadband;

		if (pLCID)
			m_dwLCID=*pLCID;

		if (phClientGroup)
			m_hClientGroup=*phClientGroup;


		if (pRequestedUpdateRate)//если хотят изменить его
		{
			if(*pRequestedUpdateRate<50) //меньше - нельзя
			{
				m_UpdateRate=50;
				*pRevisedUpdateRate=50;
				hRes=OPC_S_UNSUPPORTEDRATE;
			}
			else
			{
				m_UpdateRate=*pRequestedUpdateRate;
				*pRevisedUpdateRate=m_UpdateRate;
			}
			Changed=true;
		}			
		
		if (pActive)
			if (*pActive!=m_bActive)
			{
				m_bActive=*pActive;
				Changed2=true;
			}
// TODO: Проверить, что должно быть по активации тега
		PostThreadMessage(m_ControlThread.get_m_ThreadID(),WM_GROUP_SET_NEW_STATE,0,0);
		return hRes;
	}

STDMETHODIMP CMyGroup::SetName(LPCWSTR szName)
	{
m_pMyTestConf->m_LogFile<<"Вызов SetName\n";//);
		USES_CONVERSION;
// TODO: Сделать проверку по существованию имени в группах OPC сервера
		set_m_sObjectName(W2A(szName));
		return S_OK;
	}
STDMETHODIMP CMyGroup::CloneGroup(LPCWSTR szName, REFIID  riid, IUnknown * * ppUnk)
	{
m_pMyTestConf->m_LogFile<<"Вызов CloneGroup\n";//);
		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
		{
			*ppUnk=NULL;
			return OPC_E_SUSPENDED;
		}

		if (ppUnk == NULL)
			return E_POINTER;
			
		HRESULT GlobalHr=E_NOTIMPL;
		
		OPCHANDLE MyhServerGroup;
//		DWORD UpRate;
				
		GlobalHr=m_pOPCSrv->AddGroup(szName,FALSE,this->m_UpdateRate,m_hClientGroup,&m_TimeBias,&m_PercentDeadband,m_dwLCID,&MyhServerGroup,&m_UpdateRate,riid,ppUnk);
		//Добавим итемы и установим все ОК
		_OPCGROUPTAGMAP::iterator itm;
		std::vector<CMyGroup*>::iterator itv;
		CMyGroup * pGroup;
		if (SUCCEEDED(GlobalHr))
		{//добавление итемов	
			for(itv=m_pOPCSrv->m_Groups.begin();itv!=m_pOPCSrv->m_Groups.end();++itv)
				if ((*itv)->get_m_hObjectHandle()==MyhServerGroup)
				{//с нужной группой работаем
					pGroup=*itv;
					//по всем итемам текущей группы
					pGroup->m_InterpretHandleMap=m_InterpretHandleMap;
					for(itm=m_Tags.begin();itm!=m_Tags.end();++itm)
					{
						COPCTag * pTag = new COPCTag;
						pTag->set_m_hObjectHandle(itm->second->get_m_hObjectHandle());
						pTag->set_m_sObjectName(itm->second->get_m_sObjectName());
						pTag->set_ClientHandle(itm->second->get_ClientHandle());
						pTag->vtRequestedType = itm->second->vtRequestedType;
						pTag->m_vtCanonicalDataType=itm->second->m_vtCanonicalDataType;
/*xxxCHxxx*/			pTag->set_m_TagRef(itm->second->get_m_TagRef());
						pTag->m_OPCActive =itm->second->m_OPCActive;
						FILETIME ftx;
						GetSystemTimeAsFileTime(&ftx);
						pTag->set_m_ftLastUpdateTime(ftx);
						pTag->m_dwAccessRights = itm->second->m_dwAccessRights;
						pGroup->m_Tags.insert(_OPCGROUPTAGMAP::value_type(/*(_OPCTagID)(*pTag)*/pTag->get_m_hObjectHandle(),pTag));
					}
					break;
				}
		}
	
		return GlobalHr;
	}
// IOPCPublicGroupStateMgt
/*STDMETHODIMP CMyGroup::GetState(LONG * pPublic)
	{
		if (pPublic == NULL)
			return E_POINTER;
			
		return E_NOTIMPL;
	}
*//*STDMETHODIMP CMyGroup::MoveToPublic()
	{
		return E_NOTIMPL;
	}
*/// IOPCItemMgt
STDMETHODIMP CMyGroup::AddItems(ULONG dwCount, OPCITEMDEF * pItemArray, OPCITEMRESULT * * ppAddResults, HRESULT * * ppErrors)
	{
		m_pMyTestConf->m_LogFile<<"DEBUG: Enter AddItems!1";
//m_pMyTestConf->m_LogFile<<"Вызов AddItems dwCount=%d :\n";//,dwCount);
USES_CONVERSION;
//#ifdef _DEBUG
		m_pMyTestConf->m_LogFile<<this->m_UpdateRate;
		for (UINT t=0;t<dwCount;t++)
		{
			m_pMyTestConf->m_LogFile<<W2A((pItemArray+t)->szItemID);
		}
//#endif 
		
// TODO: Добавить при коннекте на нотификации v.1 первую передачу ADVF_PRIMEFIRST 
		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
		{
			*ppErrors=NULL;
			*ppAddResults=NULL;
			return OPC_E_SUSPENDED;
		}
			
		if (ppAddResults == NULL)
			return E_POINTER;
		if (ppErrors == NULL)
			return E_POINTER;
		if (pItemArray==NULL)
		{
			return E_POINTER;
		}
		if (dwCount==0)
		{
			return E_INVALIDARG;
		}

	//	USES_CONVERSION;
		std::map<_TagID,CTag*>::iterator itmt;
		_OPCGROUPTAGMAP::iterator itIS;
		_CHANNELMAP::iterator itmc;
		CTag*  *pT=new CTag*[dwCount];
		//m_pMyTestConf->m_LogFile<<"DEBUG: Enter AddItems! Before Validate items.";
		//сначала мы их валидейтем
		if (SUCCEEDED(ValidateItems(dwCount,pItemArray,FALSE,ppAddResults,ppErrors)))
		{
	//		m_pMyTestConf->m_LogFile<<"DEBUG: Enter AddItems! After Validate items.";
			GetTagRef(dwCount,*ppAddResults,pT);
			//если проверка прошла нормально
			m_DelAddItemsCS.Lock();

			_AsyncIORWMsg * pAs = new _AsyncIORWMsg;
			pAs->m_dwConnection = 0;
			pAs->m_phServerHandle = new OPCHANDLE[dwCount];
			ZeroMemory(pAs->m_phServerHandle,sizeof(OPCHANDLE)*dwCount);
			pAs->m_dwNumItems = dwCount;

			for(ULONG i=0;i<dwCount;i++)//пройдемся по всему массиву
			{
				if (FAILED(*((*ppErrors)+i))) continue;
		//		m_pMyTestConf->m_LogFile<<"DEBUG: Enter AddItems! Before generation items.";
				COPCTag * pTag = new COPCTag;
				//поищем на наличие такого итема в группе
				pTag->set_m_hObjectHandle((*ppAddResults+i)->hServer);
				itIS=m_Tags.find(/*(_OPCTagID)*pTag*/(*ppAddResults+i)->hServer);
				if (itIS!=m_Tags.end())
				{ //если все-таки есть уже, сформируем интерпретируемый handle
x:				DWORD ih=GenerateNewID(NULL,GetChannelID((*ppAddResults+i)->hServer));
					pTag->set_InterpretServerHandle((*ppAddResults+i)->hServer);
					pTag->set_m_hObjectHandle(ih);
					//Добавим в карту интерпретации
					INTERPRET2SERVERMap::iterator ii2s;
					ii2s=m_InterpretHandleMap.find(ih);
					if (ii2s!=m_InterpretHandleMap.end()/*Если уже есть*/) goto x;
					m_InterpretHandleMap[ih]=pTag->get_InterpretServerHandle();
					(*ppAddResults+i)->hServer = ih;
				}
				pTag->m_dwAccessRights = (*ppAddResults+i)->dwAccessRights;
				pTag->set_m_sObjectName(W2A((pItemArray+i)->szItemID));
				pTag->set_ClientHandle((pItemArray+i)->hClient);
			//	pTag->vtRequestedType=(pItemArray+i)->vtRequestedDataType;
				pTag->m_vtCanonicalDataType=(*ppAddResults+i)->vtCanonicalDataType;
				pTag->set_vtRequestedType((pItemArray+i)->vtRequestedDataType,&(*ppAddResults+i)->vtCanonicalDataType);
				pTag->set_m_TagRef(*(pT+i));

				if ((pItemArray+i)->bActive==-1)
					(pItemArray+i)->bActive=1;
				pTag->m_OPCActive = (pItemArray+i)->bActive;

				FILETIME ftx;
				GetSystemTimeAsFileTime(&ftx);
				pTag->set_m_ftLastUpdateTime(ftx);
			//	pTag->m_UpdateRate = m_UpdateRate;
				pTag->m_dwAccessRights = (*ppAddResults+i)->dwAccessRights;
				m_Tags.insert(_OPCGROUPTAGMAP::value_type(/*(_OPCTagID)(*pTag)*/pTag->get_m_hObjectHandle(),pTag));

				//Добавить в Массив Handle'ов для ADV_PRINTFIRST.
				*(pAs->m_phServerHandle+i)=(*ppAddResults+i)->hServer;
			}
			//delete pAs;
			m_DelAddItemsCS.Unlock();
			m_ControlThread.SendInactive2Active(pAs);
		}
			
		delete[] pT;
	//	m_pMyTestConf->m_LogFile<<"DEBUG: Enter AddItems! After generation items. Before exit return 0.";
		return S_OK;
	}
STDMETHODIMP CMyGroup::ValidateItems(ULONG dwCount, OPCITEMDEF * pItemArray, BOOL bBlobUpdate, OPCITEMRESULT * * ppValidationResults, HRESULT * * ppErrors)
{
//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems\n";//;

			USES_CONVERSION;
		//CLogFile_CS GGG;
		//GGG.SetNewFullLogName("c:\\PETRENKO222.log");
		//GGG<<"TEST Валидэйт тега!";
		//GGG<<W2A(pItemArray->szItemID);

		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
		{
			*ppErrors=NULL;
			*ppValidationResults=NULL;
			return OPC_E_SUSPENDED;
		}
//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 2";
		if (ppValidationResults == NULL)
			return E_POINTER;
//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 3";			
		if (ppErrors == NULL)
			return E_POINTER;
//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 4";
		_CHANNELMAP::iterator itm;
		std::vector<DWORD> vec;
		std::vector<DWORD>::iterator itv;
//		std::vector<OPCITEMDEF> DefVec;
//		DefVec.insert(pItemArray,dwCount,


		ISpaceBrowse* pSpaceBrowse;
		OPCITEMDEF * pIA=NULL,*pIAOld=NULL;
		//выделение памяти для возвращения клиенту
		*ppValidationResults=(OPCITEMRESULT*)CoTaskMemAlloc(sizeof(OPCITEMRESULT)*dwCount);
		for(ULONG lo=0;lo<dwCount;lo++)
			(*ppValidationResults+lo)->pBlob = NULL;
		OPCITEMRESULT *pRes=NULL;//внутри
		//выделение памяти для возвращения клиенту
		*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
		HRESULT* pEr=NULL;//внутри
		//Создаем свою структуру OPCITEMDEF
		pIAOld=pIA=(OPCITEMDEF*)CoTaskMemAlloc(sizeof(OPCITEMDEF)*dwCount);
		//копируем
		memcpy(pIA,pItemArray,sizeof(OPCITEMDEF)*dwCount);

		HRESULT hr=S_OK;
		DWORD dwMyCount = dwCount;
//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5";
		bool FlagNotAll=false,FlagIsAny=false;
		for(itm=m_pMyTestConf->m_ChannelMap.begin();itm!=m_pMyTestConf->m_ChannelMap.end();++itm)
		{
			IUnknown *pU;
		//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.1";
			if (SUCCEEDED(itm->second->GetBrowser(&pU)))
			{
			//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.2";
				pU->QueryInterface(IID_ISpaceBrowse,(void**)&pSpaceBrowse);
				pU->Release();
			//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.3";
				if (SUCCEEDED((hr=pSpaceBrowse->ValidateItem(dwMyCount,pIA,bBlobUpdate,&pRes,&pEr))))				
				{//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.4";
					vec.clear();
					long IndexIA=0;
					for(ULONG l=0;l<dwMyCount;l++)
					{
						//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.5";
						if((*(pEr+l)!=S_OK)&&(*(pEr+l)==OPC_E_UNKNOWNITEMID))
						{
							vec.insert(vec.end(),l);//вставляем в массив неблагополучных
							FlagNotAll=true;
							while((pItemArray+IndexIA)->hClient!=(pIA+l)->hClient)
								IndexIA++;
							*(*ppErrors+IndexIA)=*(pEr+l);
						}
						else
						{
							//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.6";
							while((pItemArray+IndexIA)->hClient!=(pIA+l)->hClient)
								IndexIA++;
							*(*ppValidationResults+IndexIA)=*(pRes+l);
							*(*ppErrors+IndexIA)=*(pEr+l);
							FlagIsAny=true;
						}
						//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.7";						
					}
                    if (!FlagNotAll) {
						//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.8";
						pSpaceBrowse->Release();
						CoTaskMemFree(pIA);
						//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.9";
						pIA=NULL;
						CoTaskMemFree(pRes);
					//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.10";
						pRes=NULL;
						CoTaskMemFree(pEr);
					//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.11";
						pEr=NULL;
						break;
					};
					pIAOld=pIA;
					//копируем результат
				//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.12";
					CoTaskMemFree(pRes);
					pRes=NULL;
				//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.13";
					CoTaskMemFree(pEr);
					pEr=NULL;
					//формируем массив
				//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.14";
					pIA=(OPCITEMDEF*)CoTaskMemAlloc(sizeof(OPCITEMDEF)*vec.size());
					//копируем только нужные данные (которые не прошли проверку в другом канале)
					DWORD i=0;
				//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.15";
					for(itv=vec.begin();itv!=vec.end();++itv,i++)
						*(pIA+i)=*(pIAOld+*itv);
					dwMyCount=i;
					CoTaskMemFree(pIAOld);
				}
				//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 5.16";
				pSpaceBrowse->Release();
			}
		}
//(*ppValidationResults)->pBlob=NULL;
	//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 6";
		if (FlagIsAny&&(!FlagNotAll)) return S_OK;
	//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 7";
		if (FlagNotAll&&FlagIsAny) return S_FALSE;
	//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 8";
		if (FlagNotAll&&(!FlagIsAny)) return S_FALSE;
	//	m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 9";
		
			CoTaskMemFree(*ppValidationResults);
			CoTaskMemFree(*ppErrors);
//m_pMyTestConf->m_LogFile<<"Вызов ValidateItems 10";
			return E_FAIL;

}
// TODO: Сделать ЗАШИЩЕННОЕ удаление тегов из группы
STDMETHODIMP CMyGroup::RemoveItems(ULONG dwCount, ULONG * phServer, HRESULT * * ppErrors)
	{
m_pMyTestConf->m_LogFile<<"Вызов RemoveItems\n";//);
		if (ppErrors == NULL)
			return E_POINTER;
	//	return S_OK;
		if (!dwCount) return S_OK;
		_OPCGROUPTAGMAP::iterator itm;
		m_DelAddItemsCS.Lock();
		*ppErrors = (HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);

		for (UINT i=0; i<dwCount;i++)
		{
		//	_OPCTagID id;
		//	id.set_m_hObjectHandle(*(phServer+i));
			itm=m_Tags.find(*(phServer+i));
			if (itm!=m_Tags.end())
			{
		//Также нам нужно удалить и интерпретатор
				m_InterpretHandleMap.erase(*(phServer+i));
				COPCTag* pTa=itm->second;
				m_Tags.erase(itm);
				
				delete pTa;
				*((*ppErrors)+i)=S_OK;
			}
			else
				*((*ppErrors)+i)=E_FAIL;

		}
		m_DelAddItemsCS.Unlock();
		return S_OK;
	}
STDMETHODIMP CMyGroup::SetActiveState(ULONG dwCount, ULONG * phServer, BOOL bActive, HRESULT * * ppErrors)
	{
m_pMyTestConf->m_LogFile<<"Вызов SetActiveState\n";//);
		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
		{
			*ppErrors=NULL;
			return OPC_E_SUSPENDED;
		}

		if (ppErrors == NULL)
			return E_POINTER;
		_OPCGROUPTAGMAP::iterator itm;
		
		HRESULT hRes=S_OK;
		bool AllOk=false;

		_AsyncIORWMsg * pAs = new _AsyncIORWMsg;
		pAs->m_dwNumItems = dwCount;
		pAs->m_phServerHandle = new OPCHANDLE[dwCount];
		ZeroMemory(pAs->m_phServerHandle,sizeof(OPCHANDLE)*dwCount);
		pAs->m_dwConnection=0;

		*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	//	_OPCTagID t;
		for(UINT i=0;i<dwCount;i++) //по весм итемам
		{
			//t.set_m_hObjectHandle(*(phServer+i));
			itm=m_Tags.find(*(phServer+i));
			if (itm==m_Tags.end())
			{
				*((*ppErrors)+i)=OPC_E_INVALIDHANDLE;
				hRes=S_FALSE;
				continue;
			}
			
			*((*ppErrors)+i)=S_OK;
			AllOk=true;
			if (itm->second->m_OPCActive!=bActive)
			{
				itm->second->m_OPCActive=bActive;
				if (itm->second->m_OPCActive)
				{
					*(pAs->m_phServerHandle+i)=itm->second->get_m_hObjectHandle();
				}
			}

			
		}

		m_ControlThread.SendInactive2Active(pAs);
		if (AllOk)
			return hRes;
		else 
		{
			CoTaskMemFree(*ppErrors);
			return E_FAIL;
		}
	}


STDMETHODIMP CMyGroup::SetClientHandles(ULONG dwCount, ULONG * phServer, ULONG * phClient, HRESULT * * ppErrors)
	{
m_pMyTestConf->m_LogFile<<"Вызов SetClientHandles\n";//);
		if (ppErrors == NULL)
			return E_POINTER;
	HRESULT hr; 	
	_OPCGROUPTAGMAP::iterator itm;

	*ppErrors =(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	//нужно сначала найти (может быть такой хендл уже есть?)
	hr=S_OK;
	for(UINT i=0;i<dwCount;i++)
	{ //по всем переданным итемам
		//может есть такой клиентский хандл?

		for (itm=m_Tags.begin();itm!=m_Tags.end();itm++)
			if ((itm->second)->get_ClientHandle()==*(phClient+i))
			{
					*(*ppErrors+i)=OPC_E_INVALIDHANDLE;
					hr=S_FALSE;
					break;
			}
			else *(*ppErrors+i)=S_OK;
		
		if (*(*ppErrors+i)==OPC_E_INVALIDHANDLE)
			continue;
		//найти - кому установить такой хандл
		//_OPCTagID tid;
		//tid.set_m_hObjectHandle(*(phServer+i));
		if ((itm=m_Tags.find(*(phServer+i)))!=m_Tags.end())
		{
			itm->second->set_ClientHandle(*(phClient+i));
		}

	}
		return hr;
	}


STDMETHODIMP CMyGroup::SetDatatypes(ULONG dwCount, ULONG * phServer, USHORT * pRequestedDatatypes, HRESULT * * ppErrors)
	{
m_pMyTestConf->m_LogFile<<"Вызов SetDatatypes\n";//);
		if (ppErrors == NULL)
			return E_POINTER;
		_OPCGROUPTAGMAP::iterator itm;
		
		HRESULT hRes=S_OK;
		bool AllOk=false;
		*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	//	_OPCTagID t;
		for(UINT i=0;i<dwCount;i++) //по весм итемам
		{
			//t.set_m_hObjectHandle(*(phServer+i));
			itm=m_Tags.find(*(phServer+i));
			if (itm==m_Tags.end())
			{
				*((*ppErrors)+i)=OPC_E_INVALIDHANDLE;
				hRes=S_FALSE;
				continue;
			}
			_variant_t x;

//			if (VariantChangeType(&x,&itm->second->m_Value,VARIANT_ALPHABOOL,*(pRequestedDatatypes+i))!=S_OK)
//			{
//				*((*ppErrors)+i)=OPC_E_BADTYPE;
//				hRes=S_FALSE;
//				continue;
//			}

			if (!itm->second->set_vtRequestedType(*(pRequestedDatatypes+i),NULL,true))
			{
				*((*ppErrors)+i)=OPC_E_BADTYPE;
				hRes=S_FALSE;
				continue;
			}

			*((*ppErrors)+i)=S_OK;
			AllOk=true;
				
		}

		if (AllOk)
			return hRes;
		else 
		{
			CoTaskMemFree(*ppErrors);
			return E_FAIL;
		}
	}


STDMETHODIMP CMyGroup::CreateEnumerator(REFIID riid, IUnknown * * ppUnk)
	{
m_pMyTestConf->m_LogFile<<"Вызов CMyGroup::CreateEnumerator\n";//);
		if (ppUnk == NULL)
			return E_POINTER;
		HRESULT hr;
	if (IsEqualIID(IID_IEnumOPCItemAttributes,riid))
	{
		typedef CComObjectNoLock<CComEnumOnSTL<IEnumOPCItemAttributes,&IID_IEnumOPCItemAttributes,OPCITEMATTRIBUTES*,_CopyOPCITEMATTRIBUTES<std::pair</*class /*_OPCTagID*/DWORD const ,class COPCTag *> ,OPCITEMATTRIBUTES*>,_OPCGROUPTAGMAP > > Enum;
		Enum * p = new Enum;
		if (p==NULL) hr= E_OUTOFMEMORY;
		else
		{
			hr=p->FinalConstruct();
			if (hr==S_OK)
			{
				hr=p->Init(NULL,m_Tags);
				if (hr==S_OK)
				{
					hr=p->QueryInterface(IID_IUnknown,(void**)ppUnk);
				}
			}
		}
		if (hr!=S_OK)
			delete p;

	}
	return hr;
	}
// IOPCSyncIO
HRESULT CMyGroup::CacheRefresh(ULONG dwConnection, OPCDATASOURCE dwSource,DWORD dwTransactionID2, ULONG * pTransactionID)
{
		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
		{
			pTransactionID=NULL;
			return OPC_E_SUSPENDED;
		}

	HRESULT GlobalHr=S_OK;

	//проверка на активность группы
	if (!this->m_bActive) 
		return E_FAIL;
	//проверка на активность тегов
	_OPCGROUPTAGMAP::iterator itm;
	bool IsFlag=false;
	for(itm=m_Tags.begin();itm!=m_Tags.end();++itm)
	{
		if (itm->second->m_OPCActive) 
		{
			IsFlag=true;
			break;
		}
	}
	if (!IsFlag)//если нет активных...
		return E_FAIL;

	//Создаем новую транзакцию
//	CTransactionWrapper * pTWrap=new CTransactionWrapper;
	//Генерируем идентификатор
//	pTWrap->m_dwTransactionID=GenerateNewID(NULL);
	*pTransactionID = GenerateNewID(NULL);
	//Заносим ее в вектор активных транзакций
//	m_TransactionVector.insert(m_TransactionVector.end(),pTWrap);

//	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);

	_AsyncIORWMsg * pmes = new _AsyncIORWMsg;
	pmes->m_dwConnection = dwConnection;
	pmes->m_dwNumItems = 0;
//	pTWrap->m_GlobalTagCount=0;
	pmes->m_dwSource=dwSource;
	pmes->m_phServerHandle = NULL;
	pmes->set_m_TransactionID(*pTransactionID);
	pmes->m_DestThreadID = m_ControlThread.get_m_ThreadID();
	pmes->m_Message=AsyncRefresh;
	pmes->m_TransactionID2;
			
	//Добавили сообщение в транзакцию
//	pTWrap->m_MessageVector.insert(pTWrap->m_MessageVector.end(),pmes);
	//m_pMyTestConf->m_LogFile<<"Добавлена транзакция %d \n",pTWrap->m_dwTransactionID);
					//отослали
	//pTWrap->ConfigComplite();
	m_ControlThread.AsRefresh(pmes);
	
	return GlobalHr;
}
HRESULT CMyGroup::CacheASyncRead(ULONG dwConnection, OPCDATASOURCE dwSource, ULONG dwCount, ULONG * phServer, ULONG * pTransactionID, HRESULT * * ppErrors)
{
	HRESULT GlobalHr=S_OK;
			//Вставим проверку на callback
	//Создаем новую транзакцию
	m_AsyncReadCS.Lock();
	CTransactionWrapper * pTWrap=new CTransactionWrapper;
	//Генерируем идентификатор
	pTWrap->m_dwTransactionID=GenerateNewID(NULL);
	*pTransactionID = pTWrap->m_dwTransactionID;
	//Заносим ее в вектор активных транзакций
	m_TransactionAccessCS.Lock();
	m_TransactionVector.insert(m_TransactionVector.end(),pTWrap);
	m_TransactionAccessCS.Unlock();
	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	_OPCGROUPTAGMAP::iterator itm;

	bool ErFlag=false;
	for(UINT i=0;i<dwCount;i++)
	{
		//_OPCTagID id;
		//id.set_m_hObjectHandle(*(phServer+i));
		itm=m_Tags.find(*(phServer+i));
		if (itm==m_Tags.end())
		{
			*(*ppErrors+i)=OPC_E_INVALIDHANDLE;
			ErFlag=true;
		}
		else
		{
		
			if (itm->second->m_dwAccessRights&OPC_READABLE)
				*(*ppErrors+i)=S_OK;
			else
			{
				*(*ppErrors+i)=OPC_E_BADRIGHTS;
				ErFlag=true;
			}
		}
	}
	if (ErFlag)
	{
		m_AsyncReadCS.Unlock();
		return S_FALSE;
	}

	_AsyncIORWMsg * pmes = new _AsyncIORWMsg;
	pmes->m_dwConnection = dwConnection;
	pmes->m_dwNumItems = dwCount;
	pTWrap->m_GlobalTagCount=dwCount;
	pmes->m_dwSource=dwSource;
	pmes->m_phServerHandle = new OPCHANDLE[dwCount] ;
	pmes->m_phInterpretHandle= new OPCHANDLE[dwCount];
	memcpy(pmes->m_phServerHandle,phServer,sizeof(OPCHANDLE)*dwCount);
//	memcpy(pmes->m_phInterpretHandle,phInterpret,sizeof(OPCHANDLE)*dwCount)
	pmes->set_m_TransactionID(pTWrap->m_dwTransactionID);//сменить
	pmes->m_DestThreadID = m_ControlThread.get_m_ThreadID();
	pmes->m_Message=AsyncRead;
			
	//Добавили сообщение в транзакцию
	pTWrap->m_MessageVector.insert(pTWrap->m_MessageVector.end(),pmes);
	//m_pMyTestConf->m_LogFile<<"Добавлена транзакция %d \n",pTWrap->m_dwTransactionID);
					//отослали
	pTWrap->ConfigComplite();
	m_AsyncReadCS.Unlock();
	m_ControlThread.AsRead(pmes);
	
	return GlobalHr;
}
HRESULT CMyGroup::CacheSyncRead(OPCDATASOURCE dwSource, ULONG dwCount, ULONG * phServer, OPCITEMSTATE * * ppItemValues, HRESULT * * ppErrors)
{
	//используется для передачи клиенту тегов из КЭША группы.
	//char f[100];
	//sprintf(f,"%s %s %d","DEBUG: Enter CacheSyncRead!",this->get_m_sObjectName().c_str(),dwCount);
	//m_pMyTestConf->m_LogFile<<f;

	//DEBUG
	/*	_OPCGROUPTAGMAP::iterator iiii;
		for(long ff=0;ff<dwCount;ff++)
		{
			iiii=m_Tags.find((DWORD)*(phServer+ff));
			COPCTag *pTtt=iiii->second;
			m_pMyTestConf->m_LogFile<<pTtt->get_m_sObjectName().c_str();
		}*/

	CLogFile_CS testoDebug;
	//testoDebug.SetNewFullLogName("c:\\TagValues.log");
	//testoDebug<<"Начинаем!!!";
	//DEBUG
	HRESULT hr=S_OK;
	//CComCriticalSection MyCSR;
//	MyCSR.Init();
//	MyCSR.Lock();
	*ppItemValues=(OPCITEMSTATE*)CoTaskMemAlloc(sizeof(OPCITEMSTATE)*dwCount);
	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);

	_OPCGROUPTAGMAP::iterator itm;
	//m_pMyTestConf->m_LogFile<<"DEBUG: Enter CacheSyncRead! before All tags cicle.";
	m_DelAddItemsCS.Lock();
//DEBUG CHANGED
//	_OPCTagID id;
	//_variant_t tv;
	OPCITEMSTATE * pMiddle=NULL;
	HRESULT * pMiddleError=NULL;
	for(UINT i=0;i<dwCount;i++)
	{
		//(*ppItemValues)->
		pMiddle=*ppItemValues+i;
		pMiddleError=*ppErrors+i;
		VariantInit(&/*(*ppItemValues+i)*/pMiddle->vDataValue);//инит в любом случае
//		id.set_m_hObjectHandle(*(phServer+i));
		itm=m_Tags.find(*(phServer+i));
		if(itm!=m_Tags.end())
		{ //есть такой
			
			/*(*ppItemValues+i)*/pMiddle->hClient=itm->second->get_ClientHandle();
			itm->second->ReadBaseValues(pMiddle->vDataValue,/*(*ppItemValues+i)*/pMiddle->wQuality,*pMiddleError,/*(*ppItemValues+i)*/pMiddle->ftTimeStamp);
			/*(*ppItemValues+i)*///VariantCopy(&pMiddle->vDataValue,&tv);
			//if (itm->second->get_m_sObjectName()=="Вычислитель КЦ-2.CALC.O2_PVS.QC")
			//{
			//	char ght[200];
			//	sprintf(ght,"Value %f Quality=%d Error=%d",(double)_variant_t(pMiddle->vDataValue),pMiddle->wQuality,*pMiddleError);
			//	testoDebug<<ght;

			//}
			if (FAILED(*pMiddleError/*(*ppErrors+i)*/))
			{
				hr=S_FALSE;
	/*			char ght[200];
				sprintf(ght,"Плохой %s Quality=%d Error=%d",itm->second->get_m_sObjectName().c_str(),pMiddle->wQuality,*pMiddleError);
				m_pMyTestConf->m_LogFile<<ght;*/

			}
//
//			if (CascVariant(0l)==pMiddle->vDataValue)
//			{
//				char ght[200];
//				sprintf(ght,"Нулевое значение %s Quality=%d Error=%d Тип=%d",itm->second->get_m_sObjectName().c_str(),pMiddle->wQuality,*pMiddleError,(int)pMiddle->vDataValue.vt);
////				m_pMyTestConf->m_LogFile<<ght;
//			}

	//		if (pMiddle->vDataValue.vt==VT_EMPTY)
	//		{
	//			char ght[200];
	//			sprintf(ght,"VT_EMPTY значение %s Quality=%d Error=%d Тип=%d",itm->second->get_m_sObjectName().c_str(),pMiddle->wQuality,*pMiddleError,(int)pMiddle->vDataValue.vt);
	////			m_pMyTestConf->m_LogFile<<ght;
	//		}

			if (!(m_bActive&&itm->second->m_OPCActive))
			{ //если что-то неактивно...
				/*(*ppItemValues+i)*/pMiddle->wQuality =OPC_QUALITY_OUT_OF_SERVICE;
			}
			
		
		}else
		{

			*(*ppErrors+i)=OPC_E_INVALIDHANDLE;
			hr=S_FALSE;
		}
	}
	m_DelAddItemsCS.Unlock();
	//MyCSR.Unlock();
	//MyCSR.Term();
	//m_pMyTestConf->m_LogFile<<"DEBUG: Enter CacheSyncRead! Before exit return 0.";
	return hr;
}
STDMETHODIMP CMyGroup::Read(OPCDATASOURCE dwSource, ULONG dwCount, ULONG * phServer, OPCITEMSTATE * * ppItemValues, HRESULT * * ppErrors)
	{
		
		//проверка состояния сервера и перенаправление в КЭШ при простое
		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
			dwSource=OPC_DS_CACHE;

		//проверка параметров
		if (ppItemValues == NULL)
			return E_POINTER;		
		if (ppErrors == NULL)
			return E_POINTER;
//DEBUG
	//	m_pMyTestConf->m_LogFile<<"Чтение111!";
	//	return CacheSyncRead(dwSource,dwCount,phServer,ppItemValues,ppErrors);
//DEBUG
		//отправим обрабатывать в КЭШ, если требуется
		if (dwSource==OPC_DS_CACHE) //из КЭША группы
			return CacheSyncRead(dwSource,dwCount,phServer,ppItemValues,ppErrors);

		HRESULT GlobalHr=S_OK;

		//m_pMyTestConf->m_LogFile<<"Read From device!!!!";//(int)(dwSource!=OPC_DS_CACHE);
		//m_pMyTestConf->m_LogFile<<dwCount;
		//из DEVICE
	//DEBUG
		//_OPCGROUPTAGMAP::iterator iiii;
		//for(long ff=0;ff<dwCount;ff++)
		//{
		//	iiii=m_Tags.find((DWORD)*(phServer+ff));
		//	COPCTag *pTtt=iiii->second;
		//	m_pMyTestConf->m_LogFile<<pTtt->get_m_sObjectName().c_str();
		//}

	//DEBUG
		std::vector<HANDLE> EventArray;
		std::vector<_SyncIORMsg*> MesVec;
		ULONG* pL=new ULONG[dwCount];
		ULONG * pIhL=new ULONG[dwCount];
		try{//глобальная попытка
		
		try{ //попытка отлова ошибки!!!
// TODO: Рассмотреть возможную переделку Read'ов для чтения из локальных тегов группы
		_CHANNELMAP::iterator itm;
	//наплевать на источник данных
	//надо разобрать по каналам и разослать по ним же
		
		memcpy(pL,phServer,sizeof(ULONG)*dwCount);

		//Создаем контэйнер для интерпретации
		
		ZeroMemory(pIhL,sizeof(ULONG)*dwCount);

		std::sort(pL,pL+dwCount); //отсортируем для скорости

		//заполним интерпретации
		INTERPRET2SERVERMap::iterator ii2s;
		for(UINT hi=0;hi<dwCount;hi++)
		{
			ii2s=m_InterpretHandleMap.find(*(pL+hi));//ищем интерпретер
			if (ii2s!=m_InterpretHandleMap.end())//если есть
			{
				*(pIhL+hi)=*(pL+hi);//устанавливаем интерпретатор
				*(pL+hi)=ii2s->second;//заменяем на реальный
			}
		}
		
		
		DWORD *pFirst=pL,Count=1;
		UINT i=1;
		bool Flag;
//m_pMyTestConf->m_LogFile<<"DEBUG: Enter SyncRead! All tags cicle.";		
		do
		{
			if (i>dwCount) break;
			if (i==dwCount) 
			{
				Flag=true;
				//Count++;
			}
			else
			{
				//if (!(Flag=(GetChannelID(*(pL+i))!=GetChannelID(*pFirst))))
				Flag=(GetChannelID(*(pL+i))!=GetChannelID(*pFirst));
				//	Count++;
				//Flag=false;
			}

			if (Flag)
			{
				_ChannelID ch;
				ch.set_m_hObjectHandle(GetChannelID(*pFirst));
				itm=m_pMyTestConf->m_ChannelMap.find(ch);
				bool ErF=false;
				if (itm==m_pMyTestConf->m_ChannelMap.end())
				{
					ErF=true;
				}else	if (((CCChannelObj*)itm->second)->m_Cache->get_m_ThreadID()==0)
					{//здесь находится проверка на состояние потока кэша.
						ErF=true;
					}

				if (ErF)
				{
					m_pMyTestConf->m_LogFile<<"В заглушке!";
					//сами сформируем заглушку
					_SyncIORMsg* pmes=new _SyncIORMsg(true);
					pmes->m_dwNumItems=Count;
					pmes->m_dwSource=dwSource;
					pmes->SetReady();
					//pmes->m_hEvent=CreateEvent(NULL,TRUE,TRUE,NULL);
					EventArray.insert(EventArray.end(),(HANDLE)*pmes);
					pmes->m_Message=SyncRead;
					pmes->m_phServerHandle=pFirst;
					pmes->m_phInterpretHandle=pIhL+(pFirst-pL);
					MesVec.insert(MesVec.end(),pmes);
					pmes->m_ppItemValues=(OPCITEMSTATE*)CoTaskMemAlloc(sizeof(OPCITEMSTATE)*Count);
					pmes->m_pErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*Count);
					for (UINT xyz=0;xyz<Count;xyz++)
					{
						VariantInit(&(pmes->m_ppItemValues+xyz)->vDataValue);
						*(pmes->m_pErrors+xyz)=OPC_E_INVALIDHANDLE;
					}

				}
				else
				{					//Создаем структуру для передачи
					_SyncIORMsg* pmes=new _SyncIORMsg(true);
					pmes->m_dwNumItems=Count;
					pmes->m_dwSource=dwSource;
					//pmes->m_hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
					EventArray.insert(EventArray.end(),(HANDLE)*pmes);
					pmes->m_Message=SyncRead;
					pmes->m_phServerHandle=pFirst;
					pmes->m_phInterpretHandle=pIhL+(pFirst-pL);
					itm->second->SRead(pmes);
					MesVec.insert(MesVec.end(),pmes);
				}
				
				Count=0;
				pFirst=pL+i;
			}
	
			i++;
			Count++;
		}while(true);

//m_pMyTestConf->m_LogFile<<"DEBUG: Enter SyncRead! Wait Event.";
		WaitForMultipleObjects(MesVec.size(),&EventArray[0],TRUE,INFINITE);
		}catch(_com_error &e)
		{
			//Ошибка COM'а
			this->m_pOPCSrv ->m_pMyTestConf->m_LogFile<<"Ошибка COM'а при чтении из устройства. ERROR!!ERROR!!";
			this->m_pOPCSrv ->m_pMyTestConf->m_LogFile<<e.Error();
		}
		catch(...)
		{
			this->m_pOPCSrv ->m_pMyTestConf->m_LogFile<<"Ошибка ХРЕН ЗНАЕТ КАКАЯ при чтении из устройства. ERROR!!ERROR!!";
		}
		try{
		//_SyncIORMsg::m_ppItemValues
		//прислали...
		//расставляем теги по местам

		*ppItemValues=(OPCITEMSTATE*)CoTaskMemAlloc(sizeof(OPCITEMSTATE)*dwCount);
		*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);


		std::vector<_SyncIORMsg*>::iterator itv;
		_OPCGROUPTAGMAP::iterator itt;
		//m_pMyTestConf->m_LogFile<<"DEBUG: Enter SyncRead! Generate result.";
		for (itv=MesVec.begin();itv!=MesVec.end();++itv)
		{//по всем сообщениям
			//_SyncIORMsg::
			for (ULONG mi=0;mi<(*itv)->m_dwNumItems;mi++)
			{//по всем итемам в сообщении
				for(ULONG si=0;si<dwCount;si++)
				{//если интерпретатор или серверный хэндл совпадают - все ок
					if((*(phServer+si)==*((*itv)->m_phServerHandle+mi))||(*(phServer+si)==*((*itv)->m_phInterpretHandle+mi)))
					{//если равно - этот
					
						VariantInit(&((*ppItemValues)+si)->vDataValue);


				//		_OPCTagID id;
						//id.set_m_hObjectHandle(*(phServer+si));
						if((itt=m_Tags.find(*(phServer+si)))!=m_Tags.end())
						{
							if (SUCCEEDED(*((*itv)->m_pErrors+mi)))
							{
								VariantCopy(&((*ppItemValues)+si)->vDataValue,&((*itv)->m_ppItemValues+mi)->vDataValue);
								((*ppItemValues)+si)->ftTimeStamp=((*itv)->m_ppItemValues+mi)->ftTimeStamp;
								((*ppItemValues)+si)->wQuality=((*itv)->m_ppItemValues+mi)->wQuality;

								*((*ppErrors)+si)=*((*itv)->m_pErrors+mi);
	
								((*ppItemValues)+si)->hClient=itt->second->get_ClientHandle();
								itt->second->WriteBaseValues(&((*ppItemValues)+si)->vDataValue,((*ppItemValues)+si)->wQuality,*((*ppErrors)+si),((*ppItemValues)+si)->ftTimeStamp);
								*((*ppErrors)+si)=VariantChangeType(&((*ppItemValues)+si)->vDataValue,&((*ppItemValues)+si)->vDataValue,VARIANT_ALPHABOOL,itt->second->vtRequestedType);
							}else
							{
								*((*ppErrors)+si)=*((*itv)->m_pErrors+mi);
								((*ppItemValues)+si)->wQuality=OPC_QUALITY_UNCERTAIN;
								if (*((*itv)->m_pErrors+mi)!=OPC_E_BADRIGHTS)
									itt->second->set_m_LastError(*((*itv)->m_pErrors+mi));
							}
						}else
						{
							*((*ppErrors)+si)=OPC_E_INVALIDHANDLE;
						}
						VariantClear(&((*itv)->m_ppItemValues+mi)->vDataValue);
						if (FAILED(*((*ppErrors)+si)))
							GlobalHr=S_FALSE;
						break;
					}
				}
			}
//			CloseHandle((*itv)->m_hEvent);
			CoTaskMemFree((*itv)->m_ppItemValues);
			(*itv)->m_ppItemValues=NULL;
			CoTaskMemFree((*itv)->m_pErrors);
			(*itv)->m_pErrors=NULL;
			delete (_SyncIORMsg*)(*itv);

		}
	//m_pMyTestConf->m_LogFile<<"DEBUG: Enter SyncRead! Before Exit.";
	
		}catch(_com_error &e)
		{
			//Ошибка COM'а
			this->m_pOPCSrv ->m_pMyTestConf->m_LogFile<<"Ошибка COM'а при чтении из устройства 222. ERROR!!ERROR!!";
			this->m_pOPCSrv ->m_pMyTestConf->m_LogFile<<e.Error();
		}
		catch(...)
		{
			this->m_pOPCSrv ->m_pMyTestConf->m_LogFile<<"Ошибка ХРЕН ЗНАЕТ КАКАЯ при чтении из устройства 222. ERROR!!ERROR!!";
		}

		}catch(_com_error &e)
		{
			//Ошибка COM'а
			this->m_pOPCSrv ->m_pMyTestConf->m_LogFile<<"Ошибка COM'а при чтении из устройства 333. ERROR!!ERROR!!";
			this->m_pOPCSrv ->m_pMyTestConf->m_LogFile<<e.Error();
		}
		catch(...)
		{
			this->m_pOPCSrv ->m_pMyTestConf->m_LogFile<<"Ошибка ХРЕН ЗНАЕТ КАКАЯ при чтении из устройства 333. ERROR!!ERROR!!";
		}
	//	this->m_pOPCSrv ->m_pMyTestConf->m_LogFile<<"Выход из чтения тегов!!!";
		delete[] pL;
		delete[] pIhL;

		return GlobalHr;
	}
STDMETHODIMP CMyGroup::Write(ULONG dwCount, ULONG * phServer, VARIANT * pItemValues, HRESULT * * ppErrors)
	{
m_pMyTestConf->m_LogFile<<"Вызов Write\n";//);

		if (m_pOPCSrv->m_pMyTestConf->IsSuspended())
		{
			//установим возвращаемые значения в NULL
			*ppErrors=NULL;
			return OPC_E_SUSPENDED;
		}

		if (ppErrors == NULL)
			return E_POINTER;

		HRESULT GlobalHr=S_OK;
		_CHANNELMAP::iterator itm;
	//надо разобрать по каналам и разослать по ним же
		ULONG* pL=new ULONG[dwCount];
		memcpy(pL,phServer,sizeof(ULONG)*dwCount);
//		memcpy(pIV,pItemValues,sizeof(VARIANT)*dwCount);

		//Создаем контэйнер для интерпретации
		ULONG * pIhL=new ULONG[dwCount];
		ZeroMemory(pIhL,sizeof(ULONG)*dwCount);


		std::sort(pL,pL+dwCount);
		//заполним интерпретации
		INTERPRET2SERVERMap::iterator ii2s;
		for(UINT hi=0;hi<dwCount;hi++)
		{
			ii2s=m_InterpretHandleMap.find(*(pL+hi));//ищем интерпретер
			if (ii2s!=m_InterpretHandleMap.end())//если есть
			{
				*(pIhL+hi)=*(pL+hi);//устанавливаем интерпретатор
				*(pL+hi)=ii2s->second;//заменяем на реальный
			}
		}


		std::vector<HANDLE> EventArray;
		std::vector<_SyncIORMsg*> MesVec;
		std::vector<VARIANT> VarVector(dwCount);
		
		DWORD *pFirst=pL,Count=1;
		UINT i=1;
		bool Flag;


		for (ULONG xi=0;xi<dwCount;xi++)//Инициаоизация первой?
		{
			if (*pL==*(phServer+xi))//если равны идентификаторы,то
			{
				VariantInit(&VarVector[0]);
				VariantCopy(&VarVector[0],pItemValues+xi);
				break;
			}

		}


		do
		{

			if (i>dwCount) break;

			if (i!=dwCount)
			{
				for(ULONG im=0;im<dwCount;im++)
				{
					if (*(pL+i)==*(phServer+im))//если равны идентификаторы,то
					{
						VariantInit(&VarVector[i]);
						VariantCopy(&VarVector[i],pItemValues+im);
						break;
					}
				}
			}

			if (i==dwCount) 
			{
				Flag=true;
				//Count++;
			}
			else
			{
				//if (!(Flag=(GetChannelID(*(pL+i))!=GetChannelID(*pFirst))))
				//	Count++;
				//Flag=false;
				Flag=(GetChannelID(*(pL+i))!=GetChannelID(*pFirst));
			}


			if (Flag)
			{
				_ChannelID ch;
				ch.set_m_hObjectHandle(GetChannelID(*pFirst));
				itm=m_pMyTestConf->m_ChannelMap.find(ch);
				

				bool ErF=false;
				if (itm==m_pMyTestConf->m_ChannelMap.end())
				{
					ErF=true;
				}else 	if (((CCChannelObj*)itm->second)->m_Cache->get_m_ThreadID()==0)
					{
						ErF=true;
					}

				if (ErF)
				{
					//сами сформируем заглушку
					_SyncIORMsg* pmes=new _SyncIORMsg(true);
					pmes->m_dwNumItems=Count;
					//pmes->m_dwSource=dwSource;
					//pmes->m_hEvent=CreateEvent(NULL,TRUE,TRUE,NULL);
					pmes->SetReady();
					EventArray.insert(EventArray.end(),(HANDLE)*pmes);
					pmes->m_Message=SyncWrite;
					pmes->m_phServerHandle=pFirst;
					pmes->m_phInterpretHandle=pIhL+(pFirst-pL);
					pmes->m_pItemValues=&VarVector[pFirst-pL];
					MesVec.insert(MesVec.end(),pmes);

					pmes->m_pErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*Count);
					for (UINT xyz=0;xyz<Count;xyz++)
					{
						*(pmes->m_pErrors+xyz)=OPC_E_INVALIDHANDLE;

					}

				}
				else
				{
					//Создаем структуру для передачи
					
					_SyncIORMsg* pmes=new _SyncIORMsg(true);
					pmes->m_dwNumItems=Count;
					//pmes->m_dwSource=dwSource;
					//pmes->m_hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
					EventArray.insert(EventArray.end(),(HANDLE)*pmes);
					pmes->m_Message=SyncWrite;
					pmes->m_phServerHandle=pFirst;
					pmes->m_phInterpretHandle=pIhL+(pFirst-pL);
					pmes->m_pItemValues=&VarVector[pFirst-pL];
			
					itm->second->SWrite(pmes);
					MesVec.insert(MesVec.end(),pmes);

				}
				
				Count=0;
				pFirst=pL+i;
			}
	
			i++;
			Count++;
		}while(true);


		WaitForMultipleObjects(MesVec.size(),&EventArray[0],TRUE,100000);



		//расставляем теги по местам

		*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
		std::vector<_SyncIORMsg*>::iterator itv;
		_OPCGROUPTAGMAP::iterator itt;
		for (itv=MesVec.begin();itv!=MesVec.end();++itv)
		{//по всем сообщениям
			//_SyncIORMsg::
			for (ULONG mi=0;mi<(*itv)->m_dwNumItems;mi++)
			{//по всем итемам в сообщении
				for(ULONG si=0;si<dwCount;si++)
				{//если интерпретатор или серверный хэндл совпадают - все ок
					if((*(phServer+si)==*((*itv)->m_phServerHandle+mi))||(*(phServer+si)==*((*itv)->m_phInterpretHandle+mi)))
					{//если равно - этот
						*((*ppErrors)+si)=*((*itv)->m_pErrors+mi);
//						_OPCTagID id;
//						id.set_m_hObjectHandle(*(phServer+si));
						if((itt=m_Tags.find(*(phServer+si)))==m_Tags.end())
						{
							*((*ppErrors)+si)=OPC_E_INVALIDHANDLE;
							GlobalHr=S_FALSE;
						}
						else //устанавливаем новое значение
						{
							//COPCTag::set_m_LastError(*((*ppErrors)+si));
							WORD q=OPC_QUALITY_GOOD;
							SYSTEMTIME st;
							FILETIME ft;
							GetLocalTime(&st);
							SystemTimeToFileTime(&st,&ft);

							itt->second->WriteBaseValues((*itv)->m_pItemValues+mi,q,*((*ppErrors)+si),ft);
						}
						VariantClear((*itv)->m_pItemValues+mi);
						

					}	

					if (FAILED(*((*ppErrors)+si)))
						GlobalHr=S_FALSE;
				}
			}
			//CloseHandle((*itv)->m_hEvent);
			CoTaskMemFree((*itv)->m_pErrors);

			(*itv)->m_pErrors=NULL;
			delete (_SyncIORMsg*)(*itv);

		}
	//	CoTaskMemFree(
	
		delete[] pL;
		delete[] pIhL;
		//здесь возвратим			
		return GlobalHr;
	}

DWORD CMyGroup::GetChannelID(DWORD hTag)
{
	DWORD x=hTag>>16;
	x&=0x00FF;
	return	(hTag>>16);//&(0x00FF);
}

void CMyGroup::GetTagRef(DWORD Count,OPCITEMRESULT *pItemArray, CTag **Tags)
{

	_CHANNELMAP::iterator itc;
	for (ULONG i=0;i<Count;i++)
	{
		_ChannelID id;
		id.set_m_hObjectHandle(GetChannelID((pItemArray+i)->hServer));
		itc=m_pMyTestConf->m_ChannelMap.find(id);
		if (itc!=m_pMyTestConf->m_ChannelMap.end())
		{
			*(Tags+i)=itc->second->GetTagRef((pItemArray+i)->hServer);
		}
		else
		{
			*(Tags+i)=NULL;
		}
	}

	return;
}


STDMETHODIMP CMyGroup::OnChannelDataChange()
{
	return S_OK;
}

STDMETHODIMP CMyGroup::DeletedTags(DWORD dwCount,OPCHANDLE *hSrvHandles)
{

	return S_OK;
}
HRESULT CMyGroup::CreateWriteNotify(DWORD Count,std::list<COPCTag*> *pList,DWORD dwTransactionID)
{
	HRESULT hr=S_OK;
	DWORD dwTransid = dwTransactionID;
	OPCHANDLE hGroup = m_hClientGroup;
	HRESULT hrMasterError=S_OK;
	DWORD dwCount=Count;

	OPCHANDLE* phClientItems=(OPCHANDLE*)CoTaskMemAlloc(sizeof(OPCHANDLE)*dwCount);
	HRESULT *pErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);

	//заполним масив хэндлов и массив ошибок. Сформируем MasterError
	std::list<COPCTag*>::iterator itl;
	int i=0;
	for(itl=pList->begin();itl!=pList->end();++itl)
	{
		*(pErrors+i)=(*itl)->get_m_LastError();
		if (FAILED(*(pErrors+i)))
				hrMasterError=S_FALSE ;
		*(phClientItems+i)=(*itl)->get_ClientHandle();
		i++;
	}

	Fire_OnWriteComplete(dwTransactionID,hGroup,hrMasterError,dwCount,phClientItems,pErrors);

	CoTaskMemFree(pErrors);
	CoTaskMemFree(phClientItems);
	return hr;
}
HRESULT CMyGroup::CreateReadOrChangeNotify(DWORD Count,std::list<COPCTag*> *pList,DWORD dwTransactionID)
{
	DWORD  dwTransid;
	OPCHANDLE hGroup; 
	HRESULT  hrMasterquality, hrMastererror;
	DWORD  dwCount; 
	OPCHANDLE * phClientItems; 
	VARIANT * pvValues; 
	WORD  * pwQualities;
	FILETIME  * pftTimeStamps;
	HRESULT *pErrors;

	std::list<COPCTag*>::iterator itl;
	//Выделение памяти для заполнения и передачи

	pErrors = (HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*Count);
	phClientItems = (OPCHANDLE*)CoTaskMemAlloc(sizeof(OPCHANDLE)*Count);
	pvValues = (VARIANT*)CoTaskMemAlloc(sizeof(VARIANT)*Count);
	pwQualities = (WORD*)CoTaskMemAlloc(sizeof(WORD)*Count);
	pftTimeStamps = (FILETIME*)CoTaskMemAlloc(sizeof(FILETIME)*Count);

	hGroup=m_hClientGroup;
	dwTransid=dwTransactionID;
	dwCount=Count;
	hrMasterquality=S_OK;
	hrMastererror=S_OK;
	VARIANT *pMiddleVar;
	//Заполним остальное
	UINT i=0;//счетчик
	//CLogFile_CS testoDebug;
	//testoDebug.SetNewFullLogName("c:\\TagValuesNotify.log");
	//testoDebug<<"Начинаем!!!";

	for(itl=pList->begin();itl!=pList->end();++itl)
	{
		pMiddleVar=pvValues+i;
		//_variant_t t;
		VariantInit(pMiddleVar);
		(*itl)->ReadBaseValues(*pMiddleVar,*(pwQualities+i),*(pErrors+i),*(pftTimeStamps+i));
//		*(pErrors+i)=(*itl)->m_hrLastError;

			//if ((*itl)->get_m_sObjectName()=="Вычислитель КЦ-2.CALC.O2_PVS.QC")
			//{
			//	char ght[200];
			//	sprintf(ght,"Value %f Quality=%d Error=%d",(double)_variant_t(*pMiddleVar),*(pwQualities+i),*(pErrors+i));
			//	testoDebug<<ght;
			//}

		if (*(pwQualities+i)!=OPC_QUALITY_GOOD)
				hrMasterquality=S_FALSE;
		if (FAILED(*(pErrors+i)))
				hrMastererror=S_FALSE ;
		*(phClientItems+i)=(*itl)->get_ClientHandle();

//		VariantInit(pvValues+i);
//		VariantCopy(pvValues+i,&t);

//		*(pwQualities+i)=(*itl)->m_wQuality;

//		*(pftTimeStamps+i)=(*itl)->m_ftLastUpdateTime;
		i++;
	}

	if (dwTransid)
		Fire_OnReadComplete(dwTransid,hGroup,hrMasterquality,hrMastererror,dwCount,phClientItems,pvValues,pwQualities,pftTimeStamps,pErrors);	
	else
		Fire_OnDataChange(dwTransid,hGroup,hrMasterquality,hrMastererror,dwCount,phClientItems,pvValues,pwQualities,pftTimeStamps,pErrors);
	//Очищаем память
	
	for(i=0;i<Count;i++)
	{
		VariantClear(pvValues+i);
	}

	CoTaskMemFree(pErrors);
	CoTaskMemFree(pvValues);
	CoTaskMemFree(phClientItems);
	CoTaskMemFree(pwQualities);
	CoTaskMemFree(pftTimeStamps);
	//char dddeee[100];
	//sprintf(dddeee,"%s %s %d","Notifycation!",this->get_m_sObjectName().c_str(),Count);
//	m_pMyTestConf->m_LogFile<<dddeee;
	return S_OK;
}

DWORD CMyGroup::CControlThread::fbody ()
 {
	
	if (m_Owner->m_bActive)
		m_TimerID=SetTimer(NULL,1,m_Owner->m_UpdateRate,NULL);	//период - 200 мс (минимум)

	MSG msg;
	::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE) ;
	_AsyncIORWMsg * mp=NULL;
	//регистрация потока для получения уведомлений об изменении ссылок от каналов
	//------------------------------------------
	OPCGroupControlThreadList.insert(OPCGroupControlThreadList.end(),this->get_m_ThreadID());
	//------------------------------------------
	while(GetMessage(&msg,0,0,0))
	{
		::DispatchMessage(&msg);
		switch(msg.message)
		{
//		case WM_CONTROLTHREAD_UPDATE_TAGREFS://сообщение приходит от объекта-конфигуратора после изменения состояния
//			break;
		case WM_GROUP_SET_NEW_STATE://сообщение приходит от группы-владельца
			OnSetNewState();
			break;
		case WM_TIMER:
			OnTimerMessage(msg);
			break;
		case WM_CONTROLTHREAD_TRANSACTION_COMPLITE_READ:
			OnTransactionRead(msg);
			break;
		case WM_CONTROLTHREAD_TRANSACTION_COMPLITE_WRITE:
			OnTransactionWrite(msg);
			break;
		case WM_CONTROLTHREAD_TRANSACTION_COMPLITE_REFRESH:
			mp=(_AsyncIORWMsg*)msg.lParam;
			OnTimerMessage(msg,mp->m_dwConnection,true,mp->get_m_TransactionID(),mp->m_TransactionID2);
			delete mp;
		case WM_CONTROLTHREAD_TRANSACTION_CANCEL:
			OnCancel2(msg);
			break;
		case WM_CONTROLTHREAD_TRANSACTION_CONFIG_COMPLITE_READ:
			OnTransactionRead(msg,true);
			break;
		case WM_CONTROLTHREAD_TRANSACTION_CONFIG_COMPLITE_WRITE:
			OnTransactionWrite(msg,true);
			break;
		case WM_CONTROLTHREAD_INACTIVE2ACTIVE:
			OnChangeStateInactive2Active(msg);
			break;
		}
	}
//удалении из списка регистрации
//------------------------------------------
std::list<DWORD>::iterator itl;
for(itl=OPCGroupControlThreadList.begin();itl!=OPCGroupControlThreadList.end();++itl)
	if (*itl==get_m_ThreadID())
	{
		OPCGroupControlThreadList.erase(itl);
		break;
	}
//------------------------------------------
	KillTimer(NULL,m_TimerID);
	return 0;
}
	//здесь будет производится проверка
	// на изменения и отсылка нотификаций
//DEL void CMyGroup::CControlThread::OnAsyncReadChache(MSG msg)
//DEL {
//DEL 	 //проверяем и отсылаем
//DEL 	 DWORD DataSize=0l;
//DEL 	 _OPCGROUPTAGMAP::iterator  itm;
//DEL 	 std::list<COPCTag*> ChL;
//DEL 	 std::list<COPCTag*>::iterator itl;
//DEL 	 _variant_t vRetVal;
//DEL 	 FILETIME   ftRetVal;
//DEL 	 HRESULT	hrRetVal;
//DEL 	 WORD		wRetVal;
//DEL 	 m_Owner->m_DelAddItemsCS.Lock();
//DEL 
//DEL 
//DEL 	 m_Owner->m_DelAddItemsCS.Unlock();
//DEL 	 //Здесь уже будем иметь Размер и список
//DEL 
//DEL 	 if (!ChL.size()) return;
//DEL 
//DEL 	 //Нужно упаковать и отправить...
//DEL 	
//DEL 	m_Owner->CreateStreamWithTime(ChL.size(),&ChL,DataSize,0);
//DEL 	m_Owner->CreateStreamWithoutTime(ChL.size(),&ChL,DataSize,0);
//DEL 	
//DEL 	if (!m_Owner->m_Enabled) return; //так Enabled есть только в версии OPC 2.0- отключим ее.
//DEL 	m_Owner->CreateReadOrChangeNotify(ChL.size(),&ChL,0);
//DEL 	return;
//DEL }
void CMyGroup::CControlThread::AsRead(_AsyncIORWMsg *mes)
{
	PostThreadMessage(get_m_ThreadID(),WM_CONTROLTHREAD_TRANSACTION_COMPLITE_READ,0,(long)mes);
}
void CMyGroup::CControlThread::AsRefresh(_AsyncIORWMsg *mes)
{
	PostThreadMessage(get_m_ThreadID(),WM_CONTROLTHREAD_TRANSACTION_COMPLITE_REFRESH,0,(long)mes);
}
void CMyGroup::CControlThread::AsCancel(DWORD dwTransactionID)
{
	PostThreadMessage(get_m_ThreadID(),WM_CONTROLTHREAD_TRANSACTION_CANCEL,0,dwTransactionID);
}
void CMyGroup::CControlThread::SendInactive2Active(_AsyncIORWMsg * pAs)
{
PostThreadMessage(get_m_ThreadID(),WM_CONTROLTHREAD_INACTIVE2ACTIVE,0,(long)pAs);
}

void CMyGroup::CControlThread::OnChangeStateInactive2Active(MSG msg)
{
	//здесь будет посылаться ADM_PRIMFIRST;
	
	//Переберем все переданные итемы
	DWORD DataSize=0l;
	std::list<COPCTag*> ChL;
	std::list<COPCTag*>::iterator itl;
	VARIANT vRetVal;
	VariantInit(&vRetVal);
	FILETIME   ftRetVal;
	HRESULT	hrRetVal;
	WORD		wRetVal;
	m_Owner->m_pMyTestConf->m_LogFile<<"ChangeState for some items\n";//);
	_OPCGROUPTAGMAP::iterator itas;
	_AsyncIORWMsg * pAs=(_AsyncIORWMsg*)msg.lParam;
	m_Owner->m_DelAddItemsCS.Lock();
	for(UINT i=0;i<pAs->m_dwNumItems;i++) //по всем
	{
		if (*(pAs->m_phServerHandle+i)!=0)//если задано
		{
			
			//_OPCTagID id;
		//	id.set_m_hObjectHandle(*(pAs->m_phServerHandle+i));
			itas=m_Owner->m_Tags.find(*(pAs->m_phServerHandle+i));	
			if (itas!=m_Owner->m_Tags.end())//если нашли такой в группе
			{
				if(itas->second->m_OPCActive)
				{
/*xxxCHxxx*/ 		CTag* pTag = itas->second->get_m_TagRef();
					//проверим на наличие в удаленных
					if (pTag==NULL)
					//r->m_
					{
						itas->second->set_m_LastError(OPC_E_UNKNOWNITEMID);
					}else
					{
					
						pTag->ReadBaseValues(vRetVal,wRetVal,hrRetVal,ftRetVal);
						if (FAILED(hrRetVal)) 
						{
							if (hrRetVal!=OPC_E_BADRIGHTS)
								itas->second->set_m_LastError(hrRetVal);
						//	continue;
						}else
						{	
							itas->second->WriteBaseValues(&vRetVal,wRetVal,hrRetVal,ftRetVal);
							itas->second->OPCValueChangeType(NULL,&DataSize);
						}
					}
					ChL.insert(ChL.end(),itas->second);
				}
			}
		}
	}
	VariantClear(&vRetVal);
	
	if (!ChL.size())
	{
		m_Owner->m_DelAddItemsCS.Unlock();
		return ;
	}
	//Нужно упаковать и отправить...
	if (m_Owner->AdviseMap.size())
	{
		m_Owner->CreateStreamWithTime(ChL.size(),&ChL,DataSize,0,pAs->m_dwConnection);
		m_Owner->CreateStreamWithoutTime(ChL.size(),&ChL,DataSize,0,pAs->m_dwConnection);
	}
	
	if (!m_Owner->m_Enabled) 
	{	
		m_Owner->m_DelAddItemsCS.Unlock();
		return; //так Enabled есть только в версии OPC 2.0- отключим ее.
	}
	
	if (m_Owner->m_vec.GetSize()&&(!pAs->m_dwConnection))
		m_Owner->CreateReadOrChangeNotify(ChL.size(),&ChL,0);
	delete pAs;
	m_Owner->m_DelAddItemsCS.Unlock();
}

HRESULT CMyGroup::CControlThread::OnTimerMessage(MSG msg,DWORD dwConnection,bool IsRefresh,DWORD dwTransactionID,DWORD dwTransactionID2)
 {
	 //проверяем и отсылаем
	// m_Owner->m_pMyTestConf->m_LogFile<<this->get_m_ThreadID();
	
	 DWORD DataSize=0l;
	 _OPCGROUPTAGMAP::iterator  itm;
	 std::list<COPCTag*> ChL;
	 std::list<COPCTag*>::iterator itl;
	// _variant_t vRetVal;
	 VARIANT vRetVal;
	 VariantInit(&vRetVal);//инициализируем
	 FILETIME   ftRetVal;
	 HRESULT	hrRetVal;
	 WORD		wRetVal;
	 m_Owner->m_DelAddItemsCS.Lock();
	 bool FlagSuspendedServerState=false;
	 if (m_Owner->m_pOPCSrv->m_pMyTestConf->IsSuspended())
		FlagSuspendedServerState=true;

long 	 DebugCount=0;
	 for(itm=m_Owner->m_Tags.begin();itm!=m_Owner->m_Tags.end();++itm)
	 {
		 DebugCount++;
		 if (FlagSuspendedServerState) //если сервер перешел в состояние SUSPENDED  
		 {
			 (itm->second)->m_wQuality = OPC_QUALITY_OUT_OF_SERVICE;
			 continue;
		 }

		 //если в RUNNING
		 
		 if ((itm->second)->m_OPCActive) //если итем активен
		 {
			 CTag* pTag=(itm->second)->get_m_TagRef();
			 if (pTag==NULL)
			 {
				 (itm->second)->set_m_LastError(OPC_E_UNKNOWNITEMID);
				 continue;
			 }
			 pTag->ReadBaseValues(vRetVal,wRetVal,hrRetVal,ftRetVal);
			if (FAILED(hrRetVal)) 
			{
				if (hrRetVal!=OPC_E_BADRIGHTS)
					itm->second->set_m_LastError(hrRetVal);
				continue;
			}
			bool Changed=true;
			if (!IsRefresh)
				Changed=itm->second->IsChanged( vRetVal,wRetVal);
			if (Changed)
			{
				itm->second->WriteBaseValues(&vRetVal,wRetVal,hrRetVal,ftRetVal);
				//if (itm->second->get_m_sObjectName()=="VICh-KC2.CALC.O2_PVS.QC")
				//	ATLTRACE("%f \n",(double)_variant_t(vRetVal));
   				itm->second->OPCValueChangeType(NULL,&DataSize);
				ChL.insert(ChL.end(),itm->second);
			}
		 }
	 }
//	ATLTRACE2("%d ---> %d\n",m_Owner->m_Tags.size(),DebugCount);
	 VariantClear(&vRetVal);
//	 m_Owner->m_DelAddItemsCS.Unlock();
	 //Здесь уже будем иметь Размер и список
//m_Owner->m_pMyTestConf->m_LogFile<<"DEBUG: Enter CControlThread::OnTimerMessage! Exit from all cicles. ";
	 if (!ChL.size())
	 {
		 m_Owner->m_DelAddItemsCS.Unlock();
//		 m_Owner->m_pMyTestConf->m_LogFile<<"DEBUG: Enter CControlThread::OnTimerMessage! All tags old.";
		 return S_OK;
	 }
	 //Нужно упаковать и отправить...
	if (m_Owner->AdviseMap.size()&&(!dwTransactionID2))
	{
		m_Owner->CreateStreamWithTime(ChL.size(),&ChL,DataSize,dwTransactionID,dwConnection);
		m_Owner->CreateStreamWithoutTime(ChL.size(),&ChL,DataSize,dwTransactionID,dwConnection);
	}
	
	if (!m_Owner->m_Enabled) 
	{	
		m_Owner->m_DelAddItemsCS.Unlock();
		return S_OK; //так Enabled есть только в версии OPC 2.0- отключим ее.
	}

	if (m_Owner->m_vec.GetSize()&&(!dwConnection))
		m_Owner->CreateReadOrChangeNotify(ChL.size(),&ChL,dwTransactionID2);

	 m_Owner->m_DelAddItemsCS.Unlock();
// m_Owner->m_pMyTestConf->m_LogFile<<"DEBUG: Enter CControlThread::OnTimerMessage! Exit return 0.";
 return S_OK;
}

bool CMyGroup::CTransactionWrapper::IsTransactionComplite()
{
return m_InMessageCount>=m_MessageVector.size();
}

DWORD CMyGroup::CTransactionWrapper::IncMessageCount()
{
	m_InMessageCount++;
return m_InMessageCount;
}
void CMyGroup::CControlThread::OnCancel2(MSG msg)
{
	//отсылаем подписчикам версии 2
	m_Owner->Fire_OnCancelComplete((DWORD)msg.lParam,m_Owner->m_hClientGroup);

}
void CMyGroup::CControlThread::OnTransactionRead(MSG msg,bool ConfigComplite)
{
	 DWORD DataSize=0l;
	 _OPCGROUPTAGMAP::iterator  itm;
	 std::list<COPCTag*> ChL;
	 std::vector<_AsyncIORWMsg*>::iterator mesitv;
	 std::vector<HRESULT> ErrorVector;
	 _AsyncIORWMsg * mp=(_AsyncIORWMsg*)msg.lParam;
	std::vector<CTransactionWrapper*>::iterator itv;
	
	_variant_t tst;
	for(itv=m_Owner->m_TransactionVector.begin();itv!=m_Owner->m_TransactionVector.end();++itv)
	{
			if (*(*itv)==mp->get_m_TransactionID())
			{
				//если идентификатор транзакции совпал - работаем
				if (!ConfigComplite)
					(*itv)->IncMessageCount();
				else
					delete mp;
				if ((*itv)->IsConfigured())
					if ((*itv)->IsTransactionComplite())
					{//РАЗБИРАЕМ И СОБИРАЕМ
						m_Owner->m_TransactionAccessCS.Lock();
/////////////////////////////////////////////////////////////////////////					

					//	_OPCTagID t;
						m_Owner->m_DelAddItemsCS.Lock();
						DWORD con=0;//(*itv)->m_dwConnection;
						//по всему вектору сообщений
						for (mesitv=(*itv)->m_MessageVector.begin();mesitv!=(*itv)->m_MessageVector.end();++mesitv)
						{	//по всем тегам в сообщении
							con=(*mesitv)->m_dwConnection;
							for (UINT i=0;i<(*mesitv)->m_dwNumItems;i++)
							{
								//проверим на интерпретатор
								if ((*mesitv)->m_dwSource==OPC_DS_CACHE)
								//	t.set_m_hObjectHandle(*((*mesitv)->m_phServerHandle+i));
									itm=m_Owner->m_Tags.find(*((*mesitv)->m_phServerHandle+i));
								else
									if (*((*mesitv)->m_phInterpretHandle+i))
								//		t.set_m_hObjectHandle(*((*mesitv)->m_phInterpretHandle+i));
										itm=m_Owner->m_Tags.find(*((*mesitv)->m_phInterpretHandle+i));
									else
								//		t.set_m_hObjectHandle(*((*mesitv)->m_phServerHandle+i));
										itm=m_Owner->m_Tags.find(*((*mesitv)->m_phServerHandle+i));
									

								//itm=m_Owner->m_Tags.find(t);
								if (itm!=m_Owner->m_Tags.end())
								{
// TODO: Не нужно присваивать значения локальным тегам
									if ((*mesitv)->m_dwSource==OPC_DS_DEVICE)
									{
										if (SUCCEEDED(*((*mesitv)->m_pErrors+i))){

											itm->second->WriteBaseValues((*mesitv)->pvValues+i,*((*mesitv)->pwQualities+i),*((*mesitv)->m_pErrors+i),*((*mesitv)->pftTimeStamps+i));
											itm->second->OPCValueChangeType(NULL,&DataSize);
										}else
										{
											if ((*((*mesitv)->m_pErrors+i))!=OPC_E_BADRIGHTS)
												itm->second->set_m_LastError(*((*mesitv)->m_pErrors+i));
											DataSize+=itm->second->GetDataSize();
										}
										VariantClear((*mesitv)->pvValues+i);
										m_Owner->AsyncCacheFlag=false;
									}else
									{
										 DataSize+=itm->second->GetDataSize();
										 m_Owner->AsyncCacheFlag=true;
									}
									ChL.insert(ChL.end(),itm->second);
								}
							}
						}
						//m_Owner->m_DelAddItemsCS.Unlock();
						//Нужно упаковать и отправить...
						if (!(*itv)->IsCanceled())
						{
						
							if (m_Owner->AdviseMap.size()&&con)
							{
								m_Owner->CreateStreamWithTime(ChL.size(),&ChL,DataSize,(*itv)->m_dwTransactionID,con);
								m_Owner->CreateStreamWithoutTime(ChL.size(),&ChL,DataSize,(*itv)->m_dwTransactionID,con);
							}
							if (m_Owner->m_vec.GetSize()&&(!con))
								if (!m_Owner->AsyncCacheFlag)
									m_Owner->CreateReadOrChangeNotify(ChL.size(),&ChL,(*itv)->m_dwTransactionID2);
						}
						m_Owner->m_DelAddItemsCS.Unlock();
/////////////////////////////////////////////////////////////////////////
//						Beep(500,500);
						//удаляем все
						m_Owner->m_pMyTestConf->m_LogFile<<"Удалена транзакция %d \n";//,(*itv)->m_dwTransactionID);
					CMyGroup::CTransactionWrapper * xtr=*itv;
					m_Owner->m_TransactionVector.erase(itv);
					delete xtr;
					m_Owner->m_TransactionAccessCS.Unlock();
						break;
					}
			}
	}
}

void CMyGroup::CControlThread::OnTransactionWrite(MSG msg,bool ConfigComplite)
{
//	return;
	 DWORD DataSize=0l;
	 _OPCGROUPTAGMAP::iterator  itm;
	 std::list<COPCTag*> ChL;
	 std::vector<_AsyncIORWMsg*>::iterator mesitv;

	_AsyncIORWMsg * mp=(_AsyncIORWMsg*)msg.lParam;
	std::vector<CTransactionWrapper*>::iterator itv;
	
	for(itv=m_Owner->m_TransactionVector.begin();itv!=m_Owner->m_TransactionVector.end();++itv)
	{
			if (*(*itv)==mp->get_m_TransactionID())
			{
				//если идентификатор транзакции совпал - работаем
				if (!ConfigComplite)
					(*itv)->IncMessageCount();
				else
					delete mp;
				if ((*itv)->IsConfigured())
					if ((*itv)->IsTransactionComplite())
					{//РАЗБИРАЕМ И СОБИРАЕМ
						m_Owner->m_TransactionAccessCS.Lock();
/////////////////////////////////////////////////////////////////////////					

					//	_OPCTagID t;
						m_Owner->m_DelAddItemsCS.Lock();
						DWORD con=0;//(*itv)->m_dwConnection;
						//по всему вектору сообщений
						for (mesitv=(*itv)->m_MessageVector.begin();mesitv!=(*itv)->m_MessageVector.end();++mesitv)
						{	//по всем тегам в сообщении
							con=(*mesitv)->m_dwConnection;
							for (UINT i=0;i<(*mesitv)->m_dwNumItems;i++)
							{
								//проверим на интерпретатор
								if (*((*mesitv)->m_phInterpretHandle+i))
								//	t.set_m_hObjectHandle(*((*mesitv)->m_phInterpretHandle+i));
									itm=m_Owner->m_Tags.find(*((*mesitv)->m_phInterpretHandle+i));
								else
									//t.set_m_hObjectHandle(*((*mesitv)->m_phServerHandle+i));
									itm=m_Owner->m_Tags.find(*((*mesitv)->m_phServerHandle+i));


								//itm=m_Owner->m_Tags.find(t);
								if (itm!=m_Owner->m_Tags.end())
								{
// TODO: Не нужно присваивать значения локальным тегам
									itm->second->WriteBaseValues((*mesitv)->pvValues+i,*((*mesitv)->pwQualities+i),*((*mesitv)->m_pErrors+i),*((*mesitv)->pftTimeStamps+i));
									itm->second->OPCValueChangeType(NULL,&DataSize);
									itm->second->set_m_LastError(*((*mesitv)->m_pErrors+i));
									ChL.insert(ChL.end(),itm->second);
									VariantClear(((*mesitv)->m_pItemValues+i));
								}
							}
						}
					//	m_Owner->m_DelAddItemsCS.Unlock();
						//Нужно упаковать и отправить...
						if (!(*itv)->IsCanceled())
						{
							if (m_Owner->AdviseMap.size()&&con)
							{
								m_Owner->CreateStreamWriteComplite(ChL.size(),&ChL,(*itv)->m_dwTransactionID,con);
							}
							if (m_Owner->m_vec.GetSize()&&(!con))
								if (!m_Owner->AsyncCacheFlag)
									m_Owner->CreateWriteNotify(ChL.size(),&ChL,(*itv)->m_dwTransactionID2);
						}
//						m_Owner->CreateReadOrChangeNotify(ChL.size(),&ChL,(*itv)->m_dwTransactionID);
						m_Owner->m_DelAddItemsCS.Unlock();
/////////////////////////////////////////////////////////////////////////
//						Beep(500,500);
						//удаляем все
					delete *itv;
					m_Owner->m_TransactionVector.erase(itv);
					m_Owner->m_TransactionAccessCS.Unlock();
						break;
					}
			}
	}
}


void CMyGroup::CControlThread::OnSetNewState()
{
	KillTimer(NULL,m_TimerID);
if (m_Owner->m_bActive)
	m_TimerID=SetTimer(NULL,1,m_Owner->m_UpdateRate,NULL);
}


void CMyOPCSrv::FinalRelease()
	{
//		Fire_ShutdownRequest(NULL);
		m_pMyTestConf->m_LogFile<<"Удаление сервера (реальное)\n";//);
		// Добавить Удаление групп
		
		for (int i=0;i<m_Groups.size();i++)
		{
			
			((CMyGroup *)m_Groups[i])->FinalRelease();
			delete m_Groups[i];
		}
		m_Groups.clear();
		OPCServersList.remove(this);
			
	}


void CMyGroup::UpdateRealTagReferences()
{
	_OPCGROUPTAGMAP::iterator itm;

	long x=0;
	//медленно - но верно!
	for (itm=m_Tags.begin();itm!=m_Tags.end();++itm)
	{
		DWORD hhh=0;
		if (itm->second->get_InterpretServerHandle()!=0)
		{
			hhh=itm->second->get_InterpretServerHandle();
		}
		else 
			hhh=itm->second->get_m_hObjectHandle();
		
		_ChannelID ss;
		ss.set_m_hObjectHandle(GetChannelID(hhh));
		std::map<_ChannelID,CCChannelObj*>::iterator itch;

		itch=m_pMyTestConf->m_ChannelMap.find(ss);
		if (itch==m_pMyTestConf->m_ChannelMap.end())
		{
			itm->second->set_m_TagRef(NULL);
		}
		else
			itm->second->set_m_TagRef(itch->second->GetTagRef(hhh));

	}
}

void CMyOPCSrv::UpdateTagsRefs()
{
	//просто проходим по всем группам и вызываем обновление ссылок
	for(int i=0;i<m_Groups.size();i++)
	{
		((CMyGroup*)m_Groups[i])->UpdateRealTagReferences();
	}
	
}

// метод для обновления ссылок на РЕАЛЬНЫЕ теги каналов
HRESULT CMyGroup::CControlThread::OnUpdateTagRefs(void)
	{
	HRESULT hRes=S_OK;
	//обработка по каналам
	return hRes;
	}
