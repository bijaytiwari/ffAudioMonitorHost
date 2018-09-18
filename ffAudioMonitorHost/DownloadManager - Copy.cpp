//#include "StdAfx.h"
//#include "DownloadManager.h"
//#include "Wininet.h"
//
//#define    WM_USER_ENDDOWNLOAD           (WM_USER + 1)
//#define    WM_USER_DISPLAYSTATUS         (WM_USER + 2)
//
//CDownloadManager::CDownloadManager(void)
//{
//	m_ulObjRefCount = 1;
//}
//
//CDownloadManager::~CDownloadManager(void)
//{
//}
//
//CDownloadManager::CDownloadManager(HWND hWnd, HANDLE hEventStop)
//{
//	m_hWnd = hWnd;  // the window handle to display status
//
//	m_hEventStop = hEventStop;  // the event object to signal to stop
//
//	m_ulObjRefCount = 1;
//}
////-----------------------------------------------------------------------------
//// IUnknown
//STDMETHODIMP CDownloadManager::QueryInterface(REFIID riid, void **ppvObject)
//{
//	//TRACE(_T("IUnknown::QueryInterface\n"));
//
//	*ppvObject = NULL;
//	
//	// IUnknown
//	if (::IsEqualIID(riid, __uuidof(IUnknown)))
//	{
//		//TRACE(_T("IUnknown::QueryInterface(IUnknown)\n"));
//
//		*ppvObject = this;
//	}
//	// IBindStatusCallback
//	else if (::IsEqualIID(riid, __uuidof(IBindStatusCallback)))
//	{
//		//TRACE(_T("IUnknown::QueryInterface(IBindStatusCallback)\n"));
//
//		*ppvObject = static_cast<IBindStatusCallback *>(this);
//	}
//
//	if (*ppvObject)
//	{
//		(*reinterpret_cast<LPUNKNOWN *>(ppvObject))->AddRef();
//
//		return S_OK;
//	}
//	
//	return E_NOINTERFACE;
//}                                             
////-----------------------------------------------------------------------------
//STDMETHODIMP_(ULONG) CDownloadManager::AddRef()
//{
//	//TRACE(_T("IUnknown::AddRef\n"));
//
//	return ++m_ulObjRefCount;
//}
////-----------------------------------------------------------------------------
//STDMETHODIMP_(ULONG) CDownloadManager::Release()
//{
//	//TRACE(_T("IUnknown::Release\n"));
//
//	return --m_ulObjRefCount;
//}
////-----------------------------------------------------------------------------
//// IBindStatusCallback
//STDMETHODIMP CDownloadManager::OnStartBinding(DWORD, IBinding *)
//{
//	//TRACE(_T("IBindStatusCallback::OnStartBinding\n"));
//
//	return S_OK;
//}
////-----------------------------------------------------------------------------
//STDMETHODIMP CDownloadManager::GetPriority(LONG *)
//{
//	//TRACE(_T("IBindStatusCallback::GetPriority\n"));
//return S_OK;
//	//venkat return E_NOTIMPL;
//}
////-----------------------------------------------------------------------------
//STDMETHODIMP CDownloadManager::OnLowResource(DWORD)
//{
//	//TRACE(_T("IBindStatusCallback::OnLowResource\n"));
//
//	return S_OK;
//}
////-----------------------------------------------------------------------------
//STDMETHODIMP CDownloadManager::OnProgress(ULONG ulProgress,
//										 ULONG ulProgressMax,
//										 ULONG ulStatusCode,
//										 LPCWSTR szStatusText)
//{
//	//venkat 
////#ifdef _DEBUG
////	static const LPCTSTR plpszStatus[] = 
////	{
////		_T("BINDSTATUS_FINDINGRESOURCE"),  // 1
////		_T("BINDSTATUS_CONNECTING"),
////		_T("BINDSTATUS_REDIRECTING"),
////		_T("BINDSTATUS_BEGINDOWNLOADDATA"),
////		_T("BINDSTATUS_DOWNLOADINGDATA"),
////		_T("BINDSTATUS_ENDDOWNLOADDATA"),
////		_T("BINDSTATUS_BEGINDOWNLOADCOMPONENTS"),
////		_T("BINDSTATUS_INSTALLINGCOMPONENTS"),
////		_T("BINDSTATUS_ENDDOWNLOADCOMPONENTS"),
////		_T("BINDSTATUS_USINGCACHEDCOPY"),
////		_T("BINDSTATUS_SENDINGREQUEST"),
////		_T("BINDSTATUS_CLASSIDAVAILABLE"),
////		_T("BINDSTATUS_MIMETYPEAVAILABLE"),
////		_T("BINDSTATUS_CACHEFILENAMEAVAILABLE"),
////		_T("BINDSTATUS_BEGINSYNCOPERATION"),
////		_T("BINDSTATUS_ENDSYNCOPERATION"),
////		_T("BINDSTATUS_BEGINUPLOADDATA"),
////		_T("BINDSTATUS_UPLOADINGDATA"),
////		_T("BINDSTATUS_ENDUPLOADINGDATA"),
////		_T("BINDSTATUS_PROTOCOLCLASSID"),
////		_T("BINDSTATUS_ENCODING"),
////		_T("BINDSTATUS_VERFIEDMIMETYPEAVAILABLE"),
////		_T("BINDSTATUS_CLASSINSTALLLOCATION"),
////		_T("BINDSTATUS_DECODING"),
////		_T("BINDSTATUS_LOADINGMIMEHANDLER"),
////		_T("BINDSTATUS_CONTENTDISPOSITIONATTACH"),
////		_T("BINDSTATUS_FILTERREPORTMIMETYPE"),
////		_T("BINDSTATUS_CLSIDCANINSTANTIATE"),
////		_T("BINDSTATUS_IUNKNOWNAVAILABLE"),
////		_T("BINDSTATUS_DIRECTBIND"),
////		_T("BINDSTATUS_RAWMIMETYPE"),
////		_T("BINDSTATUS_PROXYDETECTING"),
////		_T("BINDSTATUS_ACCEPTRANGES"),
////		_T("???")  // unknown
////	};
////#endif
////
////	//TRACE(_T("IBindStatusCallback::OnProgress\n"));
////
////	//TRACE(_T("ulProgress: %lu, ulProgressMax: %lu\n"),
////	///	  ulProgress, ulProgressMax);
////	
////	//TRACE(_T("ulStatusCode: %lu "), ulStatusCode);
////
////	if (ulStatusCode < UF_BINDSTATUS_FIRST ||
////		ulStatusCode > UF_BINDSTATUS_LAST)
////	{
////		ulStatusCode = UF_BINDSTATUS_LAST + 1;
////	}
////	
////
////	if (m_hWnd != NULL)
////	{
////		// inform the dialog box to display current status,
////		// don't use PostMessage
////		/*CUrlFileDlg::DOWNLOADSTATUS downloadStatus =
////			{ ulProgress, ulProgressMax, ulStatusCode, szStatusText };
////		::SendMessage(m_hWnd, WM_USER_DISPLAYSTATUS,
////					  0, reinterpret_cast<LPARAM>(&downloadStatus));*/
////	}
////
////	if (m_hEventStop != NULL)
////	{
////		if (::WaitForSingleObject(m_hEventStop, 0) == WAIT_OBJECT_0)
////		{
////			
////			::SendMessage(m_hWnd, WM_USER_DISPLAYSTATUS, 0, NULL);
////			return E_ABORT;  // canceled by the user
////		}
////	}
//
//	return S_OK;
//}
////-----------------------------------------------------------------------------
//STDMETHODIMP CDownloadManager::OnStopBinding(HRESULT hresult, LPCWSTR szError)
//{
//	m_bBindingInProgress = FALSE;
//    m_hrBindResult = hresult;
//	return S_OK;
//}
////-----------------------------------------------------------------------------
//STDMETHODIMP CDownloadManager::GetBindInfo(DWORD __RPC_FAR *pgrfBINDF, 
//                                                    BINDINFO __RPC_FAR *pbindInfo)
//{
//	*pgrfBINDF = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE |
//                 BINDF_GETNEWESTVERSION | BINDF_NOWRITECACHE;
//    pbindInfo->cbSize = sizeof(BINDINFO);
//    pbindInfo->szExtraInfo = NULL;
//    memset(&pbindInfo->stgmedData, 0, sizeof(STGMEDIUM));
//    pbindInfo->grfBindInfoF = 0;
//    pbindInfo->dwBindVerb = 0;
//    pbindInfo->szCustomVerb = NULL;
//    return S_OK;
//
//	return S_OK;
//}
////-----------------------------------------------------------------------------
//STDMETHODIMP CDownloadManager::OnDataAvailable(DWORD, DWORD,
//											  FORMATETC *, STGMEDIUM *)
//{
//	
//
//	//venkat return S_OK;
//	return E_NOTIMPL;
//}
////-----------------------------------------------------------------------------
//STDMETHODIMP CDownloadManager::OnObjectAvailable(REFIID, IUnknown *)
//{
//	
//
//	return S_OK;
//}
//
//
//
//HRESULT CDownloadManager::Create(REFCLSID clsid, CComPtr<IUnknown> &CcomObject,
//                             LPCWSTR szCodebase, IBindCtx *pBindContext)
//{
//
//	::MessageBox(NULL,_T("The ActiveX API is working"),_T("Message from WinAppHost"),NULL);
//
//    //Now Check if the control version needs to be updated.
//    BOOL bUpdateControlVersion = FALSE;
//    wchar_t *szURL = NULL;
//    DWORD dwFileVersionMS = 0xffffffff;
//    DWORD dwFileVersionLS = 0xffffffff;
//
//    if(szCodebase)
//    {
//        HKEY hk = NULL;   
//        wchar_t wszKey[60] = L"";
//        wchar_t wszData[MAX_PATH];
//        LPWSTR pwszClsid = NULL;
//        DWORD dwSize = 255;
//        DWORD dwHandle, dwLength, dwRegReturn;
//        DWORD dwExistingFileVerMS = 0xffffffff;
//        DWORD dwExistingFileVerLS = 0xffffffff;
//        BOOL bFoundLocalVerInfo = FALSE;
//
//        StringFromCLSID(clsid, (LPOLESTR*)&pwszClsid);
//        swprintf(wszKey, L"%s%s%s\0", L"CLSID\\", pwszClsid, L"\\InprocServer32");
//
//        if ( RegOpenKeyExW( HKEY_CLASSES_ROOT, wszKey, 0, KEY_READ, &hk ) == ERROR_SUCCESS )
//        {
//            dwRegReturn = RegQueryValueExW( hk, L"", NULL, NULL, (LPBYTE)wszData, &dwSize );
//            RegCloseKey( hk );
//        }
//
//        if(dwRegReturn == ERROR_SUCCESS)
//        {
//            VS_FIXEDFILEINFO *pFileInfo;
//            UINT uLen; 
//            dwLength = GetFileVersionInfoSizeW( wszData , &dwHandle ); 
//            LPBYTE lpData = new BYTE[dwLength]; 
//            GetFileVersionInfoW(wszData, 0, dwLength, lpData ); 
//            bFoundLocalVerInfo = VerQueryValueW( lpData, L"\\", (LPVOID*)&pFileInfo, &uLen ); 
//
//            if(bFoundLocalVerInfo)
//            {
//                dwExistingFileVerMS = pFileInfo->dwFileVersionMS;
//                dwExistingFileVerLS = pFileInfo->dwFileVersionLS;
//            }
//
//            delete [] lpData;
//        }
//
//        // Test if the code base ends in #version=a,b,c,d
//        const wchar_t *szHash = wcsrchr(szCodebase, wchar_t('#'));
//        if (szHash)
//        {
//            if (wcsnicmp(szHash, L"#version=", 9) == 0)
//            {
//                int a, b, c, d;
//                if (swscanf(szHash + 9, L"%d,%d,%d,%d", &a, &b, &c, &d) == 4)
//                {
//                    dwFileVersionMS = MAKELONG(b,a);
//                    dwFileVersionLS = MAKELONG(d,c);
//
//                    //If local version info was found compare it
//                    if(bFoundLocalVerInfo)
//                    {
//                        if(dwFileVersionMS > dwExistingFileVerMS)
//                            bUpdateControlVersion = TRUE;
//
//                        if((dwFileVersionMS == dwExistingFileVerMS) && (dwFileVersionLS > dwExistingFileVerLS))
//                            bUpdateControlVersion = TRUE;
//                    }
//
//                }
//            }
//            szURL = _wcsdup(szCodebase);
//            // Terminate at the hash mark
//            if (szURL)
//                szURL[szHash - szCodebase] = wchar_t('\0');
//        }
//        else
//        {
//            szURL = _wcsdup(szCodebase);
//        }
//    }
//
//	::MessageBox(NULL,_T("Download code"),_T("Message from WinAppHost"),NULL);
//
//    CComPtr<IUnknown> spObject;
//    HRESULT hr;
//    //If the control needs to be updated do not call CoCreateInstance otherwise you will lock files
//    //and force a reboot on CoGetClassObjectFromURL
//    if(!bUpdateControlVersion)
//    {
//        // Create the object
//        hr = CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (void **) &spObject);
//        if (SUCCEEDED(hr) )
//        {
//
//        }
//    }
//
//    // Do we need to download the control?
//    if ((FAILED(hr) && szCodebase) || (bUpdateControlVersion))
//    {
//
//        if (!szURL)
//            return E_OUTOFMEMORY;
//
//        CComPtr<IBindCtx> spBindContext; 
//        CComPtr<IBindStatusCallback> spBindStatusCallback;
//        CComPtr<IBindStatusCallback> spOldBSC;
//
//        // Create our own bind context or use the one provided?
//        BOOL useInternalBSC = FALSE;
//        if (!pBindContext)
//        {
//            useInternalBSC = TRUE;
//            hr = CreateBindCtx(0, &spBindContext);
//            if (FAILED(hr))
//            {
//                free(szURL);
//                return hr;
//            }
//
//            spBindStatusCallback = dynamic_cast<IBindStatusCallback *>(this);
//            hr = RegisterBindStatusCallback(spBindContext, spBindStatusCallback, &spOldBSC, 0);
//            if (FAILED(hr))
//            {
//                free(szURL);
//                return hr;
//            }
//        }
//        else
//        {
//            spBindContext = pBindContext;
//        }
//
//        //If the version from the CODEBASE value is greater than the installed control
//        //Call CoGetClassObjectFromURL with CLSID_NULL to prevent system change reboot prompt 
//        if(bUpdateControlVersion)
//        {
//			hr = CoGetClassObjectFromURL(CLSID_NULL, szCodebase, dwFileVersionMS, dwFileVersionLS, 
//                                         NULL, spBindContext, 
//                                         CLSCTX_INPROC_HANDLER | CLSCTX_INPROC_SERVER, 
//                                         0, IID_IClassFactory, NULL);
//			::MessageBox(NULL,_T("cogetclass"),_T("setClsIDFromProgID"),NULL);
//        }
//        else
//        {
//			hr = CoGetClassObjectFromURL(clsid, szURL, dwFileVersionMS, dwFileVersionLS,
//                                         NULL, spBindContext, CLSCTX_ALL, NULL, IID_IUnknown, 
//                                         NULL);
//			::MessageBox(NULL,_T("cogetclass"),_T("setClsIDFromProgID"),NULL);
//        }
//
//
//        free(szURL);
//
//        // Handle the internal binding synchronously so the object exists
//        // or an error code is available when the method returns.
//        if (useInternalBSC)
//        {
//            if (MK_S_ASYNCHRONOUS == hr)
//            {
//                m_bBindingInProgress = TRUE;
//                m_hrBindResult = E_FAIL;
//
//                // Spin around waiting for binding to complete
//				CString strErr;
//                HANDLE hFakeEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
//				/*DWORD dwsma = GetLastError();
//				strErr.Format(_T("Create Event GetLastError = %d"),dwsma);
//				::MessageBox(NULL,strErr,_T("setClsIDFromProgID"),NULL);*/
//                while (m_bBindingInProgress)
//                {
//                    MSG msg;
//                    // Process pending messages
//                    while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
//                    {
//                        if (!::GetMessage(&msg, NULL, 0, 0))
//                        {
//                            m_bBindingInProgress = FALSE;
//                            break;
//                        }
//                        ::TranslateMessage(&msg);
//                        ::DispatchMessage(&msg);
//                    }
//                    if (!m_bBindingInProgress)
//                        break;
//                    // Sleep for a bit or the next msg to appear
//                    ::MsgWaitForMultipleObjects(1, &hFakeEvent, FALSE, 500, QS_ALLEVENTS);
//                }
//                ::CloseHandle(hFakeEvent);
//
//                // Set the result
//                hr = m_hrBindResult;
//            }
//
//            // Destroy the bind status callback & context
//            if (spBindStatusCallback)
//            {
//                RevokeBindStatusCallback(spBindContext, spBindStatusCallback);
//                spBindStatusCallback.Release();
//                spBindContext.Release();
//            }
//        }
//        //added to create control
//        if (SUCCEEDED(hr)) 
//        { 
//            // Create the object 
//            hr = CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (void **)  &spObject); 
//
//            if (SUCCEEDED(hr)) 
//            { 
//
//            } 
//        } 
//        //EOF test code
//    }
//
//    if (spObject)
//    {        
//        m_spObject = spObject;
//		CcomObject = spObject;
//    }    
//    return hr;
//}
//
//
//void 
//CDownloadManager::setWindow(HWND win)
//{
//	if (win != Window) {
//
//		if (win) {
//			
//			// associate window with our CAxHost object so we can access 
//			// it in the window procedure
//			::SetWindowLong(win, GWL_USERDATA, (LONG)this);
//		}
//
//		Window = win;
//	}
//}
//
//
//void 
//CDownloadManager::UpdateRect(RECT rcPos)
//{
//  // Ensure clipping on parent to keep child controls happy
//	::SetWindowLong(Window, GWL_STYLE, ::GetWindowLong(Window, GWL_STYLE) | WS_CLIPCHILDREN);
//
//}
//
////IWindowForBindingUI
//HRESULT STDMETHODCALLTYPE CDownloadManager::GetWindow(
//    /* [in] */ REFGUID rguidReason,
//    /* [out] */ HWND *phwnd)
//{
//    *phwnd = NULL;
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::GetWindow(/* [out] */ HWND __RPC_FAR *phwnd)
//{
//    *phwnd = NULL;
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::ContextSensitiveHelp(/* [in] */ BOOL fEnterMode)
//{
//    return S_OK;
//}

