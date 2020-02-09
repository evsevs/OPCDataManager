// XMLPlugin.cpp : Implementation of CXMLPlugin
#include "stdafx.h"
#include "PlugInXMLOPC.h"
#include "XMLPlugin.h"
//#include "opccomn_i.c"
//#include "opcda_i.C"
//#include "spacebrowse_i.c"
#include <time.h>


#include "opccomn_i.c"
#include "opcda_i.C"
#include "spacebrowse_i.c"
#include "DMPluginIfs_i.c"
#include "opcenum_clsid.c"
//Тестовые процедуры
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////ТЕСТ КОНЕЦ/////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

ItemVector MyTestItems;
void BeginItemsFilling()
{
	MyTestItems.clear();
	for (long i=0;i<20;i++) //20 штук
	{
		PLItem * pI = new PLItem;
		MyTestItems.insert(MyTestItems.end(),pI);
		SYSTEMTIME now;
		GetSystemTime(&now);
		SystemTimeToFileTime(&now,&(pI->ftTimeStamp));//установка времени;
		pI->hServer = i+1;
		pI->hClient = 0;
		pI->ItemName = "TagNumber_";
		char s[5];
		pI->ItemName=pI->ItemName+itoa(i+1,s,10);
		pI->vDataValue = 0l;
		pI->wQuality = OPC_QUALITY_UNCERTAIN ;
	}
};
void ReleaseItemsVector()
{
	ItemVector::iterator iter;
	for (iter=MyTestItems.begin();iter!=MyTestItems.end();iter++)
	{
		delete (PLItem*) *iter;
	}
	MyTestItems.clear();
};
void MyThread::OnTimerMessage(MSG msg)
{	
	ItemVector::iterator iter;
	NotifyItemList::iterator itNot;
	bool NotFlag=false; //вообще - нотифицировать нужно?
	for (iter=MyTestItems.begin();iter!=MyTestItems.end();iter++)
	{
		((PLItem*)(*iter))->ChangeItemValue(OPC_QUALITY_GOOD,(long)rand());
		for (itNot=m_Owner->NotiItems.begin();itNot!=m_Owner->NotiItems.end();itNot++)
		{
			if ((*itNot)->ItemName==(*iter)->ItemName)
			{
				(*itNot)->NotifyNow=true;
				(*itNot)->m_it = *(*iter);
				NotFlag=true;
				break;
			}
		}
	}
//	ATLTRACE("Поменяли %d\n",(long)MyTestItems[0]->vDataValue);
	//Здесь вызываем нотификационную функцию
	if (NotFlag)
		m_Owner->NotifyTagsChange();

}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////ТЕСТ КОНЕЦ/////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*struct Params
{
	_bstr_t ParamName;
	_variant_t ParamValue;
};
*/
bool ParseInitializationString(const _bstr_t InitString,std::vector<ParametersVal> &ParamStruct)
{
	
	const char	Ex[]=";= \n\b\f\r\0";//символы для поиска
	std::string ConfStr=(char*)InitString;
	std::string::iterator ItStrF,ItStrL;
	int x,x1,x2;
	while ((x=ConfStr.find_first_not_of(Ex))>=0)
	{
		ConfStr=ConfStr.substr(x);
		//Получение названия параметра
		x1=ConfStr.find_first_of(Ex);
		ParametersVal MyVal;
		if (x1!=-1)//npos
		{
			MyVal.ParamName=ConfStr.substr(0,x1).c_str();
			ConfStr=ConfStr.substr(x1);
		}	
		else break;

		x=ConfStr.find_first_of(';');
		x2=ConfStr.find_first_of('=');
		if((x<x2)&&(x!=-1)) continue;
		//получение значения параметра
		if ((x=ConfStr.find_first_not_of(Ex))>=0)
		{
			ConfStr=ConfStr.substr(x);
			if((x1=ConfStr.find_first_of(Ex))>=0)
			{
				MyVal.ParamValue=ConfStr.substr(0,x1).c_str();
				ConfStr=ConfStr.substr(x1);
			}
			else 
				if (ConfStr.length()>0) {
					MyVal.ParamValue=ConfStr.substr(0).c_str();
					ConfStr="";
				}
					
		}
		ParamStruct.insert(ParamStruct.begin(),MyVal);
		
	}
	
 int l=ParamStruct.size();
return true;
	
	
}
/////////////////////////////////////////////////////////////////////////////
// CXMLPlugin

