// ncui.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "ncui.h"
#include "node.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�:
#include <windows.h>

#include "handler/NodeProcessHandler.h"




XNODE_API void setMessageQueue(const std::string& strName) {
    amo::NodeProcessHandler::setMessageQueue(strName);
}
