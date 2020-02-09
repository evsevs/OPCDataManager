#include "stdafx.h"

// Handlers
#include "Handlers.h"
#include <vector>
// Class CReadyEvent 
//CReadyEvent::CReadyEvent()	  : m_ReadyEvent(0)
//{
//}
//
//CReadyEvent::~CReadyEvent()
//{
//}
//
//bool CReadyEvent::SetReadyState (bool State)
//{
//	return true;
//}
//
//bool CReadyEvent::IsReady (DWORD dwWaitTime)
//{
//	return true;
//}

// Class CDeviceUpdateHandler 
//CDeviceUpdateHandler::CDeviceUpdateHandler(CLogFile_CS &lf):m_LogFile(lf), m_DeviceUpdateMode(TRUE)
//{
//}
//
//CDeviceUpdateHandler::CDeviceUpdateHandler (DWORD ClockRate,CLogFile_CS &lf) : m_DeviceUpdateMode(TRUE),m_LogFile(lf)
//{
//	set_m_ClockRate(ClockRate);
//}
//
//
//CDeviceUpdateHandler::~CDeviceUpdateHandler()
//{
//}
//void CDeviceUpdateHandler::Send_ClearAsync(DWORD dwTID)
//{
//	PostThreadMessage(this->get_m_ThreadID(),WM_HANDLER_CLEAR_ASYNC,0,(long)dwTID);
//}
//
//void CDeviceUpdateHandler::OnClearAsync(DWORD dwTID)
//{//������� � �������
//		ATLTRACE("����� OnClearAsync\n");
//	std::list<CAsyncThread*>::iterator itl;
//	for(itl=m_AsyncList.begin();itl!=m_AsyncList.end();++itl)
//	{
//		if ((*itl)->dwTransactionID=dwTID)
//		{
//			delete *itl;
//			m_AsyncList.erase(itl);
//			break;
//		}
//	}
//}
//void CDeviceUpdateHandler::Send_AsyncWrite(_AsyncIORWMsg *mes)
//{
//	PostThreadMessage(get_m_ThreadID(),WM_OPC_ASYNCWRITE,0,(long)mes);
//}
//void CDeviceUpdateHandler::OnAsyncWrite(MSG mes)
//{
//  //����� ��������� ��������� � ��������� ������?
//	CAsyncThread * pATh=new CAsyncThread;
//	
//	pATh->dwTransactionID = ((_AsyncIORWMsg*)mes.lParam)->get_m_TransactionID();
//	pATh->pMsg= (_AsyncIORWMsg*)mes.lParam;
//	pATh->m_Owner = this;
//	
//	m_AsyncList.insert(m_AsyncList.end(),pATh);
//	pATh->run();
//	//��� ���������� �������� �� update �����.
//}
//DWORD CDeviceUpdateHandler::CAsyncThread::fbody()
//{
///*	Active=true;
//	//����� ��������� ��������������� ������ ����� (�� ����������).
//
//	///_UpdateNowMsg * pUpdateNowMsg=new _UpdateNowMsg();
//	
//	//���� ����, ������� ������� ������
//	std::map<_TagID,CTag*>::iterator itm;
//	std::list<CTag*>::iterator itl;
//	std::vector<CTag*> Taglist;
//	_TagID MyID;
////	OPCHANDLE * ItemHandleArray = new OPCHANDLE[pMsg->m_dwNumItems];
//	for (int Mi=0;Mi<pMsg->m_dwNumItems;Mi++)
//	{
//		MyID.set_m_hObjectHandle(*(pMsg->m_phServerHandle+Mi));
//		itm=m_Owner->m_TagStorage->TMap.find(MyID);
//		if (itm!=m_Owner->m_TagStorage->TMap.end())
//		{
//			Taglist.insert(Taglist.end(),itm->second);
////			ItemHandleArray[Mi]=itm->second->get_m_hObjectHandle();
//		}
//	}
//
//	_UpdateNowMsg* pUpdateNowMsg = new _UpdateNowMsg();
//	//������ ��������
//	pUpdateNowMsg->dwCount=Taglist.size();
////	if (pUpdateNowMsg->dwCount==0)
////	{
////		delete pUpdateNowMsg;
////		return S_OK;
////	}
//	//�������� ����� ��� ������ ���������������
//	pUpdateNowMsg->phClient=Taglist[0];//new _TagID[pUpdateNowMsg->dwCount];
//	//�������� ����� ��� ������ ��������
//	pUpdateNowMsg->pvValues=pMsg->m_pItemValues;
//	pUpdateNowMsg->pErrors=NULL;
//
//	//������ �������� CDataPlagin
//	HRESULT hr=S_OK;
//	if (pUpdateNowMsg->dwCount)
//	{
//		hr=m_Owner->get_m_Device()->SetTagsData(pUpdateNowMsg);
//		//������������ ���������� ������
//		if (SUCCEEDED(hr))
//		{
//				pMsg->m_pErrors=pUpdateNowMsg->pErrors;
//
//		}
//
//	//	delete[] pUpdateNowMsg->phClient;
//	}
//
//
//
//
//
//	PostThreadMessage(pMsg->m_DestThreadID,WM_CONTROLTHREAD_TRANSACTION_COMPLITE_WRITE,0,(long)pMsg);
//	Active=false;
//	m_Owner->Send_ClearAsync(dwTransactionID);
//*/	return 0;
//	
/////////////////////////////////////////////////////////////////////////////////////
//
//}

