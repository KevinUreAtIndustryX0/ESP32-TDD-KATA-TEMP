#include "networkController.h"
#include "protocol_examples_common.h"
#include "esp_tls.h"
#include "esp_http_client.h"
#include "ledController.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "esp_log.h"

#define MAX_HTTP_RECEIVE_BUFFER 4096

void initNetworkController(void) {
    esp_netif_init();
    esp_event_loop_create_default();

    setLedState(LED_ON);
    example_connect();
    setLedState(LED_OFF);
}

esp_err_t _httpEventHandler(esp_http_client_event_t* clientEvent) {
    return ESP_OK;
}

void getJson() {
    char* buffer = (char*)malloc(MAX_HTTP_RECEIVE_BUFFER + 1);
    esp_http_client_config_t clientConfig = {
        .url = "http://postman-echo.com/get?foo1=bar1&foo2=bar2",
        .event_handler = _httpEventHandler,
    };

    esp_http_client_handle_t clientHandler = esp_http_client_init(&clientConfig);

    esp_err_t err;
    if((err = esp_http_client_open(clientHandler, 0)) != ESP_OK) {
        ESP_LOGE("OUR_APP", "failed to open http client connection");
        free(buffer);
        return;
    }
    
    int contentLength = esp_http_client_fetch_headers(clientHandler);
    int totalReadLength = 0, read_len;
    if(totalReadLength < contentLength && contentLength <= MAX_HTTP_RECEIVE_BUFFER) {
        read_len = esp_http_client_read(clientHandler, buffer, contentLength);
        buffer[read_len] = 0;
    }
    ESP_LOGI("OUR_APP", "data: %s", buffer);
    free(buffer);
}

