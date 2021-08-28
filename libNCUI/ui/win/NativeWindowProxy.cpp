#include "stdafx.h"
#include "ui/win/NativeWindowProxy.h"
#include <amo/string.hpp>

#include "settings/NativeWindowSettings.h"


namespace amo {

    Any NativeWindowProxy::id(IPCMessage::SmartType msg) {
        return getNativeSettings()->id;
        return 0;
    }
    
    Any NativeWindowProxy::getName(IPCMessage::SmartType msg) {
        return getNativeSettings()->name;
    }
    
    Any NativeWindowProxy::setName(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        getNativeSettings()->name = args->getString(0);
        return Undefined();
    }
    
    Any NativeWindowProxy::destroy(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        // 255 ǿ�ƹرմ���
        ::PostMessage(getNativeHWND(args), WM_CLOSE, 255, 0);
        return Undefined();
    }
    
    
    Any NativeWindowProxy::close(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        ::PostMessage(getNativeHWND(args), WM_CLOSE, 0, 0);
        return Undefined();
    }
    
    Any NativeWindowProxy::focus(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        ::SetFocus(getNativeHWND(args));
        return Undefined();
    }
    
    
    Any NativeWindowProxy::isFocused(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        HWND hWnd = getNativeHWND(args);
        HWND hFocusWnd = ::GetFocus();
        
        while (hFocusWnd != NULL) {
            if (hWnd == hFocusWnd) {
                return true;
            }
            
            hFocusWnd = ::GetParent(hFocusWnd);
        }
        
        return false;
        //return ::GetFocus() == getNativeHWND(args);
    }
    
    Any NativeWindowProxy::show(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        bool bOk = (::ShowWindow(getNativeHWND(args), SW_SHOW) != FALSE);
        ::SetFocus(getNativeHWND(args));
        ::SwitchToThisWindow(getNativeHWND(args), TRUE);
        return bOk;
    }
    
    Any NativeWindowProxy::showInactive(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        return ::ShowWindow(getNativeHWND(args), SW_SHOWNOACTIVATE) != FALSE;
    }
    
    Any NativeWindowProxy::hide(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        return ::ShowWindow(getNativeHWND(args), SW_HIDE) != FALSE;
    }
    
    Any NativeWindowProxy::isVisible(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        return ::IsWindowVisible(getNativeHWND(args)) != FALSE;
    }
    
    Any NativeWindowProxy::maximize(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        ::PostMessage(getNativeHWND(args), WM_SYSCOMMAND, SC_MAXIMIZE, 0);
        return Undefined();
    }
    
    Any NativeWindowProxy::unmaximize(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        
        if (isMaximized(msg)) {
            ::PostMessage(getNativeHWND(args), WM_SYSCOMMAND, SC_RESTORE, 0);
        }
        
        return Undefined();
    }
    
    Any NativeWindowProxy::isMaximized(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        return ::IsZoomed(getNativeHWND(args)) != FALSE;
    }
    
    Any NativeWindowProxy::minimize(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        ::PostMessage(getNativeHWND(args), WM_SYSCOMMAND, SC_MINIMIZE, 0);
        return Undefined();
    }
    
    Any NativeWindowProxy::restore(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        ::PostMessage(getNativeHWND(args), WM_SYSCOMMAND, SC_RESTORE, 0);
        return Undefined();
    }
    
    Any NativeWindowProxy::isMinimized(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        return ::IsIconic(getNativeHWND(args)) != FALSE;
    }
    
