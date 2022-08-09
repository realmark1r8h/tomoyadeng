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
     * @brief	��Դ�༭������������exe����.
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
         * @brief	�Ӵ����м��������ļ�.
         *
         * @param	#String �����ļ�·�����ļ����ݱ���ΪJSON��ʽ.
         *
         * @return	#Boolean.
         */
        
        amo::Any loadDiskSettings(IPCMessage::SmartType msg);
        
        /*!
         * @fn	amo::Any RceditTransfer::getDefaultFileSettings(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	��ȡĬ�ϵ��ļ�����.
         *
         *
         * @return	#JsonObject.
         */
        
        amo::Any getDefaultFileSettings(IPCMessage::SmartType msg);
        
        /*!
         * @fn	amo::Any RceditTransfer::getDefaultAppSettings(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	��ȡĬ�ϵ�APP��������.
         *
         * @return	#JsonObject.
         */
        
        amo::Any getDefaultAppSettings(IPCMessage::SmartType msg);
        
        /*!
         * @fn	amo::Any RceditTransfer::getDefaultBrowserSettings(IPCMessage::SmartType msg);
         *
         * @brief	��ȡĬ�ϵ������������������.
         *
         * @return	#JsonObject.
         */
        
        amo::Any getDefaultBrowserSettings(IPCMessage::SmartType msg);
        
        /*!
         * @fn	amo::Any RceditTransfer::getDefaultSplashSettings(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	��ȡĬ�ϵ���������.
         *
         * @return	#JsonObject.
         */
        
        amo::Any getDefaultSplashSettings(IPCMessage::SmartType msg);
        
        
        /*!
         * @fn	amo::Any RceditTransfer::commit(IPCMessage::SmartType msg);
         * @tag static sync
         * @brief	����EXE�ļ�����������������úõĲ���д��EXE�ļ���.
         *
         * @param	#String �����ļ�Ŀ¼.
         * @param	#String ��������,JSON�ַ���
         * @param	#String ��������ڲ���,JSON�ַ���
         * @param	#String �����������,JSON�ַ���
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


