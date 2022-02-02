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
         * @brief	��ȡ������.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any getName(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setName(IPCMessage::SmartType msg);
         *
         * @brief	���ô�����.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::destroy(IPCMessage::SmartType msg);
         *
         * @brief	ǿ�ƹرմ���, unload and beforeunload ���ᴥ�������� close Ҳ���ᴥ��, ��������֤�� closed ����.
         *
         * @param	msg	The message to destroy.
         *
         * @return	Any.
         */
        Any destroy(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::close(IPCMessage::SmartType msg);
         *
         * @brief	���Թرմ��ڣ������û�����رհ�ť��Ч��һ��. ��Ȼ��ҳ���ܻ�ȡ���ر�.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any close(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::focus(IPCMessage::SmartType msg);
         *
         * @brief	���ڻ�ý���.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any focus(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isFocused(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean, �����Ƿ��ý���.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isFocused(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::show(IPCMessage::SmartType msg);
         *
         * @brief	չʾ����ʹ���ڻ�ý���.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any show(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::showInactive(IPCMessage::SmartType msg);
         *
         * @brief	չʾ���ڵ��ǲ���ý���.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any showInactive(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::hide(IPCMessage::SmartType msg);
         *
         * @brief	���ش���.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any hide(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isVisible(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean, �����Ƿ�ɼ�.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isVisible(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::maximize(IPCMessage::SmartType msg);
         *
         * @brief	�������.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any maximize(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::unmaximize(IPCMessage::SmartType msg);
         *
         * @brief	ȡ���������.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any unmaximize(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMaximized(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean, �����Ƿ����.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isMaximized(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::minimize(IPCMessage::SmartType msg);
         *
         * @brief	������С��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any minimize(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::restore(IPCMessage::SmartType msg);
         *
         * @brief	�����ڻָ�Ϊ֮ǰ��״̬,������unmaximize��ͬ����electron��ͬ.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any restore(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMinimized(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean, �����Ƿ���С��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isMinimized(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setFullScreen(IPCMessage::SmartType msg);
         *
         * @brief	�����Ƿ�ȫ��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setFullScreen(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::isFullScreen(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean, �����Ƿ�ȫ����.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any isFullScreen(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setBounds(IPCMessage::SmartType msg);
         *
         * @brief	�������ô��ڵĿ��ֵ�������ƶ���ָ���� x, y λ��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setBounds(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::getBounds(IPCMessage::SmartType msg);
         *
         * @brief	����һ�������������˴��ڵĿ��ߣ�x���꣬y����.
         *
         * @param	msg	The message.
         *
         * @return	The bounds.
         */
        Any getBounds(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setSize(IPCMessage::SmartType msg);
         *
         * @brief	�������ô��ڵĿ��ֵ.
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
         * @brief	���ô�����С���Ŀ��ֵ.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setMinimumSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::getMinimumSize(IPCMessage::SmartType msg);
         *
         * @brief	����һ�������������˴�����С���Ŀ���.{width:100, height:200}
         *
         * @param	msg	The message.
         *
         * @return	The minimum size.
         */
        virtual Any getMinimumSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setMaximumSize(IPCMessage::SmartType msg);
         *
         * @brief	���ô�����󻯵Ŀ��ֵ.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setMaximumSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::getMaximumSize(IPCMessage::SmartType msg);
         *
         * @brief	����һ�������������˴�����󻯵Ŀ���.{width:100, height:200}
         *
         * @param	msg	The message.
         *
         * @return	The maximum size.
         */
        virtual Any getMaximumSize(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setResizable(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ���Ա��û��ı�size.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setResizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isResizable(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean,�����Ƿ���Ա��û��ı�size.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isResizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setMovable(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ���Ա��û��϶�. Linux ��Ч.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setMovable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMovable(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean,�����Ƿ���Ա��û��϶�.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isMovable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setMinimizable(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ������С��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setMinimizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMinimizable(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean,�����Ƿ������С��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isMinimizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setMaximizable(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ�������.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setMaximizable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isMaximizable(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean,�����Ƿ�������.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isMaximizable(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any NativeWindowProxy::setFullScreenable(IPCMessage::SmartType msg);
         *
         * @brief	���÷����ȫ��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setFullScreenable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isFullScreenable(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean,�Ƿ�����ȫ��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isFullScreenable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setClosable(IPCMessage::SmartType msg);
         *
         * @brief	���ô����Ƿ������Ϊ�ر�.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setClosable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isClosable(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean,�����Ƿ������Ϊ�ر�.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isClosable(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::setAlwaysOnTop(IPCMessage::SmartType msg);
         *
         * @brief	�Ƿ������������ʼ������������֮��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any setAlwaysOnTop(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::isAlwaysOnTop(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean,��ǰ�����Ƿ�ʼ������������֮ǰ.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        Any isAlwaysOnTop(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::center(IPCMessage::SmartType msg);
         *
         * @brief	���ھ���.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any center(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setPosition(IPCMessage::SmartType msg);
         *
         * @brief	�ƶ����ڵ���Ӧ�� x and y ����.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setPosition(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::getPosition(IPCMessage::SmartType msg);
         *
         * @brief	 ����һ��������ǰ����λ�õĶ���.
         *
         * @param	msg	The message.
         *
         * @return	The position.
         */
        virtual Any getPosition(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setTitle(IPCMessage::SmartType msg);
         *
         * @brief	�ı�ԭ���ڵ�title.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setTitle(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::getTitle(IPCMessage::SmartType msg);
         *
         * @brief	����ԭ���ڵ�title.
         *
         * @param	msg	The message.
         *
         * @return	The title.
         */
        virtual Any getTitle(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::flashFrame(IPCMessage::SmartType msg);
         *
         * @brief	��ʼ��ֹͣ��ʾ����������û��Ĺ�ע.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any flashFrame(IPCMessage::SmartType msg);
        /*!
         * @fn	virtual Any NativeWindowProxy::setHasShadow(IPCMessage::SmartType msg);
         *
         * @brief	�����Ƿ���ʾ������Ӱ
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        virtual Any setHasShadow(IPCMessage::SmartType msg);
        /*!
         * @fn	Any NativeWindowProxy::hasShadow(IPCMessage::SmartType msg);
         *
         * @brief	���� boolean,�Ƿ���ʾ������Ӱ
         *
         * @param	msg	The message.
         *
         * @return	Any.
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
