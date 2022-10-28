// Created by amoylel on 07/19/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_BROWSERHOSTTRANSFER_H__
#define AMO_BROWSERHOSTTRANSFER_H__

#include <amo/singleton.hpp>

#include "handler/CefHeader.hpp"
#include "transfer/ClassTransfer.hpp"

namespace amo {

    /*!
     * @class	BrowserHost
     *
     * @chapter cef
     *
     * @brief	CEF BrowserHost �����װ.<br>
     * 			�����̣߳�**UI�߳�**.
     */
    
    class BrowserHostTransfer
        : public ClassTransfer
        , public amo::singleton < BrowserHostTransfer > {
    public:
        BrowserHostTransfer();
        BrowserHostTransfer(CefRefPtr<CefBrowserHost> pBrowserHost);
        
        Any current(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any BrowserHostTransfer::click(IPCMessage::SmartType msg);
         *
         * @brief	��ҳ�淢�͵����¼�.
         *
         * @param	#Int=0 X������.
         * @param	#Int=0 Y������
         *
         * @return	#Undefined.
         * @example
         *
         ```
        	includes('BrowserWindow', 'BrowserHost');
        	var host = BrowserHost.current;
        	var x = $('.closebtn').offset().left;
        	var y = $('.closebtn').offset().top;
        
        	console.log(x);
        	console.log(y);
        	host.click(x + 20, y + 20);
         ```
         */
        
        Any click(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any BrowserHostTransfer::GetBrowser(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ȡHost����Ӧ��Browser����.
         *
         *
         * @return	#Browser.
         * @example
         *
         ```
        	includes('BrowserWindow', 'BrowserHost', 'Browser');
        	var host = BrowserHost.current;
        	console.log(host.GetBrowser().GetIdentifier());
        
         ```
         */
        
        Any GetBrowser(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any BrowserHostTransfer::CloseBrowser(IPCMessage::SmartType msg);
         *
         * @brief	�ر������.
         *
         * @return	#Undefined.
         * @example
         *
         ```
        	includes('BrowserWindow', 'BrowserHost', 'Browser');
        	var host = BrowserHost.current;
        	host.CloseBrowser();
        
         */
        
        Any CloseBrowser(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any BrowserHostTransfer::SetFocus(IPCMessage::SmartType msg);
         *
         * @brief	ʹ�������ý���.
         *
         * @return	#Undefined.
         * @example
         *
         ```
        	includes('BrowserWindow', 'BrowserHost', 'Browser');
        	var host = BrowserHost.current;
        	host.SetFocus();
        
         ```
         */
        
        Any SetFocus(IPCMessage::SmartType msg);
        Any SetWindowVisibility(IPCMessage::SmartType msg);
        Any GetWindowHandle(IPCMessage::SmartType msg);
        Any GetOpenerWindowHandle(IPCMessage::SmartType msg);
        Any GetClient(IPCMessage::SmartType msg);
        Any GetRequestContext(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any BrowserHostTransfer::GetZoomLevel(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	��ȡҳ�����ŵȼ�.
         *
         * @return	#Double.
         * @example
         *
         ```
        	includes('BrowserWindow', 'BrowserHost', 'Browser');
        	var host = BrowserHost.current;
        	console.log(host.GetZoomLevel());
        	host.SetZoomLevel(1.0);
        	console.assert(host.GetZoomLevel() == 1.0);
        	host.SetZoomLevel(0.0);
         ```
         */
        
        Any GetZoomLevel(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any BrowserHostTransfer::SetZoomLevel(IPCMessage::SmartType msg);
         *
         * @brief	�豸ҳ�����ŵȼ� .
         *
         * @param	#Double ���ŵȼ�.
         *
         * @return	#Undefined.
         *
         * @example
         *
         ```
        	includes('BrowserWindow', 'BrowserHost', 'Browser');
        	var host = BrowserHost.current;
        	host.SetZoomLevel(-0.6);
         ```
         */
        
        Any SetZoomLevel(IPCMessage::SmartType msg);
        Any RunFileDialog(IPCMessage::SmartType msg);
        Any StartDownload(IPCMessage::SmartType msg);
        Any Print(IPCMessage::SmartType msg);
        Any PrintToPDF(IPCMessage::SmartType msg);
        Any Find(IPCMessage::SmartType msg);
        Any StopFinding(IPCMessage::SmartType msg);
        Any ShowDevTools(IPCMessage::SmartType msg);
        Any CloseDevTools(IPCMessage::SmartType msg);
        Any GetNavigationEntries(IPCMessage::SmartType msg);
        Any SetMouseCursorChangeDisabled(IPCMessage::SmartType msg);
        Any IsMouseCursorChangeDisabled(IPCMessage::SmartType msg);
        Any ReplaceMisspelling(IPCMessage::SmartType msg);
        Any AddWordToDictionary(IPCMessage::SmartType msg);
        Any NotifyScreenInfoChanged(IPCMessage::SmartType msg);
        Any Invalidate(IPCMessage::SmartType msg);
        Any SendKeyEvent(IPCMessage::SmartType msg);
        Any SendMouseClickEvent(IPCMessage::SmartType msg);
        Any SendMouseMoveEvent(IPCMessage::SmartType msg);
        Any SendMouseWheelEvent(IPCMessage::SmartType msg);
        Any SendFocusEvent(IPCMessage::SmartType msg);
        Any SendCaptureLostEvent(IPCMessage::SmartType msg);
        Any NotifyMoveOrResizeStarted(IPCMessage::SmartType msg);
        Any GetWindowlessFrameRate(IPCMessage::SmartType msg);
        Any SetWindowlessFrameRate(IPCMessage::SmartType msg);
        Any HandleKeyEventBeforeTextInputClient(IPCMessage::SmartType msg);
        Any HandleKeyEventAfterTextInputClient(IPCMessage::SmartType msg);
        Any IsWindowRenderingDisabled(IPCMessage::SmartType msg);
        
        // �����¿���
        Any WasResized(IPCMessage::SmartType msg);
        Any WasHidden(IPCMessage::SmartType msg);
        Any GetNSTextInputContext(IPCMessage::SmartType msg);
        Any DragTargetDragEnter(IPCMessage::SmartType msg);
        Any DragTargetDragOver(IPCMessage::SmartType msg);
        Any DragTargetDragLeave(IPCMessage::SmartType msg);
        Any DragTargetDrop(IPCMessage::SmartType msg);
        Any DragSourceEndedAt(IPCMessage::SmartType msg);
        Any DragSourceSystemDragEnded(IPCMessage::SmartType msg);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(BrowserHostTransfer, ClassTransfer)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(current,
                                      TransferFuncConstProperty | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(click, TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetBrowser, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(CloseBrowser, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(SetFocus, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(SetWindowVisibility, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(GetZoomLevel, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(SetZoomLevel, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(StartDownload, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Print, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(SendMouseClickEvent, TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
        CefRefPtr<CefBrowserHost> m_pBrowserHost;
    };
}


#endif // AMO_BROWSERHOSTTRANSFER_H__
