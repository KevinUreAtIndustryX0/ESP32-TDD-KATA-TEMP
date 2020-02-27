#include "gtest/gtest.h"
extern "C" {
    #include "network_controller.h"
    #include "esp_netif.h"
    #include "esp_event.h"
    #include "protocol_examples_common.h"
    #include "led_controller.h"
}
#include "fff.h"

DEFINE_FFF_GLOBALS;

DEFINE_FAKE_VALUE_FUNC(esp_err_t, esp_netif_init);
DEFINE_FAKE_VALUE_FUNC(esp_err_t, esp_event_loop_create_default);
DEFINE_FAKE_VALUE_FUNC(esp_err_t, example_connect);
FAKE_VOID_FUNC(set_led_state, uint8_t);

class init_network_fixture : public testing::Test{
    void TearDown() override {
        RESET_FAKE(esp_netif_init);
        RESET_FAKE(esp_event_loop_create_default);
        RESET_FAKE(example_connect);
        RESET_FAKE(set_led_state);
    }
};

TEST_F(init_network_fixture, init_calls_esp_netif_init) {
    init_network_controller();
    EXPECT_EQ(esp_netif_init_fake.call_count, 1);
}

TEST_F(init_network_fixture, init_calls_esp_event_loop_create_default) {
    init_network_controller();
    EXPECT_EQ(esp_event_loop_create_default_fake.call_count, 1);
}

TEST_F(init_network_fixture, init_calls_example_connect) {
    init_network_controller();
    EXPECT_EQ(example_connect_fake.call_count, 1);
}

TEST_F(init_network_fixture, init_calls_set_led_on) {
    init_network_controller();
    EXPECT_EQ(set_led_state_fake.call_count, 1);
    EXPECT_EQ(set_led_state_fake.arg0_history[0], LED_ON);
}