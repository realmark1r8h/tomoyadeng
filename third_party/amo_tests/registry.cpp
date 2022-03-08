#include <iostream>

#include <gtest/gtest.h>
#include <amo/registry.hpp>

TEST(archive, test) {
    amo::registry reg(HKEY_CURRENT_USER);
    DWORD ss =
        reg.read<DWORD>("Software\\Microsoft\\Windows\\CurrentVersion\\RADAR",
                        "DisplayInterval");
                        
    reg.write("Software\\Microsoft\\Windows\\CurrentVersion\\Run",
              "TEST_TEST", "D:\\aaa.exe");
              
    reg.remove("Software\\Microsoft\\Windows\\CurrentVersion\\Run",
               "TEST_TEST");
               
               
    {
        amo::registry reg(HKEY_CURRENT_USER);
        /* DWORD ss =
        	 reg.read<DWORD>("Software\\JCW",
        					 "DisplayInterval");*/
        reg.create("Software\\JCW");
        reg.write("Software\\JCW",
                  "DisplayInterval", 3, true);
    }
    
    
    
    //zip.addFile("text.txt", "D:/test/aaa.txt");
    //system("7z.exe a D:\\ddd.zip -sitext.txt < D:/test/.txt");
    
    EXPECT_EQ(true,  ss == 1440);
    
    
    
    //EXPECT_EQ(true, zip.addFile("DDD/text.txt", "D:/test/aaa.txt"));
}