#include "StdAfx.h"

#include <Objsafe.h>

#include "DownloadManager.h"
//#include "ControlSiteIPFrame.h"
#include "atlstr.h"

//SS
//class CDefaultControlSiteSecurityPolicy : public CControlSiteSecurityPolicy
//{
//    // Test if the specified class id implements the specified category
//    BOOL ClassImplementsCategory(const CLSID & clsid, const CATID &catid, BOOL &bClassExists);
//public:
//    // Test if the class is safe to host
//    virtual BOOL IsClassSafeToHost(const CLSID & clsid);
//    // Test if the specified class is marked safe for scripting
//    virtual BOOL IsClassMarkedSafeForScripting(const CLSID & clsid, BOOL &bClassExists);
//    // Test if the instantiated object is safe for scripting on the specified interface
//    virtual BOOL IsObjectSafeForScripting(IUnknown *pObject, const IID &iid);
//};

//BOOL
//CDefaultControlSiteSecurityPolicy::ClassImplementsCategory(const CLSID &clsid, const CATID &catid, BOOL &bClassExists)
//{
//    bClassExists = FALSE;
//
//    // Test if there is a CLSID entry. If there isn't then obviously
//    // the object doesn't exist and therefore doesn't implement any category.
//    // In this situation, the function returns REGDB_E_CLASSNOTREG.
//
//    CRegKey key;
//    if (key.Open(HKEY_CLASSES_ROOT, _T("CLSID"), KEY_READ) != ERROR_SUCCESS)
//    {
//        // Must fail if we can't even open this!
//        return FALSE;
//    }
//    LPOLESTR szCLSID = NULL;
//    if (FAILED(StringFromCLSID(clsid, &szCLSID)))
//    {
//        return FALSE;
//    }
//    USES_CONVERSION;
//    CRegKey keyCLSID;
//    LONG lResult = keyCLSID.Open(key, W2CT(szCLSID), KEY_READ);
//    CoTaskMemFree(szCLSID);
//    if (lResult != ERROR_SUCCESS)
//    {
//        // Class doesn't exist
//        return FALSE;
//    }
//    keyCLSID.Close();
//
//    // CLSID exists, so try checking what categories it implements
//    bClassExists = TRUE;
//    CComQIPtr<ICatInformation> spCatInfo;
//    HRESULT hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, NULL, CLSCTX_INPROC_SERVER, IID_ICatInformation, (LPVOID*) &spCatInfo);
//    if (spCatInfo == NULL)
//    {
//        // Must fail if we can't open the category manager
//        return FALSE;
//    }
//    
//    // See what categories the class implements
//    CComQIPtr<IEnumCATID> spEnumCATID;
//    if (FAILED(spCatInfo->EnumImplCategoriesOfClass(clsid, &spEnumCATID)))
//    {
//        // Can't enumerate classes in category so fail
//        return FALSE;
//    }
//
//    // Search for matching categories
//    BOOL bFound = FALSE;
//    CATID catidNext = GUID_NULL;
//    while (spEnumCATID->Next(1, &catidNext, NULL) == S_OK)
//    {
//        if (::IsEqualCATID(catid, catidNext))
//        {
//            return TRUE;
//        }
//    }
//    return FALSE;
//}
//
//// Test if the class is safe to host
//BOOL CDefaultControlSiteSecurityPolicy::IsClassSafeToHost(const CLSID & clsid)
//{
//    return TRUE;
//}
//
//// Test if the specified class is marked safe for scripting
//BOOL CDefaultControlSiteSecurityPolicy::IsClassMarkedSafeForScripting(const CLSID & clsid, BOOL &bClassExists)
//{
//    // Test the category the object belongs to
//    return ClassImplementsCategory(clsid, CATID_SafeForScripting, bClassExists);
//}
//
//// Test if the instantiated object is safe for scripting on the specified interface
//BOOL CDefaultControlSiteSecurityPolicy::IsObjectSafeForScripting(IUnknown *pObject, const IID &iid)
//{
//    if (!pObject) {
//        return FALSE;
//    }
//    // Ask the control if its safe for scripting
//    CComQIPtr<IObjectSafety> spObjectSafety = pObject;
//    if (!spObjectSafety)
//    {
//        return FALSE;
//    }
//
//    DWORD dwSupported = 0; // Supported options (mask)
//    DWORD dwEnabled = 0; // Enabled options
//
//    // Assume scripting via IDispatch
//    if (FAILED(spObjectSafety->GetInterfaceSafetyOptions(
//            iid, &dwSupported, &dwEnabled)))
//    {
//        // Interface is not safe or failure.
//        return FALSE;
//    }
//
//    // Test if safe for scripting
//    if (!(dwEnabled & dwSupported) & INTERFACESAFE_FOR_UNTRUSTED_CALLER)
//    {
//        // Object says it is not set to be safe, but supports unsafe calling,
//        // try enabling it and asking again.
//
//        if(!(dwSupported & INTERFACESAFE_FOR_UNTRUSTED_CALLER) ||
//            FAILED(spObjectSafety->SetInterfaceSafetyOptions(
//               iid, INTERFACESAFE_FOR_UNTRUSTED_CALLER, INTERFACESAFE_FOR_UNTRUSTED_CALLER)) ||
//            FAILED(spObjectSafety->GetInterfaceSafetyOptions(
//                iid, &dwSupported, &dwEnabled)) ||
//            !(dwEnabled & dwSupported) & INTERFACESAFE_FOR_UNTRUSTED_CALLER)
//        {
//            return FALSE;
//        }
//    }
//
//    return TRUE;
//}
//
///////////////////////////////////////////////////////////////////////////////

