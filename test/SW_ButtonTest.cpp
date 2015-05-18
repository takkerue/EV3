#include <iostream>
#include "CppUTest/CommandLineTestRunner.h"
#include "../SW_Button.h"

// テストグループ定義 TEST_GROUP(group)
TEST_GROUP(swButtonTestGroup) {
};

// テストケース TEST(group, name)
TEST(swButtonTestGroup, getTest) {
}

int main(int argc, char** argv) {
  // テストランナー
  return RUN_ALL_TESTS(argc, argv);
}
