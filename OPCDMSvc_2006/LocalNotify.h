//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%3B441061021B.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B441061021B.cm

//## begin module%3B441061021B.cp preserve=no
//	Файл создан 18.07.2001 12:28:49
//	Ерохин В.С.
//	ЗСМК, ИЦ АСУ ТП
//	к.415 т.1-14-26
//## end module%3B441061021B.cp

//## Module: LocalNotify%3B441061021B; Package specification
//	Содержит класс для работы с нотификациями внутри канала.
//## Subsystem: <Top Level>
//## Source file: D:\Prj\VC++\OPC\OPCImpl\LocalNotify.h

#ifndef LocalNotify_h
#define LocalNotify_h 1

//## begin module%3B441061021B.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3B441061021B.additionalIncludes

//## begin module%3B441061021B.includes preserve=yes
//## end module%3B441061021B.includes

// _Message
#include "_Message.h"
//## begin module%3B441061021B.declarations preserve=no
//## end module%3B441061021B.declarations

//## begin module%3B441061021B.additionalDeclarations preserve=yes
//## end module%3B441061021B.additionalDeclarations


//## begin CLocalNotify%3B43EC8A0198.preface preserve=yes
//## end CLocalNotify%3B43EC8A0198.preface

//## Class: CLocalNotify%3B43EC8A0198; Abstract
//## Category: \300\321\304::DataManager::\312\340\355\340\353%3B40118B01FC
//## Subsystem: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

//## Uses: <unnamed>%3B4A947E035E;_UpdateMsg { -> }

class CLocalNotify 
{
  //## begin CLocalNotify%3B43EC8A0198.initialDeclarations preserve=yes
  //## end CLocalNotify%3B43EC8A0198.initialDeclarations

  public:

    //## Other Operations (specified)
      //## Operation: Send_OnTagUpdate%3B43ECB001CE
      virtual void Send_OnTagUpdate (_UpdateMsg* pUpdateMsg) = 0;
	
    // Additional Public Declarations
      //## begin CLocalNotify%3B43EC8A0198.public preserve=yes
      //## end CLocalNotify%3B43EC8A0198.public

  protected:
    // Additional Protected Declarations
      //## begin CLocalNotify%3B43EC8A0198.protected preserve=yes
      //## end CLocalNotify%3B43EC8A0198.protected

  private:
    // Additional Private Declarations
      //## begin CLocalNotify%3B43EC8A0198.private preserve=yes
      //## end CLocalNotify%3B43EC8A0198.private

  private: //## implementation
    // Additional Implementation Declarations
      //## begin CLocalNotify%3B43EC8A0198.implementation preserve=yes
      //## end CLocalNotify%3B43EC8A0198.implementation

};

//## begin CLocalNotify%3B43EC8A0198.postscript preserve=yes
//## end CLocalNotify%3B43EC8A0198.postscript

// Class CLocalNotify 

//## begin module%3B441061021B.epilog preserve=yes
//## end module%3B441061021B.epilog


#endif