// Constructor
CDownloadManager::CDownloadManager()
{
//    TRACE_METHOD(CDownloadManager::CDownloadManager);

    m_hWndParent = NULL;
    m_CLSID = CLSID_NULL;
    m_bSetClientSiteFirst = FALSE;
    m_bVisibleAtRuntime = TRUE;
    memset(&m_rcObjectPos, 0, sizeof(m_rcObjectPos));

    m_bInPlaceActive = FALSE;
    m_bUIActive = FALSE;
    m_bInPlaceLocked = FALSE;
    m_bWindowless = FALSE;
    m_bSupportWindowlessActivation = TRUE;
    m_bSafeForScriptingObjectsOnly = FALSE;
	//SS
    //m_pSecurityPolicy = GetDefaultControlSecurityPolicy();

    // Initialise ambient properties
    m_nAmbientLocale = 0;
    m_clrAmbientForeColor = ::GetSysColor(COLOR_WINDOWTEXT);
    m_clrAmbientBackColor = ::GetSysColor(COLOR_WINDOW);
    m_bAmbientUserMode = true;
    m_bAmbientShowHatching = true;
    m_bAmbientShowGrabHandles = true;
    m_bAmbientAppearance = true; // 3d

    // Windowless variables
    m_hDCBuffer = NULL;
    m_hRgnBuffer = NULL;
    m_hBMBufferOld = NULL;
    m_hBMBuffer = NULL;
}


