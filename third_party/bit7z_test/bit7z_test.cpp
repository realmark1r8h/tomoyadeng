// bit7z_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <amo/config.hpp>
#include <amo/path.hpp>

#include <bit7z/include/bit7z.hpp>


#include "../bit7z/include/archive.hpp"

void foo1() {
    using namespace bit7z;
    Bit7zLibrary lib(L"7z.dll");
    BitCompressor compressor(lib, BitFormat::Zip);
    compressor.open(L"D:/aaa.zip");
    //std::vector<std::wstring> files = { L"path/to/file1.jpg", L"path/to/file2.pdf" };
    ////creates a simple zip archive of two files
    //compressor.compressFiles(files, L"output_archive.zip");
    
    //compresses a directory
    compressor.setPassword(L"password");
    //compressor.setVolumeSize(1000000);
    //compressor.compressDirectory(L"doc/", L"archive.zip");
    compressor.compressFile(L"D:/test/aaa.txt", L"D:/aaa.zip");
    
    return;
}

void foo2() {
    using namespace bit7z;
    Archive zf("D:/bbb.zip", "123456");
    zf.open(Archive::NEW);
    
    //zf.addFile("D:/test/aaa.txt", "12312/dddd/23323\\2222");
    zf.addFile("D:/test/bbb.txt", "1111");
    //zf.addFile("D:/test/bbb.txt", "1111");
    ////zf.addDirectory("D:\\苏元海", "9527");
    //zf.commit();
    zf.addFile("D:/test/aaa.txt");
    zf.commit();
    /* zf.addFile("D:/test/bbb.txt");
     zf.commit();*/
    //zf.addData("", )
    zf.close();
}

void fileCallback(std::wstring fileName) {
}

void foo3() {
    using namespace bit7z;
    Bit7zLibrary lib(L"7z.dll");
    BitExtractor extractor(lib, BitFormat::Zip);
    extractor.setPassword(L"password");
    //extractor.setFileCallback()
    //extracts a simple archive
    extractor.extract(L"archive.zip.002", L"doc2/");
    
}
int main() {
    amo::path::set_work_path_to_app_path();
    
    foo2();
    return 0;
    //using namespace bit7z;
    //Bit7zLibrary lib(L"7z.dll");
    //
    //
    //
    //
    //BitExtractor extractor(lib, BitFormat::Zip);
    //extractor.setPassword(L"password");
    ////extracts a simple archive
    //extractor.extract(L"archive.zip.002", L"doc2/");
    
    
    
    //creates an encrypted zip archive of two files
    
    //compressor.compressFiles(files, L"protected_archive.zip");
    //
    ////compresses a single file into a buffer
    //vector<byte_t> buffer;
    //BitCompressor compressor2(lib, BitFormat::BZip2);
    //compressor2.compressFile(files[0], buffer);
    
    
    /*Archive zf("D:/archive.zip", "123456");
    zf.open(Archive::NEW);
    zf.addFile()*/
    return 0;
}

