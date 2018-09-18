#include "StdAfx.h"

#include <Objsafe.h>

#include "DownloadManager.h"
#include "atlstr.h"
#include "WinVer.h"

// Constructor
CDownloadManager::CDownloadManager()
{
    m_CLSID = CLSID_NULL;

}


// Destructor
CDownloadManager::~CDownloadManager()
{

}

//Download the Active X
HRESULT CDownloadManager::Create(REFCLSID clsid, CComPtr<IUnknown> &CcomObject, LPCWSTR szCodebase, IBindCtx *pBindContext )
{

    m_CLSID = clsid;

	//::MessageBox(NULL,_T("The ActiveX API is working"),_T("Message from WinAppHost"),NULL);

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
        if (SUCCEEDED(hr))
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
				//::MessageBox(NULL,strErr,_T("setClsIDFromProgID"),NULL);
				//strErr.Format(_T("Create Event GetLastError = %d"),dwsma);
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
                    ::MsgWaitForMultipleObjects(1, &hFakeEvent, FALSE, 10000, QS_ALLEVENTS);
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

            if (SUCCEEDED(hr) ) 
            { 
               
            } 
        } 
      }

    if (spObject)
    {        
        m_spObject = spObject;
		CcomObject = spObject;
    }    
    return hr;

}

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


        