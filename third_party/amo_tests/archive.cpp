#include <iostream>

#include <amo/archive.hpp>
#include <gtest/gtest.h>


//TEST(archive, addFile) {
//    amo::archive zip("D:\\ddd.zip");
//    //zip.addFile("text.txt", "D:/test/aaa.txt");
//    //system("7z.exe a D:\\ddd.zip -sitext.txt < D:/test/.txt");
//
//    //EXPECT_EQ(true, zip.addFile("D:/test/aaa.txt", "text.txt"));
//    EXPECT_EQ(true, zip.addFile("D:/test/"));
//
//    //EXPECT_EQ(true, zip.addFile("DDD/text.txt", "D:/test/aaa.txt"));
//}

TEST(archive, addData) {
    amo::archive zip("D:\\ddd1.zip");
    //zip.addFile("text.txt", "D:/test/aaa.txt");
    //system("7z.exe a D:\\ddd.zip -sitext.txt < D:/test/.txt");
    
    EXPECT_EQ(true, zip.addFile("text.txt", "D:/test/aaa.txt"));
    
    std::string ss = "fire in the hole";
    EXPECT_EQ(true, zip.addData("abc.txt", ss));
    
    //EXPECT_EQ(true, zip.addFile("DDD/text.txt", "D:/test/aaa.txt"));
}
//
//TEST(archive, test) {
//    amo::archive zip("D:\\video.zip.001");
//    bool bOk = zip.test();
//
//    EXPECT_EQ(true, bOk);
//}
//
//TEST(archive, updateFile) {
//    amo::archive zip("D:\\ddd.zip");
//    bool bOk = zip.updateFile("D:/test/aaa.txt");
//
//    EXPECT_EQ(true, bOk);
//}
//
//
//TEST(archive, removeFile) {
//    amo::archive zip("D:\\ddd.zip");
//    bool bOk = zip.removeFile("D:/test/aaa.txt");
//
//    EXPECT_EQ(true, bOk);
//}