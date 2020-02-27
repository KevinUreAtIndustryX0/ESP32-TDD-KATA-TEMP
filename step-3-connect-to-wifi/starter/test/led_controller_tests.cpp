#include "gtest/gtest.h"
extern "C" {
    #include "led_controller.h"
    #include "driver/gpio.h"
}
#include "fff.h"

DEFINE_FFF_GLOBALS;

DEFINE_FAKE_VALUE_FUNC(int, gpio_set_level, uint8_t, uint8_t)
DEFINE_FAKE_VALUE_FUNC(int, gpio_pad_select_gpio, uint8_t)
DEFINE_FAKE_VALUE_FUNC(int, gpio_set_direction, uint8_t, uint8_t)

TEST(init_led_controller, calls_gpio) {
    init_led_controller();
    
    EXPECT_EQ(gpio_pad_select_gpio_fake.call_count, 1);
    EXPECT_EQ(gpio_pad_select_gpio_fake.arg0_history[0], LED_PIN);
    
    EXPECT_EQ(gpio_set_direction_fake.call_count, 1);
    EXPECT_EQ(gpio_set_direction_fake.arg0_history[0], LED_PIN);
    EXPECT_EQ(gpio_set_direction_fake.arg1_history[0], GPIO_MODE_OUTPUT);

    EXPECT_EQ(gpio_set_level_fake.call_count, 1);
    EXPECT_EQ(gpio_set_level_fake.arg0_history[0], LED_PIN);
    EXPECT_EQ(gpio_set_level_fake.arg1_history[0], LED_ON);

    RESET_FAKE(gpio_set_level);
    RESET_FAKE(gpio_pad_select_gpio);
    RESET_FAKE(gpio_set_direction);
}