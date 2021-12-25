// bit7z_test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <bit7z/include/bit7z.hpp>
#include <amo/path.hpp>
int main() {
    amo::path::set_work_path_to_app_path();
    using namespace bit7z;
    Bit7zLibrary lib(L"7z.dll");
    BitCompressor compressor(lib, BitFormat::Zip);
    
    //std::vector<std::wstring> files = { L"path/to/file1.jpg", L"path/to/file2.pdf" };
    ////creates a simple zip archive of two files
    //compressor.compressFiles(files, L"output_archive.zip");
    
    //compresses a directory
    compressor.setPassword(L"password");
    compressor.setVolumeSize(1000000);
    compressor.compressDirectory(L"doc/", L"dir_archive.zip");
    
    //creates an encrypted zip archive of two files
    
    //compressor.compressFiles(files, L"protected_archive.zip");
    //
    ////compresses a single file into a buffer
    //vector<byte_t> buffer;
    //BitCompressor compressor2(lib, BitFormat::BZip2);
    //compressor2.compressFile(files[0], buffer);
    return 0;
}