STDMETHODIMP CXMLPlugin::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPluginConfig,
		&IID_IPluginData,
		&IID_ISpaceBrowse
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


//DEL STDMETHODIMP CXMLPlugin::ttyty()
//DEL {
//DEL	// TODO: Add your implementation code here
//DEL 
//DEL	return S_OK;
//DEL }

STDMETHODIMP CXMLPlugin::SetFullLogFileName(BSTR LogFileName)
{
	return S_OK;
}

STDMETHODIMP CXMLPlugin::GetBrowser(IUnknown**pBrowUnk)
{
/*	ISpaceBrowse * pB;
	HRESULT hr = m_pServer->QueryInterface(IID_IOPCBrowseServerAddressSpace,(void**)&pB);
	if (FAILED(hr))
		return hr;

	CComObjectNoLock<CBrowseObj>* pBrowse=new CComObjectNoLock<CBrowseObj>;
	ATLTRACE("Вызов GetBrowser плагина\n");
	//	HRESULT hr;
	pBrowse->FinalConstruct();
	pBrowse->pBrowse.Attach(pB);
//	pBrowse->m_CurPos.m_ChannelID.set_m_hObjectHandle(get_m_hObjectHandle());
//	pBrowse->m_CurPos.m_CurrentPositionName=get_m_sObjectName();
//	pBrowse->m_CurPos.m_pCarrentChannel = this;
//	pBrowse->m_TagStorage = m_TagStorage;
//	pBrowse->m_ExternalInfo=0;
*/	return E_FAIL;
}
STDMETHODIMP CXMLPlugin::AddNotifyTags(ITEMID *ClientTagID, DWORD dwCount, DWORD dwUpdateRate, HRESULT **pError)
{
	ItemAssoc * pIA = new ItemAssoc[dwCount];
	
	//в дальнейшем требуется вставить поиск уже сущ. тегов 
	//для того, чтобы дважды они не фигурировали.
	//также добавить учет UpdateRate

	//заполним нашу структуру
	for (int i=0;i<dwCount;i++)
	{
		(pIA+i)->Fill(ClientTagID+i);
		NotiItems.insert(NotiItems.end(),pIA+i);
	}
	//теперь нужно отлавливать их изменения.

	return S_OK;
}

STDMETHODIMP CXMLPlugin::DelNotifyTags(ITEMID *ClientTagID, DWORD dwCount)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CXMLPlugin::Configure(BSTR CnfgString)
{
	// Сделать разборщик строки, Забивальщик параметров
	std::vector<ParametersVal> MyParams;
	//ParseInitializationString(CnfgString,MyParams);
	BeginItemsFilling();
	m_th.m_Owner = this;
//	for(int i=0;i<MyParams.size();i++)
//	{
//		MessageBox(NULL,(LPCSTR)(char*)(_bstr_t)MyParams[i].ParamValue,(LPCSTR)(char*)MyParams[i].ParamName,MB_OK);
//	}
	//Теперь разбираем на составляющие
/*	switch () {
	case "Частота_изменения_тегов":
		break;
	case :
		break;
	case :
		break;
	case :
		break;
	default:
	}
*/	
	//opTimer();
//	int x=SetTimer(NULL,1,1000,0);
	m_th.run();
	return S_OK;
}

STDMETHODIMP CXMLPlugin::Reset()
{
	// TODO: Add your implementation code here

	return S_OK;
}