// Destructor
CDownloadManager::~CDownloadManager()
{
//    TRACE_METHOD(CDownloadManager::~CDownloadManager);
    Detach();
}

// Create the specified control, optionally providing properties to initialise
// it with and a name.
HRESULT CDownloadManager::Create(REFCLSID clsid, CComPtr<IUnknown> &CcomObject, LPCWSTR szCodebase, IBindCtx *pBindContext )
{
    //TRACE_METHOD(CDownloadManager::Create);

    m_CLSID = clsid;
//    m_ParameterList = pl;

	::MessageBox(NULL,_T("The ActiveX API is working"),_T("Message from WinAppHost"),NULL);

    // See if security policy will allow the control to be hosted
	//SS
    //if (m_pSecurityPolicy && !m_pSecurityPolicy->IsClassSafeToHost(clsid))
    //{
    //    return E_FAIL;
    //}

    //// See if object is script safe
    //BOOL checkForObjectSafety = FALSE;
    //if (m_pSecurityPolicy && m_bSafeForScriptingObjectsOnly)
    //{
    //    BOOL bClassExists = FALSE;
    //    BOOL bIsSafe = m_pSecurityPolicy->IsClassMarkedSafeForScripting(clsid, bClassExists);
    //    if (!bClassExists && szCodebase)
    //    {
    //        // Class doesn't exist, so allow code below to fetch it
    //    }
    //    else if (!bIsSafe)
    //    {
    //        // The class is not flagged as safe for scripting, so
    //        // we'll have to create it to ask it if its safe.
    //        checkForObjectSafety = TRUE;
    //    }
    //}

    //Now Check if the control version needs to be updated.
    BOOL bUpdateControlVersion = FALSE;
    wchar_t *szURL = NULL;
    DWORD dwFileVersionMS = 0xffffffff;
    DWORD dwFileVersionLS = 0xffffffff;

    if(szCodebase)
    {
        HKEY hk = NULL;   
        wchar_t wszKey[60] = L"";
        wchar_t wszData[MAX_PATH];
        LPWSTR pwszClsid = NULL;
        DWORD dwSize = 255;
        DWORD dwHandle, dwLength, dwRegReturn;
        DWORD dwExistingFileVerMS = 0xffffffff;
        DWORD dwExistingFileVerLS = 0xffffffff;
        BOOL bFoundLocalVerInfo = FALSE;

        StringFromCLSID(clsid, (LPOLESTR*)&pwszClsid);
        swprintf(wszKey, L"%s%s%s\0", L"CLSID\\", pwszClsid, L"\\InprocServer32");

        if ( RegOpenKeyExW( HKEY_CLASSES_ROOT, wszKey, 0, KEY_READ, &hk ) == ERROR_SUCCESS )
        {
            dwRegReturn = RegQueryValueExW( hk, L"", NULL, NULL, (LPBYTE)wszData, &dwSize );
            RegCloseKey( hk );
        }

        if(dwRegReturn == ERROR_SUCCESS)
        {
            VS_FIXEDFILEINFO *pFileInfo;
            UINT uLen; 
            dwLength = GetFileVersionInfoSizeW( wszData , &dwHandle ); 
            LPBYTE lpData = new BYTE[dwLength]; 
            GetFileVersionInfoW(wszData, 0, dwLength, lpData ); 
            bFoundLocalVerInfo = VerQueryValueW( lpData, L"\\", (LPVOID*)&pFileInfo, &uLen ); 

            if(bFoundLocalVerInfo)
            {
                dwExistingFileVerMS = pFileInfo->dwFileVersionMS;
                dwExistingFileVerLS = pFileInfo->dwFileVersionLS;
            }

            delete [] lpData;
        }

        // Test if the code base ends in #version=a,b,c,d
        const wchar_t *szHash = wcsrchr(szCodebase, wchar_t('#'));
        if (szHash)
        {
            if (wcsnicmp(szHash, L"#version=", 9) == 0)
            {
                int a, b, c, d;
                if (swscanf(szHash + 9, L"%d,%d,%d,%d", &a, &b, &c, &d) == 4)
                {
                    dwFileVersionMS = MAKELONG(b,a);
                    dwFileVersionLS = MAKELONG(d,c);

                    //If local version info was found compare it
                    if(bFoundLocalVerInfo)
                    {
                        if(dwFileVersionMS > dwExistingFileVerMS)
                            bUpdateControlVersion = TRUE;

                        if((dwFileVersionMS == dwExistingFileVerMS) && (dwFileVersionLS > dwExistingFileVerLS))
                            bUpdateControlVersion = TRUE;
                    }

                }
            }
            szURL = _wcsdup(szCodebase);
            // Terminate at the hash mark
            if (szURL)
                szURL[szHash - szCodebase] = wchar_t('\0');
        }
        else
        {
            szURL = _wcsdup(szCodebase);
        }
    }

    CComPtr<IUnknown> spObject;
    HRESULT hr;
    //If the control needs to be updated do not call CoCreateInstance otherwise you will lock files
    //and force a reboot on CoGetClassObjectFromURL
    if(!bUpdateControlVersion)
    {
        // Create the object
        hr = CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (void **) &spObject);
        if (SUCCEEDED(hr) /*&& checkForObjectSafety*/)
        {
            // Assume scripting via IDispatch
           /* if (!m_pSecurityPolicy->IsObjectSafeForScripting(spObject, __uuidof(IDispatch)))
            {
                return E_FAIL;
            }*/
            // Drop through, success!
        }
    }

    // Do we need to download the control?
    if ((FAILED(hr) && szCodebase) || (bUpdateControlVersion))
    {

        if (!szURL)
            return E_OUTOFMEMORY;

        CComPtr<IBindCtx> spBindContext; 
        CComPtr<IBindStatusCallback> spBindStatusCallback;
        CComPtr<IBindStatusCallback> spOldBSC;

        // Create our own bind context or use the one provided?
        BOOL useInternalBSC = FALSE;
        if (!pBindContext)
        {
            useInternalBSC = TRUE;
            hr = CreateBindCtx(0, &spBindContext);
            if (FAILED(hr))
            {
                free(szURL);
                return hr;
            }

            spBindStatusCallback = dynamic_cast<IBindStatusCallback *>(this);
            hr = RegisterBindStatusCallback(spBindContext, spBindStatusCallback, &spOldBSC, 0);
            if (FAILED(hr))
            {
                free(szURL);
                return hr;
            }
        }
        else
        {
            spBindContext = pBindContext;
        }

        //If the version from the CODEBASE value is greater than the installed control
        //Call CoGetClassObjectFromURL with CLSID_NULL to prevent system change reboot prompt 
        if(bUpdateControlVersion)
        {
			hr = CoGetClassObjectFromURL(CLSID_NULL, szCodebase, dwFileVersionMS, dwFileVersionLS, 
                                         NULL, spBindContext, 
                                         CLSCTX_INPROC_HANDLER | CLSCTX_INPROC_SERVER, 
                                         0, IID_IClassFactory, NULL);
        }
        else
        {
			hr = CoGetClassObjectFromURL(clsid, szURL, dwFileVersionMS, dwFileVersionLS,
                                         NULL, spBindContext, CLSCTX_ALL, NULL, IID_IUnknown, 
                                         NULL);
        }


        free(szURL);

        // Handle the internal binding synchronously so the object exists
        // or an error code is available when the method returns.
        if (useInternalBSC)
        {
            if (MK_S_ASYNCHRONOUS == hr)
            {
                m_bBindingInProgress = TRUE;
                m_hrBindResult = E_FAIL;

                // Spin around waiting for binding to complete
				CString strErr;
                HANDLE hFakeEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
				DWORD dwsma = GetLastError();
				strErr.Format(_T("Create Event GetLastError = %d"),dwsma);
                while (m_bBindingInProgress)
                {
				//::MessageBox(NULL,strErr,_T("setClsIDFromProgID"),NULL);
                    MSG msg;
                    // Process pending messages
                    while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
                    {
                        if (!::GetMessage(&msg, NULL, 0, 0))
                        {
                            m_bBindingInProgress = FALSE;
                            break;
                        }
                        ::TranslateMessage(&msg);
                        ::DispatchMessage(&msg);
                    }

					
                    if (!m_bBindingInProgress)
                        break;
                    // Sleep for a bit or the next msg to appear
                    ::MsgWaitForMultipleObjects(1, &hFakeEvent, FALSE, 500, QS_ALLEVENTS);
                }
                ::CloseHandle(hFakeEvent);

                // Set the result
                hr = m_hrBindResult;
            }

            // Destroy the bind status callback & context
            if (spBindStatusCallback)
            {
                RevokeBindStatusCallback(spBindContext, spBindStatusCallback);
                spBindStatusCallback.Release();
                spBindContext.Release();
            }
        }
        //added to create control
        if (SUCCEEDED(hr)) 
        { 
            // Create the object 
            hr = CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (void **)  &spObject); 

            if (SUCCEEDED(hr)/* && checkForObjectSafety*/) 
            { 
                //// Assume scripting via IDispatch 
                //if (!m_pSecurityPolicy->IsObjectSafeForScripting(spObject,  __uuidof(IDispatch))) 
                //{ 
                //    hr = E_FAIL; 
                //} 
            } 
        } 
        //EOF test code
    }

    if (spObject)
    {        
        m_spObject = spObject;
		CcomObject = spObject;
    }    
    return hr;
}


