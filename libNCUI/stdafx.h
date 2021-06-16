// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件:
#include <windows.h>


#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// Windows 头文件:
#include <windows.h>
#include <objbase.h>
#include <Commdlg.h>
#include <MmSystem.h>
#include <commctrl.h>

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "Comctl32.lib")

#include <list>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <string>
#include <tchar.h>
#include <unordered_map>
#include <cstdint>

#include <UIlib.h>
#ifdef _DEBUG
#pragma comment(lib, "libcef_dll_wrapper.lib")
#pragma comment(lib, "libcef.lib")
//#pragma comment(lib, "libuvUD32.lib")
#else
#pragma comment(lib, "libcef_dll_wrapper.lib")
#pragma comment(lib, "libcef.lib")
//#pragma comment(lib, "libuvUR32.lib")
#endif
using namespace DuiLib;

#ifdef GetNextSibling
#undef GetNextSibling
#endif

#ifdef GetFirstChild
#undef GetFirstChild
#endif


#include <amo/json.hpp>
#include <amo/loader.hpp>
#include <amo/path.hpp>
#include <amo/string.hpp>
#include <amo/logger.hpp>

// template
#include "ipc/Any.hpp"
#include "ipc/MessageLauncher.hpp"
#include "ipc/ProcessExchanger.hpp"
#include "ipc/IPCMessage.hpp"


#include "handler/BrowserManager.hpp"
#include "handler/HandlerDelegate.hpp"
#include "ipc/AsyncFunctionManager.hpp"

#include "module/basic/ClassMethodMgr.hpp"
#include "module/basic/EventFunctionManager.h"
#include "module/basic/V8HandlerManager.h"

#include "ipc/AsyncFunctionManager.hpp"
#include "ipc/RenderMessageEmitter.hpp"
#include "module/basic/TypeConvertor.h"
#include "module/dll/DllManager.h"
#include "module/dll/DllRunner.h"
#include "module/dll/DllValueAccessor.h"
#include "module/dll/DllValueHandler.h"
#include "module/dll/TypeMapManager.h"


#include "module/JSV8Handler.h"
#include "module/JsClassV8Handler.h"
#include "module/JsClassObjectV8Handler.h"
#include "module/DragWindowV8Handler.h"
#include "module/IPCRendererV8Handler.h"
#include "module/EventEmitterV8Handler.h"

#include "transfer/ClassTransfer.hpp"
#include "ui/win/menu/ObserverImplBase.hpp"
#include "ipc/UIMessageBroadcaster.hpp"


#include "transfer/Transfer.hpp"
#include "transfer/ClassTransfer.hpp"
#include "transfer/TransferMapping.hpp"
#include "transfer/TransferMappingMgr.hpp"
#include "transfer/TransferMgr.h"


#include "handler/BrowserManager.hpp"
#include "handler/BrowserProcessHandler.h"
#include "handler/CefProcessExchanger.hpp"
#include "handler/ClientApp.h"
#include "handler/ClientHandler.h"

#include "handler/ContextMenuHandler.h"
#include "handler/DialogHandler.h"
#include "handler/DisplayHandler.h"
#include "handler/DownloadHandler.h"
#include "handler/DragHandler.h"
#include "handler/FocusHandler.h"
#include "handler/GeolocationHandler.h"
#include "handler/JSDialogHandler.h"
#include "handler/KeyboardHandler.h"
#include "handler/LifeSpanHandler.h"
#include "handler/LoadHandler.h"
#include "handler/RenderHandler.h"
#include "handler/RequestHandler.h"
#include "handler/MessageRouterBrowserSide.h"
#include "handler/V8ExtentionHandler.h"

#include "handler/LocalSchemeHandler.h"
#include "handler/NativeFileHandler.h"

#include "handler/URLRequestClient.h"

#include "node/NodeContextMenuHandler.h"
#include "node/NodeDialogHandler.h"
#include "node/NodeDisplayHandler.h"
#include "node/NodeDownloadHandler.h"
#include "node/NodeDragHandler.h"
#include "node/NodeFocusHandler.h"
#include "node/NodeGeolocationHandler.h"
#include "node/NodeJSDialogHandler.h"
#include "node/NodeKeyboardHandler.h"
#include "node/NodeLifeSpanHandler.h"
#include "node/NodeLoadHandler.h"
#include "node/NodeRenderHandler.h"
#include "node/NodeRequestHandler.h"

#include "node/CefCallbackHandler.h"



#include "context/AppContext.h"

#include "settings/NativeWindowSettings.h"
#include "settings/MenuWindowSettings.h"
#include "settings/BrowserWindowSettings.h"
#include "settings/AppSettings.h"


#include "ui/win/WebkitView.h"
#include "ui/win/BrowserWindow.h"
#include "ui/win/NativeWindow.h"
#include "ui/win/OffScreenRenderView.h"
#include "ui/win/ViewRenderer.h"
#include "ui/win/RenderView.h"
#include "ui/win/LayeredWindow.h"
#include "ui/win/OffscreenDragdrop.h"
#include "ui/win/BrowserWindowManager.h"
#include "ui/win/ShadowWindow.h"
#include "ui/win/NativeWindowProxy.h"
#include "ui/win/Imm32Manager.h"


// TODO:  在此处引用程序需要的其他头文件
