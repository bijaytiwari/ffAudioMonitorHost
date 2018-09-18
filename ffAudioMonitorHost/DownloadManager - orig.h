#pragma once
#include "urlmon.h"
#include "windows.h"



#define CDOWNLOADMANAGER_INTERFACES() \
    COM_INTERFACE_ENTRY(IOleWindow) \
    COM_INTERFACE_ENTRY(IBindStatusCallback) \
    COM_INTERFACE_ENTRY(IWindowForBindingUI)

enum
{
	UF_BINDSTATUS_FIRST = BINDSTATUS_FINDINGRESOURCE,
	UF_BINDSTATUS_LAST = BINDSTATUS_ACCEPTRANGES
};

class CDownloadManager :
	public IBindStatusCallback,
	public IOleControlSite,
	public IWindowForBindingUI
{
	
public:
	CDownloadManager(void);
	virtual ~CDownloadManager(void);
	CDownloadManager(HWND hWnd, HANDLE hEventStop);

	BEGIN_COM_MAP(CDownloadManager)
		CDOWNLOADMANAGER_INTERFACES()
	END_COM_MAP()

	//BEGIN_OLECOMMAND_TABLE()
	//END_OLECOMMAND_TABLE()

	//// Returns the window used when processing ole commands
	//HWND GetCommandTargetWindow()
	//{
	//	return NULL; // TODO
	//}
	//bool SetComObject(CComPtr<IUnknown> *CcomObject);
	//void setCodeBaseUrl(LPCWSTR clsid);
	virtual HRESULT Create(REFCLSID clsid, CComPtr<IUnknown> &CcomObject, LPCWSTR szCodebase = NULL, IBindCtx *pBindContext = NULL);

	// IUnknown methods
	STDMETHOD(QueryInterface)(REFIID riid, void **ppvObject);
	STDMETHOD_(ULONG, AddRef)();
	STDMETHOD_(ULONG, Release)();

	// IBindStatusCallback methods
	STDMETHOD(OnStartBinding)(DWORD, IBinding *);
	STDMETHOD(GetPriority)(LONG *);
	STDMETHOD(OnLowResource)(DWORD);
	STDMETHOD(OnProgress)(ULONG ulProgress,
						  ULONG ulProgressMax,
						  ULONG ulStatusCode,
						  LPCWSTR szStatusText);
	STDMETHOD(OnStopBinding)(HRESULT, LPCWSTR);
	STDMETHOD(GetBindInfo)(DWORD *, BINDINFO *);
	STDMETHOD(OnDataAvailable)(DWORD, DWORD, FORMATETC *, STGMEDIUM *);
	STDMETHOD(OnObjectAvailable)(REFIID, IUnknown *);

	// IWindowForBindingUI
    virtual HRESULT STDMETHODCALLTYPE GetWindow(/* [in] */ REFGUID rguidReason, /* [out] */ HWND *phwnd);

	// IOleWindow implementation
    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow(/* [out] */ HWND __RPC_FAR *phwnd);
    virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(/* [in] */ BOOL fEnterMode);


	//window functions
	void setWindow(HWND win);
	void UpdateRect(RECT rcPos);

protected:
	ULONG m_ulObjRefCount;
	// The class/prog id of the control
	CLSID ClsID;
	LPCWSTR CodeBaseUrl;
	CComPtr<IUnknown> m_spObject;
	unsigned m_bBindingInProgress;
    // Result from the binding operation
    HRESULT m_hrBindResult;
	HWND Window;


private:
	HWND m_hWnd;
	HANDLE m_hEventStop;


};


