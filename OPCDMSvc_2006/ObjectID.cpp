//## begin module%1.2%.codegen_version preserve=yes
//   Read the documentation to learn more about C++ code generator
//   versioning.
//## end module%1.2%.codegen_version

//## begin module%3B3841330278.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B3841330278.cm

//## begin module%3B3841330278.cp preserve=no
//## end module%3B3841330278.cp

//## Module: ObjectID%3B3841330278; Package body
//## Subsystem: <Top Level>
//## Source file: D:\Prj\VC++\OPC\OPCImpl\ObjectID.cpp

//## begin module%3B3841330278.additionalIncludes preserve=no
#include "stdafx.h"
//## end module%3B3841330278.additionalIncludes

//## begin module%3B3841330278.includes preserve=yes
//## end module%3B3841330278.includes

// ObjectID
#include "ObjectID.h"
//## begin module%3B3841330278.declarations preserve=no
//## end module%3B3841330278.declarations

//## begin module%3B3841330278.additionalDeclarations preserve=yes
#include <time.h>
//## end module%3B3841330278.additionalDeclarations


// Class _ObjectID 



_ObjectID::_ObjectID()
  //## begin _ObjectID::_ObjectID%3B29956E0158_const.hasinit preserve=no
  //## end _ObjectID::_ObjectID%3B29956E0158_const.hasinit
  //## begin _ObjectID::_ObjectID%3B29956E0158_const.initialization preserve=yes
  //## end _ObjectID::_ObjectID%3B29956E0158_const.initialization
{
  //## begin _ObjectID::_ObjectID%3B29956E0158_const.body preserve=yes
	m_hObjectHandle = 0;
	m_sObjectName = "";
	m_RWCS.Init();
  //## end _ObjectID::_ObjectID%3B29956E0158_const.body
}

_ObjectID::_ObjectID(const _ObjectID &right)
  //## begin _ObjectID::_ObjectID%3B29956E0158_copy.hasinit preserve=no
  //## end _ObjectID::_ObjectID%3B29956E0158_copy.hasinit
  //## begin _ObjectID::_ObjectID%3B29956E0158_copy.initialization preserve=yes
  //## end _ObjectID::_ObjectID%3B29956E0158_copy.initialization
{
  //## begin _ObjectID::_ObjectID%3B29956E0158_copy.body preserve=yes
	m_hObjectHandle = right.get_m_hObjectHandle();
	m_sObjectName = right.get_m_sObjectName();
	m_RWCS.Init();
  //## end _ObjectID::_ObjectID%3B29956E0158_copy.body
}

_ObjectID::_ObjectID (std::string sObjectName)
  //## begin _ObjectID::_ObjectID%3B3FD80D016F.hasinit preserve=no
  //## end _ObjectID::_ObjectID%3B3FD80D016F.hasinit
  //## begin _ObjectID::_ObjectID%3B3FD80D016F.initialization preserve=yes
  //## end _ObjectID::_ObjectID%3B3FD80D016F.initialization
{
  //## begin _ObjectID::_ObjectID%3B3FD80D016F.body preserve=yes
	m_hObjectHandle=0;
	m_sObjectName = sObjectName;
	m_RWCS.Init();
  //## end _ObjectID::_ObjectID%3B3FD80D016F.body
}

_ObjectID::_ObjectID (DWORD hObjectHandle)
  //## begin _ObjectID::_ObjectID%3B3FD8390158.hasinit preserve=no
  //## end _ObjectID::_ObjectID%3B3FD8390158.hasinit
  //## begin _ObjectID::_ObjectID%3B3FD8390158.initialization preserve=yes
  //## end _ObjectID::_ObjectID%3B3FD8390158.initialization
{
  //## begin _ObjectID::_ObjectID%3B3FD8390158.body preserve=yes
	m_hObjectHandle=hObjectHandle;
	m_sObjectName = "";
	m_RWCS.Init();
  //## end _ObjectID::_ObjectID%3B3FD8390158.body
}


_ObjectID::~_ObjectID()
{
  //## begin _ObjectID::~_ObjectID%3B29956E0158_dest.body preserve=yes
	m_RWCS.Term();
  //## end _ObjectID::~_ObjectID%3B29956E0158_dest.body
}


_ObjectID & _ObjectID::operator=(const _ObjectID &right)
{
  //## begin _ObjectID::operator=%3B29956E0158_assign.body preserve=yes
	m_hObjectHandle=right.get_m_hObjectHandle();
	m_sObjectName=right.get_m_sObjectName();
		return *this;
  //## end _ObjectID::operator=%3B29956E0158_assign.body
}


bool _ObjectID::operator==(const _ObjectID &right) const
{
  //## begin _ObjectID::operator==%3B29956E0158_eq.body preserve=yes
	bool RetVal=true;
	if (right.get_m_hObjectHandle()!=0) //если установлен ИД
	{
		RetVal=(right.get_m_hObjectHandle()==m_hObjectHandle);
	}
	if (right.get_m_sObjectName().size()!=0) //если что-то есть...
	{
		RetVal=RetVal&&(right.get_m_sObjectName()==m_sObjectName);
	}

	return RetVal;
  //## end _ObjectID::operator==%3B29956E0158_eq.body
}

