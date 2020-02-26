make a new component named led_controller

include "driver/gpio.h"

define led pin, on and off states

priv_req driver in cmake

define an init function

write a mock for driver/gpio

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
    #include <stdint.h>

define blank init_led

write test for init_led to call each of those once
