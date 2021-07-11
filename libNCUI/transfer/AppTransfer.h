// Created by amoylel on 07/07/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_APPTRANSFER_H__
#define AMO_APPTRANSFER_H__


#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"


namespace amo {

    class AppTransfer
        : public ClassTransfer
        , public amo::singleton<AppTransfer> {
        
    public:
        AppTransfer();
        
        void initUrlMapping(amo::json& json);
        
        
        Any getConfig(IPCMessage::SmartType msg);
        Any setConfig(IPCMessage::SmartType msg);
        Any toAbsolutePath(IPCMessage::SmartType msg);
        Any quit(IPCMessage::SmartType msg);
        Any exit(IPCMessage::SmartType msg);
        
        
        // 这几个函数可能会被IO线程和UI线程同时调用，所以要加锁
        Any urlToNativePath(IPCMessage::SmartType msg); //IO
        
        Any addUrlMapping(IPCMessage::SmartType msg);	// UI
        Any removeUrlMapping(IPCMessage::SmartType msg); //UI
        
        Any setDragClassName(IPCMessage::SmartType msg);
        Any setNoDragClassName(IPCMessage::SmartType msg);
        
        Any makeSingleInstance(IPCMessage::SmartType msg);
        Any releaseSingleInstance(IPCMessage::SmartType msg);
        
        Any data(IPCMessage::SmartType msg);
        Any setGlobal(IPCMessage::SmartType msg);
        Any getGlobal(IPCMessage::SmartType msg);
        
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(AppTransfer, ClassTransfer)
        
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getConfig, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setConfig, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(toAbsolutePath, TransferFuncStatic | TransferExecSync)
        
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(addUrlMapping, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeUrlMapping, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(urlToNativePath, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setDragClassName, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setNoDragClassName, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(quit, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(exit, TransferFuncStatic)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(data, TransferFuncProperty | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setGlobal, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getGlobal, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
    public:
    
    private:
        std::recursive_mutex m_mutex;
        
        std::list<std::pair<std::string, std::string > > m_oUrlToNativeMap;
        CefRefPtr<CefRunFileDialogCallback> m_pRunFileDialogCallback;
        
        /*! @brief	全局数据. */
        amo::json m_global;
    };
}



#endif // AMO_APPTRANSFER_H__