bool _ObjectID::operator!=(const _ObjectID &right) const
{
  //## begin _ObjectID::operator!=%3B29956E0158_neq.body preserve=yes
	return !((*this)==(right));
  //## end _ObjectID::operator!=%3B29956E0158_neq.body
}


bool _ObjectID::operator<(const _ObjectID &right) const
{
  //## begin _ObjectID::operator<%3B29956E0158_ls.body preserve=yes
	bool RetVal = true;
	if (right.get_m_hObjectHandle()!=0) //если установлен ИД
	{
		RetVal=(right.get_m_hObjectHandle()>m_hObjectHandle);
	}
//	if (right.get_m_sObjectName().size()!=0) //если что-то есть...
//	{
//		RetVal=RetVal&&(right.get_m_sObjectName()>m_sObjectName);
//	}
	return RetVal;
  //## end _ObjectID::operator<%3B29956E0158_ls.body
}

bool _ObjectID::operator>(const _ObjectID &right) const
{
  //## begin _ObjectID::operator>%3B29956E0158_gt.body preserve=yes
	bool RetVal = true;
	if (right.get_m_hObjectHandle()!=0) //если установлен ИД
	{
		RetVal=(right.get_m_hObjectHandle()<m_hObjectHandle);
	}
	if (right.get_m_sObjectName().size()!=0) //если что-то есть...
	{
		RetVal=RetVal&&(right.get_m_sObjectName()<m_sObjectName);
	}
	return RetVal;
  //## end _ObjectID::operator>%3B29956E0158_gt.body
}

bool _ObjectID::operator<=(const _ObjectID &right) const
{
  //## begin _ObjectID::operator<=%3B29956E0158_lseq.body preserve=yes
	return (((*this)<right)||((*this)==right));
  //## end _ObjectID::operator<=%3B29956E0158_lseq.body
}

bool _ObjectID::operator>=(const _ObjectID &right) const
{
  //## begin _ObjectID::operator>=%3B29956E0158_gteq.body preserve=yes
	return (((*this)>right)||((*this)==right));
  //## end _ObjectID::operator>=%3B29956E0158_gteq.body
}



//## Other Operations (implementation)
DWORD _ObjectID::GenerateNewID (_ObjectID* pChannelID,DWORD dwChannelID)
{
  //## begin _ObjectID::GenerateNewID%3B384271022B.body preserve=yes
	
	DWORD dwChID=0;
	if (pChannelID) 
		dwChID = (DWORD)pChannelID->get_m_hObjectHandle();
	else
		if (dwChannelID)
			dwChID=dwChannelID;

	m_hObjectHandle =(dwChID<<16)|((DWORD)rand());
	return m_hObjectHandle;
  //## end _ObjectID::GenerateNewID%3B384271022B.body
}

DWORD _ObjectID::GenerateFromExisting (WORD GroupID, WORD ItemID)
{
  //## begin _ObjectID::GenerateFromExisting%3B5BDE4302B0.body preserve=yes
	m_hObjectHandle =((DWORD)(GroupID<<16))|((DWORD)ItemID);
	return m_hObjectHandle;
  //## end _ObjectID::GenerateFromExisting%3B5BDE4302B0.body
}

// Additional Declarations
  //## begin _ObjectID%3B29956E0158.declarations preserve=yes
  //## end _ObjectID%3B29956E0158.declarations

// Class _ChannelID 


_ChannelID::_ChannelID()
  //## begin _ChannelID::_ChannelID%3B299C840294_const.hasinit preserve=no
  //## end _ChannelID::_ChannelID%3B299C840294_const.hasinit
  //## begin _ChannelID::_ChannelID%3B299C840294_const.initialization preserve=yes
  //## end _ChannelID::_ChannelID%3B299C840294_const.initialization
{
  //## begin _ChannelID::_ChannelID%3B299C840294_const.body preserve=yes
	m_ChannelPluginCLSID = GUID_NULL;
  //## end _ChannelID::_ChannelID%3B299C840294_const.body
}

_ChannelID::_ChannelID(const _ChannelID &right)
  //## begin _ChannelID::_ChannelID%3B299C840294_copy.hasinit preserve=no
  //## end _ChannelID::_ChannelID%3B299C840294_copy.hasinit
  //## begin _ChannelID::_ChannelID%3B299C840294_copy.initialization preserve=yes
  //## end _ChannelID::_ChannelID%3B299C840294_copy.initialization
{
  //## begin _ChannelID::_ChannelID%3B299C840294_copy.body preserve=yes
	m_ChannelPluginCLSID=right.get_m_ChannelPluginCLSID();
	set_m_hObjectHandle(right.get_m_hObjectHandle());
	set_m_sObjectName(right.get_m_sObjectName());
//		srand((unsigned)time( NULL ) );//устанавливаем генератор

  //## end _ChannelID::_ChannelID%3B299C840294_copy.body
}


_ChannelID::~_ChannelID()
{
  //## begin _ChannelID::~_ChannelID%3B299C840294_dest.body preserve=yes
  //## end _ChannelID::~_ChannelID%3B299C840294_dest.body
}


