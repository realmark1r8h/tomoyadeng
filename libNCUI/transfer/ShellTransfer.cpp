#include "stdafx.h"

#include "transfer/ShellTransfer.h"

#include <shellapi.h>
#include <amo/path.hpp>

namespace amo {

    ShellTransfer::ShellTransfer()
        : ClassTransfer("shell") {
    }
    
    Any ShellTransfer::exec(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        amo::string strOperation(args->GetString(0), true);
        amo::string strFileName(args->GetString(1), true);
        amo::string strParam(args->GetString(2), true);
        amo::string stsrDir(args->GetString(3), true);
        int nShowCmd = SW_SHOWNORMAL;
        
        if (args->IsValid(4)) {
            nShowCmd = args->GetInt(4);
        }
        
        return (int)::ShellExecuteA(NULL,
                                    strOperation.c_str(),
                                    strFileName.c_str(),
                                    strParam.c_str(),
                                    stsrDir.c_str(),
                                    nShowCmd);
    }
    
    
    Any ShellTransfer::open(IPCMessage::SmartType msg) {
        std::shared_ptr<AnyArgsList> args = msg->GetArgumentList();
        amo::string strFileName(args->GetString(0), true);
        amo::string strParam(args->GetString(1), true);
        amo::string stsrDir(args->GetString(3), true);
        return (int)::ShellExecuteA(NULL,
                                    "open",
                                    strFileName.c_str(),
                                    strParam.c_str(),
                                    stsrDir.c_str(),
                                    SW_SHOWNORMAL);
    }
    
    Any ShellTransfer::print(IPCMessage::SmartType msg) {
        amo::string str(msg->GetArgumentList()->GetString(0), true);
        return (int)::ShellExecuteA(NULL,
                                    "print",
                                    str.c_str(),
                                    NULL,
                                    NULL,
                                    SW_SHOWNORMAL);
    }
    
    Any ShellTransfer::showItemInFolder(IPCMessage::SmartType msg) {
        amo::string str(msg->GetArgumentList()->GetString(0), true);
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
            //���ش��ڣ��״̬����һ������
            return SW_HIDE;
        } else if (str == "SW_MINIMIZE") {
            //��С�����ڣ��״̬����һ������
            return SW_MINIMIZE;
        } else if (str == "SW_RESTORE") {
            //��ԭ���Ĵ�С��λ����ʾһ�����ڣ�ͬʱ�������״̬
            return SW_RESTORE;
        } else if (str == "SW_SHOW") {
            //�õ�ǰ�Ĵ�С��λ����ʾһ�����ڣ�ͬʱ�������״̬
            return SW_SHOW;
        } else if (str == "SW_SHOWMAXIMIZED") {
            //��󻯴��ڣ������伤��
            return SW_SHOWMAXIMIZED;
        } else if (str == "SW_SHOWMINIMIZED") {
            //��С�����ڣ������伤��
            return SW_SHOWMINIMIZED;
        } else if (str == "SW_SHOWMINNOACTIVE") {
            //��С��һ�����ڣ�ͬʱ���ı�����
            return SW_SHOWMINNOACTIVE;
        } else if (str == "SW_SHOWNA") {
            //�õ�ǰ�Ĵ�С��λ����ʾһ�����ڣ����ı�����
            return SW_SHOWNA;
        } else if (str == "SW_SHOWNOACTIVATE") {
            //������Ĵ�С��λ����ʾһ�����ڣ�ͬʱ���ı�����
            return SW_SHOWNOACTIVATE;
        } else if (str == "SW_SHOWNORMAL") {
            //��RESTORE��ͬ
            return SW_SHOWNORMAL;
        } else {
            return SW_SHOWNORMAL;
        }
        
    }
    
}