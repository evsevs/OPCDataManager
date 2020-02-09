// ChannelInfo.cpp: implementation of the CChannelInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "OPCDMConf1.h"
#include "ChannelInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CTagInfo::GetTagDef(TagDefStruct * pTagDef,CString Path)//положить как структурку по указателю
{
	pTagDef->bActive = m_Active;
	pTagDef->bNotifyUpdate = m_NotifyUpdate;
	pTagDef->dwAccessRight = m_dwAccessRights;
	pTagDef->dwUpdateRateMS = m_UpdateRate;
	pTagDef->vtTagType = m_vtVarType;
	
	_bstr_t t;
	t=(LPCSTR)(Path+m_Name);
	pTagDef->bstrTagName = t.copy();
	t=(LPCSTR)m_RealName;
	pTagDef->bstrRealName = t.copy();
	t=(LPCSTR)m_Description;
	pTagDef->bstrTagDescription = t.copy();
	return;
}