STDMETHODIMP CXMLPlugin::GetTags(ITEMID *ClientTagID, DWORD dwCount, OPCITEMSTATE **pOutStruct, HRESULT **ppErrors)
{
	ItemVector::iterator iter;
	*pOutStruct=(OPCITEMSTATE*)CoTaskMemAlloc(sizeof(OPCITEMSTATE)*dwCount);
	*ppErrors = (HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	for(int i=0;i<dwCount;i++)
	{
		ITEMID*My=ClientTagID+i;
		for (iter=MyTestItems.begin();iter!=MyTestItems.end();iter++)
		{
			if (((PLItem*)(*iter))->ItemName==_bstr_t(My->ItemName))
				break;//нашли
		}
		if (iter!=MyTestItems.end()) //находимся не в конце
		{
			*(*ppErrors+i)=S_OK;
			((OPCITEMSTATE*)((*pOutStruct)+i))->ftTimeStamp=((PLItem*)(*iter))->ftTimeStamp;
			((OPCITEMSTATE*)((*pOutStruct)+i))->hClient=My->hClient;
			((OPCITEMSTATE*)((*pOutStruct)+i))->wQuality =((PLItem*)(*iter))->wQuality;
			VariantInit(&(((OPCITEMSTATE*)((*pOutStruct)+i))->vDataValue));
			VariantCopy(&((OPCITEMSTATE*)((*pOutStruct)+i))->vDataValue,&((PLItem*)(*iter))->vDataValue);
		}
	}
//ATLTRACE("Отдаем теги %d\n",::GetCurrentThreadId());
	return S_OK;
}

STDMETHODIMP CXMLPlugin::SetTags(ITEMID *ClientTagID, DWORD Count, VARIANT *pItemValues, HRESULT **ppErrors)
{
	// TODO: Add your implementation code here
	//Здесь просто запишем в файл
	FILE* mf;
	mf=fopen("DataDATA","a+");
	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*Count);
	for(int i=0;i<Count;i++)
	{
		std::string x=(char*)_bstr_t((ClientTagID+i)->ItemName);
		long xval=(long)_variant_t(*(pItemValues+i));
		fprintf(mf,"%s Value=%d \n",x.c_str(),xval);
		*(*ppErrors+i)=S_OK;
	}

	fclose(mf);
	return S_OK;
}

STDMETHODIMP CXMLPlugin::GetState(DWORD State)
{
	// TODO: Add your implementation code here

	return S_OK;
}


STDMETHODIMP CXMLPlugin::GetExampleCnfg(BSTR *bstrExampleCnfg)
{
	_bstr_t x = "Этим плагином строка конфигурации не используется";
	//x=CONST_STRING;
	*bstrExampleCnfg=x.copy();
	
	return S_OK;
}

