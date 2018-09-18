#include "StdAfx.h"
#include "DownloadManager.h"
#include "Wininet.h"

#define    WM_USER_ENDDOWNLOAD           (WM_USER + 1)
#define    WM_USER_DISPLAYSTATUS         (WM_USER + 2)

CDownloadManager::CDownloadManager(void)
{
	m_ulObjRefCount = 1;
}

CDownloadManager::~CDownloadManager(void)
{
}

CDownloadManager::CDownloadManager(HWND hWnd, HANDLE hEventStop)
{
	m_hWnd = hWnd;  // the window handle to display status

	m_hEventStop = hEventStop;  // the event object to signal to stop

	m_ulObjRefCount = 1;
}
//-----------------------------------------------------------------------------
// IUnknown
STDMETHODIMP CDownloadManager::QueryInterface(REFIID riid, void **ppvObject)
{
	//TRACE(_T("IUnknown::QueryInterface\n"));

	*ppvObject = NULL;
	
	// IUnknown
	if (::IsEqualIID(riid, __uuidof(IUnknown)))
	{
		//TRACE(_T("IUnknown::QueryInterface(IUnknown)\n"));

		*ppvObject = this;
	}
	// IBindStatusCallback
	else if (::IsEqualIID(riid, __uuidof(IBindStatusCallback)))
	{
		//TRACE(_T("IUnknown::QueryInterface(IBindStatusCallback)\n"));

		*ppvObject = static_cast<IBindStatusCallback *>(this);
	}

	if (*ppvObject)
	{
		(*reinterpret_cast<LPUNKNOWN *>(ppvObject))->AddRef();

		return S_OK;
	}
	
	return E_NOINTERFACE;
}                                             
//-----------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CDownloadManager::AddRef()
{
	//TRACE(_T("IUnknown::AddRef\n"));

	return ++m_ulObjRefCount;
}
//-----------------------------------------------------------------------------
STDMETHODIMP_(ULONG) CDownloadManager::Release()
{
	//TRACE(_T("IUnknown::Release\n"));

	return --m_ulObjRefCount;
}
//-----------------------------------------------------------------------------
// IBindStatusCallback
STDMETHODIMP CDownloadManager::OnStartBinding(DWORD, IBinding *)
{
	//TRACE(_T("IBindStatusCallback::OnStartBinding\n"));

	return S_OK;
}
//-----------------------------------------------------------------------------
STDMETHODIMP CDownloadManager::GetPriority(LONG *)
{
	//TRACE(_T("IBindStatusCallback::GetPriority\n"));
return S_OK;
	//venkat return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
STDMETHODIMP CDownloadManager::OnLowResource(DWORD)
{
	//TRACE(_T("IBindStatusCallback::OnLowResource\n"));

	return S_OK;
}
//-----------------------------------------------------------------------------
STDMETHODIMP CDownloadManager::OnProgress(ULONG ulProgress,
										 ULONG ulProgressMax,
										 ULONG ulStatusCode,
										 LPCWSTR szStatusText)
{
	//venkat 
//#ifdef _DEBUG
//	static const LPCTSTR plpszStatus[] = 
//	{
//		_T("BINDSTATUS_FINDINGRESOURCE"),  // 1
//		_T("BINDSTATUS_CONNECTING"),
//		_T("BINDSTATUS_REDIRECTING"),
//		_T("BINDSTATUS_BEGINDOWNLOADDATA"),
//		_T("BINDSTATUS_DOWNLOADINGDATA"),
//		_T("BINDSTATUS_ENDDOWNLOADDATA"),
//		_T("BINDSTATUS_BEGINDOWNLOADCOMPONENTS"),
//		_T("BINDSTATUS_INSTALLINGCOMPONENTS"),
//		_T("BINDSTATUS_ENDDOWNLOADCOMPONENTS"),
//		_T("BINDSTATUS_USINGCACHEDCOPY"),
//		_T("BINDSTATUS_SENDINGREQUEST"),
//		_T("BINDSTATUS_CLASSIDAVAILABLE"),
//		_T("BINDSTATUS_MIMETYPEAVAILABLE"),
//		_T("BINDSTATUS_CACHEFILENAMEAVAILABLE"),
//		_T("BINDSTATUS_BEGINSYNCOPERATION"),
//		_T("BINDSTATUS_ENDSYNCOPERATION"),
//		_T("BINDSTATUS_BEGINUPLOADDATA"),
//		_T("BINDSTATUS_UPLOADINGDATA"),
//		_T("BINDSTATUS_ENDUPLOADINGDATA"),
//		_T("BINDSTATUS_PROTOCOLCLASSID"),
//		_T("BINDSTATUS_ENCODING"),
//		_T("BINDSTATUS_VERFIEDMIMETYPEAVAILABLE"),
//		_T("BINDSTATUS_CLASSINSTALLLOCATION"),
//		_T("BINDSTATUS_DECODING"),
//		_T("BINDSTATUS_LOADINGMIMEHANDLER"),
//		_T("BINDSTATUS_CONTENTDISPOSITIONATTACH"),
//		_T("BINDSTATUS_FILTERREPORTMIMETYPE"),
//		_T("BINDSTATUS_CLSIDCANINSTANTIATE"),
//		_T("BINDSTATUS_IUNKNOWNAVAILABLE"),
//		_T("BINDSTATUS_DIRECTBIND"),
//		_T("BINDSTATUS_RAWMIMETYPE"),
//		_T("BINDSTATUS_PROXYDETECTING"),
//		_T("BINDSTATUS_ACCEPTRANGES"),
//		_T("???")  // unknown
//	};
//#endif
//
//	//TRACE(_T("IBindStatusCallback::OnProgress\n"));
//
//	//TRACE(_T("ulProgress: %lu, ulProgressMax: %lu\n"),
//	///	  ulProgress, ulProgressMax);
//	
//	//TRACE(_T("ulStatusCode: %lu "), ulStatusCode);
//
//	if (ulStatusCode < UF_BINDSTATUS_FIRST ||
//		ulStatusCode > UF_BINDSTATUS_LAST)
//	{
//		ulStatusCode = UF_BINDSTATUS_LAST + 1;
//	}
//	
//
//	if (m_hWnd != NULL)
//	{
//		// inform the dialog box to display current status,
//		// don't use PostMessage
//		/*CUrlFileDlg::DOWNLOADSTATUS downloadStatus =
//			{ ulProgress, ulProgressMax, ulStatusCode, szStatusText };
//		::SendMessage(m_hWnd, WM_USER_DISPLAYSTATUS,
//					  0, reinterpret_cast<LPARAM>(&downloadStatus));*/
//	}
//
//	if (m_hEventStop != NULL)
//	{
//		if (::WaitForSingleObject(m_hEventStop, 0) == WAIT_OBJECT_0)
//		{
//			
//			::SendMessage(m_hWnd, WM_USER_DISPLAYSTATUS, 0, NULL);
//			return E_ABORT;  // canceled by the user
//		}
//	}

	return S_OK;
}
//-----------------------------------------------------------------------------
STDMETHODIMP CDownloadManager::OnStopBinding(HRESULT hresult, LPCWSTR szError)
{
	m_bBindingInProgress = FALSE;
    m_hrBindResult = hresult;
	return S_OK;
}
//-----------------------------------------------------------------------------
STDMETHODIMP CDownloadManager::GetBindInfo(DWORD __RPC_FAR *pgrfBINDF, 
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

	return S_OK;
}
//-----------------------------------------------------------------------------
STDMETHODIMP CDownloadManager::OnDataAvailable(DWORD, DWORD,
											  FORMATETC *, STGMEDIUM *)
{
	

	//venkat return S_OK;
	return E_NOTIMPL;
}
//-----------------------------------------------------------------------------
STDMETHODIMP CDownloadManager::OnObjectAvailable(REFIID, IUnknown *)
{
	

	return S_OK;
}



HRESULT CDownloadManager::Create(REFCLSID clsid, CComPtr<IUnknown> &CcomObject,
                             LPCWSTR szCodebase, IBindCtx *pBindContext)
{

	::MessageBox(NULL,_T("The ActiveX API is working"),_T("Message from WinAppHost"),NULL);

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

	::MessageBox(NULL,_T("Download code"),_T("Message from WinAppHost"),NULL);

    CComPtr<IUnknown> spObject;
    HRESULT hr;
    //If the control needs to be updated do not call CoCreateInstance otherwise you will lock files
    //and force a reboot on CoGetClassObjectFromURL
    if(!bUpdateControlVersion)
    {
        // Create the object
        hr = CoCreateInstance(clsid, NULL, CLSCTX_ALL, IID_IUnknown, (void **) &spObject);
        if (SUCCEEDED(hr) )
        {

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
			::MessageBox(NULL,_T("cogetclass"),_T("setClsIDFromProgID"),NULL);
        }
        else
        {
			hr = CoGetClassObjectFromURL(clsid, szURL, dwFileVersionMS, dwFileVersionLS,
                                         NULL, spBindContext, CLSCTX_ALL, NULL, IID_IUnknown, 
                                         NULL);
			::MessageBox(NULL,_T("cogetclass"),_T("setClsIDFromProgID"),NULL);
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
				/*DWORD dwsma = GetLastError();
				strErr.Format(_T("Create Event GetLastError = %d"),dwsma);
				::MessageBox(NULL,strErr,_T("setClsIDFromProgID"),NULL);*/
                while (m_bBindingInProgress)
                {
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

            if (SUCCEEDED(hr)) 
            { 

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


void 
CDownloadManager::setWindow(HWND win)
{
	if (win != Window) {

		if (win) {
			
			// associate window with our CAxHost object so we can access 
			// it in the window procedure
			::SetWindowLong(win, GWL_USERDATA, (LONG)this);
		}

		Window = win;
	}
}


void 
CDownloadManager::UpdateRect(RECT rcPos)
{
  // Ensure clipping on parent to keep child controls happy
	::SetWindowLong(Window, GWL_STYLE, ::GetWindowLong(Window, GWL_STYLE) | WS_CLIPCHILDREN);

}

//IWindowForBindingUI
HRESULT STDMETHODCALLTYPE CDownloadManager::GetWindow(
    /* [in] */ REFGUID rguidReason,
    /* [out] */ HWND *phwnd)
{
    *phwnd = NULL;
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CDownloadManager::GetWindow(/* [out] */ HWND __RPC_FAR *phwnd)
{
    *phwnd = NULL;
    return S_OK;
}


HRESULT STDMETHODCALLTYPE CDownloadManager::ContextSensitiveHelp(/* [in] */ BOOL fEnterMode)
{
    return S_OK;
}
