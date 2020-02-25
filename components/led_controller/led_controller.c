#include "board.h"
#include "led_controller.h"


void set_led_color(enum Color color)
{
    if ((int)color & RED) {
        board_led_operation(LED_R, LED_ON);
    } else {
        board_led_operation(LED_R, LED_OFF);
    }
    if ((int)color & GREEN) {
        board_led_operation(LED_G, LED_ON);
    } else {
        board_led_operation(LED_G, LED_OFF);
    }
    if ((int)color & BLUE) {
        board_led_operation(LED_B, LED_ON);
    } else {
        board_led_operation(LED_B, LED_OFF);
    }
}