//HRESULT CDeviceUpdateHandler::OnTimerMessage (MSG msg)
//{// TODO: ����� ������� ������
//	m_TagStorage->m_ChangeMapCS.Lock();
//	HRESULT hr;
//	try
//	{
//	
//	std::hash_map<DWORD,CTag*>::iterator itm;
//	std::list<CTag*>::iterator itl;
//	std::list<CTag*> Taglist;
//	//������� - ����� ���� ����� �������� � ����������.
//
//	for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
//	{
//		//���� ��� ������� ��������...
//		if (itm->second->IsUpdatedByClient())
//		{
//		//	itm->second->set_m_bClientCacheUpdate(false);
//			//��������� � ������
//			Taglist.insert(Taglist.end(),itm->second);
//		}
//	}
//	
//	_UpdateNowMsg* pUpdateNowMsg = new _UpdateNowMsg();
//	//������ ��������
//	pUpdateNowMsg->dwCount=Taglist.size();
//	if (pUpdateNowMsg->dwCount==0)
//	{
//		delete pUpdateNowMsg;
//		m_TagStorage->m_ChangeMapCS.Unlock();
//		return S_OK;
//	}
//	//�������� ����� ��� ������ ���������������
//	pUpdateNowMsg->phClient=new _TagID[pUpdateNowMsg->dwCount];
//	//�������� ����� ��� ������ ��������
//	pUpdateNowMsg->pvValues=(VARIANT*)(CoTaskMemAlloc(pUpdateNowMsg->dwCount*sizeof(VARIANT)));
//	pUpdateNowMsg->pErrors=NULL;
//
//	long count=0;
//	for(itl=Taglist.begin();itl!=Taglist.end();++itl)
//	{
//		VariantInit(pUpdateNowMsg->pvValues+count);
//		(*itl)->VariantCopyValue(pUpdateNowMsg->pvValues+count);
//		(*itl)->set_m_bClientCacheUpdate(false);
//		*(pUpdateNowMsg->phClient+count)=(_TagID)(**itl);
//		count++;
//	}
//	//������ �������� CDataPlagin
//	hr=S_OK;
//	if (pUpdateNowMsg->dwCount)
//	{
//		hr=get_m_Device()->SetTagsData(pUpdateNowMsg);
//		//������������ ���������� ������
//		if (SUCCEEDED(hr))
//		{
//			if (pUpdateNowMsg->pErrors)
//			{
//				CoTaskMemFree(pUpdateNowMsg->pErrors);
//				pUpdateNowMsg->pErrors=NULL;
//			}
//			if (pUpdateNowMsg->pvValues)
//			{
//				for(ULONG ii;ii<pUpdateNowMsg->dwCount;ii++)
//					VariantClear(pUpdateNowMsg->pvValues+ii);
//				CoTaskMemFree(pUpdateNowMsg->pvValues);
//				pUpdateNowMsg->pvValues=NULL;
//			}
//
//		}
//
//		delete[] pUpdateNowMsg->phClient;
//	}
///*
//	CoTaskMemFree(pUpdateNowMsg->pErrors);
//	for(long ii;ii<pUpdateNowMsg->dwCount;ii++)
//		VariantClear(pUpdateNowMsg->pvValues+ii);
//	CoTaskMemFree(pUpdateNowMsg->pvValues);
//
//*/	
//	}catch(...)
//	{
//		m_LogFile<<"Error in method OnTimer Device";
//	}
//	m_TagStorage->m_ChangeMapCS.Unlock();
//	return hr;
//}

//HRESULT CDeviceUpdateHandler::OnUpdateNow (MSG msg)
//{
//	HRESULT hr=S_OK;
//		
//	if (((_UpdateNowMsg*)msg.lParam)->dwCount)
//		hr=get_m_Device()->SetTagsData((_UpdateNowMsg*)msg.lParam);
//	CoTaskMemFree(((_UpdateNowMsg*)msg.lParam)->pErrors);
//	((_UpdateNowMsg*)msg.lParam)->pErrors=NULL;
//	for(ULONG ii=0;ii<((_UpdateNowMsg*)msg.lParam)->dwCount;ii++)
//		VariantClear(((_UpdateNowMsg*)msg.lParam)->pvValues+ii);
//	CoTaskMemFree(((_UpdateNowMsg*)msg.lParam)->pvValues);
//	((_UpdateNowMsg*)msg.lParam)->pvValues=NULL;
//	return hr;
//}
//
//DWORD CDeviceUpdateHandler::fbody ()
//{
//	CoInitializeEx(NULL,COINIT_MULTITHREADED); //� ���
//ATLTRACE("�������� ����� ����������� ���������� ������ ID=%d Handle=%d\n",this->get_m_ThreadID(),this->get_m_ThreadHandle());
//	if (m_DeviceUpdateMode)
//	{
//		StartTimer();
//		ATLTRACE("�������� Timer ����������� ����������\n");
//		m_LogFile<<"�������� Timer ����������� ����������\n";
//	}
//	
//	MSG msg;
//   ::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE) ;
//	while(GetMessage(&msg,0,0,0))
//	{
//	   ::DispatchMessage(&msg);
//	   switch(msg.message)
//	   {
////	   case WM_UPDATETAGSNOW:
////		   OnUpdateNow(msg);
////		   break;
//	   case WM_TIMER://������������ ������ ��� ������
//		   OnTimerMessage(msg);
//		   break;
////	   case WM_OPC_ASYNCWRITE:
////		   OnAsyncWrite(msg);
////		   break;
//
//	   }
//	 }
//  if (m_TimerID!=0)  StopTimer();
//
//  CoUninitialize();
//	return 0;
//}

// Class CCacheUpdateHandler 
CCacheUpdateHandler::CCacheUpdateHandler(CLogFile_CS &lf):m_LogFile(lf)
{
	m_NotifyAdded=false;
}


CCacheUpdateHandler::~CCacheUpdateHandler()
{

}


