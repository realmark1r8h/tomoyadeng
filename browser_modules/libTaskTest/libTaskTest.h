// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LIBTASKTEST_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LIBTASKTEST_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef LIBTASKTEST_EXPORTS
#define LIBTASKTEST_API __declspec(dllexport)
#else
#define LIBTASKTEST_API __declspec(dllimport)
#endif


#include "transfer/ClassTransfer.hpp"

AMO_CLASS_TRANSFER_DECLARE(LIBTASKTEST_API)
