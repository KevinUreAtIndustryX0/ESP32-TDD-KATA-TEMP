#include "networkController.h"
#include "protocol_examples_common.h"
#include "esp_tls.h"
#include "esp_http_client.h"
#include "ledController.h"
#include "esp_netif.h"
#include "esp_event.h"

void initNetworkController(void) {
    esp_netif_init();
    esp_event_loop_create_default();

    setLedState(LED_ON);
    example_connect();
    setLedState(LED_OFF);
}