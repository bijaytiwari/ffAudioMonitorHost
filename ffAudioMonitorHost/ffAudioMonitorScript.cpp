#include "stdafx.h"
#include "ffAudioMonitorScript.h"

static NPObject*
AllocateffAudioMonitorScript(NPP npp, NPClass *pClass)
{
	return new ffAudioMonitorScript();
}

static void
DeallocateffAudioMonitorScript(NPObject *pNPObj)
{
	if (!pNPObj) {

		return;
	}

	ffAudioMonitorScript *ffScript = (ffAudioMonitorScript *)pNPObj;
	delete ffScript;
}

static void
InvalidateffAudioMonitorScript(NPObject *pNPObj)
{
	if (!pNPObj) {

		return;
	}

	((ffAudioMonitorScript *)pNPObj)->Invalidate();
}

NPClass ffAudioMonitorScriptNPClass = {
	/* version */		NP_CLASS_STRUCT_VERSION,
	/* allocate */		AllocateffAudioMonitorScript,
	/* deallocate */	DeallocateffAudioMonitorScript,
	/* invalidate */	InvalidateffAudioMonitorScript,
	/* hasMethod */		ffAudioMonitorScript::_HasMethod,
	/* invoke */		ffAudioMonitorScript::_Invoke,
	/* invokeDefault */	NULL,
	/* hasProperty */	ffAudioMonitorScript::_HasProperty,
	/* getProperty */	ffAudioMonitorScript::_GetProperty,
	/* setProperty */	ffAudioMonitorScript::_SetProperty,
	/* removeProperty */ NULL,
	/* enumerate */		 NULL,
	/* construct */		 NULL
};

bool ffAudioMonitorScript::find_member(ITypeInfoPtr info, TYPEATTR *attr, DISPID member_id, unsigned int invKind)
{
	bool found = false;
	unsigned int i = 0;

	FUNCDESC *fDesc;

	for (i = 0; 
		(i < attr->cFuncs) 
		&& !found; 
	++i) {

		HRESULT hr = info->GetFuncDesc(i, &fDesc);
		if (   SUCCEEDED(hr) 
			&& fDesc 
			&& (fDesc->memid == member_id)) {

				if (invKind & fDesc->invkind)
					found = true;
		}
		info->ReleaseFuncDesc(fDesc);
	}

	if (!found && (invKind & ~INVOKE_FUNC)) {

		VARDESC *vDesc;

		for (i = 0; 
			(i < attr->cVars) 
			&& !found; 
		++i) {

			HRESULT hr = info->GetVarDesc(i, &vDesc);
			if (   SUCCEEDED(hr) 
				&& vDesc 
				&& (vDesc->memid == member_id)) {

					found = true;
			}
			info->ReleaseVarDesc(vDesc);
		}
	}

	if (!found) {
		// iterate inherited interfaces
		HREFTYPE refType = NULL;

		for (i = 0; (i < attr->cImplTypes) && !found; ++i) {

			ITypeInfoPtr baseInfo;
			TYPEATTR *baseAttr;

			if (FAILED(info->GetRefTypeOfImplType(0, &refType))) {

				continue;
			}

			if (FAILED(info->GetRefTypeInfo(refType, &baseInfo))) {

				continue;
			}

			baseInfo->AddRef();
			if (FAILED(baseInfo->GetTypeAttr(&baseAttr))) {

				continue;
			}

			found = find_member(baseInfo, baseAttr, member_id, invKind);
			baseInfo->ReleaseTypeAttr(baseAttr);
		}
	}
	return found;
}



DISPID ffAudioMonitorScript::FindMethodName(NPIdentifier name, unsigned int invKind)
{

	bool found = false;
	DISPID dID = -1;
	USES_CONVERSION;

	if (!name || !invKind) {

		return -1;
	}

	if (!npnfuncs.identifierisstring(name)) {

		return -1;
	}

	NPUTF8 *npname = npnfuncs.utf8fromidentifier(name);
	LPOLESTR oleName = A2W(npname);

	IDispatchPtr disp = IUnknwcontrol.GetInterfacePtr();
	if (!disp) {

		return -1;
	}

	disp->AddRef();

	disp->GetIDsOfNames(IID_NULL, &oleName, 1, LOCALE_SYSTEM_DEFAULT, &dID);
	if (dID != -1) {

		ITypeInfoPtr info;
		disp->GetTypeInfo(0, LOCALE_SYSTEM_DEFAULT, &info);
		if (!info) {

			return -1;
		}

		info->AddRef();

		TYPEATTR *attr;
		if (FAILED(info->GetTypeAttr(&attr))) {

			return -1;
		}

		found = find_member(info, attr, dID, invKind);
		info->ReleaseTypeAttr(attr);
	}

	return found ? dID : -1;
}

bool ffAudioMonitorScript::InvokeControl(DISPID id, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult)
{

	IDispatchPtr disp = IUnknwcontrol.GetInterfacePtr();
	if (!disp) {

		return false;
	}

	disp->AddRef();

	HRESULT hr = disp->Invoke(id, IID_NULL, LOCALE_SYSTEM_DEFAULT, wFlags, pDispParams, pVarResult, NULL, NULL);

	return (SUCCEEDED(hr)) ? true : false;
}
