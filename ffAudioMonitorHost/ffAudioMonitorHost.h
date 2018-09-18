#pragma once

#include "npapi.h"
#include <npfunctions.h>
#include <prtypes.h>

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

#include <atlbase.h>
#include <atlstr.h>
#include <atlcom.h>
#include <atlctl.h>
#include <varargs.h>

#include "ffArgsParser.h"

extern NPNetscapeFuncs npnfuncs;

#define NO_REGISTRY_AUTHORIZE 

static const char PARAM_CODEBASEURL [] = "codeBaseUrl";
static const char PARAM_CLSID[] = "clsid";




void *ffax_calloc(unsigned int size);
void ffax_free(void *ptr);
NPError NPP_New(NPMIMEType pluginType, NPP npp_instance, uint16 mode, int16 argc, char *argn[], char *argv[], NPSavedData *saved);
NPError NPP_Destroy(NPP instance, NPSavedData **save);
NPError NPP_SetWindow(NPP instance, NPWindow *window);
CComPtr<IUnknown> GetCComPtr();
HRESULT GetIUnknownObject(IUnknown **ppIUnkwnObject);
