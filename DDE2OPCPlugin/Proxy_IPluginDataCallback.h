// Proxy_IPluginDataCallback.h: interface for the Proxy_IPluginDataCallback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROXY_IPLUGINDATACALLBACK_H__128CABF7_B49F_4D58_9AD7_2BAE4819B78F__INCLUDED_)
#define AFX_PROXY_IPLUGINDATACALLBACK_H__128CABF7_B49F_4D58_9AD7_2BAE4819B78F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//##ModelId=3C4E3C7703AF
template <class T>
class CProxy_IPluginDataCallback : public IConnectionPointImpl< T, &IID_IPluginDataCallback, CComDynamicUnkArray >	
{
public:
	//##ModelId=3C4E3C7800C8
	HRESULT Fire_OnDeviceNotAvailable()
	{
		HRESULT hr=S_OK;
		T* pT= static_cast<T*>(this);
		int nConnectionIndex; 
		int nConnections = m_vec.GetSize();
		for (nConnectionIndex=0;nConnectionIndex<nConnections;nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPluginDataCallback* pPlug = reinterpret_cast<IPluginDataCallback*>(sp.p);
			
			if (pPlug!=NULL)
				hr=pPlug->OnDeviceNotAvailable();
		}
		return hr;
	}
	//##ModelId=3C4E3C7800DC
	HRESULT Fire_OnTagsChange(DWORD dwCount, DWORD* phClientItems, VARIANT *pvValues,WORD* pwQualities,FILETIME*  pftTimeStamps, HRESULT * pErrors)
	{
		HRESULT hr=S_OK;
		T* pT= static_cast<T*>(this);
		int nConnectionIndex; 
		int nConnections = m_vec.GetSize();
		for (nConnectionIndex=0;nConnectionIndex<nConnections;nConnectionIndex++)
		{
			pT->Lock();
			CComPtr<IUnknown> sp = m_vec.GetAt(nConnectionIndex);
			pT->Unlock();
			IPluginDataCallback* pPlug = reinterpret_cast<IPluginDataCallback*>(sp.p);
			
			if (pPlug!=NULL)
				hr=pPlug->OnTagsChange(dwCount,phClientItems,pvValues,pwQualities,pftTimeStamps,pErrors);
			
		}
		return hr;
	}

};

#endif // !defined(AFX_PROXY_IPLUGINDATACALLBACK_H__128CABF7_B49F_4D58_9AD7_2BAE4819B78F__INCLUDED_)
