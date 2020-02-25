#ifndef _LED_CONTROLLER_H_
#define _LED_CONTROLLER_H_

#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2

#define LED_ON  1
#define LED_OFF 0

void setLedState(uint8_t);

void ledControllerInit();

#endif
