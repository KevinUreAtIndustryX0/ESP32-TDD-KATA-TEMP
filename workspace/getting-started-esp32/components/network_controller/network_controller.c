#include "network_controller.h"
#include "esp_netif.h"
#include "esp_event.h"

void init_network_controller() {
    esp_netif_init();
    esp_event_loop_create_default();
}
