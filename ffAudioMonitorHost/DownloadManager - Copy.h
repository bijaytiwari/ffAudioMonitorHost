//#pragma once
//#include "urlmon.h"
//#include "windows.h"
//
//
//
//#define CDOWNLOADMANAGER_INTERFACES() \
//    COM_INTERFACE_ENTRY(IOleWindow) \
//    COM_INTERFACE_ENTRY(IBindStatusCallback) \
//    COM_INTERFACE_ENTRY(IWindowForBindingUI)
//
//enum
//{
//	UF_BINDSTATUS_FIRST = BINDSTATUS_FINDINGRESOURCE,
//	UF_BINDSTATUS_LAST = BINDSTATUS_ACCEPTRANGES
//};
//
//class CDownloadManager :
//	public IBindStatusCallback,
//	public IOleControlSite,
//	public IWindowForBindingUI
//{
//	
//public:
//	CDownloadManager(void);
//	virtual ~CDownloadManager(void);
//	CDownloadManager(HWND hWnd, HANDLE hEventStop);
//
//	//BEGIN_COM_MAP(CDownloadManager)
//	//	CDOWNLOADMANAGER_INTERFACES()
//	//END_COM_MAP()
//
//	//BEGIN_OLECOMMAND_TABLE()
//	//END_OLECOMMAND_TABLE()
//
//	//// Returns the window used when processing ole commands
//	//HWND GetCommandTargetWindow()
//	//{
//	//	return NULL; // TODO
//	//}
//	//bool SetComObject(CComPtr<IUnknown> *CcomObject);
//	//void setCodeBaseUrl(LPCWSTR clsid);
//	virtual HRESULT Create(REFCLSID clsid, CComPtr<IUnknown> &CcomObject, LPCWSTR szCodebase = NULL, IBindCtx *pBindContext = NULL);
//
//	// IUnknown methods
//	STDMETHOD(QueryInterface)(REFIID riid, void **ppvObject);
//	STDMETHOD_(ULONG, AddRef)();
//	STDMETHOD_(ULONG, Release)();
//
//	// IBindStatusCallback methods
//	STDMETHOD(OnStartBinding)(DWORD, IBinding *);
//	STDMETHOD(GetPriority)(LONG *);
//	STDMETHOD(OnLowResource)(DWORD);
//	STDMETHOD(OnProgress)(ULONG ulProgress,
//						  ULONG ulProgressMax,
//						  ULONG ulStatusCode,
//						  LPCWSTR szStatusText);
//	STDMETHOD(OnStopBinding)(HRESULT, LPCWSTR);
//	STDMETHOD(GetBindInfo)(DWORD *, BINDINFO *);
//	STDMETHOD(OnDataAvailable)(DWORD, DWORD, FORMATETC *, STGMEDIUM *);
//	STDMETHOD(OnObjectAvailable)(REFIID, IUnknown *);
//
//	// IWindowForBindingUI
//    virtual HRESULT STDMETHODCALLTYPE GetWindow(/* [in] */ REFGUID rguidReason, /* [out] */ HWND *phwnd);
//
//	// IOleWindow implementation
//    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow(/* [out] */ HWND __RPC_FAR *phwnd);
//    virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(/* [in] */ BOOL fEnterMode);
//
//
//	//window functions
//	void setWindow(HWND win);
//	void UpdateRect(RECT rcPos);
//
//protected:
//	ULONG m_ulObjRefCount;
//	// The class/prog id of the control
//	CLSID ClsID;
//	LPCWSTR CodeBaseUrl;
//	CComPtr<IUnknown> m_spObject;
//	unsigned m_bBindingInProgress;
//    // Result from the binding operation
//    HRESULT m_hrBindResult;
//	HWND Window;
//
//
//private:
//	HWND m_hWnd;
//	HANDLE m_hEventStop;
//
//
//};


#ifndef CDOWNLOADMANAGER_H
#define CDOWNLOADMANAGER_H

#include "IOleCommandTargetImpl.h"


// If you created a class derived from CControlSite, use the following macro
// in the interface map of the derived class to include all the necessary
// interfaces.
#define CDOWNLOADMANAGER_INTERFACES() \
    COM_INTERFACE_ENTRY(IOleControlSite) \
    COM_INTERFACE_ENTRY(IOleCommandTarget) \
    COM_INTERFACE_ENTRY(IBindStatusCallback) \
    COM_INTERFACE_ENTRY(IWindowForBindingUI)

