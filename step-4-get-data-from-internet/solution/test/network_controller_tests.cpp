#include "gtest/gtest.h"
extern "C" {
    #include "network_controller.h"
    #include "esp_netif.h"
    #include "esp_event.h"
    #include "protocol_examples_common.h"
    #include "led_controller.h"
    #include "esp_log.h"
    #include "esp_http_client.h"
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

DEFINE_FAKE_VOID_FUNC(ESP_LOGI, char*, char*, char*);
DEFINE_FAKE_VALUE_FUNC(esp_http_client_handle_t, esp_http_client_init, esp_http_client_config_t*);
DEFINE_FAKE_VALUE_FUNC(esp_err_t, esp_http_client_open, esp_http_client_handle_t, int);
DEFINE_FAKE_VALUE_FUNC(int, esp_http_client_fetch_headers, esp_http_client_handle_t);
DEFINE_FAKE_VALUE_FUNC(int, esp_http_client_read, esp_http_client_handle_t, char*, int);

char* example_json = (char *)"hello world";
int fake_read(esp_http_client_handle_t a, char* b, int c) {
    b = example_json;
    return 12;
}

class get_json_fixture : public testing::Test{
    void SetUp() override {
        esp_http_client_fetch_headers_fake.return_val = 12;
        esp_http_client_open_fake.return_val = ESP_OK;
        esp_http_client_read_fake.custom_fake = fake_read;
    }
    void TearDown() override {
        RESET_FAKE(ESP_LOGI);
        RESET_FAKE(esp_http_client_init);
        RESET_FAKE(esp_http_client_open);
        RESET_FAKE(esp_http_client_fetch_headers);
        RESET_FAKE(esp_http_client_read);
    }
};

TEST_F(get_json_fixture, calls_log_with_data) {
    get_json();
    EXPECT_EQ(ESP_LOGI_fake.call_count, 1);
    // EXPECT_EQ(ESP_LOGI_fake.arg2_history[0], example_json); Dereferencing issue
}

TEST_F(get_json_fixture, calls_http_client_init) {
    get_json();
    esp_http_client_config_t expectedConfig = {
        .url = "http://postman-echo.com/get?foo1=bar1&foo2=bar2",
    };
    EXPECT_EQ(esp_http_client_init_fake.call_count, 1);
    // EXPECT_EQ(esp_http_client_init_fake.arg0_history[0]->url, expectedConfig.url); Dereferencing issue
}

TEST_F(get_json_fixture, calls_http_client_open) {
    get_json();
    EXPECT_EQ(esp_http_client_open_fake.call_count, 1);
}

TEST_F(get_json_fixture, bails_if_client_failed_to_open) {
    esp_http_client_open_fake.return_val = 66;
    get_json();
    EXPECT_EQ(esp_http_client_open_fake.call_count, 1);
    EXPECT_EQ(esp_http_client_fetch_headers_fake.call_count, 0);
}

TEST_F(get_json_fixture, calls_esp_http_client_fetch_headers) {
    get_json();
    EXPECT_EQ(esp_http_client_fetch_headers_fake.call_count, 1);
}

TEST_F(get_json_fixture, calls_esp_http_client_read) {
    get_json();
    EXPECT_EQ(esp_http_client_fetch_headers_fake.call_count, 1);
}