_ChannelID & _ChannelID::operator=(const _ChannelID &right)
{
  //## begin _ChannelID::operator=%3B299C840294_assign.body preserve=yes
 	m_ChannelPluginCLSID=right.get_m_ChannelPluginCLSID();
	set_m_hObjectHandle(right.get_m_hObjectHandle());
	set_m_sObjectName(right.get_m_sObjectName());
	return *this;
  //## end _ChannelID::operator=%3B299C840294_assign.body
}


// Additional Declarations
  //## begin _ChannelID%3B299C840294.declarations preserve=yes
  //## end _ChannelID%3B299C840294.declarations

// Class _TagID 
_TagID::_TagID()
{
	set_m_hObjectHandle(0);
	set_m_sObjectName("");
	set_m_sRealName("");
}
_TagID::~_TagID()
{
  //## begin _TagID::~_TagID%3B299E64017E_dest.body preserve=yes
  //## end _TagID::~_TagID%3B299E64017E_dest.body
}

_TagID & _TagID::operator=(const _TagID &right)
{
	set_m_hObjectHandle(right.get_m_hObjectHandle());
	set_m_sObjectName(right.get_m_sObjectName());
	set_m_sRealName(right.get_m_sRealName());
	return *this;
}
// Additional Declarations
  //## begin _TagID%3B299E64017E.declarations preserve=yes
  //## end _TagID%3B299E64017E.declarations

// Class _GroupID 

_GroupID::~_GroupID()
{
  //## begin _GroupID::~_GroupID%3B299FF40318_dest.body preserve=yes
  //## end _GroupID::~_GroupID%3B299FF40318_dest.body
}


// Additional Declarations
  //## begin _GroupID%3B299FF40318.declarations preserve=yes
  //## end _GroupID%3B299FF40318.declarations

// Class _OPCTagID 


 _OPCTagID::_OPCTagID()
   //## begin _OPCTagID::_OPCTagID%3B3054DF00FB_const.hasinit preserve=no
       : ClientHandle(0)
   //## end _OPCTagID::_OPCTagID%3B3054DF00FB_const.hasinit
   //## begin _OPCTagID::_OPCTagID%3B3054DF00FB_const.initialization preserve=yes
   //## end _OPCTagID::_OPCTagID%3B3054DF00FB_const.initialization
 {
   //## begin _OPCTagID::_OPCTagID%3B3054DF00FB_const.body preserve=yes
	ClientHandle = -1;
	set_m_hObjectHandle(0);
	set_m_sObjectName("");
	set_m_sRealName("");
    m_InterpretServerHandle=0;
   //## end _OPCTagID::_OPCTagID%3B3054DF00FB_const.body
 }

_OPCTagID::_OPCTagID(const _OPCTagID &right)
  //## begin _OPCTagID::_OPCTagID%3B3054DF00FB_copy.hasinit preserve=no
      : ClientHandle(0)
  //## end _OPCTagID::_OPCTagID%3B3054DF00FB_copy.hasinit
  //## begin _OPCTagID::_OPCTagID%3B3054DF00FB_copy.initialization preserve=yes
  //## end _OPCTagID::_OPCTagID%3B3054DF00FB_copy.initialization
{
  //## begin _OPCTagID::_OPCTagID%3B3054DF00FB_copy.body preserve=yes
	ClientHandle = right.get_ClientHandle();
	set_m_hObjectHandle(right.get_m_hObjectHandle());
	set_m_sObjectName(right.get_m_sObjectName());
	set_m_sRealName(right.get_m_sRealName());
  //## end _OPCTagID::_OPCTagID%3B3054DF00FB_copy.body
}


_OPCTagID::~_OPCTagID()
{
  //## begin _OPCTagID::~_OPCTagID%3B3054DF00FB_dest.body preserve=yes
  //## end _OPCTagID::~_OPCTagID%3B3054DF00FB_dest.body
}


_OPCTagID & _OPCTagID::operator=(const _OPCTagID &right)
{
  //## begin _OPCTagID::operator=%3B3054DF00FB_assign.body preserve=yes
	ClientHandle = right.get_ClientHandle();
	set_m_hObjectHandle( right.get_m_hObjectHandle());
	set_m_sObjectName( right.get_m_sObjectName());
	set_m_sRealName(right.get_m_sRealName());
	return *this;
  //## end _OPCTagID::operator=%3B3054DF00FB_assign.body
}

/*bool _OPCTagID::operator==(const _OPCTagID &right) const
{
  //## begin _ObjectID::operator==%3B29956E0158_eq.body preserve=yes
	bool RetVal=true;
	if (right.get_ClientHandle()!=0) //если установлен ИД
	{
		RetVal=(right.get_ClientHandle()==ClientHandle);
	}

	return RetVal;
  //## end _ObjectID::operator==%3B29956E0158_eq.body
}*/
// Additional Declarations
  //## begin _OPCTagID%3B3054DF00FB.declarations preserve=yes
  //## end _OPCTagID%3B3054DF00FB.declarations

//## begin module%3B3841330278.epilog preserve=yes
//## end module%3B3841330278.epilog
