// CChannelObj.cpp : Implementation of CCChannelObj
#include "stdafx.h"
#include "OPCDMSvc_h.h"
#include "CChannelObj.h"
#include "spacebrowse_i.c"
#include <lm.h>
#include <lmerr.h>
//filter
#include "FilterString.h"
#include <algorithm>
#include <atlstr.h>
/////////////////////////////////////////////////////////////////////////////
// CCChannelObj
STDMETHODIMP CCChannelObj::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ICChannelObj
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

DWORD CCChannelObj::GetItemCount ()
{
	DWORD ret;
		m_AddTagCS.Lock();
		ret=m_TagStorage->TMap.size();
		m_AddTagCS.Unlock();
	return ret;
}

HRESULT CCChannelObj::GetChannelStatus (FILETIME& ftLastUpdateTime, DWORD& dwBandWidth)
{
	ftLastUpdateTime = m_ftLastUpdateTime;
	dwBandWidth = m_dwBandWidth;
	return S_OK;
}

DWORD CCChannelObj::fbody ()
{
	ATLTRACE("�������� ����� ID=%d Handle=%d ������ = %s\n",this->get_m_ThreadID(),this->get_m_ThreadHandle(),this->get_m_sObjectName().c_str());
	CoInitializeEx(NULL,COINIT_MULTITHREADED);//�������� � MTA

	Initialize("","");

	MSG msg;
   ::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE) ;
	while(GetMessage(&msg,0,0,0))
	{
	   ::DispatchMessage(&msg);
	   switch(msg.message)
	   {
	   case WM_CHANNEL_STOP:
		   StopChannelHandler();
		   break;
	   case WM_CHANNEL_START:
		   StartChannelHandler();
		   break;
	   case WM_OPC_SYNCREAD:
		   OnSyncRead((_SyncIORMsg*)msg.lParam);
		   break;
	   case WM_OPC_ASYNCREAD:
		   OnAsyncRead((_AsyncIORWMsg*)msg.lParam);
		   break;
	   case WM_OPC_SYNCWRITE:
		   OnSyncWrite((_SyncIORMsg*)msg.lParam);
		   break;
	   case WM_OPC_ASYNCWRITE:
		   OnAsyncWrite((_AsyncIORWMsg*)msg.lParam);
		   break;
	   case WM_TAGSUPDATED:
		   OnTagsUpdated(msg);
		   break;
	   }
	 }
	CoUninitialize();
	return 0;
}

void CCChannelObj::OnTagsUpdated (MSG msg)
{
	_UpdateMsg * pUM= (_UpdateMsg*)msg.lParam;
	delete pUM;
}

void CCChannelObj::TagsUpdated (_UpdateNowMsg UpdateNowMsg)
{
}

void CCChannelObj::Send_OnTagUpdate (_UpdateMsg* pUpdateMsg)
{
	//����� ����������� ���������� � ������� ��������� ������
	//���������� ��������� � ����������� � ������� ��������� ������
	PostThreadMessage(get_m_ThreadID(),WM_TAGSUPDATED,0,(long)pUpdateMsg);
}

