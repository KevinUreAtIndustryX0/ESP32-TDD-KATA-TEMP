#include "network_controller.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "protocol_examples_common.h"
#include "led_controller.h"
#include "esp_http_client.h"
#include "esp_log.h"

void init_network_controller() {
    esp_netif_init();
    esp_event_loop_create_default();
    example_connect();
    set_led_state(LED_ON);
}

esp_err_t _httpEventHandler(esp_http_client_event_t* clientEvent) {
    return ESP_OK;
}

void get_json(void) {
    ESP_LOGI("network", "hello: %s", "world");
}