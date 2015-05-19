#include <iostream>
#include "CppUTest/CommandLineTestRunner.h"
#include "../SW_Button.h"

// テストグループ定義 TEST_GROUP(group)
TEST_GROUP(swButtonTestGroup) {
};

// テストケース TEST(group, name)
TEST(swButtonTestGroup, initialButtonState) {
    SW_Button_init();
    BYTES_EQUAL(false, SW_Button_isPressed(StartButton));
    BYTES_EQUAL(false, SW_Button_isPressed(ResetButton));
}

int main(int argc, char** argv) {
  // テストランナー
  return RUN_ALL_TESTS(argc, argv);
}
