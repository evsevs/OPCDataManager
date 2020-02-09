// OPCPlug.cpp : Implementation of COPCPlug
#include "stdafx.h"
#include "OPC2OPCPlugin.h"
#include "OPCPlug.h"
#include "comdef.h"
/////////////////////////////////////////////////////////////////////////////
// COPCPlug

/////////////////////////////////////////////////////////////////////////////
// COPCPlug

#include "opccomn_i.c"
#include "opcda_i.C"
#include "spacebrowse_i.c"
#include "DMPluginIfs_i.c"
#include "opcenum_clsid.c"

_variant_t COPCPlug::GetParameter(const _bstr_t ParamName,std::vector<ParametersVal> &ParVal)
{
	_variant_t val;
	std::vector<ParametersVal>::iterator itv;
	bool IsFlag=false;
	for(itv=ParVal.begin();itv!=ParVal.end();++itv)
	{
		if (itv->ParamName==ParamName)
		{
			val=itv->ParamValue;
			IsFlag=true;
			break;
		}
	}

	if (!IsFlag)
	{
		VariantInit(&val);//������������� VT_EMPTY
	}

	return val;
}
bool COPCPlug::ParseInitializationString(const _bstr_t InitString,std::vector<ParametersVal> &ParamStruct)
{
	
	const char	Ex[]=";= \n\b\f\r\0";//������� ��� ������
	std::string ConfStr=(char*)InitString;
//	std::string::iterator ItStrF,ItStrL;
	int x,x1,x2;
	while ((x=ConfStr.find_first_not_of(Ex))>=0)
	{
		ConfStr=ConfStr.substr(x);
		//��������� �������� ���������
		x1=ConfStr.find_first_of(Ex);
		ParametersVal MyVal;
		if (x1!=-1)//npos
		{
			MyVal.ParamName=ConfStr.substr(0,x1).c_str();
			ConfStr=ConfStr.substr(x1);
		}	
		else break;

		x=ConfStr.find_first_of(';');
		x2=ConfStr.find_first_of('=');
		if((x<x2)&&(x!=-1)) continue;
		//��������� �������� ���������
		if ((x=ConfStr.find_first_not_of(Ex))>=0)
		{
			ConfStr=ConfStr.substr(x);
			if((x1=ConfStr.find_first_of(Ex))>=0)
			{
				MyVal.ParamValue=ConfStr.substr(0,x1).c_str();
				ConfStr=ConfStr.substr(x1);
			}
			else 
				if (ConfStr.length()>0) {
					MyVal.ParamValue=ConfStr.substr(0).c_str();
					ConfStr="";
				}
					
		}
		ParamStruct.insert(ParamStruct.begin(),MyVal);
		
	}
	
 int l=ParamStruct.size();
return true;
	
	
};