HRESULT CCChannelObj::Initialize (_bstr_t bstrChannelString, _bstr_t bstrPluginString)
{
//	CoInitializeEx(NULL,COINIT_MULTITHREADED);
	if (m_Init)
	{
		SetEvent(m_hInitEvent);
		return S_OK;
	}
	
	//����� ����� �������� ��� ��� ���-�����
	bool ErrorFlag=false;
	try{//�� ��� ������������� �� XML


		//���������
		char buf[500];
		sprintf(buf,"%s_%d","�����_��_���������������_ID",this->get_m_hObjectHandle());
		this->set_m_sObjectName(buf);
		sprintf(buf,"%s","�� ��������� ������ ������������!");
		this->m_bstrChannelString=buf;
		//���������� �����c
		SYSTEMTIME d;
		GetLocalTime(&d);
		SystemTimeToFileTime(&d,&this->m_CreateTime);	
		this->m_ChannelMode=(_ChannelMode)2;
		this->m_ClockRate=50;
	//	this->m_DeviceUpdateMode=1;
		sprintf(buf,"%s","�� ����������� �������� ��� ������!");
		this->m_Description = buf;


		if (this->m_ChannelCnfgNode==NULL)
			_com_issue_error(E_FAIL);


		try{ //�� ��������� ���������� ������ ������
			MSXML2::IXMLDOMNamedNodeMapPtr Attributes = this->m_ChannelCnfgNode->attributes;
			if (Attributes==NULL) 
				_com_issue_error(E_FAIL);
			MSXML2::IXMLDOMNodePtr node;

			//-----------------
			//�������� ������
			node=Attributes->getNamedItem("ChannelName");
			if (node!=NULL)
			{
				this->set_m_sObjectName((char*)(_bstr_t(node->nodeValue)));
				node.Release();	
			}else
				ErrorFlag=true;

			//-----------------
			//������ ������������ ������
			node=Attributes->getNamedItem("CnfgString");
			if (node!=NULL)
			{
				this->m_bstrChannelString=node->nodeValue;
				node.Release();
			}else
				ErrorFlag=true;
		
			//-----------------			
			//����� �������� ������
			try{
			variant_t crtime="";
			node=Attributes->getNamedItem("CreateTime");
			if (node!=NULL)
			{
				crtime=node->nodeValue;
				node.Release();
			}
			SYSTEMTIME d;
			if (VariantTimeToSystemTime(crtime,&d))
			{
				SystemTimeToFileTime(&d,&this->m_CreateTime);	
			}
			}catch(...)
			{
			}

			//-----------------
			//����� ������
			node=Attributes->getNamedItem("ChannelMode");
			if (node!=NULL)
			{
				this->m_ChannelMode=(_ChannelMode)(long)node->nodeValue;
				node.Release();	
			}else
				ErrorFlag=true;			

			//-----------------
			//������ ���������� ������ ������
			node=Attributes->getNamedItem("ClockRate");
			if (node!=NULL)
			{
				this->m_ClockRate=(unsigned long)node->nodeValue;
				node.Release();	
			}else
				ErrorFlag=true;

			//-----------------
			//����� ���������� ������ � ���������� - �� ������������ � �� �����!
		//	this->m_DeviceUpdateMode=1;

			//-----------------
			//�������� ������
			node=Attributes->getNamedItem("Description");
			if (node!=NULL)
			{
				this->m_Description=(char*)_bstr_t(node->nodeValue);
				node.Release();	
			}else
				ErrorFlag=true;

		//�� ������������� ���������� ������ ������
		}catch(_com_error &e)
		{
			ErrorFlag=true;
		}
		catch(...)
		{
			ErrorFlag=true;
		}

		PhysicalCreatePath(m_ConfigLogPath+"\\Channels\\"+get_m_sObjectName()+"\\Plugin");
		m_LogFile.SetNewLogFile(get_m_sObjectName(),m_ConfigLogPath+"\\Channels\\"+get_m_sObjectName());
		m_LogFile.GenerateLogFile(true,true);
		char b[300];
		ATLTRACE("������������� ������  ID=%d Name=%s ",get_m_hObjectHandle(),get_m_sObjectName().c_str());
		m_LogFile<<"\n==============================================";
		sprintf(b,"������������� ������  ID=%d Name=%s ",get_m_hObjectHandle(),get_m_sObjectName().c_str());
		m_LogFile<<b;


		try{//�� ������������� �������
			//���������
			if (!m_Plagin) m_Plagin = new CDataPlugin(m_LogFile);
				m_Plagin->m_PluginLogFilePrefix = m_ConfigLogPath+"\\Channels\\"+get_m_sObjectName()+"\\Plugin\\";
				m_Plagin->m_PluginLogFilePrefix+=get_m_sObjectName()+"Plugin";
				m_Plagin->m_PluginLogFilePostFix = m_LogFile.GetPostfix()+".log";

			m_Plagin->set_m_ProgID("NotFound!");
			m_Plagin->m_bstrPluginStringX=this->m_bstrPluginString = "NotFound!;";


			MSXML2::IXMLDOMNamedNodeMapPtr Attributes = this->m_ChannelCnfgNode->attributes;
			if (Attributes==NULL) 
				_com_issue_error(E_FAIL);

			MSXML2::IXMLDOMNodePtr node;

			//-----------------
			//ProgID �������
			node=Attributes->getNamedItem("PluginProgID");
			if (node!=NULL)
			{
				m_Plagin->set_m_ProgID(_bstr_t(node->nodeValue));
				node.Release();	
			}
			
			//-----------------
			//������ ������������ �������
			node=Attributes->getNamedItem("PluginCnfgString");
			if (node!=NULL)
			{
				m_Plagin->m_bstrPluginStringX=this->m_bstrPluginString=_bstr_t(node->nodeValue);
				node.Release();	
			}
		//�� ������������� �������
		}catch(_com_error &e)
		{
		}
		catch(...)
		{
		}
		
		//������������� ����� ������
		if (m_TagStorage==NULL) m_TagStorage = new CTagStorage;
		if (!ErrorFlag)//���� ����������� � ����������� - �� ����� ��������� ����
		{
			this->InitializeTagFromXML();
		}
    //�� ��� ������������� �� XML
	}catch(_com_error &e)
	{
	}
	catch(...)
	{
	}

	m_Init = true;
	
	//������� ���������� ����
	if (!m_Cache) m_Cache = new CCacheUpdateHandler(m_LogFile); 
	m_Cache->set_m_TagStorage(m_TagStorage);
	m_Cache->set_m_ClockRate(m_ClockRate);
	m_Cache->set_m_ChannelNotify((CLocalNotify*)this);	
	m_Cache->set_m_Device(m_Plagin);
	m_Cache->Stop();

	if((m_ChannelMode==chmEnabled)&&(GlobalServerState==OPC_STATUS_RUNNING))
	{
		m_LogFile<<"�������� ���������� ���� ������ (CacheHandler)";
		m_Cache->run();
	}
	m_LogFile<<"������������� ������ ���������";
	if (this->m_ChannelCnfgNode)
		this->m_ChannelCnfgNode.Release();
	SetEvent(m_hInitEvent);
	return S_OK;
}
// ������������� ����� �� XML
int CCChannelObj::InitializeTagFromXML(void)
{
	try{
		FILETIME ft;
		GetSystemTimeAsFileTime(&ft);
		
		srand(ft.dwLowDateTime);

		MSXML2::IXMLDOMNodeListPtr NodeList = this->m_ChannelCnfgNode->childNodes;
		if (NodeList==NULL)
			_com_issue_error(E_FAIL);
		for(long i=0;i<NodeList->length;i++)
		{
			try{
			//������� ���
				CTag * pTag=new CTag();
			//���������
				pTag->GenerateNewID(this);
				pTag->set_m_AccessRights(OPC_READABLE);
				char buf[500];
				sprintf(buf,"%s_%d","���_��_���������������_ID",pTag->get_m_hObjectHandle());
				pTag->set_m_sObjectName(buf);				
				pTag->m_sRealName=buf;
				pTag->set_m_UpdateRate(10);
				pTag->set_m_vtCanonicalDataType(VT_EMPTY);
				pTag->set_m_Active(1);
				pTag->m_UpdateFromNotify=false;
				sprintf(buf,"%s","�� ����������� �������� ��� ����!");
				pTag->m_Description=buf;

			//���������� ���������� �� XML
				MSXML2::IXMLDOMNamedNodeMapPtr Attributes = NodeList->item[i]->attributes;
				if (Attributes==NULL) 
					_com_issue_error(E_FAIL);
				MSXML2::IXMLDOMNodePtr node;

				//-----------------
				//�������� ����
				node=Attributes->getNamedItem("TagName");
				if (node!=NULL)
				{
					pTag->set_m_sObjectName(this->get_m_sObjectName()+"."+(char*)(_bstr_t(node->nodeValue)));
					node.Release();	
				}

				//-----------------
				//�������� ���� � ����������AccessRights
				node=Attributes->getNamedItem("RealName");
				if (node!=NULL)
				{
					pTag->m_sRealName=_bstr_t(node->nodeValue);
					node.Release();
				}

				//-----------------
				//����� ������� � ���� ��������
				node=Attributes->getNamedItem("AccessRights");
				if (node!=NULL)
				{
					pTag->set_m_AccessRights((long)node->nodeValue);
					node.Release();
				}

				//-----------------
				//������������� ��� ������ (OPC �������)
				node=Attributes->getNamedItem("CanonicalDataType");
				if (node!=NULL)
				{
					pTag->set_m_vtCanonicalDataType((VARTYPE)(long)node->nodeValue);
					node.Release();
				}

				//-----------------
				//���������� ����
				node=Attributes->getNamedItem("Active");
				if (node!=NULL)
				{
					pTag->set_m_Active((long)node->nodeValue);
					node.Release();
				}

				//-----------------
				//���������� �� �����������
				node=Attributes->getNamedItem("NotifyUpdate");
				if (node!=NULL)
				{
					pTag->m_UpdateFromNotify=(bool)(long)node->nodeValue;
					node.Release();
				}

				//-----------------
				//���������� �� �����������
				node=Attributes->getNamedItem("Description");
				if (node!=NULL)
				{
					pTag->m_Description=_bstr_t(node->nodeValue);
					node.Release();
				}

			//���������� � ����� ����������� (���� �����)
				if (pTag->m_UpdateFromNotify && pTag->get_m_Active())
				{	
					//������� � ������
					_TagID tid=(_TagID)(*pTag);
					m_TagStorage->m_NotifyTagList.insert(m_TagStorage->m_NotifyTagList.end(),tid);
				}

			//���������� � ����� �����
				sprintf(buf,"TagID = %d Name = %s",pTag->get_m_hObjectHandle(),pTag->get_m_sObjectName().c_str());
				m_LogFile<<buf;
				_TAGMAP::iterator itm;
NewGenerateHandle:	if ((itm=m_TagStorage->TMap.find(pTag->get_m_hObjectHandle()))==m_TagStorage->TMap.end())
				{
					m_TagStorage->TMap.insert(_TAGMAP::value_type(pTag->get_m_hObjectHandle(),pTag));
					//wchar_t * mystr=static_cast<wchar_t*>(CoTaskMemAlloc(sizeof(wchar_t)*(pTag->get_m_sObjectName().length()+1)));
					//memcpy(mystr,
					//CStringW wName=pTag->get_m_sObjectName().c_str();
                    m_TagStorage->m_NameHandleTagMap.insert(_TAGMAP_NAME_HANDLE::value_type(pTag->get_m_sObjectName(),pTag->get_m_hObjectHandle()));
				}
				else
				{
				//	m_LogFile <<"��� ����!!!";
						pTag->GenerateNewID(this);
						goto NewGenerateHandle;
				}

			}catch(_com_error &e)
			{
				m_LogFile<<"������ ��� ������������� ����";
			}
			catch(...)
			{
				m_LogFile<<"����������� ������ ��� ������������� ����";
			}
		}
	
	}
	catch(_com_error &e)
	{
		m_LogFile<<"������ ��� ������������� �����";
	}
	catch(...)
	{
		m_LogFile<<"����������� ������ ��� ������������� �����";
	}
	return 0;
}

