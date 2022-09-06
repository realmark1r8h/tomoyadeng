// Created by amoylel on 12/01/2017.
// Copyright (c) 2017 amoylel All rights reserved.


#ifndef LIBSEXT_FILETRANSFER_7B3B1E43_5470_4945_A0D5_0AFA9312172F_HPP__
#define LIBSEXT_FILETRANSFER_7B3B1E43_5470_4945_A0D5_0AFA9312172F_HPP__






#include <string>
#include <memory>

#include <amo/singleton.hpp>
#include <transfer/RunnableTransfer.hpp>

#include <amo/file.hpp>
#include <amo/filestream.hpp>
#include <amo/path.hpp>

namespace amo {

    /**
     * @class	FileStream
     *
     * @chapter extend
     *
     * @brief	文件读写类.
     *
     * @extend	Runnable
     */
    
    class FileTransfer
        : public RunnableTransfer
        , public amo::singleton<FileTransfer> {
    public:
        FileTransfer()
            : RunnableTransfer("FileStream") {
            
        }
        
        /**
         * @fn	FileTransfer::FileStream(const amo::string& fileName, int mode = 3)
         * @tag constructor
         *
         * @brief	创建或打开一个文件.
         *
         * @param	#String 需要操作文件的路径.
         * @param	#Int=3	文件打开方式，可以选择以下值，组合使用.<br>
         * 					&nbsp;&nbsp;&nbsp;&nbsp; 1 以只读方式打开，如果文件不存在，那么将打开失败<br>
         * 					&nbsp;&nbsp;&nbsp;&nbsp; 2 以写方式打开，如果文件不存在则会创建文件<br>
         * 					&nbsp;&nbsp;&nbsp;&nbsp; 8 以追加方式打开<br>
         * 					&nbsp;&nbsp;&nbsp;&nbsp; 32 以二进制方式打开文件<br>
         * @return #FileStream
         */
        
        FileTransfer(const amo::string& fileName, int mode = 3)
            : RunnableTransfer("FileStream") {
            
            
            m_filename = fileName;
            m_mode = mode;
            open(IPCMessage::Empty());
        }
        
        ~FileTransfer() {
            if (m_filestream) {
                m_filestream->close();
            }
            
            m_filestream.reset();
            m_file.reset();
        }
        
        virtual std::string getClass() const override {
            return "FileStream";
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
            pTransfer->setDefaultTriggerEventFunc(this->getDefaultTriggerEventFunc());
            return pTransfer->getFuncMgr().toSimplifiedJson();
        }
        
        /**
         * @fn	Any FileTransfer::open(IPCMessage::SmartType msg)
         * @tag sync
         * @brief	打开文件，创建对象时会默认打开文件，不需要重复调用.
         * 			如果你调用了{@link close=FileStream.close}函数，那么可以调用该函数重新打开文件
         *
         * @param	#int=0 文件打开方式，参见{@link 构造函数=FileStream.FileStream}的内容.
         * 				   如果不输入该参数，程序会使用创建该对象时指定的打开方式
         *
         *
         * @return	#Boolean.
         */
        
        Any open(IPCMessage::SmartType msg) {
        
            if (m_filestream) {
                m_filestream->close();
            }
            
            m_filestream.reset();
            m_file.reset();
            Any& val = msg->getArgumentList()->getValue(0);
            int mode = m_mode;
            
            if (val.is<int>()) {
                mode = val.As<int>();
            }
            
            if (mode <= 0) {
                return false;
            }
            
            amo::path p(m_filename);
            m_file.reset(new amo::file(p));
            m_filestream = m_file->get_filestream(mode);
            
        }
        
        /**
         * @fn	Any FileTransfer::read(IPCMessage::SmartType msg)
         * @tag sync
         * @brief	读取所有文件内容.
         *
         * @return	#String 读取到的字符串.
         */
        
        Any read(IPCMessage::SmartType msg) {
            if (!m_filestream) {
                return "";
            }
            
            return m_filestream->read_all();
        }
        
        /**
         * @fn	Any FileTransfer::write(IPCMessage::SmartType msg)
         * @tag sync
         * @brief	向文件中写入字符串.
         *
         * @param	#String 需要写入的数据.
         *
         * @return	#Boolean true 成功/false 失败.
         */
        
        Any write(IPCMessage::SmartType msg) {
            if (!m_filestream) {
                return false;
            }
            
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            std::string str = args->getString(0);
            
            if (str.empty()) {
                return false;
            }
            
            m_filestream->write(str);
            return true;
        }
        
        /**
         * @fn	Any FileTransfer::append(IPCMessage::SmartType msg)
         * @tag sync
         * @brief	将一个文件的内容追加到当前文件中.
         *
         * @param	#String 文件路径
         *
         * @return	#Boolean true 成功/false 失败.
         */
        
        Any append(IPCMessage::SmartType msg) {
            std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
            amo::string str(args->getString(0), true);
            amo::path p(str);
            
            if (!p.file_exists()) {
                return false;
            }
            
            amo::filestream file(p, std::ios::in | std::ios::binary);
            int nTotal = 0;
            
            while (true) {
                char buffer[4096] = { 0 };
                int nBytes = file.read_some(buffer, 4095);
                nTotal += nBytes;
                
                if (nBytes == 0) {
                    break;
                }
                
                m_filestream->write(buffer, nBytes);
                
            }
            
            return true;
        }
        
        
        // 将当前文件追加到另一个文件中去
        Any appendTo(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        /**
         * @fn	Any FileTransfer::close(IPCMessage::SmartType msg)
         * @tag sync
         * @brief	关闭文件，关闭后不能再调用其他API操作文件.
         *
         *
         * @return	无.
         * @see open=FileStream.open
         */
        
        Any close(IPCMessage::SmartType msg) {
            if (!m_filestream) {
                return Undefined();
            }
            
            m_filestream->close();
            m_filestream.reset();
            m_file.reset();
            return Undefined();
        }
        
        /**
         * @fn	Any FileTransfer::size(IPCMessage::SmartType msg)
         * @tag sync
         * @brief	获取文件大小.
         *
         * @return	#Int.
         */
        
        Any size(IPCMessage::SmartType msg) {
            if (!m_file) {
                return 0;
            }
            
            return (int)m_file->size();
        }
        
        /**
         * @fn	Any FileTransfer::Remove(IPCMessage::SmartType msg)
         * @tag sync static
         * @brief 删除文件.
         *
         * @param #String 文件路径.
         *
         * @return	无.
         */
        
        Any Remove(IPCMessage::SmartType msg) {
            amo::string strPath(msg->getArgumentList()->getString(0), true);
            amo::path p(strPath);
            p.remove();
            return Undefined();
        }
        
        
        /**
        * @fn	Any FileTransfer::remove(IPCMessage::SmartType msg)
        * @tag sync
        * @brief 删除当前文件.
        *
        * @return	无.
        */
        
        Any remove(IPCMessage::SmartType msg) {
            close(msg);
            amo::path p(m_filename);
            p.remove();
            return Undefined();
        }
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(FileTransfer, RunnableTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Remove, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(read, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(write, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(append, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(appendTo, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(close, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(size, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(remove, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    public:
    
        std::shared_ptr<amo::file> m_file;
        amo::string m_filename;
        std::shared_ptr<amo::filestream> m_filestream;
        int m_mode;
    };
}

#endif //LIBSEXT_FILETRANSFER_7B3B1E43_5470_4945_A0D5_0AFA9312172F_HPP__
