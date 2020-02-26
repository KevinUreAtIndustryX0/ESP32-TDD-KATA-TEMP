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

class init_network_fixture : public testing::Test{
    void TearDown() override {
        RESET_FAKE(esp_netif_init);
        RESET_FAKE(esp_event_loop_create_default);
    }
};

TEST_F(init_network_fixture, calls_esp_netif_init) {
    init_network_controller();
    EXPECT_EQ(esp_netif_init_fake.call_count, 1);
    RESET_FAKE(esp_netif_init);
}

TEST_F(init_network_fixture, calls_esp_event_loop_create_default) {
    init_network_controller();
    EXPECT_EQ(esp_event_loop_create_default_fake.call_count, 1);
    RESET_FAKE(esp_event_loop_create_default);
}