bool CCChannelObj::Uninitialize ()
{
	if (!m_Init) return true;
	char b[300];
ATLTRACE("��������������� ������  ID=%d Name=%s \n",get_m_hObjectHandle(),get_m_sObjectName().c_str());
	m_LogFile.ChangeMode();
	m_LogFile<<"\n";
	m_LogFile.ChangeMode();
	m_LogFile<<"================================";
	sprintf(b,"��������������� ������  ID=%d Name=%s",get_m_hObjectHandle(),get_m_sObjectName().c_str());
	m_LogFile<<b;
	m_LogFile.ChangeMode();
	m_Init=false;
//	Sleep(10000);
	if (m_Cache)
	{
		m_LogFile<<"������������� ���������� ����";
		m_Cache->Stop();
		
	}

	//if (m_Device) 
	//{
	//	m_LogFile<<"������������� ���������� ����������";
	//	m_Device->Stop();
	//}

//	if(m_Plagin) 
//	{
//		m_LogFile<<"���������������� ������";
//		m_Plagin->DeinitializePlugin();
//	}
	

	_TAGMAP::iterator it;
	for(it=m_TagStorage->TMap.begin();it!=m_TagStorage->TMap.end();++it)
	{

		delete (CTag*)it->second;
	}

	m_TagStorage->TMap.clear();
m_LogFile.ChangeMode();
	delete m_Cache;
	//delete m_Device;
	delete m_Plagin;
	delete m_TagStorage;
	m_LogFile<<"��������������� ������ ���������";
	return true;
}

STDMETHODIMP CCChannelObj::get_ClockRate(DWORD *pVal)
{
	if (!pVal)
		return E_POINTER;
	//Lock();
		*pVal=m_ClockRate;
	//Unlock();
	return S_OK;
}

STDMETHODIMP CCChannelObj::put_ClockRate(DWORD newVal)
{
	// TODO: ����� �� ������ �������� �������� ���������� - �� � �������� ������� ������
	if (GlobalServerState==OPC_STATUS_RUNNING)
		return OPC_E_RUNNING;
	m_ClockRate = newVal;
	m_Cache->set_m_ClockRate(m_ClockRate);
	return S_OK;
}

STDMETHODIMP CCChannelObj::get_CreationTime(FILETIME *pVal)
{
	*pVal=this->m_CreateTime;

	return S_OK;
}


//STDMETHODIMP CCChannelObj::get_DeviceUpdateMode( BOOL *pVal)
//{
//	
//	//*pVal = this->m_DeviceUpdateMode;
//
//	return S_OK;
//}
//
//STDMETHODIMP CCChannelObj::put_DeviceUpdateMode(BOOL newVal)
//{
//	// TODO: ���� �������������� �� �����
//	if (GlobalServerState==OPC_STATUS_RUNNING)
//		return OPC_E_RUNNING;
//	//m_DeviceUpdateMode=newVal;
//	return S_OK;
//}

