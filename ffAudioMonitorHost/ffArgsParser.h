#pragma once

void ConvertVarianttoNPVar(const VARIANT *var, NPVariant *npvar, NPP instance);
void ConvertNPVartoVariant(const NPVariant *npvar, VARIANT *var, NPP instance);
BSTR Utf8StringToBstr(LPCSTR szStr, int iSize);
