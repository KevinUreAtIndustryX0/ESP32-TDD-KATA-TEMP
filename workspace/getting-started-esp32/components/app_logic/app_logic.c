#include "app_logic.h"
#include <stdio.h>
#include "led_controller.h"
#include "network_controller.h"
#include "nvs_flash.h"
#include "esp_err.h"

void app_init(void) {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }     

    init_led_controller();
    init_network_controller();
}

void app_do_work(void) {
}