STDMETHODIMP CCChannelObj::GetBrowser(IUnknown **pChannelBrowse)
{
	CComObjectNoLock<CChannelBrowseObj>* pBrowse=new CComObjectNoLock<CChannelBrowseObj>;
ATLTRACE("����� GetBrowser\n");
//	HRESULT hr;
	pBrowse->FinalConstruct();
	pBrowse->m_CurPos.m_ChannelID.set_m_hObjectHandle(get_m_hObjectHandle());
	pBrowse->m_CurPos.m_CurrentPositionName=get_m_sObjectName();
	pBrowse->m_CurPos.m_pCarrentChannel = this;
	pBrowse->m_TagStorage = m_TagStorage;
//	pBrowse->m_ExternalInfo=0;

	
	return pBrowse->QueryInterface(IID_ISpaceBrowse,(void**)pChannelBrowse);
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
	STDMETHODIMP CChannelBrowseObj::BrowseAccessPaths(/*[in]*/LPCWSTR szItemID,/*[out]*/ LPENUMSTRING *ppIEnumString)
	{
		return S_OK;
	}
	STDMETHODIMP CChannelBrowseObj::GetItemID(/*[in]*/LPCWSTR szItemDataID, /*[out]*/LPWSTR *szItemID)
	{
		USES_CONVERSION;
		ATLTRACE("����� ISpaceBrowse::GetItemID, ������ %d\n",m_CurPos.m_pCarrentChannel->get_m_hObjectHandle());
		if (szItemID==NULL)
			return E_POINTER;
		std::string str = (m_CurPos.m_CurrentPositionName+".")+W2A(szItemDataID);
		*szItemID=(LPWSTR)CoTaskMemAlloc(sizeof(wchar_t)*(str.size()+1));
		wcscpy(*szItemID,A2W(str.c_str()));
		return S_OK;

	}
	STDMETHODIMP CChannelBrowseObj::BrowseOPCItemIDs(/*[in]*/ OPCBROWSETYPE  dwBrowseFilterType,/*[in]*/ LPCWSTR  szFilterCriteria, /*[in]*/ VARTYPE   vtDataTypeFilter, /*[in]*/ DWORD    dwAccessRightsFilter,	/*[out]*/ LPENUMSTRING	* ppIEnumString)
	{

		// TODO: ���������� �� ������ ������ ��� IEnumString (����������� ���������� �� OLESTR)
		// TODO: ����� ������� ������
		ATLTRACE("����� ISpaceBrowse::BrowseOPCItemIDs, ������ %d\n",m_CurPos.m_pCarrentChannel->get_m_hObjectHandle());

		if (ppIEnumString == NULL)
			return E_POINTER;
		std::vector<LPOLESTR> strvec;
		_TAGMAP::iterator itm;

		LPOLESTR olestr=NULL;
		typedef CComObjectNoLock<CComEnum<IEnumString,&IID_IEnumString,LPOLESTR,_Copy<LPOLESTR> > > Enum;
		Enum * p = new Enum;
		HRESULT hr;
		std::string xx;
	USES_CONVERSION;
		//�������� ��������� �������
	CFilterString FilterS;
	LPCSTR szFilterName = W2A(szFilterCriteria);
		switch(dwBrowseFilterType)
		{
		case OPC_BRANCH:
				for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
				{
					int pos = -1;
					if ((pos=itm->second->get_m_sObjectName().find(m_CurPos.m_CurrentPositionName))!=-1)
					{
						if (itm->second->get_m_sObjectName().size()>m_CurPos.m_CurrentPositionName.size())//��� branch?
							if (itm->second->get_m_sObjectName().at(pos+m_CurPos.m_CurrentPositionName.size())=='.')//�������� �� �����
							{
								xx=itm->second->get_m_sObjectName().substr(m_CurPos.m_CurrentPositionName.size()+1);
								if ((pos=xx.find("."))!=-1)
								{
/*��� �������� ������?*/			xx.replace(pos,xx.size()-pos,"");
									bool Is=false;
									for(int xyz=0;xyz!=strvec.size();xyz++)
										if (xx==W2A(strvec[xyz]))
										{
											Is=true;
											break;
										}

									if (Is) continue;
									//���� ������� ���������� (�� ����� �������� �������� �� �������)
									if (FALSE==FilterS.MatchPattern(xx.c_str(),szFilterName,FALSE))
									{
										continue;//��������
									}
									
									long s;
									olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((s=xx.size()+1)));
									wcscpy(olestr,A2W(xx.c_str()));
									strvec.insert(strvec.end(),olestr);
								}
							}
					}
				}
				//��������� ���������
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
					//	if (strvec.size()!=0)
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
				if ((strvec.size()==0)&&SUCCEEDED(hr)) hr= S_FALSE;

				
				return hr;
			break;
		case OPC_LEAF:
				for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
				{
					int pos = -1;
					if ((pos=itm->second->get_m_sObjectName().find(m_CurPos.m_CurrentPositionName))!=-1)
					{
						if (itm->second->get_m_sObjectName().size()>m_CurPos.m_CurrentPositionName.size())//��� branch?
							if (itm->second->get_m_sObjectName().at(pos+m_CurPos.m_CurrentPositionName.size())=='.')//�������� �� �����
							{
								xx=itm->second->get_m_sObjectName().substr(m_CurPos.m_CurrentPositionName.size()+1);
								if ((pos=xx.find("."))==-1)
								{
									//������ �� �����			
									if (FALSE==FilterS.MatchPattern(xx.c_str(),szFilterName,FALSE))
									{
										continue;//��������
									}
									//������ �� ����
									if (FALSE==FilterS.MatchType(vtDataTypeFilter,itm->second->get_m_vtCanonicalDataType()))
									{
										continue;//��������
									}
									//������ �� ������ �������
									if (FALSE==FilterS.MatchAccessRights(dwAccessRightsFilter,itm->second->get_m_AccessRights()))
									{
										continue;//��������
									}
									long s;
									olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((s=xx.size()+1)));
									wcscpy(olestr,A2W(xx.c_str()));
									strvec.insert(strvec.end(),olestr);
								}
							}
					}
				}
				//��������� ���������
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
				if ((strvec.size()==0)&&SUCCEEDED(hr)) hr= S_FALSE;


				return hr;
			break;
		case OPC_FLAT://���������� ���, ��� �����
			{
				//������� �� ���� ����� � ������
				for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
				{
					//������ �� �����		
					if (FALSE==FilterS.MatchPattern(itm->second->get_m_sObjectName().c_str(),szFilterName,FALSE))
					{
						continue;//��������
					}
					//������ �� ����
					if (FALSE==FilterS.MatchType(vtDataTypeFilter,itm->second->get_m_vtCanonicalDataType()))
					{
						continue;//��������
					}
					//������ �� ������ �������
					if (FALSE==FilterS.MatchAccessRights(dwAccessRightsFilter,itm->second->get_m_AccessRights()))
					{
						continue;//��������
					}

					long s;
					olestr=(LPOLESTR)CoTaskMemAlloc(sizeof(OLECHAR)*((s=itm->second->get_m_sObjectName().size()+1)));
					wcscpy(olestr,A2W(itm->second->get_m_sObjectName().c_str()));
					strvec.insert(strvec.end(),olestr);
				}
				//��������� ���������
				if (p==NULL) hr= E_OUTOFMEMORY;
				else
				{
					hr=p->FinalConstruct();
					if (hr==S_OK)
					{	LPOLESTR *mas = new LPOLESTR[strvec.size()];
						for (int i=0;i<strvec.size();i++)
						{
							mas[i]=strvec[i];
						}

						hr=p->Init(mas,mas+strvec.size(),NULL,AtlFlagCopy);
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

			}
			break;
		default:
			return E_INVALIDARG;
		}
		return S_OK;
	}
	STDMETHODIMP CChannelBrowseObj::ChangeBrowsePosition(/*[in]*/ OPCBROWSEDIRECTION dwBrowseDirection,/*[in]*/ LPCWSTR  szString)
	{// TODO: ����� ������� ������
		ATLTRACE("����� ISpaceBrowse::ChangeBrowsePosition, ������ %d\n",m_CurPos.m_pCarrentChannel->get_m_hObjectHandle());
		USES_CONVERSION;
		std::string str,curstr;
		_TAGMAP::iterator itm;

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
			//szString - ����?
			if (str=="") return E_FAIL;
			for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
			{
				std::string x=itm->second->get_m_sObjectName();
				int posx=-1;
				if ((posx=x.find(curstr))!=-1)//���� �����?
					if (x.size()>curstr.size())//��� branch?
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
				if ((posx=x.find(str))!=-1)//���� �����?
					if (x.size()>str.size())//��� branch?
						if (x.at(posx+str.size())=='.')//�������� �� �����
						{
							m_CurPos.m_CurrentPositionName = str;
							return S_OK;
						}
			}
			return E_FAIL;

			break;
		default:
			return E_INVALIDARG;
		}

//	return S_OK;
	}
	STDMETHODIMP CChannelBrowseObj::QueryAvailableProperties(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR **ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes)
	{//��������� �������� ������
		PropMap::const_iterator itm;
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
		}
		return S_OK;
	}
	STDMETHODIMP CChannelBrowseObj::GetItemProperties(/*[in]*/ BSTR ItemID,/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ DWORD * pdwPropertyIDs,/*[out, size_is(,dwCount)] */VARIANT ** ppvData,/*[out, size_is(,dwCount)]*/ HRESULT **ppErrors)
	{// TODO: ����� ������� ������
		//����� ���� � ������ �� ��������
		USES_CONVERSION;
		_TAGMAP::iterator itm;
		// ������ ������ �� ���� �����
		for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
			if (itm->second->get_m_sObjectName()==W2A(ItemID))
				return itm->second->GetProperties(dwCount,pdwPropertyIDs,ppvData,ppErrors);

		return OPC_E_UNKNOWNITEMID;
	}