void CCacheUpdateHandler::ChangeLogFile()
{
	if (m_dwChangeLogCicleCount>5000)//5000 ������
	{
		m_LogFile.GenerateLogFile();
		get_m_Device()->SetNewLogForPlugin(m_LogFile.GetPostfix()+".log");
		m_dwChangeLogCicleCount=0;
	}
	else
		m_dwChangeLogCicleCount++;

}
bool CCacheUpdateHandler::ControlPluginInit()
{
	if (!get_m_Device()->get_m_Init())
	{//���� �� ���������������
		if (m_dwInitCount>10/*0*/)//��� ������
		{ //���� ����� �������� �������
			::PostThreadMessage(get_m_ThreadID(),WM_INITPLUGIN,0,0);
			m_dwInitCount=0;
		}
		else
			m_dwInitCount++;
		return false;
	}
	return true;
}
HRESULT CCacheUpdateHandler::OnTimerMessage (MSG msg)
{
	USES_CONVERSION;
	HRESULT hr;
	try{
	
	HRESULT hr1=E_FAIL;;
	//����� ����� ���-�����
	ChangeLogFile();
	//m_LogFile<<"DEBUG: OnTimerMessage::!!";
	//�������� ������������� �������
	if (!ControlPluginInit())	return S_OK;

///////////////////////////////////////////////////////////////////////////////
    //���������� �������� 2 ����
	m_pUpdateNowMsg2->GenerateTAGsUpdateList(m_TagStorage,m_NotifyAdded);
	if (!m_pUpdateNowMsg2->dwCount/*ItCount*/) 
		return S_OK;

	hr=S_OK;

	hr=get_m_Device()->GetTagsData(m_pUpdateNowMsg2);
	
	if (SUCCEEDED(hr))
	{
		for(ULONG i=0;i<m_pUpdateNowMsg2->dwCount;i++)
		{
			//����������� ��������, �������� � ����� ��������� ����.
			//���� �������� ���� ���� �������� �������� - ����� �������� �� �������.
			try{
				CTag * pTa=(CTag*)*(m_pUpdateNowMsg2->phClient+i);
				if (SUCCEEDED(pTa->WriteNewValue(m_pUpdateNowMsg2->pItemState+i,m_pUpdateNowMsg2->pErrors+i)))
				//���� TRUE -  �������� � � ��� ��������
				{
				//	Taglist.insert(Taglist.end(),itm->second);
				}
			}catch(...)
			{
				m_LogFile<<"ERROR: �������������� ������ � CCacheUpdateHandler::OnTimerMessage() WriteNewValue()!!!";
			}
		}
	}
	else //���� �������� ������ ������
	{
		m_LogFile<<"ERROR: ��������� ������ ����� � ��acheUpdateHandler::OnTimerMessage!!!";
		m_LogFile<<hr;
		//������������� Quality � OPC_QUALITY_LAST_KNOWN
		for(ULONG ii=0;ii<m_pUpdateNowMsg2->dwCount;ii++)
		{ 
			CTag * pTa=(CTag*)*(m_pUpdateNowMsg2->phClient+ii);
			pTa->set_m_wQuality(OPC_QUALITY_LAST_KNOWN);
		}
	}

	//������������ ������

	
	if (m_pUpdateNowMsg2->pItemState) {
		CoTaskMemFree(m_pUpdateNowMsg2->pItemState);
		m_pUpdateNowMsg2->pItemState=NULL;
	}
	if (m_pUpdateNowMsg2->pErrors)
	{
		CoTaskMemFree(m_pUpdateNowMsg2->pErrors);
		m_pUpdateNowMsg2->pErrors=NULL;
	}
	


	}catch(...)
	{
		m_LogFile<<"ERROR: �������������� ������ � CCacheUpdateHandler::OnTimerMessage()!!!";
	}

return hr;
}
//HRESULT CCacheUpdateHandler::OnUpdateNow (MSG msg)
//{
//	return E_FAIL;
//}
void CCacheUpdateHandler::Client_DeviceReadSync(_SyncIORMsg *mes)
{
	PostThreadMessage(get_m_ThreadID(),WM_OPC_SYNCREAD,0,(long)mes);
}
void CCacheUpdateHandler::Client_DeviceReadAsync(_AsyncIORWMsg *mes)
{
	PostThreadMessage(get_m_ThreadID(),WM_OPC_ASYNCREAD,0,(long)mes);
}
void CCacheUpdateHandler::Client_DeviceWriteSync(_SyncIORMsg *mes)
{
	PostThreadMessage(get_m_ThreadID(),WM_OPC_SYNCWRITE,0,(long)mes);
}
void CCacheUpdateHandler::Client_DeviceWriteAsync(_AsyncIORWMsg *mes)
{
	PostThreadMessage(get_m_ThreadID(),WM_OPC_ASYNCWRITE,0,(long)mes);
}

void CCacheUpdateHandler::OnWriteNow (MSG msg,bool IsEvented)
{
	HRESULT hr=S_OK;
	if (((_UpdateNowMsg*)msg.lParam)->dwCount)
		hr=get_m_Device()->SetTagsData((_UpdateNowMsg*)msg.lParam);
	if (((_UpdateNowMsg*)msg.lParam)->pErrors!=NULL)
	{
		CoTaskMemFree(((_UpdateNowMsg*)msg.lParam)->pErrors);
		((_UpdateNowMsg*)msg.lParam)->pErrors=NULL;
	}
	for(ULONG ii=0;ii<((_UpdateNowMsg*)msg.lParam)->dwCount;ii++)
		VariantClear(((_UpdateNowMsg*)msg.lParam)->pvValues+ii);

	CoTaskMemFree(((_UpdateNowMsg*)msg.lParam)->pvValues);
	((_UpdateNowMsg*)msg.lParam)->pvValues=NULL;

	return ;
}
void CCacheUpdateHandler::OnReadNow (MSG msg,bool IsEvented)
{
	//HRESULT hr;
	//try{
	//
	//_UpdateNowMsg2 * pUpdateNowMsg2=new _UpdateNowMsg2();
	////��������������� �������� ���������
	//pUpdateNowMsg2->phClient=((_UpdateMsg*)msg.lParam)->phClient;
	//pUpdateNowMsg2->dwCount=((_UpdateMsg*)msg.lParam)->dwCount;
	////������� ������ ���������
	//delete (_UpdateMsg*)msg.lParam;
	//
	////� ������ ����� ������ � ���������.
	//std::hash_map<DWORD,CTag*>::iterator itm;
	//std::list<CTag*> Taglist;
	//hr=S_OK;
	//if (pUpdateNowMsg2->dwCount)
	//{
	//	hr=get_m_Device()->GetTagsData(pUpdateNowMsg2);
	//	if (SUCCEEDED(hr))
	//	{
	//		//_TagID t;
	//		for(ULONG i=0;i<pUpdateNowMsg2->dwCount;i++)
	//		{
	//			//t.set_m_hObjectHandle((pUpdateNowMsg2->pItemState+i)->hClient);
	//			itm=m_TagStorage->TMap.find((pUpdateNowMsg2->pItemState+i)->hClient);
	//			if (itm!=m_TagStorage->TMap.end())
	//			{
	//				//����������� ��������, �������� � ����� ��������� ����.
	//				//���� �������� ���� ���� �������� �������� - ����� �������� �� �������.
	//				if (SUCCEEDED(itm->second->WriteNewValue(pUpdateNowMsg2->pItemState+i,pUpdateNowMsg2->pErrors+i)))
	//					//���� TRUE -  �������� � � ��� ��������
	//					Taglist.insert(Taglist.end(),itm->second);
	//				//VariantClear(&(pUpdateNowMsg2->pItemState+i)->vDataValue);
	//			}
	//
	//		}

	//	}
	//}
	////������������ ������
	//CoTaskMemFree(pUpdateNowMsg2->phClient);
	//pUpdateNowMsg2->phClient=NULL;
	//CoTaskMemFree(pUpdateNowMsg2->pItemState);
	//pUpdateNowMsg2->pItemState=NULL;

	//delete pUpdateNowMsg2;

	//if (Taglist.size())
	//{
	//	//���������� ��������� �� �����������
	//	_UpdateMsg * pUpdateMsg = new _UpdateMsg();
	//	pUpdateMsg->dwCount=Taglist.size();
	//	*(pUpdateMsg->phClient=(_TagID*))(CoTaskMemAlloc(pUpdateMsg->dwCount*sizeof(_TagID)));
	//
	//	std::list<CTag*>::iterator itl;
	//	long count=0;
	//	for(itl=Taglist.begin();itl!=Taglist.end();++itl)
	//	{
	//		*(pUpdateMsg->phClient+count)=(_TagID)(**itl);
	//		count++;
	//	}	
	//	
	//	//����������� ������ �� ����������
	//	if (SUCCEEDED(hr))
	//		m_ChannelNotify->Send_OnTagUpdate(pUpdateMsg);	
	//}
	//}catch(...)
	//{
	//	m_LogFile<<"Error in method OnUpdateNow Cache";
	//}
	return ;
}

