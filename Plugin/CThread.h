//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%3AB956900397.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3AB956900397.cm

//## begin module%3AB956900397.cp preserve=no
//	Файл создан 10.07.2001 12:37:54
//	Ерохин В.С.
//	ЗСМК, ИЦ АСУ ТП
//	к.415 т.1-14-26
//## end module%3AB956900397.cp

//## Module: CThread%3AB956900397; Pseudo Package specification
//## Source file: D:\Prj\VC++\OPC\OPCImpl\CThread.h

#ifndef CThread_h
#define CThread_h 1

//## begin module%3AB956900397.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3AB956900397.additionalIncludes

//## begin module%3AB956900397.includes preserve=yes
//## end module%3AB956900397.includes

//## begin module%3AB956900397.additionalDeclarations preserve=yes
//## end module%3AB956900397.additionalDeclarations


//## begin CThread%3AB956900397.preface preserve=yes
//## end CThread%3AB956900397.preface

//## Class: CThread%3AB956900397; Abstract
//	Абстарактный класс для работы с потоком.
//	Потомок для всех активных классов.
//	Требуется переопределение функции fbody.
//## Category: \316\341\371\350\351%3B29789801D2
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class CThread 
{
  //## begin CThread%3AB956900397.initialDeclarations preserve=yes
  //## end CThread%3AB956900397.initialDeclarations

  public:
    //## Constructors (generated)
      CThread();

      CThread(const CThread &right);

    //## Destructor (generated)
      ~CThread();

    //## Assignment Operation (generated)
      CThread & operator=(const CThread &right);


    //## Other Operations (specified)
      //## Operation: fbodyWrapper%3AB9587A004D
      static DWORD WINAPI fbodyWrapper (void *pObject);

      //## Operation: run%3AB958E60009
      void run ();

      //## Operation: Stop%3AB95A9A0356
      void Stop ();

    //## Get and Set Operations for Class Attributes (generated)

      //## Attribute: m_ThreadID%3AF2638B02FD
      //	Идентификатор потока. По идентификатору передаются
      //	сообщения.
      DWORD get_m_ThreadID ();

      //## Attribute: m_ThreadHandle%3AF263BC02C4
      //	Handle потока.
      //	Используется в ожидающих функциях, таких как WaitFor
      //	SingleObject.
      HANDLE get_m_ThreadHandle ();

      //## Attribute: m_Active%3AF2640902C4
      //	Флаг активности
      //	TRUE - активен.
      //	FALSE - НЕ активен.
      BOOL get_m_Active ();

    // Additional Public Declarations
      //## begin CThread%3AB956900397.public preserve=yes
      //## end CThread%3AB956900397.public

  protected:
    // Additional Protected Declarations
      //## begin CThread%3AB956900397.protected preserve=yes
      //## end CThread%3AB956900397.protected

  private:

    //## Other Operations (specified)
      //## Operation: fbody%3AB957A40088
      //	Операция представляет выполняемую в потоке функцию.
      virtual DWORD fbody () = 0;

    // Additional Private Declarations
      //## begin CThread%3AB956900397.private preserve=yes
      //## end CThread%3AB956900397.private

  private: //## implementation
    // Data Members for Class Attributes

      //## begin CThread::m_ThreadID%3AF2638B02FD.attr preserve=no  public: DWORD {U} 0
      DWORD m_ThreadID;
      //## end CThread::m_ThreadID%3AF2638B02FD.attr

      //## begin CThread::m_ThreadHandle%3AF263BC02C4.attr preserve=no  public: HANDLE {U} 0
      HANDLE m_ThreadHandle;
      //## end CThread::m_ThreadHandle%3AF263BC02C4.attr

      //## begin CThread::m_Active%3AF2640902C4.attr preserve=no  public: BOOL {U} FALSE
      BOOL m_Active;
      //## end CThread::m_Active%3AF2640902C4.attr

    // Additional Implementation Declarations
      //## begin CThread%3AB956900397.implementation preserve=yes
      //## end CThread%3AB956900397.implementation

};

//## begin CThread%3AB956900397.postscript preserve=yes
//## end CThread%3AB956900397.postscript

// Class CThread 

//## Get and Set Operations for Class Attributes (inline)

inline DWORD CThread::get_m_ThreadID ()
{
  //## begin CThread::get_m_ThreadID%3AF2638B02FD.get preserve=no
  return m_ThreadID;
  //## end CThread::get_m_ThreadID%3AF2638B02FD.get
}

inline HANDLE CThread::get_m_ThreadHandle ()
{
  //## begin CThread::get_m_ThreadHandle%3AF263BC02C4.get preserve=no
  return m_ThreadHandle;
  //## end CThread::get_m_ThreadHandle%3AF263BC02C4.get
}

inline BOOL CThread::get_m_Active ()
{
  //## begin CThread::get_m_Active%3AF2640902C4.get preserve=no
  return m_Active;
  //## end CThread::get_m_Active%3AF2640902C4.get
}

//## begin module%3AB956900397.epilog preserve=yes
//## end module%3AB956900397.epilog


#endif
