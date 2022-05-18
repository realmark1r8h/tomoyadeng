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
         * @brief	获取窗口名.
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
         * @brief	设置窗口名,这个函数暂时还没有什么用，只是把名称保留下来了.
         *
         * @param	#String 名称.
         *
         * @return	无.
         * @example
         * 		   ```
        			var win = BrowserWindow.current;
        			win.setName('NCUI测试窗口');
        			console.assert(win.getName() == 'NCUI测试窗口');
         * 		   ```
         */
        virtual Any setName(IPCMessage::SmartType msg);
        
        
        /*!
        * @fn	Any NativeWindowProxy::close(IPCMessage::SmartType msg);
        *
        * @brief	尝试关闭窗口，可以被用户取消如：window.onload.<br>
        * 			当{@link isClosable=BrowserWindow.isClosable}为true,该函数无效.
        *
        *
        * @return	无.
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
         * @brief	强制关闭窗口,用户不能取消该操作, 但是它保证了 closed 触发.<br>
         * 			当{@link isClosable=BrowserWindow.isClosable}为true,该函数无效.
         *
         * @return	无.
         *
         * @see close=NativeWindowProxy.close
         *
         * @example
         * 		   ```
        				// 窗口将被强制关闭，用户不能取消该操作
        				var win = BrowserWindow.current;
        				win.destroy();
         * 		   ```
         */
        Any destroy(IPCMessage::SmartType msg);
        
        
        
        /*!
         * @fn	Any NativeWindowProxy::focus(IPCMessage::SmartType msg);
         *
         * @brief	窗口获得焦点.
         *
         * @return	无.
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
         * @brief	判断窗口是否获得焦点.
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
         * @brief	显示并且使窗口获得焦点.
         *
         * @return	无.
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
         * @brief	显示窗口但是不获得焦点.但如果窗口本身就已经获得焦点，调用该函数后窗口依然有焦点
         *
         * @return	无.
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
         * @brief	隐藏窗口.
         *
         * @return	无.
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
         * @brief	判断窗口是否可见.
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
         * @brief	窗口最大化.
         *
         * @return	无.
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
         * @brief	取消窗口最大化.
         *
         *
         * @return	无.
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
         * @brief	判断窗口是否最大化.
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
         * @brief	窗口最小化.
         *
         * @return	无.
         */
        Any minimize(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::restore(IPCMessage::SmartType msg);
         *
         * @brief	将窗口恢复为之前的状态,不管窗口之前是最小化还是最大化.
         *
         * @return	无.
         */
        Any restore(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isMinimized(IPCMessage::SmartType msg);
         * @tag sync
         * @brief  判断窗口是否最小化.
         *
         *
         * @return	#Boolean.
         */
        Any isMinimized(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setFullScreen(IPCMessage::SmartType msg);
         *
         * @brief	设置是否全屏.
         *
         * @param	#Boolean=false 全屏/非全屏.
         *
         * @return	Any.
         */
        virtual Any setFullScreen(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::isFullScreen(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	判断窗口是否处于全屏状态.
         *
         *
         * @return	#Boolean.
         */
        virtual Any isFullScreen(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setBounds(IPCMessage::SmartType msg);
         *
         * @brief	重新设置窗口的宽高值，并且移动到指定的 x, y 位置.
         *
         * @param	#JsonObject.
         *
         * @return	无.
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
         * @brief	返回一个对象，它包含了窗口的宽，高，x坐标，y坐标.
         *
         *
         * @return	#JsonObject 窗口的坐标参数.
         * @example
        		```
        		var win = BrowserWindow.current;
        
        		win.setBounds({
        			x: 100,
        			y: 100,
        			width: 1000,
        			height: 500,
        		});
        
        		// 获取窗体坐标
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
         * @brief	重新设置窗口的宽高值,窗口的X坐标和Y坐标保持不变
         *
         * @param	#Int=0 宽.
         *
         * @param	#Int=0 高
         *
         * @return	无.
         */
        Any setSize(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::getSize(IPCMessage::SmartType msg);
         *
         * @brief	获取窗口宽高.
         *
         *
         * @return	#JsonObject 窗口的宽高数据.
         * @example
         * 		   ```
        				var win = BrowserWindow.current;
        				// 设置窗口宽高
        				win.setSize(500,500);
        				// 获取窗口宽高
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
         * @brief	设置窗口最小化的宽高值.
         *
         * @param	#Int	最小宽度.
         * @param	#Int	最小高度
         *
         * @return	无.
         * @example
          		   ```
        				// 设置最小宽高
        				var win = BrowserWindow.current;
        				win.setMinimumSize(1280,720);
          		   ```
         */
        virtual Any setMinimumSize(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::getMinimumSize(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	返回一个对象，它包含了窗口最小化的宽，高.{width:100, height:200}
         *
         *
         * @return	#JsonObject 窗口的最小宽高信息.
         * @example
         * 		   ```
        				var win = BrowserWindow.current;
        				win.setMinimumSize(1280,720);
        
        				// 获取最小宽高
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
         * @brief	设置窗口最大化的宽高值.
         *
          * @param	#Int	最大宽度.
         * @param	#Int	最大高度
         *
         * @return	无.
         * @example
        		   ```
        				// 设置最小宽高
        				var win = BrowserWindow.current;
        				win.setMaximumSize(1280,720);
        		   ```
         */
        
        virtual Any setMaximumSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::getMaximumSize(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	返回一个对象，它包含了窗口最大化的宽，高.{width:100, height:200}
         *
         * @param	msg	The message.
         *
         * @return	#JsonObject 窗口的最大宽高信息.
         * @example
         * 		   ```
        				var win = BrowserWindow.current;
        				win.setMaximumSize(1280,720);
        
        				// 获取最大宽高
        				var info = win.getMaximumSize();
        				console.assert(info.width == 1280);
        				console.assert(info.height == 720);
         * 		   ```
         */
        virtual Any getMaximumSize(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::setResizable(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口是否可以被用户改变窗口大小.
         *
         * @param	#Boolean=false true允许 false不允许 .
         *
         * @return	无.
         *
         */
        virtual Any setResizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isResizable(IPCMessage::SmartType msg);
         * @tag sync
         *
         * @brief	判断窗口是否可以被用户改变大小.
         *
         *
         * @return	#Boolean.
         */
        Any isResizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setMovable(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口是否可以被用户拖动.
         *
         * @param	#Boolean=false true可以移动，false不能移动窗口位置.
         *
         * @return	无.
         */
        Any setMovable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMovable(IPCMessage::SmartType msg);
         *
         * @brief	判断窗口是否可以被用户拖动.
         *
         *
         * @return	#Boolean.
         */
        Any isMovable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setMinimizable(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口是否可以最小化.
         *
         * @param	#Boolean true/false.
         *
         * @return	无.
         */
        Any setMinimizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMinimizable(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	判断窗口是否可以最小化.
         *
         *
         * @return	#Boolean.
         */
        Any isMinimizable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setMaximizable(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口是否可以最大化.
         *
         * @param	#Boolean true/false.
         *
         * @return	无.
         */
        Any setMaximizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMaximizable(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	判断窗口是否可以最大化.
         *
         *
         * @return	#Boolean.
         */
        Any isMaximizable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setFullScreenable(IPCMessage::SmartType msg);
         *
         * @brief	设置否可以全屏.
         *
         * @param	#Boolean=false true/false.
         *
         * @return	无.
         */
        
        Any setFullScreenable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isFullScreenable(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	判断是否允许全屏.
         *
         * @return	#Boolean.
         */
        Any isFullScreenable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setClosable(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口是否可以人为关闭.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setClosable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::isClosable(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean,窗口是否可以人为关闭.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isClosable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setAlwaysOnTop(IPCMessage::SmartType msg);
         *
         * @brief	是否设置这个窗口始终在其他窗口之上.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setAlwaysOnTop(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isAlwaysOnTop(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean,当前窗口是否始终在其它窗口之前.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isAlwaysOnTop(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::center(IPCMessage::SmartType msg);
         *
         * @brief	窗口居中.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any center(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setPosition(IPCMessage::SmartType msg);
         *
         * @brief	移动窗口到对应的 x and y 坐标.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setPosition(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::getPosition(IPCMessage::SmartType msg);
         *
         * @brief	 返回一个包含当前窗口位置的对象.
         *
         * @param	msg	The message.
         *
         * @return	The position.
         */
        virtual Any getPosition(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setTitle(IPCMessage::SmartType msg);
         *
         * @brief	改变原窗口的title.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setTitle(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::getTitle(IPCMessage::SmartType msg);
         *
         * @brief	返回原窗口的title.
         *
         * @param	msg	The message.
         *
         * @return	The title.
         */
        virtual Any getTitle(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::flashFrame(IPCMessage::SmartType msg);
         *
         * @brief	开始或停止显示窗口来获得用户的关注.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any flashFrame(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setHasShadow(IPCMessage::SmartType msg);
         *
         * @brief	设置是否显示窗口阴影
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setHasShadow(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::hasShadow(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean,是否显示窗口阴影
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any hasShadow(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::topmost(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口置顶.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any topmost(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::isTopmost(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean, 窗口是否置顶.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any isTopmost(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::toggleVisible(IPCMessage::SmartType msg);
         *
         * @brief	显示/隐藏窗口.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any toggleVisible(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::toggleFullScreen(IPCMessage::SmartType msg);
         *
         * @brief	全屏/非全屏窗口.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any toggleFullScreen(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::showModal(IPCMessage::SmartType msg);
         *
         * @brief	显示模态窗口.
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
         * @brief	获取窗口的配置信息.
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
         * @brief	获取窗口原生句柄.
         *
         * @param	args	The arguments.
         *
         * @return	The native hwnd.
         */
        HWND getNativeHWND(std::shared_ptr<AnyArgsList> args);
        /*!
         * @fn	virtual HWND NativeWindowProxy::getNativeHWND();
         *
         * @brief	获取窗口原生句柄.
         *
         * @return	The native hwnd.
         */
        virtual HWND getNativeHWND();
        /*!
         * @fn	virtual std::shared_ptr<NativeWindowSettings> NativeWindowProxy::getBrowserSettings();
         *
         * @brief	获取窗口配置参数.
         *
         * @return	The browser settings.
         */
        virtual std::shared_ptr<NativeWindowSettings> getNativeSettings();
        
    private:
    };
    
}

#endif // AMO_NATIVEWINDOWPROXY_H__
