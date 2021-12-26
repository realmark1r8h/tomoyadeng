#include <iostream>

#include <amo/archive.hpp>
#include <gtest/gtest.h>


TEST(archive, addFile) {
    amo::archive zip("D:\\ddd.zip");
    bool bOk =  zip.addFile("D:/test/aaa.txt");
    
    
    EXPECT_EQ(true, bOk);
}

TEST(archive, test) {
    amo::archive zip("D:\\video.zip.001");
    bool bOk = zip.test();
    
    EXPECT_EQ(true, bOk);
}

TEST(archive, updateFile) {
    amo::archive zip("D:\\ddd.zip");
    bool bOk = zip.updateFile("D:/test/aaa.txt");
    
    EXPECT_EQ(true, bOk);
}


TEST(archive, removeFile) {
    amo::archive zip("D:\\ddd.zip");
    bool bOk = zip.removeFile("D:/test/aaa.txt");
    
    EXPECT_EQ(true, bOk);
}