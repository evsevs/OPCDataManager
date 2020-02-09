//	Файл создан 18.07.2001 16:39:38
//	Ерохин В.С.
//	ЗСМК, ИЦ АСУ ТП
//	к.415 т.1-14-26
#ifndef DataPlugin_h
#define DataPlugin_h 1

#include "stdafx.h"
#include "DMPluginIfs.h"
#include "SimpleLogFile.h"
#include "_Message.h"
// LocalNotify
#include "LocalNotify.h"
//	Класс реализует функции плагина.

class CDataPlugin;

//Приемник нотификаций
class CPluginNotifyListener://ПРОВЕРЕН
				public CComObjectRootEx< CComMultiThreadModel >,
				public IPluginDataCallback
{
public:
	HRESULT DisconnectFromNotify();
	bool m_Connected;
	HRESULT ConnectToNotify();
	DWORD m_dwCoockie;
	BEGIN_COM_MAP(CPluginNotifyListener)
		COM_INTERFACE_ENTRY(IPluginDataCallback)
	END_COM_MAP()

	CDataPlugin *m_Owner;//указатель на класс владелец приемника

	STDMETHOD (OnDeviceNotAvailable)(void);
	STDMETHOD (OnTagsChange)(DWORD dwCount, DWORD* phClientItems, VARIANT *pvValues,WORD* pwQualities,FILETIME*  pftTimeStamps, HRESULT * pErrors);
};

class CDataPlugin 
{
 friend class CPluginNotifyListener;
  public:
	  CDataPlugin(CLogFile_CS &lf);
	  ~CDataPlugin();
	  //приемник нотификаций
	CComObjectNoLock<CPluginNotifyListener> * m_NotifyListener;
	  //	Операция для определения является ли плагин плагином
	  //	константных значений.
	  //	true - является.
	  //	false - не является.
	  bool IsConstDataPlugin ();
	  //	Метод инициализации плагина (соединение, доп.
	  //	информация).
	  //	Значение переменной m_Init не важно.
	  //	Переменная m_Init=true.
	  HRESULT InitializePlugin (_bstr_t bstrPluginString);
	  //	Операция деинициализации плагина. При этом освобождаются
	  //	занимаемы плагином ресурсы.
	  //	Плагин инициализирован (m_Init==true).
	  //	Указатели COM объекта != NULL.
	  //	Плагин деинициализирован (m_Init==false).
	  //	Освобождаются ресурсы. Указатели=NULL.
	  HRESULT DeinitializePlugin ();
	  //	Метод для получения данных из плагина.
	  HRESULT GetTagsData (_UpdateNowMsg2* TagsNow);
	  //	Метод для передачи значений тегов в устройство.
	  HRESULT SetTagsData (_UpdateNowMsg* TagsData);
	  HRESULT AddTagsNotify (_TagID* phClient, DWORD Count, DWORD UpdateRate, HRESULT** pError);
	  //	Метод отмены уведомлений на изменение переданных тегов.
	  HRESULT DelTagsNotify (_TagID* phClient, DWORD Count, HRESULT** pError);
	  //	Возвращает состояние источника данных.
	  HRESULT GetState (WORD wState // Состояние плагина. Перечисление (пока нет).
  );
	  //	CLSID идентификатор для работы с плагином.
	  //	Если CLSID== (
	  //	   {93A34F8E-CA92-43d3-9B92-51B769CD739C}
	  //	static const GUID CLSID_ConstDataOPCPlugin ={ 0x93a34f8e, 0xca92, 0x43d3, { 0x9b, 0x92, 0x51, 0xb7,	0x69, 0xcd, 0x73, 0x9c } }
	  //	), то этот"плагин" представляет КОНСТАНТНЫЕ ЗНАЧЕНИЯ.
	  CLSID get_m_ChannelPluginCLSID ();
	  void set_m_ChannelPluginCLSID (CLSID value);
	  HRESULT SetNewLogForPlugin(std::string postfix);
	  const CLocalNotify * get_m_CacheNotify () const;
	  void set_m_CacheNotify (CLocalNotify * value);
  public:
	  //	Переменная для хранения информации о состоянии плагина.
	  //	true - плагин инициализирован, false - плагин
	  //	деинициализирован.
	  // 
	  _bstr_t m_bstrPluginStringX;
	  bool get_m_Init ();
	  void set_m_Init (bool value);
	  //	ProgID для плагина.
	public: _bstr_t get_m_ProgID ();
	public: void set_m_ProgID (_bstr_t value);
			std::string m_PluginLogFilePrefix;
			std::string m_PluginLogFilePostFix;

  private:
	  HRESULT DeInitListener();
	  HRESULT InitListener();
	  CLSID m_ChannelPluginCLSID;
	  CLogFile_CS &m_LogFile;
	  bool m_InitListener;
	  bool m_Init;
	  //	Строка инициализации плагина.
	  _bstr_t m_ProgID;
	   CComPtr<IPluginConfig> m_pIPluginConfig;
	CComPtr<IPluginData> m_pIPluginData;
  CLocalNotify *m_CacheNotify;
};

// Class CDataPlugin 

inline CLSID CDataPlugin::get_m_ChannelPluginCLSID ()
{
  return m_ChannelPluginCLSID;
}

inline void CDataPlugin::set_m_ChannelPluginCLSID (CLSID value)
{
  m_ChannelPluginCLSID = value;
}

inline bool CDataPlugin::get_m_Init ()
{
  return m_Init;
}

inline void CDataPlugin::set_m_Init (bool value)
{
  m_Init = value;
}

inline _bstr_t CDataPlugin::get_m_ProgID ()
{
  return m_ProgID;
}

inline void CDataPlugin::set_m_ProgID (_bstr_t value)
{
  m_ProgID = value;
  CLSIDFromProgID((LPOLESTR)value,&m_ChannelPluginCLSID);
}

inline const CLocalNotify * CDataPlugin::get_m_CacheNotify () const
{
  return m_CacheNotify;
}
inline void CDataPlugin::set_m_CacheNotify (CLocalNotify * value)
{
  m_CacheNotify = value;
}

#endif
