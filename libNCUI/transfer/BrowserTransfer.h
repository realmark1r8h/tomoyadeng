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
     * @brief	CEF提供的浏览器类封装.<br>
     * 			工作线程：**UI线程**.
     */
    
    class BrowserTransfer
        : public ClassTransfer
        , public amo::singleton<BrowserTransfer> {
    public:
        BrowserTransfer();
        BrowserTransfer(CefRefPtr<CefBrowser> pBrowser);
        
        /*!
         * @fn	Any BrowserTransfer::GetHost(IPCMessage::SmartType msg);
         *
         * @brief	获取浏览器的Host对象.
         *
         * @return	#BrowserHost.
         */
        
        Any GetHost(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::CanGoBack(IPCMessage::SmartType msg);
         *
         * @brief	判断当前浏览器是否可以后退.
         *
         *
         * @return	#Boolean true可以后退/false不能回退.
         */
        
        Any CanGoBack(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GoBack(IPCMessage::SmartType msg);
         *
         * @brief	后退.
         *
         * @return	无.
         */
        
        Any GoBack(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::CanGoForward(IPCMessage::SmartType msg);
         *
         * @brief	判断当前浏览器是否可以前进.
         *
         *
         * @return	#Boolean true可以前进false不能前进.
         */
        
        Any CanGoForward(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GoForward(IPCMessage::SmartType msg);
         *
         * @brief	前进.
         *
         * @return	无.
         */
        
        Any GoForward(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::IsLoading(IPCMessage::SmartType msg);
         *
         * @brief	是否正在加载页面.
         *
         * @return	#Boolean true是/false否.
         */
        
        Any IsLoading(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::Reload(IPCMessage::SmartType msg);
         *
         * @brief	重新加载页面.
         *
         * @return	无.
         */
        
        Any Reload(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::ReloadIgnoreCache(IPCMessage::SmartType msg);
         *
         * @brief	重新加载页面，无视任何缓存数据.
         *
         * @return	无.
         */
        
        Any ReloadIgnoreCache(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::StopLoad(IPCMessage::SmartType msg);
         *
         * @brief	停止加载页面.
         *
         * @return	无.
         */
        
        Any StopLoad(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetIdentifier(IPCMessage::SmartType msg);
         *
         * @brief	获取浏览器ID.
         *
         * @return	#Int 浏览器ID.
         */
        
        Any GetIdentifier(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::IsSame(IPCMessage::SmartType msg);
         *
         * @brief	与另一个Borwser对象比较是否相等.
         *
         * @param	#Object Browser 对象.
         *
         * @return	#Boolean true相同/false失败.
         */
        
        Any IsSame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::IsPopup(IPCMessage::SmartType msg);
         *
         * @brief	是否为一个弹出窗口.
         *
         * @return	#Boolean true弹出窗口/false非弹出窗口.
         */
        
        Any IsPopup(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::HasDocument(IPCMessage::SmartType msg);
         *
         * @brief	是否在浏览器中加载了文档.
         *
         *
         * @return	#Boolean true有document/false 无document.
         */
        
        Any HasDocument(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetMainFrame(IPCMessage::SmartType msg);
         *
         * @brief	返回浏览器窗口的主（顶层）框架Frame.
         *
         *
         * @return	#Frame Frame 对象.
         */
        
        Any GetMainFrame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFocusedFrame(IPCMessage::SmartType msg);
         *
         * @brief	返回浏览器窗口的焦点框架Frame.
         *
         *
         * @return	#Frame Frame 对象.
         */
        
        Any GetFocusedFrame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrame(IPCMessage::SmartType msg);
         *
         * @brief	通过名称或ID获取Frame.
         *
         * @param	#Int/String Frame ID 或Frame 名称.
         *
         * @return	#Frame Frame 对象.
         */
        
        Any GetFrame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrameCount(IPCMessage::SmartType msg);
         *
         * @brief	获取Frame个数.
         *
         * @return	#Int Frame个数.
         */
        
        Any GetFrameCount(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrameIdentifiers(IPCMessage::SmartType msg);
         *
         * @brief	获取所有Frame的ID，返回一个数组[].
         *
         * @return	#Array .
         */
        
        Any GetFrameIdentifiers(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrameNames(IPCMessage::SmartType msg);
         *
         * @brief	获取所有Frame的名称，返回一个数组[].
         *
         *
         * @return	#Array.
         */
        
        Any GetFrameNames(IPCMessage::SmartType msg);
        
        Any SendProcessMessage(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::currentFrame(IPCMessage::SmartType msg);
         *
         * @brief	获取当前Frame.
         *
         *
         * @return	#Frame Frame 对象.
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