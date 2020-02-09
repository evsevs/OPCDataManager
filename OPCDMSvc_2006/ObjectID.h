//## begin module%1.2%.codegen_version preserve=yes
//	 Read the documentation to learn more about C++ code generator
//	 versioning.
//## end module%1.2%.codegen_version

//## begin module%3B384130036E.cm preserve=no
//	  %X% %Q% %Z% %W%
//## end module%3B384130036E.cm

//## begin module%3B384130036E.cp preserve=no
//	Файл создан 23.07.2001 16:21:10
//	Ерохин В.С.
//	ЗСМК, ИЦ АСУ ТП
//	к.415 т.1-14-26
//## end module%3B384130036E.cp

//## Module: ObjectID%3B384130036E; Package specification
//## Subsystem: <Top Level>
//## Source file: D:\Prj\VC++\OPC\OPCImpl\ObjectID.h

#ifndef ObjectID_h
#define ObjectID_h 1

//## begin module%3B384130036E.additionalIncludes preserve=no
#include "stdafx.h"
#include "OPCDataCallbackCP.h"	// Added by ClassView
//## end module%3B384130036E.additionalIncludes

//## begin module%3B384130036E.includes preserve=yes
//## end module%3B384130036E.includes

//## begin module%3B384130036E.declarations preserve=no
//## end module%3B384130036E.declarations

//## begin module%3B384130036E.additionalDeclarations preserve=yes
//## end module%3B384130036E.additionalDeclarations


//## begin _ObjectID%3B29956E0158.preface preserve=yes
//## end _ObjectID%3B29956E0158.preface

//## Class: _ObjectID%3B29956E0158
//	Структура идентификации объектов внутри DM
//	.
//## Category: \300\321\304::DataManager::\310\344\345\355\362\350\364\350\352\340\362\356\360\373%3B2F000C035D
//## Subsystem: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class _ObjectID 
{
  //## begin _ObjectID%3B29956E0158.initialDeclarations preserve=yes
  //## end _ObjectID%3B29956E0158.initialDeclarations

  public:
	//## Constructors (generated)
	  _ObjectID();
	 CComCriticalSection m_RWCS;
	  _ObjectID(const _ObjectID &right);

	//## Constructors (specified)
	  //## Operation: _ObjectID%3B3FD80D016F
	  //	Конструктор для использования при создании экземпляра
	  //	идентификатора для поиска по имени.
	  _ObjectID (std::string sObjectName);

	  //## Operation: _ObjectID%3B3FD8390158
	  //	Конструктор для использования при создании экземпляра
	  //	идентификатора для поиска по ObjectHandle.
	  _ObjectID (DWORD hObjectHandle);

	//## Destructor (generated)
	  virtual ~_ObjectID();

	//## Assignment Operation (generated)
	  virtual _ObjectID & operator=(const _ObjectID &right);

	//## Equality Operations (generated)
	  virtual bool operator==(const _ObjectID &right) const;

	  virtual bool operator!=(const _ObjectID &right) const;

	//## Relational Operations (generated)
	  virtual bool operator<(const _ObjectID &right) const;

	  virtual bool operator>(const _ObjectID &right) const;

	  virtual bool operator<=(const _ObjectID &right) const;

	  virtual bool operator>=(const _ObjectID &right) const;


	//## Other Operations (specified)
	  //## Operation: GenerateNewID%3B384271022B
	  //	Метод для генереции нового идентификатора.
	  //## Postconditions:
	  //	Изменяется значение аттрибута m_ObjectHandle.
	  DWORD GenerateNewID (_ObjectID* pChannelID,DWORD dwChannelID=0);

	  //## Operation: GenerateFromExisting%3B5BDE4302B0
	  DWORD GenerateFromExisting (WORD GroupID, WORD ItemID);

	//## Get and Set Operations for Class Attributes (generated)

	  //## Attribute: m_hObjectHandle%3B29964D02B6
	  //	Идентификатор объекта.
	  //	Устанавливается при создании (именно добавления)
	  //	объекта.
	  //	Глобально уникален.
	  //	Используется для быстрого поиска и внутренней
	  //	идентификации.
	  const unsigned int get_m_hObjectHandle () const;
	  void set_m_hObjectHandle (unsigned int value);

	  //## Attribute: m_sObjectName%3B29970901D4
	  //	Имя объекта.
	  //	Задается при конфигурировании менеджера и сохраняется
	  //	непосредственно до удаления канала.
	  //	Используется для внешней идентификации.
	  const std::string get_m_sObjectName () const;
	  void set_m_sObjectName (std::string value);

	// Additional Public Declarations
	  //## begin _ObjectID%3B29956E0158.public preserve=yes
	  //## end _ObjectID%3B29956E0158.public

  protected:
	// Additional Protected Declarations
	  //## begin _ObjectID%3B29956E0158.protected preserve=yes
	  //## end _ObjectID%3B29956E0158.protected

  private:
	// Additional Private Declarations
	  //## begin _ObjectID%3B29956E0158.private preserve=yes
	  //## end _ObjectID%3B29956E0158.private

  private: //## implementation
	// Data Members for Class Attributes

	  //## begin _ObjectID::m_hObjectHandle%3B29964D02B6.attr preserve=no  public: unsigned int {V} 
	  unsigned int m_hObjectHandle;
	  //## end _ObjectID::m_hObjectHandle%3B29964D02B6.attr

	  //## begin _ObjectID::m_sObjectName%3B29970901D4.attr preserve=no  public: std::string {U} 
	  std::string m_sObjectName;
	  //## end _ObjectID::m_sObjectName%3B29970901D4.attr

	// Additional Implementation Declarations
	  //## begin _ObjectID%3B29956E0158.implementation preserve=yes
	  //## end _ObjectID%3B29956E0158.implementation

};

