#include "networkController.h"
#include "protocol_examples_common.h"
#include "esp_tls.h"
#include "esp_http_client.h"
#include "ledController.h"

void initNetworkController(void) {
    setLedState(LED_ON);
    example_connect();
    setLedState(LED_OFF);
}