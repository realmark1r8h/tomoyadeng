// Created by amoylel on 06/14/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_BROWSERWINDOWTRANSFER_H__
#define AMO_BROWSERWINDOWTRANSFER_H__

#include <memory>

#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"
#include "ui/win/NativeWindowProxy.h"

namespace amo {

    /*!
     * @class	BrowserWindow
     *
     * @copy  NativeWindowProxy
     *
     * @extend Object
     *
     * @brief	浏览器窗口创建及控制.<br>
     * 			工作线程:**UI线程**.
     */
    
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
        
        /**
         * @fn	virtual Any BrowserWindow(IPCMessage::SmartType msg) override;
         * @index 1
         *
         * @tag constructor sync
         *
         * @brief	创建一个浏览器窗口.
         *
         * @param	#Object 参见{@link 浏览器窗口参数}.
         *
         * @return	#BrowserWindow 一个浏览器窗口对象.
         * @example
         *
         ```
        	include('BrowserWindow');
        	// 创建一个普通窗口
        	var win = new BrowserWindow({titleBar:true, url: 'http://127.0.0.1:8030/example/BrowserWindow.html'});
        	// 创建一个离屏窗口
        	new BrowserWindow({
        			titleBar:false,
        			url: 'http://127.0.0.1:8030/example/FramelessWindow.html',
        			offscreen: true
        		});
        	// 创建一个透明窗口
        	new BrowserWindow({
        			titleBar:false,
        			hasShadow:false,
        			url: 'http://127.0.0.1:8030/example/TransparentWindow.html',
        			offscreen: true,
        			transparent: true
        		});
         ```
         */
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        
        // 静态函数
        
