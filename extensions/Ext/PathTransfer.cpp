#include "stdafx.h"
#include "PathTransfer.h"
#include <amo/string.hpp>
#include <amo/path.hpp>


namespace amo {

    PathTransfer::PathTransfer()
        : ClassTransfer("Path") {
        m_pPath.reset(new path());
    }
    
    PathTransfer::PathTransfer(const std::string& ansiPath)
        : ClassTransfer("Path") {
        
        m_pPath.reset(new path(ansiPath));
        
    }
    
    PathTransfer::~PathTransfer() {
    
    }
    
    Any PathTransfer::onCreateClass(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        std::string u8Path = args->getString(0);
        amo::string ansiPath(u8Path, true);
        std::shared_ptr<PathTransfer> pTransfer(new PathTransfer(ansiPath));
        
        pTransfer->registerFunction();
        addTransfer(pTransfer);
        return  pTransfer->getFuncMgr().toSimplifiedJson();
    }
    
    
    
    Any PathTransfer::toString(IPCMessage::SmartType msg) {
        amo::string ansiPath(m_pPath->c_str(), false);
        return ansiPath.to_utf8();
    }
    
    Any PathTransfer::isExsit(IPCMessage::SmartType msg) {
        return m_pPath->file_exists();
    }
    
    Any PathTransfer::append(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        amo::string ansiPath(args->getString(0), true);
        amo::path p(ansiPath);
        m_pPath->append(p);
        
        // ����this
        return getFuncMgr().toSimplifiedJson();
    }
    
    Any PathTransfer::removeFileSpec(IPCMessage::SmartType msg) {
        m_pPath->remove_file_spec();
        return getFuncMgr().toSimplifiedJson();
    }
    
    Any PathTransfer::getFullAppDir(IPCMessage::SmartType msg) {
        amo::string ansiPath = amo::path::getExeDir();
        IPCMessage::SmartType cloneMsg = msg->clone();
        cloneMsg->getArgumentList()->setValue(0, ansiPath.to_utf8());
        return onCreateClass(cloneMsg);
    }
    
    Any PathTransfer::getFullAppName(IPCMessage::SmartType msg) {
        amo::string ansiPath = amo::path::getFullExeName();
        IPCMessage::SmartType cloneMsg = msg->clone();
        cloneMsg->getArgumentList()->setValue(0, ansiPath.to_utf8());
        return onCreateClass(cloneMsg);
    }
    
    
}
