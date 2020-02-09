#pragma once
#include "cthread.h"
#import "msxml3.dll" 
#include <string>
#include <comdef.h>
#include "SimpleLogFile.h"
#define WM_LOADNEWDOCUMENT  WM_USER+610
#define  WM_ABORTDOCUMENT WM_USER+611
#define  WM_STATUSDOCUMENT WM_USER+612

class CAsyncXMLRead :
	public CThread
{
private:
	bool m_Loading;//загружаем...
	bool m_bReady;
	CLogFile_CS th_log;
public:

	void run() //с анализом готовности
	{
		CThread::run();
		while (! m_bReady)
		{
			Sleep(10);
		}

	}

	HANDLE EventMy;
	DWORD dwTimerID;
	
	CAsyncXMLRead(std::string EventName);
	virtual ~CAsyncXMLRead(void);
	// Получение статуса документа
	long getStatus(void);
	// Прерывание операции загрузки документа
	HRESULT Abort(void);
	virtual DWORD fbody();
	std::string m_url;
	/*_bstr_t*/ BSTR m_loadedXML;
	std::string m_ErrorString;
	std::string m_EventName;
	long m_CurrentState;

	int LoadNew(void);
};
