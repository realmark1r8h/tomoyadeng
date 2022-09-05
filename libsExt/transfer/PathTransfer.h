// Created by amoylel on 17/03/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIBSEXT_PATHTRANSFER_F5089CC4_51A8_4448_BB3D_04242220BFA0_H__
#define LIBSEXT_PATHTRANSFER_F5089CC4_51A8_4448_BB3D_04242220BFA0_H__







#include <transfer/RunnableTransfer.hpp>
namespace amo {

    class path;
    
    /*!
     * @class	Path
     * @chapter extend
     *
     * @extend Runnable
     *
     * @chapter extend
     *
     * @brief	·����.<br>
     * 			�����߳�**Renderer�߳�**
     */
    
    class PathTransfer
        : public RunnableTransfer
        , public amo::singleton<PathTransfer> {
    public:
    
        PathTransfer();
        PathTransfer(const std::string& ansiPath);
        ~PathTransfer();
        
        
        virtual Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual std::string getClass() const override;
        virtual Transfer* getInterface(const std::string& name) override;
        
        
        
        /*!
         * @fn	Any PathTransfer::getFullAppDir(IPCMessage::SmartType msg);
         *  @tag sync static
         * @brief	���ص�ǰ��������Ŀ¼.
         *
         *
         * @return	#Path ����һ��Path����.
         */
        
        Any getFullAppDir(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any PathTransfer::getFullAppName(IPCMessage::SmartType msg);
         *  @tag sync static
         * @brief	��ȡ��ǰ���������·��.
         *
         * @return	#Path ����һ��Path����.
         */
        
        Any getFullAppName(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any PathTransfer::fileExsit(IPCMessage::SmartType msg);
         *  @tag sync static
         * @brief	�ж��ļ���Ŀ¼�Ƿ����.
         *
         * @param	#String ·��.
         *
         * @return	#Boolean true ����/false ������.
         */
        
        Any fileExsit(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any PathTransfer::Remove(IPCMessage::SmartType msg);
         * @tag static
         * @brief	ɾ��һ���ļ������Ŀ¼.
         *
         * @param	#String ·��.
         *
         * @return	#Boolean true �ɹ�/false ʧ��.
         */
        
        Any Remove(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any PathTransfer::RemoveAll(IPCMessage::SmartType msg);
         * @tag static
         * @brief	ɾ��һ���ļ����ļ��У��ļ�Ŀ¼���Բ�Ϊ��.
         *
         * @param	#String ·��.
         *
         * @return	#Boolean true �ɹ�/false ʧ��.
         */
        
        Any RemoveAll(IPCMessage::SmartType msg);
        
        
        /*!
        * @fn	Any PathTransfer::toString(IPCMessage::SmartType msg);
        * @tag sync
        * @brief	����ǰPath����ת��ΪString.
        *
        *
        * @return	#String .
        */
        
        Any toString(IPCMessage::SmartType msg);
        
        /*!
        * @fn	Any PathTransfer::isExsit(IPCMessage::SmartType msg);
        * @tag sync
        * @brief	�жϵ�ǰ·���Ƿ����.
        *
        *
        * @return	#Boolean true ����/ false ������.
        */
        
        Any isExsit(IPCMessage::SmartType msg);
        
        /*!
        * @fn	Any PathTransfer::append(IPCMessage::SmartType msg);
        * @tag sync
        * @brief	����ǰ·����׷����·��.
        *
        * @param	#String ��Ҫ׷����·��.
        *
        * @return	#Path ��ǰ����.
        */
        
        Any append(IPCMessage::SmartType msg);
        
        /*!
        * @fn	Any PathTransfer::removeFileSpec(IPCMessage::SmartType msg);
        * @tag sync
        * @brief	ȥ���ļ������õ�Ŀ¼.
        *
        *
        * @return	#Path ��ǰ����.
        */
        
        Any removeFileSpec(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any PathTransfer::copyTo(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	�����ļ���ָ��λ��.
         *
         * @param	#String Ŀ��λ��.
         *
         * @return	#Boolean true ����/ false ������.
         */
        
        Any copyTo(IPCMessage::SmartType msg);
        
        /*!
         * @fn	Any PathTransfer::moveTo(IPCMessage::SmartType msg);
         * @tag sync
         * @brief	�ƶ��ļ���ָ��λ��.
         *
         * @param	#String Ŀ��λ��.
         *
         * @return	#Boolean true ����/ false ������.
         */
        
        Any moveTo(IPCMessage::SmartType msg);
        
        
        /*!
        * @fn	Any PathTransfer::remove(IPCMessage::SmartType msg);
        * @tag
        * @brief	ɾ����ǰ·������·��ֻ����һ���ļ����Ŀ¼ɾ��һ���ļ������Ŀ¼.
        *
        * @return	#Boolean true �ɹ�/false ʧ��.
        */
        
        Any remove(IPCMessage::SmartType msg);
        
        /*!
        * @fn	Any PathTransfer::removeAll(IPCMessage::SmartType msg);
        * @tag
        * @brief	ɾ����ǰ·��������ɾ����Ŀ¼��.
        *
        *
        * @return	#Boolean true �ɹ�/false ʧ��.
        */
        
        Any removeAll(IPCMessage::SmartType msg);
    public:
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(PathTransfer, RunnableTransfer)
        
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getFullAppDir,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(getFullAppName,
                                      TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(fileExsit, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Remove, TransferFuncStatic | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(RemoveAll,
                                      TransferFuncStatic | TransferExecNormal)
                                      
        AMO_CEF_MESSAGE_TRANSFER_FUNC(toString, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isExsit, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(append, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeFileSpec,
                                      TransferFuncNormal | TransferExecSync)
                                      
        AMO_CEF_MESSAGE_TRANSFER_FUNC(remove,   TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(removeAll,
                                      TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(copyTo,
                                      TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(moveTo,
                                      TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        std::shared_ptr<amo::path>  m_pPath;
        
    };
}

#endif //LIBSEXT_PATHTRANSFER_F5089CC4_51A8_4448_BB3D_04242220BFA0_H__