//	Файл создан 18.07.2001 10:33:06
//	Ерохин В.С.
//	ЗСМК, ИЦ АСУ ТП
//	к.415 т.1-14-26

#ifndef Handlers_h
#define Handlers_h 1


#include "stdafx.h"
#include "SimpleLogFile.h"

// Tag
#include "Tag.h"
// _Message
#include "_Message.h"
// DataPlugin
#include "DataPlugin.h"
// LocalNotify
#include "LocalNotify.h"
// CThread
#include "CThread.h"
#define WM_HANDLER_CLEAR_ASYNC (WM_USER+125)

//
//class CReadyEvent 
//{
//
//  public:
//	  CReadyEvent();
//	  ~CReadyEvent();
//	  //	Установка в сигнальное\несигнальное состояние событие
//	  //	готовности.
//	  bool SetReadyState (bool State);
//	  //	Проверка на занятость.
//	  bool IsReady (DWORD dwWaitTime = 0	// Время ожидания освобождения (мс).
//	  );
//  private:
//	  //	Событие готовности/занятости.
//	  HANDLE get_m_ReadyEvent ();
//	  void set_m_ReadyEvent (HANDLE value);
//
//  private: 
//	  HANDLE m_ReadyEvent;
//};

//	Класс реализует работу с таймером в потоке.
class CHandlerBase : virtual public CThread/*, 
						public CReadyEvent	*/
{
  public:
	  CHandlerBase();
	  virtual ~CHandlerBase();
	  //	Обновить немедленно.
	  //	Посылает сообщение своему классу WM_UPDATETAGSNOW.
//	  BOOL UpdateNow (_UpdateMsg* UpdateNowMsg	// Идентификаторы тегов, которые нужно обновить.
//	  );
	  //	Операция запускает таймер.
	  BOOL StartTimer (DWORD ClockRate=0);
	  //	Операция остановки таймера.
	  BOOL StopTimer ();
	  //	Частота внутреннего тактового генератора канала. (мс).
	  //	Параметр требуется для работы класса обновления кэша и
	  //	класса обновления данных в устройстве.
	  void set_m_ClockRate (unsigned int value);
	  CTagStorage * get_m_TagStorage ();
	  void set_m_TagStorage (CTagStorage * value);
	  CDataPlugin * get_m_Device ();
	  void set_m_Device (CDataPlugin * value);
	  //	Идентификатор таймера, используемого классом.
	  DWORD m_TimerID;
	  CTagStorage *m_TagStorage;
  private:
	  //	Функция обработки сообщения от таймера.
	  //	Устаревшие значения тегов (в хранилище или устройстве).
	  //	Пришло сообщение от таймера.
	  //	Новые значения тегов (в хранилище или устройстве).
	  virtual HRESULT OnTimerMessage (MSG msg	// Сообщение от таймера, также содержащее текущее время.
	  ) = 0;
	  //	Переопределение функции, выполгняющейся в потоке, в
	  //	классе-наследнике.
	  virtual DWORD fbody ()=0;
	  //	Функция реакции на сообщение WM_UPDATETAGSNOW.
//	  virtual HRESULT OnUpdateNow (MSG msg	// Сообщение WM_UPDATETAGSNOW c соответствующими
		// параметрами.
//	  ) = 0;
  private:
	  unsigned int m_ClockRate;
	  CDataPlugin *m_Device;
};

//	Класс для обновления данных в устройстве.
//	Класс работает в 2х вариантах:
//	1)Активизируется непосредственно при записи клиента в
//	устройство.
//	2)активен всегда и пишет в устройство последние
//	обновленные данные. Клиент же пишет в кэш.
//	Режим работы хранится в члене-переменной класса CChannel
//	m_DeviceUpdateMode. (TRUE - режим 1, FALSE - режим 2).
//class CDeviceUpdateHandler : virtual public CHandlerBase  
//{
//  public:
//	//  void Send_ClearAsync(DWORD dwTID);
//	//  void OnClearAsync(DWORD dwTID);
//	//class CAsyncThread :virtual public CThread
//	//{
//	//	  public:
//	//		  virtual ~CAsyncThread()
//	//	  {
//	//	  };
//	//	 virtual DWORD fbody ();
//	//						//здесь будет производится проверка
//	//						// на изменения и отсылка нотификаций
//	//public:
//	//	_AsyncIORWMsg* pMsg;
//	//	DWORD m_TimerID;
//	//	CDeviceUpdateHandler * m_Owner;
//	//	DWORD dwTransactionID;
//	//	bool Active;
//	//};	
//	//void OnAsyncWrite(MSG mes);
//	//void Send_AsyncWrite( _AsyncIORWMsg * mes);
//	//std::list<CAsyncThread*> m_AsyncList;
//	CDeviceUpdateHandler(CLogFile_CS &lf);
//
//	CDeviceUpdateHandler (DWORD ClockRate,CLogFile_CS &lf);
//	virtual ~CDeviceUpdateHandler();
//	  //	Переопределение функции, выполгняющейся в потоке, в
//	  //	классе-наследнике.
//	  virtual DWORD fbody ();
//	  //	Режим работы класса обновления данных в устройстве.
//	  BOOL get_m_DeviceUpdateMode ();
//	  void set_m_DeviceUpdateMode (BOOL value);
//  private:
//	  //	Переопределение абстрактной функции в наследнике.
//	  //	Функция работает только при режиме постоянного
//	  //	обновления устройства.
//	  CLogFile_CS &m_LogFile;
//	  HRESULT OnTimerMessage (MSG msg);
//	 // //	Функция реакции на сообщение WM_UPDATETAGSNOW.
//	 // HRESULT OnUpdateNow (MSG msg	// Сообщение WM_UPDATETAGSNOW c соответствующими
//		//// параметрами.
//	//  );
//	  BOOL m_DeviceUpdateMode;
//};

