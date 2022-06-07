// libResource.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "libResource.h"
#include <fstream>
#include <sstream>

#include <amo/path.hpp>

// ���ǵ���������һ��ʾ��
LIBRESOURCE_API int nlibResource = 0;

// ���ǵ���������һ��ʾ����
LIBRESOURCE_API int fnlibResource(void) {
    return 42;
}



// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� libResource.h
ClibResource::ClibResource() {
    return;
}

LIBRESOURCE_API int readAsText(const char* path, char** retval) {

    amo::path p = amo::path::fullPathInAppDir("doc");
    p.append(path);
    
    std::fstream ifs(p.c_str(), std::ios::in | std::ios::binary);
    
    if (!ifs.is_open()) {
        return 0;
    }
    
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    
    static std::string str;
    str = buffer.str();
    *retval = (char*)str.c_str();
    
    return str.size();
}