//class CControlSiteSecurityPolicy
//{
//public:
//    // Test if the class is safe to host
//    virtual BOOL IsClassSafeToHost(const CLSID & clsid) = 0;
//    // Test if the specified class is marked safe for scripting
//    virtual BOOL IsClassMarkedSafeForScripting(const CLSID & clsid, BOOL &bClassExists) = 0;
//    // Test if the instantiated object is safe for scripting on the specified interface
//    virtual BOOL IsObjectSafeForScripting(IUnknown *pObject, const IID &iid) = 0;
//};


class CDownloadManager : public CComObjectRootEx<CComSingleThreadModel>,
                        /*public CControlSiteSecurityPolicy,*/
						/*public IOleInPlaceSite,*/
                        public IOleControlSite,
                        public IOleCommandTargetImpl<CDownloadManager>,
                        public IBindStatusCallback,
                        public IWindowForBindingUI
{
public:
// Site management values
    // Handle to parent window
    HWND m_hWndParent;
    // Position of the site and the contained object
    RECT m_rcObjectPos;
    // Flag indicating if client site should be set early or late
    unsigned m_bSetClientSiteFirst:1;
    // Flag indicating whether control is visible or not
    unsigned m_bVisibleAtRuntime:1;
    // Flag indicating if control is in-place active
    unsigned m_bInPlaceActive:1;
    // Flag indicating if control is UI active
    unsigned m_bUIActive:1;
    // Flag indicating if control is in-place locked and cannot be deactivated
    unsigned m_bInPlaceLocked:1;
    // Flag indicating if the site allows windowless controls
    unsigned m_bSupportWindowlessActivation:1;
    // Flag indicating if control is windowless (after being created)
    unsigned m_bWindowless:1;
    // Flag indicating if only safely scriptable controls are allowed
    unsigned m_bSafeForScriptingObjectsOnly:1;
    // Pointer to the OLE container
    CComPtr<IOleContainer> m_spContainer;
    // Return the default security policy object
	//ss
   // static CControlSiteSecurityPolicy *GetDefaultControlSecurityPolicy();

protected:
// Pointers to object interfaces
    // Raw pointer to the object
    CComPtr<IUnknown> m_spObject;
    // Pointer to objects IViewObject interface
    CComQIPtr<IViewObject, &IID_IViewObject> m_spIViewObject;
    // Pointer to object's IOleObject interface
    CComQIPtr<IOleObject, &IID_IOleObject> m_spIOleObject;
    // Pointer to object's IOleInPlaceObject interface
    CComQIPtr<IOleInPlaceObject, &IID_IOleInPlaceObject> m_spIOleInPlaceObject;
    // Pointer to object's IOleInPlaceObjectWindowless interface
    CComQIPtr<IOleInPlaceObjectWindowless, &IID_IOleInPlaceObjectWindowless> m_spIOleInPlaceObjectWindowless;
    // CLSID of the control
    CLSID m_CLSID;
    // Parameter list
   // PropertyList m_ParameterList;
    // Pointer to the security policy
	//ss
    //CControlSiteSecurityPolicy *m_pSecurityPolicy;

// Binding variables
    // Flag indicating whether binding is in progress
    unsigned m_bBindingInProgress;
    // Result from the binding operation
    HRESULT m_hrBindResult;

// Double buffer drawing variables used for windowless controls
    // Area of buffer
    RECT m_rcBuffer;
    // Bitmap to buffer
    HBITMAP m_hBMBuffer;
    // Bitmap to buffer
    HBITMAP m_hBMBufferOld;
    // Device context
    HDC m_hDCBuffer;
    // Clipping area of site
    HRGN m_hRgnBuffer;
    // Flags indicating how the buffer was painted
    DWORD m_dwBufferFlags;

// Ambient properties
    // Locale ID
    LCID m_nAmbientLocale;
    // Foreground colour
    COLORREF m_clrAmbientForeColor;
    // Background colour
    COLORREF m_clrAmbientBackColor;
    // Flag indicating if control should hatch itself
    bool m_bAmbientShowHatching:1;
    // Flag indicating if control should have grab handles
    bool m_bAmbientShowGrabHandles:1;
    // Flag indicating if control is in edit/user mode
    bool m_bAmbientUserMode:1;
    // Flag indicating if control has a 3d border or not
    bool m_bAmbientAppearance:1;

protected:
    // Notifies the attached control of a change to an ambient property
    virtual void FireAmbientPropertyChange(DISPID id);

public:
// Construction and destruction
    // Constructor
    CDownloadManager();
    // Destructor
    virtual ~CDownloadManager();

BEGIN_COM_MAP(CDownloadManager)
    CDOWNLOADMANAGER_INTERFACES()
END_COM_MAP()

BEGIN_OLECOMMAND_TABLE()
END_OLECOMMAND_TABLE()

    // Returns the window used when processing ole commands
    HWND GetCommandTargetWindow()
    {
        return NULL; // TODO
    }

// Object creation and management functions
    // Creates and initialises an object
    virtual HRESULT Create(REFCLSID clsid, CComPtr<IUnknown> &CcomObject, LPCWSTR szCodebase = NULL, IBindCtx *pBindContext = NULL);
    // Attaches the object to the site
    virtual HRESULT Attach(HWND hwndParent, const RECT &rcPos, IUnknown *pInitStream = NULL);
    // Detaches the object from the site
    virtual HRESULT Detach();
    // Returns the IUnknown pointer for the object
    virtual HRESULT GetControlUnknown(IUnknown **ppObject);
    // Sets the bounding rectangle for the object
    virtual HRESULT SetPosition(const RECT &rcPos);
    // Draws the object using the provided DC
    virtual HRESULT Draw(HDC hdc);
    // Performs the specified action on the object
    virtual HRESULT DoVerb(LONG nVerb, LPMSG lpMsg = NULL);
    // Sets an advise sink up for changes to the object
    virtual HRESULT Advise(IUnknown *pIUnkSink, const IID &iid, DWORD *pdwCookie);
    // Removes an advise sink
    virtual HRESULT Unadvise(const IID &iid, DWORD dwCookie);
    
    virtual void SetContainer(IOleContainer *pContainer)
    {
        m_spContainer = pContainer;
    }
    // Set the security policy object. Ownership of this object remains with the caller and the security
    // policy object is meant to exist for as long as it is set here.
	//SS
    //virtual void SetSecurityPolicy(CControlSiteSecurityPolicy *pSecurityPolicy)
    //{
    //    m_pSecurityPolicy = pSecurityPolicy;
    //}
    //virtual CControlSiteSecurityPolicy *GetSecurityPolicy() const
    //{
    //    return m_pSecurityPolicy;
    //}

// Methods to set ambient properties
    virtual void SetAmbientUserMode(BOOL bUser);
	//STDMETHOD(QueryInterface)(REFIID riid, void **ppvObject);

// Inline helper methods
    // Returns the object's CLSID
    virtual const CLSID &GetObjectCLSID() const
    {
        return m_CLSID;
    }
    // Tests if the object is valid or not
    virtual BOOL IsObjectValid() const
    {
        return (m_spObject) ? TRUE : FALSE;
    }
    // Returns the parent window to this one
    virtual HWND GetParentWindow() const
    {
        return m_hWndParent;
    }
    // Returns the inplace active state of the object
    virtual BOOL IsInPlaceActive() const
    {
        return m_bInPlaceActive;
    }

// CControlSiteSecurityPolicy
	//SS
    // Test if the class is safe to host
    //virtual BOOL IsClassSafeToHost(const CLSID & clsid);
    //// Test if the specified class is marked safe for scripting
    //virtual BOOL IsClassMarkedSafeForScripting(const CLSID & clsid, BOOL &bClassExists);
    //// Test if the instantiated object is safe for scripting on the specified interface
    //virtual BOOL IsObjectSafeForScripting(IUnknown *pObject, const IID &iid);
    //// Test if the instantiated object is safe for scripting on the specified interface
    //virtual BOOL IsObjectSafeForScripting(const IID &iid);


// IOleWindow implementation
    virtual /* [input_sync] */ HRESULT STDMETHODCALLTYPE GetWindow(/* [out] */ HWND __RPC_FAR *phwnd);
    virtual HRESULT STDMETHODCALLTYPE ContextSensitiveHelp(/* [in] */ BOOL fEnterMode);

// IOleClientSite implementation
    //virtual HRESULT STDMETHODCALLTYPE SaveObject(void);
    //virtual HRESULT STDMETHODCALLTYPE GetMoniker(/* [in] */ DWORD dwAssign, /* [in] */ DWORD dwWhichMoniker, /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk);
    //virtual HRESULT STDMETHODCALLTYPE GetContainer(/* [out] */ IOleContainer __RPC_FAR *__RPC_FAR *ppContainer);
    //virtual HRESULT STDMETHODCALLTYPE ShowObject(void);
    //virtual HRESULT STDMETHODCALLTYPE OnShowWindow(/* [in] */ BOOL fShow);
    //virtual HRESULT STDMETHODCALLTYPE RequestNewObjectLayout(void);

// IOleInPlaceSite implementation
    //virtual HRESULT STDMETHODCALLTYPE CanInPlaceActivate(void);
    //virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivate(void);
    //virtual HRESULT STDMETHODCALLTYPE OnUIActivate(void);
    //virtual HRESULT STDMETHODCALLTYPE GetWindowContext(/* [out] */ IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame, /* [out] */ IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc, /* [out] */ LPRECT lprcPosRect, /* [out] */ LPRECT lprcClipRect, /* [out][in] */ LPOLEINPLACEFRAMEINFO lpFrameInfo);
    //virtual HRESULT STDMETHODCALLTYPE Scroll(/* [in] */ SIZE scrollExtant);
    //virtual HRESULT STDMETHODCALLTYPE OnUIDeactivate(/* [in] */ BOOL fUndoable);
    //virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivate(void);
    //virtual HRESULT STDMETHODCALLTYPE DiscardUndoState(void);
    //virtual HRESULT STDMETHODCALLTYPE DeactivateAndUndo(void);
    //virtual HRESULT STDMETHODCALLTYPE OnPosRectChange(/* [in] */ LPCRECT lprcPosRect);

// IOleInPlaceSiteEx implementation
    //virtual HRESULT STDMETHODCALLTYPE OnInPlaceActivateEx(/* [out] */ BOOL __RPC_FAR *pfNoRedraw, /* [in] */ DWORD dwFlags);
    //virtual HRESULT STDMETHODCALLTYPE OnInPlaceDeactivateEx(/* [in] */ BOOL fNoRedraw);
    //virtual HRESULT STDMETHODCALLTYPE RequestUIActivate(void);

// IOleInPlaceSiteWindowless implementation
    //virtual HRESULT STDMETHODCALLTYPE CanWindowlessActivate(void);
    //virtual HRESULT STDMETHODCALLTYPE GetCapture(void);
    //virtual HRESULT STDMETHODCALLTYPE SetCapture(/* [in] */ BOOL fCapture);
    //virtual HRESULT STDMETHODCALLTYPE GetFocus(void);
    //virtual HRESULT STDMETHODCALLTYPE SetFocus(/* [in] */ BOOL fFocus);
    //virtual HRESULT STDMETHODCALLTYPE GetDC(/* [in] */ LPCRECT pRect, /* [in] */ DWORD grfFlags, /* [out] */ HDC __RPC_FAR *phDC);
    //virtual HRESULT STDMETHODCALLTYPE ReleaseDC(/* [in] */ HDC hDC);
    //virtual HRESULT STDMETHODCALLTYPE InvalidateRect(/* [in] */ LPCRECT pRect, /* [in] */ BOOL fErase);
    //virtual HRESULT STDMETHODCALLTYPE InvalidateRgn(/* [in] */ HRGN hRGN, /* [in] */ BOOL fErase);
    //virtual HRESULT STDMETHODCALLTYPE ScrollRect(/* [in] */ INT dx, /* [in] */ INT dy, /* [in] */ LPCRECT pRectScroll, /* [in] */ LPCRECT pRectClip);
    //virtual HRESULT STDMETHODCALLTYPE AdjustRect(/* [out][in] */ LPRECT prc);
    //virtual HRESULT STDMETHODCALLTYPE OnDefWindowMessage(/* [in] */ UINT msg, /* [in] */ WPARAM wParam, /* [in] */ LPARAM lParam, /* [out] */ LRESULT __RPC_FAR *plResult);

// IOleControlSite implementation
    virtual HRESULT STDMETHODCALLTYPE OnControlInfoChanged(void);
    virtual HRESULT STDMETHODCALLTYPE LockInPlaceActive(/* [in] */ BOOL fLock);
    virtual HRESULT STDMETHODCALLTYPE GetExtendedControl(/* [out] */ IDispatch __RPC_FAR *__RPC_FAR *ppDisp);
    virtual HRESULT STDMETHODCALLTYPE TransformCoords(/* [out][in] */ POINTL __RPC_FAR *pPtlHimetric, /* [out][in] */ POINTF __RPC_FAR *pPtfContainer, /* [in] */ DWORD dwFlags);
    virtual HRESULT STDMETHODCALLTYPE TranslateAccelerator(/* [in] */ MSG __RPC_FAR *pMsg, /* [in] */ DWORD grfModifiers);
    virtual HRESULT STDMETHODCALLTYPE OnFocus(/* [in] */ BOOL fGotFocus);
    virtual HRESULT STDMETHODCALLTYPE ShowPropertyFrame( void);

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

typedef CComObject<CDownloadManager> CControlSiteInstance;



#endif