    Any NativeWindowProxy::setFullScreen(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::isFullScreen(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::setBounds(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        amo::json json(args->getString(0));
        int x = json.getInt("x");
        int y = json.getInt("y");
        int width = json.getInt("width");
        int height = json.getInt("height");
        ::MoveWindow(getNativeHWND(args), x, y, width, height, TRUE);
        return Undefined();
    }
    
    Any NativeWindowProxy::getBounds(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        RECT rect = { 0 };
        ::GetWindowRect(getNativeHWND(args), &rect);
        amo::json json;
        json.put("x", rect.left);
        json.put("y", rect.top);
        json.put("width", rect.right - rect.left);
        json.put("height", rect.bottom - rect.top);
        return json;
    }
    
    Any NativeWindowProxy::setSize(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        RECT rect = { 0 };
        ::GetWindowRect(getNativeHWND(args), &rect);
        
        int x = rect.left;
        int y = rect.top;
        int width = args->getInt(0);
        int height = args->getInt(1);
        ::MoveWindow(getNativeHWND(args), x, y, width, height, TRUE);
        return Undefined();
    }
    
    Any NativeWindowProxy::getSize(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        RECT rect = { 0 };
        ::GetWindowRect(getNativeHWND(args), &rect);
        amo::json json;
        json.put("width", rect.right - rect.left);
        json.put("height", rect.bottom - rect.top);
        return json;
    }
    
    
    Any NativeWindowProxy::setMinimumSize(IPCMessage::SmartType msg) {
    
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::getMinimumSize(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::setMaximumSize(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::getMaximumSize(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::setResizable(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::isResizable(IPCMessage::SmartType msg) {
        return  getNativeSettings()->resizeable;
    }
    
    Any NativeWindowProxy::setMovable(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        bool moveable = args->getBool(0);
        getNativeSettings()->moveable = moveable;
        return Undefined();
    }
    
    Any NativeWindowProxy::isMovable(IPCMessage::SmartType msg) {
        return  getNativeSettings()->moveable;
    }
    
    Any NativeWindowProxy::setMinimizable(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        bool minimizable = args->getBool(0);
        getNativeSettings()->minimizable = minimizable;
        return Undefined();
    }
    
    Any NativeWindowProxy::isMinimizable(IPCMessage::SmartType msg) {
        return getNativeSettings()->minimizable;
    }
    
    Any NativeWindowProxy::setMaximizable(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        bool maximizable = args->getBool(0);
        getNativeSettings()->maximizable = maximizable;
        return Undefined();
    }
    
    Any NativeWindowProxy::isMaximizable(IPCMessage::SmartType msg) {
        return getNativeSettings()->maximizable;
    }
    
    Any NativeWindowProxy::setFullScreenable(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        bool fullscreenable = args->getBool(0);
        getNativeSettings()->fullscreenable = fullscreenable;
        return Undefined();
    }
    
    Any NativeWindowProxy::isFullScreenable(IPCMessage::SmartType msg) {
        return getNativeSettings()->fullscreenable;
    }
    
    Any NativeWindowProxy::setClosable(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        bool closable = args->getBool(0);
        getNativeSettings()->closable = closable;
        return Undefined();
    }
    
    Any NativeWindowProxy::isClosable(IPCMessage::SmartType msg) {
        return  getNativeSettings()->closable;
    }
    
    Any NativeWindowProxy::setAlwaysOnTop(IPCMessage::SmartType msg) {
        return topmost(msg);
    }
    
    Any NativeWindowProxy::isAlwaysOnTop(IPCMessage::SmartType msg) {
        return isTopmost(msg);
    }
    
    Any NativeWindowProxy::center(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::setPosition(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        int x = args->getInt(0);
        int y = args->getInt(1);
        RECT rect = { 0 };
        ::GetWindowRect(getNativeHWND(args), &rect);
        ::MoveWindow(getNativeHWND(args),
                     x,
                     y,
                     rect.right - rect.left,
                     rect.bottom - rect.top,
                     TRUE);
        return Undefined();
    }
    
    Any NativeWindowProxy::getPosition(IPCMessage::SmartType msg) {
        return getBounds(msg);
    }
    
    Any NativeWindowProxy::setTitle(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        amo::string str(args->getString(0), true);
        BOOL bOk = ::SetWindowTextA(getNativeHWND(args), str.c_str());
        return bOk != FALSE;
    }
    
    Any NativeWindowProxy::getTitle(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        char str[256] = { 0 };
        ::GetWindowTextA(getNativeHWND(args), str, 256);
        return amo::string(str).to_utf8();
    }
    
    Any NativeWindowProxy::flashFrame(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        bool bFlahFrame = args->getBool(0);
        
        if (bFlahFrame) {
            FLASHWINFO fw;
            fw.cbSize = sizeof(FLASHWINFO);
            fw.hwnd = getNativeHWND(args);
            fw.dwFlags = FLASHW_ALL | FLASHW_TIMER;
            fw.uCount = 5;
            fw.dwTimeout = 500;
            FlashWindowEx(&fw);
        } else {
            FLASHWINFO fw;
            fw.cbSize = sizeof(FLASHWINFO);
            fw.hwnd = getNativeHWND(args);
            fw.dwFlags = FLASHW_STOP;
            FlashWindowEx(&fw);
        }
        
        return Undefined();
    }
    
    
    Any NativeWindowProxy::setHasShadow(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::hasShadow(IPCMessage::SmartType msg) {
        return getNativeSettings()->hasShadow;
    }
    
    Any NativeWindowProxy::topmost(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::isTopmost(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    
    Any NativeWindowProxy::toggleVisible(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::toggleFullScreen(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    
    
    Any NativeWindowProxy::showModal(IPCMessage::SmartType msg) {
        // ��LocalWindow������
        return Undefined();
    }
    
    Any NativeWindowProxy::setIcon(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        amo::string strPath(args->getString(0), true);
        HICON m_hIcon = (HICON)LoadImage(NULL,
                                         strPath.to_unicode().c_str(),
                                         IMAGE_ICON,
                                         0,
                                         0,
                                         LR_LOADFROMFILE);
        ::SendMessage(getNativeHWND(args),
                      WM_SETICON,
                      (WPARAM)false,
                      (LPARAM)m_hIcon);
        return Undefined();
    }
    
    HWND NativeWindowProxy::getNativeHWND(std::shared_ptr<AnyArgsList> args) {
        return getNativeHWND();
    }
    
    
    
    HWND NativeWindowProxy::getNativeHWND() {
        return NULL;
    }
    
    std::shared_ptr<NativeWindowSettings> NativeWindowProxy::getNativeSettings() {
        // ��LocalWindow������
        return  std::shared_ptr<NativeWindowSettings>();
    }
    
    
}

