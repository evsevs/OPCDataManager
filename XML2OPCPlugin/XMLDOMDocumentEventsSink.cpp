// XMLDOMDocumentEventsSink.cpp : Implementation of CXmltreeApp and DLL registration.

#include "stdafx.h"
#include "xmltree.h"
#include "XMLDOMDocumentEventsSink.h"

/////////////////////////////////////////////////////////////////////////////
//

// Define type info structure
_ATL_FUNC_INFO OnEventInfo = {CC_STDCALL, VT_EMPTY, 0};

void __stdcall CXMLDOMDocumentEventsSink::ondataavailable ( )
{
	::PostMessage(m_hwndPostWindow, WM_DATA_AVAILABLE, 0, 0);
}

void __stdcall CXMLDOMDocumentEventsSink::onreadystatechange ( )
{
	::PostMessage(m_hwndPostWindow, WM_READYSTATE_CHANGE, 0, 0);
}