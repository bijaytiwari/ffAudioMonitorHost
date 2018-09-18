#include "stdafx.h"
#include <atlbase.h>
#include <atlsafe.h>
#include <npapi.h>
#include <npfunctions.h>
#include <prtypes.h>

#include <npruntime.h>
#include "ffAudioMonitorScript.h"
#include "ffArgsParser.h"

extern NPNetscapeFuncs npnfuncs;

BSTR 
Utf8StringToBstr(LPCSTR szStr, int iSize)
{ 
	BSTR bstrVal; 
    // Chars required for string
	int iReq = 0;

	if (iSize > 0) {

		if ((iReq = MultiByteToWideChar(CP_UTF8, 0, szStr, iSize, 0, 0)) ==  0) {

			return (0); 
		}
	}

	// Account for terminating 0. 
    if (iReq != -1) {

		++iReq; 
	}

    if ((bstrVal = ::SysAllocStringLen(0, iReq)) == 0) {

		return (0); 
	}

	memset(bstrVal, 0, iReq * sizeof(wchar_t));

	if (iSize > 0) {
		// Convert into the buffer. 
		if (MultiByteToWideChar(CP_UTF8, 0, szStr, iSize, bstrVal, iReq) == 0) {

			::SysFreeString(bstrVal); 
			return 0; 
		} 
	}

	return (bstrVal); 
}

void
BSTR2NPVar(BSTR bstr, NPVariant *npvar, NPP instance)
{
	USES_CONVERSION;
	char *npStr = NULL;
  size_t sourceLen;
  size_t bytesNeeded;

  sourceLen = lstrlenW(bstr);

  bytesNeeded = WideCharToMultiByte(CP_UTF8,
                                    0,
                                    bstr,
                                    sourceLen,
                                    NULL,
                                    0,
                                    NULL,
                                    NULL);

  bytesNeeded += 1;

	// complete lack of documentation on Mozilla's part here, I have no
	// idea how this string is supposed to be freed
	npStr = (char *)npnfuncs.memalloc(bytesNeeded);
	if (npStr) {

		memset(npStr, 0, bytesNeeded);

    WideCharToMultiByte(CP_UTF8,
                        0,
                        bstr,
                        sourceLen,
                        npStr,
                        bytesNeeded - 1,
                        NULL,
                        NULL);
		
		STRINGZ_TO_NPVARIANT(npStr, (*npvar));
	}
	else {

		STRINGZ_TO_NPVARIANT(NULL, (*npvar));
	}
}

void
Dispatch2NPVar(IDispatch *disp, NPVariant *npvar, NPP instance)
{
	NPObject *obj = NULL;

	obj = npnfuncs.createobject(instance, &ffAudioMonitorScriptNPClass);

	((ffAudioMonitorScript *)obj)->setControl(disp);
	((ffAudioMonitorScript *)obj)->setInstance(instance);
	OBJECT_TO_NPVARIANT(obj, (*npvar));
}

void
Unknown2NPVar(IUnknown *unk, NPVariant *npvar, NPP instance)
{
	NPObject *obj = NULL;

	obj = npnfuncs.createobject(instance, &ffAudioMonitorScriptNPClass);

	((ffAudioMonitorScript *)obj)->setIUnknwcontrol(unk);
	((ffAudioMonitorScript *)obj)->setInstance(instance);
	OBJECT_TO_NPVARIANT(obj, (*npvar));
}

NPObject *
SafeArray2NPObject(SAFEARRAY *parray, unsigned short dim, unsigned long *pindices, NPP instance)
{
	unsigned long *indices = pindices;
	NPObject *obj = NULL;
	bool rc = true;

	if (!parray || !instance) {

		return NULL;
	}

	if (NULL == obj) {

		return NULL;
	}

	do {
		if (NULL == indices) {
			// just getting started
			SafeArrayLock(parray);

			indices = (unsigned long *)calloc(1, parray->cDims * sizeof(unsigned long));
			if (NULL == indices) {

				rc = false;
				break;
			}
		}

		NPIdentifier id = NULL;
		NPVariant val;
		VOID_TO_NPVARIANT(val);

		for(indices[dim] = 0; indices[dim] < parray->rgsabound[dim].cElements; indices[dim]++) {

			if (dim == (parray->cDims - 1)) {
				// single dimension (or the bottom of the recursion)
				if (parray->fFeatures & FADF_VARIANT) {

					VARIANT variant;
					VariantInit(&variant);

					if(FAILED(SafeArrayGetElement(parray, (long *)indices, &variant))) {

						rc = false;
						break;
					}

					ConvertVarianttoNPVar(&variant, &val, instance);
					VariantClear(&variant);
				}
				else if (parray->fFeatures & FADF_BSTR) {

					BSTR bstr;

					if(FAILED(SafeArrayGetElement(parray, (long *)indices, &bstr))) {

						rc = false;
						break;
					}

					BSTR2NPVar(bstr, &val, instance);
				}
				else if (parray->fFeatures & FADF_DISPATCH) {

					IDispatch *disp;

					if(FAILED(SafeArrayGetElement(parray, (long *)indices, &disp))) {

						rc = false;
						break;
					}

					Dispatch2NPVar(disp, &val, instance);
				}
				else if (parray->fFeatures & FADF_UNKNOWN) {

					IUnknown *unk;

					if(FAILED(SafeArrayGetElement(parray, (long *)indices, &unk))) {

						rc = false;
						break;
					}

					Unknown2NPVar(unk, &val, instance);
				}
			}
			else {
				// recurse
				NPObject *o = SafeArray2NPObject(parray, dim + 1, indices, instance);
				if (NULL == o) {

					rc = false;
					break;
				}

				OBJECT_TO_NPVARIANT(o, val);
			}

			id = npnfuncs.getintidentifier(parray->rgsabound[dim].lLbound + indices[dim]);

			// setproperty will call retainobject or copy the internal string, we should
			// release variant
			npnfuncs.setproperty(instance, obj, id, &val);
			npnfuncs.releasevariantvalue(&val);
			VOID_TO_NPVARIANT(val);
		}
	} while (0);

	if (false == rc) {

		if (!pindices && indices) {

			free(indices);
			indices = NULL;

			SafeArrayUnlock(parray);
		}

		if (obj) {

			npnfuncs.releaseobject(obj);
			obj = NULL;
		}
	}

	return obj;
}

