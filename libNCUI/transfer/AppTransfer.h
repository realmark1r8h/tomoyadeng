// Created by amoylel on 07/07/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_APPTRANSFER_H__
#define AMO_APPTRANSFER_H__


#include <amo/singleton.hpp>

#include "transfer/ClassTransfer.hpp"


namespace amo {

    /*!
     * @class	app
     *
     * @extend  Object
     *
     * @brief	���Ƴ��������������ڣ����ṩһЩ�������صĹ���.<br>
     * 			�����̣߳�**UI�߳�**��
     */
    
    class AppTransfer
        : public ClassTransfer
        , public amo::singleton<AppTransfer> {
        
    public:
        AppTransfer();
        
        /*!
         * @ignore
         *
         * @fn	void AppTransfer::initUrlMapping(amo::json& json);
         *
         * @brief	�������ļ��е�������ӵ�MAP��.
         *
         * @param [in,out]	json	The JSON.
         */
        
        void initUrlMapping(amo::json& json);
        
        /*!
         * @fn	static Any AppTransfer::getConfig(IPCMessage::SmartType msg);
         *
         * @brief	��ȡӦ�ó�����������ò���,�ɻ�ȡ�����ݼ�{@link ��������=��������}.
         *
         * @return	#JsonObject �������ò���.
         */
        
        
        /*!
        * @fn	static Any AppTransfer::getConfig(IPCMessage::SmartType msg);
        *
        * @brief	��ȡӦ�ó����ָ�����ò���.
        *
        * @param	#String ��Ҫ��ȡ���ֶ�����.
        *
        * @return	�����ֶ�������Ӧ�����ò������������������ò������Ͷ�����ΪJS��֧�ֵĻ�����������.
        *
        * @see setConfig=app.setConfig
        * @example
        			```
        				//��ȡӦ�ó�����������ò���
        				var config = app.getConfig();
        				console.log(config);
        
        				//��ȡӦ�ó����ָ�����ò���
        				var single_process = app.getConfig('single_process');
        				console.log('������ģʽ��' + single_process);
        			```
        */
        
        
        Any getConfig(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::setConfig(IPCMessage::SmartType msg);
         *
         * @brief	����Ӧ�ó������ò���.�ú�������Ҫ��һ��Ҫ������֧�ֵĲ�����
         * 			��Ҳ���������Զ������������getConfig�����ȡ�����õ�ֵ��{@link app.getConfig}���Ӧ.
         *
         * @param	#JsonObject ��Ҫ���õĲ�������ֵΪһ��JSON����.
         *
         * @return	��.
         *
         * @see getConfig=app.getConfig
         *
         * @example
        			```
        			app.setConfig({
        				debugMode: true,
        				custom: 'custom'
        			});
        
        			```
         */
        
        Any setConfig(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::toAbsolutePath(IPCMessage::SmartType msg);
         *
         * @brief	��һ��·��תΪ����·���磺%web%.
         *
         * @param	#String ��Ҫת����·��.
         *
         * @return	#String ת����ľ���·��.
         */
        
        Any toAbsolutePath(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::quit(IPCMessage::SmartType msg);
         *
         * @brief	�����˳����򣬿����û���ȡ������window.unload������.
         *
         *
         * @return	��.
         */
        
        Any quit(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::exit(IPCMessage::SmartType msg);
         *
         * @brief	ǿ���˳�����.
         *
         *
         * @return	��.
         */
        
        Any exit(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::urlToNativePath(IPCMessage::SmartType msg);
         *
         * @brief	��һ��URLת��Ϊ����·����
         * 			�⼸���������ܻᱻIO�̺߳�UI�߳�ͬʱ���ã�����Ҫ����.
         *
         * @param	#String ��Ҫת����URL.
         * @param	#Boolean=false �Ƿ�Ҫ����ӳ����ļ����� .
         *
         * @return	#String ת�����·���������ǰ������URLû����֮ӳ��ı���·����
         * 			�����ظ�URL.
         */
        
        Any urlToNativePath(IPCMessage::SmartType msg); //IO
        
        /*!
         * @fn	static Any AppTransfer::addUrlMapping(IPCMessage::SmartType msg);
         *
         * @brief	���URLӳ��·��.
         *
         * @param	#String ��Ҫ���ӳ���URL.
         *
         * @param   #String ��ӳ��ı����ļ�·������·��������һ����ͨ���ļ����ļ��У�
         * 					Ҳ������ZIPѹ������SQLITE���ݿ�.
         *
         * @return	#Boolean ��Ϊ����true, ʧ�ܷ���false.
         */
        
        Any addUrlMapping(IPCMessage::SmartType msg);	// UI
        
        /*!
         * @fn	static Any AppTransfer::removeUrlMapping(IPCMessage::SmartType msg);
         *
         * @brief	�Ƴ�URLӳ��·��.
         *
         * @param	#String ��Ҫ�Ƴ���URL.
         *
         * @return	��.
         */
        
        Any removeUrlMapping(IPCMessage::SmartType msg); //UI
        
        /*!
         * @ignore
         *
         * @fn	static Any AppTransfer::setDragClassName(IPCMessage::SmartType msg);
         *
         * @brief	���ÿ��϶����ڿؼ�Class��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setDragClassName(IPCMessage::SmartType msg);
        
        /*!
         * @ignore
         *
         * @fn	static Any AppTransfer::setNoDragClassName(IPCMessage::SmartType msg);
         *
         * @brief	���ò����ֶ����ڿؼ�Class��.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setNoDragClassName(IPCMessage::SmartType msg);
        
        /*!
         * @ignore
         *
         * @fn	static Any AppTransfer::setGlobal(IPCMessage::SmartType msg);
         *
         * @brief	����ȫ������.
         *
         * @param	msg	The message.
         *
         * @return	Any.
         */
        
        Any setGlobal(IPCMessage::SmartType msg);
        
        /*!
         * @ignore
         *
         * @fn	static Any AppTransfer::getGlobal(IPCMessage::SmartType msg);
         *
         * @brief	��ȡȫ������.
         *
         * @param	msg	The message.
         *
         * @return	The global.
         */
        
        Any getGlobal(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::getAutoRun(IPCMessage::SmartType msg);
         *
         * @brief	��ȡ�Ƿ񿪻�����.
         *
         * @return	#Boolean .
         */
        
        Any getAutoRun(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::setAutoRun(IPCMessage::SmartType msg);
         *
         * @brief	�����Ƿ񿪻�����.
         *
         * @param	#Boolean=false true����������faseȡ����������.
         *
         * @return	��.
         */
        
        Any setAutoRun(IPCMessage::SmartType msg);
        
        /**
         * @fn	static Any AppTransfer::duration(IPCMessage::SmartType msg);
         *
         * @brief	��ǰ��������������ڵ�����ʱ��(����).
         *
         * @return	#Int.
         */
        
        Any elapsed(IPCMessage::SmartType msg);
        
        /*!
         * @fn	static Any AppTransfer::restart(IPCMessage::SmartType msg);
         *
         * @brief	������ǰ����.
         *
         * @param	#Int=0 ������ʱ(��)����ǰ����������رգ��µĳ��������ʱʱ�䵽�������.
         *
         * @return	#Boolean ���ɷ���true, ʧ�ܷ���false.
         */
        
        Any restart(IPCMessage::SmartType msg);
        
        /**
         * @fn	static Any AppTransfer::destroy(IPCMessage::SmartType msg);
         *
         * @brief	���ٵ�ǰ����(�Ӵ�����ɾ����ǰ��ִ�г���).
         *
         *
         * @return	��.
         */
        
        Any destroy(IPCMessage::SmartType msg);
        
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