//## begin module%1.2%.codegen_version preserve=yes
//	 Read the documentation to learn more about C++ code generator
//	 versioning.
//## end module%1.2%.codegen_version

//## begin module%3AB956900397.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AB956900397.cm

//## begin module%3AB956900397.cp preserve=no
//## end module%3AB956900397.cp

//## Module: CThread%3AB956900397; Pseudo Package body
//## Source file: D:\Prj\VC++\OPC\OPCImpl\CThread.cpp

//## begin module%3AB956900397.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3AB956900397.additionalIncludes

//## begin module%3AB956900397.includes preserve=yes
//## end module%3AB956900397.includes

// CThread
#include "CThread.h"
//## begin module%3AB956900397.additionalDeclarations preserve=yes
//## end module%3AB956900397.additionalDeclarations


// Class CThread 




CThread::CThread()
  //## begin CThread::CThread%3AB956900397_const.hasinit preserve=no
	  : m_ThreadID(0),
		m_ThreadHandle(0),
		m_Active(FALSE)
  //## end CThread::CThread%3AB956900397_const.hasinit
  //## begin CThread::CThread%3AB956900397_const.initialization preserve=yes
  //## end CThread::CThread%3AB956900397_const.initialization
{
  //## begin CThread::CThread%3AB956900397_const.body preserve=yes
  //## end CThread::CThread%3AB956900397_const.body
}

CThread::CThread(const CThread &right)
  //## begin CThread::CThread%3AB956900397_copy.hasinit preserve=no
	  : m_ThreadID(0),
		m_ThreadHandle(0),
		m_Active(FALSE)
  //## end CThread::CThread%3AB956900397_copy.hasinit
  //## begin CThread::CThread%3AB956900397_copy.initialization preserve=yes
  //## end CThread::CThread%3AB956900397_copy.initialization
{
  //## begin CThread::CThread%3AB956900397_copy.body preserve=yes
  //## end CThread::CThread%3AB956900397_copy.body
}


CThread::~CThread()
{
  //## begin CThread::~CThread%3AB956900397_dest.body preserve=yes
  //## end CThread::~CThread%3AB956900397_dest.body
}


CThread & CThread::operator=(const CThread &right)
{
  //## begin CThread::operator=%3AB956900397_assign.body preserve=yes
	return *this;
  //## end CThread::operator=%3AB956900397_assign.body
}



//## Other Operations (implementation)
DWORD WINAPI CThread::fbodyWrapper (void *pObject)
{
  //## begin CThread::fbodyWrapper%3AB9587A004D.body preserve=yes
  CThread * thread = (CThread *)pObject;
   DWORD rc=thread->fbody();

   ExitThread(0);
	return rc;
  //## end CThread::fbodyWrapper%3AB9587A004D.body
}

void CThread::run ()
{
  //## begin CThread::run%3AB958E60009.body preserve=yes
	if (m_ThreadHandle!=0) return;
/// ATLTRACE("Запуск потока обработчика \n");
	CThread *t = this;
	m_ThreadHandle=CreateThread(NULL,0,fbodyWrapper,t,0,&m_ThreadID);
  //## end CThread::run%3AB958E60009.body
}

void CThread::Stop ()
{
  //## begin CThread::Stop%3AB95A9A0356.body preserve=yes
	ATLTRACE("Останов потока обработчика \n");
 ::PostThreadMessage(CThread::m_ThreadID,WM_QUIT,0,0);
   WaitForSingleObject(m_ThreadHandle,12000);
   CloseHandle(m_ThreadHandle);
   m_ThreadHandle=0;
  //## end CThread::Stop%3AB95A9A0356.body
}

// Additional Declarations
  //## begin CThread%3AB956900397.declarations preserve=yes
  //## end CThread%3AB956900397.declarations

//## begin module%3AB956900397.epilog preserve=yes
//## end module%3AB956900397.epilog


// Detached code regions:
// WARNING: this code will be lost if code is regenerated.
#if 0
//## begin CThread::fbody%3AB957A40088.body preserve=no
 return 0;
//## end CThread::fbody%3AB957A40088.body

#endif