#define GETVALUE(var, val)	(((var->vt) & VT_BYREF) ? *(var->p##val) : (var->val))

void
ConvertVarianttoNPVar(const VARIANT *var, NPVariant *npvar, NPP instance)
{
	NPObject *obj = NULL;
	SAFEARRAY *parray = NULL;

	if (!var || !npvar) {

		return;
	}

	VOID_TO_NPVARIANT(*npvar);

	switch (var->vt & ~VT_BYREF) {
	case VT_ARRAY:
		obj = SafeArray2NPObject(GETVALUE(var, parray), 0, NULL, instance);
		OBJECT_TO_NPVARIANT(obj, (*npvar));
		break;

	case VT_EMPTY:
		VOID_TO_NPVARIANT((*npvar));
		break;

	case VT_NULL:
		NULL_TO_NPVARIANT((*npvar));
		break;

	case VT_LPSTR:
		// not sure it can even appear in a VARIANT, but...
		STRINGZ_TO_NPVARIANT(var->pcVal, (*npvar));
		break;

	case VT_BSTR:
		BSTR2NPVar(GETVALUE(var, bstrVal), npvar, instance);
		break;

	case VT_I1:
		INT32_TO_NPVARIANT((int32)GETVALUE(var, cVal), (*npvar));
		break;

	case VT_I2:
		INT32_TO_NPVARIANT((int32)GETVALUE(var, iVal), (*npvar));
		break;

	case VT_I4:
		INT32_TO_NPVARIANT((int32)GETVALUE(var, lVal), (*npvar));
		break;

	case VT_UI1:
		INT32_TO_NPVARIANT((int32)GETVALUE(var, bVal), (*npvar));
		break;

	case VT_UI2:
		INT32_TO_NPVARIANT((int32)GETVALUE(var, uiVal), (*npvar));
		break;

	case VT_UI4:
		INT32_TO_NPVARIANT((int32)GETVALUE(var, ulVal), (*npvar));
		break;

	case VT_BOOL:
		BOOLEAN_TO_NPVARIANT((GETVALUE(var, boolVal) == VARIANT_TRUE) ? true : false, (*npvar));
		break;

	case VT_R4:
		DOUBLE_TO_NPVARIANT((double)GETVALUE(var, fltVal), (*npvar));
		break;

	case VT_R8:
		DOUBLE_TO_NPVARIANT(GETVALUE(var, dblVal), (*npvar));
		break;

	case VT_DISPATCH:
		Dispatch2NPVar(GETVALUE(var, pdispVal), npvar, instance);
		break;

	case VT_UNKNOWN:
		Unknown2NPVar(GETVALUE(var, punkVal), npvar, instance);
		break;

	default:
		// Some unsupported type
		break;
	}
}
#undef GETVALUE

void
ConvertNPVartoVariant(const NPVariant *npvar, VARIANT *var, NPP instance)
{
	USES_CONVERSION;

	if (!var || !npvar) {

		return;
	}

	switch (npvar->type) {
	case NPVariantType_Void:
		var->vt = VT_VOID;
		var->ulVal = 0;
		break;

	case NPVariantType_Null:
		var->vt = VT_PTR;
		var->byref = NULL;
		break;

	case NPVariantType_Bool:
		var->vt = VT_BOOL;
		var->ulVal = npvar->value.boolValue;
		break;

	case NPVariantType_Int32:
		var->vt = VT_UI4;
		var->ulVal = npvar->value.intValue;
		break;

	case NPVariantType_Double:
		var->vt = VT_R8;
		var->dblVal = npvar->value.doubleValue;
		break;

	case NPVariantType_String:
		var->vt = VT_BSTR;
		var->bstrVal = Utf8StringToBstr(npvar->value.stringValue.UTF8Characters, npvar->value.stringValue.UTF8Length);
		break;

	case NPVariantType_Object:
		NPIdentifier *identifiers = NULL;
		uint32_t identifierCount = 0;
		NPObject *object = NPVARIANT_TO_OBJECT(*npvar);

		if (npnfuncs.enumerate(instance, object, &identifiers, &identifierCount)) {
			CComSafeArray<VARIANT> variants;

			for (uint32_t index = 0; index < identifierCount; ++index) {
				NPVariant npVariant;

				if (npnfuncs.getproperty(instance, object, identifiers[index], &npVariant)) {

					if (npVariant.type != NPVariantType_Object) {

						CComVariant variant;

						ConvertNPVartoVariant(&npVariant, &variant, instance);
						variants.Add(variant);
					}

					npnfuncs.releasevariantvalue(&npVariant);
				}
			}

			npnfuncs.memfree(identifiers);
			*reinterpret_cast<CComVariant*>(var) = variants;
		}
		else {

			var->vt = VT_VOID;
			var->ulVal = 0;
		}
		break;
	}
}

