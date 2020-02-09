/********************************************************************
	created:	2002/01/23
	created:	23:1:2002   12:14
	filename: 	D:\Prj\VC++\OPC\OPCImpl\OPC2OPCPlugin\NotifyRecipients.h
	file path:	D:\Prj\VC++\OPC\OPCImpl\OPC2OPCPlugin
	file base:	NotifyRecipients
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef __NOTIFYRECIPIENTS_H_
#define __NOTIFYRECIPIENTS_H_

//Базовый класс для получения нотификаций
template <class T>
class CNotifyBase
{
public:
	CNotifyBase()
	{
		m_Connected=false;
		m_RWCS.Init();
		m_pOwner=NULL;
	}

virtual ~CNotifyBase()
	{
		m_RWCS.Term();
	}

	void SetOwner(T* pOwner)
	{
		m_pOwner=pOwner;
	}
	bool IsConnected()
	{
		return m_Connected;
	}
virtual	HRESULT DisconnectFromNotify(DWORD dwGroupID)=0;
virtual HRESULT ConnectToNotify(DWORD dwGroupID)=0;
protected:
	T* m_pOwner;
	bool m_Connected;
	CComCriticalSection m_RWCS;
};


//классы для получения нотификаций v.2.03
template <class T>
class CNotify_IOPCDataCallback : public CComObjectRootEx<CComSingleThreadModel>,
								public CNotifyBase<T>,
								public IOPCDataCallback
{
public:

	HRESULT FinalConstruct()
	{
		m_dwCoockie=0;
		return S_OK;
	}

	BEGIN_COM_MAP(CNotify_IOPCDataCallback)
		COM_INTERFACE_ENTRY(IOPCDataCallback)
	END_COM_MAP()
	
public:
	HRESULT DisconnectFromNotify(DWORD dwGroupID)
	{
		if (!IsConnected())
			return S_OK;
		HRESULT hr=S_OK;
		IUnknown* pUnk=NULL;
		
		if(SUCCEEDED(hr=m_pOwner->m_Group->QueryInterface(IID_IConnectionPointContainer,(void**)&pUnk)))
		{	
			hr=AtlUnadvise(pUnk,IID_IOPCDataCallback,m_dwCoockie);
			pUnk->Release();
			m_Connected=false;
		}
		return hr;
	}
	HRESULT ConnectToNotify(DWORD dwGroupID)
	{
		IUnknown * pPDC=NULL,*pUnk=NULL;
		if (IsConnected())
			return S_OK;
		this->QueryInterface(IID_IUnknown,(void**)&pPDC);
		this->AddRef();
		HRESULT hr=S_OK;
		
		if(SUCCEEDED(hr=m_pOwner->m_Group->QueryInterface(IID_IUnknown,(void**)&pUnk)))
		{
			if(SUCCEEDED(hr=AtlAdvise(pUnk,pPDC,IID_IOPCDataCallback,&m_dwCoockie)))
			{
					m_Connected=true;
			}
			pUnk->Release();
		}
		pPDC->Release();
		return hr;
	}

private:
	DWORD m_dwCoockie;
public:
//методы интерфейсов
STDMETHOD (OnDataChange)(
     DWORD       dwTransid, 
     OPCHANDLE   hGroup, 
     HRESULT     hrMasterquality,
     HRESULT     hrMastererror,
     DWORD       dwCount, 
     OPCHANDLE * phClientItems, 
     VARIANT   * pvValues, 
     WORD      * pwQualities,
     FILETIME  * pftTimeStamps,
     HRESULT   * pErrors
);

STDMETHOD (OnReadComplete)(
    DWORD       dwTransid, 
    OPCHANDLE   hGroup, 
    HRESULT     hrMasterquality,
    HRESULT     hrMastererror,
    DWORD       dwCount, 
    OPCHANDLE * phClientItems, 
    VARIANT   * pvValues, 
    WORD      * pwQualities,
    FILETIME  * pftTimeStamps,
    HRESULT   * pErrors
);

STDMETHOD (OnWriteComplete)(
    DWORD       dwTransid, 
    OPCHANDLE   hGroup, 
    HRESULT     hrMastererr, 
    DWORD       dwCount, 
    OPCHANDLE * pClienthandles, 
    HRESULT   * pErrors
);

STDMETHOD (OnCancelComplete)(
    DWORD       dwTransid, 
    OPCHANDLE   hGroup
);


};

//классы для получения нотификаций v.1.0a

template <class T>
class CNotify_IAdviseSink : public CComObjectRootEx<CComMultiThreadModel>,
							public CNotifyBase<T>,
							public IAdviseSink
{
public:
	
	HRESULT FinalConstruct()
	{
		m_dwConnection=0;
		fmt.cfFormat=RegisterClipboardFormat("OPCSTMFORMATDATA");
		fmt.dwAspect=DVASPECT_CONTENT;
		fmt.lindex=-1;
		fmt.ptd=NULL;
		fmt.tymed = TYMED_HGLOBAL;
		return S_OK;
	}
	BEGIN_COM_MAP(CNotify_IAdviseSink)
		COM_INTERFACE_ENTRY(IAdviseSink)
		END_COM_MAP()
		
public:
	HRESULT DisconnectFromNotify(DWORD dwGroupID)
	{
		HRESULT hr=S_OK;
		if (!IsConnected())
			return S_OK;
		IDataObject* pUnk=NULL;
		hr=m_pOwner->m_Group->QueryInterface(IID_IDataObject,(void**)&pUnk);
		if(SUCCEEDED(hr))
		{	
			hr=pUnk->DUnadvise(m_dwConnection);
			pUnk->Release();
			m_Connected=false;
		}
		return hr;

	}
	HRESULT ConnectToNotify(DWORD dwGroupID)
	{
		IDataObject * pDO=NULL;
		if (IsConnected())
			return S_OK;
	
		//	this->AddRef();
		HRESULT hr=S_OK;
		IAdviseSink * pAS=NULL;
		//		this->Int
		hr=this->QueryInterface(IID_IAdviseSink,(void**)&pAS);
		//	pAS->OnDataChange(NULL,NULL);
		
		if(SUCCEEDED(hr=m_pOwner->m_Group->QueryInterface(IID_IDataObject,(void**)&pDO)))
		{
			hr=pDO->DAdvise(&fmt,ADVF_PRIMEFIRST,pAS,&m_dwConnection);
			if(SUCCEEDED(hr))
			{
				m_Connected=true;
			}
			pDO->Release();
		}
		return hr;
	}

private:
	DWORD m_dwConnection;
	FORMATETC fmt;
public:
//методы интерфейсов
	STDMETHOD_(void,OnDataChange)(LPFORMATETC pFE, LPSTGMEDIUM pSTM);
	STDMETHOD_(void,OnViewChange)(DWORD, LONG);
	STDMETHOD_(void,OnRename)(LPMONIKER);
	STDMETHOD_(void,OnSave)(void);
	STDMETHOD_(void,OnClose)(void);
};


//методы приемы нотификаций v1.0a
template <class T>
STDMETHODIMP_(void) CNotify_IAdviseSink<T>::OnDataChange(LPFORMATETC pFE, LPSTGMEDIUM pSTM)
{
	m_RWCS.Lock();
	ATLTRACE("Нотификация - IDataObject!!!\n");
	m_pOwner->OwnerOnDataChange(pFE,pSTM);
	m_RWCS.Unlock();
	return;
}
template <class T>
STDMETHODIMP_(void) CNotify_IAdviseSink<T>::OnViewChange(DWORD, LONG)
{
	m_RWCS.Lock();
	m_RWCS.Unlock();

	return;
}

template <class T>
STDMETHODIMP_(void) CNotify_IAdviseSink<T>::OnRename(LPMONIKER)
{
	m_RWCS.Lock();
	m_RWCS.Unlock();
	return;
}

template <class T>
STDMETHODIMP_(void) CNotify_IAdviseSink<T>::OnSave(void)
{
	m_RWCS.Lock();
	m_RWCS.Unlock();
	return;
}

template <class T>
STDMETHODIMP_(void) CNotify_IAdviseSink<T>::OnClose(void)
{
	m_RWCS.Lock();
	m_RWCS.Unlock();
	return;
}

//методы приемы нотификаций v2.03

template <class T>
STDMETHODIMP CNotify_IOPCDataCallback<T>::OnDataChange(DWORD       dwTransid, OPCHANDLE   hGroup, HRESULT     hrMasterquality,
     HRESULT     hrMastererror,DWORD       dwCount, OPCHANDLE * phClientItems, VARIANT   * pvValues, 
     WORD      * pwQualities,FILETIME  * pftTimeStamps,HRESULT   * pErrors)
{
	m_RWCS.Lock();
	try{
	
//	ATLTRACE("Нотификация!!!\n");
	//Требуется преобразовать в наш формат передачи и ВСЕ!!!!!!!!!!!!!!!!!!!!!
	m_pOwner->OwnerOnDataChange(dwTransid,hGroup,hrMasterquality,hrMastererror,
		dwCount,phClientItems,pvValues,pwQualities,pftTimeStamps,pErrors);
//	m_pOwner->Fire_OnTagsChange();
	}catch(...)
	{
		ATLTRACE("ererererererererer\n");
	}
	m_RWCS.Unlock();

	return S_OK;
}

template <class T>
STDMETHODIMP CNotify_IOPCDataCallback<T>::OnReadComplete(DWORD       dwTransid, OPCHANDLE   hGroup, HRESULT     hrMasterquality,HRESULT     hrMastererror,
    DWORD       dwCount, OPCHANDLE * phClientItems, VARIANT   * pvValues, WORD      * pwQualities,FILETIME  * pftTimeStamps,
    HRESULT   * pErrors)
{
	m_RWCS.Lock();
	m_RWCS.Unlock();

	return S_OK;
}

template <class T>
STDMETHODIMP CNotify_IOPCDataCallback<T>::OnWriteComplete(DWORD       dwTransid, OPCHANDLE   hGroup, HRESULT     hrMastererr, 
    DWORD       dwCount, OPCHANDLE * pClienthandles, HRESULT   * pErrors)
{
	m_RWCS.Lock();
	m_RWCS.Unlock();

	return S_OK;
}

template <class T>
STDMETHODIMP CNotify_IOPCDataCallback<T>::OnCancelComplete(DWORD       dwTransid, OPCHANDLE   hGroup)
{
	m_RWCS.Lock();
	m_RWCS.Unlock();

	return S_OK;
}



#endif //__NOTIFYRECIPIENTS_H_