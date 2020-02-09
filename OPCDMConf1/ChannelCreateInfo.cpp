// ChannelCreateInfo.cpp: implementation of the CChannelCreateInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OPCDMConf1.h"
#include "ChannelCreateInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChannelCreateInfo::CChannelCreateInfo()
{

}

CChannelCreateInfo::~CChannelCreateInfo()
{

}

void CChannelCreateInfo::GetCreateStruct(ChannelDef &ChDef)
{
	
	CComBSTR d;
	d=m_ChannelName;
	ChDef.ChannelName = d.Copy();
	d=m_ChannelCnfg;
	ChDef.ChannelCnfg = d.Copy();
	d=this->m_PluginProgID;
	ChDef.PluginProgID = d.Copy();
	d=this->m_PluginCnfg;
	ChDef.PluginCnfg = d.Copy();
	ChDef.ChannelMode = 2;//this->m_ChannelMode;
	ChDef.UpdateRate = this->m_ChannelUpdateRate;
	d=this->m_Description;
	ChDef.ChannelDescription = d.Copy();
	ChDef.DeviceUpdateMode = 1l;//this->m_DeviceUpdateMode;
}
