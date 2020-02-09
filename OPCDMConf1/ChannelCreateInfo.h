// ChannelCreateInfo.h: interface for the CChannelCreateInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHANNELCREATEINFO_H__1EC7C5BD_4772_4FBD_9765_74CE8818110B__INCLUDED_)
#define AFX_CHANNELCREATEINFO_H__1EC7C5BD_4772_4FBD_9765_74CE8818110B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChannelCreateInfo  
{
public:
	void GetCreateStruct(ChannelDef &ChDef);
	CChannelCreateInfo();
	virtual ~CChannelCreateInfo();
	CString m_ChannelName;
	CString m_Description;
	CString m_ChannelCnfg;
	CString m_PluginProgID;
	CString m_PluginCnfg;
	UINT	m_ChannelUpdateRate;
	UINT    m_ChannelMode;
	UINT	m_DeviceUpdateMode;
};

#endif // !defined(AFX_CHANNELCREATEINFO_H__1EC7C5BD_4772_4FBD_9765_74CE8818110B__INCLUDED_)
