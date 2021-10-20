// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LIBEXT_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LIBEXT_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef LIBEXT_EXPORTS
#define LIBEXT_API __declspec(dllexport)
#else
#define LIBEXT_API __declspec(dllimport)
#endif


#include "transfer/ClassTransfer.hpp"

extern "C" {
    LIBEXT_API bool registerTransfer(std::shared_ptr<amo::TransferRegister> info);
}
