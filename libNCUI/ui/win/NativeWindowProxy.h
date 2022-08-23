// Created by amoylel on 07/27/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_NATIVEWINDOWPROXY_H__
#define AMO_NATIVEWINDOWPROXY_H__


#include <memory>
#include "ipc/Any.hpp"
/*!
 * @namespace	amo
 *
 * @brief	.
 */
namespace amo {
    /*!
     * @class	NativeWindowSettings
     *
     * @unexport
     *
     * @brief	A native window settings.
     */
    class NativeWindowSettings;
    /*!
     * @class	NativeWindowProxy
     *
     * @unexport
     *
     * @brief	A native window proxy.
     */
    class NativeWindowProxy {
    public:
    
        virtual Any id(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::getName(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	��ȡ������.
         *
         * @return	#String.
         *
         * @see setName=NativeWindowProxy.setName
         * @example
         * 			```
        			var win = BrowserWindow.current;
        			console.log(win.getName());
         * 			```
         */
        virtual Any getName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::setName(IPCMessage::SmartType msg);
         *
         * @brief	���ô�����,���������ʱ��û��ʲô�ã�ֻ�ǰ����Ʊ���������.
         *
         * @param	#String ����.
         *
         * @return	��.
         * @example
         * 		   ```
        			var win = BrowserWindow.current;
        			win.setName('NCUI���Դ���');
        			console.assert(win.getName() == 'NCUI���Դ���');
         * 		   ```
         */
        virtual Any setName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::showTitleBar(IPCMessage::SmartType msg);
         *
         * @brief	��ʾ/���ر�����.
         *
         * @param	#Boolean=false  true��ʾ/false����.
         *
         * @return	��.
         *
         * @example
        
        		 ```
        		 var win = BrowserWindow.current;
        		 var titleBar = win.getConfig('titleBar');
        		 win.showTitleBar(!titleBar);
        		```
         */
        
        virtual Any showTitleBar(IPCMessage::SmartType msg);
        
        
        
        /*!
        * @fn	Any NativeWindowProxy::close(IPCMessage::SmartType msg);
        *
        * @brief	���Թرմ��ڣ����Ա��û�ȡ���磺window.onload.<br>
        * 			��{@link isClosable=BrowserWindow.isClosable}Ϊtrue,�ú�����Ч.
        *
        *
        * @return	��.
        *
        * @see destroy=NativeWindowProxy.destroy setClosable=BrowserWindow.setClosable
        *
        * @example
        * 		   ```
        * 		   var win = BrowserWindow.current;
        * 		   win.close();
        * 		   ```
        */
        Any close(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::destroy(IPCMessage::SmartType msg);
         *
         * @brief	ǿ�ƹرմ���,�û�����ȡ���ò���, ��������֤�� closed ����.<br>
         * 			��{@link isClosable=BrowserWindow.isClosable}Ϊtrue,�ú�����Ч.
         *
         * @return	��.
         *
         * @see close=NativeWindowProxy.close setClosable=BrowserWindow.setClosable
         *
         * @example
         * 		   ```
        				// ���ڽ���ǿ�ƹرգ��û�����ȡ���ò���
        				var win = BrowserWindow.current;
        				win.destroy();
         * 		   ```
         */
        Any destroy(IPCMessage::SmartType msg);
        
        
        
        /*!
         * @fn	Any NativeWindowProxy::focus(IPCMessage::SmartType msg);
         *
         * @brief	���ڻ�ý���.
         *
         * @return	��.
         *
         * @example
         * 		   ```
         * 		   var win = BrowserWindow.current;
         * 		   win.focus();
         * 		   ```
         */
        Any focus(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isFocused(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	�жϴ����Ƿ��ý���.
         *
         * @return	#Boolean .
         * @example
         * 		   ```
         * 		   var win = BrowserWindow.current;
         * 		   console.assert(win.isFocused() == true);
         *
         *		   win.minimize();
         *		   console.assert(win.isFocused() == false);
         *
         *		   win.restore();
         *		   console.assert(win.isFocused() == true);
         * 		   ```
         */
        Any isFocused(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::show(IPCMessage::SmartType msg);
         *
         * @brief	��ʾ����ʹ���ڻ�ý���.
         *
         * @return	��.
         *
         * @see hide=BrowserWindow.hide isVisible=BrowserWindow.isVisible showInactive=BrowserWindow.showInactive
         *
         * @example
         * 		   ```
          		   var win = BrowserWindow.current;
          		   win.show();
          		   console.assert(win.isFocused() == true);
        
         * 		   ```
         */
        Any show(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::showInactive(IPCMessage::SmartType msg);
         *
         * @brief	��ʾ���ڵ��ǲ���ý���.��������ڱ�����Ѿ���ý��㣬���øú����󴰿���Ȼ�н���
         *
         * @return	��.
         *
         * @see hide=BrowserWindow.hide isVisible=BrowserWindow.isVisible show=BrowserWindow.show
         *
         * @example
         * 		   ```
          		   var win = BrowserWindow.current;
        		   win.show();
        		   console.assert(win.isFocused() == true);
        
          		   win.showInactive();
          		   console.assert(win.isFocused() == true);
         * 		   ```
         */
        Any showInactive(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::hide(IPCMessage::SmartType msg);
         *
         * @brief	���ش���.
         *
         * @return	��.
         *
         * @see isVisible=BrowserWindow.isVisible show=BrowserWindow.show showInactive=BrowserWindow.showInactive
         *
         * @example
         * 		   ```
         * 			var win = BrowserWindow.current;
         * 			win.hide();
         * 			console.assert(win.isVisible() == false);
         *			console.assert(win.isFocused() == false);
         *
         *			// ��ʾ���������
         * 			win.showInactive();
         * 			console.assert(win.isFocused() == false);
         * 		   ```
         */
        Any hide(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isVisible(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	�жϴ����Ƿ�ɼ�.
         *
         * @return	#Boolean.
         *
         * @see hide=BrowserWindow.hide show=BrowserWindow.show showInactive=BrowserWindow.showInactive
         *
         * @example
         * 		   ```
         *			var win = BrowserWindow.current;
         * 			win.hide();
         *			console.assert(win.isVisible() == false);
         *
         * 			win.showInactive();
         * 			console.assert(win.isVisible() == true);
         * 			console.assert(win.isFocused() == false);
         *
         * 			win.show();
         * 			console.assert(win.isVisible() == true);
         * 			console.assert(win.isFocused() == true);
         * 		   ```
         */
        Any isVisible(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::maximize(IPCMessage::SmartType msg);
         *
         * @brief	�������.
         *
         * @return	��.
         *
         * @see unmaximize=BrowserWindow.unmaximize restore=BrowserWindow.restore isMaximized=BrowserWindow.isMaximized
         * @example
         *
        			 ```
        			 var win = BrowserWindow.current;
        			 win.maximize();
        			 console.assert(win.isMaximized()==true);
        			 ```
         */
        Any maximize(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::unmaximize(IPCMessage::SmartType msg);
         *
         * @brief	ȡ��������󻯣�����ʹ��{@link restore=BrowserWindow.restore}����
         *
         * @return	��.
         *
         * @see restore=BrowserWindow.restore
         *
         * @example
         *
        		 ```
        			var win = BrowserWindow.current;
        			win.unmaximize();
        			console.assert(win.isMaximized() == false);
        		 ```
         */
        Any unmaximize(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isMaximized(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	�жϴ����Ƿ����.
         *
         *
         * @return	#Boolean.
         *
         * @example
         *
        		 ```
        			var win = BrowserWindow.current;
        			win.maximize();
        			console.assert(win.isMaximized() == true);
        
        			win.unmaximize();
        			console.assert(win.isMaximized() == false);
        		 ```
         */
        Any isMaximized(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::minimize(IPCMessage::SmartType msg);
         *
         * @brief	������С��.
         *
         * @return	��.
         *
         * @see isMinimized=BrowserWindow.isMinimized restore=BrowserWindow.restore
         *
         * @example
         *
        		```
        			var win = BrowserWindow.current;
        
        			win.minimize();
        			console.assert(win.isMinimized() == true);
        
        			// ��ԭ����
        			win.restore();
        			console.assert(win.isMinimized() == false);
        		```
         */
        Any minimize(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::restore(IPCMessage::SmartType msg);
         *
         * @brief	�����ڻָ�Ϊ֮ǰ��״̬,���ܴ���֮ǰ����С���������.
         *
         * @return	��.
         *
         * @see  minimize=BrowserWindow.minimize maximize=BrowserWindow.maximize
         *
         * @example
         *
        			 ```
        			 var win = BrowserWindow.current;
        
        			 win.minimize();
        			 console.assert(win.isMinimized() == true);
        			 win.maximize();
        			 console.assert(win.isMaximized() == true);
        			 // ��ԭ����
        			 win.restore();
        			 console.assert(win.isMinimized() == false);
        			 ```
         *
         */
        Any restore(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isMinimized(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief  �жϴ����Ƿ���С��.
         *
         * @see minimize=BrowserWindow.minimize
         *
         * @example
          *
        			 ```
        			 var win = BrowserWindow.current;
        
        			 win.minimize();
        			 console.assert(win.isMinimized() == true);
        			 win.maximize();
        			 console.assert(win.isMaximized() == true);
        			 // ��ԭ����
        			 win.restore();
        			 console.assert(win.isMinimized() == false);
        			 ```
         *
         *
         * @return	#Boolean.
         */
        Any isMinimized(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::setFullScreen(IPCMessage::SmartType msg);
         *
         * @brief	�����Ƿ�ȫ��.
         *
         * @param	#Boolean=false ȫ��/��ȫ��.
         *
         * @return	��.
         *
         * @see isFullScreen=BrowserWindow.isFullScreen toggleFullScreen=BrowserWindow.toggleFullScreen
         *
         * @example
         *
        		 ```
        			var win = BrowserWindow.current;
        			win.setFullScreen(true);
        			console.assert(win.isFullScreen() == true);
        
        		 ```
         */
        virtual Any setFullScreen(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::isFullScreen(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	�жϴ����Ƿ���ȫ��״̬.
         *
         *
         * @return	#Boolean.
         *
         * @example
         *
        		 ```
        		 var win = BrowserWindow.current;
        		 win.setFullScreen(true);
        		 console.assert(win.isFullScreen() == true);
        
        		 win.setFullScreen(false);
        		 console.assert(win.isFullScreen() == false);
        
        		 ```
         */
        virtual Any isFullScreen(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setWindowRect(IPCMessage::SmartType msg);
         *
         * @brief	�������ô��ڵĿ��ֵ�������ƶ���ָ���� x, y λ��,<br>
         * 			�����ڴ���ȫ���������״̬ʱ���ú�����Ч.<br>
         * 			���������С�����ƿ��ʱ������С���Ϊ׼<br>
         * 			��������ߴ������ƿ��ʱ���������Ϊ׼
         *
         * @param	#JsonObject .
         *
         * @return	��.
         *
         * @see  getWindowRect=BrowserWindow.getWindowRect
         *
         * @example
        			 ```
        				var win = BrowserWindow.current;
        
        				win.setWindowRect({
        					x: 100,
        					y: 100,
        					width: 1000,
        					height: 500,
        				});
        
        			 ```
         */
        Any setWindowRect(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::getWindowRect(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	����һ�������������˴��ڵĿ��ߣ�x���꣬y����.
         *
         *
         * @return	#JsonObject ���ڵ��������.
         *			|#Int x �������Ͻ�X����.
         *			|#Int y �������Ͻ�Y����.
         *			|#Int r �������½�X����.
         *			|#Int b �������½�Y����.
         *			|#Int width ���ڿ��.
         *			|#Int height ���ڸ߶�.
         *
         * @see setWindowRect=BrowserWindow.setWindowRect
         *
         * @example
        			```
        				var win = BrowserWindow.current;
        
        				win.setWindowRect({
        					x: 100,
        					y: 100,
        					width: 1000,
        					height: 500,
        				});
        
        				// ��ȡ��������
        				var winInfo = win.getWindowRect();
        				console.assert(winInfo.x == 100);
        				console.assert(winInfo.y == 100);
        				console.assert(winInfo.width == 1000);
        				console.assert(winInfo.height == 500);
        
        			```
         */
        Any getWindowRect(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setSize(IPCMessage::SmartType msg);
         *
         * @brief	�������ô��ڵĿ��ֵ,���ڵ�X�����Y���걣�ֲ���,<br>
         * 			�����ڴ���ȫ���������״̬ʱ���ú�����Ч<br>
         * 			���������С�����ƿ��ʱ������С���Ϊ׼<br>
         * 			��������ߴ������ƿ��ʱ���������Ϊ׼.
         *
         * @param	#Int=0 ��.
         *
         * @param	#Int=0 ��
         *
         * @return	��.
         *
         * @see getSize=BrowserWindow.getSize
         *
         * @example
         *
        		 ```
        			 var win = BrowserWindow.current;
        			 win.setSize(1300,800);
        		 ```
         *
         */
        Any setSize(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::getSize(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ���ڿ��.
         *
         *
         * @return	#JsonObject ���ڵĿ������.
         *
         * @see setSize=BrowserWindow.setSize
         *
         * @example
         * 		   ```
        				var win = BrowserWindow.current;
        				// ���ô��ڿ��
        				win.setSize(1000,500);
        
        				// ��ȡ���ڿ��
        				var info = win.getSize();
        				console.log(info);
        				console.assert(info.width == 1000);
        				console.assert(info.height == 500);
        
         * 		   ```
         */
        Any getSize(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::setMinimumSize(IPCMessage::SmartType msg);
         *
         * @brief	���ô�����С���Ŀ��ֵ��,��������Ϊ0ʱ����ȡ����С�������.
         *
         * @param	#Int	��С���.
         *
         * @param	#Int	��С�߶�.
         *
         * @return	��.
         *
         * @example
          		   ```
        				// ������С���
        				var win = BrowserWindow.current;
        				win.setMinimumSize(1280,720);
          		   ```
         */
        virtual Any setMinimumSize(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::getMinimumSize(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	����һ�������������˴�����С���Ŀ���.{width:100, height:200}
         *
         *
         * @return	#JsonObject ���ڵ���С�����Ϣ.
         * @example
         * 		   ```
        				var win = BrowserWindow.current;
        				win.setMinimumSize(1280,720);
        
        				// ��ȡ��С���
        				var info = win.getMinimumSize();
        				console.assert(info.width == 1280);
        				console.assert(info.height == 720);
        
        				// ȡ������
        				win..setMinimumSize(0,0);
         * 		   ```
         *
         */
        virtual Any getMinimumSize(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::setMaximumSize(IPCMessage::SmartType msg);
         *
         * @brief	���ô��������ֵ,��������Ϊ0ʱ����ȡ�����������<br>
         * 			�������������ߣ���ô���ڲ��ܱ���󻯣�����������ֵ�ǲ��Ǳ���Ļ���ڴ�<br>
         * 			����ȫ�����ܸú���Ӱ��.
         *
         * @param	#Int	�����.
         *
         * @param	#Int	���߶�
         *
         * @return	��.
         * @example
        		   ```
        				// ������С���
        				var win = BrowserWindow.current;
        				win.setMaximumSize(1280,720);
        		   ```
         */
        
        virtual Any setMaximumSize(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::getMaximumSize(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	����һ�������������˴�����󻯵Ŀ���.{width:100, height:200}
         *
         * @return	#JsonObject ���ڵ��������Ϣ.
         *
         * @example
         * 		   ```
        				var win = BrowserWindow.current;
        				win.setMaximumSize(1280,720);
        
        				// ��ȡ�����
        				var info = win.getMaximumSize();
        				console.assert(info.width == 1280);
        				console.assert(info.height == 720);
        
        				// ȡ����󻯿������,DEBUGģ������Ч
        				win.setMaximumSize(0,0);
        
        
         * 		   ```
         */
        virtual Any getMaximumSize(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::setResizable(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ���Ա��û��ı䴰�ڴ�С.<br>
         * 			�ú������ȼ�����setMaximizable��ֻҪ���������������������ڵ�����һ��{@link setMaximizable(true)=BrowserWindow.setMaximizable},
         * 			maximizable�ᱻ����Ϊtrue
         *
         * @param	#Boolean=false true���� false������ .
         *
         * @return	��.
         *
         * @example
         *
        		```
        		// �������ڸı��С
        		var win = BrowserWindow.current;
        		win.setResizable(false);
        		console.assert(win.isResizable() == false);
        		```
         *
         */
        virtual Any setResizable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isResizable(IPCMessage::SmartType msg);
         * @tag sync
         *
         * @brief	�жϴ����Ƿ���Ա��û��ı��С.
         *
         * @return	#Boolean.
         *
         * @example
         *
        		 ```
        			var win = BrowserWindow.current;
        			win.setResizable(false);
        			console.assert(win.isResizable()== false);
        			// �����ڸı��С
        			win.setResizable(true);
        			console.assert(win.isResizable() == true);
        		 ```
         */
        Any isResizable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setMovable(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ���Ա��û��϶�.
         *
         * @param	#Boolean=false true�����ƶ���false�����ƶ�����λ��.
         *
         * @return	��.
         * @example
         *
        		 ```
        			// �϶���������
        			var win = BrowserWindow.current;
        			win.setMovable(false);
        
        		 ```
         */
        Any setMovable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isMovable(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	�жϴ����Ƿ���Ա��û��϶�.
         *
         * @return	#Boolean.
         *
         * @example
         *
        		 ```
        			var win = BrowserWindow.current;
        			win.setMovable(false);
        			console.assert(win.isMovable() == false);
        			// �����ڱ��ı�λ��
        			win.setMovable(true);
        			console.assert(win.isMovable() == true);
        
        		 ```
         */
        Any isMovable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setMinimizable(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ������С��.
         *
         * @param	#Boolean true/false.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        			// ���ô��ڲ��ܱ���С��
        			var win = BrowserWindow.current;
        			win.setMinimizable(false);
        			console.assert(win.isMinimizable()== false);
        		 ```
         */
        Any setMinimizable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isMinimizable(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	�жϴ����Ƿ������С��.
         *
         *
         * @return	#Boolean.
         * @example
         *
        	 ```
        		 // ���ô��ڲ��ܱ���С��
        		 var win = BrowserWindow.current;
        		 win.setMinimizable(false);
        		 console.assert(win.isMinimizable() == false);
        
        		 // ���ô��ڿ��Ա���С��
        		 win.setMinimizable(true);
        		 console.assert(win.isMinimizable() == true);
        	 ```
         */
        Any isMinimizable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setMaximizable(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ�������. ���{@link isResizable=BrowserWindow.isResizable}==false���˺�����Ч
         *
         * @param	#Boolean true/false.
         *
         * @return	��.
         *
         * @see setResizable=BrowserWindow.setResizable isMaximizable=BrowserWindow.isMaximizable
         *
         * @example
         *
        			```
        			// �����������
        			var win = BrowserWindow.current;
        			win.setMaximizable(false);
        			console.assert(win.isMaximizable() == false);
        
        			```
         */
        virtual Any setMaximizable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isMaximizable(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	�жϴ����Ƿ�������.
         *
         *
         * @return	#Boolean.
         * @example
         *
        		 ```
        			// �����������
        			var win = BrowserWindow.current;
        			win.setMaximizable(false);
        			console.assert(win.isMaximizable() == false);
        			// ���������
        			win.setMaximizable(true);
        			console.assert(win.isMaximizable() == true);
        
        		 ```
         */
        Any isMaximizable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setFullScreenable(IPCMessage::SmartType msg);
         *
         * @brief	���÷����ȫ��.
         *
         * @param	#Boolean=false true/false.
         *
         * @return	��.
         *
         * @example
         *
        			```
        				// ��������ȫ��
        				var win = BrowserWindow.current;
        				win.setFullScreenable(false);
        				console.assert(win.isFullScreenable() == false);
        				// �޷�ȫ��
        				win.setFullScreen(true);
        				console.assert(win.isFullScreen() == false);
        			```
         */
        
        Any setFullScreenable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isFullScreenable(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	�ж��Ƿ�����ȫ��.
         *
         * @return	#Boolean.
         * @example
         *
         ```
        		 // ��������ȫ��
        		 var win = BrowserWindow.current;
        		 win.setFullScreenable(false);
        		 console.assert(win.isFullScreenable() == false);
        		 // �޷�ȫ��
        		 win.setFullScreen(true);
        		 console.assert(win.isFullScreen() == false);
        
        		// ������ȫ��
        		 win.setFullScreenable(true);
        		 console.assert(win.isFullScreenable() == true);
        		 // ����ȫ��
        		 win.setFullScreen(true);
        		 console.assert(win.isFullScreen() == true);
        
        		 ```
         */
        Any isFullScreenable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setClosable(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ������Ϊ�ر�.
         *
         * @param	#Boolean=false true���Թرգ�false���ܹر�.
         *
         * @return	��.
         * @example
         *
        			 ```
        			 var win = BrowserWindow.current;
        			 win.setClosable(false);
        			 // ���ڴ��ڹز�����
        			 console.assert(win.isClosable() == false);
        
        			 ```
         */
        Any setClosable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isClosable(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	�жϴ����Ƿ���Թر�.
         *
         * @return	#Boolean.
         *
         * @example
         *
        			 ```
        			 var win = BrowserWindow.current;
        			 win.setClosable(false);
        			 console.assert(win.isClosable() == false);
        
        			 win.setClosable(true);
        			 console.assert(win.isClosable() == true);
        
        			 ```
        
         */
        Any isClosable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setAlwaysOnTop(IPCMessage::SmartType msg);
         *
         * @brief	�Ƿ������������ʼ������������֮��.
         *
         * @param	#Boolean true�ö���falseȡ���ö�.
         *
         * @return	��.
         * @example
         *
        		 ```
        		 // ʹ�����ö�
        		 var win = BrowserWindow.current;
        		 win.setAlwaysOnTop(true);
        		 console.assert(win.isAlwaysOnTop() == true);
        		 ```
         */
        Any setAlwaysOnTop(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isAlwaysOnTop(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	���� boolean,��ǰ�����Ƿ�ʼ������������֮ǰ.
         *
         * @return	#Boolean.
         *
         * @example
         *
        		 ```
        		 // ʹ�����ö�
        		 var win = BrowserWindow.current;
        		 win.setAlwaysOnTop(true);
        		 console.assert(win.isAlwaysOnTop() == true);
        
        		 // ȡ���ö�
        		 win.setAlwaysOnTop(false);
        		 console.assert(win.isAlwaysOnTop() == false);
        
        		 ```
         */
        Any isAlwaysOnTop(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::center(IPCMessage::SmartType msg);
         *
         * @brief	���ھ���.
         *
         * @return	��.
         * @example
        			 ```
        			 var win = BrowserWindow.current;
        			 win.center();
        			 ```
         */
        virtual Any center(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::setPosition(IPCMessage::SmartType msg);
         *
         * @brief	�ƶ����ڵ���Ӧ�� x and y ����.
         *
         * @param	#Int=0 x����.
         *
         * @param	#Int=0 y����.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        		 var win = BrowserWindow.current;
        		 win.setPosition( 300,200);
        		 ```
         */
        
        virtual Any setPosition(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::getPosition(IPCMessage::SmartType msg);
         *
         * @brief	 ����һ��������ǰ����λ�õĶ���,����������{@link getWindowRect=BrowserWindow.getWindowRect}��ͬ.
         *
         * @return	#JsonObject.
         *
         * @see getWindowRect=BrowserWindow.getWindowRect
         *
         * @example
         *
        		 ```
        		 var win = BrowserWindow.current;
        
        		 win.setPosition( 100,200);
        
        		 // ��ȡ��������
        		 var winInfo = win.getPosition();
        
        		 console.assert(winInfo.x == 100);
        		 console.assert(winInfo.y == 200);
        		 ```
         */
        virtual Any getPosition(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::setTitle(IPCMessage::SmartType msg);
         *
         * @brief	�ı�ԭ���ڵ�title.
         *
         * @param	#String ����������.
         *
         * @return	��.
         *
         * @example
         *
        	 ```
        	 var win = BrowserWindow.current;
        	 win.setTitle("NCUI���Դ���");
        	 ```
         */
        virtual Any setTitle(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::getTitle(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	����ԭ���ڵ�title.
         *
         *
         * @return	#String.
         *
         * @see setTitle=BrowserWindow.setTitle
         *
         * @example
         *
        		 ```
        			var win = BrowserWindow.current;
        			win.setTitle("NCUI���Դ���");
        			console.assert(win.getTitle() == 'NCUI���Դ���');
        		 ```
         */
        virtual Any getTitle(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::flashFrame(IPCMessage::SmartType msg);
         *
         * @brief	��ʼ��ֹͣ��˸����������û��Ĺ�ע.
         *
         * @param	#Boolean=false true��˸���ڣ�falseֹͣ��˸.
         *
         * @return	��.
         *
         * @example
         *
        			 ```
        			 var win = BrowserWindow.current;
        			 win.flashFrame(true);
        			 // ֹͣ
        			 win.flashFrame(false);
        			 ```
         */
        virtual Any flashFrame(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::setHasShadow(IPCMessage::SmartType msg);
         *
         * @brief	�����Ƿ���ʾ������Ӱ
         *
         * @param	#Boolean=false  true��ʾ������Ӱ��false����ʾ������Ӱ.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        			var win = BrowserWindow.current;
        			win.setHasShadow(false);
        		 ```
         */
        virtual Any setHasShadow(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::hasShadow(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	���� boolean,�Ƿ���ʾ������Ӱ
         *
         * @return	#Boolean.
         *
         * @example
         *
        		 ```
        			 var win = BrowserWindow.current;
        			 // ����ʾ��Ӱ
        			 win.setHasShadow(false);
        			 console.assert(win.hasShadow() == false);
        
        			 // ��ʾ��Ӱ
        			 win.setHasShadow(true);
        			 console.assert(win.hasShadow() == true);
        
        		 ```
         */
        Any hasShadow(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::topmost(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ��ö�.
         *
         * @param	#Boolean true�ö�/falseȡ���ö�.
         *
         * @return	��.
         *
         * @see setAlwaysOnTop=BrowserWindow.setAlwaysOnTop isTopmost=BrowserWindow.isTopmost
         *
         * @example
         *
        			 ```
        			 // ʹ�����ö�
        			 var win = BrowserWindow.current;
        			 win.topmost(true);
        			 console.assert(win.isTopmost() == true);
        			 ```
         */
        virtual Any topmost(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::isTopmost(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	�жϴ����Ƿ��ö�.
         *
         *
         * @return	#Boolean.
         *
         * @example
         *
        		 ```
        		 // ʹ�����ö�
        		 var win = BrowserWindow.current;
        		 win.topmost(true);
        		 console.assert(win.isTopmost() == true);
        
        		 // ȡ���ö�
        		 win.topmost(false);
        		 console.assert(win.isTopmost() == false);
        		 ```
         */
        virtual Any isTopmost(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::toggleVisible(IPCMessage::SmartType msg);
         *
         * @brief	��ʾ/���ش���.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        		 var win= BrowserWindow.current;
        		 win.toggleVisible();
        		 console.assert(win.isVisible() == false);
        		 win.toggleVisible();
        		 console.assert(win.isVisible() == true);
        		 ```
         */
        virtual Any toggleVisible(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::toggleFullScreen(IPCMessage::SmartType msg);
         *
         * @brief	ȫ��/��ȫ������.
         *
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        			 var win = BrowserWindow.current;
        			 // ���ô��ڿ���ȫ����ʾ
        			 win.setFullScreenable(true);
        			 // �˳�ȫ��
        			 win.setFullScreen(false);
        
        			 // ȫ��
        			 win.toggleFullScreen();
        			 console.assert(win.isFullScreen() == true);
        
        			 // �˳�ȫ��
        			 win.toggleFullScreen();
        			 console.assert(win.isFullScreen() == false);
        
        		 ```
         */
        virtual Any toggleFullScreen(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::showModal(IPCMessage::SmartType msg);
         *
         * @ignore
         *
         * @brief	��ǰ�ӿڲ�������ʹ�ã����Ҫ��ʾΪģ̬���ڱ����ڴ���ʱָ��.
         *
         *
         * @return	��.
         */
        
        Any showModal(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any NativeWindowProxy::setIcon(IPCMessage::SmartType msg);
         *
         * @brief	���ô���ͼ��.
         *
         * @param	#String ͼ��·��.
         *
         * @return	��.
         *
         * @example
         *
        		 ```
        			var win = BrowserWindow.current;
        			var icon = app.toAbsolutePath('%skinDir%logo1.ico');
        			console.log(icon);
        			win.setIcon(icon);
        		 ```
         */
        
        Any setIcon(IPCMessage::SmartType msg);
        
        
        
        
        /*!
        * @fn	static Any AppTransfer::setConfig(IPCMessage::SmartType msg);
        *
        * @brief	���ô������ò���.�ú�������Ҫ��һ��Ҫ������֧�ֵĲ�����
        * 			�ú�������Ӱ��һ���ִ�����Ϊ����������Щ��Ҫ��ȷ��<br>
        * 			һ�����������Զ������������getConfig�����ȡ�����õ�ֵ��{@link BrowserWindow.getConfig}���Ӧ.
        *
        * @param	#JsonObject ��Ҫ���õĲ�������ֵΪһ��JSON����.
        *
        * @return	��.
        *
        * @see getConfig=BrowserWindow.getConfig
        *
        * @example
        			```
        			var win = BrowserWindow.current;
        			win.setConfig({
        				debugMode: true,
        				custom: 'custom'
        			});
        
        			```
        */
        
        Any setConfig(IPCMessage::SmartType msg);
        
        
        /*!
        * @fn	static Any NativeWindowProxy::getConfig(IPCMessage::SmartType msg);
        *
        * @tag sync
        *
        * @brief	��ȡӦ�ó�����������ò���,�ɻ�ȡ�����ݼ�{@link ��������ڲ���=��������ڲ���}.
        *
        * @return	#JsonObject �������ò���.
        */
        
        
        /*!
        * @fn	static Any NativeWindowProxy::getConfig(IPCMessage::SmartType msg);
        *
        * @tag sync
        *
        * @brief	��ȡ���ڵ�ָ�����ò���.
        *
        * @param	#String ��Ҫ��ȡ���ֶ�����.
        *
        * @return	�����ֶ�������Ӧ�����ò������������������ò������Ͷ�����ΪJS��֧�ֵĻ�����������.
        *
        * @see setConfig=BrowserWindow.setConfig
        *
        * @example
        			```
        
        			//��ȡ��������ڵ��������ò���
        			var win = BrowserWindow.current;
        			var config = win.getConfig();
        			console.log(config);
        
        			//��ȡ��������ڵ�ָ�����ò���
        			var titleBar = win.getConfig('titleBar');
        			console.assert(titleBar == false);
        			```
        */
        
        Any getConfig(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::setOpacity(IPCMessage::SmartType msg);
         *
         * @brief	���ô��ڲ�͸����, �÷������������������ڴ����ϣ�����벿��͸������ôӦ��ʹ��������Ⱦ������ʵ��.
         *
         * @param	#Int=255 ��͸���ȣ�ȡֵ��Χ[0,255],ֵԽ��Խ��͸�� 0��ʾ��ȫ͸����255��ʾ��ȫ��͸��.
         *
         * @return	��.
         *
         * @see getOpacity=BrowserWindow.getOpacity
         *
         * @example
         *
         *
        	 ```
        		include('BrowserWindow');
        		BrowserWindow.current.setOpacity(200);
        	 ```
         *
         */
        
        virtual Any setOpacity(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::getOpacity(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	��ȡ��ǰ���ڵĲ�͸����.
         *
         *
         * @return	#Int ��͸����.
         *
         * @see setOpacity=BrowserWindow.setOpacity
         *
         * @example
         *
         ```
        	 include('BrowserWindow');
        	 BrowserWindow.current.setOpacity(100);
        	 console.assert(BrowserWindow.current.getOpacity() == 100);
        
        	 BrowserWindow.current.setOpacity(255);
        	 console.assert(BrowserWindow.current.getOpacity() == 255);
         ```
         *
         */
        
        virtual Any getOpacity(IPCMessage::SmartType msg);
        
    public:
        /*!
         * @fn	HWND NativeWindowProxy::getNativeHWND(std::shared_ptr<AnyArgsList> args);
         *
         * @ignore
         *
         * @brief	��ȡ����ԭ�����.
         *
         * @param	args	The arguments.
         *
         * @return	The native hwnd.
         */
        HWND getNativeHWND(std::shared_ptr<AnyArgsList> args);
        /*!
         * @fn	virtual HWND NativeWindowProxy::getNativeHWND();
         *
         * @ignore
         *
         * @brief	��ȡ����ԭ�����.
         *
         * @return	The native hwnd.
         */
        virtual HWND getNativeHWND();
        /*!
         * @fn	virtual std::shared_ptr<NativeWindowSettings> NativeWindowProxy::getBrowserSettings();
         *
         * @ignore
         *
         * @brief	��ȡ�������ò���.
         *
         * @return	The browser settings.
         */
        virtual std::shared_ptr<NativeWindowSettings> getNativeSettings();
        
    private:
    };
    
}

#endif // AMO_NATIVEWINDOWPROXY_H__