        /*!
         * @fn	Any BrowserWindowTransfer::currentWindow(IPCMessage::SmartType msg);
         *
         * @tag deprecated
         *
         * @brief   获取当前页面所对应的窗口对象
         *
         * @return	#BrowserWindow 如果不存在，返回Undefined.
         *
         * @see current=BrowserWindow.current
         */
        Any currentWindow(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any current(IPCMessage::SmartType msg);
         *
         * @brief	获取当前页面所对应的窗口对象.
         *
         * @return	#BrowserWindow 如果不存在，返回Undefined.
         */
        
        Any current(IPCMessage::SmartType msg);
        /*!
         * @fn	Any BrowserWindowTransfer::getAllWindows(IPCMessage::SmartType msg);
         *
         * @brief	获取所有的浏览器窗口.
         *
         *
         * @return	#Array 所有的浏览器窗口.
         *
         * @see All=BrowserWindow.All
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
         * @param	#Boolean  是否重绘界面,如果为false，将移除之前的计时器.
         * @param	#Int   重绘界面的间隔时间(毫秒)，程序每隔(delay)对页面进行一次重绘。
         * 				  如果=0，将不会添加计时器进行重绘.
         * 				  如果<30,delay会提升到30ms.
         *
         * @return	#Undefined.
         */
        
        virtual Any repaint(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any addOverlap(IPCMessage::SmartType msg);
         *
         * @brief	添加一个渲染图层，在进行页面重绘时会将该图片合并到页面原始的Bitmap中
         *
         * @param	#String   图层名称 （该名称为一个共享内存的名称，页面重绘时将读取共享内存中的数据进行合并）.
         *
         * @return	#Undefined.
         */
        
        virtual Any addOverlap(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any removeOverlap(IPCMessage::SmartType msg);
         *
         * @brief	移除一个渲染图层
         *
         * @param	#String 图层名称.
         *
         * @return	#Undefined.
         */
        
        virtual Any removeOverlap(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any setDragBlackList(IPCMessage::SmartType msg);
         *
         * @brief	设置拖拽黑名单.
         *
         * @param	#Int 参数.
         *
         * @return	无.
         */
        
        virtual Any setDragBlackList(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any getDragBlackList(IPCMessage::SmartType msg);
         *
         * @brief	获取拖拽黑名单.
         *
         *
         * @return	#Int 不允许拖拽的类型.
         */
        
        virtual Any getDragBlackList(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any addBrowserWindowSettings(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	为一个URL预设置窗口参数，当这个URL对应及其子路径的浏览器窗口由浏览器触发创建时，将使用该方法预设置的参数.<br>
         * 			说明:**该方法并不能影响new BrowserWindow() 创建的浏览器窗口**
         *
         * @param	#String 需要预设置窗口参数的url.
         *
         * @param	#JsonObject 可以支持的{@link 浏览器窗口参数}
         *
         * @return	无.
         *
         * @see removeBrowserWindowSettings 浏览器窗口参数
         * @example
         *
         ```
        	 includes('BrowserWindow', 'app');
        	 app.removeUrlMapping( "http://www.baidu.com/more");
        	 BrowserWindow.addBrowserWindowSettings('https://www.baidu.com',{titleBar: true});
        	 window.open('https://www.baidu.com');
        	 window.open('https://www.baidu.com/more');
        
         ```
         */
        
        Any addBrowserWindowSettings(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any removeBrowserWindowSettings(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	移除一个URL的默认窗口参数.
         *
         * @param	#String 需要移除浏览器窗口参数的URL.
         *
         * @return	无.
         *
         * @see addBrowserWindowSettings
         * @example
         *
         ```
        	 include('BrowserWindow');
        	 BrowserWindow.removeBrowserWindowSettings('https://www.baidu.com');
        	 window.open('https://www.baidu.com');
        	 window.open('https://www.baidu.com/more');
         ```
         */
        
        Any removeBrowserWindowSettings(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any getBrowserWindowSettings(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	获取指定URL的默认窗口参数.
         *
         * @param	#String URL.
         *
         * @return	#JsonObject.
         *
         * @example
         *
         */
        
        Any getBrowserWindowSettings(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any saveImageToFile(IPCMessage::SmartType msg);
         *
         * @brief	保存页面到文件， 离屏模式下(offscreen== true)有效.支持.png, .bmp, .gif, .jpeg, .jpg, .tiff
         *
         * @param	#String 图片保存路径.
         * @param	#Boolean=false 是否保存标题栏（标题栏存在时有效）
         *
         * @return	#Undefined.
         * @example
         *
         ```
        	include('BrowserWindow');
        	var win = BrowserWindow.current;
        	// 如果当前程序是以离屏模式运行才能成功
        	win.saveImageToFile('1.png', true);
        
        
        
         ```
         */
        
        virtual Any saveImageToFile(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any saveGifToFile(IPCMessage::SmartType msg);
         *
         * @brief	录制GIF到文件,离屏模式下(offscreen== true)有效(不建议使用).
         *
         * @param	#JsonObject 录制参数.<br>
         * 						| #String filename gif文件保存目录<br>
         * 						| #Int=10	delay 帧间隔（注意单位为:百分一秒）<br>
         * 						| #Int=20	total 最多录制帧数<br>
         *
         * @return	#Undefined.
         * @example
         *
         ```
        	include('BrowserWindow');
        	var win = BrowserWindow.current;
        	win.recordGifToFile({
        		filename: '1.gif',
        		delay: 10,
        		total:100
        	});
         ```
         */
        
        virtual Any recordGifToFile(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any stopRecordGif(IPCMessage::SmartType msg);
         *
         * @brief	停止录制GIF,离屏模式下(offscreen== true)有效(不建议使用).
         *
         * @return	#Undefined.
         * @example
         *
         ```
        	include('BrowserWindow');
        	var win = BrowserWindow.current;
        	win.stopRecordGif();
         ```
         */
        
        virtual Any stopRecordGif(IPCMessage::SmartType msg);
        
        
        //virtual Any dropFiles(IPCMessage::SmartType msg);
        
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
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeBrowserWindowSettings,
                                      TransferFuncStatic | TransferExecSync)
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
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(showTitleBar, TransferExecNormal)
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
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setWindowRect, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getWindowRect, TransferExecSync)
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
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getConfig, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setConfig, TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(repaint, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(addOverlap, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeOverlap, TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getOpacity, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setOpacity, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(disableIME, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(enableIME, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(computeCursor, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isComputeCursor, TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(saveImageToFile, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(recordGifToFile, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(stopRecordGif, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setTheme, TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
    protected:
    private:
        std::list<std::pair<std::string, amo::u8json > > m_oBrowserWindowSettings;
        
        std::string m_strBaseUrl;
    };
}

#endif // AMO_BROWSERWINDOWTRANSFER_H__
