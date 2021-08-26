// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� RENDEREREXTENSION_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// RENDEREREXTENSION_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef RENDEREREXTENSION_EXPORTS
#define RENDEREREXTENSION_API __declspec(dllexport)
#else
#define RENDEREREXTENSION_API __declspec(dllimport)
#endif
#include "transfer/ClassTransfer.hpp"
#include <functional>

extern "C" {
    RENDEREREXTENSION_API bool registerTransfer(int nBrowserID, std::function<void(int, std::shared_ptr<amo::ClassTransfer>)> fn);
}

namespace amo {



    class RendererExtensionTransfer : public ClassTransfer {
    public:
    
        RendererExtensionTransfer();
        amo::Any foo1(IPCMessage::SmartType msg);
        
        
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(RendererExtensionTransfer, ClassTransfer)
        AMO_CEF_MESSAGE_TRANSFER_FUNC(foo1, TransferFuncStatic | TransferExecSync)
        AMO_CEF_MESSAGE_TRANSFER_END()
    private:
    
    };
}