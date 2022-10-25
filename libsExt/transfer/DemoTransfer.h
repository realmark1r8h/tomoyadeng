// Created by amoylel on 11/24/2017.
// Copyright (c) 2017 amoylel All rights reserved.

#ifndef AMO_DEMOTRANSFER_H__
#define AMO_DEMOTRANSFER_H__




#include <transfer/RunnableTransfer.hpp>
#include <amo/singleton.hpp>


// ��򵥵���չ����Ҫ�ṩ���½ӿ�
//namespace amo {
//	class DemoTransfer
//		: public RunnableTransfer
//		, public amo::singleton<DemoTransfer> {
//	public:
//		DemoTransfer();
//		Any onCreateClass(IPCMessage::SmartType msg) override;
//		virtual std::string getClass() const override;
//		virtual Transfer* getInterface(const std::string& name) override;
//
//		Any foo(IPCMessage::SmartType msg);
//
//		AMO_CEF_MESSAGE_TRANSFER_BEGIN(DemoTransfer, RunnableTransfer)
//			AMO_CEF_MESSAGE_TRANSFER_FUNC(foo, TransferFuncNormal | TransferExecNormal)
//			AMO_CEF_MESSAGE_TRANSFER_END()
//
//	};
//}

//
//// Transfer����
//enum TransferType {
//    TransferUnknown = -1,
//    TransferClass,						//��
//    TransferObject						//����
//};
//
//// ���߳�֧��
//enum TransferMultiType {
//    TransferMultiUnkown = -1, //δ֪
//    TransferMultiSupport = 0 << 16,  // �����������߳���ִ�У�Ĭ�ϣ�
//    TransferMultiDisabled = 1 << 16, // ��ֹ���߳�ִ��
//};
//// JS���еĺ������ͣ�
//enum TransferFuncType {
//    TransferFuncUnknown = -1,					// δ֪
//    TransferFuncNormal = 0 << 8,				// ��ͨ����
//    TransferFuncStatic = 1 << 8,				// ��̬����
//    TransferFuncConstructor = 2 << 8,			// ���캯��
//    TransferFuncConstProperty = 3 << 8,			// �ྲ̬�������ԣ����ܱ���ֵ
//    TransferFuncClassProperty = 4 << 8,			// �����ԣ�����ͨ��.CLASS���ʸ�ֵ
//    TransferFuncMemberProperty = 5 << 8,		// �������ԣ����Ը�ֵ
//};
//
//// JS�ڵ���C++ʱ��ͬ������
//enum TransferExecType {
//    TransferExecUnknown = -1,	//δ֪
//    TransferExecNormal = 0,		//��ͨ
//    TransferExecSync = 1,		//ͬ��
//    TransferExecAsync = 2,		//�첽
//};



#define AMO_CONFIG_GETTER_SETTER4(item)\
	Any item (IPCMessage::SmartType msg) {\
		std::shared_ptr<AnyArgsList> args = msg->getArgumentList();\
		Any& val = args->getValue(0);\
		if (val.is<Nil>() || val.is<Undefined>()) {\
			return GetConfigValue < decltype(this-> m_##item ) > (this-> m_##item );\
		} else {\
			return SetConfigValue < decltype(this-> m_##item ) > (this-> m_##item , val);\
		}\
	}

namespace amo {
    class DemoTransfer
        : public RunnableTransfer
        , public amo::singleton<DemoTransfer> {
    public:
    
        DemoTransfer();
        Any onCreateClass(IPCMessage::SmartType msg) override;
        virtual std::string getClass() const override;
        virtual Transfer* getInterface(const std::string& name) override;
        
        Any add(IPCMessage::SmartType msg);
        Any sub(IPCMessage::SmartType msg);
        Any mul(IPCMessage::SmartType msg);
        Any div(IPCMessage::SmartType msg);
        Any sleepForWeakup(IPCMessage::SmartType msg);
        
        
        AMO_CONFIG_GETTER_SETTER(staticTestID)
        AMO_CONFIG_GETTER_SETTER(constStaticTestID)
        AMO_CONFIG_GETTER_SETTER(memberTestID)
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(DemoTransfer, RunnableTransfer)
        // ��Ա����
        AMO_CEF_MESSAGE_TRANSFER_FUNC(add, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(sub, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(mul, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(div, TransferFuncNormal | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(sleepForWeakup, TransferFuncNormal | TransferExecNormal)
        
        AMO_CEF_MESSAGE_TRANSFER_FUNC(staticTestID,
                                      TransferFuncClassProperty | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(constStaticTestID,
                                      TransferFuncConstProperty | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(memberTestID,
                                      TransferFuncMemberProperty | TransferExecSync)
                                      
        AMO_CEF_MESSAGE_TRANSFER_END()
        
    private:
        int m_staticTestID;
        int m_constStaticTestID;
        int m_memberTestID;
    };
}


#endif // AMO_DEMOTRANSFER_H__