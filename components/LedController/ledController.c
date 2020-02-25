#include "ledController.h"

void setLedState(uint8_t state){
    gpio_set_level(LED_PIN, state);
}

void ledControllerInit() {
    gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, LED_OFF);
}