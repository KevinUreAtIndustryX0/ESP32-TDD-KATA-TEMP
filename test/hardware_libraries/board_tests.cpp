#include "gtest/gtest.h"
extern "C" {
    #include "board.h"
    #include "driver/gpio.h"
}
#include "fff.h"

DEFINE_FFF_GLOBALS;

DEFINE_FAKE_VALUE_FUNC(int, gpio_set_level, uint8_t, uint8_t)
DEFINE_FAKE_VALUE_FUNC(int, gpio_pad_select_gpio, uint8_t)
DEFINE_FAKE_VALUE_FUNC(int, gpio_set_direction, uint8_t, uint8_t)

class BoardTestFixture : public testing::Test {
    void TearDown() override {
        RESET_FAKE(gpio_set_level);
        RESET_FAKE(gpio_pad_select_gpio);
        RESET_FAKE(gpio_set_direction);
    }
};

TEST_F(BoardTestFixture, board_init_sets_pins){
    board_init();
    EXPECT_EQ(gpio_pad_select_gpio_fake.call_count, 3);
    EXPECT_EQ(gpio_pad_select_gpio_fake.arg0_history[0], LED_R);
    EXPECT_EQ(gpio_pad_select_gpio_fake.arg0_history[1], LED_G);
    EXPECT_EQ(gpio_pad_select_gpio_fake.arg0_history[2], LED_B);
    EXPECT_EQ(gpio_set_direction_fake.call_count, 3);
    EXPECT_EQ(gpio_set_direction_fake.arg0_history[0], LED_R);
    EXPECT_EQ(gpio_set_direction_fake.arg0_history[1], LED_G);
    EXPECT_EQ(gpio_set_direction_fake.arg0_history[2], LED_B);
    EXPECT_EQ(gpio_set_direction_fake.arg1_history[0], GPIO_MODE_OUTPUT);
    EXPECT_EQ(gpio_set_direction_fake.arg1_history[1], GPIO_MODE_OUTPUT);
    EXPECT_EQ(gpio_set_direction_fake.arg1_history[2], GPIO_MODE_OUTPUT);
    EXPECT_EQ(gpio_set_level_fake.call_count, 3);
    EXPECT_EQ(gpio_set_level_fake.arg0_history[0], LED_R);
    EXPECT_EQ(gpio_set_level_fake.arg0_history[1], LED_G);
    EXPECT_EQ(gpio_set_level_fake.arg0_history[2], LED_B);
    EXPECT_EQ(gpio_set_level_fake.arg1_history[0], LED_OFF);
    EXPECT_EQ(gpio_set_level_fake.arg1_history[1], LED_OFF);
    EXPECT_EQ(gpio_set_level_fake.arg1_history[2], LED_OFF);
}

TEST_F(BoardTestFixture, board_led_operation_sets_pin_on){
    board_led_operation(2,LED_ON);
    EXPECT_EQ(gpio_set_level_fake.call_count, 1);
    EXPECT_EQ(gpio_set_level_fake.arg0_history[0], 2);
    EXPECT_EQ(gpio_set_level_fake.arg1_history[0], LED_ON);
}

TEST_F(BoardTestFixture, board_led_operation_sets_pin_off){
    board_led_operation(3,LED_OFF);
    EXPECT_EQ(gpio_set_level_fake.call_count, 1);
    EXPECT_EQ(gpio_set_level_fake.arg0_history[0], 3);
    EXPECT_EQ(gpio_set_level_fake.arg1_history[0], LED_OFF);
}