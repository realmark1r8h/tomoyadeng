// Created by amoylel on 07/10/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_IPCNODEV8HANDLER_H__
#define AMO_IPCNODEV8HANDLER_H__



#include <string>
#include <amo/unordered_map.hpp>
#include "transfer/ClassTransfer.hpp"

namespace amo {

    // JS �첽����C++ ����ص�����������
    class IPCNodeV8Handler   : public ClassTransfer {
    
    public:
        IPCNodeV8Handler();
        
        virtual ~IPCNodeV8Handler();
        
        // �첽����C++����ص�������
        amo::Any asyncExecuteResult(IPCMessage::SmartType msg);
        
        // ����JS����
        amo::Any runJSFunction(IPCMessage::SmartType msg);
        
        // ����JSƬ��
        amo::Any runJsFragment(IPCMessage::SmartType msg);
        
        // �����¼�
        amo::Any triggerEvent(IPCMessage::SmartType msg);
        
        // �������е�ǰBrowser������Frameע����¼� ��ָ��Browser�� ��ָ��Frame
        amo::Any emitEventAllFrame(IPCMessage::SmartType msg);
        
        // ��ȡ��������
        int getArgsSize(std::shared_ptr<AnyArgsList> args) const;
        
        // for transfer
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(IPCNodeV8Handler, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(asyncExecuteResult, 0)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(runJSFunction, 0)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(runJsFragment, 0)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(triggerEvent, 0)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(emitEventAllFrame, 0)
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
        
    protected:
    
    
    };
}



#endif // AMO_IPCNODEV8HANDLER_H__
