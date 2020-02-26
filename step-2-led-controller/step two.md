make a new component named led_controller

include "driver/gpio.h"

define led pin, on and off states

priv_req driver in cmake

define an init function

write a mock for driver/gpio
    `#include <stdint.h>`
    #include "fff.h"
    #define GPIO_NUM_23 23
    #define HIGH 1
    #define LOW 0
    #define GPIO_MODE_OUTPUT 0
    DECLARE_FAKE_VALUE_FUNC(int, gpio_set_level, uint8_t, uint8_t)
    DECLARE_FAKE_VALUE_FUNC(int, gpio_pad_select_gpio, uint8_t)
    DECLARE_FAKE_VALUE_FUNC(int, gpio_set_direction, uint8_t, uint8_t)

write a test for app_logic_init calling ledctrlr init

define init_led_controller in the C file
call it from app_logic
 - include led_controller.h
 - cmake requires led_controller

see green

write mocks for 
    gpio_pad_select_gpio();
    gpio_set_direction();
    gpio_set_level();
    `#include <stdint.h>`

define blank init_led

write test for init_led to call each of those once

see red

implement init

see green