// Attach the created control to a window and activate it
HRESULT CDownloadManager::Attach(HWND hwndParent, const RECT &rcPos, IUnknown *pInitStream)
{
//    TRACE_METHOD(CDownloadManager::Attach);

    if (hwndParent == NULL)
    {
        NS_ASSERTION(0, "No parent hwnd");
        return E_INVALIDARG;
    }

    m_hWndParent = hwndParent;
    m_rcObjectPos = rcPos;

    // Object must have been created
    if (m_spObject == NULL)
    {
        return E_UNEXPECTED;
    }

    m_spIViewObject = m_spObject;
    m_spIOleObject = m_spObject;
    
    if (m_spIOleObject == NULL)
    {
        return E_FAIL;
    }
    
    DWORD dwMiscStatus;
    m_spIOleObject->GetMiscStatus(DVASPECT_CONTENT, &dwMiscStatus);

    if (dwMiscStatus & OLEMISC_SETCLIENTSITEFIRST)
    {
        m_bSetClientSiteFirst = TRUE;
    }
    if (dwMiscStatus & OLEMISC_INVISIBLEATRUNTIME)
    {
        m_bVisibleAtRuntime = FALSE;
    }

    // Some objects like to have the client site as the first thing
    // to be initialised (for ambient properties and so forth)
	//SS
    //if (m_bSetClientSiteFirst)
    //{
    //    m_spIOleObject->SetClientSite(this);
    //}

    // If there is a parameter list for the object and no init stream then
    // create one here.
    /*CPropertyBagInstance *pPropertyBag = NULL;
    if (pInitStream == NULL && m_ParameterList.GetSize() > 0)
    {
        CPropertyBagInstance::CreateInstance(&pPropertyBag);
        pPropertyBag->AddRef();
        for (unsigned long i = 0; i < m_ParameterList.GetSize(); i++)
        {
            pPropertyBag->Write(m_ParameterList.GetNameOf(i),
                const_cast<VARIANT *>(m_ParameterList.GetValueOf(i)));
        }
        pInitStream = (IPersistPropertyBag *) pPropertyBag;
    }*/

    // Initialise the control from store if one is provided
    if (pInitStream)
    {
        CComQIPtr<IPropertyBag, &IID_IPropertyBag> spPropertyBag = pInitStream;
        CComQIPtr<IStream, &IID_IStream> spStream = pInitStream;
        CComQIPtr<IPersistStream, &IID_IPersistStream> spIPersistStream = m_spIOleObject;
        CComQIPtr<IPersistPropertyBag, &IID_IPersistPropertyBag> spIPersistPropertyBag = m_spIOleObject;

        if (spIPersistPropertyBag && spPropertyBag)
        {
            spIPersistPropertyBag->Load(spPropertyBag, NULL);
        }
        else if (spIPersistStream && spStream)
        {
            spIPersistStream->Load(spStream);
        }
    }
    else
    {
        // Initialise the object if possible
        CComQIPtr<IPersistStreamInit, &IID_IPersistStreamInit> spIPersistStreamInit = m_spIOleObject;
        if (spIPersistStreamInit)
        {
            spIPersistStreamInit->InitNew();
        }
    }

    m_spIOleInPlaceObject = m_spObject;
    m_spIOleInPlaceObjectWindowless = m_spObject;

	if (m_spIOleInPlaceObject)
	{
		SetPosition(m_rcObjectPos);
	}

    // In-place activate the object
    if (m_bVisibleAtRuntime)
    {
        DoVerb(OLEIVERB_INPLACEACTIVATE);
    }

    // For those objects which haven't had their client site set yet,
    // it's done here.
	//SS
    //if (!m_bSetClientSiteFirst)
    //{
    //    m_spIOleObject->SetClientSite(this);
    //}

    return S_OK;
}


// Unhook the control from the window and throw it all away
HRESULT CDownloadManager::Detach()
{
//    TRACE_METHOD(CDownloadManager::Detach);

    if (m_spIOleInPlaceObjectWindowless)
    {
        m_spIOleInPlaceObjectWindowless.Release();
    }

    if (m_spIOleInPlaceObject)
    {
        m_spIOleInPlaceObject->InPlaceDeactivate();
        m_spIOleInPlaceObject.Release();
    }

    if (m_spIOleObject)
    {
        m_spIOleObject->Close(OLECLOSE_NOSAVE);
        m_spIOleObject->SetClientSite(NULL);
        m_spIOleObject.Release();
    }

    m_spIViewObject.Release();
    m_spObject.Release();
    
    return S_OK;
}


