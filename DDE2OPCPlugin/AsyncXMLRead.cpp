#include "stdafx.h"
#include ".\asyncxmlread.h"
#include <comdef.h>

CAsyncXMLRead::CAsyncXMLRead(std::string EventName)
{
	th_log.SetNewFullLogName("c:\\OPC2XML_THREAD.log");
	m_EventName =EventName;
	//th_log<<"��������������� ����� ��������� ������";
	EventMy=CreateEvent(NULL,TRUE,FALSE,m_EventName.c_str());
	//th_log<<"��������������� ����� �������� ������";
	m_bReady=false;
//	ResetEvent(EventMy);
}

CAsyncXMLRead::~CAsyncXMLRead(void)
{
	if (EventMy)
	{
		::CloseHandle(EventMy);
		EventMy=0;
	}
	this->Stop();
}

// ��������� ������� ���������
long CAsyncXMLRead::getStatus(void)
{
	::PostThreadMessage(this->get_m_ThreadID(),WM_STATUSDOCUMENT,0,0);
	return 0;
}

// ���������� �������� �������� ���������
HRESULT CAsyncXMLRead::Abort(void)
{
	::PostThreadMessage(this->get_m_ThreadID(),WM_ABORTDOCUMENT,0,0);
	return S_OK;
}
DWORD CAsyncXMLRead::fbody()
{
   CoInitializeEx(NULL,COINIT_MULTITHREADED); //� ���
   {
	   m_loadedXML=NULL;
	   try{
	  MSXML2::IXMLDOMDocumentPtr xxxDD;

	try{
	//th_log<<"��������������� ����� CreateInstance";

	xxxDD.CreateInstance("msxml2.domdocument");
	//th_log<<"��������������� ����� CreateInstance";
	xxxDD->async=VARIANT_TRUE;
	}catch(...)
	{
		m_ErrorString="ERROR: �� ���� ������� ������ ������� MSXMLDomdocument!";
		th_log<<"ERROR: �� ���� ������� ������ ������� MSXMLDomdocument!";
		CoUninitialize();
		if (EventMy)
		{
			CloseHandle(EventMy);
			EventMy=0;
		}
		return 0;
	}

	m_Loading=false;
	try{
	MSG msg;
     ::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE) ;
	 m_bReady=true;
	while(GetMessage(&msg,0,0,0))
	{
	   ::DispatchMessage(&msg);
	   switch(msg.message)
	   {
	   case WM_TIMER:
		   //m_pOwner->m_LogFile<<"����� OnTimer";
		   //OnTimerMessage(msg);
		   if (m_Loading)//���� ����������� - �������� ���������
		   {
			   //��������
	//		    th_log<<"����� ��������� ���������";
				xxxDD->get_readyState(&m_CurrentState);
	//			 th_log<<"����� �������� ���������";
			//	printf("Result=%d\n",m_CurrentState);
				if(m_CurrentState==4)
				{
	//				th_log<<"���������=4";
					HRESULT hhr=xxxDD->get_xml(&m_loadedXML);
					if (FAILED(hhr))
						_com_issue_error(hhr);
					KillTimer(NULL,dwTimerID);
					SetEvent(EventMy);
					m_Loading=FALSE;
	//				th_log<<"���������=4";
				}			   
		   }
		   break;
	   case WM_LOADNEWDOCUMENT: //����� �����!
		   if (m_Loading) //���� ��� ����������� - 
				break;
		   ResetEvent(EventMy);
	//	   th_log<<"����� load";
		   xxxDD->load(m_url.c_str());
	//	   th_log<<"����� load";
		   dwTimerID=SetTimer(NULL,1,50,0);
		   m_Loading=true;
		   break;
	   case WM_ABORTDOCUMENT: //������, ��������� ���!
		   //���������� ������� �������
		    th_log<<"Abort before";
		   KillTimer(NULL,dwTimerID);
		   xxxDD->abort();
		   th_log<<"Abort after";
		   break;
	   }
	 }
	}catch(...)
	{
		ATLTRACE2("ERROR IN THREAD!!!");
	}
	KillTimer(NULL,dwTimerID);
		xxxDD.Release();
	if (m_loadedXML)
	{	SysFreeString(m_loadedXML);
		m_loadedXML=NULL;
	}

	   }catch(...)
	{
		th_log<<"ERROR: ERROR in thread. E_FAIL!";
	}

   }
//    th_log<<"Exit thread";
	if (EventMy)
	{
		CloseHandle(EventMy);
		EventMy=0;
	}
   	if (m_loadedXML)
	{	SysFreeString(m_loadedXML);
		m_loadedXML=NULL;
	}
   CoUninitialize();
	
	return 0;
}

int CAsyncXMLRead::LoadNew(void)
{
	::PostThreadMessage(this->get_m_ThreadID(),WM_LOADNEWDOCUMENT,0,0);
	return 0;
}