void CCacheUpdateHandler::TagsUpdated (_UpdateMsg* pUpdateMsg)
{
	//������� ������ �� ���������� ����� � ����.
	m_ChannelNotify->Send_OnTagUpdate(pUpdateMsg);
}

void CCacheUpdateHandler::Send_OnTagUpdate (_UpdateMsg* pUpdateMsg)
{
	//���������� ��������� � ����������� � ������� ��������� ������
	PostThreadMessage(get_m_ThreadID(),WM_TAGSUPDATED,0,(long)pUpdateMsg);
}

HRESULT CCacheUpdateHandler::OnNotify (MSG msg)
{
	try{
	
	stdext::hash_map<DWORD,CTag*>::iterator itm;
	std::list<CTag*> Taglist;

	_UpdateNowMsg2 * pUpdateNowMsg2 = (_UpdateNowMsg2*)msg.lParam;
//	_TagID t;
//	m_LogFile<<"�����������";
	for(ULONG i=0;i<pUpdateNowMsg2->dwCount;i++)
	{
		//t.set_m_hObjectHandle((pUpdateNowMsg2->pItemState+i)->hClient);
		itm=m_TagStorage->TMap.find((pUpdateNowMsg2->pItemState+i)->hClient);
		if (itm!=m_TagStorage->TMap.end())
		{
			//����������� ��������, �������� � ����� ��������� ����.
			//���� �������� ���� ���� �������� �������� - ����� �������� �� �������.
			try{
			
			if (SUCCEEDED(itm->second->WriteNewValue(pUpdateNowMsg2->pItemState+i,pUpdateNowMsg2->pErrors+i)))
			{	//���� TRUE -  �������� � � ��� ��������
			//Taglist.insert(Taglist.end(),itm->second);
			}
			
			VariantClear(&(pUpdateNowMsg2->pItemState+i)->vDataValue);
			}catch(...)
			{
				ATLTRACE("ERRRRRRRRRRRRRRRRRRRRRRRRRRR\n");
			}
		}
	
	}
	
	//������������ ������
	CoTaskMemFree(pUpdateNowMsg2->pItemState);
	pUpdateNowMsg2->pItemState=NULL;
	CoTaskMemFree(pUpdateNowMsg2->pErrors);
	pUpdateNowMsg2->pErrors=NULL;
	delete pUpdateNowMsg2;

/*	if (Taglist.size())
	{
		//���������� ��������� �� �����������
		_UpdateMsg * pUpdateMsg = new _UpdateMsg();
		pUpdateMsg->dwCount=Taglist.size();
		pUpdateMsg->phClient= new _TagID[pUpdateMsg->dwCount];
	
		std::list<CTag*>::iterator itl;
		long count=0;
		for(itl=Taglist.begin();itl!=Taglist.end();++itl)
		{
			*(pUpdateMsg->phClient+count)=(_TagID)(**itl);
			count++;
		}	
		
		//����������� ������ �� ����������
		TagsUpdated(pUpdateMsg);	
	}*/

	//	ATLTRACE("��������� ���������� � CacheHandler �� �������\n");
	//m_LogFile<<"����� �� �����������";
}catch(...)
{
	ATLTRACE("Error in method OnNotify cache\n");
}
//m_TagStorage->m_ChangeMapCS.Unlock();
	return S_OK;
  //## end CCacheUpdateHandler::OnNotify%3B4408DD026D.body
}

DWORD CCacheUpdateHandler::fbody ()
{
	CoInitializeEx(NULL,COINIT_MULTITHREADED);//�������� � ���
    m_pUpdateNowMsg2 = new _UpdateNowMsg2();
	ATLTRACE("�������� ����� ����������� ���� ������ ID=%d Handle=%d\n",this->get_m_ThreadID(),this->get_m_ThreadHandle());
	StartTimer();
	//������������� � ���������� ��������� ��� �������� ���������� � ������.
	get_m_Device()->set_m_CacheNotify((CLocalNotify*)this);
	m_dwChangeLogCicleCount=0;
	//�������� �������� �� �����������
//	NotifyTagsSink();
/*#define		WM_INITPLUGIN	WM_USER+190	//������������� �������
#define		WM_ADDNOTIFYTOPLUGIN	WM_USER+191 //���������� ����� ��� �����������
#define		WM_UNINITPLUFIN	WM_USER+192//��������������� �������
*/	
	MSG msg;
   ::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE) ;

	Sleep(1);
   ::PostThreadMessage(get_m_ThreadID(),WM_INITPLUGIN,0,0);
	while(GetMessage(&msg,0,0,0))
	{
	   ::DispatchMessage(&msg);
	   switch(msg.message)
	   {
	   //case WM_UPDATETAGSNOW:
		  // OnUpdateNow(msg);
		  // break;
	   case WM_TIMER://������ ��� ������
		   OnTimerMessage(msg);
		   break;
	   case WM_TAGSUPDATED://����� �����������
		   OnNotify(msg);
		   break;
	   case WM_INITPLUGIN://������������� �������
		   OnInitPlugin(msg.lParam);
		   break;
	   case WM_ADDNOTIFYTOPLUGIN://�������� ����� ���� �� �����������
		   OnAddNotifyPlugin(msg.lParam,msg.wParam);
		   break;
	   case WM_UNINITPLUGIN://��������������� �������
		   OnUninitPlugin();
		   break;
	   case WM_OPC_SYNCREAD://���������� ������ ��� ��������
		   OnDeviceReadSync((_SyncIORMsg*)msg.lParam);
		   break;
	   case WM_OPC_ASYNCREAD://����������� ������ ��� ��������
		   OnDeviceReadAsync((_AsyncIORWMsg*)msg.lParam);
		   break;
	   case WM_OPC_SYNCWRITE://���������� ������
		   OnDeviceWriteSync((_SyncIORMsg*)msg.lParam);
		   break;
	   case WM_OPC_ASYNCWRITE:	//����������� ������ ��� ��������
		   OnDeviceWriteAsync((_AsyncIORWMsg*)msg.lParam);
		   break;
	   case WM_OPC_READCACHE://������ �� ���� (������������ ����������� ������� ��� ������)
			
		   break;
	   case WM_MAPPER_WRITENOW://������ (������������ ��� ���������� ������ �� ������ ������ � ������)
		   break;
	   }
	 }
	get_m_Device()->DeinitializePlugin();
	StopTimer();
	delete m_pUpdateNowMsg2;
	CoUninitialize();
	return 0;
 }

