#include "network_controller.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "protocol_examples_common.h"
#include "led_controller.h"

void init_network_controller() {
    esp_netif_init();
    esp_event_loop_create_default();
    example_connect();
    set_led_state(LED_ON);
}
