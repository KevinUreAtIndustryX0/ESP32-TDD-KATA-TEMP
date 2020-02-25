#include "appController.h"
#include <stdio.h>
#include "esp_log.h"
#include "ledController.h"
#include "networkController.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void mainLoop(void){
}

void init(void){
    ESP_LOGI("Example", "Hello World");
    initLedController();
    initNetworkController();
}