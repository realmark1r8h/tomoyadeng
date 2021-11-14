// Created by amoylel on 12/01/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_FILETRANSFER_HPP__
#define AMO_FILETRANSFER_HPP__

#include <amo/singleton.hpp>
#include <transfer/RunnableTransfer.hpp>
#include <string>
#include <amo/file.hpp>

namespace amo {

    class FileTransfer
        : public RunnableTransfer
        , public amo::singleton<FileTransfer> {
    public:
        FileTransfer()
            : RunnableTransfer("File2") {
            
        }
        
        FileTransfer(const amo::string& fileName, int mode = 3)
            : RunnableTransfer("File2") {
            amo::path p(fileName);
            m_pFile.reset(new amo::file(p, mode));
        }
        ~FileTransfer() {
            if (m_pFile) {
                m_pFile->close();
            }
            
            m_pFile.reset();
        }
        
        virtual std::string getClass() const override {
            return "File2";
        }
        
        virtual amo::Transfer * getInterface(const std::string& name) override {
            if (name == FileTransfer::getClass()) {
                return this;
            }
            
            return RunnableTransfer::getInterface(name);
        }
        
        virtual  Any onCreateClass(IPCMessage::SmartType msg) override {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            amo::string fileName(args->getString(0), true);
            int nMode = 3;
            Any& val = args->getValue(1);
            
            if (val.is<int>()) {
                nMode = args->getInt(1);
            }
            
            auto pTransfer = ClassTransfer::createTransfer<FileTransfer>(fileName, nMode);
            pTransfer->setTriggerEventFunc(this->getTriggerEventFunc());
            return pTransfer->getFuncMgr().toSimplifiedJson();
        }
        
        // 读取
        Any read(IPCMessage::SmartType msg) {
            if (!m_pFile) {
                return "";
            }
            
            return m_pFile->read();
        }
        
        // 写入
        Any write(IPCMessage::SmartType msg) {
            if (!m_pFile) {
                return false;
            }
            
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            std::string str = args->getString(0);
            
            if (str.empty()) {
                return false;
            }
            
            m_pFile->write(str);
            return true;
        }
        
        // 追加一个文件
        Any append(IPCMessage::SmartType msg) {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            amo::string str(args->getString(0), true);
            amo::path p(str);
            
            if (!p.file_exists()) {
                return false;
            }
            
            /*  amo::file file(amo::path("D:\\1ff97805-4901-418d-9f1c-76c925e47af7.zip"));
              std::vector<int8_t> fileStream;
              file.read_all_bytes(fileStream);
              m_pFile->write((char*)fileStream.data(), fileStream.size());
              return Undefined();*/
            
            amo::file file(p, std::ios::in | std::ios::binary);
            
            while (true) {
                char buffer[4096] = { 0 };
                int nBytes = file.read(buffer, 4095);
                
                if (nBytes == 0) {
                    break;
                }
                
                m_pFile->write(buffer, nBytes);
                
            }
            
            return true;
        }
        
        
        // 将当前文件追加到另一个文件中去
        Any appendTo(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        Any close(IPCMessage::SmartType msg) {
            if (!m_pFile) {
                return Undefined();
            }
            
            m_pFile->close();
            m_pFile.reset();
            return Undefined();
        }
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(FileTransfer, RunnableTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(read, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(write, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(append, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(appendTo, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(close, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    public:
    
        std::shared_ptr<amo::file> m_pFile;
    };
}

#endif // AMO_FILETRANSFER_HPP__