//## begin _ObjectID%3B29956E0158.postscript preserve=yes
//## end _ObjectID%3B29956E0158.postscript

//## begin _ChannelID%3B299C840294.preface preserve=yes
//## end _ChannelID%3B299C840294.preface

//## Class: _ChannelID%3B299C840294
//	Структура идентификации каналов.
//## Category: \300\321\304::DataManager::\310\344\345\355\362\350\364\350\352\340\362\356\360\373%3B2F000C035D
//## Subsystem: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class _ChannelID : public _ObjectID  //## Inherits: <unnamed>%3B299C970071
{
  //## begin _ChannelID%3B299C840294.initialDeclarations preserve=yes
  //## end _ChannelID%3B299C840294.initialDeclarations

  public:
	//## Constructors (generated)
	  _ChannelID();

	  _ChannelID(const _ChannelID &right);

	//## Destructor (generated)
	  virtual ~_ChannelID();

	//## Assignment Operation (generated)
	  _ChannelID & operator=(const _ChannelID &right);

	//## Get and Set Operations for Class Attributes (generated)

	  //## Attribute: m_ChannelPluginCLSID%3B2995960359
	  //	Уникальный идентификатор для источника данных канала.
	  //	Канал может иметь только один источник данных.
	  //	Используется для внутренней идентификации и быстрого
	  //	поиска.
	  const CLSID get_m_ChannelPluginCLSID () const;
	  void set_m_ChannelPluginCLSID (CLSID value);

	// Additional Public Declarations
	  //## begin _ChannelID%3B299C840294.public preserve=yes
	  //## end _ChannelID%3B299C840294.public

  protected:
	// Additional Protected Declarations
	  //## begin _ChannelID%3B299C840294.protected preserve=yes
	  //## end _ChannelID%3B299C840294.protected

  private:
	// Additional Private Declarations
	  //## begin _ChannelID%3B299C840294.private preserve=yes
	  //## end _ChannelID%3B299C840294.private

  private: //## implementation
	// Data Members for Class Attributes

	  //## begin _ChannelID::m_ChannelPluginCLSID%3B2995960359.attr preserve=no  public: CLSID {V} 
	  CLSID m_ChannelPluginCLSID;
	  //## end _ChannelID::m_ChannelPluginCLSID%3B2995960359.attr

	// Additional Implementation Declarations
	  //## begin _ChannelID%3B299C840294.implementation preserve=yes
	  //## end _ChannelID%3B299C840294.implementation

};

//## begin _ChannelID%3B299C840294.postscript preserve=yes
//## end _ChannelID%3B299C840294.postscript

//## begin _TagID%3B299E64017E.preface preserve=yes
//## end _TagID%3B299E64017E.preface

//## Class: _TagID%3B299E64017E
//	Структура идентификации тега внутри DM.
//## Category: \300\321\304::DataManager::\310\344\345\355\362\350\364\350\352\340\362\356\360\373%3B2F000C035D
//## Subsystem: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class _TagID : public _ObjectID  //## Inherits: <unnamed>%3B299E6E019F
{
  //## begin _TagID%3B299E64017E.initialDeclarations preserve=yes
  //## end _TagID%3B299E64017E.initialDeclarations

  public:
	//## Destructor (generated)
	  _TagID();
	  virtual ~_TagID();
	  const std::string get_m_sRealName() const;
	  void set_m_sRealName(std::string RealName);
	 virtual _TagID & operator=(const _TagID &right);	  
	// Additional Public Declarations
	  //## begin _TagID%3B299E64017E.public preserve=yes
	  //## end _TagID%3B299E64017E.public

  protected:
	// Additional Protected Declarations
	  //## begin _TagID%3B299E64017E.protected preserve=yes
	  //## end _TagID%3B299E64017E.protected

  private:
	// Additional Private Declarations
	  //## begin _TagID%3B299E64017E.private preserve=yes
	  //## end _TagID%3B299E64017E.private

  public: //## implementation
	  std::string m_sRealName;
	// Additional Implementation Declarations
	  //## begin _TagID%3B299E64017E.implementation preserve=yes
	  //## end _TagID%3B299E64017E.implementation

};

