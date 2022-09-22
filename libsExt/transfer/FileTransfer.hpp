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
     * @brief	�ļ���д��.
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
         * @brief	�������һ���ļ�.
         *
         * @param	#String ��Ҫ�����ļ���·��.
         * @param	#Int=3	�ļ��򿪷�ʽ������ѡ������ֵ�����ʹ��.<br>
         * 					&nbsp;&nbsp;&nbsp;&nbsp; 1 ��ֻ����ʽ�򿪣�����ļ������ڣ���ô����ʧ��<br>
         * 					&nbsp;&nbsp;&nbsp;&nbsp; 2 ��д��ʽ�򿪣�����ļ���������ᴴ���ļ�<br>
         * 					&nbsp;&nbsp;&nbsp;&nbsp; 8 ��׷�ӷ�ʽ��<br>
         * 					&nbsp;&nbsp;&nbsp;&nbsp; 32 �Զ����Ʒ�ʽ���ļ�<br>
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
         * @brief	���ļ�����������ʱ��Ĭ�ϴ��ļ�������Ҫ�ظ�����.
         * 			����������{@link close=FileStream.close}��������ô���Ե��øú������´��ļ�
         *
         * @param	#int=0 �ļ��򿪷�ʽ���μ�{@link ���캯��=FileStream.FileStream}������.
         * 				   ���������ò����������ʹ�ô����ö���ʱָ���Ĵ򿪷�ʽ
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
            
            return true;
        }
        
        /**
         * @fn	Any FileTransfer::read(IPCMessage::SmartType msg)
         *
         * @tag sync deprecated
         *
         * @brief	��ȡ�����ļ�����.
         *
         * @return	#String ��ȡ�����ַ���.
         *
         * @see readSome=FileStream.readSome
         * @example
         *
         ```
        	include('FileStream');
        	var filestream = new FileStream('manifest.json');
        	console.log(filestream.read());
        	filestream.close();
         ```
         */
        
        Any read(IPCMessage::SmartType msg) {
            if (!m_filestream) {
                return "";
            }
            
            return m_filestream->read_all();
        }
        
        /**
         * @fn	Any FileTransfer::readAll(IPCMessage::SmartType msg)
         * @tag sync
         * @brief	��ȡ�����ַ���, readAll���ò�ͬ�Ļ��ƶ�ȡ�ļ����ò����뵱ǰ���޹أ�
         * 			���Ե��øú�������Ӱ������״̬������{@link eof=FileStream.eof}.
         *
         * @return	#String
         * @example
         *
         ```
        	include('FileStream');
        	var filestream = new FileStream('manifest.json');
        	console.log(filestream.readAll());
        	filestream.close();
         ```
         */
        
        Any readAll(IPCMessage::SmartType msg) {
            if (!m_filestream) {
                return "";
            }
            
            return m_filestream->read_all();
        }
        
        /**
         * @fn	Any FileTransfer::readSome(IPCMessage::SmartType msg)
         * @tag sync
         * @brief	��ȡָ������.
         *
         * @param	#Int ����ȡ���ٸ��ַ�.
         *
         * @return	#String.
         * @example
         *
         ```
        	include('FileStream');
        	var filestream = new FileStream('manifest.json');
        	while(!filestream.eof()){
        		console.log(filestream.readSome(100));
        	}
        	filestream.close();
         ```
         */
        
        Any readSome(IPCMessage::SmartType msg) {
            if (!m_filestream) {
                return "";
            }
            
            int count = msg->getArgumentList()->getInt(0);
            
            if (count <= 0) {
                return "";
            }
            
            std::vector<char> buffer(count, 0);
            
            int bytes = m_filestream->read_some(buffer.data(), count);
            return std::string(buffer.data(), bytes);
        }
        
        /**
         * @fn	Any FileTransfer::readLine(IPCMessage::SmartType msg)
         *
         * @tag sync
         *
         * @brief	��ȡһ��,һ�����4096���ַ�������������ֵ���ܻ�ȡ�������ݣ��ο�
         * 			{@link readSome=FileStream.readSome}.
         *
         * @return	#String.
         * @example
         *
         ```
        	include('FileStream');
        	var filestream = new FileStream('manifest.json');
        	while(!filestream.eof()){
        		console.log(filestream.readLine());
        	}
        	filestream.close();
         ```
         */
        
        Any readLine(IPCMessage::SmartType msg) {
            if (!m_filestream) {
                return "";
            }
            
            return m_filestream->read_line();
        }
        
        /**
         * @fn	Any FileTransfer::write(IPCMessage::SmartType msg)
         * @tag sync
         * @brief	���ļ���д���ַ���.
         *
         * @param	#String ��Ҫд�������.
         *
         * @return	#Boolean true �ɹ�/false ʧ��.
         * @example
         *
         ```
        	 include('FileStream');
        	 var filestream = new FileStream('manifest2.json');
        	 console.assert(filestream.write('1234567890') == true);
        	 filestream.remove();
         ```
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
         *
         * @tag sync
         *
         * @brief	��һ���ļ�������׷�ӵ���ǰ�ļ���.
         *
         * @param	#String �ļ�·��
         *
         * @return	#Boolean true �ɹ�/false ʧ��.
         *
         * @example
         *
         ```
        	include('FileStream');
        	var filestream = new FileStream('manifest2.json', 2);
        	filestream.append('manifest.json');
        	filestream.close();
        	console.log(filestream.size());
        	filestream.remove();
         ```
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
        
        
        // ����ǰ�ļ�׷�ӵ���һ���ļ���ȥ
        Any appendTo(IPCMessage::SmartType msg) {
            return Undefined();
        }
        
        /**
         * @fn	Any FileTransfer::close(IPCMessage::SmartType msg)
         * @tag sync
         * @brief	�ر��ļ����رպ����ٵ�������API�����ļ�.
         *
         *
         * @return	��.
         *
         * @see open=FileStream.open
         *
         * @example
         *
         ```
        		include('FileStream');
        		var filestream = new FileStream('manifest.json');
        		filestream.close();
        
        		console.assert(filestream.isOpened() == false);
         ```
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
         * @fn	Any FileTransfer::isOpened(IPCMessage::SmartType msg)
         *
         * @tag sync
         *
         * @brief	�ж��ļ��Ƿ��.
         *
         * @return	#Boolean.
         * @example
         *
         ```
        	include('FileStream');
        	var filestream = new FileStream('manifest.json');
        	console.assert(filestream.isOpened() == true);
        
        	filestream.close();
        	console.assert(filestream.isOpened() == false);
         ```
         */
        
        Any isOpened(IPCMessage::SmartType msg) {
            if (!m_filestream) {
                return false;
            }
            
            return m_filestream->is_open();
            
        }
        
        /**
         * @fn	Any FileTransfer::size(IPCMessage::SmartType msg)
         * @tag sync
         * @brief	��ȡ�ļ���С.
         *
         * @return	#Int.
         * @example
         *
         ```
        	include('FileStream');
        	var filestream = new FileStream('manifest.json');
        	console.log(filestream.size());
        
        	var filestream2 = new FileStream('manifest2.json');
        	console.assert(filestream.size() == 0);
        
        	filestream2.write('1234567890');
        	console.assert(filestream.size() == 10);
        
        	filestream2.remove();
         ```
         */
        
        Any size(IPCMessage::SmartType msg) {
            if (!m_file) {
                amo::path p(m_filename);
                m_file.reset(new amo::file(p));
            }
            
            return (int)m_file->size();
        }
        
        /**
         * @fn	Any FileTransfer::Remove(IPCMessage::SmartType msg)
         * @tag sync static
         * @brief ɾ���ļ�.
         *
         * @param #String �ļ�·��.
         *
         * @return	#Boolean.
         * @example
         *
         ```
        	include('FileStream');
        	var filestream = new FileStream('manifest2.json');
        	filestream.write('33');
        	// �ļ���ռ�ã��޷�ɾ��
        	console.assert(FileStream.Remove('manifest2.json') == false);
        	filestream.close();
        	// ����ļ�ռ�ã�����ɾ��
        	console.assert(FileStream.Remove('manifest2.json') == true);
         ```
         */
        
        Any Remove(IPCMessage::SmartType msg) {
            amo::string strPath(msg->getArgumentList()->getString(0), true);
            amo::path p(strPath);
            return p.remove();
        }
        
        
        /**
        * @fn	Any FileTransfer::remove(IPCMessage::SmartType msg)
        * @tag sync
        * @brief ɾ����ǰ�ļ�.
        *
        * @return	#Boolean.
        * @example
        *
        ```
        	include('FileStream');
        	// �Զ�д��ʽ�򿪣�����ļ������ڣ��ᴴ���ļ�
        	var filestream = new FileStream('manifest2.json');
        	console.assert(filestream.remove() == true);
        	// ��ֻ����ʽ�򿪣�����ļ������ڣ��򲻻ᴴ���ļ�
        	var filestream2 = new FileStream('manifest2.json', 1);
        	console.assert(filestream.remove() == false);
        ```
        */
        
        Any remove(IPCMessage::SmartType msg) {
            close(msg);
            amo::path p(m_filename);
            return  p.remove();
        }
        
        /**
         * @fn	Any FileTransfer::eof(IPCMessage::SmartType msg)
         *
         * @brief	�ж��Ƿ��Ѷ�ȡ���ļ�ĩβ.
         *
         *
         * @return	#Boolean true ĩβ/ false ��ĩβ.
         * @example
         *
         ```
        	include('FileStream');
        	var filestream = new FileStream('manifest.json');
        	filestream.readAll(); // readAll����Ӱ���ڲ��ļ�ָ��λ��
        	console.assert(filestream.eof() ==false);
        	while(!filestream.eof()){
        		console.log(filestream.readSome(100));
        	}
        	console.assert(filestream.eof() == true);
        
         ```
         */
        
        Any eof(IPCMessage::SmartType msg) {
            if (!m_filestream) {
                return true;
            }
            
            bool bRetval =  m_filestream->eof();
            return bRetval;
        }
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(FileTransfer, RunnableTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(Remove, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(read, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(readAll, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(readSome, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(readLine, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(write, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(append, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(appendTo, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(close, TransferFuncNormal | TransferExecNormal)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(size, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(remove, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(eof, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(open, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(isOpened, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    public:
    
        std::shared_ptr<amo::file> m_file;
        amo::string m_filename;
        std::shared_ptr<amo::filestream> m_filestream;
        int m_mode;
    };
}

#endif //LIBSEXT_FILETRANSFER_7B3B1E43_5470_4945_A0D5_0AFA9312172F_HPP__