// Class CHandlerBase 





CHandlerBase::CHandlerBase() : m_TimerID(0),m_ClockRate(100)
{
}

CHandlerBase::~CHandlerBase()
{
}
//
//DWORD CHandlerBase::fbody ()
//{
//	return 0;
//}

//BOOL CHandlerBase::UpdateNow (_UpdateMsg* UpdateNowMsg)
//{
// 	PostThreadMessage(get_m_ThreadID(),WM_UPDATETAGSNOW,0,(long)UpdateNowMsg);
//	return TRUE;
//}

BOOL CHandlerBase::StartTimer (DWORD ClockRate)
{
	if (!ClockRate)
		m_TimerID=SetTimer(NULL,1,m_ClockRate,NULL);
	else
		m_TimerID=SetTimer(NULL,1,ClockRate,NULL);
	return (BOOL)m_TimerID;
}

BOOL CHandlerBase::StopTimer ()
{
	return KillTimer(NULL,m_TimerID);
}

//
//CExternalInfoHandler::CExternalInfoHandler()
//{
//}
//
//CExternalInfoHandler::~CExternalInfoHandler()
//{
//}
//
//DWORD CExternalInfoHandler::fbody ()
//{
//	return S_OK;
//}
//
//HRESULT CExternalInfoHandler::GetItemIDs (OPCBROWSETYPE Type, DWORD* pCount, LPWSTR* pItemNames)
//{
//	return S_OK;
//}
//
//HRESULT CExternalInfoHandler::GetAllIDs (LPWSTR* pItemNames, DWORD* pCount)
//{
//	return S_OK;
//}
//
//HRESULT CExternalInfoHandler::GetSet2Properties ()
//{
//	return S_OK;
//}

//
//HRESULT CCacheUpdateHandler::NotifyTagsSink()
//{// TODO: ����� ������� ������
//	//����� ������ �� ���� ����� ������
//	m_TagStorage->m_ChangeMapCS.Lock();
//	HRESULT hr;
//	try{
//	
//	std::hash_map<DWORD,CTag*>::iterator itm;
//	std::list<CTag*>::iterator itl;
//	std::list<CTag*> Taglist;
//	//������� - ����� ���� ����� �������� � ���.
//	for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
//		//���� ������ - ��������...
//		if(itm->second->get_m_Active() )
//			Taglist.insert(Taglist.end(),itm->second);
//
//	if (Taglist.size()==0)
//	{
//		m_TagStorage->m_ChangeMapCS.Unlock();
//		return S_OK;
//	}
//
//	_TagID* pItemID = new _TagID[Taglist.size()];
//
//	HRESULT* pErrors=NULL;
//	DWORD dwCount=0;
//	for (itl=Taglist.begin();itl!= Taglist.end();++itl,dwCount++)
//		pItemID[dwCount]=**itl;
//	
//
//	hr=get_m_Device()->AddTagsNotify(pItemID,dwCount,0,&pErrors);
//	CoTaskMemFree(pErrors);
//	delete[] pItemID;
//
//	}catch(...)
//	{
//		m_LogFile<<"Error in method NotifyTagsSink cache";
//	}
//	m_TagStorage->m_ChangeMapCS.Unlock();
//	return hr;
//
//}

//void CCacheUpdateHandler::Send_AsyncRead(_AsyncIORWMsg *mes)
//{
//	PostThreadMessage(get_m_ThreadID(),WM_OPC_ASYNCREAD,0,(long)mes);
//}
//
//void CCacheUpdateHandler::OnAsyncRead(MSG mes)
//{
//  //����� ��������� ��������� � ��������� ������?
//	CAsyncReadThread * pATh=new CAsyncReadThread;
//	
//	pATh->dwTransactionID = ((_AsyncIORWMsg*)mes.lParam)->get_m_TransactionID();
//	pATh->pMsg= (_AsyncIORWMsg*)mes.lParam;
//	pATh->m_Owner = this;
//	
//	m_AsyncList.insert(m_AsyncList.end(),pATh);
//	pATh->run();
//	//��� ���������� �������� �� update �����.
//}

