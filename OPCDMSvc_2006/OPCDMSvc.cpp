// OPCDMSvc.cpp : Implementation of WinMain


// Note: Proxy/Stub Information
//      To build a separate proxy/stub DLL, 
//      run nmake -f OPCDMSvcps.mk in the project directory.

#include "stdafx.h"
#include <stdlib.h>
#include "resource.h"
#include <initguid.h>
///**/#include "OPCDMSvc.h"

#include "OPCDMSvc_i.c"
#include "MyOPCSrv.h"
#include "OPCShutdownCP.h"
#include "MyTestConf.h"
#include "CChannelObj.h"
//#ifdef _DEBUG
////#include "stackwalker.h"
//#endif 
#include <stdio.h>

//CServiceModule _Module;

//BEGIN_OBJECT_MAP(ObjectMap)
//	OBJECT_ENTRY(CLSID_MyOPCSrv, CMyOPCSrv)
//	OBJECT_ENTRY(CLSID_MyTestConf, CMyTestConf)
//END_OBJECT_MAP()


//LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2)
//{
//    while (p1 != NULL && *p1 != NULL)
//    {
//        LPCTSTR p = p2;
//        while (p != NULL && *p != NULL)
//        {
//            if (*p1 == *p)
//                return CharNext(p1);
//            p = CharNext(p);
//        }
//        p1 = CharNext(p1);
//    }
//    return NULL;
//}
////////////////////////////////////////////////////////////NEW/////////////////////////////////////////////////////
////////////////////////////////////////////////////////////NEW/////////////////////////////////////////////////////
////////////////////////////////////////////////////////////NEW/////////////////////////////////////////////////////
////////////////////////////////////////////////////////////NEW/////////////////////////////////////////////////////
class CServiceModule : public CAtlServiceModuleT<CServiceModule, 
                                                 IDS_SERVICENAME>
{
public:
    DECLARE_LIBID(LIBID_OPCDMSVCLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_OPCDMSvc, 
                              "{E75BC663-1D39-11D6-8E8A-000000000000}")

    HRESULT PreMessageLoop(int nShowCmd)
	{
		CSecurityDescriptor sd;
		sd.InitializeFromThreadToken();
		HRESULT hr = CoInitializeSecurity(sd, -1, NULL, NULL,
	        RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
			ATLASSERT(SUCCEEDED(hr));


		hr=this->RegisterClassObjects(CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER, REGCLS_MULTIPLEUSE);
	    ATLASSERT(SUCCEEDED(hr));

		return S_OK;
	 }
    HRESULT PostMessageLoop()
	{
		HRESULT RevokeClassObjects();
		return S_OK;
	}
	void RegCat();
};

//CServiceModule _Module;
CServiceModule _AtlModule;
////////////////////////////////////////////////////////////NEW/////////////////////////////////////////////////////
////////////////////////////////////////////////////////////NEW/////////////////////////////////////////////////////
////////////////////////////////////////////////////////////NEW/////////////////////////////////////////////////////
////////////////////////////////////////////////////////////NEW/////////////////////////////////////////////////////
void CServiceModule::RegCat()
{
		USES_CONVERSION;
		CoInitializeEx(NULL,COINIT_MULTITHREADED);
   ICatRegister* pcr = NULL ;
    HRESULT hr = S_OK ;

    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
			NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
	if (FAILED(hr))
		return ;

    // Make sure the HKCR\Component Categories\{..catid...}
    // key is registered
    CATEGORYINFO catinfo[3];
    catinfo[0].catid = CATID_OPCDAServer10;
	catinfo[1].catid = CATID_OPCDAServer20;
	catinfo[2].catid = CATID_DataManagerPlugin;
    catinfo[0].lcid = 0x0409 ; // english
	catinfo[1].lcid = 0x0409 ; // english
	catinfo[2].lcid = 0x0409 ;

	// Make sure the provided description is not too long.
	// Only copy the first 127 characters if it is
	int len = wcslen(A2W("OPC Data Access Servers Version 1.0"));
	if (len>127)
		len = 127;
    wcsncpy(catinfo[0].szDescription, A2W("OPC Data Access Servers Version 1.0"), len);
	// Make sure the description is null terminated
	catinfo[0].szDescription[len] = '\0';

	len = wcslen(A2W("OPC Data Access Servers Version 2.0"));
	if (len>127)
		len = 127;
	wcsncpy(catinfo[1].szDescription,A2W("OPC Data Access Servers Version 2.0"), len);
	// Make sure the description is null terminated
	catinfo[1].szDescription[len] = '\0';

	len = wcslen(A2W("OPCDataManagerPlugin"));
	if (len>127)
		len = 127;
	wcsncpy(catinfo[2].szDescription,A2W("OPCDataManagerPlugin"), len);
	// Make sure the description is null terminated
	catinfo[2].szDescription[len] = '\0';

    hr = pcr->RegisterCategories(3, &catinfo[0]);
	pcr->Release();

	CoUninitialize();
	return ;

}
//// Although some of these functions are big they are declared inline since they are only used once
//
//inline HRESULT CServiceModule::RegisterServer(BOOL bRegTypeLib, BOOL bService)
//{
//    HRESULT hr = CoInitializeEx(NULL,COINIT_MULTITHREADED);
//    if (FAILED(hr))
//        return hr;
//
//    // Remove any previous service since it may point to
//    // the incorrect file
//    Uninstall();
//
//    // Add service entries
//    UpdateRegistryFromResource(IDR_OPCDMSvc, TRUE);
//
//    // Adjust the AppID for Local Server or Service
//    CRegKey keyAppID;
//    LONG lRes = keyAppID.Open(HKEY_CLASSES_ROOT, _T("AppID"), KEY_WRITE);
//    if (lRes != ERROR_SUCCESS)
//        return lRes;
//
//    CRegKey key;
//    lRes = key.Open(keyAppID, _T("{E75BC663-1D39-11D6-8E8A-000000000000}"), KEY_WRITE);
//    if (lRes != ERROR_SUCCESS)
//        return lRes;
//    key.DeleteValue(_T("LocalService"));
//    
//    if (bService)
//    {
//        key.SetValue(_T("OPCDMSvc"), _T("LocalService"));
//        key.SetValue(_T("-Service"), _T("ServiceParameters"));
//        // Create service
//        Install();
//    }
//
//    // Add object entries
//    hr = CComModule::RegisterServer(bRegTypeLib);
//
//    CoUninitialize();
//    return hr;
//}
//
//inline HRESULT CServiceModule::UnregisterServer()
//{
//    HRESULT hr = CoInitializeEx(NULL,COINIT_MULTITHREADED);
//    if (FAILED(hr))
//        return hr;
//
//    // Remove service entries
//    UpdateRegistryFromResource(IDR_OPCDMSvc, FALSE);
//    // Remove service
//    Uninstall();
//    // Remove object entries
//    CComModule::UnregisterServer(TRUE);
//    CoUninitialize();
//    return S_OK;
//}
//
//inline void CServiceModule::Init(_ATL_OBJMAP_ENTRY* p, HINSTANCE h, UINT nServiceNameID, const GUID* plibid)
//{
//    CComModule::Init(p, h, plibid);
//
//    m_bService = TRUE;
//
//    LoadString(h, nServiceNameID, m_szServiceName, sizeof(m_szServiceName) / sizeof(TCHAR));
//
//    // set up the initial service status 
//    m_hServiceStatus = NULL;
//    m_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
//    m_status.dwCurrentState = SERVICE_STOPPED;
//    m_status.dwControlsAccepted = SERVICE_ACCEPT_STOP;
//    m_status.dwWin32ExitCode = 0;
//    m_status.dwServiceSpecificExitCode = 0;
//    m_status.dwCheckPoint = 0;
//    m_status.dwWaitHint = 0;
//}
//
//LONG CServiceModule::Unlock()
//{
//    LONG l = CComModule::Unlock();
//    if (l == 0 && !m_bService)
//        PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
//    return l;
//}
//
//BOOL CServiceModule::IsInstalled()
//{
//    BOOL bResult = FALSE;
//
//    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
//
//    if (hSCM != NULL)
//    {
//        SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_QUERY_CONFIG);
//        if (hService != NULL)
//        {
//            bResult = TRUE;
//            ::CloseServiceHandle(hService);
//        }
//        ::CloseServiceHandle(hSCM);
//    }
//    return bResult;
//}
//
//inline BOOL CServiceModule::Install()
//{
//    if (IsInstalled())
//        return TRUE;
//
//    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
//    if (hSCM == NULL)
//    {
//        MessageBox(NULL, _T("Couldn't open service manager"), m_szServiceName, MB_OK);
//        return FALSE;
//    }
//
//    // Get the executable file path
//    TCHAR szFilePath[_MAX_PATH];
//    ::GetModuleFileName(NULL, szFilePath, _MAX_PATH);
//
//    SC_HANDLE hService = ::CreateService(
//        hSCM, m_szServiceName, m_szServiceName,
//        SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
//        SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
//        szFilePath, NULL, NULL, _T("RPCSS\0"), NULL, NULL);
//
//    if (hService == NULL)
//    {
//        ::CloseServiceHandle(hSCM);
//        MessageBox(NULL, _T("Couldn't create service"), m_szServiceName, MB_OK);
//        return FALSE;
//    }
//
//    ::CloseServiceHandle(hService);
//    ::CloseServiceHandle(hSCM);
//    return TRUE;
//}
//
//inline BOOL CServiceModule::Uninstall()
//{
//    if (!IsInstalled())
//        return TRUE;
//
//    SC_HANDLE hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
//
//    if (hSCM == NULL)
//    {
//        MessageBox(NULL, _T("Couldn't open service manager"), m_szServiceName, MB_OK);
//        return FALSE;
//    }
//
//    SC_HANDLE hService = ::OpenService(hSCM, m_szServiceName, SERVICE_STOP | DELETE);
//
//    if (hService == NULL)
//    {
//        ::CloseServiceHandle(hSCM);
//        MessageBox(NULL, _T("Couldn't open service"), m_szServiceName, MB_OK);
//        return FALSE;
//    }
//    SERVICE_STATUS status;
//    ::ControlService(hService, SERVICE_CONTROL_STOP, &status);
//
//    BOOL bDelete = ::DeleteService(hService);
//    ::CloseServiceHandle(hService);
//    ::CloseServiceHandle(hSCM);
//
//    if (bDelete)
//        return TRUE;
//
//    MessageBox(NULL, _T("Service could not be deleted"), m_szServiceName, MB_OK);
//    return FALSE;
//}
//
/////////////////////////////////////////////////////////////////////////////////////////
//// Logging functions
//void CServiceModule::LogEvent(LPCTSTR pFormat, ...)
//{
//    TCHAR    chMsg[256];
//    HANDLE  hEventSource;
//    LPTSTR  lpszStrings[1];
//    va_list pArg;
//
//    va_start(pArg, pFormat);
//    _vstprintf(chMsg, pFormat, pArg);
//    va_end(pArg);
//
//    lpszStrings[0] = chMsg;
//
//    if (m_bService)
//    {
//        /* Get a handle to use with ReportEvent(). */
//        hEventSource = RegisterEventSource(NULL, m_szServiceName);
//        if (hEventSource != NULL)
//        {
//            /* Write to event log. */
//            ReportEvent(hEventSource, EVENTLOG_INFORMATION_TYPE, 0, 0, NULL, 1, 0, (LPCTSTR*) &lpszStrings[0], NULL);
//            DeregisterEventSource(hEventSource);
//        }
//    }
//    else
//    {
//        // As we are not running as a service, just write the error to the console.
//        _putts(chMsg);
//    }
//}
//
////////////////////////////////////////////////////////////////////////////////////////////////
//// Service startup and registration
//inline void CServiceModule::Start()
//{
//    SERVICE_TABLE_ENTRY st[] =
//    {
//        { m_szServiceName, _ServiceMain },
//        { NULL, NULL }
//    };
//    if (m_bService && !::StartServiceCtrlDispatcher(st))
//    {
//        m_bService = FALSE;
//    }
//    if (m_bService == FALSE)
//        Run();
//}
//
//inline void CServiceModule::ServiceMain(DWORD /* dwArgc */, LPTSTR* /* lpszArgv */)
//{
//    // Register the control request handler
//    m_status.dwCurrentState = SERVICE_START_PENDING;
//    m_hServiceStatus = RegisterServiceCtrlHandler(m_szServiceName, _Handler);
//    if (m_hServiceStatus == NULL)
//    {
//        LogEvent(_T("Handler not installed"));
//        return;
//    }
//    SetServiceStatus(SERVICE_START_PENDING);
//
//    m_status.dwWin32ExitCode = S_OK;
//    m_status.dwCheckPoint = 0;
//    m_status.dwWaitHint = 0;
//
//    // When the Run function returns, the service has stopped.
//    Run();
//
//    SetServiceStatus(SERVICE_STOPPED);
//    LogEvent(_T("Service stopped"));
//}
//
//inline void CServiceModule::Handler(DWORD dwOpcode)
//{
//    switch (dwOpcode)
//    {
//    case SERVICE_CONTROL_STOP:
//        SetServiceStatus(SERVICE_STOP_PENDING);
//        PostThreadMessage(dwThreadID, WM_QUIT, 0, 0);
//        break;
//    case SERVICE_CONTROL_PAUSE:
//        break;
//    case SERVICE_CONTROL_CONTINUE:
//        break;
//    case SERVICE_CONTROL_INTERROGATE:
//        break;
//    case SERVICE_CONTROL_SHUTDOWN:
//        break;
//    default:
//        LogEvent(_T("Bad service request"));
//    }
//}
//
//void WINAPI CServiceModule::_ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
//{
//    _Module.ServiceMain(dwArgc, lpszArgv);
//}
//void WINAPI CServiceModule::_Handler(DWORD dwOpcode)
//{
//    _Module.Handler(dwOpcode); 
//}
//
//void CServiceModule::SetServiceStatus(DWORD dwState)
//{
//    m_status.dwCurrentState = dwState;
//    ::SetServiceStatus(m_hServiceStatus, &m_status);
//}
//
//void CServiceModule::Run()
//{
////	ConfObjectInitEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
//	USES_CONVERSION;
//    _Module.dwThreadID = GetCurrentThreadId();
//
////    HRESULT hr = CoInitialize(NULL);
////  If you are running on NT 4.0 or higher you can use the following call
////  instead to make the EXE free threaded.
////  This means that calls come in on a random RPC thread
//  HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
//
//    _ASSERTE(SUCCEEDED(hr));
//
//    // This provides a NULL DACL which will allow access to everyone.
//    CSecurityDescriptor sd;
//    sd.InitializeFromThreadToken();
//    hr = CoInitializeSecurity(sd, -1, NULL, NULL,
//        RPC_C_AUTHN_LEVEL_PKT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
//    _ASSERTE(SUCCEEDED(hr));
//
//    hr = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER | CLSCTX_REMOTE_SERVER, REGCLS_MULTIPLEUSE);
//	//hr = _Module.Re
//    _ASSERTE(SUCCEEDED(hr));
//	char ch[30];
//	LogEvent(_ltoa(hr,ch,10));
//
//    LogEvent(_T("Service started"));
//    if (m_bService)
//        SetServiceStatus(SERVICE_RUNNING);
//
//    MSG msg;
//    while (GetMessage(&msg, 0, 0, 0))
//        DispatchMessage(&msg);
//
//	std::list<CMyOPCSrv*>::iterator itl;
//	for(itl=OPCServersList.begin();itl!=OPCServersList.end();++itl)
//	{
//		(*itl)->Fire_ShutdownRequest(A2W("I need shutdown!!!!"));
//	}
//    _Module.RevokeClassObjects();
//
//    CoUninitialize();
//}

/////////////////////////////////////////////////////////////////////////////
//
extern "C" int WINAPI _tWinMain(HINSTANCE hInstance, 
    HINSTANCE /*hPrevInstance*/, LPTSTR lpCmdLine, int nShowCmd)
{
	//Beep(500,1000);

	  return _AtlModule.WinMain(nShowCmd);

//	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//
//	{ConfObjectInitEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
//   //ResetEvent(ConfObjectInitEvent);
//    lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT
////    _Module.Init(ObjectMap, hInstance, IDS_SERVICENAME, &LIBID_OPCDMSVCLib);
//    _Module.m_bService = TRUE;
//
//    TCHAR szTokens[] = _T("-/");
//
//    LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
//    while (lpszToken != NULL)
//    {
//     //   if (lstrcmpi(lpszToken, _T("UnregServer"))==0)
////            return _Module.UnregisterServer();
//
//        // Register as Local Server
//        if (lstrcmpi(lpszToken, _T("RegServer"))==0)
//		{
////			_Module.RegCat();
//            return _Module.RegisterServer(TRUE, FALSE);
//		}
//        
//        // Register as Service
//        if (lstrcmpi(lpszToken, _T("Service"))==0)
//		{
//		//	_Module.RegCat();
//            return _Module.RegisterServer(TRUE, NULL);
//		}
//        
//        lpszToken = FindOneOf(lpszToken, szTokens);
//    }
//
//    // Are we Service or Local Server
//    CRegKey keyAppID;
//    LONG lRes = keyAppID.Open(HKEY_CLASSES_ROOT, _T("AppID"), KEY_READ);
//    if (lRes != ERROR_SUCCESS)
//        return lRes;
//
//    CRegKey key;
//    lRes = key.Open(keyAppID, _T("{E75BC663-1D39-11D6-8E8A-000000000000}"), KEY_READ);
//    if (lRes != ERROR_SUCCESS)
//        return lRes;
//
//    TCHAR szValue[_MAX_PATH];
//    DWORD dwLen = _MAX_PATH;
//    lRes = key.QueryValue(szValue, _T("LocalService"), &dwLen);
//
//    _Module.m_bService = FALSE;
//    if (lRes == ERROR_SUCCESS)
//        _Module.m_bService = TRUE;
//
//    _Module.Start(0);
//	}
//    // When we get here, the service has been stopped
//    return _Module.m_status.dwWin32ExitCode;
}

