#include "driver/gpio.h"
#include "board.h"

struct _led_state led_state[3] = {
    { LED_OFF, LED_R, "red"   },
    { LED_OFF, LED_G, "green" },
    { LED_OFF, LED_B, "blue"  },
};

void board_led_operation(uint8_t pin, uint8_t onoff)
{
    gpio_set_level(pin, onoff);
}

static void board_led_init(void)
{
    for (int i = 0; i < 3; i++) {
        gpio_pad_select_gpio(led_state[i].pin);
        gpio_set_direction(led_state[i].pin, GPIO_MODE_OUTPUT);
        gpio_set_level(led_state[i].pin, LED_OFF);
    }
}

void board_init(void)
{
    board_led_init();
}
