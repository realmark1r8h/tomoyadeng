#include <iostream>

#include <amo/path.hpp>
#include <gtest/gtest.h>


TEST(path, exists) {
    amo::path p;
    EXPECT_EQ(false, p.exists());
    
    EXPECT_EQ(true, amo::path::fullAppName().exists());
}
TEST(path, to_string) {
    amo::path p;
    EXPECT_EQ("", p.to_string());
}

TEST(path, is_directory) {

    amo::path p("D:\\video3");
    p.create_directory();
    EXPECT_EQ(p.is_directory(), true);
}

TEST(path, create_directory) {
    amo::path p("D:\\测试目录");
    EXPECT_EQ(p.create_directory(), true);
    
    /*{
    	amo::path p("测试目录");
    	EXPECT_EQ(p.create_directory(), true);
    }
    
    {
    	amo::path p("..\\测试目录11");
    	EXPECT_EQ(p.create_directory(), true);
    }*/
    
}

//TEST(path, copy_to) {
//    amo::path p("D:/test1.xlsx");
//    amo::path p2("D:/text2.xlsx");
//    EXPECT_EQ(p.copy_to(p2), true);
//
//    amo::path p3("D:/测试目录");
//    amo::path p4("D:/中文目录2");
//    EXPECT_EQ(p3.copy_to(p4), true);
//}

TEST(path, move_to) {
    amo::path p1("D:/test1.xlsx");
    amo::path p2("E:/text2.xlsx");
    EXPECT_EQ(p1.move_to(p2), true);
    
    amo::path p3("D:/测试目录");
    amo::path p4("E:/中文目录2");
    EXPECT_EQ(p3.move_to(p4), true);
}

TEST(path, remove) {
    amo::path p1("D:/test1.xlsx");
    EXPECT_EQ(p1.remove(), true);
    
    amo::path p3("D:/测试目录");
    EXPECT_EQ(p3.remove_all(), true);
}
//int main(int argc, char** argv) {
//    const LPCSTR MUSIC_FILE_EXT_NAME[] =
//    { ".mp3", ".wma", ".aac", ".ogg", ".wav", ".m4a", ".amr", ".ape", ".cue", ".flac", ".mkv" };
//    amo::path path("D:/a.txt -d 23 -c 32");
//    amo::path p1("D:");
//    amo::path p2("video/");
//    p1.combine(p2);
//    p1.skip_root();
//    p1.strip_path();
//    path.remove_args();
//    amo::path p3("C:\\Users\\Default\\AppData\\Local\\Microsoft\\Windows\\History");
//    amo::path p4("\\Windows\\History");
//    p3.unexpand_env_strings();
//    p3.find_on_path(p4);
//    amo::string ssb = p3.find_next_component();
//    ssb = p3.find_next_component();
//    amo::path p5("D:/video/oh.mkv");
//    bool bOk = p3.find_suffix_array((const char**)MUSIC_FILE_EXT_NAME, 11);
//    bool bOk1 = p5.find_suffix_array((const char**)MUSIC_FILE_EXT_NAME, 11);
//
//    amo::path p6("D:\\a\\b");
//    amo::path p7("D:\\a\\c");
//    p6.relative_path_to(p7);
//    amo::path p8("A:\\name_1\\.\\name_2\\..\\name_3");
//    p8.canonicalize();
//    amo::path p9("C:\\Users\\Default\\AppData\\Local\\Microsoft\\Windows\\History\\ / : * ? \" < > | ");
//    p9.cleanup_spec();
//    p9.get_short_path_name();
//
//
//
//    amo::path p10("D:\\cef-Out");
//    amo::path p11("E:\\cef2-Out");
//
//    int i = 0;
//    std::vector<amo::string> oSet;
//    oSet.push_back(".obj");
//    oSet.push_back(".pch");
//    oSet.push_back(".pdb");
//    oSet.push_back(".cc");
//    p10.transfer([&](amo::path & p) {
//        if (p.find_suffix_array(oSet)) {
//            return;
//        }
//
//        ++i;
//        amo::path p1 = p.relative_path_to_c(p10);
//        amo::path p2 = p11.append_c(p1);
//        bool bOk = p.copy_to(p2);
//    }, true);
//    std::cout << i << std::endl;
//    return 0;
//}