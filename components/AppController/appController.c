#include "appController.h"
#include <stdio.h>
#include "esp_log.h"
#include "ledController.h"
#include "networkController.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"

void mainLoop(void){
    getJson();
}

void init(void){
    ESP_LOGI("Example", "Hello World");
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        nvs_flash_init();
    }     
    initLedController();
    initNetworkController();

}