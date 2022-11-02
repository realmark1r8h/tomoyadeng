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
     * @brief	��������ڴ���������.<br>
     * 			�����̣߳�**UI�߳�**.
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
         * @brief	����һ�����������.
         *
         * @param	#Object �μ�{@link ��������ڲ���}.
         *
         * @return	#BrowserWindow һ����������ڶ���.
         * @example
         *
         ```
        	include('BrowserWindow');
        	// ����һ����ͨ����
        	var win = new BrowserWindow({titleBar:true, url: 'http://127.0.0.1:8020/doc/example/BrowserWindow.html'});
        	// ����һ����������
        	new BrowserWindow({
        			titleBar:false,
        			url: 'http://127.0.0.1:8020/doc/example/FramelessWindow.html',
        			offscreen: true
        		});
        	// ����һ��͸������
        	new BrowserWindow({
        			titleBar:false,
        			hasShadow:false,
        			url: 'http://127.0.0.1:8020/doc/example/TransparentWindow.html',
        			offscreen: true,
        			transparent: true
        		});
         ```
         */
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        
        // ��̬����
        
        /*!
         * @fn	Any BrowserWindowTransfer::currentWindow(IPCMessage::SmartType msg);
         *
         * @tag deprecated
         *
         * @brief   ��ȡ��ǰҳ������Ӧ�Ĵ��ڶ���
         *
         * @return	#BrowserWindow ��������ڣ�����Undefined.
         *
         * @see current=BrowserWindow.current
         */
        Any currentWindow(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any current(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ��ǰҳ������Ӧ�Ĵ��ڶ���.
         *
         * @return	#BrowserWindow ��������ڣ�����Undefined.
         */
        
        Any current(IPCMessage::SmartType msg);
        /*!
         * @fn	Any BrowserWindowTransfer::getAllWindows(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ���е����������.
         *
         *
         * @return	#Array ���е����������.
         *
         * @see All=BrowserWindow.All
         */
        Any getAllWindows(IPCMessage::SmartType msg);
        
        Any getFocusedWindow(IPCMessage::SmartType msg);
        
        Any fromID(IPCMessage::SmartType msg);
        
        Any fromName(IPCMessage::SmartType msg);
        
        // ����
        // ���ڵ�Ψһid
        virtual Any id(IPCMessage::SmartType msg) override;
        virtual Any loadURL(IPCMessage::SmartType msg);
        virtual Any reload(IPCMessage::SmartType msg);
        virtual Any enableDrag(IPCMessage::SmartType msg);
        virtual Any disableDrag(IPCMessage::SmartType msg);
        virtual Any getBrowser(IPCMessage::SmartType msg);
        virtual Any showDevTools(IPCMessage::SmartType msg);
        virtual Any closeDevTools(IPCMessage::SmartType msg);
        
        // �򴰿ڷ�����Ϣ
        virtual Any exec(IPCMessage::SmartType msg);
        virtual Any sync(IPCMessage::SmartType msg);
        virtual Any async(IPCMessage::SmartType msg);
        
        virtual Any isMainWindow(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any repaint(IPCMessage::SmartType msg);
         *
         * @brief	ǿ��ҳ���ػ棬��ֹ֮ͣǰ��ǿ���ػ�
         *
         * @param	#Boolean  �Ƿ��ػ����,���Ϊfalse�����Ƴ�֮ǰ�ļ�ʱ��.
         * @param	#Int   �ػ����ļ��ʱ��(����)������ÿ��(delay)��ҳ�����һ���ػ档
         * 				  ���=0����������Ӽ�ʱ�������ػ�.
         * 				  ���<30,delay��������30ms.
         *
         * @return	#Undefined.
         */
        
        virtual Any repaint(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any addOverlap(IPCMessage::SmartType msg);
         *
         * @brief	���һ����Ⱦͼ�㣬�ڽ���ҳ���ػ�ʱ�Ὣ��ͼƬ�ϲ���ҳ��ԭʼ��Bitmap��
         *
         * @param	#String   ͼ������ ��������Ϊһ�������ڴ�����ƣ�ҳ���ػ�ʱ����ȡ�����ڴ��е����ݽ��кϲ���.
         *
         * @return	#Undefined.
         */
        
        virtual Any addOverlap(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any removeOverlap(IPCMessage::SmartType msg);
         *
         * @brief	�Ƴ�һ����Ⱦͼ��
         *
         * @param	#String ͼ������.
         *
         * @return	#Undefined.
         */
        
        virtual Any removeOverlap(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any setDragBlackList(IPCMessage::SmartType msg);
         *
         * @brief	������ק������.
         *
         * @param	#Int ����.
         *
         * @return	��.
         */
        
        virtual Any setDragBlackList(IPCMessage::SmartType msg);
        
        /**
         * @fn	virtual Any getDragBlackList(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ��ק������.
         *
         *
         * @return	#Int ��������ק������.
         */
        
        virtual Any getDragBlackList(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any addBrowserWindowSettings(IPCMessage::SmartType msg);
         *
         * @tag static sync
         *
         * @brief	Ϊһ��URLԤ���ô��ڲ����������URL��Ӧ������·����������������������������ʱ����ʹ�ø÷���Ԥ���õĲ���.<br>
         * 			˵����**�÷���������Ӱ��new BrowserWindow() ���������������**
         *
         * @param	#String ��ҪԤ���ô��ڲ�����url.
         *
         * @param	#JsonObject ����֧�ֵ�{@link ��������ڲ���}
         *
         * @return	��.
         *
         * @see removeBrowserWindowSettings ��������ڲ���
         * @example
         *
         ```
        	 include('BrowserWindow');
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
         * @brief	�Ƴ�һ��URL��Ĭ�ϴ��ڲ���.
         *
         * @param	#String ��Ҫ�Ƴ���������ڲ�����URL.
         *
         * @return	��.
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
         * @brief	��ȡָ��URL��Ĭ�ϴ��ڲ���.
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
         * @brief	����ҳ�浽�ļ��� ����ģʽ��(offscreen== true)��Ч.֧��.png, .bmp, .gif, .jpeg, .jpg, .tiff
         *
         * @param	#String ͼƬ����·��.
         * @param	#Boolean=false �Ƿ񱣴������������������ʱ��Ч��
         *
         * @return	#Undefined.
         * @example
         *
         ```
        	include('BrowserWindow');
        	var win = BrowserWindow.current;
        	// �����ǰ������������ģʽ���в��ܳɹ�
        	win.saveImageToFile('1.png', true);
        
        
        
         ```
         */
        
        virtual Any saveImageToFile(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(BrowserWindowTransfer, ClassTransfer)
        
        // ������
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
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
    protected:
    private:
        std::list<std::pair<std::string, amo::json > > m_oBrowserWindowSettings;
        
        std::string m_strBaseUrl;
    };
}

#endif // AMO_BROWSERWINDOWTRANSFER_H__
