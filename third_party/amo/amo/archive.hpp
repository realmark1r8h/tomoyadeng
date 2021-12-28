// Created by amoylel on 07/02/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef AMO_ARCHIVE_66CE452B_183B_4825_BBF5_04945F2EC3F8_HPP__
#define AMO_ARCHIVE_66CE452B_183B_4825_BBF5_04945F2EC3F8_HPP__

#include <string>
#include <memory>
#include <amo/process.hpp>
#include <amo/logger.hpp>
#include <amo/shell.hpp>

namespace amo {
    class archive : public log_object {
    public:
        archive(const std::string& archivePath, const std::string& password = "")
            : m_path(archivePath)
            , m_password(password) {
            
        }
        
        bool addFile(const std::string& entryName, const std::string& filePath) {
            auto pProcess = createProcess("a");
            pProcess->show(true);
            pProcess->addArgs("-si" + entryName);
            pProcess->addArgs("<");
            pProcess->start(filePath);
            
            
            return parseReult(pProcess->getResult());
            
            /*amo::shell shell("7z.exe");
            shell.addArgs("a");
            shell.addArgs(m_path);
            shell.addArgs("-si" + entryName);
            shell.addArgs("<");
            shell.addArgs(filePath);
            return shell.open();*/
            
        }
        
        bool addFile(const std::string& filePath) {
            auto pProcess = createProcess("a");
            
            pProcess->start(filePath);
            auto result =   pProcess->getResult();
            return parseReult(result);
        }
        
        bool updateFile(const std::string& filePath) {
            auto pProcess = createProcess("a");
            
            pProcess->start(filePath);
            auto result = pProcess->getResult();
            return parseReult(result);
        }
        
        bool removeFile(const std::string& filePath) {
            auto pProcess = createProcess("d");
            
            pProcess->start(filePath);
            auto result = pProcess->getResult();
            return parseReult(result);
        }
        
        bool extractFile(const std::string& filePath) {
        
        }
        
        bool test() {
            auto pProcess = createProcess("t");
            
            pProcess->start();
            auto result = pProcess->getResult();
            return parseReult(result);
        }
        
    private:
        bool parseReult(std::shared_ptr<amo::process::result> result) {
            if (!result->isSuccess()) {
                return false;
            }
            
            std::vector<amo::string> message =
                result->removeBlankMessage()->getResultMessage();
                
            // 这里可以判断以下具体是要好多
            if (message.size() < 5) {
                return false;
            }
            
            for (auto& p : message) {
                if (p.find("Everything is Ok") != -1) {
                    return true;
                }
            }
        }
        std::shared_ptr<amo::process> createProcess(const std::string& args = "") {
            std::shared_ptr<amo::process> pProcess(new process("7z.exe"));
            
            pProcess->setLogger(getLogger());
            
            
            if (!args.empty()) {
                pProcess->addArgs(args);
            }
            
            pProcess->addArgs(m_path);
            
            if (!m_password.empty()) {
                pProcess->addArgs("-p");
                pProcess->addArgs(m_password);
            }
            
            m_process = pProcess;
            
            return pProcess;
        }
    private:
        std::string m_path;
        std::string m_password;
        std::shared_ptr<amo::process> m_process;
    };
}


#endif //AMO_ARCHIVE_66CE452B_183B_4825_BBF5_04945F2EC3F8_HPP__