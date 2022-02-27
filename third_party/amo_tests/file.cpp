#include <amo/file.hpp>
#include <amo/uuid.hpp>

#include <gtest/gtest.h>

amo::astring file1 = amo::uuid().to_string() + ".txt";
amo::astring file2 = amo::uuid().to_string() + ".txt";
amo::astring file3 = amo::astring("C:\\") + amo::uuid().to_string() + ".txt";
amo::astring file4 = amo::astring("C:/") + amo::uuid().to_string() + ".txt";
amo::astring file5 = "C:/windows";

amo::file f1(file1);
amo::file f2(file2);
amo::file f3(file3);
amo::file f4(file4);
amo::file f5(file5);

TEST(file, is_exists) {

    std::cout << file1 << std::endl;
    std::cout << file2 << std::endl;
    std::cout << file3 << std::endl;
    std::cout << file4 << std::endl;
    std::cout << file5 << std::endl;
    
    EXPECT_EQ(false, f1.is_exists());
    EXPECT_EQ(false, f2.is_exists());
    EXPECT_EQ(false, f3.is_exists());
    EXPECT_EQ(false, f4.is_exists());
    
    auto stream = f1.get_filestream(std::ios::out);
    stream->write("111111111111");
    stream->close();
    EXPECT_EQ(true, f1.is_exists());
    
}

TEST(file, is_file) {
    EXPECT_EQ(true, f1.is_file());
    EXPECT_EQ(false, f5.is_file());
}


TEST(file, is_picture) {
    EXPECT_EQ(false, f1.is_picture());
}

TEST(file, file_type) {
    EXPECT_EQ("txt", f1.file_type());
    EXPECT_EQ("txt", f1.file_type(true));
}


TEST(file, copy_to) {

    EXPECT_EQ(true, f1.copy_to(file2));
    EXPECT_EQ(true, f2.is_exists());
    
    EXPECT_EQ(true, f1.copy_to(file3));
    EXPECT_EQ(true, f3.is_exists());
    f3.remove();
    f2.remove();
}


TEST(file, move_to) {

    EXPECT_EQ(true, f1.move_to(file2));
    EXPECT_EQ(false, f1.is_exists());
    EXPECT_EQ(true, f2.is_exists());
    
    EXPECT_EQ(true, f2.copy_to(file1));
    
    EXPECT_EQ(true, f2.move_to(file3));
    EXPECT_EQ(false, f2.is_exists());
    EXPECT_EQ(true, f3.is_exists());
}


TEST(file, rename) {

    EXPECT_EQ(true, f1.rename(file2));
    EXPECT_EQ(false, f3.rename(file4));
    
}


TEST(file, remove) {
    EXPECT_EQ(true, f1.remove());
    EXPECT_EQ(true, f2.remove());
    EXPECT_EQ(true, f3.remove());
    EXPECT_EQ(true, f4.remove());
}
