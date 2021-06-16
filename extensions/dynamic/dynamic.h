// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� DYNAMIC_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// DYNAMIC_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef DYNAMIC_EXPORTS
#define DYNAMIC_API __declspec(dllexport)
#else
#define DYNAMIC_API __declspec(dllimport)
#endif

#include "transfer/ClassTransfer.hpp"

extern "C" {
    DYNAMIC_API int fndynamic(void);
    DYNAMIC_API bool registerTransfer(int nBrowserID, std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fn);
}

namespace amo {



    class DynamicTransfer : public ClassTransfer {
    public:
    
        DynamicTransfer();
        ~DynamicTransfer();
        amo::Any foo1(IPCMessage::SmartType anyMessage);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(DynamicTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(foo1, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
    };
}