STDMETHODIMP CChannelBrowseObj::ValidateItem(DWORD dwCount, OPCITEMDEF *pItemArray, BOOL bBlobUpdate, OPCITEMRESULT **ppValidationResults, HRESULT **ppErrors)
{// TODO: ����� ������� ������
    CLogFile_CS dlog;
	dlog.SetNewLogFile("Browser","D:");
//	dlog<<"DEBUG: BEGIN BEGIN BEGIN!!!!";
//	dlog<<dwCount;
	USES_CONVERSION;
	if (dwCount==0)
	{
		return S_OK;
	}
	//�� ����� �������
	_TAGMAP::iterator itm;
	*ppValidationResults=(OPCITEMRESULT*)CoTaskMemAlloc(sizeof(OPCITEMRESULT)*dwCount);
//	dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 1";
//	for(ULONG lo=0;lo<dwCount;lo++)
//		(*ppValidationResults+lo)->pBlob = NULL;
//dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 2";
	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	bool FlagIsAny=false,FlagNotAll=false;
//	dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 3";

	_TAGMAP::iterator itmTM;
	_TAGMAP_NAME_HANDLE::iterator itmNHTM;

	for(ULONG i=0;i<dwCount;i++)
	{
//dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 3.1";
		(*ppValidationResults+i)->pBlob = NULL;
		*(*ppErrors+i)=OPC_E_UNKNOWNITEMID;
		DWORD xxll=0;

		//DEBUG ��������� �����
		try{
		itmNHTM=m_TagStorage->m_NameHandleTagMap.find(W2A((pItemArray+i)->szItemID));	
		if (itmNHTM!=m_TagStorage->m_NameHandleTagMap.end())
		{
//				dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 3.2 FINDED 1";
			//������ ������ ��� ���
            itmTM=m_TagStorage->TMap.find(itmNHTM->second);
			if (itmTM!=m_TagStorage->TMap.end())
			{
				//��� ����� �����
//				dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 3.2 FINDED 2";
				*(*ppErrors+i)=itmTM->second->get_pOPCITEMRESULT((*ppValidationResults)+i,(pItemArray+i)->vtRequestedDataType);
				if(*(*ppErrors+i)==S_OK) FlagIsAny=true;
			}
			else
			{
//				dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 3.2 NOT FINDED 2";
				FlagNotAll=true;
			}
		}
		else
		{
//			dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 3.2 NOT FINDED 1";
			FlagNotAll=true;
		}
		}
		catch(...)
		{
				dlog<<"ERROR!!!!";
				dlog<<"ERROR!!!!";
				dlog<<"ERROR!!!!";
		}
		
/*		for (itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
		{	//if (pItemArray)

			dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 3.1.1";
			xxll++;
			dlog<<xxll;
			try{
			if (itm->second->get_m_sObjectName()==W2A((pItemArray+i)->szItemID))
			{
				//dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 3.1.2";
				*(*ppErrors+i)=itm->second->get_pOPCITEMRESULT((*ppValidationResults)+i,(pItemArray+i)->vtRequestedDataType);
				if(*(*ppErrors+i)!=S_OK) break;
				FlagIsAny=true;
				break;
			}
			}catch(...)
			{
//				dlog<<"ERROR!!!!";
//				dlog<<"ERROR!!!!";
//				dlog<<"ERROR!!!!";
//				dlog<<"ERROR!!!!";
				dlog<<"ERROR!!!!";
				dlog<<"ERROR!!!!";
				dlog<<"ERROR!!!!";
			}
		}

dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 3.2";
		if (itm==m_TagStorage->TMap.end()) FlagNotAll=true;
*/
	}
//dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 4";
	if (FlagIsAny&&(!FlagNotAll)) return S_OK;
//dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 5";
	if (FlagNotAll&&FlagIsAny) return S_FALSE;
//	dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 6";
	if (FlagNotAll&&(!FlagIsAny)) return S_FALSE;
//dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 7";		
			CoTaskMemFree(*ppValidationResults);
			CoTaskMemFree(*ppErrors);
//dlog<<"DEBUG: Enter CChannelBrowseObj::ValidateItem! 8";
	return S_OK;
}

STDMETHODIMP CCChannelObj::ReadTags(DWORD dwCount, OPCHANDLE *phServer, OPCITEMSTATE **ppItemValues, HRESULT **ppErrors)
{
	// TODO: ������ ������ �����.

	return E_NOTIMPL;
}

STDMETHODIMP CCChannelObj::WriteTags(DWORD dwCount, OPCHANDLE *phServer, VARIANT *pItemValues, HRESULT **ppErrors)
{
	// TODO: ������ ����� - ���� �� ����� ���������������.
	if (GlobalServerState==OPC_STATUS_RUNNING)
		return OPC_E_RUNNING;//Error(IDS_ERROR_OPC_E_RUNNING,IID_IMyTestConf,OPC_E_RUNNING);

	return E_NOTIMPL;
}

DWORD CCChannelObj::GetChannelID(DWORD hTag)
{
	return 0;
}

void CCChannelObj::SRead(_SyncIORMsg* mes)
{

//	PostThreadMessage(get_m_ThreadID(),WM_OPC_SYNCREAD,0,(long)mes);
	if (0==PostThreadMessage(m_Cache->get_m_ThreadID(),WM_OPC_SYNCREAD,0,(long)mes))
		mes->SetReady();
//	return S_OK;
}

void CCChannelObj::OnSyncRead(_SyncIORMsg *mes)
{// TODO: ����� ������� ������
	//mes->m_ppItemValues=(OPCITEMSTATE*)CoTaskMemAlloc(sizeof(OPCITEMSTATE)*mes->m_dwNumItems);
	//mes->m_pErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*mes->m_dwNumItems);

	//m_AddTagCS.Lock();
	//try{
	//
	//_TAGMAP::iterator itm;
	//for(UINT i=0;i<mes->m_dwNumItems;i++)
	//{
	//	//_TagID id;
	//	//id.set_m_hObjectHandle(*(mes->m_phServerHandle+i));
	//	itm=m_TagStorage->TMap.find(*(mes->m_phServerHandle+i));
	//	if (itm!=m_TagStorage->TMap.end())
	//	{
	//		*(mes->m_pErrors+i)=itm->second->get_pOPCITEMSTATE((mes->m_ppItemValues+i));
	//	}else
	//	{
	//		VariantInit(&(mes->m_ppItemValues+i)->vDataValue);
	//		*(mes->m_pErrors+i)=OPC_E_INVALIDHANDLE;
	//	}
	//}
	//}catch(...)
	//{
	//	m_LogFile<<"Error in method OnSyncRead of channel";
	//}
	//m_AddTagCS.Unlock();
	//SetEvent(mes->m_hEvent);
	//return;
}

void CCChannelObj::SWrite(_SyncIORMsg *mes)
{
//	PostThreadMessage(get_m_ThreadID(),WM_OPC_SYNCWRITE,0,(long)mes);
	if (0==PostThreadMessage(m_Cache->get_m_ThreadID(),WM_OPC_SYNCWRITE,0,(long)mes))
		mes->SetReady();
//	return S_OK;
}

void CCChannelObj::OnSyncWrite(_SyncIORMsg *mes)
{// TODO: ����� ������� ������
	//mes->m_pErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*mes->m_dwNumItems);
	////����� ���������� �������� � ����� ��������� ����
	//_TAGMAP::iterator itm;
	//FILETIME MyFT;
	//m_AddTagCS.Lock();
	//try{
	//
	//GetSystemTimeAsFileTime(&MyFT);
	//for(UINT i=0;i<mes->m_dwNumItems;i++)
	//{
	//	//��������� ���������.
	//	OPCITEMSTATE St;
	//	VariantInit(&St.vDataValue);
	//	VariantCopy(&St.vDataValue,mes->m_pItemValues+i);
	//	St.ftTimeStamp=MyFT;
	//	itm=m_TagStorage->TMap.find(*(mes->m_phServerHandle+i));
	//	if (itm!=m_TagStorage->TMap.end())
	//		*(mes->m_pErrors+i)=itm->second->WriteNewValue(&St,NULL,true);
	//	else
	//		*(mes->m_pErrors+i)=OPC_E_INVALIDHANDLE;

	//}
	//SetEvent(mes->m_hEvent);
	//}catch(...)
	//{
	//	m_LogFile<<"Error in method OnSyncWrite";
	//}
	//m_AddTagCS.Unlock();
	//return;
}