// Return the IUnknown of the contained control
HRESULT CDownloadManager::GetControlUnknown(IUnknown **ppObject)
{
    *ppObject = NULL;
    if (m_spObject)
    {
        m_spObject->QueryInterface(IID_IUnknown, (void **) ppObject);
    }
    return S_OK;
}

// Subscribe to an event sink on the control
HRESULT CDownloadManager::Advise(IUnknown *pIUnkSink, const IID &iid, DWORD *pdwCookie)
{
    if (m_spObject == NULL)
    {
        return E_UNEXPECTED;
    }

    if (pIUnkSink == NULL || pdwCookie == NULL)
    {
        return E_INVALIDARG;
    }

    return AtlAdvise(m_spObject, pIUnkSink, iid, pdwCookie);
}


// Unsubscribe event sink from the control
HRESULT CDownloadManager::Unadvise(const IID &iid, DWORD dwCookie)
{
    if (m_spObject == NULL)
    {
        return E_UNEXPECTED;
    }

    return AtlUnadvise(m_spObject, iid, dwCookie);
}


// Draw the control
HRESULT CDownloadManager::Draw(HDC hdc)
{
//    TRACE_METHOD(CDownloadManager::Draw);

    // Draw only when control is windowless or deactivated
    if (m_spIViewObject)
    {
        if (m_bWindowless || !m_bInPlaceActive)
        {
            RECTL *prcBounds = (m_bWindowless) ? NULL : (RECTL *) &m_rcObjectPos;
            m_spIViewObject->Draw(DVASPECT_CONTENT, -1, NULL, NULL, NULL, hdc, prcBounds, NULL, NULL, 0);
        }
    }
    else
    {
        // Draw something to indicate no control is there
        HBRUSH hbr = CreateSolidBrush(RGB(200,200,200));
        FillRect(hdc, &m_rcObjectPos, hbr);
        DeleteObject(hbr);
    }

    return S_OK;
}


// Execute the specified verb
HRESULT CDownloadManager::DoVerb(LONG nVerb, LPMSG lpMsg)
{
//    TRACE_METHOD(CDownloadManager::DoVerb);

    if (m_spIOleObject == NULL)
    {
        return E_FAIL;
    }

   // return m_spIOleObject->DoVerb(nVerb, lpMsg, this, 0, m_hWndParent, &m_rcObjectPos);
	//SS
	return S_OK;
}


// Set the position on the control
HRESULT CDownloadManager::SetPosition(const RECT &rcPos)
{
	HWND hwnd;
//    TRACE_METHOD(CDownloadManager::SetPosition);
    m_rcObjectPos = rcPos;
    if (m_spIOleInPlaceObject && SUCCEEDED(m_spIOleInPlaceObject->GetWindow(&hwnd)))
    {
		m_spIOleInPlaceObject->SetObjectRects(&m_rcObjectPos, &m_rcObjectPos);
    }
    return S_OK;
}


void CDownloadManager::FireAmbientPropertyChange(DISPID id)
{
    if (m_spObject)
    {
        CComQIPtr<IOleControl> spControl = m_spObject;
        if (spControl)
        {
            spControl->OnAmbientPropertyChange(id);
        }
    }
}


void CDownloadManager::SetAmbientUserMode(BOOL bUserMode)
{
    bool bNewMode = bUserMode ? true : false;
    if (m_bAmbientUserMode != bNewMode)
    {
        m_bAmbientUserMode = bNewMode;
        FireAmbientPropertyChange(DISPID_AMBIENT_USERMODE);
    }
}

///////////////////////////////////////////////////////////////////////////////
// CDownloadManagerSecurityPolicy implementation

//CControlSiteSecurityPolicy *CDownloadManager::GetDefaultControlSecurityPolicy()
//{
//    static CDefaultControlSiteSecurityPolicy defaultControlSecurityPolicy;
//    return &defaultControlSecurityPolicy;
//}
//
//// Test if the class is safe to host
//BOOL CDownloadManager::IsClassSafeToHost(const CLSID & clsid)
//{
//    if (m_pSecurityPolicy)
//        return m_pSecurityPolicy->IsClassSafeToHost(clsid);
//    return TRUE;
//}
//
//// Test if the specified class is marked safe for scripting
//BOOL CDownloadManager::IsClassMarkedSafeForScripting(const CLSID & clsid, BOOL &bClassExists)
//{
//    if (m_pSecurityPolicy)
//        return m_pSecurityPolicy->IsClassMarkedSafeForScripting(clsid, bClassExists);
//    return TRUE;
//}
//
//// Test if the instantiated object is safe for scripting on the specified interface
//BOOL CDownloadManager::IsObjectSafeForScripting(IUnknown *pObject, const IID &iid)
//{
//    if (m_pSecurityPolicy)
//        return m_pSecurityPolicy->IsObjectSafeForScripting(pObject, iid);
//    return TRUE;
//}
//
//BOOL CDownloadManager::IsObjectSafeForScripting(const IID &iid)
//{
//    return IsObjectSafeForScripting(m_spObject, iid);
//}
//

///////////////////////////////////////////////////////////////////////////////
// IOleWindow implementation

