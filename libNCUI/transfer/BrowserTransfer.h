// Created by amoylel on 06/14/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_BROWSERTRANSFER_H__
#define AMO_BROWSERTRANSFER_H__


#include <amo/singleton.hpp>

#include "handler/CefHeader.hpp"
#include "transfer/ClassTransfer.hpp"


namespace amo {

    /*!
     * @class	Browser
     *
     * @chapter cef
     *
     * @brief	CEF�ṩ����������װ.<br>
     * 			�����̣߳�**UI�߳�**.
     */
    
    class BrowserTransfer
        : public ClassTransfer
        , public amo::singleton<BrowserTransfer> {
    public:
        BrowserTransfer();
        BrowserTransfer(CefRefPtr<CefBrowser> pBrowser);
        
        /*!
         * @fn	Any BrowserTransfer::GetHost(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ȡ�������Host����.
         *
         * @return	#BrowserHost.
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 var host = browser.GetHost();
        	 var browser2 = host.GetBrowser();
        	 console.assert(browser.IsSame(browser2) == true);
         ```
         */
        
        Any GetHost(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::CanGoBack(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	�жϵ�ǰ������Ƿ���Ժ���.
         *
         *
         * @return	#Boolean true���Ժ���/false���ܻ���.
         * @example
         *
         ```
        	includes('BrowserWindow', 'Browser');
        	var browser = BrowserWindow.current.getBrowser();
        	console.log(browser.CanGoBack());
         ```
         */
        
        Any CanGoBack(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GoBack(IPCMessage::SmartType msg);
         *
         * @brief	����. BrowserWindowSettings.back_forword���Ϊfalse������{@link CanGoBack=Browser.CanGoBack}==false�ò�������ɹ�.
         *
         * @return	��.
         *
         * @see GetHost=Browser.GetHost
         *
         * @example
         *
         ```
        	includes('BrowserWindow', 'Browser');
        	var browser = BrowserWindow.current.getBrowser();
        	browser.GoBack();
         ```
         */
        
        Any GoBack(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::CanGoForward(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	�жϵ�ǰ������Ƿ����ǰ��.
         *
         *
         * @return	#Boolean true����ǰ��false����ǰ��.
         * @example
         *
         ```
        	includes('BrowserWindow', 'Browser');
        	var browser = BrowserWindow.current.getBrowser();
        	console.log(browser.CanGoForward());
         ```
         */
        
        Any CanGoForward(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GoForward(IPCMessage::SmartType msg);
         *
         * @brief	ǰ��. BrowserWindowSettings.back_forword���Ϊfalse������{@link CanGoForward=Browser.CanGoForward}==false�ò�������ɹ�.
         *
         * @return	��.
         * @see CanGoForward=Browser.CanGoForward
         *
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 browser.GoForward();
         ```
         */
        
        Any GoForward(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::IsLoading(IPCMessage::SmartType msg);
         *
         * @brief	�Ƿ����ڼ���ҳ��.
         *
         * @return	#Boolean true��/false��.
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 console.log(browser.IsLoading());
        	 console.assert(browser.IsLoading() != true);
         ```
         */
        
        Any IsLoading(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::Reload(IPCMessage::SmartType msg);
         *
         * @brief	���¼���ҳ��.
         *
         * @return	��.
         *
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 browser.Reload();
         ```
         */
        
        Any Reload(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::ReloadIgnoreCache(IPCMessage::SmartType msg);
         *
         * @brief	���¼���ҳ�棬�����κλ�������.
         *
         * @return	��.
         *
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 browser.ReloadIgnoreCache();
         ```
         */
        
        Any ReloadIgnoreCache(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::StopLoad(IPCMessage::SmartType msg);
         *
         * @brief	ֹͣ����ҳ��.
         *
         * @return	��.
         *
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 browser.StopLoad();
         ```
         */
        
        Any StopLoad(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetIdentifier(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ȡ�����ID.
         *
         * @return	#Int �����ID.
         *
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 console.log(browser.GetIdentifier());
         ```
         */
        
        Any GetIdentifier(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::IsSame(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	����һ��Borwser����Ƚ��Ƿ����.
         *
         * @param	#Object Browser ����.
         *
         * @return	#Boolean true��ͬ/falseʧ��.
         *
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 var win = new BrowserWindow({url:'http://www.baidu.com'});
        	 var browser2 = win.getBrowser();
        	 console.assert(browser.IsSame(browser) == false);
        	 setTimeout(function(){
        		win.close();
        	 }, 3000);
         ```
         */
        
        Any IsSame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::IsPopup(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	�Ƿ�Ϊһ����������.
         *
         * @return	#Boolean true��������/false�ǵ�������.
         *
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 console.log(browser.IsPopup());
         ```
         */
        
        Any IsPopup(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::HasDocument(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	�Ƿ���������м������ĵ�.
         *
         *
         * @return	#Boolean true��document/false ��document.
         *
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 console.log(browser.HasDocument());
         ```
         */
        
        Any HasDocument(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetMainFrame(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	������������ڵ��������㣩���Frame.
         *
         *
         * @return	#Frame Frame ����.
         *
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 var frame = browser.GetMainFrame();
        	 console.log(frame.GetIdentifier());
         ```
         */
        
        Any GetMainFrame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFocusedFrame(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	������������ڵĽ�����Frame.
         *
         *
         * @return	#Frame Frame ����.
         *
         * @example
         *
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 var frame = browser.GetFocusedFrame();
        	 console.log(frame.GetIdentifier());
         ```
         */
        
        Any GetFocusedFrame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrame(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	ͨ�����ƻ�ID��ȡFrame.
         *
         * @param	#Int/String Frame ID ��Frame ����.
         *
         * @return	#Frame Frame ����.
         * @example
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 var frame = browser.GetFocusedFrame();
        	 var id = frame.GetIdentifier();
        	 var frame2 = browser.GetFrame(id);
        	 console.assert(frame.GetIdentifier() == frame2.GetIdentifier());
         ```
         */
        
        Any GetFrame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrameCount(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ȡFrame����.
         *
         * @return	#Int Frame����.
         *
         * @example
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 var count = browser.GetFrameCount();
        	 console.log(count);
        	 console.assert(count == 1);
         ```
         */
        
        Any GetFrameCount(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrameIdentifiers(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ȡ����Frame��ID������һ������[].
         *
         * @return	#Array .
         *
         * @example
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 var arr = browser.GetFrameIdentifiers();
        	 console.log(arr);
        	 console.assert(arr.length == 1);
         ```
         */
        
        Any GetFrameIdentifiers(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrameNames(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ����Frame�����ƣ�����һ������[].
         *
         *
         * @return	#Array.
         *
         * @example
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 var arr = browser.GetFrameNames();
        	 console.log(arr);
        	 console.assert(arr.length == 1);
         ```
         */
        
        Any GetFrameNames(IPCMessage::SmartType msg);
        
        Any SendProcessMessage(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::currentFrame(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ��ǰFrame.
         *
         *
         * @return	#Frame Frame ����.
         *
         * @example
         ```
        	 includes('BrowserWindow', 'Browser');
        	 var browser = BrowserWindow.current.getBrowser();
        	 var frame = browser.currentFrame();
        	 console.log(frame.GetIdentifier());
         ```
         */
        
        Any currentFrame(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(BrowserTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetHost, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(CanGoBack, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GoBack, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(CanGoForward, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GoForward, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsLoading, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Reload, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(ReloadIgnoreCache, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(StopLoad, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetIdentifier, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsSame, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(IsPopup, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(HasDocument, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetMainFrame, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetFocusedFrame, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetFrame, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetFrameCount, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetFrameIdentifiers, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetFrameNames, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(SendProcessMessage, TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(currentFrame, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
        CefRefPtr<CefBrowser> m_pBrowser;
    };
}

#endif // AMO_BROWSERTRANSFER_H__