CTag* CCChannelObj::GetTagRef(DWORD hServer)
{// TODO: ����� ������� ������
//	_TagID id;
	_TAGMAP::iterator itt;
	//id.set_m_hObjectHandle(hServer);
//m_AddTagCS.Lock();
	itt=m_TagStorage->TMap.find(hServer);
	if (itt!=m_TagStorage->TMap.end())
	//{
	//	itt->second->m_dwRefCount++;
		return (itt->second);
	//}
//m_AddTagCS.Unlock();
	return NULL;
}

void CCChannelObj::AsRead(_AsyncIORWMsg *mes)
{
	////PostThreadMessage(get_m_ThreadID(),WM_OPC_ASYNCREAD,0,(long)mes);
	PostThreadMessage(m_Cache->get_m_ThreadID(),WM_OPC_ASYNCREAD,0,(long)mes);
}

void CCChannelObj::AsWrite(_AsyncIORWMsg *mes)
{
	////PostThreadMessage(get_m_ThreadID(),WM_OPC_ASYNCWRITE,0,(long)mes);
	PostThreadMessage(m_Cache->get_m_ThreadID(),WM_OPC_ASYNCWRITE,0,(long)mes);
}

void CCChannelObj::OnAsyncRead(_AsyncIORWMsg *mes)
{// TODO: ����� ������� ������
//����� ��� � ��������� ���������� ����� ������
	//mes->pvValues=(VARIANT*)CoTaskMemAlloc(sizeof(VARIANT)*mes->m_dwNumItems);
	//mes->m_pErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*mes->m_dwNumItems);
	//mes->pwQualities = (WORD*) CoTaskMemAlloc(sizeof(WORD)*mes->m_dwNumItems);
	//mes->pftTimeStamps = (FILETIME*) CoTaskMemAlloc(sizeof(FILETIME)*mes->m_dwNumItems);

	//m_AddTagCS.Lock();
	//try{
	//
	//_TAGMAP::iterator itm;
	//for(UINT i=0;i<mes->m_dwNumItems;i++)
	//{
	////	_TagID id;
	////	id.set_m_hObjectHandle(*(mes->m_phServerHandle+i));
	//	itm=m_TagStorage->TMap.find(*(mes->m_phServerHandle+i));

	//	_variant_t xxx;

	//	VariantInit(mes->pvValues+i);
	//	if (itm!=m_TagStorage->TMap.end())
	//	{
	//		itm->second->ReadBaseValues(xxx,*(mes->pwQualities+i),*(mes->m_pErrors+i),*(mes->pftTimeStamps+i));
	//	}else
	//	{
	//		*(mes->m_pErrors+i)=OPC_E_INVALIDHANDLE;
	//	}
	//	*(mes->pvValues+i)=xxx.Detach();
	//}

	//}catch(...)
	//{
	//	m_LogFile<<"Error in method OnAsyncRead of channel";
	//}
	//m_AddTagCS.Unlock();
	//PostThreadMessage(mes->m_DestThreadID,WM_CONTROLTHREAD_TRANSACTION_COMPLITE_READ,0,(long)mes);
}

void CCChannelObj::OnAsyncWrite(_AsyncIORWMsg *mes)
{// TODO: ����� ������� ������
//����� ��� � ��������� ���������� ����� ������
	//mes->m_pErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*mes->m_dwNumItems);
	//_TAGMAP::iterator itm;
	//FILETIME MyFT;
	//m_AddTagCS.Lock();
	//try{
	//
	//GetSystemTimeAsFileTime(&MyFT);	
	//for(UINT i=0;i<mes->m_dwNumItems;i++)
	//{
	////	_TagID id;
	////	id.set_m_hObjectHandle(*(mes->m_phServerHandle+i));

	//	//��������� ���������.
	//	OPCITEMSTATE St;
	//	VariantInit(&St.vDataValue);
	//	VariantCopy(&St.vDataValue,mes->m_pItemValues+i);
	//	St.ftTimeStamp=MyFT;
	//	itm=m_TagStorage->TMap.find(*(mes->m_phServerHandle+i));
	//	if (itm!=m_TagStorage->TMap.end())
	//		*(mes->m_pErrors+i)=itm->second->WriteNewValue(&St,NULL,true);
	//	else
	//		*(mes->m_pErrors+i)=OPC_E_INVALIDHANDLE;
	//}
	//}catch(...)
	//{
	//	m_LogFile<<"Error in method InAsyncWrite of channel";
	//}
	//m_AddTagCS.Unlock();
	//PostThreadMessage(mes->m_DestThreadID,WM_CONTROLTHREAD_TRANSACTION_COMPLITE_WRITE,0,(long)mes);
	//
}

STDMETHODIMP CCChannelObj::get_ChannelName(BSTR *pVal)
{
	*pVal=_bstr_t(get_m_sObjectName().c_str()).copy();
	return S_OK;
}


STDMETHODIMP CCChannelObj::get_ChannelID(DWORD *pVal)
{
	*pVal=get_m_hObjectHandle();

	return S_OK;
}

STDMETHODIMP CCChannelObj::get_Description(BSTR *pVal)
{
	*pVal = m_Description.copy();
	return S_OK;
}

STDMETHODIMP CCChannelObj::put_Description(BSTR newVal)
{
	USES_CONVERSION;
	if (GlobalServerState==OPC_STATUS_RUNNING)
		return OPC_E_RUNNING;
	this->m_Description = newVal;
	return S_OK;
}

STDMETHODIMP CCChannelObj::get_ConfgStr(BSTR *pVal)
{
	*pVal=m_bstrChannelString.copy();
	return S_OK;
}

STDMETHODIMP CCChannelObj::get_PluginCnfgString(BSTR *pVal)
{
	*pVal=m_bstrPluginString.copy();
	return S_OK;
}

STDMETHODIMP CCChannelObj::get_PluginProgID(BSTR *pVal)
{
	*pVal = m_Plagin->get_m_ProgID().copy();
	
	return S_OK;
}

