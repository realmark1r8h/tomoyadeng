// Created by amoylel on 06/19/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_RCEDITTRANSFER_H__
#define AMO_RCEDITTRANSFER_H__

#include "transfer/ClassTransfer.hpp"


#include <memory>
#include <amo/json.hpp>
#include <vector>


namespace amo {

    class ResourceUpdater;
    // test
    class RceditTransfer
        : public ClassTransfer
        , public amo::singleton<RceditTransfer> {
    public:
        RceditTransfer();
        ~RceditTransfer();
        amo::Any loadDiskSettings(IPCMessage::SmartType msg);
        amo::Any getDefaultFileSettings(IPCMessage::SmartType msg);
        amo::Any getDefaultAppSettings(IPCMessage::SmartType msg);
        amo::Any getDefaultBrowserSettings(IPCMessage::SmartType msg);
        amo::Any getDefaultSplashSettings(IPCMessage::SmartType msg);
        amo::Any commit(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(RceditTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(loadDiskSettings, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getDefaultFileSettings, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getDefaultAppSettings, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getDefaultBrowserSettings, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getDefaultSplashSettings, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(commit, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    protected:
        amo::json m_oConfig;
        std::shared_ptr<ResourceUpdater> m_pUpdater;
        amo::json m_oSettings;
    };
    
}


#endif // AMO_RCEDITTRANSFER_H__

