//	���� ������ 18.07.2001 16:39:38
//	������ �.�.
//	����, �� ��� ��
//	�.415 �.1-14-26
#ifndef DataPlugin_h
#define DataPlugin_h 1

#include "stdafx.h"
#include "DMPluginIfs.h"
#include "SimpleLogFile.h"
#include "_Message.h"
// LocalNotify
#include "LocalNotify.h"
//	����� ��������� ������� �������.

class CDataPlugin;

//�������� �����������
class CPluginNotifyListener://��������
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

	CDataPlugin *m_Owner;//��������� �� ����� �������� ���������

	STDMETHOD (OnDeviceNotAvailable)(void);
	STDMETHOD (OnTagsChange)(DWORD dwCount, DWORD* phClientItems, VARIANT *pvValues,WORD* pwQualities,FILETIME*  pftTimeStamps, HRESULT * pErrors);
};

class CDataPlugin 
{
 friend class CPluginNotifyListener;
  public:
	  CDataPlugin(CLogFile_CS &lf);
	  ~CDataPlugin();
	  //�������� �����������
	CComObjectNoLock<CPluginNotifyListener> * m_NotifyListener;
	  //	�������� ��� ����������� �������� �� ������ ��������
	  //	����������� ��������.
	  //	true - ��������.
	  //	false - �� ��������.
	  bool IsConstDataPlugin ();
	  //	����� ������������� ������� (����������, ���.
	  //	����������).
	  //	�������� ���������� m_Init �� �����.
	  //	���������� m_Init=true.
	  HRESULT InitializePlugin (_bstr_t bstrPluginString);
	  //	�������� ��������������� �������. ��� ���� �������������
	  //	��������� �������� �������.
	  //	������ ��������������� (m_Init==true).
	  //	��������� COM ������� != NULL.
	  //	������ ����������������� (m_Init==false).
	  //	������������� �������. ���������=NULL.
	  HRESULT DeinitializePlugin ();
	  //	����� ��� ��������� ������ �� �������.
	  HRESULT GetTagsData (_UpdateNowMsg2* TagsNow);
	  //	����� ��� �������� �������� ����� � ����������.
	  HRESULT SetTagsData (_UpdateNowMsg* TagsData);
	  HRESULT AddTagsNotify (_TagID* phClient, DWORD Count, DWORD UpdateRate, HRESULT** pError);
	  //	����� ������ ����������� �� ��������� ���������� �����.
	  HRESULT DelTagsNotify (_TagID* phClient, DWORD Count, HRESULT** pError);
	  //	���������� ��������� ��������� ������.
	  HRESULT GetState (WORD wState // ��������� �������. ������������ (���� ���).
  );
	  //	CLSID ������������� ��� ������ � ��������.
	  //	���� CLSID== (
	  //	   {93A34F8E-CA92-43d3-9B92-51B769CD739C}
	  //	static const GUID CLSID_ConstDataOPCPlugin ={ 0x93a34f8e, 0xca92, 0x43d3, { 0x9b, 0x92, 0x51, 0xb7,	0x69, 0xcd, 0x73, 0x9c } }
	  //	), �� ����"������" ������������ ����������� ��������.
	  CLSID get_m_ChannelPluginCLSID ();
	  void set_m_ChannelPluginCLSID (CLSID value);
	  HRESULT SetNewLogForPlugin(std::string postfix);
	  const CLocalNotify * get_m_CacheNotify () const;
	  void set_m_CacheNotify (CLocalNotify * value);
  public:
	  //	���������� ��� �������� ���������� � ��������� �������.
	  //	true - ������ ���������������, false - ������
	  //	�����������������.
	  // 
	  _bstr_t m_bstrPluginStringX;
	  bool get_m_Init ();
	  void set_m_Init (bool value);
	  //	ProgID ��� �������.
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
	  //	������ ������������� �������.
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
