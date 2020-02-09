//	���� ������ 18.07.2001 10:33:06
//	������ �.�.
//	����, �� ��� ��
//	�.415 �.1-14-26

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
//	  //	��������� � ����������\������������ ��������� �������
//	  //	����������.
//	  bool SetReadyState (bool State);
//	  //	�������� �� ���������.
//	  bool IsReady (DWORD dwWaitTime = 0	// ����� �������� ������������ (��).
//	  );
//  private:
//	  //	������� ����������/���������.
//	  HANDLE get_m_ReadyEvent ();
//	  void set_m_ReadyEvent (HANDLE value);
//
//  private: 
//	  HANDLE m_ReadyEvent;
//};

//	����� ��������� ������ � �������� � ������.
class CHandlerBase : virtual public CThread/*, 
						public CReadyEvent	*/
{
  public:
	  CHandlerBase();
	  virtual ~CHandlerBase();
	  //	�������� ����������.
	  //	�������� ��������� ������ ������ WM_UPDATETAGSNOW.
//	  BOOL UpdateNow (_UpdateMsg* UpdateNowMsg	// �������������� �����, ������� ����� ��������.
//	  );
	  //	�������� ��������� ������.
	  BOOL StartTimer (DWORD ClockRate=0);
	  //	�������� ��������� �������.
	  BOOL StopTimer ();
	  //	������� ����������� ��������� ���������� ������. (��).
	  //	�������� ��������� ��� ������ ������ ���������� ���� �
	  //	������ ���������� ������ � ����������.
	  void set_m_ClockRate (unsigned int value);
	  CTagStorage * get_m_TagStorage ();
	  void set_m_TagStorage (CTagStorage * value);
	  CDataPlugin * get_m_Device ();
	  void set_m_Device (CDataPlugin * value);
	  //	������������� �������, ������������� �������.
	  DWORD m_TimerID;
	  CTagStorage *m_TagStorage;
  private:
	  //	������� ��������� ��������� �� �������.
	  //	���������� �������� ����� (� ��������� ��� ����������).
	  //	������ ��������� �� �������.
	  //	����� �������� ����� (� ��������� ��� ����������).
	  virtual HRESULT OnTimerMessage (MSG msg	// ��������� �� �������, ����� ���������� ������� �����.
	  ) = 0;
	  //	��������������� �������, �������������� � ������, �
	  //	������-����������.
	  virtual DWORD fbody ()=0;
	  //	������� ������� �� ��������� WM_UPDATETAGSNOW.
//	  virtual HRESULT OnUpdateNow (MSG msg	// ��������� WM_UPDATETAGSNOW c ����������������
		// �����������.
//	  ) = 0;
  private:
	  unsigned int m_ClockRate;
	  CDataPlugin *m_Device;
};

//	����� ��� ���������� ������ � ����������.
//	����� �������� � 2� ���������:
//	1)�������������� ��������������� ��� ������ ������� �
//	����������.
//	2)������� ������ � ����� � ���������� ���������
//	����������� ������. ������ �� ����� � ���.
//	����� ������ �������� � �����-���������� ������ CChannel
//	m_DeviceUpdateMode. (TRUE - ����� 1, FALSE - ����� 2).
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
//	//						//����� ����� ������������ ��������
//	//						// �� ��������� � ������� �����������
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
//	  //	��������������� �������, �������������� � ������, �
//	  //	������-����������.
//	  virtual DWORD fbody ();
//	  //	����� ������ ������ ���������� ������ � ����������.
//	  BOOL get_m_DeviceUpdateMode ();
//	  void set_m_DeviceUpdateMode (BOOL value);
//  private:
//	  //	��������������� ����������� ������� � ����������.
//	  //	������� �������� ������ ��� ������ �����������
//	  //	���������� ����������.
//	  CLogFile_CS &m_LogFile;
//	  HRESULT OnTimerMessage (MSG msg);
//	 // //	������� ������� �� ��������� WM_UPDATETAGSNOW.
//	 // HRESULT OnUpdateNow (MSG msg	// ��������� WM_UPDATETAGSNOW c ����������������
//		//// �����������.
//	//  );
//	  BOOL m_DeviceUpdateMode;
//};

