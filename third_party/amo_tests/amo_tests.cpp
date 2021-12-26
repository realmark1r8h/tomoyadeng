// amo_tests.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <gtest/gtest.h>
#include <amo/logger.hpp>
#ifdef _DEBUG
#pragma comment(lib, "gtestd.lib")
#pragma comment(lib, "gtest_maind.lib")
#else
#pragma comment(lib, "gtest.lib")
#pragma comment(lib, "gtest_main.lib")
#endif


int Add(int a, int b) {
    return a + b;
}

TEST(testCase, test0) {
    EXPECT_EQ(14, 14);//EXPECT_EQ是比较两个值是否相等
}
//
//TEST(testCase, test1)
//{
//	/*本用例不过*/
//	EXPECT_EQ(6, Add(5, 7));
//}
//
//TEST(testCase, test2)
//{
//	EXPECT_EQ(28, Add(10, 18));
//}

int _tmain(int argc, _TCHAR* argv[]) {
    amo::path::set_work_path_to_app_path();
    amo::log::initialize(true, true);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}