HRESULT CXMLPlugin::NotifyTagsChange()
{//  [12/7/2001]
	//нужно создать и заполнить структурку.
	DWORD dwCount=0;
	NotifyItemList::iterator iter;
	for (iter=NotiItems.begin();iter!=NotiItems.end();iter++)
	{
		if ((*iter)->NotifyNow)
		{
			dwCount++;
		}
	}

	DWORD* phClientItems = (DWORD*)CoTaskMemAlloc(sizeof(DWORD)*dwCount);
	VARIANT *pvValues= (VARIANT*)CoTaskMemAlloc(sizeof(VARIANT)*dwCount);
	WORD* pwQualities= (WORD*)CoTaskMemAlloc(sizeof(WORD)*dwCount);
	FILETIME*  pftTimeStamps= (FILETIME*)CoTaskMemAlloc(sizeof(FILETIME)*dwCount);
	HRESULT * pErrors= (HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);

	//Заполняем
	int Count=0;
	for (iter=NotiItems.begin();iter!=NotiItems.end();iter++)
	{
		if ((*iter)->NotifyNow)
		{
			*(phClientItems+Count) = (*iter)->hClient;
			VariantInit(pvValues+Count);
			VariantCopy(pvValues+Count,&(*iter)->m_it.vDataValue);
			*(pwQualities+Count)=(*iter)->m_it.wQuality;
			*(pftTimeStamps+Count)=(*iter)->m_it.ftTimeStamp;
			*(pErrors+Count)=S_OK;
			Count++;
			if (Count==dwCount) break;
		}

	}
	Fire_OnTagsChange(dwCount,phClientItems,pvValues,pwQualities,pftTimeStamps,pErrors);
	//Освобождение памяти
	CoTaskMemFree(phClientItems);
	for (int i=0;i<dwCount;i++)
	{
		VariantClear(pvValues+i);
	}
	CoTaskMemFree(pvValues);
	CoTaskMemFree(pwQualities);
	CoTaskMemFree(pftTimeStamps);
	CoTaskMemFree(pErrors);


//	Fire_OnDeviceNotAvailable();
	return S_OK;
}



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
	STDMETHODIMP CBrowseObj::BrowseAccessPaths(/*[in]*/LPCWSTR szItemID,/*[out]*/ LPENUMSTRING *ppIEnumString)
	{
		return S_OK;
	}
	STDMETHODIMP CBrowseObj::GetItemID(/*[in]*/LPCWSTR szItemDataID, /*[out]*/LPWSTR *szItemID)
	{
/*		USES_CONVERSION;
		ATLTRACE("Вызов ISpaceBrowse::GetItemID, канала %d\n",m_CurPos.m_pCarrentChannel->get_m_hObjectHandle());
		if (szItemID==NULL)
			return E_POINTER;
		std::string str = (m_CurPos.m_CurrentPositionName+".")+W2A(szItemDataID);
		*szItemID=(LPWSTR)CoTaskMemAlloc(sizeof(wchar_t)*(str.size()+1));
		wcscpy(*szItemID,A2W(str.c_str()));
*/		return S_OK;

	}
	STDMETHODIMP CBrowseObj::BrowseOPCItemIDs(/*[in]*/ OPCBROWSETYPE  dwBrowseFilterType,/*[in]*/ LPCWSTR  szFilterCriteria, /*[in]*/ VARTYPE   vtDataTypeFilter, /*[in]*/ DWORD    dwAccessRightsFilter,	/*[out]*/ LPENUMSTRING	* ppIEnumString)
	{
/*		ATLTRACE("Вызов ISpaceBrowse::BrowseOPCItemIDs, канала %d\n",m_CurPos.m_pCarrentChannel->get_m_hObjectHandle());

		if (ppIEnumString == NULL)
			return E_POINTER;
		std::vector<LPOLESTR> strvec;
		std::map<_TagID,CTag*>::iterator itm;

		LPOLESTR olestr=NULL;
		typedef CComObjectNoLock<CComEnum<IEnumString,&IID_IEnumString,LPOLESTR,_Copy<LPOLESTR> > > Enum;
		Enum * p = new Enum;
		HRESULT hr;
		std::string xx;
	USES_CONVERSION;
		switch(dwBrowseFilterType)
		{
		case OPC_BRANCH:
				for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
				{
					int pos = -1;
					if ((pos=itm->second->get_m_sObjectName().find(m_CurPos.m_CurrentPositionName))!=-1)
					{
						if (itm->second->get_m_sObjectName().size()>m_CurPos.m_CurrentPositionName.size())//это branch?
							if (itm->second->get_m_sObjectName().at(pos+m_CurPos.m_CurrentPositionName.size())=='.')//проверка на точку
							{
								xx=itm->second->get_m_sObjectName().substr(m_CurPos.m_CurrentPositionName.size()+1);
								if ((pos=xx.find("."))!=-1)
								{
*//*Как выделить Бранчи?*//*			xx.replace(pos,xx.size()-pos,"");
									bool Is=false;
									for(int xyz=0;xyz!=strvec.size();xyz++)
										if (xx==W2A(strvec[0]))
										{
											Is=true;
											break;
										}

									if (Is) continue;
									long s;
									olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((s=xx.size()+1)));
									wcscpy(olestr,A2W(xx.c_str()));
									strvec.insert(strvec.end(),olestr);
								}
							}
					}
				}
				//формируем интерфейс
				if (p==NULL) hr= E_OUTOFMEMORY;
				else
				{
					hr=p->FinalConstruct();
					if (hr==S_OK)
					{
						hr=p->Init(&strvec[0],&strvec[strvec.size()],NULL,AtlFlagCopy);
						if (hr==S_OK)
						{
							hr=p->QueryInterface(IID_IUnknown,(void**)ppIEnumString);
						}
					}
				}
				if (hr!=S_OK)
					delete p;
				if ((strvec.size()==0)&&SUCCEEDED(hr)) hr= S_FALSE;

				return hr;
			break;
		case OPC_LEAF:
				for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
				{
					int pos = -1;
					if ((pos=itm->second->get_m_sObjectName().find(m_CurPos.m_CurrentPositionName))!=-1)
					{
						if (itm->second->get_m_sObjectName().size()>m_CurPos.m_CurrentPositionName.size())//это branch?
							if (itm->second->get_m_sObjectName().at(pos+m_CurPos.m_CurrentPositionName.size())=='.')//проверка на точку
							{
								xx=itm->second->get_m_sObjectName().substr(m_CurPos.m_CurrentPositionName.size()+1);
								if ((pos=xx.find("."))==-1)
								{
			
									long s;
									olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((s=xx.size()+1)));
									wcscpy(olestr,A2W(xx.c_str()));
									strvec.insert(strvec.end(),olestr);
								}
							}
					}
				}
				//формируем интерфейс
				if (p==NULL) hr= E_OUTOFMEMORY;
				else
				{
					hr=p->FinalConstruct();
					if (hr==S_OK)
					{
						hr=p->Init(&strvec[0],&strvec[strvec.size()],NULL,AtlFlagCopy);
						if (hr==S_OK)
						{
							hr=p->QueryInterface(IID_IUnknown,(void**)ppIEnumString);
						}
					}
				}
				if (hr!=S_OK)
					delete p;
				if ((strvec.size()==0)&&SUCCEEDED(hr)) hr= S_FALSE;


				return hr;
			break;
		case OPC_FLAT:
			break;
		default:
			return E_INVALIDARG;
		}*/
		return S_OK;
	}
	STDMETHODIMP CBrowseObj::ChangeBrowsePosition(/*[in]*/ OPCBROWSEDIRECTION dwBrowseDirection,/*[in]*/ LPCWSTR  szString)
	{
/*		ATLTRACE("Вызов ISpaceBrowse::ChangeBrowsePosition, канала %d\n",m_CurPos.m_pCarrentChannel->get_m_hObjectHandle());
		USES_CONVERSION;
		std::string str,curstr;
		std::map<_TagID,CTag*>::iterator itm;

		if (szString)
		{
			str = W2A(szString);
			curstr=m_CurPos.m_CurrentPositionName+"."+str;

		}
		else str="";
		int pos=-1;
		switch(dwBrowseDirection)
		{
		case OPC_BROWSE_UP:
			//szString - ignore
			if (m_CurPos.m_CurrentPositionName==m_CurPos.m_pCarrentChannel->get_m_sObjectName()) return E_FAIL;
			if ((pos=m_CurPos.m_CurrentPositionName.rfind("."))!=-1)
				m_CurPos.m_CurrentPositionName.replace(pos,m_CurPos.m_CurrentPositionName.size()-pos,"");
				return S_OK;
			break;
		case OPC_BROWSE_DOWN:
			//szString - куда?
			if (str=="") return E_FAIL;
			for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
			{
				std::string x=itm->second->get_m_sObjectName();
				int posx=-1;
				if ((posx=x.find(curstr))!=-1)//есть такое?
					if (x.size()>curstr.size())//это branch?
						if (x.at(posx+curstr.size())=='.')
						{
							m_CurPos.m_CurrentPositionName = curstr;
							return S_OK;
						}
			}
			return E_FAIL;
			break;
		case OPC_BROWSE_TO:
			if (str=="") 
			{
				m_CurPos.m_CurrentPositionName = m_CurPos.m_pCarrentChannel->get_m_sObjectName();
				return S_OK;
			}
			for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
			{
				std::string x=itm->second->get_m_sObjectName();
				int posx=-1;
				if ((posx=x.find(str))!=-1)//есть такое?
					if (x.size()>str.size())//это branch?
						if (x.at(posx+str.size())=='.')//проверка на точку
						{
							m_CurPos.m_CurrentPositionName = str;
							return S_OK;
						}
			}
			return E_FAIL;

			break;
		default:
			return E_INVALIDARG;
		}*/

	return S_OK;
	}
	STDMETHODIMP CBrowseObj::QueryAvailableProperties(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR **ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes)
	{//доступные свойства итемов
/*		PropMap::const_iterator itm;
		int cf=MyMap.size();
		*ppPropertyIDs = (DWORD*)CoTaskMemAlloc(MyMap.size()*sizeof(DWORD));	
		*ppDescriptions = (BSTR*)CoTaskMemAlloc(MyMap.size()*sizeof(BSTR));
		*pdwCount=0;
		for(itm=MyMap.begin();itm!=MyMap.end();++itm)
		{
			*(*ppPropertyIDs+(*pdwCount))=itm->first;
			_bstr_t t=itm->second.c_str();
			*(*ppDescriptions+(*pdwCount))=t.copy();
			(*pdwCount)++;
		}*/
		return S_OK;
	}
	STDMETHODIMP CBrowseObj::GetItemProperties(/*[in]*/ BSTR ItemID,/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ DWORD * pdwPropertyIDs,/*[out, size_is(,dwCount)] */VARIANT ** ppvData,/*[out, size_is(,dwCount)]*/ HRESULT **ppErrors)
	{
/*		//поиск тега и запрос на проперти
		USES_CONVERSION;
		std::map<_TagID,CTag*>::iterator itm;
		// только проход по всем тегам
		for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
			if (itm->second->get_m_sObjectName()==W2A(ItemID))
				return itm->second->GetProperties(dwCount,pdwPropertyIDs,ppvData,ppErrors);

*/		return /*OPC_E_UNKNOWNITEMID*/S_OK;
	}


