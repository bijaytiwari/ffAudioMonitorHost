// dllmain.cpp : Defines the entry point for the DLL application.
#include "ffAudioMonitorScript.h"
#include "ffAudioMonitorHost.h"


CComModule _Module;
NPNetscapeFuncs npnfuncs;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

NPError	NPP_GetValue(NPP npp_instance, NPPVariable variable, void *value)
{
	NPObject *NPobj = NULL;
	IUnknown **TempIunk = NULL;
	IUnknown *Iunk = NULL;
	TempIunk = &Iunk;

	if(npp_instance == NULL)
		return NPERR_INVALID_INSTANCE_ERROR;

	NPError errorType = NPERR_NO_ERROR;

	if(npp_instance == NULL)
		return NPERR_GENERIC_ERROR;


	switch (variable) {
	case NPPVpluginNameString:
		*((char **)value) = "AudioMonitorActiveX";
		break;

	case NPPVpluginDescriptionString:
		*((char **)value) = "ActiveX for AudioMonitor to launch from Firefox";
		break;

	case NPPVpluginScriptableNPObject:
		NPobj = npnfuncs.createobject(npp_instance, &ffAudioMonitorScriptNPClass);
		*TempIunk = NULL;
		if(GetCComPtr())
		{
			GetCComPtr()->QueryInterface(IID_IUnknown, (void **) TempIunk);
		}
		//get_comPtr()->GetControlUnknown(&unk);
		((ffAudioMonitorScript *)NPobj)->setIUnknwcontrol(Iunk);
		((ffAudioMonitorScript *)NPobj)->setInstance(npp_instance);
		*(NPObject **)value = NPobj;
		break;

	default:
		errorType = NPERR_GENERIC_ERROR;
	}

	return errorType;
}

NPError OSCALL NP_GetEntryPoints(NPPluginFuncs* pPluginFuncs)
{

	if(pPluginFuncs == NULL)
		return NPERR_INVALID_FUNCTABLE_ERROR;

	if(pPluginFuncs->size < sizeof(NPPluginFuncs))
		return NPERR_INVALID_FUNCTABLE_ERROR;

	pPluginFuncs->version       = (NP_VERSION_MAJOR << 8) | NP_VERSION_MINOR;
	pPluginFuncs->newp          = NPP_New;
	pPluginFuncs->destroy       = NPP_Destroy;
	pPluginFuncs->setwindow     = NPP_SetWindow;
	pPluginFuncs->getvalue      = NPP_GetValue;
	return NPERR_NO_ERROR;
}

#define MIN(x, y)	((x) < (y)) ? (x) : (y)

NPError OSCALL NP_Initialize(NPNetscapeFuncs* pFuncs)
{

	if(pFuncs == NULL)
		return NPERR_INVALID_FUNCTABLE_ERROR;

#ifdef NDEF
  // The following statements prevented usage of newer Mozilla sources than installed browser at runtime
	if(HIBYTE(pFuncs->version) > NP_VERSION_MAJOR)
		return NPERR_INCOMPATIBLE_VERSION_ERROR;

	if(pFuncs->size < sizeof(NPNetscapeFuncs))
		return NPERR_INVALID_FUNCTABLE_ERROR;
#endif

	if (!AtlAxWinInit()) {

		return NPERR_GENERIC_ERROR;
	}

	CoInitialize(NULL);

	_pAtlModule = &_Module;

	memset(&npnfuncs, 0, sizeof(NPNetscapeFuncs));
	memcpy(&npnfuncs, pFuncs, MIN(pFuncs->size, sizeof(NPNetscapeFuncs)));

	return NPERR_NO_ERROR;
}

/*
 * Shutdown the plugin. Called when no more instanced of this plugin exist and
 * the browser wants to unload it.
 */
NPError OSCALL NP_Shutdown(void)
{
	AtlAxWinTerm();

	return NPERR_NO_ERROR;
}