//## begin _TagID%3B299E64017E.postscript preserve=yes
//## end _TagID%3B299E64017E.postscript

//## begin _GroupID%3B299FF40318.preface preserve=yes
//## end _GroupID%3B299FF40318.preface

//## Class: _GroupID%3B299FF40318
//	Структура идентификации общей OPC группы.
//	К уникальности этого индекса применяются более жесткие
//	рамки.
//## Category: \300\321\304::DataManager::\310\344\345\355\362\350\364\350\352\340\362\356\360\373%3B2F000C035D
//## Subsystem: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class _GroupID : public _ObjectID  //## Inherits: <unnamed>%3B29A53A00F4
{
  //## begin _GroupID%3B299FF40318.initialDeclarations preserve=yes
  //## end _GroupID%3B299FF40318.initialDeclarations

  public:
	//## Destructor (generated)
	  virtual ~_GroupID();

	// Additional Public Declarations
	  //## begin _GroupID%3B299FF40318.public preserve=yes
	  //## end _GroupID%3B299FF40318.public

  protected:
	// Additional Protected Declarations
	  //## begin _GroupID%3B299FF40318.protected preserve=yes
	  //## end _GroupID%3B299FF40318.protected

  private:
	// Additional Private Declarations
	  //## begin _GroupID%3B299FF40318.private preserve=yes
	  //## end _GroupID%3B299FF40318.private

  private: //## implementation
	// Additional Implementation Declarations
	  //## begin _GroupID%3B299FF40318.implementation preserve=yes
	  //## end _GroupID%3B299FF40318.implementation

};

//## begin _GroupID%3B299FF40318.postscript preserve=yes
//## end _GroupID%3B299FF40318.postscript

//## begin _OPCTagID%3B3054DF00FB.preface preserve=yes
//## end _OPCTagID%3B3054DF00FB.preface

//## Class: _OPCTagID%3B3054DF00FB
//	Используется для хранения в ОРС сервере.
//## Category: \300\321\304::DataManager::\310\344\345\355\362\350\364\350\352\340\362\356\360\373%3B2F000C035D
//## Subsystem: <Top Level>
//## Persistence: Transient
//## Cardinality/Multiplicity: n

class _OPCTagID : public _TagID  //## Inherits: <unnamed>%3B3054EC00EE
{
  //## begin _OPCTagID%3B3054DF00FB.initialDeclarations preserve=yes
/*
+++++++++++++++++
Использование идентификатора:
			При использовании идентификатора в нормальном режиме в поле m_hObjectHandle
		заноситcя ServerHandle (используемый в канале), поле m_InterpretServerHandle 
		инциализируется в 0. 
			При вставке тега, уже умеющегося в группе, в поле m_hObjectHandle заносится
		ИНТЕРПРЕТИРУЕМЫЙ handle ((((Интерпретируемый handle генерируется с 
		использованием идентификатора канала, подобно генерации идентификатора для тегов
		в канале)))), а в поле m_InterpretServerHandle - ServerHandle (используемый в канале). 
		Также в карту интерпретации m_InterpretHandleMap заносится	значение ServerHandle 
		канала под ключом m_InterpretServerHandle (это гарантирует ункальность интерпретируемых 
		 handle'ов в группе).
+++++++++++
       
		 Такая путаница введена в связи с тем, что это ускорит поиск тегов, проверку на наличие
		 тега в группе и т.д.
*/
  //## end _OPCTagID%3B3054DF00FB.initialDeclarations

  public:
	//## Constructors (generated)

	  _OPCTagID(const _OPCTagID &right);
		_OPCTagID();
	//## Destructor (generated)
	  virtual ~_OPCTagID();

	//## Assignment Operation (generated)
	  _OPCTagID & operator=(const _OPCTagID &right);

	//## Get and Set Operations for Class Attributes (generated)

	  //## Attribute: ClientHandle%3B30550D02E6
	  //	Идентификатор тега клиента.
	  const DWORD get_ClientHandle () const;
	  void set_ClientHandle (DWORD value);
	  const DWORD get_InterpretServerHandle() const;
	  void set_InterpretServerHandle(DWORD value);
	//bool operator==(const _OPCTagID &right) const;

