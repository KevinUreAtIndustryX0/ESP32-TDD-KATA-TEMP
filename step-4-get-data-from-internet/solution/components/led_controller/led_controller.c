#include "led_controller.h"

void init_led_controller() {
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, LED_OFF);
}

void set_led_state(uint8_t state){
    gpio_set_level(LED_PIN, state);
}