HRESULT STDMETHODCALLTYPE CDownloadManager::GetWindow(/* [out] */ HWND __RPC_FAR *phwnd)
{
    *phwnd = m_hWndParent;
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CDownloadManager::ContextSensitiveHelp(/* [in] */ BOOL fEnterMode)
{
    return S_OK;
}


///////////////////////////////////////////////////////////////////////////////
// IOleClientSite implementation


//HRESULT STDMETHODCALLTYPE CDownloadManager::SaveObject(void)
//{
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::GetMoniker(/* [in] */ DWORD dwAssign, /* [in] */ DWORD dwWhichMoniker, /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk)
//{
//    return E_NOTIMPL;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::GetContainer(/* [out] */ IOleContainer __RPC_FAR *__RPC_FAR *ppContainer)
//{
//    if (!ppContainer) return E_INVALIDARG;
//    *ppContainer = m_spContainer;
//    if (*ppContainer)
//    {
//        (*ppContainer)->AddRef();
//    }
//    return (*ppContainer) ? S_OK : E_NOINTERFACE;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::ShowObject(void)
//{
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::OnShowWindow(/* [in] */ BOOL fShow)
//{
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::RequestNewObjectLayout(void)
//{
//    return E_NOTIMPL;
//}
//
//
///////////////////////////////////////////////////////////////////////////////
// IOleInPlaceSite implementation

//
//HRESULT STDMETHODCALLTYPE CDownloadManager::CanInPlaceActivate(void)
//{
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::OnInPlaceActivate(void)
//{
//    m_bInPlaceActive = TRUE;
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::OnUIActivate(void)
//{
//    m_bUIActive = TRUE;
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::GetWindowContext(/* [out] */ IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame, /* [out] */ IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc, /* [out] */ LPRECT lprcPosRect, /* [out] */ LPRECT lprcClipRect, /* [out][in] */ LPOLEINPLACEFRAMEINFO lpFrameInfo)
//{
//    /**lprcPosRect = m_rcObjectPos;
//    *lprcClipRect = m_rcObjectPos;
//
//   CControlSiteIPFrameInstance *pIPFrame = NULL;
//    CControlSiteIPFrameInstance::CreateInstance(&pIPFrame);
//    pIPFrame->AddRef();
//
//    *ppFrame = (IOleInPlaceFrame *) pIPFrame;
//    *ppDoc = NULL;
//
//    lpFrameInfo->fMDIApp = FALSE;
//    lpFrameInfo->hwndFrame = NULL;
//    lpFrameInfo->haccel = NULL;
//    lpFrameInfo->cAccelEntries = 0;*/
//
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::Scroll(/* [in] */ SIZE scrollExtant)
//{
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::OnUIDeactivate(/* [in] */ BOOL fUndoable)
//{
//    m_bUIActive = FALSE;
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::OnInPlaceDeactivate(void)
//{
//    m_bInPlaceActive = FALSE;
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::DiscardUndoState(void)
//{
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::DeactivateAndUndo(void)
//{
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::OnPosRectChange(/* [in] */ LPCRECT lprcPosRect)
//{
//    if (lprcPosRect == NULL)
//    {
//        return E_INVALIDARG;
//    }
//    SetPosition(m_rcObjectPos);
//    return S_OK;
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//// IOleInPlaceSiteEx implementation
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::OnInPlaceActivateEx(/* [out] */ BOOL __RPC_FAR *pfNoRedraw, /* [in] */ DWORD dwFlags)
//{
//    m_bInPlaceActive = TRUE;
//
//    if (pfNoRedraw)
//    {
//        *pfNoRedraw = FALSE;
//    }
//    if (dwFlags & ACTIVATE_WINDOWLESS)
//    {
//        if (!m_bSupportWindowlessActivation)
//        {
//            return E_INVALIDARG;
//        }
//        m_bWindowless = TRUE;
//    }
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::OnInPlaceDeactivateEx(/* [in] */ BOOL fNoRedraw)
//{
//    m_bInPlaceActive = FALSE;
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::RequestUIActivate(void)
//{
//    return S_FALSE;
//}
//
//
/////////////////////////////////////////////////////////////////////////////////
//// IOleInPlaceSiteWindowless implementation
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::CanWindowlessActivate(void)
//{
//    // Allow windowless activation?
//    return (m_bSupportWindowlessActivation) ? S_OK : S_FALSE;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::GetCapture(void)
//{
//    // TODO capture the mouse for the object
//    return S_FALSE;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::SetCapture(/* [in] */ BOOL fCapture)
//{
//    // TODO capture the mouse for the object
//    return S_FALSE;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::GetFocus(void)
//{
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::SetFocus(/* [in] */ BOOL fFocus)
//{
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::GetDC(/* [in] */ LPCRECT pRect, /* [in] */ DWORD grfFlags, /* [out] */ HDC __RPC_FAR *phDC)
//{
//    if (phDC == NULL)
//    {
//        return E_INVALIDARG;
//    }
//
//    // Can't do nested painting
//    if (m_hDCBuffer != NULL)
//    {
//        return E_UNEXPECTED;
//    }
//
//    m_rcBuffer = m_rcObjectPos;
//    if (pRect != NULL)
//    {
//        m_rcBuffer = *pRect;
//    }
//
//    m_hBMBuffer = NULL;
//    m_dwBufferFlags = grfFlags;
//
//    // See if the control wants a DC that is onscreen or offscreen
//    if (m_dwBufferFlags & OLEDC_OFFSCREEN)
//    {
//        m_hDCBuffer = CreateCompatibleDC(NULL);
//        if (m_hDCBuffer == NULL)
//        {
//            // Error
//            return E_OUTOFMEMORY;
//        }
//
//        long cx = m_rcBuffer.right - m_rcBuffer.left;
//        long cy = m_rcBuffer.bottom - m_rcBuffer.top;
//
//        m_hBMBuffer = CreateCompatibleBitmap(m_hDCBuffer, cx, cy);
//        m_hBMBufferOld = (HBITMAP) SelectObject(m_hDCBuffer, m_hBMBuffer);
//        SetViewportOrgEx(m_hDCBuffer, m_rcBuffer.left, m_rcBuffer.top, NULL);
//
//        // TODO When OLEDC_PAINTBKGND we must draw every site behind this one
//    }
//    else
//    {
//        // TODO When OLEDC_PAINTBKGND we must draw every site behind this one
//
//        // Get the window DC
//        m_hDCBuffer = GetWindowDC(m_hWndParent);
//        if (m_hDCBuffer == NULL)
//        {
//            // Error
//            return E_OUTOFMEMORY;
//        }
//
//        // Clip the control so it can't trash anywhere it isn't allowed to draw
//        if (!(m_dwBufferFlags & OLEDC_NODRAW))
//        {
//            m_hRgnBuffer = CreateRectRgnIndirect(&m_rcBuffer);
//
//            // TODO Clip out opaque areas of sites behind this one
//
//            SelectClipRgn(m_hDCBuffer, m_hRgnBuffer);
//        }
//    }
//
//    *phDC = m_hDCBuffer;
//
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::ReleaseDC(/* [in] */ HDC hDC)
//{
//    // Release the DC
//    if (hDC == NULL || hDC != m_hDCBuffer)
//    {
//        return E_INVALIDARG;
//    }
//
//    // Test if the DC was offscreen or onscreen
//    if ((m_dwBufferFlags & OLEDC_OFFSCREEN) &&
//        !(m_dwBufferFlags & OLEDC_NODRAW))
//    {
//        // BitBlt the buffer into the control's object
//        SetViewportOrgEx(m_hDCBuffer, 0, 0, NULL);
//        HDC hdc = GetWindowDC(m_hWndParent);
//
//        long cx = m_rcBuffer.right - m_rcBuffer.left;
//        long cy = m_rcBuffer.bottom - m_rcBuffer.top;
//
//        BitBlt(hdc, m_rcBuffer.left, m_rcBuffer.top, cx, cy, m_hDCBuffer, 0, 0, SRCCOPY);
//        
//        ::ReleaseDC(m_hWndParent, hdc);
//    }
//    else
//    {
//        // TODO If OLEDC_PAINTBKGND is set draw the DVASPECT_CONTENT of every object above this one
//    }
//
//    // Clean up settings ready for next drawing
//    if (m_hRgnBuffer)
//    {
//        SelectClipRgn(m_hDCBuffer, NULL);
//        DeleteObject(m_hRgnBuffer);
//        m_hRgnBuffer = NULL;
//    }
//    
//    SelectObject(m_hDCBuffer, m_hBMBufferOld);
//    if (m_hBMBuffer)
//    {
//        DeleteObject(m_hBMBuffer);
//        m_hBMBuffer = NULL;
//    }
//
//    // Delete the DC
//    if (m_dwBufferFlags & OLEDC_OFFSCREEN)
//    {
//        ::DeleteDC(m_hDCBuffer);
//    }
//    else
//    {
//        ::ReleaseDC(m_hWndParent, m_hDCBuffer);
//    }
//    m_hDCBuffer = NULL;
//
//    return S_OK;
//}
//
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::InvalidateRect(/* [in] */ LPCRECT pRect, /* [in] */ BOOL fErase)
//{
//    // Clip the rectangle against the object's size and invalidate it
//    RECT rcI = { 0, 0, 0, 0 };
//    if (pRect == NULL)
//    {
//        rcI = m_rcObjectPos;
//    }
//    else
//    {
//        IntersectRect(&rcI, &m_rcObjectPos, pRect);
//    }
//    ::InvalidateRect(m_hWndParent, &rcI, fErase);
//
//    return S_OK;
//}
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::InvalidateRgn(/* [in] */ HRGN hRGN, /* [in] */ BOOL fErase)
//{
//    if (hRGN == NULL)
//    {
//        ::InvalidateRect(m_hWndParent, &m_rcObjectPos, fErase);
//    }
//    else
//    {
//        // Clip the region with the object's bounding area
//        HRGN hrgnClip = CreateRectRgnIndirect(&m_rcObjectPos);
//        if (CombineRgn(hrgnClip, hrgnClip, hRGN, RGN_AND) != ERROR)
//        {
//            ::InvalidateRgn(m_hWndParent, hrgnClip, fErase);
//        }
//        DeleteObject(hrgnClip);
//    }
//
//    return S_OK;
//}
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::ScrollRect(/* [in] */ INT dx, /* [in] */ INT dy, /* [in] */ LPCRECT pRectScroll, /* [in] */ LPCRECT pRectClip)
//{
//    return S_OK;
//}
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::AdjustRect(/* [out][in] */ LPRECT prc)
//{
//    if (prc == NULL)
//    {
//        return E_INVALIDARG;
//    }
//
//    // Clip the rectangle against the object position
//    RECT rcI = { 0, 0, 0, 0 };
//    IntersectRect(&rcI, &m_rcObjectPos, prc);
//    *prc = rcI;
//    return S_OK;
//}
//
//HRESULT STDMETHODCALLTYPE CDownloadManager::OnDefWindowMessage(/* [in] */ UINT msg, /* [in] */ WPARAM wParam, /* [in] */ LPARAM lParam, /* [out] */ LRESULT __RPC_FAR *plResult)
//{
//    if (plResult == NULL)
//    {
//        return E_INVALIDARG;
//    }
//    
//    // Pass the message to the windowless control
//    if (m_bWindowless && m_spIOleInPlaceObjectWindowless)
//    {
//        return m_spIOleInPlaceObjectWindowless->OnWindowMessage(msg, wParam, lParam, plResult);
//    }
//	else if (m_spIOleInPlaceObject) {
//
//		HWND wnd;
//		if (SUCCEEDED(m_spIOleInPlaceObject->GetWindow(&wnd)))
//			SendMessage(wnd, msg, wParam, lParam);
//	}
//
//    return S_FALSE;
//}
//
//
///////////////////////////////////////////////////////////////////////////////
// IOleControlSite implementation


HRESULT STDMETHODCALLTYPE CDownloadManager::OnControlInfoChanged(void)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CDownloadManager::LockInPlaceActive(/* [in] */ BOOL fLock)
{
    m_bInPlaceLocked = fLock;
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CDownloadManager::GetExtendedControl(/* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp)
{
    return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CDownloadManager::TransformCoords(/* [out][in] */ POINTL __RPC_FAR *pPtlHimetric, /* [out][in] */ POINTF __RPC_FAR *pPtfContainer, /* [in] */ DWORD dwFlags)
{
    HRESULT hr = S_OK;

    if (pPtlHimetric == NULL)
    {
        return E_INVALIDARG;
    }
    if (pPtfContainer == NULL)
    {
        return E_INVALIDARG;
    }

    HDC hdc = ::GetDC(m_hWndParent);
    ::SetMapMode(hdc, MM_HIMETRIC);
    POINT rgptConvert[2];
    rgptConvert[0].x = 0;
    rgptConvert[0].y = 0;

    if (dwFlags & XFORMCOORDS_HIMETRICTOCONTAINER)
    {
        rgptConvert[1].x = pPtlHimetric->x;
        rgptConvert[1].y = pPtlHimetric->y;
        ::LPtoDP(hdc, rgptConvert, 2);
        if (dwFlags & XFORMCOORDS_SIZE)
        {
            pPtfContainer->x = (float)(rgptConvert[1].x - rgptConvert[0].x);
            pPtfContainer->y = (float)(rgptConvert[0].y - rgptConvert[1].y);
        }
        else if (dwFlags & XFORMCOORDS_POSITION)
        {
            pPtfContainer->x = (float)rgptConvert[1].x;
            pPtfContainer->y = (float)rgptConvert[1].y;
        }
        else
        {
            hr = E_INVALIDARG;
        }
    }
    else if (dwFlags & XFORMCOORDS_CONTAINERTOHIMETRIC)
    {
        rgptConvert[1].x = (int)(pPtfContainer->x);
        rgptConvert[1].y = (int)(pPtfContainer->y);
        ::DPtoLP(hdc, rgptConvert, 2);
        if (dwFlags & XFORMCOORDS_SIZE)
        {
            pPtlHimetric->x = rgptConvert[1].x - rgptConvert[0].x;
            pPtlHimetric->y = rgptConvert[0].y - rgptConvert[1].y;
        }
        else if (dwFlags & XFORMCOORDS_POSITION)
        {
            pPtlHimetric->x = rgptConvert[1].x;
            pPtlHimetric->y = rgptConvert[1].y;
        }
        else
        {
            hr = E_INVALIDARG;
        }
    }
    else
    {
        hr = E_INVALIDARG;
    }

    ::ReleaseDC(m_hWndParent, hdc);

    return hr;
}


HRESULT STDMETHODCALLTYPE CDownloadManager::TranslateAccelerator(/* [in] */ MSG __RPC_FAR *pMsg, /* [in] */ DWORD grfModifiers)
{
    return E_NOTIMPL;
}


HRESULT STDMETHODCALLTYPE CDownloadManager::OnFocus(/* [in] */ BOOL fGotFocus)
{
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CDownloadManager::ShowPropertyFrame(void)
{
    return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////////
// IBindStatusCallback implementation

HRESULT STDMETHODCALLTYPE CDownloadManager::OnStartBinding(DWORD dwReserved, 
                                                       IBinding __RPC_FAR *pib)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CDownloadManager::GetPriority(LONG __RPC_FAR *pnPriority)
{
    return S_OK;
}
    
HRESULT STDMETHODCALLTYPE CDownloadManager::OnLowResource(DWORD reserved)
{
    return S_OK;
}
    
HRESULT STDMETHODCALLTYPE CDownloadManager::OnProgress(ULONG ulProgress, 
                                        ULONG ulProgressMax, 
                                        ULONG ulStatusCode, 
                                        LPCWSTR szStatusText)
{
    return S_OK;
}

HRESULT STDMETHODCALLTYPE CDownloadManager::OnStopBinding(HRESULT hresult, LPCWSTR szError)
{
    m_bBindingInProgress = FALSE;
    m_hrBindResult = hresult;
    return S_OK;
}
    
HRESULT STDMETHODCALLTYPE CDownloadManager::GetBindInfo(DWORD __RPC_FAR *pgrfBINDF, 
                                                    BINDINFO __RPC_FAR *pbindInfo)
{
    *pgrfBINDF = BINDF_ASYNCHRONOUS | BINDF_ASYNCSTORAGE |
                 BINDF_GETNEWESTVERSION | BINDF_NOWRITECACHE;
    pbindInfo->cbSize = sizeof(BINDINFO);
    pbindInfo->szExtraInfo = NULL;
    memset(&pbindInfo->stgmedData, 0, sizeof(STGMEDIUM));
    pbindInfo->grfBindInfoF = 0;
    pbindInfo->dwBindVerb = 0;
    pbindInfo->szCustomVerb = NULL;
    return S_OK;
}
    
HRESULT STDMETHODCALLTYPE CDownloadManager::OnDataAvailable(DWORD grfBSCF, 
                                                        DWORD dwSize, 
                                                        FORMATETC __RPC_FAR *pformatetc, 
                                                        STGMEDIUM __RPC_FAR *pstgmed)
{
    return E_NOTIMPL;
}
  
HRESULT STDMETHODCALLTYPE CDownloadManager::OnObjectAvailable(REFIID riid, 
                                                          IUnknown __RPC_FAR *punk)
{
    return S_OK;
}

// IWindowForBindingUI
HRESULT STDMETHODCALLTYPE CDownloadManager::GetWindow(
    /* [in] */ REFGUID rguidReason,
    /* [out] */ HWND *phwnd)
{
    *phwnd = NULL;
    return S_OK;
}


//IUnknown
//STDMETHODIMP CDownloadManager::QueryInterface(REFIID riid, void **ppvObject)
//{
//	//TRACE(_T("IUnknown::QueryInterface\n"));
//
//	*ppvObject = NULL;
//	
//	// IUnknown
//	if (::IsEqualIID(riid, __uuidof(IUnknown)))
//	{
//		//TRACE(_T("IUnknown::QueryInterface(IUnknown)\n"));
//
//		*ppvObject = this;
//	}
//	// IBindStatusCallback
//	else if (::IsEqualIID(riid, __uuidof(IBindStatusCallback)))
//	{
//		//TRACE(_T("IUnknown::QueryInterface(IBindStatusCallback)\n"));
//
//		*ppvObject = static_cast<IBindStatusCallback *>(this);
//	}
//
//	if (*ppvObject)
//	{
//		(*reinterpret_cast<LPUNKNOWN *>(ppvObject))->AddRef();
//
//		return S_OK;
//	}
//	
//	return E_NOINTERFACE;
//}          