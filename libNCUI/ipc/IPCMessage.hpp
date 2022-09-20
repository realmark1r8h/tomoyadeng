// Created by amoylel on 06/13/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_CONSTANTS_HPP__
#define AMO_CONSTANTS_HPP__

#include <string>


#define WM_CUSTOM_MESSAGE_BEGIN (WM_USER + 1000)
// ����ȫ��
#define WM_ENTER_FULLSCREEN (WM_CUSTOM_MESSAGE_BEGIN + 1)
// �뿪ȫ��
#define WM_LEAVE_FULLSCREEN (WM_CUSTOM_MESSAGE_BEGIN + 2)
// ���ڴ����ɹ�
#define WM_WINDOW_CREATED (WM_CUSTOM_MESSAGE_BEGIN + 3)
// �������ɹ�
#define WM_IPC_READY (WM_CUSTOM_MESSAGE_BEGIN + 4)

namespace amo {

    /*! @brief	֪ͨ�����̹ܵ��Ѿ�׼���ã����Խ��йܵ�ͨ����. */
    static const std::string MSG_IPC_READY = "IPCReady";
    /*! @brief	������Ⱦ���̿ͻ���Pipe����Ⱦ���̷��ͣ������̽��մ���. */
    static const std::string MSG_CREATE_PIPE_CLIENT	 = "CreatePipeClient";
    /*! @brief	��־��Ϣ. */
    static const std::string MSG_LOG_MESSAGE		 = "LogMessage";
    /*! @brief	�����Ƿ�����ǰ������. */
    static const std::string MSG_ENABLE_BACK_FORWORD = "EnableBackForword";
    /*! @brief	ֱ�ӵ���C++��JS. */
    static const std::string MSG_NATIVE_EXECUTE		 = "NativeExecute";
    /*! @brief	ͬ������C++��JS. */
    static const std::string MSG_NATIVE_SYNC_EXECUTE = "NativesyncExecute";
    /*! @brief	�첽����C++��JS. */
    static const std::string MSG_NATIVE_ASYNC_EXECUTE = "NativeasyncExecute";
    /*! @brief	֪ͨ�Է�����ͬ������. */
    static const std::string MSG_PROCESS_SYNC_EXECUTE = "ProcesssyncExecute";
    /*! @brief	���㷢���ı�ʱ����. */
    static const std::string MSG_FOCUSED_NODE_CHANGED = "focusedNodeChanged";
    
    static const std::string MSG_BROWSER_SETTINGS = "browserSettings";
    
    /*! @brief	Ĭ�Ϲܵ���С. */
    static const int DefaultPipeSize = 2000000;
    
    /*! @brief	��Ⱦ���̹ܵ�ǰ׺. */
    static const std::string RendererPipePrefix = "render_pipe_name_";
    /*! @brief	�����̹ܵ�ǰ׺. */
    static const std::string BrowserPipePrefix = "browser_pipe_name_";
    
    /*! @brief	�ܵ���Ϣͷ��. */
    static const char PipeMessageHeader = 'a';
    /*! @brief	�ܵ���Ϣβ��. */
    static const char PipeMessageTail = 'z';
    
    // ��Ϣ����������λ��
    class IPCArgsPosInfo {
    public:
        /*! @brief	��Ϣ��������ʼλ��. */
        const static int MessageArgs = 0;
        /*! @brief	��Ϣ��������λ��. */
        const static int FuncName = 10;
        
        /*! @brief	�Զ����������ʼλ��. */
        const static int CustomArgs = 11;
        
        /*! @brief	�Զ����¼�����. */
        const static int CustomEventName = 18;
        
        /*! @brief	Transfer����λ��. */
        const static int TransferName = 11;
        /*! @brief	TransferIDλ��. */
        const static int TransferID = 12;
        
        /*! @brief	��Ҫ�����¼���EventEmittter ID. */
        const static int EventObjectID = 14;
        /*! @brief	JavaScript ������ �൱���Զ�����������һ��. */
        const static int JsFuncName = 13;
        
        
        /*! @brief	��̬����. */
        const static int DllName = 11;
        /*! @brief	��̬�⺯����. */
        const static int DllFuncName = 12;
        /*! @brief	��̬�⺯������ֵ����. */
        const static int DllRetalType = 13;
        
        /** @brief	Ҫ���߳���ִ�е�Transfer Name. */
        const static int ThreadTransferName = 15;
        
        /** @brief	Ҫ���߳���ִ�е�Transfer ID. */
        const static int ThreadTransferID = 16;
        
        /** @brief	Ҫ���߳���ִ�еĺ�����. */
        const static int ThreadTransferFuncName = 17;
        
        /** @brief	����̵��ñ�־1��ʾֻ�ڵ�ǰ������ִ�У�0��ʾ����̵���. */
        const static int CrossProcessFlag = 22;
        
        /*! @brief	�첽����ʱ�ص�����λ��. */
        const static int AsyncCallback = 23;
        /*! @brief	��Ϣ�б��б���BrowserID��λ��. */
        const static int BrowserID = 24;
        /*! @brief	��Ϣ�б��б���FrameID��λ��. */
        const static int FrameID = 25;
        /*! @brief	��Ϣ�б��б�������б��ȵ�λ��. */
        const static int ArgsLength = 26;
        /*! @brief	��ϢID. */
        const static int MessageID = 27;
        /*! @brief	�����б���󳤶�[0,16]. */
        const static int MaxLength = 28;
    };
    
    
}
#endif // AMO_CONSTANTS_HPP__