// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� EXT_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// EXT_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef EXT_EXPORTS
#define EXT_API __declspec(dllexport)
#else
#define EXT_API __declspec(dllimport)
#endif


#include "transfer/ClassTransfer.hpp"

extern "C" {
    EXT_API bool registerTransfer(std::shared_ptr<amo::TransferRegister> info);
}

namespace amo {

    class ExtTransfer : public ClassTransfer {
    public:
    
        ExtTransfer();
        ~ExtTransfer();
        
    public:
        AMO_CEF_MESSAGE_TRANSFER_BEGIN(ExtTransfer, ClassTransfer)
        
        
        AMO_CEF_MESSAGE_TRANSFER_END()
        
        
    };
}
