#include "appController.h"
#include <stdio.h>
#include "esp_log.h"
#include "ledController.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void mainLoop(void){
    while (1) {
        setLedState(LED_ON);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        setLedState(LED_OFF);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void init(void){
    ESP_LOGI("Example", "Hello World");
    ledControllerInit();
}