//DWORD CCacheUpdateHandler::CAsyncReadThread::fbody()
//{// TODO: ����� ������� ������
//	Active=true;
//	//����� ��������� ��������������� ������ ����� (�� ����������).
//
//	_UpdateNowMsg2 * pUpdateNowMsg2=new _UpdateNowMsg2();
//	
//	//���� ����, ������� ������� ������
//	std::hash_map<DWORD,CTag*>::iterator itm;
//	std::list<CTag*>::iterator itl;
//	std::list<CTag*> Taglist;
////	_TagID MyID;
//
//	for (int Mi=0;Mi<pMsg->m_dwNumItems;Mi++)
//	{
//		//MyID.set_m_hObjectHandle(*(pMsg->m_phServerHandle+Mi));
//		itm=m_Owner->m_TagStorage->TMap.find(*(pMsg->m_phServerHandle+Mi));
//		if (itm!=m_Owner->m_TagStorage->TMap.end())
//		{
//		//	if (itm->second->get_m_AccessRights()&(DWORD)OPC_READABLE)
//				Taglist.insert(Taglist.end(),itm->second);
//		}
//	}
//
//	//������� ������, ����� ������ ���� ��� ������ ������.
//	pUpdateNowMsg2->dwCount=Taglist.size();
//	pUpdateNowMsg2->phClient=new _TagID[pMsg->m_dwNumItems];
//	pUpdateNowMsg2->pItemState=NULL;
//	long count;
//	for(itl=Taglist.begin(), count=0;itl!=Taglist.end();++itl,count++)
//		*(pUpdateNowMsg2->phClient+count)=**itl;
//
//	Taglist.clear();
//	//� ������ ����� ������ � ���������.
//	HRESULT hr=S_OK;
//	if(pUpdateNowMsg2->dwCount>0)
//	{
//		hr=m_Owner->get_m_Device()->GetTagsData(pUpdateNowMsg2);
//		if (SUCCEEDED(hr))
//		{
//			//�������� ������������ ���������
//			pMsg->m_pErrors = (HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*(pUpdateNowMsg2->dwCount));
//			pMsg->pvValues = (VARIANT*) CoTaskMemAlloc(sizeof(VARIANT)*(pUpdateNowMsg2->dwCount));
//			pMsg->pwQualities = (WORD*) CoTaskMemAlloc(sizeof(WORD)*(pUpdateNowMsg2->dwCount));
//			pMsg->pftTimeStamps = (FILETIME*) CoTaskMemAlloc(sizeof(FILETIME)*(pUpdateNowMsg2->dwCount));
//
//			for (int MyY=0;MyY<pUpdateNowMsg2->dwCount;MyY++)
//			{
//				for(int MyI=0;MyI<pUpdateNowMsg2->dwCount;MyI++)
//				{
//					if (*(pMsg->m_phServerHandle+MyI)==(pUpdateNowMsg2->phClient+MyY)->get_m_hObjectHandle())
//					{
//						VariantInit(pMsg->pvValues+MyI);
//						if (SUCCEEDED(*(pUpdateNowMsg2->pErrors+MyY)))
//						{
//							VariantCopy(pMsg->pvValues+MyI,&(pUpdateNowMsg2->pItemState+MyY)->vDataValue);
//							*(pMsg->pwQualities+MyI)=(pUpdateNowMsg2->pItemState+MyY)->wQuality;
//							*(pMsg->pftTimeStamps+MyI)=(pUpdateNowMsg2->pItemState+MyY)->ftTimeStamp;
//						}
//							*(pMsg->m_pErrors+MyI)=*(pUpdateNowMsg2->pErrors+MyY);
//						VariantClear(&(pUpdateNowMsg2->pItemState+MyY)->vDataValue);
//						break;
//					}
//				}
//
//			}
//
//		}
//
//		//������������ ������
//		ATLTRACE("�������� �� %d\n",(DWORD)pUpdateNowMsg2->pItemState);
//		if (pUpdateNowMsg2->pItemState) {
//			CoTaskMemFree(pUpdateNowMsg2->pItemState);
//			pUpdateNowMsg2->pItemState=NULL;
//		}
//		if (pUpdateNowMsg2->pErrors){
//			CoTaskMemFree(pUpdateNowMsg2->pErrors);
//			pUpdateNowMsg2->pErrors=NULL;
//		}
//		delete pUpdateNowMsg2;
//	}
//
//	PostThreadMessage(pMsg->m_DestThreadID,WM_CONTROLTHREAD_TRANSACTION_COMPLITE_READ,0,(long)pMsg);
//	Active=false;
//	m_Owner->Send_ClearAsync(dwTransactionID);
//	return 0;
//}
//
//void CCacheUpdateHandler::Send_ClearAsync(DWORD dwTID)
//{
//	PostThreadMessage(this->get_m_ThreadID(),WM_HANDLER_CLEAR_ASYNC,0,(long)dwTID);
//}
//
//void CCacheUpdateHandler::OnClearAsync(DWORD dwTID)
//{//������� � �������
//		ATLTRACE("����� OnClearAsync\n");
//	std::list<CAsyncReadThread*>::iterator itl;
//	for(itl=m_AsyncList.begin();itl!=m_AsyncList.end();++itl)
//	{
//		if ((*itl)->dwTransactionID=dwTID)
//		{
//			delete *itl;
//			m_AsyncList.erase(itl);
//			break;
//		}
//	}
//}

void CCacheUpdateHandler::OnInitPlugin(DWORD lParam)
{
	HRESULT hr=get_m_Device()->InitializePlugin("");
	if (FAILED(hr))
	{
		m_LogFile.ChangeMode();
		m_LogFile<<hr;
		m_LogFile<<"������ ��� ������������� �������";
		m_LogFile.ChangeMode();
	}
	else
	{
		m_LogFile<<"����������� ������������� �������.";
		
		//��������� ������ ��� ���������� � �������������� ����
		if (!m_TagStorage->m_NotifyTagList.empty())
		{ //���� ���� ���� � ����������� �� �����������
			_TagID * pTagID = new _TagID[m_TagStorage->m_NotifyTagList.size()];
		
			DWORD dwMinUpdateRate=0;
			//������ �������� ���������...
			//�� ���� �� ���� ��������� ������
			std::list<_TagID>::iterator iterList;
			int inty=0;
			for(iterList=m_TagStorage->m_NotifyTagList.begin();iterList!=m_TagStorage->m_NotifyTagList.end();++iterList)
			{
				*(pTagID+inty)=*iterList;
				inty++;
			}

			//����� �������� ��������� � ���������� �� ������
			::PostThreadMessage(get_m_ThreadID(),WM_ADDNOTIFYTOPLUGIN,inty,(DWORD)pTagID);
		}
	}
}

void CCacheUpdateHandler::OnAddNotifyPlugin(DWORD lParam,DWORD wParam)
{
	HRESULT hr=S_OK;
	HRESULT *pErrrr=NULL;

	hr=get_m_Device()->AddTagsNotify((_TagID*)lParam,wParam,0,&pErrrr);
	
	if (SUCCEEDED(hr))
	{
		m_NotifyAdded=true;
		m_LogFile<<"���������� ����� �� ����������� ������ �������!";
		if(pErrrr)
			CoTaskMemFree(pErrrr);
	}
	else
	{
		m_LogFile<<"Error: ������ ��� ���������� ����� �� �����������!";
	}
	
	delete[] (_TagID*)lParam;

}

void CCacheUpdateHandler::OnUninitPlugin()
{
	m_LogFile<<"���������������� ������";
	get_m_Device()->DeinitializePlugin();
	m_LogFile<<"������������������ ������";
}

// ������� �� ��������� WM_OPC_SYNCREAD
void CCacheUpdateHandler::OnDeviceReadSync(_SyncIORMsg* mes)
{
	mes->m_ppItemValues=(OPCITEMSTATE*)CoTaskMemAlloc(sizeof(OPCITEMSTATE)*mes->m_dwNumItems);
	mes->m_pErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*mes->m_dwNumItems);

	try{
	
	_TAGMAP::iterator itm;
	for(UINT i=0;i<mes->m_dwNumItems;i++)
	{
		itm=m_TagStorage->TMap.find(*(mes->m_phServerHandle+i));
		if (itm!=m_TagStorage->TMap.end())
		{
			*(mes->m_pErrors+i)=itm->second->get_pOPCITEMSTATE((mes->m_ppItemValues+i));
		}else
		{
			VariantInit(&(mes->m_ppItemValues+i)->vDataValue);
			*(mes->m_pErrors+i)=OPC_E_INVALIDHANDLE;
		}
	}
	}catch(...)
	{
		m_LogFile<<"Error in method OnSyncRead of channel";
	}
	mes->SetReady();
	return;
}

