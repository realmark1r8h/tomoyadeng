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
     * @brief	注册表操作类.<br>工作线程**Renderer线程**
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
         * @brief	创建一个注册表操作对象.
         *
         * @param	#Int  .
         *
         * @return  #Registy 注册表操作对象
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
         * @brief	创建一个子键.
         *
         * @param	#String 子键路径.
         *
         * @return	#Boolean true成功/false失败.
         */
        
        Any create(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any RegistryTransfer::open(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	打开子键.
         *
         * @param	#String 子键路径.
         *
         * @return	#Boolean true成功/false失败.
         */
        
        Any open(IPCMessage::SmartType msg);
        
        
        /*!
         * @fn	Any RegistryTransfer::read(IPCMessage::SmartType msg);
         *
         * @tag	sync
         *
         * @brief	读取键值.
         *
         * @param	#String 子键.
         * @param	#String 键名.
         *
         * @return	#String 读取到的值.
         */
        
        Any read(IPCMessage::SmartType msg);
        
        
        /*!
         * @fn	Any RegistryTransfer::write(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	写入键值.
         *
         * @param	#String 子键.
         * @param	#String 键名.
         * @param	#String 键值.
         * @param	#Boolean=false 如果子键不存在，是否自己创建子键.
         *
         * @return	#Boolean true成功/false失败.
         */
        
        Any write(IPCMessage::SmartType msg);
        
        
        
        
        /*!
         * @fn	Any RegistryTransfer::remove(IPCMessage::SmartType msg);
         *
         * @tag sync
         *
         * @brief	删除键值.
         *
         * @param	#String 子键.
         * @param	#String 键名.
         *
         * @return	#Boolean true成功/false失败.
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