STDMETHODIMP CBrowseObj::ValidateItem(DWORD dwCount, OPCITEMDEF *pItemArray, BOOL bBlobUpdate, OPCITEMRESULT **ppValidationResults, HRESULT **ppErrors)
{
/*	USES_CONVERSION;
	if (dwCount==0)
	{
		return S_OK;
	}
	//по всему массиву
	std::map<_TagID,CTag*>::iterator itm;
	*ppValidationResults=(OPCITEMRESULT*)CoTaskMemAlloc(sizeof(OPCITEMRESULT)*dwCount);
	for(long lo=0;lo<dwCount;lo++)
		(*ppValidationResults+lo)->pBlob = NULL;
	
	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	bool FlagIsAny=false,FlagNotAll=false;
	for(long i=0;i<dwCount;i++)
	{
		*(*ppErrors+i)=OPC_E_UNKNOWNITEMID;
		for (itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
		{	//if (pItemArray)
			if (itm->second->get_m_sObjectName()==W2A((pItemArray+i)->szItemID))
			{
				*(*ppErrors+i)=itm->second->get_pOPCITEMRESULT((*ppValidationResults)+i,(pItemArray+i)->vtRequestedDataType);
				if(*(*ppErrors+i)!=S_OK) break;
				FlagIsAny=true;
				break;
			}
		}
		if (itm==m_TagStorage->TMap.end()) FlagNotAll=true;
		
	}
	if (FlagIsAny&&(!FlagNotAll)) return S_OK;
	if (FlagNotAll&&FlagIsAny) return S_FALSE;
	if (FlagNotAll&&(!FlagIsAny)) return S_FALSE;
	
	CoTaskMemFree(*ppValidationResults);
	CoTaskMemFree(*ppErrors);*/
	return S_OK;
}

