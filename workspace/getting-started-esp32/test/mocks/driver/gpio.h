#ifndef _MOCK_GPIO_H_
#define _MOCK_GPIO_H_

#include <stdint.h>
#include "fff.h"

#define GPIO_NUM_23 23
#define HIGH 1
#define LOW 0

DECLARE_FAKE_VALUE_FUNC(int, gpio_set_level, uint8_t, uint8_t)
DECLARE_FAKE_VALUE_FUNC(int, gpio_pad_select_gpio, uint8_t)
DECLARE_FAKE_VALUE_FUNC(int, gpio_set_direction, uint8_t, uint8_t)

#endif