// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>


#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>

// TODO: reference additional headers your program requires here



#if !defined(AFX_STDAFX_H__1339B542_3453_11D2_93B9_000000000000__INCLUDED_)
#define AFX_STDAFX_H__1339B542_3453_11D2_93B9_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

  // under MSVC shut off copious warnings about debug symbol too long
#ifdef _MSC_VER
  #pragma warning( disable: 4786 )
#endif

//#include "jstypes.h"
//#include "prtypes.h"

// Mozilla headers

//#include "jscompat.h"

//#include "prthread.h"
//#include "prprf.h"
//#include "nsID.h"
//#include "nsIComponentManager.h"
//#include "nsIServiceManager.h"
//#include "nsStringAPI.h"
//#include "nsCOMPtr.h"
//#include "nsComponentManagerUtils.h"
//#include "nsServiceManagerUtils.h"

//#include "nsIDocument.h"
//#include "nsIDocumentObserver.h"
//#include "nsVoidArray.h"

//#include "nsIDOMNode.h"
//#include "nsIDOMNodeList.h"
//#include "nsIDOMDocument.h"
//#include "nsIDOMDocumentType.h"
//#include "nsIDOMElement.h"

//#undef _WIN32_WINNT
//#define _WIN32_WINNT 0x0400
#define _ATL_APARTMENT_THREADED
//#define _ATL_STATIC_REGISTRY
// #define _ATL_DEBUG_INTERFACES

// ATL headers
// The ATL headers that come with the platform SDK have bad for scoping
#if _MSC_VER >= 1400
#pragma conform(forScope, push, atlhack, off)
#endif

#include <atlbase.h>

//You may derive a class from CComModule and use it if you want to override
//something, but do not change the name of _Module
extern CComModule _Module;
#include <atlcom.h>
#include <atlctl.h>

#if _MSC_VER >= 1400
#pragma conform(forScope, pop, atlhack)
#endif

#include <mshtml.h>
#include <mshtmhst.h>
#include <docobj.h>
//#include <winsock2.h>
#include <comdef.h>

#include <vector>
#include <list>
#include <string>

// New winsock2.h doesn't define this anymore
typedef long int32;

#define NS_SCRIPTABLE

#include "nscore.h"
#include "npapi.h"
//#include "npupp.h"
#include "npfunctions.h"

#include "nsID.h"
#include <npruntime.h>

#include "ffArgsParser.h"


extern NPNetscapeFuncs npnfuncs;

// Turn off warnings about debug symbols for templates being too long
#pragma warning(disable : 4786)


#define NS_ASSERTION(x, y)

#endif // !defined(AFX_STDAFX_H__1339B542_3453_11D2_93B9_000000000000__INCLUDED)
