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
        * @fn	Any NativeWindowProxy::close(IPCMessage::SmartType msg);
        *
        * @brief	���Թرմ��ڣ����Ա��û�ȡ���磺window.onload.<br>
        * 			��{@link isClosable=BrowserWindow.isClosable}Ϊtrue,�ú�����Ч.
        *
        *
        * @return	��.
        *
        * @see destroy=NativeWindowProxy.destroy
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
         * @see close=NativeWindowProxy.close
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
         *			//
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
         * 			win.showInactive();
         * 			console.assert(win.isVisible() == true);
         * 			win.show();
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
         * @see unmaximize=BrowserWindow.unmaximize restore=BrowserWindow.restore
         *		 isMaximized=BrowserWindow.isMaximized
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
         * @brief	ȡ���������.
         *
         *
         * @return	��.
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
         * @tag sync
         *
         * @brief  �жϴ����Ƿ���С��.
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
         * @fn	Any NativeWindowProxy::setBounds(IPCMessage::SmartType msg);
         *
         * @brief	�������ô��ڵĿ��ֵ�������ƶ���ָ���� x, y λ��,<br>
         * 			�����ڴ���ȫ���������״̬ʱ���ú�����Ч.<br>
         * 			���������С�����ƿ��ʱ������С���Ϊ׼<br>
         * 			��������ߴ������ƿ��ʱ���������Ϊ׼
         *
         * @param	#JsonObject.
         *
         * @return	��.
         *
         * @example
        			 ```
        				var win = BrowserWindow.current;
        
        				win.setBounds({
        					x: 100,
        					y: 100,
        					width: 1000,
        					height: 500,
        				});
        
        			 ```
         */
        Any setBounds(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::getBounds(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	����һ�������������˴��ڵĿ��ߣ�x���꣬y����.
         *
         *
         * @return	#JsonObject ���ڵ��������.
         * @example
        		```
        		var win = BrowserWindow.current;
        
        		win.setBounds({
        			x: 100,
        			y: 100,
        			width: 1000,
        			height: 500,
        		});
        
        		// ��ȡ��������
        		var winInfo = win.getBounds();
        		console.assert(winInfo.x == 100);
        		console.assert(winInfo.y == 100);
        		console.assert(winInfo.width == 1000);
        		console.assert(winInfo.height == 500);
        		```
         */
        Any getBounds(IPCMessage::SmartType msg);
        
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
         * @example
         * 		   ```
        				var win = BrowserWindow.current;
        				// ���ô��ڿ��
        				win.setSize(500,500);
        				// ��ȡ���ڿ��
        				var info = win.getSize();
        				console.log(info);
        				console.assert(info.width == 500);
        				console.assert(info.height == 500);
        
         * 		   ```
         */
        Any getSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setMinimumSize(IPCMessage::SmartType msg);
         *
         * @brief	���ô�����С���Ŀ��ֵ.
         *
         * @param	#Int	��С���.
         * @param	#Int	��С�߶�
         *
         * @return	��.
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
         * 		   ```
         *
         */
        virtual Any getMinimumSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setMaximumSize(IPCMessage::SmartType msg);
         *
         * @brief	���ô�����󻯵Ŀ��ֵ.
         *
          * @param	#Int	�����.
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
         * @tag sync
         * @brief	����һ�������������˴�����󻯵Ŀ���.{width:100, height:200}
         *
         * @param	msg	The message.
         *
         * @return	#JsonObject ���ڵ��������Ϣ.
         * @example
         * 		   ```
        				var win = BrowserWindow.current;
        				win.setMaximumSize(1280,720);
        
        				// ��ȡ�����
        				var info = win.getMaximumSize();
        				console.assert(info.width == 1280);
        				console.assert(info.height == 720);
         * 		   ```
         */
        virtual Any getMaximumSize(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::setResizable(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ���Ա��û��ı䴰�ڴ�С.
         *
         * @param	#Boolean=false true���� false������ .
         *
         * @return	��.
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
         * @brief	���ô����Ƿ�������.
         *
         * @param	#Boolean true/false.
         *
         * @return	��.
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
        Any setMaximizable(IPCMessage::SmartType msg);
        
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
        		 win.setAlwaysOnTop(true);
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
         * @brief	 ����һ��������ǰ����λ�õĶ���,����������{@link getBounds=BrowserWindow.getBounds}��ͬ.
         *
         * @return	#JsonObject.
         *
         * @see getBounds=BrowserWindow.getBounds
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
         * @example
         *
        		 ```
        			var win = BrowserWindow.current;
        			win.sethasShadow(false);
        		 ```
         */
        virtual Any setHasShadow(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::hasShadow(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean,�Ƿ���ʾ������Ӱ
         *
         * @return	#Boolean.
         * @example
         *
        		 ```
        			 var win = BrowserWindow.current;
        			 // ����ʾ��Ӱ
        			 win.sethasShadow(false);
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
         * @brief	���ô����ö�.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any topmost(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::isTopmost(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean, �����Ƿ��ö�.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any isTopmost(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::toggleVisible(IPCMessage::SmartType msg);
         *
         * @brief	��ʾ/���ش���.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any toggleVisible(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::toggleFullScreen(IPCMessage::SmartType msg);
         *
         * @brief	ȫ��/��ȫ������.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any toggleFullScreen(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::showModal(IPCMessage::SmartType msg);
         *
         * @brief	��ʾģ̬����.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any showModal(IPCMessage::SmartType msg);
        
        Any setIcon(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any NativeWindowProxy::config(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ���ڵ�������Ϣ.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any getConfigs(IPCMessage::SmartType msg);
        
        Any setConfig(IPCMessage::SmartType msg);
        
        Any getConfig(IPCMessage::SmartType msg);
    public:
        /*!
         * @fn	HWND NativeWindowProxy::getNativeHWND(std::shared_ptr<AnyArgsList> args);
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
         * @brief	��ȡ����ԭ�����.
         *
         * @return	The native hwnd.
         */
        virtual HWND getNativeHWND();
        /*!
         * @fn	virtual std::shared_ptr<NativeWindowSettings> NativeWindowProxy::getBrowserSettings();
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
