#include "app_logic.h"
#include <stdio.h>
#include "esp_log.h"
#include "led_controller.h"

void app_init(void) {
    init_led_controller();
}

void app_do_work(void) {
}
