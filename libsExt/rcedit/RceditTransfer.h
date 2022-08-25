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
         *
         * @tag static sync
         *
         * @brief	�Ӵ����м��������ļ��������ļ������ĸ����ݶΣ�����������������manifest.json��ͬ��ֻ������һ���ļ�������EXE�ļ��Ļ�����Ϣ������"fileSettings",����ֵ���£�<br>
         *			&nbsp; **CompanyName**: ��˾���ƣ�Ĭ��ֵ"NCUI"<br>
         *			&nbsp; **FileDescription**: �ļ�������Ĭ��ֵ"NCUI��ʾ����"<br>
         *			&nbsp; **FileVersion**:�ļ��汾��Ĭ��ֵ"1.0.0.0"<br>
         *			&nbsp; **InternalName**:�ڲ����ƣ�Ĭ��ֵ"NCUIDemo.exe"<br>
         *			&nbsp; **LegalCopyright**:��������Ȩ��Ĭ��ֵ"Copyright (C) 2017"<br>
         *			&nbsp; **OriginalFileName**:ԭʼ�ļ����ƣ�Ĭ��ֵ"NCUIDemo.exe"<br>
         *			&nbsp; **ProductName**:��Ʒ���ƣ�Ĭ��ֵ"NCUI��ʾ����"<br>
         *			&nbsp; **ProductVersion**:��Ʒ�汾��Ĭ��ֵ"1.0.0.0"<br>
         *			&nbsp; **Icon**:ͼ��·����Ĭ��ʹ�õ�ǰ�����ͼ��<br>
         *
         * @param	#String �����ļ�·�����ļ����ݱ���ΪJSON��ʽ.
         *
         * @return	#Boolean true �ɹ�/ false ʧ��.
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
         * 			ע��:**����Ĳ�������JSON��ʽ���ַ���������JSON����**
         *
         * @param	#String EXE�ļ���Ϣ��JSON�ַ��������ü�{@link loadDiskSettings=rcedit.loadDiskSettings}.
         * @param	#String ��������,JSON�ַ���������ֵ��{@link ��������}.
         * @param	#String ��������ڲ���,JSON�ַ���������ֵ��{@link ��������ڲ���}.
         * @param	#String �����������,JSON�ַ���������ֵ��{@link ��������}.
         *
         * @return	#Boolean true/false.
         * @example
         *
         ```
        	include('rcedit');
        	var fileSettings = rcedit.getDefaultFileSettings();
        	var appSettings = rcedit.getDefaultAppSettings();
        	var browserWindowSettings = rcedit.getDefaultBrowserSettings();
        	var splashWindowSettings = rcedit.getDefaultSplashSettings();
        	console.log(fileSettings);
        	console.log(appSettings);
        	console.log(browserWindowSettings);
        	console.log(splashWindowSettings);
        	rcedit.commit(fileSettings, appSettings, browserWindowSettings, splashWindowSettings);
        
         ```
         */
        
        /*!
        * @fn	amo::Any RceditTransfer::commit(IPCMessage::SmartType msg);
        * @tag static sync
        * @brief	����EXE�ļ�����������������úõĲ���д��EXE�ļ���.
        *
        * @return	#Boolean .
        * @example
        *
        ```
        	include('rcedit');
        	rcedit.commit();
        ```
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


