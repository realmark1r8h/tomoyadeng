// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� LIBRESOURCE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// LIBRESOURCE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef LIBRESOURCE_EXPORTS
#define LIBRESOURCE_API __declspec(dllexport)
#else
#define LIBRESOURCE_API __declspec(dllimport)
#endif

// �����Ǵ� libResource.dll ������
class LIBRESOURCE_API ClibResource {
public:
    ClibResource(void);
    // TODO:  �ڴ�������ķ�����
};

extern LIBRESOURCE_API int nlibResource;

LIBRESOURCE_API int fnlibResource(void);

#include <string>

extern "C" {
    LIBRESOURCE_API int readAsText(const char* path, char** retval);
}