// ������� �� WM_OPC_ASYNCREAD
void CCacheUpdateHandler::OnDeviceReadAsync(_AsyncIORWMsg* mes)
{
//����� ��� � ��������� ���������� ����� ������
	mes->pvValues=(VARIANT*)CoTaskMemAlloc(sizeof(VARIANT)*mes->m_dwNumItems);
	mes->m_pErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*mes->m_dwNumItems);
	mes->pwQualities = (WORD*) CoTaskMemAlloc(sizeof(WORD)*mes->m_dwNumItems);
	mes->pftTimeStamps = (FILETIME*) CoTaskMemAlloc(sizeof(FILETIME)*mes->m_dwNumItems);

	try{
	
	_TAGMAP::iterator itm;
	for(UINT i=0;i<mes->m_dwNumItems;i++)
	{
		itm=m_TagStorage->TMap.find(*(mes->m_phServerHandle+i));

		//_variant_t xxx;

		VariantInit(mes->pvValues+i);
		if (itm!=m_TagStorage->TMap.end())
		{
			itm->second->ReadBaseValues(*(mes->pvValues+i),*(mes->pwQualities+i),*(mes->m_pErrors+i),*(mes->pftTimeStamps+i));
		}else
		{
			*(mes->m_pErrors+i)=OPC_E_INVALIDHANDLE;
		}
		//*(mes->pvValues+i)=xxx.Detach();
	}

	}catch(...)
	{
		m_LogFile<<"Error in method OnAsyncRead of channel";
	}
	mes->SetReady();
}

// ������� �� ��������� WM_OPC_SYNWRITE
void CCacheUpdateHandler::OnDeviceWriteSync(_SyncIORMsg * mes)
{
	mes->m_pErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*mes->m_dwNumItems);
	try{
		DeviceWrite(mes->m_dwNumItems,mes->m_phServerHandle,mes->m_pItemValues,mes->m_pErrors);	
	}catch(...)
	{
		m_LogFile<<"Error in method OnSyncWrite";
	}
	mes->SetReady();
}

