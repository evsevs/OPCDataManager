
#include "stdafx.h"
// DataPlugin
#include "DataPlugin.h"
#include "DMPluginIfs_i.c"
static const GUID CLSID_ConstDataOPCPlugin = 
{ 0x93a34f8e, 0xca92, 0x43d3, { 0x9b, 0x92, 0x51, 0xb7, 0x69, 0xcd, 0x73, 0x9c } }	; 

///////////////////////////////////////////////////////////////////////////////
// Class CPluginNotifyListener
///////////////////////////////////////////////////////////////////////////////
	STDMETHODIMP CPluginNotifyListener::OnDeviceNotAvailable()
	{
		return S_OK;
	}

	STDMETHODIMP CPluginNotifyListener::OnTagsChange(DWORD dwCount, DWORD* phClientItems, VARIANT *pvValues,WORD* pwQualities,FILETIME*  pftTimeStamps, HRESULT * pErrors)
	{
		//Формируем сообщение для уведомления
		try{
		
		_UpdateNowMsg2 * pUM = new _UpdateNowMsg2;
		pUM->phClient = NULL;
		pUM->dwCount = dwCount;
		pUM->pErrors = (HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
		pUM->pItemState =(OPCITEMSTATE*) CoTaskMemAlloc(sizeof(OPCITEMSTATE)*dwCount);

		for(UINT i=0;i<dwCount;i++)
		{
			*(pUM->pErrors+i)=*(pErrors+i);
			(pUM->pItemState+i)->hClient=*(phClientItems+i);
			(pUM->pItemState+i)->ftTimeStamp=*(pftTimeStamps+i);
			VariantInit(&((pUM->pItemState+i)->vDataValue));
			VariantCopy(&((pUM->pItemState+i)->vDataValue),(pvValues+i));
			(pUM->pItemState+i)->wQuality=*(pwQualities+i);
				
		}

			m_Owner->m_CacheNotify->Send_OnTagUpdate(pUM);
		}catch(_com_error &e)
		{
			ATLTRACE("ERROR: OnTagsChange() \n");
		}
		catch(...){

			ATLTRACE("ERROR!!! Неопознанная ошибка в методе CPluginNotifyListener::OnTagsChange \n");
		}
		return S_OK;
	}

///////////////////////////////////////////////////////////////////////////////
// Class CDataPlugin 
///////////////////////////////////////////////////////////////////////////////

	CDataPlugin::CDataPlugin(CLogFile_CS &lf) : m_ChannelPluginCLSID(GUID_NULL),
		m_Init(false),
		m_LogFile(lf)
{
	m_InitListener=false;
}


CDataPlugin::~CDataPlugin()
{
	this->DeinitializePlugin();
}

HRESULT CDataPlugin::SetNewLogForPlugin(std::string postfix)
{
	if (!m_Init) return E_FAIL;
	if (IsConstDataPlugin()) return S_OK;
	
	HRESULT hr=S_OK;
	_bstr_t full=(m_PluginLogFilePrefix+postfix).c_str();
	m_pIPluginConfig->SetFullLogFileName(full);
	return hr;
}

bool CDataPlugin::IsConstDataPlugin ()
{
	return (bool)IsEqualGUID(get_m_ChannelPluginCLSID(),CLSID_ConstDataOPCPlugin);
}

HRESULT CDataPlugin::InitializePlugin (_bstr_t bstrPluginString)
{
	//если не проинициализировали GUID - возвращаем ошибку.
	if (bstrPluginString==_bstr_t(""))
		bstrPluginString=m_bstrPluginStringX;
	else
		m_bstrPluginStringX=bstrPluginString;
	if (IsEqualGUID(m_ChannelPluginCLSID,GUID_NULL)) return E_FAIL;
	//если плагин - константных значений(без устройства) - возвр OK
	if (IsConstDataPlugin()) return S_OK;

	if (m_Init) return S_OK;//уже инициализирован
	else
	{
		HRESULT hr;
		if (SUCCEEDED(hr=DeinitializePlugin())) //пытаемся деинициалищировать
		{
			//соединяемся с плагином
			hr=CoCreateInstance(m_ChannelPluginCLSID,0,CLSCTX_ALL,IID_IPluginConfig,(void**)&m_pIPluginConfig);
			if (SUCCEEDED(hr))
			{
				_bstr_t pl=(m_PluginLogFilePrefix+m_PluginLogFilePostFix).c_str();
				m_pIPluginConfig->SetFullLogFileName(pl);
				if (SUCCEEDED(hr=m_pIPluginConfig->Configure(bstrPluginString.copy())))
				{
					m_pIPluginConfig->QueryInterface(IID_IPluginData,(void**)&m_pIPluginData);
					m_Init=true;
				}
				else
				{	m_pIPluginConfig.Release();
					DeinitializePlugin();
				}
			}
			return hr;
		}
		else
			return hr;
	}
}

HRESULT CDataPlugin::DeinitializePlugin ()
{
		if (IsConstDataPlugin()) return S_OK;
		if (!m_Init) return S_OK;
		//отписка от получения нотификаций
		HRESULT hr=DeInitListener();
		if (m_pIPluginConfig)
			m_pIPluginConfig->Reset();
		if (m_pIPluginConfig.p) m_pIPluginConfig.Release();
		if (m_pIPluginData.p) m_pIPluginData.Release();
		m_Init=false;
		return S_OK;
}

HRESULT CDataPlugin::GetTagsData (_UpdateNowMsg2* TagsNow)
{
	//защита от запроса неинициализированного плагина
		if (!m_Init) return E_FAIL;
		if (IsConstDataPlugin()) return S_OK;
		HRESULT hr=S_OK;

		try
		{
			hr = m_pIPluginData->GetTags(TagsNow->m_ItemDef/*pItemID*/,TagsNow->dwCount,&TagsNow->pItemState,&TagsNow->pErrors);
		}catch(...)
		{
			m_LogFile<<"ERROR: GetTagsData: Неизвестная ошибка, пришедшая от плагина при чтении!!!";
			hr=E_FAIL;
		}
		return hr;
}

HRESULT CDataPlugin::SetTagsData (_UpdateNowMsg* TagsData)
{
		if (!m_Init) return E_FAIL;
		if (IsConstDataPlugin()) return S_OK;
		ITEMID * pItemID = (ITEMID*)CoTaskMemAlloc(sizeof(ITEMID)*TagsData->dwCount);
		//формируем структуру
		for (ULONG i=0;i<TagsData->dwCount;i++)
		{
			(pItemID+i)->hClient = (*(TagsData->phClient+i))->get_m_hObjectHandle();
			(pItemID+i)->ItemName = _bstr_t((*(TagsData->phClient+i))->get_m_sRealName().c_str()).copy();
		}
		//посылаем запрос на данные
		HRESULT hr=S_OK;
		try{
			hr = m_pIPluginData->SetTags(pItemID,TagsData->dwCount,TagsData->pvValues,&TagsData->pErrors);
		}catch(...)
		{
			ATLTRACE("Неизвестная ошибка, пришедшая от плагина при записи!!!");
			hr=E_FAIL;
		}
		//освобождаем память под идентификаторами
	for (ULONG ii=0;ii<TagsData->dwCount;ii++)
	{
		SysFreeString((pItemID+ii)->ItemName);
	}	
	CoTaskMemFree(pItemID);
		return hr;
}

HRESULT CDataPlugin::AddTagsNotify (_TagID* phClient, DWORD Count, DWORD UpdateRate, HRESULT** pError)
{
	if (!m_Init) return S_OK;
	if (IsConstDataPlugin()) return S_OK;
	HRESULT hrx=InitListener();
	if (FAILED(hrx)) return hrx;

	ITEMID * pItemID = (ITEMID*)CoTaskMemAlloc(sizeof(ITEMID)*Count);
	//формируем структуру
	for (ULONG i=0;i<Count;i++)
	{
		(pItemID+i)->hClient = (phClient+i)->get_m_hObjectHandle();
		(pItemID+i)->ItemName = _bstr_t((phClient+i)->get_m_sRealName().c_str()).copy();
	}

	HRESULT hr=m_pIPluginConfig->AddNotifyTags(pItemID,Count,UpdateRate,pError);
	for (ULONG ii=0;ii<Count;ii++)
	{
		SysFreeString((pItemID+ii)->ItemName);
	}	
	CoTaskMemFree(pItemID);
	return hr;
}

HRESULT CDataPlugin::DelTagsNotify (_TagID* phClient, DWORD Count, HRESULT** pError)
{
	if (IsConstDataPlugin()) return S_OK;//если не с физическим плагином работает - ошибка
	ITEMID * pItemID = (ITEMID*)CoTaskMemAlloc(sizeof(ITEMID)*Count);
	//формируем структуру
	for (ULONG i=0;i<Count;i++)
	{
		(pItemID+i)->hClient = (phClient+i)->get_m_hObjectHandle();
		(pItemID+i)->ItemName = _bstr_t((phClient+i)->get_m_sObjectName().c_str()).copy();
	}

	m_pIPluginConfig->DelNotifyTags(pItemID,Count);
	for (ULONG ii=0;ii<Count;ii++)
	{
		SysFreeString((pItemID+ii)->ItemName);
	}	
	CoTaskMemFree(pItemID);

	return S_OK;
}

HRESULT CDataPlugin::GetState (WORD wState)
{
	if (!this->m_Init) return E_FAIL; //если плагин не инициализирован - ошибка.

	if (IsConstDataPlugin()) return S_OK;
//здесь помещабтся запросы к плагину непосредственно.

	return S_OK;
}

HRESULT CDataPlugin::InitListener()
{
	if (m_InitListener)
		return S_OK;
	HRESULT hr=S_OK;
	m_NotifyListener = new CComObjectNoLock<CPluginNotifyListener> ;
	m_NotifyListener->FinalConstruct();
	m_NotifyListener->AddRef();
	m_NotifyListener->m_Owner = this;//устанавливаем указатель владельца
	m_NotifyListener->m_Connected=false;
	hr=m_NotifyListener->ConnectToNotify();
	if (SUCCEEDED(hr))
		m_InitListener = true;
	else
		m_InitListener=false;
	return hr;

}

HRESULT CDataPlugin::DeInitListener()
{
	if (!m_InitListener)
		return S_OK;
	HRESULT hr = S_OK;
	if (m_NotifyListener->m_Connected)
		hr=m_NotifyListener->DisconnectFromNotify();
m_NotifyListener->Release();
	m_InitListener=false;
return hr;
}

HRESULT CPluginNotifyListener::ConnectToNotify()
{
//	IConnectionPointContainer* pICPC;
//	IConnectionPoint * pICP;
	//IPluginDataCallback * pPDC;
	HRESULT hr=S_OK;
	try{	
	IUnknown * pPDC=NULL,*pUnk=NULL;
	//pNot->FinalConstruct();	
	this->QueryInterface(IID_IUnknown,(void**)&pPDC);
	this->AddRef();
	
	if(SUCCEEDED(hr=m_Owner->m_pIPluginConfig->QueryInterface(IID_IUnknown,(void**)&pUnk)))
	{
		if(SUCCEEDED(hr=AtlAdvise(pUnk,pPDC,IID_IPluginDataCallback,&m_dwCoockie)))
		{
				m_Connected=true;
		}
		pUnk->Release();
	}
	pPDC->Release();		
	}catch(...)
	{
		ATLTRACE("ERROR!!! Неопознанная ошибка в методе CPluginNotifyListener::ConnectToNotify \n");
	}

	return hr;
}

HRESULT CPluginNotifyListener::DisconnectFromNotify()
{
	HRESULT hr=S_OK;
	IUnknown* pUnk=NULL;
	try{

	if(SUCCEEDED(hr=m_Owner->m_pIPluginConfig->QueryInterface(IID_IConnectionPointContainer,(void**)&pUnk)))
	{
		hr=AtlUnadvise(pUnk,IID_IPluginDataCallback,m_dwCoockie);
		pUnk->Release();
	}
	}catch(...)
	{
				ATLTRACE("ERROR!!! Неопознанная ошибка в методе CPluginNotifyListener::DisconnectFromNotify \n");
	}

	return hr;
}
