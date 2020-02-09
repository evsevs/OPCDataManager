// OPCDataCallback.h: interface for the CProxy_IOPCDataCallback class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPCDATACALLBACK_H__3D0E6422_0FB8_4B73_B147_FA2836613A8D__INCLUDED_)
#define AFX_OPCDATACALLBACK_H__3D0E6422_0FB8_4B73_B147_FA2836613A8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#import "D:\DEVELOP\OPC\OPC2\OPCDA.TLB" raw_interfaces_only, raw_native_types, no_namespace, named_guids 
typedef DWORD OPCHANDLE;
//#include "opcda.h"
//#include "opcda_i.c"
//##ModelId=3B2979EE0384
template <class T>
class CProxy_IOPCDataCallback : public IConnectionPointImpl<T,&IID_IOPCDataCallback >  
{
public:

	//##ModelId=3B2979EE03C4
	HRESULT Fire_OnDataChange(	DWORD  dwTransid,
								OPCHANDLE hGroup, 
								HRESULT  hrMasterquality,
								HRESULT  hrMastererror,
								DWORD  dwCount, 
								OPCHANDLE * phClientItems, 
								VARIANT * pvValues, 
								WORD  * pwQualities,
								FILETIME  * pftTimeStamps,
								HRESULT *pErrors)
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
			IOPCDataCallback* pChan = reinterpret_cast<IOPCDataCallback*>(sp.p);
			
			if (pChan!=NULL)
				hr=pChan->OnDataChange(dwTransid,hGroup,hrMasterquality,hrMastererror,dwCount,phClientItems,
										pvValues,pwQualities,pftTimeStamps,pErrors);
			
		}
		return hr;
	}

	//##ModelId=3B2979EE03B9
	HRESULT Fire_OnReadComplete(	DWORD  dwTransid, 
									OPCHANDLE hGroup, 
									HRESULT  hrMasterquality,
									HRESULT  hrMastererror,
									DWORD  dwCount, 
									OPCHANDLE * phClientItems, 
									VARIANT * pvValues, 
									WORD  * pwQualities,
									FILETIME  * pftTimeStamps,
									HRESULT *pErrors)
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
			IOPCDataCallback* pChan = reinterpret_cast<IOPCDataCallback*>(sp.p);
			
			if (pChan!=NULL)
				hr=pChan->OnReadComplete(dwTransid,hGroup,hrMasterquality,hrMastererror,dwCount,phClientItems,
										pvValues,pwQualities,pftTimeStamps,pErrors);
			
		}
		return hr;
	}

	//##ModelId=3B2979EE03B2
	HRESULT Fire_OnWriteComplete(	DWORD  dwTransid, 
									OPCHANDLE	hGroup, 
									HRESULT  hrMasterError, 
									DWORD  dwCount, 
									OPCHANDLE * phClientItems, 
									HRESULT   * pErrors)
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
			IOPCDataCallback* pChan = reinterpret_cast<IOPCDataCallback*>(sp.p);
			
			if (pChan!=NULL)
				hr=pChan->OnWriteComplete(dwTransid,hGroup,hrMasterError,dwCount,phClientItems,pErrors);
		}
		return hr;

	}

	//##ModelId=3B2979EE03AF
	HRESULT Fire_OnCancelComplete(	DWORD  dwTransid, 
									OPCHANDLE	hGroup )
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
			IOPCDataCallback* pChan = reinterpret_cast<IOPCDataCallback*>(sp.p);
			
			if (pChan!=NULL)
				hr=pChan->OnCancelComplete(dwTransid,hGroup);
			
		}
		return hr;

	}


};

#endif // !defined(AFX_OPCDATACALLBACK_H__3D0E6422_0FB8_4B73_B147_FA2836613A8D__INCLUDED_)