	// Additional Public Declarations
	  //## begin _OPCTagID%3B3054DF00FB.public preserve=yes
	  //## end _OPCTagID%3B3054DF00FB.public

  protected:
	// Additional Protected Declarations
	  //## begin _OPCTagID%3B3054DF00FB.protected preserve=yes
	  //## end _OPCTagID%3B3054DF00FB.protected

  private:
	// Additional Private Declarations
	  //## begin _OPCTagID%3B3054DF00FB.private preserve=yes
	  //## end _OPCTagID%3B3054DF00FB.private

  private: //## implementation
	  //Используется именно ОРС сервером для многократного добавления тега
	  //Если тег с известным  ObjectHandle тега канала уже добавлен в группу - 
	  //то клиентом использкется интерпретированный handle сервера
	  OPCHANDLE m_InterpretServerHandle; 

	// Data Members for Class Attributes

	  //## begin _OPCTagID::ClientHandle%3B30550D02E6.attr preserve=no	public: DWORD {U} 0
	  DWORD ClientHandle;
	  //## end _OPCTagID::ClientHandle%3B30550D02E6.attr

	// Additional Implementation Declarations
	  //## begin _OPCTagID%3B3054DF00FB.implementation preserve=yes
	  //## end _OPCTagID%3B3054DF00FB.implementation

};

//## begin _OPCTagID%3B3054DF00FB.postscript preserve=yes
//## end _OPCTagID%3B3054DF00FB.postscript

// Class _ObjectID 

//## Get and Set Operations for Class Attributes (inline)

inline const unsigned int _ObjectID::get_m_hObjectHandle () const
{
  //## begin _ObjectID::get_m_hObjectHandle%3B29964D02B6.get preserve=no
  return m_hObjectHandle;
  //## end _ObjectID::get_m_hObjectHandle%3B29964D02B6.get
}

inline void _ObjectID::set_m_hObjectHandle (unsigned int value)
{
  //## begin _ObjectID::set_m_hObjectHandle%3B29964D02B6.set preserve=no
  m_hObjectHandle = value;
  //## end _ObjectID::set_m_hObjectHandle%3B29964D02B6.set
}

inline const std::string _ObjectID::get_m_sObjectName () const
{
  //## begin _ObjectID::get_m_sObjectName%3B29970901D4.get preserve=no
  return m_sObjectName;
  //## end _ObjectID::get_m_sObjectName%3B29970901D4.get
}

inline void _ObjectID::set_m_sObjectName (std::string value)
{
  //## begin _ObjectID::set_m_sObjectName%3B29970901D4.set preserve=no
  m_sObjectName = value;
  //## end _ObjectID::set_m_sObjectName%3B29970901D4.set
}

// Class _ChannelID 

//## Get and Set Operations for Class Attributes (inline)

inline const CLSID _ChannelID::get_m_ChannelPluginCLSID () const
{
  //## begin _ChannelID::get_m_ChannelPluginCLSID%3B2995960359.get preserve=no
  return m_ChannelPluginCLSID;
  //## end _ChannelID::get_m_ChannelPluginCLSID%3B2995960359.get
}

inline void _ChannelID::set_m_ChannelPluginCLSID (CLSID value)
{
  //## begin _ChannelID::set_m_ChannelPluginCLSID%3B2995960359.set preserve=no
  m_ChannelPluginCLSID = value;
  //## end _ChannelID::set_m_ChannelPluginCLSID%3B2995960359.set
}

// Class _TagID 
inline const std::string _TagID::get_m_sRealName() const
{
	return m_sRealName;
}
inline	 void _TagID::set_m_sRealName(std::string RealName)
{
	m_sRealName=RealName;
}
	
// Class _GroupID 

// Class _OPCTagID 

//## Get and Set Operations for Class Attributes (inline)

inline const DWORD _OPCTagID::get_ClientHandle () const
{
  //## begin _OPCTagID::get_ClientHandle%3B30550D02E6.get preserve=no
  return ClientHandle;
  //## end _OPCTagID::get_ClientHandle%3B30550D02E6.get
}

inline void _OPCTagID::set_ClientHandle (DWORD value)
{
  //## begin _OPCTagID::set_ClientHandle%3B30550D02E6.set preserve=no
  ClientHandle = value;
  //## end _OPCTagID::set_ClientHandle%3B30550D02E6.set
}
inline 	  const DWORD _OPCTagID::get_InterpretServerHandle() const
{
	return m_InterpretServerHandle;
}
inline	  void _OPCTagID::set_InterpretServerHandle(DWORD value)
{
	m_InterpretServerHandle=value;
}

//## begin module%3B384130036E.epilog preserve=yes
//## end module%3B384130036E.epilog


#endif
