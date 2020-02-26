#include "gtest/gtest.h"
extern "C" {
    #include "network_controller.h"
    #include "esp_netif.h"
    #include "esp_event.h"
}
#include "fff.h"

DEFINE_FFF_GLOBALS;

DEFINE_FAKE_VALUE_FUNC(esp_err_t, esp_netif_init);
DEFINE_FAKE_VALUE_FUNC(esp_err_t, esp_event_loop_create_default);

TEST(init_network_controller, calls_esp_netif_init) {
    app_init();
    EXPECT_EQ(esp_netif_init_fake.call_count, 1);
    RESET_FAKE(esp_netif_init);
}

TEST(init_network_controller, calls_esp_event_loop_create_default) {
    app_init();
    EXPECT_EQ(esp_event_loop_create_default_fake.call_count, 1);
    RESET_FAKE(esp_event_loop_create_default);
}