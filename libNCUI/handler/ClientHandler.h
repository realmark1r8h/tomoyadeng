// Created by amoylel on 6/22/2017.
// Copyright (c) 2017 amoylel. All rights reserved.

#ifndef AMO_CLIENTHANDLER_H__
#define AMO_CLIENTHANDLER_H__

#include <memory>

#include "handler/CefHeader.hpp"
#include "ipc/Any.hpp"

#include "handler/HandlerDelegate.hpp"
#include "handler/MessageRouterBrowserSide.h"

#include "handler/BrowserManager.hpp"
#include "handler/LifeSpanHandler.h"
#include <functional>






namespace amo {

    class ProcessExchanger;
    
    class ContextMenuHandler;
    class DialogHandler;
    class DisplayHandler;
    class DownloadHandler;
    class DragHandler;
    class FocusHandler;
    class GeolocationHandler;
    class JSDialogHandler;
    class KeyboardHandler;
    class LifeSpanHandler;
    class LoadHandler;
    class RenderHandler;
    class RequestHandler;
    class MessageRouterBrowserSide;
    
    class ContextMenuHandlerDelegate;
    class DialogHandlerDelegate;
    class DisplayHandlerDelegate;
    class DownloadHandlerDelegate;
    class DragHandlerDelegate;
    class FocusHandlerDelegate;
    class GeolocationHandlerDelegate;
    class JSDialogHandlerDelegate;
    class KeyboardHandlerDelegate;
    class LifeSpanHandlerDelegate;
    class LoadHandlerDelegate;
    class RenderHandlerDelegate;
    class RequestHandlerDelegate;
    class MessageRouterBrowserSide;
    class MessageHandlerDelegate;
    
    class ClientHandlerDelegate {
    public:
        ClientHandlerDelegate() {}
        
        virtual ~ClientHandlerDelegate() {}
        
        virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                              CefProcessId source_process,
                                              CefRefPtr<CefProcessMessage> message) {
            return false;
        }
        
    };
    
    
    class BrowserTempInfo {
    public:
        BrowserTempInfo() {
        
        
        }
        BrowserTempInfo(CefRefPtr<CefBrowser> browser,
                        std::function<bool(int, IPCMessage::SmartType)> fn) {
            pBrowser = browser;
            m_fnExec = fn;
        }
        
        CefRefPtr<CefBrowser> pBrowser;
        std::function<bool(int, IPCMessage::SmartType)> m_fnExec;
    };
    
    // Cef����ӿڴ�����
    class ClientHandler : public CefClient
        , public HandlerDelegate<ClientHandlerDelegate>
        , public LifeSpanHandlerDelegate
        , public BrowserManager<PID_BROWSER> {
    public:
        typedef std::set<MessageRouterBrowserSide::Handler*> MessageHandlerSet;
        
        
    public:
    
    public:
        ClientHandler();
        
        virtual ~ClientHandler();
        
        virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler();
        virtual CefRefPtr<CefDialogHandler> GetDialogHandler();
        virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler();
        virtual CefRefPtr<CefDownloadHandler> GetDownloadHandler();
        virtual CefRefPtr<CefDragHandler> GetDragHandler();
        virtual CefRefPtr<CefFocusHandler> GetFocusHandler();
        virtual CefRefPtr<CefGeolocationHandler> GetGeolocationHandler();
        virtual CefRefPtr<CefJSDialogHandler> GetJSDialogHandler();
        virtual CefRefPtr<CefKeyboardHandler> GetKeyboardHandler();
        virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler();
        virtual CefRefPtr<CefLoadHandler> GetLoadHandler();
        virtual CefRefPtr<CefRenderHandler> GetRenderHandler();
        virtual CefRefPtr<CefRequestHandler> GetRequestHandler();
        virtual CefRefPtr<MessageRouterBrowserSide> GetMessageRouterBrowserSide();
        
        /*!
         * @fn	virtual bool OnProcessMessageReceived(
         * 		CefRefPtr<CefBrowser> browser,
         * 		CefProcessId source_process,
         * 		CefRefPtr<CefProcessMessage> message);
         *
         * @brief	���������ӽ��̵���Ϣ.
         *
         * @param	browser		  	The browser.
         * @param	source_process	Source process.
         * @param	message		  	The message.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser,
                                              CefProcessId source_process,
                                              CefRefPtr<CefProcessMessage> message);
                                              
        /*!
         * @fn	bool RegisterContextMenuHandlerDelegate(
         * 		ContextMenuHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע���Ҽ��˵��¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterContextMenuHandlerDelegate(ContextMenuHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterContextMenuHandlerDelegate(
         * 		ContextMenuHandlerDelegate* delegate);
         *
         * @brief	��ע���Ҽ��˵��¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterContextMenuHandlerDelegate(ContextMenuHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterDialogHandlerDelegate(
         * 		DialogHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע���ļ��Ի�������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterDialogHandlerDelegate(DialogHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterDialogHandlerDelegate(DialogHandlerDelegate* delegate);
         *
         * @brief	��ע���ļ��Ի�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterDialogHandlerDelegate(DialogHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterDisplayHandlerDelegate(
         * 		DisplayHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע����ʾ�¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterDisplayHandlerDelegate(DisplayHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterDisplayHandlerDelegate(DisplayHandlerDelegate* delegate);
         *
         * @brief	��ע����ʾ�¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterDisplayHandlerDelegate(DisplayHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterDownloadHandlerDelegate(
         * 		DownloadHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע�������¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterDownloadHandlerDelegate(DownloadHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterDownloadHandlerDelegate(DownloadHandlerDelegate* delegate);
         *
         * @brief	��ע�������¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterDownloadHandlerDelegate(DownloadHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterDragHandlerDelegate(
         * 		DragHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע����ק�¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterDragHandlerDelegate(DragHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterDragHandlerDelegate(DragHandlerDelegate* delegate);
         *
         * @brief	��ע����ק�¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterDragHandlerDelegate(DragHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterFocusHandlerDelegate(
         * 		FocusHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע�ό���¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterFocusHandlerDelegate(FocusHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterFocusHandlerDelegate(FocusHandlerDelegate* delegate);
         *
         * @brief	��ע�ό���¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterFocusHandlerDelegate(FocusHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterGeolocationHandlerDelegate(
         * 		GeolocationHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע�����λ�ô�����.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterGeolocationHandlerDelegate(GeolocationHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterGeolocationHandlerDelegate(GeolocationHandlerDelegate* delegate);
         *
         * @brief	��ע�����λ�ô�����.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterGeolocationHandlerDelegate(GeolocationHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterJSDialogHandlerDelegate(
         * 		JSDialogHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	��Ϣ������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterJSDialogHandlerDelegate(JSDialogHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterJSDialogHandlerDelegate(JSDialogHandlerDelegate* delegate);
         *
         * @brief	��ע��JS��Ϣ������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterJSDialogHandlerDelegate(JSDialogHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterKeyboardHandlerDelegate(
         * 		KeyboardHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע������¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterKeyboardHandlerDelegate(KeyboardHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterKeyboardHandlerDelegate(KeyboardHandlerDelegate* delegate);
         *
         * @brief	��ע������¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterKeyboardHandlerDelegate(KeyboardHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterLifeSpanHandlerDelegate(
         * 		LifeSpanHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע������������¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterLifeSpanHandlerDelegate(LifeSpanHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterLifeSpanHandlerDelegate(LifeSpanHandlerDelegate* delegate);
         *
         * @brief	��ע������������¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterLifeSpanHandlerDelegate(LifeSpanHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterLoadHandlerDelegate(
         * 		LoadHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע��ҳ������¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterLoadHandlerDelegate(LoadHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterLoadHandlerDelegate(LoadHandlerDelegate* delegate);
         *
         * @brief	��ע��ҳ������¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterLoadHandlerDelegate(LoadHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterRenderHandlerDelegate(
         * 		RenderHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע����Ⱦ�¼�������
         * 			����ģʽ�¿���.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterRenderHandlerDelegate(RenderHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterRenderHandlerDelegate(RenderHandlerDelegate* delegate);
         *
         * @brief	��ע����Ⱦ�¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterRenderHandlerDelegate(RenderHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterRequestHandlerDelegate(
         * 		RequestHandlerDelegate* delegate,
         * 		int nIndex = -1);
         *
         * @brief	ע��Request�¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	nIndex				(Optional) the index.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterRequestHandlerDelegate(RequestHandlerDelegate* delegate, int nIndex = -1);
        
        /*!
         * @fn	void UnregisterRequestHandlerDelegate(RequestHandlerDelegate* delegate);
         *
         * @brief	��ע��Request�¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterRequestHandlerDelegate(RequestHandlerDelegate* delegate);
        
        /*!
         * @fn	bool RegisterMesssageHandlerDelegate(
         * 		MessageHandlerDelegate* delegate,
         * 		bool first = false);
         *
         * @brief	ע����Ϣ�¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         * @param	first				(Optional) true to first.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool RegisterMesssageHandlerDelegate(MessageHandlerDelegate* delegate, bool first = false);
        
        /*!
         * @fn	void UnregisterMesssageHandlerDelegate(MessageHandlerDelegate* delegate);
         *
         * @brief	��ע����Ϣ�¼�������.
         *
         * @param 	delegate	If non-null, the delegate.
         */
        
        void UnregisterMesssageHandlerDelegate(MessageHandlerDelegate* delegate);
        
        /*!
         * @fn	void CopyDelegates();
         *
         * @brief	 ����DummyClientHandler��ע���Handler.
         */
        
        void CopyDelegates();
        
        /*!
         * @fn	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
         *
         * @brief	Executes the after created action.
         *
         * @param	browser	The browser.
         */
        
        virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;
        
        /*!
         * @fn	virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
         *
         * @brief	Executes the close operation.
         *
         * @param	browser	The browser.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;
        
        /*!
         * @fn	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
         *
         * @brief	Executes the before close action.
         *
         * @param	browser	The browser.
         */
        
        virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;
        
        /*!
         * @fn	bool ProcessSyncMessage(int nID, IPCMessage::SmartType msg);
         *
         * @brief	����ͬ����Ϣ.
         *
         * @param	nID	The identifier.
         * @param	msg	The message.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool ProcessSyncMessage(int nID, IPCMessage::SmartType msg);
        
        
        IMPLEMENT_REFCOUNTING(ClientHandler);
        
        
    public:
        static BrowserTempInfo GetBrowserInfoFromTempByID(int nBrowserID);
        static void RemoveBrowserFromTempByID(int nBrowserID);
    private:
    
        /*! @brief	�˵��¼�������. */
        CefRefPtr<ContextMenuHandler> m_pContextMenuHandler;
        /*! @brief	�Ի����¼�������. */
        CefRefPtr<DialogHandler> m_pDialogHandler;
        /*! @brief	��ʾ�¼�������. */
        CefRefPtr<DisplayHandler> m_pDisplayHandler;
        /*! @brief	�����¼�������. */
        CefRefPtr<DownloadHandler> m_pDownloadHandler;
        /*! @brief	��ק�¼�������. */
        CefRefPtr<DragHandler> m_pDragHandler;
        /*! @brief	�����¼�������. */
        CefRefPtr<FocusHandler> m_pFocusHandler;
        /*! @brief	λ���¼�������. */
        CefRefPtr<GeolocationHandler> m_pGeolocationHandler;
        /*! @brief	JS��Ϣ������. */
        CefRefPtr<JSDialogHandler> m_pJSDialogHandler;
        /*! @brief	�����¼�������. */
        CefRefPtr<KeyboardHandler> m_pKeyboardHandler;
        /*! @brief	ҳ�洰���¼�������. */
        CefRefPtr<LifeSpanHandler> m_pLifeSpanHandler;
        /*! @brief	ҳ������¼�������. */
        CefRefPtr<LoadHandler> m_pLoadHandler;
        /*! @brief	ҳ����Ⱦ�¼�������. */
        CefRefPtr<RenderHandler> m_pRenderHandler;
        /*! @brief	ҳ�������¼�������. */
        CefRefPtr<RequestHandler> m_pRequestHandler;
        /*! @brief	��Ϣ�¼�������. */
        CefRefPtr<MessageRouterBrowserSide> m_pMessageRouter;
        /*! @brief	��Ϣ�����༯��. */
        static MessageHandlerSet m_MessageSet;
        /*! @brief	The temporary browser map. */
        static std::unordered_map<int, BrowserTempInfo > m_oTempBrowserMap;
    };
}

#endif // AMO_CLIENTHANDLER_H__
