// ffAudioMonitorHost.cpp : Defines the exported functions for the DLL application.

#include "stdafx.h"
#include "ffAudioMonitorHost.h"
#include "atlutil.h"
#include <ObjBase.h>
#include "DownloadManager.h"

//CComPtr for the CLSID
CComPtr<IUnknown> CcomObject;
LPCWSTR CodeBaseUrl;
CLSID ClsID = CLSID_NULL;
//CDownloadManager *pDownloadManager = NULL;
CDownloadManagerInstance *pDownloadManager;

void *
ffax_calloc(unsigned int size)
{
	void *ptr = NULL;

	ptr = npnfuncs.memalloc(size);
	if (ptr) {

		memset(ptr, 0, size);
	}

	return ptr;
}

void
ffax_free(void *ptr)
{
	if (ptr)
		npnfuncs.memfree(ptr);
}

 

//Create ActiveX plugin instance to allow Active X to be launched using FireFox
NPError 
NPP_New(NPMIMEType pluginType,
        NPP npp_instance, uint16 mode,
        int16 argc, char *argn[],
        char *argv[], NPSavedData *saved)
{
	NPError errorType = NPERR_NO_ERROR;
	int16 i = 0;
	USES_CONVERSION;
	HRESULT hr;
	
	//::MessageBox(NULL,_T("NPP_New"),_T("setClsIDFromProgID"),NULL);

  	if (!npp_instance || (0 == npnfuncs.size)) {

		return NPERR_INVALID_PARAM;
	}
	do {

		//pDownloadManager = new CDownloadManager();
		CDownloadManagerInstance::CreateInstance(&pDownloadManager);
		if (!pDownloadManager) {

			errorType = NPERR_OUT_OF_MEMORY_ERROR;
			break;
		}

		// Iterate over the arguments we've been passed
		for (i = 0; 
			(i < argc) && (NPERR_NO_ERROR == errorType); 
			++i) {
				//convert to the string to print in messagebox
				LPCWSTR wText = (LPCWSTR)A2W( argv[i] );

				// search for any needed information: clsid, event handling directives, etc.
								
				if (0 == strnicmp(argn[i], PARAM_CLSID, strlen(PARAM_CLSID))) {
					//::MessageBox(NULL,wText,_T("setClsID"),NULL);
					//::MessageBox(NULL,wText,_T("setClsID"),NULL);

					LPOLESTR oleClsID = A2OLE(argv[i]);
					hr = CLSIDFromString(oleClsID, &ClsID);
					
					
				}
				else if(0  == strnicmp(argn[i], PARAM_CODEBASEURL, strlen(PARAM_CODEBASEURL))) {
					
						CodeBaseUrl = A2W(argv[i]);					
				}
				
			}
		
		hr = pDownloadManager->Create(ClsID,CcomObject,CodeBaseUrl);

		if (NPERR_NO_ERROR != errorType)
			break;

	} while (0);


	return errorType;
}


NPError 
NPP_Destroy(NPP npp_instance, NPSavedData **ppSave)
{
	if (!npp_instance || !npp_instance->pdata) {

		return NPERR_INVALID_PARAM;
	}

	npp_instance->pdata = NULL;

	return NPERR_NO_ERROR;
}


CComPtr<IUnknown> GetCComPtr()
{
   return CcomObject;
}

HRESULT GetIUnknownObject(IUnknown **ppIUnkwnObject)
{
    *ppIUnkwnObject = NULL;
    if (GetCComPtr())
    {
        GetCComPtr()->QueryInterface(IID_IUnknown, (void **) ppIUnkwnObject);
    }
    return S_OK;
}

NPError 
NPP_SetWindow(NPP npp_instance, NPWindow *window)
{
	/*CAxHost *host = NULL;*/
	RECT rcPos;

	if (!npp_instance) {

		return NPERR_INVALID_PARAM;
	}


	rcPos.left = 0;
	rcPos.top = 0;
	rcPos.right = window->width;
	rcPos.bottom = window->height;


	return NPERR_NO_ERROR;
}