//	Класс для обновления данных из DEVICE в CACHE.
//	Частоту генератора берет у класса канала, так как
//	является ему другом.
class CCacheUpdateHandler : virtual public CHandlerBase, 
								virtual public CLocalNotify 
{
  public:
	  struct ArrayMap
	  {
		  ULONG right;
		  ULONG left;
	  };
//	  void Send_ClearAsync(DWORD dwTID);
//	  void OnClearAsync(DWORD dwTID);
	  DWORD m_dwInitCount;
	  bool m_NotifyAdded;
	  _UpdateNowMsg2 *m_pUpdateNowMsg2;
	  DWORD m_dwChangeLogCicleCount;
	//class CAsyncReadThread :virtual public CThread
	//{
	//	  public:
	//		  virtual ~CAsyncReadThread()
	//	  {
	//	  };
	//	 virtual DWORD fbody ();
	//						//здесь будет производится проверка
	//						// на изменения и отсылка нотификаций
	//public:
	//	_AsyncIORWMsg* pMsg;
	//	DWORD m_TimerID;
	//	CCacheUpdateHandler * m_Owner;
	//	DWORD dwTransactionID;
	//	bool Active;
	//};
	//std::list<CAsyncReadThread*> m_AsyncList;
	//void OnAsyncRead(MSG mes);
	//void Send_AsyncRead( _AsyncIORWMsg * mes);
	//HRESULT NotifyTagsSink();
	CCacheUpdateHandler(CLogFile_CS &lf);
	virtual ~CCacheUpdateHandler();
	virtual void Send_OnTagUpdate (_UpdateMsg* pUpdateMsg);
	  //	Переопределение функции, выполгняющейся в потоке, в
	  //	классе-наследнике.
	  virtual DWORD fbody ();
	  const CLocalNotify * get_m_ChannelNotify () const;
	  void set_m_ChannelNotify (CLocalNotify * value);
  private:
	  //	Переопределение абстрактной функции в наследнике.
	  //	Вызывается для обработки сигнала от таймера.
	  virtual HRESULT OnTimerMessage (MSG msg);
	  //	Функция реакции на сообщение WM_UPDATETAGSNOW.
	 // virtual HRESULT OnUpdateNow (MSG msg	// Сообщение WM_UPDATETAGSNOW c соответствующими
		//// параметрами.
	 // );
	  //	Вызывается после обновления тегов. По приходй сообщения
	  //	WM_TAGSUPDATED.
	  void TagsUpdated (_UpdateMsg* pUpdateMsg);
	  HRESULT OnNotify (MSG msg);
	  CLogFile_CS & m_LogFile;	
  private:
	  void OnUninitPlugin();
 	  void OnInitPlugin(DWORD lParam);
	  void OnAddNotifyPlugin(DWORD lParam,DWORD wParam);
	  CLocalNotify *m_ChannelNotify;
protected:
	//смена лог-файла
	void ChangeLogFile();
	bool ControlPluginInit();
	void OnReadNow (MSG msg,bool IsEvented);
	void OnWriteNow(MSG msg,bool IsEvented);
//    void OnDeviceRead(MSG msg,bool IsEvented);
	
//то, что было в DeviceHandler
public:
	//посылает сообщение о чтении ИМЕННО из устройства (плагина).
	//используется при синхронном чтении из устройства (в этом случае событие,
	//переданное в сообщении устанавливается в Signaled
	void Client_DeviceReadSync(_SyncIORMsg *mes);
	//посылает сообщение о чтении ИМЕННО из устройства (плагина).
	//используется при асинхронном чтении из устройства.
	//По окончании операции посылает сообщение о завершении в 
	//контрольный поток клиента (группы ОРС). Идентификатор потока клиента 
	//указывается в сообщении
	void Client_DeviceReadAsync(_AsyncIORWMsg *mes);
	//посылает сообщение о чтении из кэша канала.
	//используется контрольным потоком группы ОРС для обновления 
	//кэша группы. В этом случае ВСЕГДА в сообщении передается событие,
	//которое устанавливается в Signaled после операции чтения
	void Client_CacheRead();
	//посылает сообщение о записи в устройство
	//используется при синхронной записи (в этом случае событие,
	//переданное в сообщении устанавливается в Signaled
	void Client_DeviceWriteSync(_SyncIORMsg *mes);
	//посылает сообщение о записи в устройство
	//используется при асинхронной записи 
	//По окончании операции посылает сообщение о завершении в 
	//контрольный поток клиента (группы ОРС). Идентификатор потока клиента 
	//указывается в сообщении
	void Client_DeviceWriteAsync(_AsyncIORWMsg *mes);
	
protected:
//	void DeviceRead(MSG msg);

	// реакция на сообщение WM_OPC_SYNCREAD
	void OnDeviceReadSync(_SyncIORMsg* mes);
	// реакция на WM_OPC_ASYNCREAD
	void OnDeviceReadAsync(_AsyncIORWMsg* mes);
	// реакция на сообщение WM_OPC_SYNWRITE
	void OnDeviceWriteSync(_SyncIORMsg * mes);
	// реакция на WM_OPC_ASYNCWRITE
	void OnDeviceWriteAsync(_AsyncIORWMsg* mes);
	HRESULT DeviceWrite(DWORD xCount,OPCHANDLE *pH,VARIANT *pV,HRESULT *pE);
public:
	// Чтение из устройства
	HRESULT DeviceRead(void);
};
//	Класс для получения дополнительной информации от
//	устройства.
//
//class CExternalInfoHandler : public CThread  //## Inherits: <unnamed>%3B42B9920119
//{
//  public:
//	  CExternalInfoHandler();
//	  ~CExternalInfoHandler();
//	  HRESULT GetItemIDs (OPCBROWSETYPE Type,	// Тип, что вернуть.
//	  DWORD* pCount,	// Количество названий в массиве.
//	  LPWSTR* pItemNames);
//	  //	Возвращает ВСЕ названия тегов. Полные.
//	  HRESULT GetAllIDs (LPWSTR* pItemNames, DWORD* pCount);
//	  //	Возвращает дополнительную информацию по тегам
//	  //	(информация из Set2).
//	  HRESULT GetSet2Properties ();
//	  const CDataPlugin * get_m_Device () const;
//	  void set_m_Device (CDataPlugin * value);
//  private:
//	  //	Переопределение функции, выполгняющейся в потоке, в
//	  //	классе-наследнике.
//	  virtual DWORD fbody ();
//	  CDataPlugin *m_Device;
//};
//
//inline HANDLE CReadyEvent::get_m_ReadyEvent ()
//{
//  return m_ReadyEvent;
//}
//inline void CReadyEvent::set_m_ReadyEvent (HANDLE value)
//{
//  m_ReadyEvent = value;
//}
inline void CHandlerBase::set_m_ClockRate (unsigned int value)
{
  m_ClockRate = value;
}
inline CTagStorage * CHandlerBase::get_m_TagStorage ()
{
  return m_TagStorage;
}
inline void CHandlerBase::set_m_TagStorage (CTagStorage * value)
{
  m_TagStorage = value;
}
inline CDataPlugin * CHandlerBase::get_m_Device ()
{
  return m_Device;
}

inline void CHandlerBase::set_m_Device (CDataPlugin * value)
{
  m_Device = value;
}

// Class CDeviceUpdateHandler 
//
//inline BOOL CDeviceUpdateHandler::get_m_DeviceUpdateMode ()
//{
//  return m_DeviceUpdateMode;
//}
//
//inline void CDeviceUpdateHandler::set_m_DeviceUpdateMode (BOOL value)
//{
//  m_DeviceUpdateMode = value;
//}

// Class CCacheUpdateHandler 

inline const CLocalNotify * CCacheUpdateHandler::get_m_ChannelNotify () const
{
  return m_ChannelNotify;
}

inline void CCacheUpdateHandler::set_m_ChannelNotify (CLocalNotify * value)
{
  m_ChannelNotify = value;
}

//// Class CExternalInfoHandler 
//
//inline const CDataPlugin * CExternalInfoHandler::get_m_Device () const
//{
//  return m_Device;
//}
//
//inline void CExternalInfoHandler::set_m_Device (CDataPlugin * value)
//{
//  m_Device = value;
//}

#endif
