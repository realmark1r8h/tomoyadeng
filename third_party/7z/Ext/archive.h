// Created by amoylel on 28/03/2018.
// Copyright (c) 2018 amoylel All rights reserved.

#ifndef LIB7Z_ARCHIVE_F8499230_346D_4B46_91DE_5F87D0B36211_H__
#define LIB7Z_ARCHIVE_F8499230_346D_4B46_91DE_5F87D0B36211_H__

#include <string>

namespace amo {
    class Archive {
    public:
        Archive(const std::string& archivePath, const std::string& password = "")
            : m_path(archivePath)
            , m_password(password) {
            
        }
        
        bool addFile(const std::string& filePath) {
            auto pProcess = createProcess("a");
            pProcess->start(filePath);
            auto result = pProcess->getResult();
            return parseReult(result);
        }
        
        bool addData(const std::string& entryName, const std::string& str) {
            return addData(entryName, str.c_str(), str.size());
        }
        
        bool addData(const std::string& entryName, const char* data, size_t size = 0) {
            if (size == 0) {
                size = strlen(data);
            }
            
            char tempDir[MAX_PATH] = { 0 };
            SHGetSpecialFolderPathA(NULL, tempDir, CSIDL_TEMPLATES, FALSE);
            amo::path p(tempDir);
            p.append(amo::uuid().to_string());
            std::ofstream ofs(p.c_str(), std::ios::out | std::ios::app);
            ofs.write(data, size);
            ofs.close();
            auto pProcess = createProcess("a");
            pProcess->addArgs("-tzip");
            pProcess->addArgs(std::string("-si") + entryName);
            pProcess->addArgs("<");
            pProcess->addArgs(p.c_str());
            pProcess->start();
            
            auto result = pProcess->getResult();
            p.remove();
            return parseReult(result);
        }
        
        bool addFile(const std::string& entryName, const std::string& filePath) {
            auto pProcess = createProcess("a");
            pProcess->addArgs("-si");
            pProcess->addArgs(entryName);
            pProcess->addArgs("<");
            pProcess->start(filePath);
            auto result = pProcess->getResult();
            return parseReult(result);
        }
        
        bool updateFile(const std::string& filePath) {
            auto pProcess = createProcess("u");
            pProcess->start(filePath);
            auto result = pProcess->getResult();
            return parseReult(result);
        }
        
        bool updateFile(const std::string& entryName, const std::string& filePath) {
            auto pProcess = createProcess("u");
            pProcess->addArgs("-si");
            pProcess->addArgs(entryName);
            pProcess->addArgs("<");
            pProcess->start(filePath);
            auto result = pProcess->getResult();
            return parseReult(result);
        }
        
        bool rename(const std::string& oldName, const std::string& newName) {
            auto pProcess = createProcess("rn");
            pProcess->addArgs(oldName);
            pProcess->addArgs(newName);
            pProcess->start();
            auto result = pProcess->getResult();
            return parseReult(result);
        }
        
        bool removeFile(const std::string& entryName) {
            auto pProcess = createProcess("d");
            
            pProcess->start(entryName);
            auto result = pProcess->getResult();
            return parseReult(result);
        }
        
        std::string readAsText(const std::string& entryName) {
            auto pProcess = createProcess("x");
            
            pProcess->start(entryName);
            auto result = pProcess->getResult();
            
            if (!result->isSuccess()) {
                return "";
            }
            
            return result->getData().to_string();
        }
        
        bool extract(const std::string& entryName, const std::string& outPath) {
            auto pProcess = createProcess("x");
            pProcess->addArgs("-y");
            pProcess->addArgs("-o");
            pProcess->addArgs(outPath);
            pProcess->start(entryName);
            auto result = pProcess->getResult();
            return parseReult(result);
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
            
            return false;
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



#endif //LIB7Z_ARCHIVE_F8499230_346D_4B46_91DE_5F87D0B36211_H__