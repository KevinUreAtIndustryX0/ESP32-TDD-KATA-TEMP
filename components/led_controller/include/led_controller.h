#ifndef _LED_CTRL_H_
#define _LED_CTRL_H_

enum Color{
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7
};

void set_led_color(enum Color color);

#endif