//	����� ��� ���������� ������ �� DEVICE � CACHE.
//	������� ���������� ����� � ������ ������, ��� ���
//	�������� ��� ������.
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
	//						//����� ����� ������������ ��������
	//						// �� ��������� � ������� �����������
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
	  //	��������������� �������, �������������� � ������, �
	  //	������-����������.
	  virtual DWORD fbody ();
	  const CLocalNotify * get_m_ChannelNotify () const;
	  void set_m_ChannelNotify (CLocalNotify * value);
  private:
	  //	��������������� ����������� ������� � ����������.
	  //	���������� ��� ��������� ������� �� �������.
	  virtual HRESULT OnTimerMessage (MSG msg);
	  //	������� ������� �� ��������� WM_UPDATETAGSNOW.
	 // virtual HRESULT OnUpdateNow (MSG msg	// ��������� WM_UPDATETAGSNOW c ����������������
		//// �����������.
	 // );
	  //	���������� ����� ���������� �����. �� ������� ���������
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
	//����� ���-�����
	void ChangeLogFile();
	bool ControlPluginInit();
	void OnReadNow (MSG msg,bool IsEvented);
	void OnWriteNow(MSG msg,bool IsEvented);
//    void OnDeviceRead(MSG msg,bool IsEvented);
	
//��, ��� ���� � DeviceHandler
public:
	//�������� ��������� � ������ ������ �� ���������� (�������).
	//������������ ��� ���������� ������ �� ���������� (� ���� ������ �������,
	//���������� � ��������� ��������������� � Signaled
	void Client_DeviceReadSync(_SyncIORMsg *mes);
	//�������� ��������� � ������ ������ �� ���������� (�������).
	//������������ ��� ����������� ������ �� ����������.
	//�� ��������� �������� �������� ��������� � ���������� � 
	//����������� ����� ������� (������ ���). ������������� ������ ������� 
	//����������� � ���������
	void Client_DeviceReadAsync(_AsyncIORWMsg *mes);
	//�������� ��������� � ������ �� ���� ������.
	//������������ ����������� ������� ������ ��� ��� ���������� 
	//���� ������. � ���� ������ ������ � ��������� ���������� �������,
	//������� ��������������� � Signaled ����� �������� ������
	void Client_CacheRead();
	//�������� ��������� � ������ � ����������
	//������������ ��� ���������� ������ (� ���� ������ �������,
	//���������� � ��������� ��������������� � Signaled
	void Client_DeviceWriteSync(_SyncIORMsg *mes);
	//�������� ��������� � ������ � ����������
	//������������ ��� ����������� ������ 
	//�� ��������� �������� �������� ��������� � ���������� � 
	//����������� ����� ������� (������ ���). ������������� ������ ������� 
	//����������� � ���������
	void Client_DeviceWriteAsync(_AsyncIORWMsg *mes);
	
protected:
//	void DeviceRead(MSG msg);

	// ������� �� ��������� WM_OPC_SYNCREAD
	void OnDeviceReadSync(_SyncIORMsg* mes);
	// ������� �� WM_OPC_ASYNCREAD
	void OnDeviceReadAsync(_AsyncIORWMsg* mes);
	// ������� �� ��������� WM_OPC_SYNWRITE
	void OnDeviceWriteSync(_SyncIORMsg * mes);
	// ������� �� WM_OPC_ASYNCWRITE
	void OnDeviceWriteAsync(_AsyncIORWMsg* mes);
	HRESULT DeviceWrite(DWORD xCount,OPCHANDLE *pH,VARIANT *pV,HRESULT *pE);
public:
	// ������ �� ����������
	HRESULT DeviceRead(void);
};
//	����� ��� ��������� �������������� ���������� ��
//	����������.
//
//class CExternalInfoHandler : public CThread  //## Inherits: <unnamed>%3B42B9920119
//{
//  public:
//	  CExternalInfoHandler();
//	  ~CExternalInfoHandler();
//	  HRESULT GetItemIDs (OPCBROWSETYPE Type,	// ���, ��� �������.
//	  DWORD* pCount,	// ���������� �������� � �������.
//	  LPWSTR* pItemNames);
//	  //	���������� ��� �������� �����. ������.
//	  HRESULT GetAllIDs (LPWSTR* pItemNames, DWORD* pCount);
//	  //	���������� �������������� ���������� �� �����
//	  //	(���������� �� Set2).
//	  HRESULT GetSet2Properties ();
//	  const CDataPlugin * get_m_Device () const;
//	  void set_m_Device (CDataPlugin * value);
//  private:
//	  //	��������������� �������, �������������� � ������, �
//	  //	������-����������.
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
