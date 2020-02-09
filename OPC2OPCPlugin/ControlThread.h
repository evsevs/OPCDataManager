// ControlThread.h: interface for the CControlThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLTHREAD_H__9CD6CA1B_9236_4F98_A7DD_447A4992354A__INCLUDED_)
#define AFX_CONTROLTHREAD_H__9CD6CA1B_9236_4F98_A7DD_447A4992354A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CThread.h"

#define WM_OPC_REINIT (WM_USER+222)

template <class T>
class CControlThread : public CThread  
{
public:
CControlThread()
{
	m_pOwner=NULL;
	dwTimerID=0;
m_ServerStream=NULL;
m_GroupStream=NULL;
}
virtual ~CControlThread()
{
}
void OnTimerMessage(MSG msg);
virtual DWORD fbody ();
public:
	IStream * m_ServerStream;
	IStream * m_GroupStream;
	void SetOwner(T* pOwner)
	{
		m_pOwner=pOwner;
	}
private:
	DWORD dwTimerID;
	T * m_pOwner;
	DWORD m_ErrorCount;//счетчик ошибок получения статуса
	bool ChangeStateFlag;//флаг отлова перехода состояний
};
template < class T >
DWORD  CControlThread< T >::fbody ()
 {
	CoInitializeEx(NULL,COINIT_MULTITHREADED); //в МТА
   dwTimerID=SetTimer(NULL,1,m_pOwner->m_ControlThreadPeriod,0);

	MSG msg;
   ::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE) ;
	while(GetMessage(&msg,0,0,0))
	{
	   ::DispatchMessage(&msg);
	   switch(msg.message)
	   {
	   case WM_TIMER:
		   m_pOwner->m_LogFile<<"Перед OnTimer";
		   OnTimerMessage(msg);
		   break;
	   case WM_OPC_REINIT:
		  // KillTimer(NULL,dwTimerID);
		   ATLTRACE("ИМЕННО Переинициализация сервера ОРС\n");
		   m_pOwner->m_LogFile<<"Перед переинициализацией";
		  // m_pOwner->m_ConfigCS.Lock();
		   m_pOwner->ReInit();
		   m_pOwner->m_LogFile<<"После переинициализации";
		   //m_pOwner->m_ConfigCS.Unlock();
		   dwTimerID=SetTimer(NULL,1,m_pOwner->m_ControlThreadPeriod,0);					   

	   }
	 }
	KillTimer(NULL,dwTimerID);
	CoUninitialize();
	return 0;
 }

template < class T >
void CControlThread< T >::OnTimerMessage(MSG msg)
{
	KillTimer(NULL,dwTimerID);
	dwTimerID=SetTimer(NULL,1,m_pOwner->m_ControlThreadPeriod,0);
	DWORD dwState=0;
	if (!m_pOwner->bStatus)
	{
		::PostThreadMessage(get_m_ThreadID(),WM_OPC_REINIT,0,0);
		return;
	}
	m_pOwner->m_LogFile<<"Перед GetOPCServerState";
	HRESULT hr=m_pOwner->GetOPCServerState(dwState);
	m_pOwner->m_LogFile<<"После GetOPCServerState";
	if (SUCCEEDED(hr))
	{
		switch(dwState)
		{
		case OPC_STATUS_RUNNING:
			m_pOwner->m_LogFile<<"Running";
			m_pOwner->bStatus=true;
			m_ErrorCount=0;//обнуление
			if (ChangeStateFlag)
			{
				ChangeStateFlag=false;
				//подать сигнал о смене состояний
			}
			ChangeStateFlag=false;
			break;
		case OPC_STATUS_FAILED:
			m_pOwner->m_LogFile<<"Failed";
			m_ErrorCount++;//переконнект
			if (m_ErrorCount==m_pOwner->m_ControlThreadErCount)
			{
				m_pOwner->bStatus=false;
				::PostThreadMessage(get_m_ThreadID(),WM_OPC_REINIT,0,0);
			}

			break;
		case OPC_STATUS_NOCONFIG:
			m_pOwner->m_LogFile<<"NoConfig";
			ChangeStateFlag=true;
			break;
		case OPC_STATUS_SUSPENDED:
			m_pOwner->m_LogFile<<"Suspended";
			ChangeStateFlag=true;
			break;

		}
	}else
	{
		m_ErrorCount++;

		if (m_ErrorCount>=m_pOwner->m_ControlThreadErCount)
		{m_pOwner->m_LogFile<<"Превышено количество ошибок";
			m_pOwner->bStatus=false;
			//подать сигнал о переконнете самому себе
			ATLTRACE("Переинициализация сервера ОРС\n");
			::PostThreadMessage(get_m_ThreadID(),WM_OPC_REINIT,0,0);
		}

	}
	return;
}


#endif // !defined(AFX_CONTROLTHREAD_H__9CD6CA1B_9236_4F98_A7DD_447A4992354A__INCLUDED_)