STDMETHODIMP CCChannelObj::CreateTags(DWORD dwCount,TagDefStruct *pTagDefs,HRESULT**ppErrors)
{
	//����� ����� �������� ����� 
	//������������������ ������ �� ������������������
	//�������� ��� ���������� ������.

	if (GlobalServerState==OPC_STATUS_RUNNING)
		return OPC_E_RUNNING;

	HRESULT hr=S_OK;
	try{	USES_CONVERSION;
	std::vector<CTag*> m_TempVector;
	DWORD NotifyCount=0;
	//_bstr_t coma="select ChannelID,TagName,TagID,RealName,UpdateRate,\
	//	AccessRights,CanonicalDataType,Active,NotifyUpdate,Description from Tag where Channelid=";
	char ch[10];
	FILETIME ft;
	GetSystemTimeAsFileTime(&ft);
	srand(ft.dwLowDateTime);

	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	
	for (UINT iy=0;iy<dwCount;iy++)
	{
		bool IsFlag=false;
		//����� �����(���� ��� ����� ���?)
		stdext::hash_map<DWORD,CTag*>::iterator itm;	
		LPSTR MyCharStr = new char[2000];
		RtlZeroMemory(MyCharStr,2000);
		WideCharToMultiByte(CP_ACP,0,(pTagDefs+iy)->bstrTagName,-1,MyCharStr,2000,NULL,NULL);
		for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
		{
			RtlZeroMemory(MyCharStr,2000);
			WideCharToMultiByte(CP_ACP,0,(pTagDefs+iy)->bstrTagName,-1,MyCharStr,2000,NULL,NULL);
		
			if (itm->second->get_m_sObjectName()==(MyCharStr/*W2A((pTagDefs+iy)->bstrTagName)*/))
			{	
				IsFlag=true;
				break;
			}
		}
		if (IsFlag)
		{
			*(*ppErrors+iy)=E_FAIL;
			continue;
		}else
			*(*ppErrors+iy)=S_OK;
		CTag *pTag = new CTag;
		pTag->GenerateNewID(this,get_m_hObjectHandle());
		pTag->set_m_sObjectName(/*W2A((pTagDefs+iy)->bstrTagName)*/MyCharStr);
		RtlZeroMemory(MyCharStr,2000);
		WideCharToMultiByte(CP_ACP,0,(pTagDefs+iy)->bstrRealName,-1,MyCharStr,2000,NULL,NULL);

		pTag->m_sRealName=/*(char*)W2A((pTagDefs+iy)->bstrRealName)*/MyCharStr;		
		pTag->set_m_UpdateRate((long)(pTagDefs+iy)->dwUpdateRateMS);
		pTag->set_m_AccessRights((long)(pTagDefs+iy)->dwAccessRight);
		pTag->set_m_vtCanonicalDataType((ULONG)(pTagDefs+iy)->vtTagType);
		pTag->set_m_Active((long)(pTagDefs+iy)->bActive);
		pTag->m_UpdateFromNotify=(long)(pTagDefs+iy)->bNotifyUpdate;
		pTag->m_Description=(pTagDefs+iy)->bstrTagDescription;
		
		////��������� ����� �������� ����� � � ����� ����������� �� �����������


		//���������� �� ��������� ����� �����
		if (SUCCEEDED(hr))
			m_TempVector.insert(m_TempVector.end(),pTag);
		
		//����� �������� �����������
		if (pTag->m_UpdateFromNotify)
			NotifyCount++;
		
		delete[] MyCharStr;	
	}	
	
	//���������� ����� � �����.
	//������� ������� � ����� �����

	_TagID* pTagID = new _TagID[NotifyCount];
	long yy=0;
	for(UINT i=0;i<m_TempVector.size();i++)
	{
		m_TagStorage->TMap.insert(_TAGMAP::value_type(m_TempVector[i]->get_m_hObjectHandle(),m_TempVector[i]));
		//DEBUG
		m_TagStorage->m_NameHandleTagMap.insert(_TAGMAP_NAME_HANDLE::value_type(m_TempVector[i]->get_m_sObjectName(),m_TempVector[i]->get_m_hObjectHandle()));
		if (m_TempVector[i]->m_UpdateFromNotify)
		{
			m_TagStorage->m_NotifyTagList.insert(m_TagStorage->m_NotifyTagList.end(),(_TagID)*m_TempVector[i]);
			pTagID[yy]=(_TagID)*m_TempVector[i];
			yy++;
		}
	}
}catch(...)
{
	m_LogFile<<"Error! �������� ��� ������  -  ������������ �����";
	return S_FALSE;
}
	return S_OK;
}

