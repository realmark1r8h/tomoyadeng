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
         *
         * @brief	��ȡ�������Host����.
         *
         * @return	#BrowserHost.
         */
        
        Any GetHost(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::CanGoBack(IPCMessage::SmartType msg);
         *
         * @brief	�жϵ�ǰ������Ƿ���Ժ���.
         *
         *
         * @return	#Boolean true���Ժ���/false���ܻ���.
         */
        
        Any CanGoBack(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GoBack(IPCMessage::SmartType msg);
         *
         * @brief	����.
         *
         * @return	��.
         */
        
        Any GoBack(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::CanGoForward(IPCMessage::SmartType msg);
         *
         * @brief	�жϵ�ǰ������Ƿ����ǰ��.
         *
         *
         * @return	#Boolean true����ǰ��false����ǰ��.
         */
        
        Any CanGoForward(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GoForward(IPCMessage::SmartType msg);
         *
         * @brief	ǰ��.
         *
         * @return	��.
         */
        
        Any GoForward(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::IsLoading(IPCMessage::SmartType msg);
         *
         * @brief	�Ƿ����ڼ���ҳ��.
         *
         * @return	#Boolean true��/false��.
         */
        
        Any IsLoading(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::Reload(IPCMessage::SmartType msg);
         *
         * @brief	���¼���ҳ��.
         *
         * @return	��.
         */
        
        Any Reload(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::ReloadIgnoreCache(IPCMessage::SmartType msg);
         *
         * @brief	���¼���ҳ�棬�����κλ�������.
         *
         * @return	��.
         */
        
        Any ReloadIgnoreCache(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::StopLoad(IPCMessage::SmartType msg);
         *
         * @brief	ֹͣ����ҳ��.
         *
         * @return	��.
         */
        
        Any StopLoad(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetIdentifier(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ�����ID.
         *
         * @return	#Int �����ID.
         */
        
        Any GetIdentifier(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::IsSame(IPCMessage::SmartType msg);
         *
         * @brief	����һ��Borwser����Ƚ��Ƿ����.
         *
         * @param	#Object Browser ����.
         *
         * @return	#Boolean true��ͬ/falseʧ��.
         */
        
        Any IsSame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::IsPopup(IPCMessage::SmartType msg);
         *
         * @brief	�Ƿ�Ϊһ����������.
         *
         * @return	#Boolean true��������/false�ǵ�������.
         */
        
        Any IsPopup(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::HasDocument(IPCMessage::SmartType msg);
         *
         * @brief	�Ƿ���������м������ĵ�.
         *
         *
         * @return	#Boolean true��document/false ��document.
         */
        
        Any HasDocument(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetMainFrame(IPCMessage::SmartType msg);
         *
         * @brief	������������ڵ��������㣩���Frame.
         *
         *
         * @return	#Frame Frame ����.
         */
        
        Any GetMainFrame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFocusedFrame(IPCMessage::SmartType msg);
         *
         * @brief	������������ڵĽ�����Frame.
         *
         *
         * @return	#Frame Frame ����.
         */
        
        Any GetFocusedFrame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrame(IPCMessage::SmartType msg);
         *
         * @brief	ͨ�����ƻ�ID��ȡFrame.
         *
         * @param	#Int/String Frame ID ��Frame ����.
         *
         * @return	#Frame Frame ����.
         */
        
        Any GetFrame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrameCount(IPCMessage::SmartType msg);
         *
         * @brief	��ȡFrame����.
         *
         * @return	#Int Frame����.
         */
        
        Any GetFrameCount(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrameIdentifiers(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ����Frame��ID������һ������[].
         *
         * @return	#Array .
         */
        
        Any GetFrameIdentifiers(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any BrowserTransfer::GetFrameNames(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ����Frame�����ƣ�����һ������[].
         *
         *
         * @return	#Array.
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