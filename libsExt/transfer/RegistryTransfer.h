// Created by amoylel on 14/04/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIBSEXT_REGISTRYTRANSFER_91F3BC0D_B8D6_4BBA_984C_B861753B0CF0_H__
#define LIBSEXT_REGISTRYTRANSFER_91F3BC0D_B8D6_4BBA_984C_B861753B0CF0_H__


#include <amo/singleton.hpp>
#include "transfer/RunnableTransfer.hpp"
#include <amo/registry.hpp>

namespace amo {

    /*!
     * @class	Registry
     *
     * @chapter extend
     *
     * @extend Runnable
     *
     * @brief	ע��������.<br>�����߳�**Renderer�߳�**
     */
    
    class RegistryTransfer
        : public RunnableTransfer
        , public amo::singleton<RegistryTransfer> {
    public:
        RegistryTransfer();
        
        /*!
         * @fn	RegistryTransfer::RegistryTransfer(int hKey);
         *
         * @tag constructor sync
         *
         * @brief	����һ��ע����������.
         *
         * @param	#Int  .
         *
         * @return  #Registy ע����������
         */
        
        RegistryTransfer(int hKey);
        Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual std::string getClass() const override;
        virtual Transfer* getInterface(const std::string& name) override;
        
        /*!
         * @fn	Any RegistryTransfer::create(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	����һ���Ӽ�.
         *
         * @param	#String �Ӽ�·��.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any create(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any RegistryTransfer::open(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	���Ӽ�.
         *
         * @param	#String �Ӽ�·��.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any open(IPCMessage::SmartType msg);
        
        
        /*!
         * @fn	Any RegistryTransfer::read(IPCMessage::SmartType msg);
         *
         * @tag	sync
         *
         * @brief	��ȡ��ֵ.
         *
         * @param	#String �Ӽ�.
         * @param	#String ����.
         *
         * @return	#String ��ȡ����ֵ.
         */
        
        Any read(IPCMessage::SmartType msg);
        
        
        /*!
         * @fn	Any RegistryTransfer::write(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	д���ֵ.
         *
         * @param	#String �Ӽ�.
         * @param	#String ����.
         * @param	#String ��ֵ.
         * @param	#Boolean=false ����Ӽ������ڣ��Ƿ��Լ������Ӽ�.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any write(IPCMessage::SmartType msg);
        
        
        
        
        /*!
         * @fn	Any RegistryTransfer::remove(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	ɾ����ֵ.
         *
         * @param	#String �Ӽ�.
         * @param	#String ����.
         *
         * @return	#Boolean true�ɹ�/falseʧ��.
         */
        
        Any remove(IPCMessage::SmartType msg);
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(RegistryTransfer, RunnableTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(create, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(open, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(read, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(write, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(remove, TransferFuncNormal | TransferExecSync)
        
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(HKEY_CLASSES_ROOT, (int)HKEY_CLASSES_ROOT)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(HKEY_CURRENT_USER, (int)HKEY_CURRENT_USER)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(HKEY_LOCAL_MACHINE, (int)HKEY_LOCAL_MACHINE)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(HKEY_USERS, (int)HKEY_USERS)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(HKEY_PERFORMANCE_DATA,
                                       (int)HKEY_PERFORMANCE_DATA)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(HKEY_PERFORMANCE_TEXT,
                                       (int)HKEY_PERFORMANCE_TEXT)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(HKEY_PERFORMANCE_NLSTEXT,
                                       (int)HKEY_PERFORMANCE_NLSTEXT)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(HKEY_CURRENT_CONFIG, (int)HKEY_CURRENT_CONFIG)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(HKEY_DYN_DATA, (int)HKEY_DYN_DATA)
        AMO_CEF_MESSAGE_TRANSFER_ATTR2(HKEY_CURRENT_USER_LOCAL_SETTINGS,
                                       (int)HKEY_CURRENT_USER_LOCAL_SETTINGS)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        std::shared_ptr<amo::registry> m_registry;
    };
}



#endif //LIBSEXT_REGISTRYTRANSFER_91F3BC0D_B8D6_4BBA_984C_B861753B0CF0_H__