// ������� �� WM_OPC_ASYNCWRITE
void CCacheUpdateHandler::OnDeviceWriteAsync(_AsyncIORWMsg* mes)
{
//����� ��� � ��������� ���������� ����� ������
	mes->m_pErrors=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*mes->m_dwNumItems);
	try{
		DeviceWrite(mes->m_dwNumItems,mes->m_phServerHandle,mes->m_pItemValues,mes->m_pErrors);
	}catch(...)
	{
		m_LogFile<<"Error in method InAsyncWrite of channel";
	}
	mes->SetReady();
}
HRESULT CCacheUpdateHandler::DeviceWrite(DWORD xCount,OPCHANDLE *pH,VARIANT *pV,HRESULT *pE)
{
	if (!xCount) return S_OK;//���� ������ ��� - �������

	HRESULT hr;
	_UpdateNowMsg pUpdateNowMsg;
	try
	{
	
		stdext::hash_map<DWORD,CTag*>::iterator itm;
		std::list<CTag*>::iterator itl;
		std::list<CTag*> Taglist;

		CCacheUpdateHandler::ArrayMap *pM=new ArrayMap[xCount];//��� ���������

		
		//������ ��������
		pUpdateNowMsg.dwCount=Taglist.size();
		//�������� ����� ��� ������ ���������������(�� ������������� �����)
		pUpdateNowMsg.phClient=new _TagID*[xCount];
		pUpdateNowMsg.pErrors=NULL;
		pUpdateNowMsg.pvValues = (VARIANT*)CoTaskMemAlloc(sizeof(VARIANT)*xCount);

		
		//��������� ������ ������������ �����
		ULONG yCount=0;
		for(UINT i=0;i<xCount;i++)
		{
			itm=m_TagStorage->TMap.find(*(pH+i));
			if (itm!=m_TagStorage->TMap.end())
			{
				if ((itm->second->get_m_AccessRights()&OPC_WRITEABLE)==0)
				{
					*(pE+i)=OPC_E_BADRIGHTS;
					continue;
				}

				(pM+yCount)->left=i;
				(pM+yCount)->right=yCount;
				Taglist.insert(Taglist.end(),itm->second);
				*(pUpdateNowMsg.phClient+yCount)=(_TagID*)itm->second;
				VariantInit(pUpdateNowMsg.pvValues+yCount);
				VariantCopy(pUpdateNowMsg.pvValues+yCount,pV+i);
				yCount++;
			}
			else
			{
				*(pE+i)=OPC_E_INVALIDHANDLE;
			}
		}

		pUpdateNowMsg.dwCount=yCount;
		if (pUpdateNowMsg.dwCount==0)
		{
			delete[] pM;
			CoTaskMemFree(pUpdateNowMsg.pvValues);
			return S_FALSE;
		}

		hr=S_OK;
		hr=get_m_Device()->SetTagsData(&pUpdateNowMsg);
		//������������ ���������� ������
		if (SUCCEEDED(hr))
		{
			//������� ��� ����
			FILETIME MyFT;
			GetSystemTimeAsFileTime(&MyFT);	
			for(ULONG xx=0;xx<pUpdateNowMsg.dwCount;xx++)
			{	//��������� ���������.
				OPCITEMSTATE St;
				VariantInit(&St.vDataValue);
				VariantCopy(&St.vDataValue,pUpdateNowMsg.pvValues+xx);
				St.ftTimeStamp=MyFT;
				((CTag*)*(pUpdateNowMsg.phClient+xx))->WriteNewValue(&St,pUpdateNowMsg.pErrors+xx);
				VariantClear(pUpdateNowMsg.pvValues+xx);
				*(pE+(pM+xx)->left)=*(pUpdateNowMsg.pErrors+xx);
			}

			if (pUpdateNowMsg.pErrors)
			{
				CoTaskMemFree(pUpdateNowMsg.pErrors);
				pUpdateNowMsg.pErrors=NULL;
			}
			if (pUpdateNowMsg.pvValues)
			{
				CoTaskMemFree(pUpdateNowMsg.pvValues);
				pUpdateNowMsg.pvValues=NULL;
			}
		}
	}catch(...)
	{
		m_LogFile<<"Error in method OnTimer Device";
	}
return hr;
}
// ������ �� ����������
HRESULT CCacheUpdateHandler::DeviceRead(void)
{

///////////////////////////////////////////////////////////////////////////////
	try{
	HRESULT hr;
	_UpdateNowMsg2 pUpdateNowMsg2;
	DWORD xCount;
	OPCHANDLE *pH;
	OPCITEMSTATE *pSt;
	HRESULT *pE;
	//���� ����, ������� ������� ������
	stdext::hash_map<DWORD,CTag*>::iterator itm;
	std::list<CTag*>::iterator itl;
	std::list<CTag*> Taglist;
	CCacheUpdateHandler::ArrayMap *pM=new ArrayMap[xCount];//��� ���������
	//������� ������ ��� ��������� ITEMID ��� ���� ������ � �����.
	//pUpdateNowMsg2.m_ItemDef = (ITEMID*)CoTaskMemAlloc(sizeof(ITEMID)*m_TagStorage->TMap.size());

	//������� �� ���������
	pUpdateNowMsg2.phClient	= new _TagID*[xCount];
	pUpdateNowMsg2.m_ItemDef = NULL;

	//������� - ����� ���� ����� �������� � ����������.
	DWORD ItCount=0;
	//for(itm=m_TagStorage->TMap.begin();itm!=m_TagStorage->TMap.end();++itm)
	for (ULONG xx=0;xx<xCount;xx++)
	{
		itm=m_TagStorage->TMap.find(*(pH+xx));
		if (itm!=m_TagStorage->TMap.end())
		{
			if ((itm->second->get_m_AccessRights()&OPC_READABLE)==0)
			{
				*(pE+xx)=OPC_E_BADRIGHTS;
				continue;
			}
			(pM+ItCount)->left=xx;
			(pM+ItCount)->right=ItCount;
			*(pUpdateNowMsg2.phClient+ItCount)=(CTag*)itm->second;
			ItCount++;
		}
		else
		{//���� �� ������
			*(pE+xx)=OPC_E_INVALIDHANDLE;
		}
	}
	if (!ItCount) 
	{
		//delete pUpdateNowMsg2;
		return S_OK;
	}
	//������� ������, ����� ������ ���� ��� ������ ������.
	pUpdateNowMsg2.dwCount=ItCount;
	//pUpdateNowMsg2.phClient=NULL;
	pUpdateNowMsg2.pItemState=NULL;
	pUpdateNowMsg2.pErrors=NULL;
	//� ������ ����� ������ � ���������.
	hr=S_OK;
	hr=get_m_Device()->GetTagsData(&pUpdateNowMsg2);
	
	if (SUCCEEDED(hr))
	{
		for(ULONG i=0;i<pUpdateNowMsg2.dwCount;i++)
		{
		//	itm=m_TagStorage->TMap.find((pUpdateNowMsg2.m_ItemDef+i)->hClient);
		//	if (itm!=m_TagStorage->TMap.end())
		//	{
			//����������� ��������, �������� � ����� ��������� ����.
			//���� �������� ���� ���� �������� �������� - ����� �������� �� �������.
			//���������� �� ������ ��� �������� - ��� � �������!!!!!
			try{
				if (SUCCEEDED(/*itm->second->*/((CTag*)*(pUpdateNowMsg2.phClient+i))->WriteNewValue(pUpdateNowMsg2.pItemState+i,pUpdateNowMsg2.pErrors+i)))
				//���� TRUE -  �������� � � ��� ��������
				{
				//	Taglist.insert(Taglist.end(),itm->second);

					//����� �������
					//((CTag*)*(pUpdateNowMsg2.phClient+i))->
					
				}
				else
				{//����� ������� ������
					*(pE+(pM+i)->left)=((CTag*)*(pUpdateNowMsg2.phClient+i))->get_m_LastHRESULT();
				}
			}catch(...)
			{
				m_LogFile<<"ERROR: �������������� ������ � CCacheUpdateHandler::OnTimerMessage() WriteNewValue()!!!";
			}
		//	}
		//	else{
		//		VariantClear(&(pUpdateNowMsg2.pItemState+i)->vDataValue);
		//	}
			//������� ITEMID
			SysFreeString((pUpdateNowMsg2.m_ItemDef+i)->ItemName);
		}
	}
	else //���� �������� ������ ������
	{
		m_LogFile<<"ERROR: ��������� ������ ����� � ��acheUpdateHandler::OnTimerMessage!!!";
		m_LogFile<<hr;
		//������������� Quality � OPC_QUALITY_LAST_KNOWN
		for(ULONG ii=0;ii<pUpdateNowMsg2.dwCount;ii++)
		{
				((CTag*)*(pUpdateNowMsg2.phClient+ii))->set_m_wQuality(OPC_QUALITY_LAST_KNOWN);
				SysFreeString((pUpdateNowMsg2.m_ItemDef+ii)->ItemName);
				//������� �� �� ����� �������
		}
	}
	if (Taglist.size())
	{
		//���������� ��������� ��� �����������
/*			_UpdateMsg * pUpdateMsg = new _UpdateMsg();//�������� ����� ������������ � ������� ������
		pUpdateMsg->dwCount=Taglist.size();
		pUpdateMsg->phClient=new _TagID[pUpdateMsg->dwCount];
		
		for(itl=Taglist.begin(),count=0;itl!=Taglist.end();++itl,count++)
			*(pUpdateMsg->phClient+count)=**itl;
		
		//����������� ������ �� ����������
	//	ATLTRACE("������ ����������� �� ����-�� �� ��������� ����� \n");
		if (SUCCEEDED(hr))
			TagsUpdated(pUpdateMsg);*/
	}
	//������������ ������

	
	if (pUpdateNowMsg2.pItemState) {
		CoTaskMemFree(pUpdateNowMsg2.pItemState);
		pUpdateNowMsg2.pItemState=NULL;
	}
	if (pUpdateNowMsg2.pErrors)
	{
		CoTaskMemFree(pUpdateNowMsg2.pErrors);
		pUpdateNowMsg2.pErrors=NULL;
	}



	}catch(...)
	{
		m_LogFile<<"ERROR: �������������� ������ � CCacheUpdateHandler::OnTimerMessage()!!!";
	}

	return E_NOTIMPL;
}

//DEL void CCacheUpdateHandler::Stop()
//DEL {
//DEL //	
//DEL 	CHandlerBase::Stop();
//DEL }
