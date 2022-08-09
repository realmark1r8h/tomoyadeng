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
    
    /*!
     * @class	rcedit
     *
     * @chapter extend
     *
     * @brief	资源编辑器，用来生成exe程序.
     */
    
    class RceditTransfer
        : public ClassTransfer
        , public amo::singleton<RceditTransfer> {
    public:
        RceditTransfer();
        ~RceditTransfer();
        
        /*!
         * @fn	amo::Any RceditTransfer::loadDiskSettings(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	从磁盘中加载配置文件.
         *
         * @param	#String 配置文件路径，文件内容必须为JSON格式.
         *
         * @return	#Boolean.
         */
        
        amo::Any loadDiskSettings(IPCMessage::SmartType msg);
        
        /*!
         * @fn	amo::Any RceditTransfer::getDefaultFileSettings(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	获取默认的文件参数.
         *
         *
         * @return	#JsonObject.
         */
        
        amo::Any getDefaultFileSettings(IPCMessage::SmartType msg);
        
        /*!
         * @fn	amo::Any RceditTransfer::getDefaultAppSettings(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	获取默认的APP启动参数.
         *
         * @return	#JsonObject.
         */
        
        amo::Any getDefaultAppSettings(IPCMessage::SmartType msg);
        
        /*!
         * @fn	amo::Any RceditTransfer::getDefaultBrowserSettings(IPCMessage::SmartType msg);
         *
         * @brief	获取默认的浏览器窗口启动参数.
         *
         * @return	#JsonObject.
         */
        
        amo::Any getDefaultBrowserSettings(IPCMessage::SmartType msg);
        
        /*!
         * @fn	amo::Any RceditTransfer::getDefaultSplashSettings(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	获取默认的启动画面.
         *
         * @return	#JsonObject.
         */
        
        amo::Any getDefaultSplashSettings(IPCMessage::SmartType msg);
        
        
        /*!
         * @fn	amo::Any RceditTransfer::commit(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	生成EXE文件，这个函数将把配置好的参数写入EXE文件中.
         *
         * @param	#String 配置文件目录.
         * @param	#String 启动参数,JSON字符串
         * @param	#String 浏览器窗口参数,JSON字符串
         * @param	#String 启动画面参数,JSON字符串
         *
         * @return	#Boolean .
         */
        
        amo::Any commit(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(RceditTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(loadDiskSettings, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getDefaultFileSettings, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getDefaultAppSettings, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getDefaultBrowserSettings, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getDefaultSplashSettings, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(commit, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    protected:
        amo::json m_oConfig;
        std::shared_ptr<ResourceUpdater> m_pUpdater;
        amo::json m_oSettings;
    };
    
}


#endif // AMO_RCEDITTRANSFER_H__


