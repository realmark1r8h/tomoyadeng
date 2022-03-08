// Created by amoylel on 06/14/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_BROWSERWINDOWTRANSFER_H__
#define AMO_BROWSERWINDOWTRANSFER_H__

#include <memory>

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"
#include "ui/win/NativeWindowProxy.h"

namespace amo {

    class BrowserWindowTransfer
        : public ClassTransfer
        , public virtual NativeWindowProxy
        , public amo::singleton<BrowserWindowTransfer> {
        
    public:
        BrowserWindowTransfer();
        
        Any test1(IPCMessage::SmartType msg);
        Any test2(IPCMessage::SmartType msg);
        Any test3(IPCMessage::SmartType msg);
        
        Any test4(IPCMessage::SmartType msg);
        Any test5(IPCMessage::SmartType msg);
        Any test6(IPCMessage::SmartType msg);
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        
        // 静态函数
        
        /*!
         * @fn	Any BrowserWindowTransfer::currentWindow(IPCMessage::SmartType msg);
         *
         * @brief   获取当前窗口
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any currentWindow(IPCMessage::SmartType msg);
        Any current(IPCMessage::SmartType msg);
        /*!
         * @fn	Any BrowserWindowTransfer::getAllWindows(IPCMessage::SmartType msg);
         *
         * @brief	获取所有的浏览器窗口.
         *
         * @param	msg	The message.
         *
         * @return	all windows.
         */
        Any getAllWindows(IPCMessage::SmartType msg);
        Any getFocusedWindow(IPCMessage::SmartType msg);
        Any fromID(IPCMessage::SmartType msg);
        Any fromName(IPCMessage::SmartType msg);
        
        // 属性
        // 窗口的唯一id
        virtual Any id(IPCMessage::SmartType msg) override;
        virtual Any loadURL(IPCMessage::SmartType msg);
        virtual Any reload(IPCMessage::SmartType msg);
        virtual Any enableDrag(IPCMessage::SmartType msg);
        virtual Any disableDrag(IPCMessage::SmartType msg);
        virtual Any getBrowser(IPCMessage::SmartType msg);
        virtual Any showDevTools(IPCMessage::SmartType msg);
        virtual Any closeDevTools(IPCMessage::SmartType msg);
        
        // 向窗口发送消息
        virtual Any exec(IPCMessage::SmartType msg);
        virtual Any sync(IPCMessage::SmartType msg);
        virtual Any async(IPCMessage::SmartType msg);
        
        virtual Any isMainWindow(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any repaint(IPCMessage::SmartType msg);
         *
         * @brief	强制页面重绘，或停止之前的强制重绘
         *
         * @param	repaint 是否重绘界面,如果为false，将移除之前的计时器.
         * @param	delay 重绘界面的间隔时间(毫秒)，程序每隔(delay)对页面进行一次重绘。
         * 				  如果=0，将不会添加计时器进行重绘.
         * 				  如果<30,delay会提升到30ms.
         *
         * @return	Undefined.
         */
        
        virtual Any repaint(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any addOverlap(IPCMessage::SmartType msg);
         *
         * @brief	添加一个渲染图层，在进行页面重绘时会将该图片合并到页面原始的Bitmap中
         *
         * @param	name 图层名称 （该名称为一个共享内存的名称，页面重绘时将读取共享内存中的数据进行合并）.
         *
         * @return	Undefined.
         */
        
        virtual Any addOverlap(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any removeOverlap(IPCMessage::SmartType msg);
         *
         * @brief	移除一个渲染图层
         *
         * @param	name 图层名称.
         *
         * @return	Undefined.
         */
        
        virtual Any removeOverlap(IPCMessage::SmartType msg);
        
        Any addBrowserWindowSettings(IPCMessage::SmartType msg);
        Any removeBrowserWindowSettings(IPCMessage::SmartType msg);
        Any getBrowserWindowSettings(IPCMessage::SmartType msg);
        
        
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(BrowserWindowTransfer, ClassTransfer)
        
        // 测试用
        //AMO_CEF_MESSAGE_TRANSFER_FUNC(test1, TransferExecNormal)
        //AMO_CEF_MESSAGE_TRANSFER_FUNC(test2, TransferExecSync)
        //AMO_CEF_MESSAGE_TRANSFER_FUNC(test3, TransferExecAsync)
        //
        //AMO_CEF_MESSAGE_TRANSFER_FUNC(test4, TransferExecSync)
        //AMO_CEF_MESSAGE_TRANSFER_FUNC(test5, TransferExecSync)
        //AMO_CEF_MESSAGE_TRANSFER_FUNC(test6, TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(addBrowserWindowSettings,
                                      TransferFuncStatic | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeBrowserWindowSettings,
                                      TransferFuncStatic | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getBrowserWindowSettings,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(current,
                                      TransferFuncConstProperty | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(currentWindow,
                                      TransferFuncConstProperty | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getAllWindows,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getFocusedWindow,
                                      TransferFuncStatic | TransferExecSync)
                                      
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getName,  TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setName, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(id,  TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(close, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(destroy, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(focus, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isFocused, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(show, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(showInactive, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(hide, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isVisible, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(maximize, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(unmaximize, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isMaximized, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(minimize, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(restore, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isMinimized, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setFullScreen, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isFullScreen, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setBounds, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getBounds, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setSize, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getSize, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setMinimumSize, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getMinimumSize, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setMaximumSize, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getMaximumSize, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setResizable, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isResizable, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setMovable, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isMovable, TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setMinimizable, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isMinimizable, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setMaximizable, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isMaximizable, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setFullScreenable, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isFullScreenable, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setClosable, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isClosable, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setAlwaysOnTop, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isAlwaysOnTop, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(center, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setPosition, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getPosition, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setTitle, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getTitle, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(flashFrame, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(topmost, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isTopmost, TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(loadURL, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(reload, TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setHasShadow, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(hasShadow, TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(showDevTools, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(closeDevTools, TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(exec, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(sync, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(async, TransferExecAsync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(enableDrag, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(disableDrag, TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getBrowser, TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(toggleFullScreen, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(toggleVisible, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setIcon, TransferExecNormal)
        
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isMainWindow, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(showModal, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getConfigs, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getConfig, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setConfig, TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(repaint, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(addOverlap, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeOverlap, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
    protected:
    private:
        std::list<std::pair<std::string, amo::json > > m_oBrowserWindowSettings;
        
        std::string m_strBaseUrl;
    };
}

#endif // AMO_BROWSERWINDOWTRANSFER_H__
