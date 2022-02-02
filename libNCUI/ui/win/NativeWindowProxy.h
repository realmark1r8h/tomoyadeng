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
     * @brief	A native window settings.
     */
    class NativeWindowSettings;
    /*!
     * @class	NativeWindowProxy
     *
     * @brief	A native window proxy.
     */
    class NativeWindowProxy {
    public:
    
        virtual Any id(IPCMessage::SmartType msg);
        
        /*!
         * @fn	virtual Any NativeWindowProxy::getName(IPCMessage::SmartType msg);
         *
         * @brief	获取窗口名.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any getName(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setName(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口名.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::destroy(IPCMessage::SmartType msg);
         *
         * @brief	强制关闭窗口, unload and beforeunload 不会触发，并且 close 也不会触发, 但是它保证了 closed 触发.
         *
         * @param	msg	The message to destroy.
         *
         * @return	Any.
         */
        Any destroy(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::close(IPCMessage::SmartType msg);
         *
         * @brief	尝试关闭窗口，这与用户点击关闭按钮的效果一样. 虽然网页可能会取消关闭.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any close(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::focus(IPCMessage::SmartType msg);
         *
         * @brief	窗口获得焦点.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any focus(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isFocused(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean, 窗口是否获得焦点.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isFocused(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::show(IPCMessage::SmartType msg);
         *
         * @brief	展示并且使窗口获得焦点.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any show(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::showInactive(IPCMessage::SmartType msg);
         *
         * @brief	展示窗口但是不获得焦点.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any showInactive(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::hide(IPCMessage::SmartType msg);
         *
         * @brief	隐藏窗口.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any hide(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isVisible(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean, 窗口是否可见.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isVisible(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::maximize(IPCMessage::SmartType msg);
         *
         * @brief	窗口最大化.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any maximize(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::unmaximize(IPCMessage::SmartType msg);
         *
         * @brief	取消窗口最大化.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any unmaximize(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMaximized(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean, 窗口是否最大化.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isMaximized(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::minimize(IPCMessage::SmartType msg);
         *
         * @brief	窗口最小化.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any minimize(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::restore(IPCMessage::SmartType msg);
         *
         * @brief	将窗口恢复为之前的状态,作用与unmaximize相同，与electron不同.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any restore(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMinimized(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean, 窗口是否最小化.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isMinimized(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setFullScreen(IPCMessage::SmartType msg);
         *
         * @brief	设置是否全屏.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setFullScreen(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::isFullScreen(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean, 窗口是否全屏化.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any isFullScreen(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setBounds(IPCMessage::SmartType msg);
         *
         * @brief	重新设置窗口的宽高值，并且移动到指定的 x, y 位置.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setBounds(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::getBounds(IPCMessage::SmartType msg);
         *
         * @brief	返回一个对象，它包含了窗口的宽，高，x坐标，y坐标.
         *
         * @param	msg	The message.
         *
         * @return	The bounds.
         */
        Any getBounds(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setSize(IPCMessage::SmartType msg);
         *
         * @brief	重新设置窗口的宽高值.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setSize(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::getSize(IPCMessage::SmartType msg);
         *
         * @brief	Gets a size.
         *
         * @param	msg	.
         *
         * @return	The size.
         */
        Any getSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setMinimumSize(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口最小化的宽高值.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setMinimumSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::getMinimumSize(IPCMessage::SmartType msg);
         *
         * @brief	返回一个对象，它包含了窗口最小化的宽，高.{width:100, height:200}
         *
         * @param	msg	The message.
         *
         * @return	The minimum size.
         */
        virtual Any getMinimumSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setMaximumSize(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口最大化的宽高值.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setMaximumSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::getMaximumSize(IPCMessage::SmartType msg);
         *
         * @brief	返回一个对象，它包含了窗口最大化的宽，高.{width:100, height:200}
         *
         * @param	msg	The message.
         *
         * @return	The maximum size.
         */
        virtual Any getMaximumSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setResizable(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口是否可以被用户改变size.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setResizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isResizable(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean,窗口是否可以被用户改变size.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isResizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setMovable(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口是否可以被用户拖动. Linux 无效.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setMovable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMovable(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean,窗口是否可以被用户拖动.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isMovable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setMinimizable(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口是否可以最小化.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setMinimizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMinimizable(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean,窗口是否可以最小化.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isMinimizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setMaximizable(IPCMessage::SmartType msg);
         *
         * @brief	设置窗口是否可以最大化.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setMaximizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMaximizable(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean,窗口是否可以最大化.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isMaximizable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setFullScreenable(IPCMessage::SmartType msg);
         *
         * @brief	设置否可以全屏.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setFullScreenable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isFullScreenable(IPCMessage::SmartType msg);
         *
         * @brief	返回 boolean,是否允许全屏.
         *
         * @param	msg	The message.
         *
         * @return	Any.
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
