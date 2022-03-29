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
        
        /*!
         * @fn	void AppTransfer::initUrlMapping(amo::json& json);
         *
         * @brief	将配置文件中的设置添加到MAP中.
         *
         * @param [in,out]	json	The JSON.
         */
        
        void initUrlMapping(amo::json& json);
        
        
        Any getConfig(IPCMessage::SmartType msg);
        
        Any setConfig(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::toAbsolutePath(IPCMessage::SmartType msg);
         *
         * @brief	将一个路径转为绝对路径如：%web%.
         *
         * @param	msg	The message.
         *
         * @return	msg as Any.
         */
        
        Any toAbsolutePath(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::quit(IPCMessage::SmartType msg);
         *
         * @brief	尝试退出程序，可以被取消.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any quit(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::exit(IPCMessage::SmartType msg);
         *
         * @brief	强制退出程序.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any exit(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::urlToNativePath(IPCMessage::SmartType msg);
         *
         * @brief	这几个函数可能会被IO线程和UI线程同时调用，所以要加锁.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any urlToNativePath(IPCMessage::SmartType msg); //IO
        
        /*!
         * @fn	Any AppTransfer::addUrlMapping(IPCMessage::SmartType msg);
         *
         * @brief	添加URL映射路径.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any addUrlMapping(IPCMessage::SmartType msg);	// UI
        
        /*!
         * @fn	Any AppTransfer::removeUrlMapping(IPCMessage::SmartType msg);
         *
         * @brief	移除URL映射路径.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any removeUrlMapping(IPCMessage::SmartType msg); //UI
        
        /*!
         * @fn	Any AppTransfer::setDragClassName(IPCMessage::SmartType msg);
         *
         * @brief	设置可拖动窗口控件Class名.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setDragClassName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::setNoDragClassName(IPCMessage::SmartType msg);
         *
         * @brief	设置不可手动窗口控件Class名.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setNoDragClassName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::setGlobal(IPCMessage::SmartType msg);
         *
         * @brief	设置全局数据.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setGlobal(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::getGlobal(IPCMessage::SmartType msg);
         *
         * @brief	获取全局数据.
         *
         * @param	msg	The message.
         *
         * @return	The global.
         */
        
        Any getGlobal(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::getAutoRun(IPCMessage::SmartType msg);
         *
         * @brief	获取是否开机启动.
         *
         * @param	msg	The message.
         *
         * @return	The automatic run.
         */
        
        Any getAutoRun(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::setAutoRun(IPCMessage::SmartType msg);
         *
         * @brief	设置是否开机启动.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setAutoRun(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any AppTransfer::duration(IPCMessage::SmartType msg);
         *
         * @brief	当前程序运行时间.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any elapsed(IPCMessage::SmartType msg);
        /**
         * @fn	bool AppTransfer::restart(IPCMessage::SmartType msg);
         *
         * @brief	重启当前程序.
         *
         * @param	msg	The message.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool restart(IPCMessage::SmartType msg);
        
        /**
         * @fn	bool AppTransfer::destroy(IPCMessage::SmartType msg);
         *
         * @brief	销毁当前程序，（删除自身可执行程序）
         *
         * @param	msg	The Message to destroy.
         *
         * @return	True if it succeeds, false if it fails.
         */
        
        bool destroy(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(AppTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getConfig, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setConfig, TransferFuncStatic)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setGlobal, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getGlobal, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setAutoRun, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getAutoRun, TransferFuncStatic | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(toAbsolutePath,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(urlToNativePath,
                                      TransferFuncStatic | TransferExecSync)
                                      
        AMO_CEF_MESSAGE_TRANSFER_FUNC(addUrlMapping, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeUrlMapping, TransferFuncStatic)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setDragClassName,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(setNoDragClassName,
                                      TransferFuncStatic | TransferExecSync)
                                      
        AMO_CEF_MESSAGE_TRANSFER_FUNC(quit, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(exit, TransferFuncStatic)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(restart, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(destroy, TransferFuncStatic)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(elapsed,
                                      TransferFuncStatic | TransferExecSync)
                                      
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        /*! @brief	URL转本地路径锁. */
        std::recursive_mutex m_mutex;
        /*! @brief	URL到本地路径映射. */
        std::list<std::pair<std::string, std::string > > m_oUrlToNativeMap;
        /*! @brief	全局数据. */
        amo::json m_global;
    };
}



#endif // AMO_APPTRANSFER_H__