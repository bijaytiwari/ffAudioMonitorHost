#pragma once

#include <atlbase.h>
#include <comdef.h>
#include <npapi.h>
#include <npfunctions.h>
#include <npruntime.h>
#include "ffArgsParser.h"

extern NPNetscapeFuncs npnfuncs;
extern NPClass ffAudioMonitorScriptNPClass;

class ffAudioMonitorScript: public NPObject
{
private:
	ffAudioMonitorScript(const ffAudioMonitorScript &);
	//Find the member id
	bool find_member(ITypeInfoPtr info, TYPEATTR *attr, DISPID member_id, unsigned int invKind);
	bool InvokeControl(DISPID id, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult);
	DISPID FindMethodName(NPIdentifier name, unsigned int invKind);

	IUnknownPtr IUnknwcontrol;
	NPP NPPInstance;
	bool bInvalid;

public:
	ffAudioMonitorScript():
	  bInvalid(false),
		  IUnknwcontrol(NULL),
		  NPPInstance(NULL) {
	  }

	  ~ffAudioMonitorScript() {if(NULL != IUnknwcontrol) IUnknwcontrol->Release();}

	  void setIUnknwcontrol(IUnknown *unk) {IUnknwcontrol = unk;}
	  void setControl(IDispatch *disp) {disp->QueryInterface(IID_IUnknown, (void **)&IUnknwcontrol);}
	  void setInstance(NPP npp_instance) {NPPInstance = npp_instance;}

	  void Invalidate() {bInvalid = true;}

	  static bool _HasMethod(NPObject *npobj, NPIdentifier name) {

			return ((ffAudioMonitorScript *)npobj)->HasMethod(name);
	  }

	  static bool _Invoke(NPObject *npobj, NPIdentifier name,
		  const NPVariant *args, uint32_t argCount,
		  NPVariant *result)
	  {
		 //	::MessageBox(NULL,_T("Scriptable::Invoke "),_T("SWITCHCASE"),NULL);
		return ((ffAudioMonitorScript *)npobj)->Invoke(name, args, argCount, result);
	  }

	  static bool _HasProperty(NPObject *npobj, NPIdentifier name)
	  {

		 return ((ffAudioMonitorScript *)npobj)->HasProperty(name);
	  }

	  static bool _GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result) 
	  {
			return ((ffAudioMonitorScript *)npobj)->GetProperty(name, result);
		  
	  }

	  static bool _SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value) {

		  return ((ffAudioMonitorScript *)npobj)->SetProperty(name, value);

	  }

	  bool HasMethod(NPIdentifier name) {

		  if (bInvalid) return false;

		  DISPID id = FindMethodName(name, INVOKE_FUNC);
		  return (id != -1) ? true : false;
	  }

	  bool Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result) {

	  	if (bInvalid) return false;

	  	DISPID id = FindMethodName(name, INVOKE_FUNC);
	  	if (-1 == id) {

	  		return false;
	  	}

	  	VARIANT *vArgs = NULL;
	  	if (argCount) {

	  		vArgs = new VARIANT[argCount];
	  		if (!vArgs) {

	  			return false;
	  		}

	  		for (unsigned int i = 0; i < argCount; ++i) {

	  			// copy the arguments in reverse order
	  			ConvertNPVartoVariant(&args[i], &vArgs[argCount - i - 1], NPPInstance);
	  		}
	  	}

	  	DISPPARAMS params = {NULL, NULL, 0, 0};

	  	params.cArgs = argCount;
	  	params.cNamedArgs = 0;
	  	params.rgdispidNamedArgs = NULL;
	  	params.rgvarg = vArgs;

	  	VARIANT vResult;

	  	bool rc = InvokeControl(id, DISPATCH_METHOD, &params, &vResult);
	  	if (vArgs) delete[] vArgs;

	  	if (!rc) {

	  		return false;
	  	}

	  	ConvertVarianttoNPVar(&vResult, result, NPPInstance);
	  	return true;
	  }

	  bool HasProperty(NPIdentifier name) {

		  if (bInvalid) return false;

		  DISPID id = FindMethodName(name, INVOKE_PROPERTYGET | INVOKE_PROPERTYPUT);
		  return (id != -1) ? true : false;
	  }

	  bool GetProperty(NPIdentifier name, NPVariant *result) {

		  if (bInvalid) return false;

		  DISPID id = FindMethodName(name, INVOKE_PROPERTYGET);
		  if (-1 == id) {

			  return false;
		  }

		  DISPPARAMS params;

		  params.cArgs = 0;
		  params.cNamedArgs = 0;
		  params.rgdispidNamedArgs = NULL;
		  params.rgvarg = NULL;

		  VARIANT vResult;

		  if (!InvokeControl(id, DISPATCH_PROPERTYGET, &params, &vResult)) {

			  return false;
		  }

		  ConvertVarianttoNPVar(&vResult, result, NPPInstance);
		  return true;
	  }

	    bool SetProperty(NPIdentifier name, const NPVariant *value) {

	  	if (bInvalid) return false;

	  	DISPID id = FindMethodName(name, INVOKE_PROPERTYPUT);
	  	if (-1 == id) {

	  		return false;
	  	}

	  	VARIANT val;
	  	ConvertNPVartoVariant(value, &val, NPPInstance);

	  	DISPPARAMS params;
	  	// Special initialization needed when using propery put.
	  	DISPID dispidNamed = DISPID_PROPERTYPUT;
	  	params.cNamedArgs = 1;
	  	params.rgdispidNamedArgs = &dispidNamed;
	  	params.cArgs = 1;
	  	params.rgvarg = &val;

	  	VARIANT vResult;
	  	if (!InvokeControl(id, DISPATCH_PROPERTYPUT, &params, &vResult)) {

	  		return false;
	  	}

	  	return true;
	  }
};

