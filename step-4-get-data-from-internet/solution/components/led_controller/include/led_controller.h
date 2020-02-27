#ifndef _LED_CONTROLLER_H_
#define _LED_CONTROLLER_H_

#include "driver/gpio.h"
#include <stdint.h>

#define LED_PIN GPIO_NUM_23
#define LED_ON 1
#define LED_OFF 0

void init_led_controller(void);

void set_led_state(uint8_t state);

#endif
