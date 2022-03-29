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
         * @brief	�������ļ��е�������ӵ�MAP��.
         *
         * @param [in,out]	json	The JSON.
         */
        
        void initUrlMapping(amo::json& json);
        
        
        Any getConfig(IPCMessage::SmartType msg);
        
        Any setConfig(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::toAbsolutePath(IPCMessage::SmartType msg);
         *
         * @brief	��һ��·��תΪ����·���磺%web%.
         *
         * @param	msg	The message.
         *
         * @return	msg as Any.
         */
        
        Any toAbsolutePath(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::quit(IPCMessage::SmartType msg);
         *
         * @brief	�����˳����򣬿��Ա�ȡ��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any quit(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::exit(IPCMessage::SmartType msg);
         *
         * @brief	ǿ���˳�����.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any exit(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::urlToNativePath(IPCMessage::SmartType msg);
         *
         * @brief	�⼸���������ܻᱻIO�̺߳�UI�߳�ͬʱ���ã�����Ҫ����.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any urlToNativePath(IPCMessage::SmartType msg); //IO
        
        /*!
         * @fn	Any AppTransfer::addUrlMapping(IPCMessage::SmartType msg);
         *
         * @brief	���URLӳ��·��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any addUrlMapping(IPCMessage::SmartType msg);	// UI
        
        /*!
         * @fn	Any AppTransfer::removeUrlMapping(IPCMessage::SmartType msg);
         *
         * @brief	�Ƴ�URLӳ��·��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any removeUrlMapping(IPCMessage::SmartType msg); //UI
        
        /*!
         * @fn	Any AppTransfer::setDragClassName(IPCMessage::SmartType msg);
         *
         * @brief	���ÿ��϶����ڿؼ�Class��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setDragClassName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::setNoDragClassName(IPCMessage::SmartType msg);
         *
         * @brief	���ò����ֶ����ڿؼ�Class��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setNoDragClassName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::setGlobal(IPCMessage::SmartType msg);
         *
         * @brief	����ȫ������.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setGlobal(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::getGlobal(IPCMessage::SmartType msg);
         *
         * @brief	��ȡȫ������.
         *
         * @param	msg	The message.
         *
         * @return	The global.
         */
        
        Any getGlobal(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::getAutoRun(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ�Ƿ񿪻�����.
         *
         * @param	msg	The message.
         *
         * @return	The automatic run.
         */
        
        Any getAutoRun(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any AppTransfer::setAutoRun(IPCMessage::SmartType msg);
         *
         * @brief	�����Ƿ񿪻�����.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setAutoRun(IPCMessage::SmartType msg);
        
        /**
         * @fn	Any AppTransfer::duration(IPCMessage::SmartType msg);
         *
         * @brief	��ǰ��������ʱ��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any elapsed(IPCMessage::SmartType msg);
        /**
         * @fn	bool AppTransfer::restart(IPCMessage::SmartType msg);
         *
         * @brief	������ǰ����.
         *
         * @param	msg	The message.
         *
         * @return	true if it succeeds, false if it fails.
         */
        
        bool restart(IPCMessage::SmartType msg);
        
        /**
         * @fn	bool AppTransfer::destroy(IPCMessage::SmartType msg);
         *
         * @brief	���ٵ�ǰ���򣬣�ɾ�������ִ�г���
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
        /*! @brief	URLת����·����. */
        std::recursive_mutex m_mutex;
        /*! @brief	URL������·��ӳ��. */
        std::list<std::pair<std::string, std::string > > m_oUrlToNativeMap;
        /*! @brief	ȫ������. */
        amo::json m_global;
    };
}



#endif // AMO_APPTRANSFER_H__