STDMETHODIMP CCChannelObj::ChangeTagsDef(DWORD dwCount,OPCHANDLE * pHandles,TagDefStruct *pNewDefs,HRESULT**ppErrors)
{
	if (GlobalServerState==OPC_STATUS_RUNNING)
		return OPC_E_RUNNING;
    //������� ������� ���, � ����� - ��������
	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	ZeroMemory(*ppErrors,sizeof(HRESULT)*dwCount);

	try{
		for (int i=0;i<dwCount;i++)
		{
				_TAGMAP::iterator itm;
				itm=this->m_TagStorage->TMap.find(pHandles[i]);
				if (itm!=m_TagStorage->TMap.end())
				{
					bool OldNotify=false;
					//�����
					CTag *pTag=itm->second;

					//name
					_bstr_t tnameX=this->get_m_sObjectName().c_str();
					tnameX+=".";
					tnameX+=(char*)(_bstr_t(pNewDefs[i].bstrTagName));
					pTag->set_m_sObjectName((char*)tnameX);
					//real name
					pTag->set_m_sRealName((char*)_bstr_t(pNewDefs[i].bstrRealName));
					//access rights
					pTag->set_m_AccessRights( pNewDefs[i].dwAccessRight);
					//description
					pTag->m_Description=(char*)_bstr_t(pNewDefs[i].bstrTagDescription);	
					//active
					pTag->set_m_Active((bool)pNewDefs[i].bActive);	
					//bNotifyUpdate
					OldNotify=pTag->m_UpdateFromNotify;
					pTag->m_UpdateFromNotify = (bool)pNewDefs[i].bNotifyUpdate;
					//dwUpdateRateMS
					pTag->set_m_UpdateRate(pNewDefs[i].dwUpdateRateMS);
					//vtTagType
					pTag->set_m_vtCanonicalDataType(pNewDefs[i].vtTagType);


					if (OldNotify)//���� ��� �� �����������...
					{
						//������� �������� �� ������ �������������� �����
						std::list<_TagID>::iterator findIt=std::find(m_TagStorage->m_NotifyTagList.begin(),m_TagStorage->m_NotifyTagList.end(),*pTag);
						if (findIt!=m_TagStorage->m_NotifyTagList.end())
						{//���� ����� - ������
							m_TagStorage->m_NotifyTagList.erase(findIt);
						}
					}
					if (pTag->m_UpdateFromNotify)
					{
						//������� � ������ �����������
						m_TagStorage->m_NotifyTagList.insert(m_TagStorage->m_NotifyTagList.end(),*pTag);
					}

					char  ddd[500];
					sprintf(ddd,"��� � ID=%d ������� �������.",pHandles[i]);
					m_LogFile<<ddd;
					*(*ppErrors+i)=S_OK;
				}
				else
				{
					*(*ppErrors+i)=OPC_E_UNKNOWNITEMID;
				}
		}
	}
	catch(...)
	{
		m_LogFile<<"����������� ������ ��� ��������� ����!!!";
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CCChannelObj::DeleteTags(DWORD dwCount, DWORD *dwHandles, HRESULT **ppErrors)
{
	if (GlobalServerState==OPC_STATUS_RUNNING)
		return OPC_E_RUNNING;
	
	HRESULT hr = S_OK;
	//�������� ����� ������������ �� ����� �����.
	*ppErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	ZeroMemory(*ppErrors,sizeof(HRESULT)*dwCount);
	try{
		for (int i=0;i<dwCount;i++)
		{
				//�������� �� ����� �����
				_TAGMAP::iterator itm;
				itm=this->m_TagStorage->TMap.find(dwHandles[i]);
				if (itm!=m_TagStorage->TMap.end())
				{
					//�����
					CTag *pTag=itm->second;

					//������� �������� �� ������ �������������� �����
					std::list<_TagID>::iterator findIt=std::find(m_TagStorage->m_NotifyTagList.begin(),m_TagStorage->m_NotifyTagList.end(),*pTag);
					if (findIt!=m_TagStorage->m_NotifyTagList.end())
					{//���� ����� - ������
						m_TagStorage->m_NotifyTagList.erase(findIt);
					}
					//��� ��� ����� ������...

					//DEBUG
					_TAGMAP_NAME_HANDLE::iterator itmNH;
					itmNH=m_TagStorage->m_NameHandleTagMap.find(itm->second->get_m_sObjectName());
					if (itmNH!=m_TagStorage->m_NameHandleTagMap.end())
						m_TagStorage->m_NameHandleTagMap.erase(itmNH);

					m_TagStorage->TMap.erase(itm);
					char  ddd[500];
					sprintf(ddd,"��� � ID=%d ������� ������.",dwHandles[i]);
					m_LogFile<<ddd;
					*(*ppErrors+i)=S_OK;
				}
				else
				{
					*(*ppErrors+i)=OPC_E_UNKNOWNITEMID;
				}
		}
	}catch(...)
	{
		m_LogFile<<"����������� ������ ��� �������� ����!!!";
		return S_FALSE;
	}
	return hr;
}

void CCChannelObj::StopChannelHandler()
{
	if (m_Cache)
	{
		m_LogFile<<"������������� ���������� ����";
		m_Cache->Stop();
		
	}

	m_LogFile<<"������� Handler'� �� �������!";
	
}

void CCChannelObj::StartChannelHandler()
{
	if (m_ChannelMode==chmEnabled)
	{
		m_LogFile<<"������ Handler'� �� �������!";
		m_Cache->run();
	}

}


// ������� ��� ������������� ������ ����� CreateChannel ������� ������������
HRESULT CCChannelObj::InitNoytFromXML(ChannelDef* pChannelDef)
{
	USES_CONVERSION;
	HRESULT hr=S_OK;
	PhysicalCreatePath(m_ConfigLogPath+"\\Channels\\"+get_m_sObjectName()+"\\Plugin");
	m_LogFile.SetNewLogFile(get_m_sObjectName(),m_ConfigLogPath+"\\Channels\\"+get_m_sObjectName());
	m_LogFile.GenerateLogFile(true,true);
	char b[300];
//	ATLTRACE("������������� ������  ID=%d Name=%s ",get_m_hObjectHandle(),get_m_sObjectName().c_str());
//	m_LogFile<<"\n==============================================";
//	sprintf(b,"������������� ������  ID=%d Name=%s ",get_m_hObjectHandle(),get_m_sObjectName().c_str());
//	m_LogFile<<b;

	try{
	try{//�� ������������� �������
		//���������
		if (!m_Plagin) m_Plagin = new CDataPlugin(m_LogFile);
			m_Plagin->m_PluginLogFilePrefix = m_ConfigLogPath+"\\Channels\\"+get_m_sObjectName()+"\\Plugin\\";
			m_Plagin->m_PluginLogFilePrefix+=get_m_sObjectName()+"Plugin";
			m_Plagin->m_PluginLogFilePostFix = m_LogFile.GetPostfix()+".log";
			m_Plagin->set_m_ProgID(W2A(pChannelDef->PluginProgID));
			m_Plagin->m_bstrPluginStringX=this->m_bstrPluginString = W2A(pChannelDef->PluginCnfg);

		//�� ������������� �������
		}catch(_com_error &e)
		{
		}
		catch(...)
		{
		}
		
		//������������� ����� ������
		if (m_TagStorage==NULL) m_TagStorage = new CTagStorage;
    //�� ��� ������������� �� XML
	}catch(_com_error &e)
	{
		hr=E_FAIL;
	}
	catch(...)
	{
		hr=E_FAIL;
	}

	m_Init = true;
	
	//������� ���������� ����
	if (!m_Cache) m_Cache = new CCacheUpdateHandler(m_LogFile); 
	m_Cache->set_m_TagStorage(m_TagStorage);
	m_Cache->set_m_ClockRate(m_ClockRate);
	m_Cache->set_m_ChannelNotify((CLocalNotify*)this);	
	m_Cache->set_m_Device(m_Plagin);
	m_Cache->Stop();

//	if((m_ChannelMode==chmEnabled)&&(GlobalServerState==OPC_STATUS_RUNNING))
//	{
//		m_LogFile<<"�������� ���������� ���� ������ (CacheHandler)";
//		m_Cache->run();
//	}

	return hr;
}

// ���������� ��������� ������ � XML. ���������� �������������� ���� ������
MSXML2::IXMLDOMNodePtr CCChannelObj::Save2XML()
{
	MSXML2::IXMLDOMNodePtr retnode;
	HRESULT hr=E_NOTIMPL;
	try{
		//�������� XML ��������� ��� �������� �������
		MSXML2::IXMLDOMDocumentPtr xmldoc;
		xmldoc.CreateInstance(__uuidof(MSXML2::DOMDocument60));

		//�������� ������� ������ ��������� �� ��������
		CString ChannelXMLTemplate;
		ChannelXMLTemplate.LoadString(IDS_XMLTEMPLATE_CHANNEL);
		//�������, ��� �� ����� ���������� �������������
		_bstr_t tt(ChannelXMLTemplate.AllocSysString(),false);
		//��������� XML �� �������
		xmldoc->loadXML(tt);

		//������ ���������� � �������� ����� ����� ������ "���������"
		MSXML2::IXMLDOMNodePtr node=xmldoc->getElementsByTagName("Channel")->item[0l];//��� ��� � ������� ����� ����
		//�������� ������
		node->attributes->getNamedItem("ChannelName")->nodeValue=this->get_m_sObjectName().c_str();
		//���������������� ������ ������
		node->attributes->getNamedItem("CnfgString")->nodeValue=this->m_bstrChannelString;
		//����� �������� ������
		SYSTEMTIME st;
		FileTimeToSystemTime(&this->m_CreateTime,&st);
		DOUBLE VarTime;
		SystemTimeToVariantTime(&st,&VarTime);
		_variant_t _VarTime=VarTime;
		_VarTime.ChangeType(VT_DATE);
		node->attributes->getNamedItem("CreateTime")->nodeValue=_VarTime;
		//����� ������ ������
		node->attributes->getNamedItem("ChannelMode")->nodeValue=(long)this->m_ChannelMode;
		//������ ���������� ������
		node->attributes->getNamedItem("ClockRate")->nodeValue=this->m_ClockRate;
		//�������� ������
		node->attributes->getNamedItem("Description")->nodeValue=this->m_Description;
		//ProgID �������, �\� ������� �������� ����� � �����������
		node->attributes->getNamedItem("PluginProgID")->nodeValue=this->m_Cache->get_m_Device()->get_m_ProgID();
		//���������������� ������ �������
		node->attributes->getNamedItem("PluginCnfgString")->nodeValue=this->m_bstrPluginString;
		
		//������ ���������� �������� ���� ����� ������ � XML
		_TAGMAP::iterator itm;
		//���� �� ���� ����� � ����� ������
		for(itm=this->m_TagStorage->TMap.begin();itm!=this->m_TagStorage->TMap.end();++itm)
		{
			MSXML2::IXMLDOMNodePtr pN=itm->second->Save2XML();
			if (!(pN==NULL))
				node->appendChild(pN);
		}
		retnode=node;
	}catch(_com_error &e)
	{
		m_LogFile<<"������: ������ ������ ������ � XML ����!";
//		ATLTRACE((char*)e.Description);
	}
	catch(...)
	{
		m_LogFile<<"������: ����������� ������ ������ ������ � XML ����!!!";
	}
	_bstr_t testo=retnode->xml;
	return retnode;	
}
