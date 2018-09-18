#ifndef CDOWNLOADMANAGER_H
#define CDOWNLOADMANAGER_H

#define CDOWNLOADMANAGER_INTERFACES() \
    COM_INTERFACE_ENTRY(IBindStatusCallback) \
    COM_INTERFACE_ENTRY(IWindowForBindingUI)


class CDownloadManager : public CComObjectRootEx<CComSingleThreadModel>,
                        public IBindStatusCallback,
                        public IWindowForBindingUI
{

protected:
    CComPtr<IUnknown> m_spObject;

    CLSID m_CLSID;
    unsigned m_bBindingInProgress;
    // Result from the binding operation
    HRESULT m_hrBindResult;


public:
// Construction and destruction
    // Constructor
    CDownloadManager();
    // Destructor
    virtual ~CDownloadManager();

BEGIN_COM_MAP(CDownloadManager)
    CDOWNLOADMANAGER_INTERFACES()
END_COM_MAP()


    virtual HRESULT Create(REFCLSID clsid, CComPtr<IUnknown> &CcomObject, LPCWSTR szCodebase = NULL, IBindCtx *pBindContext = NULL);
// IBindStatusCallback
    virtual HRESULT STDMETHODCALLTYPE OnStartBinding(/* [in] */ DWORD dwReserved, /* [in] */ IBinding __RPC_FAR *pib);
    virtual HRESULT STDMETHODCALLTYPE GetPriority(/* [out] */ LONG __RPC_FAR *pnPriority);
    virtual HRESULT STDMETHODCALLTYPE OnLowResource(/* [in] */ DWORD reserved);
    virtual HRESULT STDMETHODCALLTYPE OnProgress(/* [in] */ ULONG ulProgress, /* [in] */ ULONG ulProgressMax, /* [in] */ ULONG ulStatusCode, /* [in] */ LPCWSTR szStatusText);
    virtual HRESULT STDMETHODCALLTYPE OnStopBinding(/* [in] */ HRESULT hresult, /* [unique][in] */ LPCWSTR szError);
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE GetBindInfo( /* [out] */ DWORD __RPC_FAR *grfBINDF, /* [unique][out][in] */ BINDINFO __RPC_FAR *pbindinfo);
    virtual /* [local] */ HRESULT STDMETHODCALLTYPE OnDataAvailable(/* [in] */ DWORD grfBSCF, /* [in] */ DWORD dwSize, /* [in] */ FORMATETC __RPC_FAR *pformatetc, /* [in] */ STGMEDIUM __RPC_FAR *pstgmed);
    virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable(/* [in] */ REFIID riid, /* [iid_is][in] */ IUnknown __RPC_FAR *punk);

// IWindowForBindingUI
    virtual HRESULT STDMETHODCALLTYPE GetWindow(/* [in] */ REFGUID rguidReason, /* [out] */ HWND *phwnd);
};

typedef CComObject<CDownloadManager> CDownloadManagerInstance;



#endif