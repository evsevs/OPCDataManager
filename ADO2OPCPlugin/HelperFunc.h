// HelperFunc.h: interface for the HelperFunc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELPERFUNC_H__AAE41C58_B618_483B_BF73_FC8DB178A5B7__INCLUDED_)
#define AFX_HELPERFUNC_H__AAE41C58_B618_483B_BF73_FC8DB178A5B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>
#include <list>
#include <hash_map>
#include <comdef.h>
#include "DMPluginIfs.h"
//#include "DMPluginIfs_i.c"
//##ModelId=3C4E3C7900C9
class PLItem
{
public:
	//##ModelId=3C4E3C7900FB
	OPCHANDLE	hClient;	
	//##ModelId=3C4E3C790110
	OPCHANDLE	hServer;
	//##ModelId=3C4E3C79011A
	FILETIME	ftTimeStamp; 
	//##ModelId=3C4E3C790125
	WORD		wQuality;
	//##ModelId=3C4E3C790157
	_variant_t		vDataValue;
	//##ModelId=3C4E3C79016B
	_bstr_t ItemName;

	//##ModelId=3C4E3C790174
	void ChangeItemValue(WORD wNewQuality,_variant_t wNewValue)
	{
		vDataValue = wNewValue;
		wQuality = wNewQuality;
		SYSTEMTIME now;
		GetSystemTime(&now);
		SystemTimeToFileTime(&now,&(ftTimeStamp));//установка времени;

	};
};




//##ModelId=3C4E3C79019C
class ItemAssoc
{
public:
	//##ModelId=3C4E3C7901A6
	ItemAssoc()
	{
		NotifyNow=false;
	}
	//##ModelId=3C4E3C7901A8
	_bstr_t ItemName;
	//##ModelId=3C4E3C7901BB
	OPCHANDLE hClient;
	//##ModelId=3C4E3C7901C5
	OPCHANDLE hServer;
	//##ModelId=3C4E3C7901CE
	bool NotifyNow;

	//##ModelId=3C4E3C7901D8
	void Fill(ITEMID* pItemID)
	{
		hClient= pItemID->hClient;
		ItemName = _bstr_t(pItemID->ItemName);
	}
	//##ModelId=3C4E3C7901F7
	PLItem m_it;
	bool operator==(const ItemAssoc &right) const
{
  //## begin _ObjectID::operator==%3B29956E0158_eq.body preserve=yes
	bool RetVal=true;
	RetVal=(right.hClient==hClient);
	return RetVal;
  //## end _ObjectID::operator==%3B29956E0158_eq.body
}
bool operator==(const OPCHANDLE handle) const
{
  //## begin _ObjectID::operator==%3B29956E0158_eq.body preserve=yes
	bool RetVal=true;
	RetVal=(handle==hClient);
	return RetVal;
  //## end _ObjectID::operator==%3B29956E0158_eq.body
}
};

//##ModelId=3C4E3C790200
typedef std::list<ItemAssoc*> NotifyItemList;
typedef stdext::hash_map<long,ItemAssoc*> NotifyItemMap;


//##ModelId=3C4E3C79021E
struct ParametersVal
{
	//##ModelId=3C4E3C790229
	_bstr_t ParamName;
	//##ModelId=3C4E3C790233
	_variant_t ParamValue;
};
//extern bool ParseInitializationString(const _bstr_t InitString,std::vector<ParametersVal> &ParamStruct);


#endif // !defined(AFX_HELPERFUNC_H__AAE41C58_B618_483B_BF73_FC8DB178A5B7__INCLUDED_)
