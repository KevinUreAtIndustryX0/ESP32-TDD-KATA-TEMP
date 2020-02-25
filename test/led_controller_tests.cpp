#include "gtest/gtest.h"
extern "C" {
    #include "led_controller.h"
    #include "board.h"
}
#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(board_led_operation, uint8_t, uint8_t);

typedef struct {
    enum Color color;
    int expected_red;
    int expected_green;
    int expected_blue;
} test_setup;

test_setup tests_to_run[8]= {
    (test_setup){.color = BLACK, .expected_red = LED_OFF, .expected_green = LED_OFF, .expected_blue = LED_OFF },
    (test_setup){.color = RED, .expected_red = LED_ON, .expected_green = LED_OFF, .expected_blue = LED_OFF },
    (test_setup){.color = GREEN, .expected_red = LED_OFF, .expected_green = LED_ON, .expected_blue = LED_OFF },
    (test_setup){.color = YELLOW, .expected_red = LED_ON, .expected_green = LED_ON, .expected_blue = LED_OFF },
    (test_setup){.color = BLUE, .expected_red = LED_OFF, .expected_green = LED_OFF, .expected_blue = LED_ON },
    (test_setup){.color = MAGENTA, .expected_red = LED_ON, .expected_green = LED_OFF, .expected_blue = LED_ON },
    (test_setup){.color = CYAN, .expected_red = LED_OFF, .expected_green = LED_ON, .expected_blue = LED_ON },
    (test_setup){.color = WHITE, .expected_red = LED_ON, .expected_green = LED_ON, .expected_blue = LED_ON }
};

class MyTestSuite : public testing::TestWithParam<test_setup> {
    void TearDown() {
        RESET_FAKE(board_led_operation);
    }
};

TEST_P(MyTestSuite, set_color_works_for_color){
    test_setup currentSetup = (test_setup)GetParam();
    set_led_color(currentSetup.color);
    EXPECT_EQ(board_led_operation_fake.call_count, 3);
    EXPECT_EQ(board_led_operation_fake.arg0_history[0], LED_R);
    EXPECT_EQ(board_led_operation_fake.arg1_history[0], currentSetup.expected_red);
    EXPECT_EQ(board_led_operation_fake.arg0_history[1], LED_G);
    EXPECT_EQ(board_led_operation_fake.arg1_history[1], currentSetup.expected_green);
    EXPECT_EQ(board_led_operation_fake.arg0_history[2], LED_B);
    EXPECT_EQ(board_led_operation_fake.arg1_history[2], currentSetup.expected_blue);
}

INSTANTIATE_TEST_SUITE_P(try_all_colors, MyTestSuite, testing::ValuesIn(tests_to_run));
