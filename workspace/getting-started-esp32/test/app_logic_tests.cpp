#include "gtest/gtest.h"
extern "C" {
    #include "led_controller.h"
    #include "network_controller.h"
    #include "app_logic.h"
    #include "nvs_flash.h"
}
#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(init_led_controller);
FAKE_VOID_FUNC(init_network_controller);
DEFINE_FAKE_VALUE_FUNC(esp_err_t, nvs_flash_init)
DEFINE_FAKE_VALUE_FUNC(esp_err_t, nvs_flash_erase)

class app_init_fixture : public testing::Test{
    void TearDown() override {
        RESET_FAKE(nvs_flash_init);
        RESET_FAKE(nvs_flash_erase);
        RESET_FAKE(init_led_controller);
        RESET_FAKE(init_network_controller);
    }
};

TEST_F(app_init_fixture, calls_init_led_controller) {
    app_init();
    EXPECT_EQ(init_led_controller_fake.call_count, 1);
}

TEST_F(app_init_fixture, calls_init_network_controller) {
    app_init();
    EXPECT_EQ(init_network_controller_fake.call_count, 1);
}

TEST_F(app_init_fixture, calls_nvs_flash_init) {
    nvs_flash_init_fake.return_val = ESP_OK;
    app_init();
    EXPECT_EQ(nvs_flash_init_fake.call_count, 1);
}

TEST_F(app_init_fixture, calls_nvs_erase_and_then_flash_if_no_free_pages) {
    nvs_flash_init_fake.return_val = ESP_ERR_NVS_NO_FREE_PAGES;
    app_init();
    EXPECT_EQ(nvs_flash_init_fake.call_count, 2);
    EXPECT_EQ(nvs_flash_erase_fake.call_count, 1);
}

TEST_F(app_init_fixture, calls_nvs_erase_and_then_flash_if_new_version_found) {
    nvs_flash_init_fake.return_val = ESP_ERR_NVS_NEW_VERSION_FOUND;
    app_init();
    EXPECT_EQ(nvs_flash_init_fake.call_count, 2);
    EXPECT_EQ(nvs_flash_erase_fake.call_count, 1);
}