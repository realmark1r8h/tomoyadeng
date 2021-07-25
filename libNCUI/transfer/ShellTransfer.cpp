#include "stdafx.h"

#include "transfer/ShellTransfer.h"

#include <shellapi.h>
#include <amo/path.hpp>

namespace amo {

    ShellTransfer::ShellTransfer()
        : ClassTransfer("shell") {
    }
    
    Any ShellTransfer::exec(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        amo::string strOperation(args->getString(0), true);
        amo::string strFileName(args->getString(1), true);
        amo::string strParam(args->getString(2), true);
        amo::string stsrDir(args->getString(3), true);
        int nShowCmd = SW_SHOWNORMAL;
        
        if (args->isValid(4)) {
            nShowCmd = args->getInt(4);
        }
        
        return (int)::ShellExecuteA(NULL,
                                    strOperation.c_str(),
                                    strFileName.c_str(),
                                    strParam.c_str(),
                                    stsrDir.c_str(),
                                    nShowCmd);
    }
    
    
    Any ShellTransfer::open(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->getArgumentList();
        amo::string strFileName(args->getString(0), true);
        amo::string strParam(args->getString(1), true);
        amo::string stsrDir(args->getString(3), true);
        return (int)::ShellExecuteA(NULL,
                                    "open",
                                    strFileName.c_str(),
                                    strParam.c_str(),
                                    stsrDir.c_str(),
                                    SW_SHOWNORMAL);
    }
    
    Any ShellTransfer::print(IPCMessage::SmartType msg) {
        amo::string str(msg->getArgumentList()->getString(0), true);
        return (int)::ShellExecuteA(NULL,
                                    "print",
                                    str.c_str(),
                                    NULL,
                                    NULL,
                                    SW_SHOWNORMAL);
    }
    
    Any ShellTransfer::showItemInFolder(IPCMessage::SmartType msg) {
        amo::string str(msg->getArgumentList()->getString(0), true);
        amo::string strParam("/e, /select, ");
        strParam += str;
        return (int)::ShellExecuteA(NULL,
                                    "open",
                                    "explorer.exe",
                                    strParam.c_str(),
                                    NULL,
                                    SW_SHOWNORMAL);
    }
    
    int ShellTransfer::StringToShowCmd(const amo::string& str) {
        if (str == "SW_HIDE") {
            //隐藏窗口，活动状态给令一个窗口
            return SW_HIDE;
        } else if (str == "SW_MINIMIZE") {
            //最小化窗口，活动状态给令一个窗口
            return SW_MINIMIZE;
        } else if (str == "SW_RESTORE") {
            //用原来的大小和位置显示一个窗口，同时令其进入活动状态
            return SW_RESTORE;
        } else if (str == "SW_SHOW") {
            //用当前的大小和位置显示一个窗口，同时令其进入活动状态
            return SW_SHOW;
        } else if (str == "SW_SHOWMAXIMIZED") {
            //最大化窗口，并将其激活
            return SW_SHOWMAXIMIZED;
        } else if (str == "SW_SHOWMINIMIZED") {
            //最小化窗口，并将其激活
            return SW_SHOWMINIMIZED;
        } else if (str == "SW_SHOWMINNOACTIVE") {
            //最小化一个窗口，同时不改变活动窗口
            return SW_SHOWMINNOACTIVE;
        } else if (str == "SW_SHOWNA") {
            //用当前的大小和位置显示一个窗口，不改变活动窗口
            return SW_SHOWNA;
        } else if (str == "SW_SHOWNOACTIVATE") {
            //用最近的大小和位置显示一个窗口，同时不改变活动窗口
            return SW_SHOWNOACTIVATE;
        } else if (str == "SW_SHOWNORMAL") {
            //与RESTORE相同
            return SW_SHOWNORMAL;
        } else {
            return SW_SHOWNORMAL;
        }
        
    }
    
}