bool COPCPlug::IsInGroup(OPCHANDLE handle,OPCHANDLE &hServer)
{
	bool Ret=false;
	NotifyItemMap::iterator itm;
	itm=m_ItemList.find(handle);
	if (itm==m_ItemList.end())
	{
		hServer=-1;
		Ret= false;
	}
	else
	{
		hServer=(itm->second)->hServer;
		return true;
	}
	itm=m_NotiItems.find(handle);
	if (itm==m_NotiItems.end())
	{
		hServer=-1;
		return false;
	}
	else
	{
		hServer=(itm->second)->hServer;
		return true;
	}
}
//##ModelId=3C4E3C780356
STDMETHODIMP COPCPlug::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IPluginConfig,
			&IID_IPluginData,
			&IID_ISpaceBrowse
	};
	for (int i=0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

STDMETHODIMP COPCPlug::SetFullLogFileName(BSTR LogFileName)
{
	USES_CONVERSION;
	m_LogFile.SetNewFullLogName(W2A(LogFileName));
	return S_OK;
}
STDMETHODIMP COPCPlug::GetBrowser(IUnknown**pBrowUnk)
{
	if (!IsConfigured) return S_FALSE;
	if (IsDisconnected) return S_FALSE;
	IOPCBrowseServerAddressSpace * pB;
	HRESULT hr = m_pServer->QueryInterface(IID_IOPCBrowseServerAddressSpace,(void**)&pB);
	if (FAILED(hr))
		return hr;
	CComObjectNoLock<CBrowseObj>* pBrowse=new CComObjectNoLock<CBrowseObj>;
	pBrowse->FinalConstruct();
	pBrowse->pBrowse.Attach(pB);
	*pBrowUnk=pBrowse->GetUnknown();
	return S_OK;
}

//##ModelId=3C4E3C7803E0
STDMETHODIMP COPCPlug::AddNotifyTags(ITEMID *ClientTagID, DWORD dwCount, DWORD dwUpdateRate, HRESULT **pError)
{
	if (!IsConfigured)//���� �� ���������������
		return E_FAIL;
	if (IsDisconnected)
		return E_FAIL;
	if (!bStatus)
		return E_FAIL;
	ATLTRACE("����� AddNotifyTags\n");

 USES_CONVERSION;

	Lock();
	//����� ���� � �������� �� ����������� � �������� ������ �������.
	//������� ��������� ������������
	HRESULT hr=S_OK;
	if (!m_pNotify)
	{
	if (IsServerVersion203())//203
	{
		
		CComObjectNoLock<CNotify_IOPCDataCallback<COPCPlug> > * pNot = new CComObjectNoLock<CNotify_IOPCDataCallback<COPCPlug> >;
		if (pNot)
		{
			pNot->FinalConstruct();
			m_pNotify=(CNotifyBase<COPCPlug>*)pNot;
		}
		else
		{
			Unlock();
			return E_FAIL;
		}
	}else //10a
	{
		CComObjectNoLock<CNotify_IAdviseSink<COPCPlug> > * pNot = new CComObjectNoLock<CNotify_IAdviseSink<COPCPlug> >;
		if (pNot)
		{
			pNot->FinalConstruct();
			m_pNotify=(CNotifyBase<COPCPlug>*)pNot;
		}
		else
		{
			Unlock();
			return E_FAIL;
		}
	}

	m_pNotify->SetOwner(this);
		ATLTRACE("������� ��������\n");
	hr=m_pNotify->ConnectToNotify(0);
		ATLTRACE("�������� ���������\n");
	if (FAILED(hr))
	{

		m_LogFile<<"�� ����������� �� �����������";	
		delete m_pNotify;
		m_pNotify=NULL;
		Unlock();
		return E_FAIL;
	}
	}
	ItemAssoc * pIA = new ItemAssoc[dwCount];
	
	//� ���������� ��������� �������� ����� ��� ���. ����� 
	//��� ����, ����� ������ ��� �� ������������.
	//����� �������� ���� UpdateRate

	//�������� ���� ��������� c ����������� � ������ ��� ������� �����.
	OPCITEMDEF * pDef=(OPCITEMDEF*)CoTaskMemAlloc(sizeof(OPCITEMDEF)*dwCount);
	OPCITEMRESULT * pRes=NULL;
	HRESULT * pEr=NULL;
	int inn=0;
	for (int i=0;i<dwCount;i++)
	{
		m_LogFile<<(char*)_bstr_t((ClientTagID+i)->ItemName);
		(pDef+i)->bActive=true;
		(pDef+i)->dwBlobSize=0;
		(pDef+i)->hClient = (ClientTagID+i)->hClient;
		(pDef+i)->pBlob=NULL;
		(pDef+i)->vtRequestedDataType=VT_EMPTY;
		(pDef+i)->wReserved=0;
		(pDef+i)->szItemID=A2W((char*)_bstr_t((ClientTagID+i)->ItemName));
		(pDef+i)->szAccessPath=A2W("");
		if (SUCCEEDED(hr=m_Group->ValidateItems(1,pDef+i,FALSE,&pRes,&pEr)))
		{//����� ������� Canonical ��� ������	
			(pDef+i)->vtRequestedDataType=pRes->vtCanonicalDataType;
			CoTaskMemFree(pRes);
			pRes=NULL;
			CoTaskMemFree(pEr);
			pEr=NULL;
		}
		inn++;
	}
	if (SUCCEEDED(hr=m_Group->AddItems(dwCount,pDef,&pRes,&pEr)))	
	{
		*pError=(HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
		//��������� � ������ ������
		for (int y=0;y<dwCount;y++)
			if (SUCCEEDED(*(pEr+y)))
			{
				ItemAssoc * pAss = new ItemAssoc;
				pAss->Fill(ClientTagID+y);
				pAss->hServer=(pRes+y)->hServer;
				m_NotiItems.insert(NotifyItemMap::value_type((ClientTagID+y)->hClient,pAss));
			}
			else
			{
				*(*pError+y)=*(pEr+y);
				m_LogFile<<"ERROR!!! �� ���� �������� ���!";
			}
		CoTaskMemFree(pRes);
		pRes=NULL;
		CoTaskMemFree(pEr);
		pEr=NULL;
	}
	Unlock();
	return hr;
}

//##ModelId=3C4E3C7803D5
STDMETHODIMP COPCPlug::DelNotifyTags(ITEMID *ClientTagID, DWORD dwCount)
{

	// TODO: Add your implementation code here
	if (!IsConfigured)//���� �� ���������������
		return E_FAIL;
	if (!bStatus)
		return E_FAIL;

	return S_OK;
}

//##ModelId=3C4E3C7803C3
STDMETHODIMP COPCPlug::Configure(BSTR CnfgString)
{
	CoInitializeEx(NULL,COINIT_MULTITHREADED);
Reset();	
Lock();

USES_CONVERSION;
	m_LogFile<<"=============================";
	m_LogFile<<"������������ ������� OPC2OPC.";
	m_LogFile<<std::string(std::string("������ �����������: ")+W2A(CnfgString)).c_str();
	
	HRESULT hr=S_OK;
	FlagLocal=false;
	
	ParseInitializationString(CnfgString,MyParams);
	_variant_t v;
	v=GetParameter("OPCServerName_GUID_or_ProgID",MyParams);//����� ���� � ���� GUID � ProgID
	if (v.vt!=VT_EMPTY)//���� ���������� ����� ���������
	{
		OPCServerName=(char*)(_bstr_t)v;

		if (*OPCServerName.data()=='{')//�� ��� GUID
		{
			ServerProgID="";
			hr=CLSIDFromString(A2OLE(OPCServerName.c_str()),&ServerGUID);
		}
		else//ProgID
			ServerProgID=OPCServerName.c_str();
	}
	else
		hr=E_FAIL;

	if (FAILED(hr)) 
	{
		m_LogFile<<"Error! �� ���� ������������� �������� ������ CLSID � CLSID.";
		Unlock();
		return hr;
	}


	//���� ��� ���������� (���� �� ���������� - �������� ���������)
	v=GetParameter("Computer_Name_or_IP",MyParams);

	if (v.vt!=VT_EMPTY)//���� ���������� ����� ���������
	{

		FlagLocal=false;
		ComputerName=(char*)(_bstr_t)v;
	}
	else
	{
		ComputerName="";
		FlagLocal=true;
	}

//���� ������� ����� ���� ���
	m_ConfigCS.Lock();
	if (!FlagLocal)
	{
		COSERVERINFO MySF;
		MySF.dwReserved1=0;
		MySF.dwReserved2=0;
		MySF.pAuthInfo=NULL;//������ �� ���������
		MySF.pwszName = A2W(ComputerName.c_str());
		MULTI_QI MyQI;
		MyQI.pIID = &IID_IOPCServer;
		MyQI.pItf =NULL;
		MyQI.hr=0;
	
		if (ServerProgID=="")//��� �������� � ������ GUID�
		{
			hr=CoCreateInstanceEx(ServerGUID,0,CLSCTX_REMOTE_SERVER,&MySF,1,&MyQI);
			if (SUCCEEDED(hr))
			{
				hr=MyQI.pItf->QueryInterface(IID_IOPCServer,(void**)&m_pServer);
				MyQI.pItf->Release();
			}
		}else
		{ //������ ��� Enumerator
			MyQI.pIID=&IID_IOPCServerList; 
 			hr=CoCreateInstanceEx(CLSID_OPCServerList,0,CLSCTX_ALL,&MySF,1,&MyQI);
			if (SUCCEEDED(hr))
			{
				IOPCServerList * pSRVList; 
				hr=MyQI.pItf->QueryInterface(IID_IOPCServerList,(void**)&pSRVList);
				MyQI.pItf->Release();
				//������ ������ GUID
				hr=pSRVList->CLSIDFromProgID(A2OLE(ServerProgID.c_str()),&ServerGUID);
				if (SUCCEEDED(hr))
				{	//������ ������� ��� ������ ���������
					MyQI.pIID = &IID_IOPCServer;
					MyQI.pItf=NULL;
					hr=CoCreateInstanceEx(ServerGUID,0,CLSCTX_REMOTE_SERVER,&MySF,1,&MyQI);
					if (SUCCEEDED(hr))
					{
						hr=MyQI.pItf->QueryInterface(IID_IOPCServer,(void**)&m_pServer);
						MyQI.pItf->Release();
						m_LogFile<<"����� ������� ������";
					}
					else
					{
						m_LogFile<<"�� ������� ������";
					}
				}
				pSRVList->Release();
			}
		}
		
	}else
	{
		if (ServerProgID!="")
			hr=CLSIDFromProgID(A2OLE(ServerProgID.c_str()),&ServerGUID);
		if (SUCCEEDED(hr))
			hr=CoCreateInstance(ServerGUID,NULL,CLSCTX_ALL,IID_IOPCServer,(void**)&m_pServer);
	}

	//����� �������� ������� �������� ������
	if (SUCCEEDED(hr))
	{ //��������, ������ ����� ������� ������
		CComPtr<IOPCItemMgt> pGroup;
		DWORD Ur;
		m_LogFile<<"������ common";
		m_pServer->QueryInterface(IID_IOPCCommon,(void**)&m_pCommon);
		m_LogFile<<"������� ������";

		//��������� ���������� �� ������ ������������
		v=GetParameter("GroupUpdateRate",MyParams);
		long UR=300;
		if (v.vt!=VT_EMPTY)//���� ���������� ����� ���������
		{
			try
			{
				UR=(long)v;
			}catch(...)
			{
				m_LogFile<<"WARNING!!! �������� GroupUpdateRate �� ���������. ������������� �� ��������� = 500 ��";
				UR=300;
			}
		}
		v=GetParameter("GroupReadSource",MyParams);
		m_GroupReadSource=OPC_DS_CACHE;
		if (v.vt!=VT_EMPTY)//���� ���������� ����� ���������
		{
			try
			{
				m_GroupReadSource=(OPCDATASOURCE)(long)v;
			}catch(...)
			{
				m_LogFile<<"WARNING!!! �������� GroupReadSource �� ���������. ������������� �� ��������� = 1";
				m_GroupReadSource=OPC_DS_CACHE;
			}
		}
		
		hr=m_pServer->AddGroup(A2W("x"),TRUE,(DWORD)UR,m_GroupHandleClient,NULL,NULL,0x0409,&m_GroupHandleServer,&Ur,IID_IOPCItemMgt,(IUnknown**)&m_Group);
		if (SUCCEEDED(hr))
		{
			m_LogFile<<"������� ������";
			//������� ������ (��������). � �������� ������ ������ �� �����
			//m_Groups.insert(m_Groups.end(),pGroup);
			IsConfigured=true;	
			IsDisconnected=false;
			bStatus=true;
		//	pGroup.Release();
		}
		else 
		{
			m_LogFile<<"�� ������� ������";
			IsDisconnected=true;
			IsConfigured=false;
			m_pServer.Release();
		}
	}
	if (SUCCEEDED(hr))
	{
		//���������� - � �����
	//	CoMarshalInterThreadInterfaceInStream(IID_IOPCServer,(IUnknown*)m_pServer,&m_pStreamOPCServer);
	//	CoMarshalInterThreadInterfaceInStream(IID_IOPCGroupStateMgt,(IUnknown*)m_Groups[0].m_T,&m_pStreamOPCGroup);
		SetControlThreadSettings(MyParams);//��������� ��������� ������ ��������
		m_ControlThread.SetOwner(this);
		m_LogFile<<"Start ControlThread";
		m_ControlThread.run();
	}
	m_ConfigCS.Unlock();
	Unlock();
	m_LogFile<<"������� �� Configure";
	return hr;
}

//##ModelId=3C4E3C7803C1
STDMETHODIMP COPCPlug::Reset()
{

	if (!IsConfigured) return S_OK;
	IsConfigured=false;
	Lock();

	m_ConfigCS.Lock();
	//����������
	DisconnectFromAll();
	//������� �������
	m_ControlThread.Stop();
	NotifyItemMap::iterator itl;
	
	for(itl=m_ItemList.begin();itl!=m_ItemList.end();++itl)
	{
		ItemAssoc* p;
		p=(itl->second);
		delete p;
	}
	m_ItemList.clear();
	for(itl=m_NotiItems.begin();itl!=m_NotiItems.end();++itl)
	{
		ItemAssoc* p;
		p=(itl->second);
		delete p;
	}
	m_NotiItems.clear();
	
	m_ConfigCS.Unlock();
	Unlock();
	return S_OK;
}



//##ModelId=3C4E3C7803A3
STDMETHODIMP COPCPlug::GetTags(ITEMID *ClientTagID, DWORD dwCount, OPCITEMSTATE **pOutStruct, HRESULT **ppErrors)
{
	USES_CONVERSION;
	HRESULT hr=S_OK;
	try{

	if (IsDisconnected)
		{
		*ppErrors=NULL;
		*pOutStruct=NULL;
		return E_FAIL;
	}
	if (!IsConfigured)//���� �� ���������������
		{
		*ppErrors=NULL;
		*pOutStruct=NULL;
		return E_FAIL;
	}
	if (!bStatus){
		*ppErrors=NULL;
		*pOutStruct=NULL;
		return E_FAIL;
	}
	Lock();
	m_ConfigCS.Lock();
	OPCITEMDEF * pDef=(OPCITEMDEF*) CoTaskMemAlloc(sizeof(OPCITEMDEF)*dwCount);

	OPCITEMRESULT * pResult;
	HRESULT *pEr;
	//��� ��� ����������� ���������� ���������� ����� ( � ���� ����) �� ����� (�����
	//������� ��������� ������������ ����������������� �������), �� �������� ���������� ��������.
	m_LogFile<<"������";
	if (m_xpHandles==NULL)
	{
		/*OPCHANDLE **/ m_xpHandles= (OPCHANDLE*)CoTaskMemAlloc(sizeof(OPCHANDLE)*dwCount);
		FillMemory(m_xpHandles,sizeof(OPCHANDLE)*dwCount,0xFFFFFFFF);

		for (int i =0;i<dwCount;i++)
	{ //�� ���� �������������� ������
		
		if (!IsInGroup((ClientTagID+i)->hClient,*(m_xpHandles+i)))
		{//���� ���� � ������ 
			(pDef+i)->bActive=TRUE;
			(pDef+i)->dwBlobSize=0;
			(pDef+i)->hClient = (ClientTagID+i)->hClient;
			(pDef+i)->pBlob=NULL;
			(pDef+i)->vtRequestedDataType=VT_EMPTY;
			(pDef+i)->wReserved=0;
			(pDef+i)->szItemID=A2W((char*)_bstr_t((ClientTagID+i)->ItemName));

			(pDef+i)->szAccessPath=A2W("");
			if (SUCCEEDED(hr=m_Group->ValidateItems(1,pDef+i,FALSE,&pResult,&pEr)))
			{//����� ������� Canonical ��� ������	
				(pDef+i)->vtRequestedDataType=pResult->vtCanonicalDataType;
				CoTaskMemFree(pResult);
				pResult=NULL;
				CoTaskMemFree(pEr);
				pEr=NULL;
				if (SUCCEEDED(hr=m_Group->AddItems(1,pDef+i,&pResult,&pEr)))	
				{
					//��������� � ������ ������
					if (SUCCEEDED(*pEr))
					{
						ItemAssoc * pAss = new ItemAssoc;
						pAss->Fill(ClientTagID+i);
						pAss->hServer=pResult->hServer;
						*(m_xpHandles+i)=pAss->hServer;
						m_ItemList.insert(NotifyItemMap::value_type((ClientTagID+i)->hClient,pAss));
					}
					else
					{
						m_LogFile<<"ERROR!!! ������ ��� ���������� ���� � ������.";
					}
					CoTaskMemFree(pResult);
					pResult=NULL;
					CoTaskMemFree(pEr);
					pEr=NULL;
				}
			}
			else
			{
				LPWSTR x;
				
				HRESULT xh=m_pCommon->SetLocaleID(0x0409);
				if (SUCCEEDED(xh=m_pCommon->GetErrorString(hr,&x)))
				{
					m_LogFile<<_bstr_t("ERROR!!! ") + W2A(x);
					CoTaskMemFree(x);
				}
				else
					m_LogFile<<_bstr_t("ERROR!!! �� ���� �������� ������ �������� ������ ��� �������. ErrorCode=")+_bstr_t(_variant_t(long(xh)));
			}
		}	
	}
	}
	CoTaskMemFree(pDef);
	
	//for(int fff=0;fff<dwCount;fff++)
	//{
	//	m_LogFile<<(unsigned long)*(m_xpHandles+fff);
	//}
	//IOPCSyncIO* pSync=NULL;
	if (m_xpSync==NULL)
	{	
		hr=m_Group->QueryInterface(IID_IOPCSyncIO,(void**)&m_xpSync);
	}
	if (m_xpSync!=NULL)
	{
		try{
			
			m_LogFile<<"Read";
			m_LogFile<<(long)dwCount;
			m_LogFile<<(long)m_GroupReadSource;
			//OPC
			OPCITEMSTATE *sdf=NULL;
			HRESULT *eee=NULL;
			
			hr=m_xpSync->Read(m_GroupReadSource,dwCount,m_xpHandles,pOutStruct,ppErrors);
			//CoTaskMemFree(sdf);
			//CoTaskMemFree(eee);
//			hr=E_FAIL;
//			*pOutStruct=NULL;//sdf;
//			*ppErrors=NULL;//eee;
			m_LogFile<<"End of Read";

			if (FAILED(hr))
			{
				m_LogFile<<"�������� ��������� �� ������";
				LPWSTR x;
				HRESULT xh=m_pCommon->SetLocaleID(0x0409);
				xh=m_pCommon->GetErrorString(hr,&x);
				m_LogFile<<W2A(x);
				CoTaskMemFree(x);
	//			int xw;
	//			xw++;
			}
			
		//	pSync->Release();
	//		CoTaskMemFree(m_xpHandles);
		}catch(...)
		{
			hr=E_FAIL;
			ATLTRACE("��������� ��� ������ ������ Read ������� ���\n");
		}
	}else
	{
//		CoTaskMemFree(m_xpHandles);
		*pOutStruct=NULL;
		*ppErrors=NULL;
	}
	m_ConfigCS.Unlock();
	Unlock();
	m_LogFile<<"End of GetTags";
	}catch(...)
		{
			hr=E_FAIL;
		ATLTRACE("������ �� � OPC2OPCPlugin\n");
		}
		m_LogFile<<"�����";
	return hr;
}

//##ModelId=3C4E3C780386
STDMETHODIMP COPCPlug::SetTags(ITEMID *ClientTagID, DWORD Count, VARIANT *pItemValues, HRESULT **ppErrors)
{
	USES_CONVERSION;
	if (IsDisconnected)
		return E_FAIL;
	if (!IsConfigured)//���� �� ���������������
		return E_FAIL;
	if (!bStatus)
		return E_FAIL;

	Lock();
	m_ConfigCS.Lock();
	OPCITEMDEF * pDef=(OPCITEMDEF*) CoTaskMemAlloc(sizeof(OPCITEMDEF)*Count);
	OPCHANDLE * pHandles= (OPCHANDLE*)CoTaskMemAlloc(sizeof(OPCHANDLE)*Count);

	OPCITEMRESULT * pResult;
	HRESULT *pEr;

	HRESULT hr=S_OK;
	for (int i =0;i<Count;i++)
	{ //�� ���� �������������� ������
		
		if (!IsInGroup((ClientTagID+i)->hClient,*(pHandles+i)))
		{//���� ���� � ������ 
			(pDef+i)->bActive=true;
			(pDef+i)->dwBlobSize=0;
			(pDef+i)->hClient = (ClientTagID+i)->hClient;
			(pDef+i)->pBlob=NULL;
			(pDef+i)->vtRequestedDataType=VT_EMPTY;
			(pDef+i)->wReserved=0;
			(pDef+i)->szItemID=A2W((char*)_bstr_t((ClientTagID+i)->ItemName));
			(pDef+i)->szAccessPath=A2W("");
			if (SUCCEEDED(hr=m_Group->ValidateItems(1,pDef+i,FALSE,&pResult,&pEr)))
			{//����� ������� Canonical ��� ������	
				(pDef+i)->vtRequestedDataType=pResult->vtCanonicalDataType;
				CoTaskMemFree(pResult);
				pResult=NULL;
				CoTaskMemFree(pEr);
				pEr=NULL;
				if (SUCCEEDED(hr=m_Group->AddItems(1,pDef+i,&pResult,&pEr)))	
				{
					//��������� � ������ ������
					if (SUCCEEDED(*pEr))
					{
						ItemAssoc * pAss = new ItemAssoc;
						pAss->Fill(ClientTagID+i);
						pAss->hServer=pResult->hServer;
						*(pHandles+i)=pAss->hServer;
						m_ItemList.insert(NotifyItemMap::value_type((ClientTagID+i)->hClient,pAss));
					}
					else
					{
						m_LogFile<<"ERROR!!! ������ ��� ���������� ���� � ������.";
					}

					CoTaskMemFree(pResult);
					pResult=NULL;
					CoTaskMemFree(pEr);
					pEr=NULL;
				}
			}	
		}
	}
	CoTaskMemFree(pDef);
	IOPCSyncIO* pSync;
	if  (SUCCEEDED(hr=m_Group->QueryInterface(IID_IOPCSyncIO,(void**)&pSync)))
	{
		hr=pSync->Write(Count,pHandles,pItemValues,ppErrors);
		pSync->Release();
		CoTaskMemFree(pHandles);
	}
	m_ConfigCS.Unlock();
	Unlock();
	return hr;
}

//##ModelId=3C4E3C78037C
STDMETHODIMP COPCPlug::GetState(DWORD State)
{
	// TODO: Add your implementation code here
	if (!IsConfigured)//���� �� ���������������
		return E_FAIL;
	if (!bStatus)
		return E_FAIL;

	return S_OK;
}

////##ModelId=3C4E3C79002A
//STDMETHODIMP COPCPlug::BrowseAccessPaths(/*[in]*/LPCWSTR szItemID,/*[out]*/ LPENUMSTRING *ppIEnumString)
//{
//	return E_NOTIMPL;
//}
////##ModelId=3C4E3C79003D
//STDMETHODIMP COPCPlug::GetItemID(/*[in]*/LPCWSTR szItemDataID, /*[out]*/LPWSTR *szItemID)
//{
//	/*�����*/
//	return S_OK;
//}
////##ModelId=3C4E3C790051
//STDMETHODIMP COPCPlug::BrowseOPCItemIDs(/*[in]*/ OPCBROWSETYPE  dwBrowseFilterType,/*[in]*/ LPCWSTR  szFilterCriteria, /*[in]*/ VARTYPE	vtDataTypeFilter, /*[in]*/ DWORD	dwAccessRightsFilter,	 /*[out]*/ LPENUMSTRING  * ppIEnumString)
//{
//	/*�����*/
//	
//	return S_OK;
//}
////##ModelId=3C4E3C790066
//STDMETHODIMP COPCPlug::ChangeBrowsePosition(/*[in]*/ OPCBROWSEDIRECTION dwBrowseDirection,/*[in]*/ LPCWSTR  szString)
//{
////	CComPtr<IOPCBrowseServerAddressSpace> pBrows;
////	HRESULT hr=m_pServer->QueryInterface(IID_IOPCBrowseServerAddressSpace,(void**)&pBrow);
////	if (FAILED(hr)) return hr;
//	
//	//���� ��
//
//
//	return S_OK;
//}
////##ModelId=3C4E3C790083
//STDMETHODIMP COPCPlug::QueryAvailableProperties(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR **ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes)
//{
//	/*�����*/
//	return S_OK;
//}
////##ModelId=3C4E3C790099
//STDMETHODIMP COPCPlug::GetItemProperties(/*[in]*/ BSTR ItemID,/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ DWORD * pdwPropertyIDs,/*[out, size_is(,dwCount)] */VARIANT ** ppvData,/*[out, size_is(,dwCount)]*/ HRESULT **ppErrors)
//{
//	/*�����*/
//	
//	return S_OK;
//}
////##ModelId=3C4E3C79000D
//STDMETHODIMP COPCPlug::ValidateItem(DWORD dwCount, OPCITEMDEF *pItemArray, BOOL bBlobUpdate, OPCITEMRESULT **ppValidationResults, HRESULT **ppErrors)
//{
//	// TODO: Add your implementation code here
//	/*�����*/
//	return S_OK;
//}
//
//##ModelId=3C4E3C780371
STDMETHODIMP COPCPlug::GetExampleCnfg(BSTR *bstrExampleCnfg)
{
	_bstr_t x;
	x="OPCServerName_GUID_or_ProgID=FactorySoft.Sample;Computer_Name_or_IP=ASU-EROHIN;";
	*bstrExampleCnfg=x.copy();

	return S_OK;
}

HRESULT COPCPlug::DisconnectFromAll()
{
   m_LogFile<<"���������� ������� �� ���������";
	//TODO: ���������, ������ ��� ����� ��������� ������� (� ��������� WinCC) ����������� ������ (� ������ GetTags)
	if (!IsConfigured) return S_OK;
	if (IsDisconnected) return S_OK;
	IsDisconnected=true;
	//�������� �� �������
	//m_ControlThread.Stop();

	try{
	
	//���������� �����������
	if(m_pNotify)
	{
		m_pNotify->DisconnectFromNotify(0);
		delete m_pNotify;
		m_pNotify=NULL;
	}
	//������ 
	

	//������ �����
	OPCHANDLE *pSHandle = (OPCHANDLE*)CoTaskMemAlloc(sizeof(OPCHANDLE)*m_ItemList.size()+sizeof(OPCHANDLE)*m_NotiItems.size());
	HRESULT* pEr=NULL;
	//��������

	NotifyItemMap::iterator itl;
	int in=0;
	//�������� ������
	for(itl=m_ItemList.begin();itl!=m_ItemList.end();++itl)
	{
		*(pSHandle+in)=(itl->second)->hServer;
		in++;
	}
	//�� ������ ������ ��� �����������
	for(itl=m_NotiItems.begin();itl!=m_NotiItems.end();++itl)
	{
		*(pSHandle+in)=(itl->second)->hServer;
		in++;
	}

	if (m_Group.p)
	{
		m_Group->RemoveItems(in,pSHandle,&pEr);
	//������� �� ���������
		if (pEr)
			CoTaskMemFree(pEr);
	}

	CoTaskMemFree(pSHandle);
	m_Group.Release();
	//������ ������
	if (m_pServer)
	{
		m_pServer->RemoveGroup(m_GroupHandleServer,TRUE);
		//���������� �� �������
		m_pServer.Release();
	}	
	}catch(...)
	{
		m_LogFile<<"sweqwljierhqwlkhelqkwhelkqwhelkqwhelkqwhelkhqwlekhqwlkehqlwkhelqwhelqwhelqhwe";
	}
	return S_OK;

}

void COPCPlug::SetControlThreadSettings(std::vector<ParametersVal> &ParVal)
{
	variant_t v=GetParameter("ServerStatusControlPeriod",ParVal);
	m_ControlThreadPeriod=10000;
	if (v.vt!=VT_EMPTY)//���� ���������� ����� ���������
	{
		try{	
			m_ControlThreadPeriod=((long) v)*1000;
		}catch(...)
		{
			m_LogFile<<"WARNING!!! �������� ServerStatusControlPeriod �� ���������.������������� �� ��������� = 10 ���";
			m_ControlThreadPeriod=10000;
		}
	}
	
	v=GetParameter("ResetErrorCount",ParVal);
	m_ControlThreadErCount=1;// ��� ������
	if (v.vt!=VT_EMPTY)//���� ���������� ����� ���������
	{
		try
		{
			m_ControlThreadErCount=((long) v);
		}catch(...)
		{
			m_LogFile<<"WARNING!!! �������� ResetErrorCount �� ���������.������������� �� ��������� = 1";
			m_ControlThreadErCount=10000;
		}

	}
}

bool COPCPlug::IsServerVersion203()
{
	//������� ��������� IOPCAsyncIO2
	IOPCAsyncIO2 * pAS;
	bool Ret=false;
	HRESULT hr;
	if (FAILED(hr=m_Group->QueryInterface(IID_IOPCAsyncIO2,(void**)&pAS)))
		Ret=false;
	else
		Ret=true;

	return Ret;
}
HRESULT COPCPlug::GetOPCServerState(DWORD &dwStatus)
{
	HRESULT hr=S_OK;
	Lock();
	OPCSERVERSTATUS *pSrvStatus=NULL;
	if (m_pServer.p==NULL) return E_FAIL;
	hr=m_pServer->GetStatus(&pSrvStatus);
	if (SUCCEEDED(hr))
	{
		dwStatus=pSrvStatus->dwServerState;
		//��������� ����������
		CoTaskMemFree(pSrvStatus->szVendorInfo);
		CoTaskMemFree(pSrvStatus);
	}
	Unlock();
	return hr;
}

HRESULT COPCPlug::ReInit()
{
	Lock();
	DisconnectFromAll();
	IsConfigured=false;
	//����������������� �����....
	HRESULT hr;
	if (m_xpHandles)
			CoTaskMemFree(m_xpHandles);
	m_xpHandles=NULL;
	m_xpSync->Release();
	m_xpSync=NULL;
	ATLTRACE("ReInit\n");
	USES_CONVERSION;
	if (!FlagLocal)
	{
		COSERVERINFO MySF;
		MySF.dwReserved1=0;
		MySF.dwReserved2=0;
		MySF.pAuthInfo=NULL;//������ �� ���������
		MySF.pwszName = A2W(ComputerName.c_str());
		MULTI_QI MyQI;
		MyQI.pIID = &IID_IOPCServer;
		MyQI.pItf =NULL;
		MyQI.hr=0;
	
		hr=CoCreateInstanceEx(ServerGUID,0,CLSCTX_ALL,&MySF,1,&MyQI);
		if (SUCCEEDED(hr))
		{
			hr=MyQI.pItf->QueryInterface(IID_IOPCServer,(void**)&m_pServer);
			MyQI.pItf->Release();
		}
		
	}else
	{
		hr=CoCreateInstance(ServerGUID,NULL,CLSCTX_ALL,IID_IOPCServer,(void**)&m_pServer);
	}
	
	
	if (SUCCEEDED(hr))
	{ //��������, ������ ����� ������� ������
		//CComPtr<IOPCItemMgt> pGroup;
		DWORD Ur;
		hr=m_pServer->AddGroup(A2W("x"),TRUE,1000,m_GroupHandleClient,NULL,NULL,0x0409,&m_GroupHandleServer,&Ur,IID_IOPCItemMgt,(IUnknown**)&m_Group);
		if (SUCCEEDED(hr))
		{
			//������� ������ (��������). � �������� ������ ������ �� �����
		//	m_Groups.insert(m_Groups.end(),pGroup);
		//	pGroup.Release();
			//m_TagsIsInGroup=false;
		}
		else 
		{
			m_LogFile<<"�� ������� �������� ������";
			m_pServer.Release();
		}
	}
	else
	{
		m_LogFile<<"�� ������� ����������������";
	}

	
	//������������ ���� � ������ ������ ���������
	if (SUCCEEDED(hr))
	{
		OPCITEMDEF *pDef = (OPCITEMDEF*)CoTaskMemAlloc(sizeof(OPCITEMDEF)*m_ItemList.size()+sizeof(OPCITEMDEF)*m_NotiItems.size());
		NotifyItemMap::iterator itl;
		int in=0;
		HRESULT * pErr=NULL;
		OPCITEMRESULT * pRes=NULL;
		for(itl=m_ItemList.begin();itl!=m_ItemList.end();++itl)
		{
			(pDef+in)->bActive=true;
			(pDef+in)->dwBlobSize=0;
			(pDef+in)->hClient =(itl->second)->hClient;
			(pDef+in)->pBlob=NULL;
			(pDef+in)->vtRequestedDataType=VT_EMPTY;
			(pDef+in)->wReserved=0;
			(pDef+in)->szItemID=A2W((char*)(itl->second)->ItemName);
			(pDef+in)->szAccessPath=A2W("");
			in++;
		}
		for(itl=m_NotiItems.begin();itl!=m_NotiItems.end();++itl)
		{
			(pDef+in)->bActive=true;
			(pDef+in)->dwBlobSize=0;
			(pDef+in)->hClient =(itl->second)->hClient;
			(pDef+in)->pBlob=NULL;
			(pDef+in)->vtRequestedDataType=VT_EMPTY;
			(pDef+in)->wReserved=0;
			(pDef+in)->szItemID=A2W((char*)(itl->second)->ItemName);
			(pDef+in)->szAccessPath=A2W("");
			in++;
		}
		
		hr=m_Group->ValidateItems(in,pDef,FALSE,&pRes,&pErr);
		if (SUCCEEDED(hr))
		{
			for(int iii=0;iii<in;iii++)
			{
				if (SUCCEEDED(*(pErr+iii)))
					(pDef+iii)->vtRequestedDataType=(pRes+iii)->vtCanonicalDataType;
			}
			CoTaskMemFree(pRes);
			pRes=NULL;
			CoTaskMemFree(pErr);
			pErr=NULL;
			
			hr=m_Group->AddItems(in,pDef,&pRes,&pErr);
			if (SUCCEEDED(hr))
			{
				//������� Handles �������
				in=0;
				for(itl=m_ItemList.begin();itl!=m_ItemList.end();++itl)
				{
					(itl->second)->hServer=(pRes+in)->hServer;
					in++;
				}
				for(itl=m_NotiItems.begin();itl!=m_NotiItems.end();++itl)
				{
					(itl->second)->hServer=(pRes+in)->hServer;
					in++;
				}
				
				CoTaskMemFree(pRes);
				pRes=NULL;
				CoTaskMemFree(pErr);
				pErr=NULL;
				IsDisconnected=false;
				//m_TagsIsInGroup=true;
			}
			else
			{ 
				m_LogFile<<"�� ������� ������������ ����";
				//m_TagsIsInGroup=false;
			}
			
		}
		CoTaskMemFree(pDef);
		//����� ����������� �� �����������
		hr=ReAddToNotify();
		//���������� - � �����
	//	CoMarshalInterThreadInterfaceInStream(IID_IOPCServer,(IUnknown*)m_pServer,&m_pStreamOPCServer);
	//	CoMarshalInterThreadInterfaceInStream(IID_IOPCGroupStateMgt,(IUnknown*)m_Groups[0].m_T,&m_pStreamOPCGroup);

		IsConfigured=true;	
		IsDisconnected=false;
		bStatus=true;
	}	
	
	Unlock();
	return hr;
}

HRESULT COPCPlug::ReAddToNotify()
{
	if (!IsConfigured)//���� �� ���������������
		return E_FAIL;

 USES_CONVERSION;
	Lock();
	//����� ���� � �������� �� ����������� � �������� ������ �������.
	//������� ��������� ������������
	HRESULT hr=S_OK;
	if (IsServerVersion203())//203
	{
		
		CComObjectNoLock<CNotify_IOPCDataCallback<COPCPlug> > * pNot = new CComObjectNoLock<CNotify_IOPCDataCallback<COPCPlug> >;
		if (pNot)
		{
			pNot->FinalConstruct();
			m_pNotify=(CNotifyBase<COPCPlug>*)pNot;
		}
		else
		{
			Unlock();
			return E_FAIL;
		}
	}else //10a
	{
		CComObjectNoLock<CNotify_IAdviseSink<COPCPlug> > * pNot = new CComObjectNoLock<CNotify_IAdviseSink<COPCPlug> >;
		if (pNot)
		{
			pNot->FinalConstruct();
			m_pNotify=(CNotifyBase<COPCPlug>*)pNot;
		}
		else
		{
			Unlock();
			return E_FAIL;
		}
	}

	m_pNotify->SetOwner(this);
	hr=m_pNotify->ConnectToNotify(0);
	if (FAILED(hr))
	{
		m_LogFile<<"�� ������� �������������� �����������";
		delete m_pNotify;
		m_pNotify=NULL;
		Unlock();
		return E_FAIL;
	}
	

	Unlock();
	return hr;
}

void COPCPlug::OwnerOnDataChange(LPFORMATETC pFE, LPSTGMEDIUM pSTM)
{
/*	//����� ������� � ��������� ����������.
	DWORD dwCount=0;
	NotifyItemList::iterator iter;
	for (iter=NotiItems.begin();iter!=NotiItems.end();iter++)
	{
		if ((*iter)->NotifyNow)
		{
			dwCount++;
		}
	}
	
	DWORD* phClientItems = (DWORD*)CoTaskMemAlloc(sizeof(DWORD)*dwCount);
	VARIANT *pvValues= (VARIANT*)CoTaskMemAlloc(sizeof(VARIANT)*dwCount);
	WORD* pwQualities= (WORD*)CoTaskMemAlloc(sizeof(WORD)*dwCount);
	FILETIME*  pftTimeStamps= (FILETIME*)CoTaskMemAlloc(sizeof(FILETIME)*dwCount);
	HRESULT * pErrors= (HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	
	//���������
	int Count=0;
	for (iter=NotiItems.begin();iter!=NotiItems.end();iter++)
	{
		if ((*iter)->NotifyNow)
		{
			*(phClientItems+Count) = (*iter)->hClient;
			VariantInit(pvValues+Count);
			VariantCopy(pvValues+Count,&(*iter)->m_it.vDataValue);
			*(pwQualities+Count)=(*iter)->m_it.wQuality;
			*(pftTimeStamps+Count)=(*iter)->m_it.ftTimeStamp;
			*(pErrors+Count)=S_OK;
			Count++;
			if (Count==dwCount) break;
		}
		
	}
	Fire_OnTagsChange(dwCount,phClientItems,pvValues,pwQualities,pftTimeStamps,pErrors);
	//������������ ������
	CoTaskMemFree(phClientItems);
	for (int i=0;i<dwCount;i++)
	{
		VariantClear(pvValues+i);
	}
	CoTaskMemFree(pvValues);
	CoTaskMemFree(pwQualities);
	CoTaskMemFree(pftTimeStamps);
	CoTaskMemFree(pErrors);
	
	
	//	Fire_OnDeviceNotAvailable();*/
}

void COPCPlug::OwnerOnDataChange(DWORD dwTransid, OPCHANDLE hGroup, HRESULT hrMasterquality, HRESULT hrMastererror, DWORD dwCount, OPCHANDLE *phClientItems, VARIANT *pvValues, WORD *pwQualities, FILETIME *pftTimeStamps, HRESULT *pErrors)
{
	//����� ������� � ��������� ����������.
	/*	DWORD dwCount=0;
	NotifyItemList::iterator iter;
	for (iter=NotiItems.begin();iter!=NotiItems.end();iter++)
	{
	if ((*iter)->NotifyNow)
	{
	dwCount++;
	}
	}
	*/	
	/*	DWORD* phClientItemsx = (DWORD*)CoTaskMemAlloc(sizeof(DWORD)*dwCount);
	VARIANT *pvValuesx= (VARIANT*)CoTaskMemAlloc(sizeof(VARIANT)*dwCount);
	WORD* pwQualitiesx= (WORD*)CoTaskMemAlloc(sizeof(WORD)*dwCount);
	FILETIME*  pftTimeStampsx= (FILETIME*)CoTaskMemAlloc(sizeof(FILETIME)*dwCount);
	HRESULT * pErrorsx= (HRESULT*)CoTaskMemAlloc(sizeof(HRESULT)*dwCount);
	*/	
	//���������
	/*	int Count=0;
	for (iter=NotiItems.begin();iter!=NotiItems.end();iter++)
	{
	if ((*iter)->NotifyNow)
	{
	*(phClientItems+Count) = (*iter)->hClient;
	VariantInit(pvValues+Count);
	VariantCopy(pvValues+Count,&(*iter)->m_it.vDataValue);
	*(pwQualities+Count)=(*iter)->m_it.wQuality;
	*(pftTimeStamps+Count)=(*iter)->m_it.ftTimeStamp;
	*(pErrors+Count)=S_OK;
	Count++;
	if (Count==dwCount) break;
	}
	
	  }
	*/	
	//�������� �������� �� ����������� �����.
//	SYSTEMTIME st;
//	double vt;
//	GetSystemTime(&st);
//	SystemTimeToVariantTime(&st,&vt);
//	_variant_t x=vt;
//	x.ChangeType(VT_DATE);
//	ATLTRACE("NOTIFICATION PLUGIN %f === %s\n",vt,(char*)(_bstr_t)x);
	try{
	
		Fire_OnTagsChange(dwCount,phClientItems,pvValues,pwQualities,pftTimeStamps,pErrors);
	}catch(...)
	{
		ATLTRACE("Exception!!!!\n");
	}
	//������������ ������
/*	CoTaskMemFree(phClientItems);
	for (int i=0;i<dwCount;i++)
	{
		VariantClear(pvValues+i);
	}
	CoTaskMemFree(pvValues);
	CoTaskMemFree(pwQualities);
	CoTaskMemFree(pftTimeStamps);
	CoTaskMemFree(pErrors);
*/	
	
	//	Fire_OnDeviceNotAvailable();
	
}


	STDMETHODIMP CBrowseObj::BrowseAccessPaths(/*[in]*/LPCWSTR szItemID,/*[out]*/ LPENUMSTRING *ppIEnumString)
	{
		return S_OK;
	}
	STDMETHODIMP CBrowseObj::GetItemID(/*[in]*/LPCWSTR szItemDataID, /*[out]*/LPWSTR *szItemID)
	{
		HRESULT hr=S_OK;
		try
		{
			hr=pBrowse->GetItemID((LPWSTR)szItemDataID,szItemID);
		}catch(...)
		{
			hr=E_FAIL;
			*szItemID=NULL;
		}
		return hr;
	}
	STDMETHODIMP CBrowseObj::BrowseOPCItemIDs(/*[in]*/ OPCBROWSETYPE  dwBrowseFilterType,/*[in]*/ LPCWSTR  szFilterCriteria, /*[in]*/ VARTYPE   vtDataTypeFilter, /*[in]*/ DWORD    dwAccessRightsFilter,	/*[out]*/ LPENUMSTRING	* ppIEnumString)
	{
		HRESULT hr=S_OK;
		try
		{
			hr=pBrowse->BrowseOPCItemIDs(dwBrowseFilterType,szFilterCriteria,vtDataTypeFilter,dwAccessRightsFilter,ppIEnumString);
		}catch(...)
		{
			hr=E_FAIL;
			*ppIEnumString=NULL;
		}
		return hr;

	}
	STDMETHODIMP CBrowseObj::ChangeBrowsePosition(/*[in]*/ OPCBROWSEDIRECTION dwBrowseDirection,/*[in]*/ LPCWSTR  szString)
	{
		HRESULT hr=S_OK;
		try
		{
			hr=pBrowse->ChangeBrowsePosition(dwBrowseDirection,szString);
		}catch(...)
		{
			hr=E_FAIL;
		}
		return hr;

	}
	STDMETHODIMP CBrowseObj::QueryAvailableProperties(/*[in]*/ BSTR ItemID,/*[out]*/ DWORD * pdwCount,/*[out, size_is(,*pdwCount)]*/ DWORD **ppPropertyIDs,/*[out, size_is(,*pdwCount)]*/ BSTR **ppDescriptions,/*[out, size_is(,*pdwCount)]*/VARTYPE **ppvtDataTypes)
	{//��������� �������� ������
		HRESULT hr=S_OK;
		USES_CONVERSION;
		CComPtr<IOPCItemProperties> pProp;
		hr=pBrowse->QueryInterface(IID_IOPCItemProperties,(void**)&pProp);
		if (FAILED(hr)) return hr;
		LPWSTR itid=(LPWSTR)CoTaskMemAlloc(sizeof(WCHAR)*(SysStringLen(ItemID)+1));
		_bstr_t t=ItemID;
		wcscpy(itid,A2W((char*)t));
		LPWSTR * pW;

		try
		{
			hr=pProp->QueryAvailableProperties(itid,pdwCount,ppPropertyIDs,&pW,ppvtDataTypes);
		}catch(...)
		{
			hr=E_FAIL;
		}
		return hr;
	}


STDMETHODIMP CBrowseObj::ValidateItem(DWORD dwCount, OPCITEMDEF *pItemArray, BOOL bBlobUpdate, OPCITEMRESULT **ppValidationResults, HRESULT **ppErrors)
{
	return E_NOTIMPL;
}
STDMETHODIMP CBrowseObj::GetItemProperties(/*[in]*/ BSTR ItemID,/*[in]*/ DWORD dwCount,/*[in, size_is(dwCount)]*/ DWORD * pdwPropertyIDs,/*[out, size_is(,dwCount)] */VARIANT ** ppvData,/*[out, size_is(,dwCount)]*/ HRESULT **ppErrors)
{
	USES_CONVERSION;
	HRESULT hr=S_OK;
	CComPtr<IOPCItemProperties> pProp;
	hr=pBrowse->QueryInterface(IID_IOPCItemProperties,(void**)&pProp);
	if (FAILED(hr)) return hr;
	LPWSTR itid=(LPWSTR)CoTaskMemAlloc(sizeof(WCHAR)*(SysStringLen(ItemID)+1));
	_bstr_t t=ItemID;
	wcscpy(itid,A2W((char*)t));
	LPWSTR * pW;


	try
	{
		hr=pProp->GetItemProperties(itid,dwCount,pdwPropertyIDs,ppvData,ppErrors);
	}catch(...)
	{
		hr=E_FAIL;
	}
	return hr;
}
