#ifndef EMBEDDED_CRAFTSMANSHIP_DRIVER_GPIO_H
#define EMBEDDED_CRAFTSMANSHIP_DRIVER_GPIO_H

#include "fff.h"
#include <stdint.h>

#define GPIO_NUM_25 25
#define GPIO_NUM_26 26
#define GPIO_NUM_27 27
#define GPIO_MODE_OUTPUT 0

DECLARE_FAKE_VALUE_FUNC(int, gpio_set_level, uint8_t, uint8_t)
DECLARE_FAKE_VALUE_FUNC(int, gpio_pad_select_gpio, uint8_t)
DECLARE_FAKE_VALUE_FUNC(int, gpio_set_direction, uint8_t, uint8_t)

#endif
