#include "gtest/gtest.h"
extern "C" {
    #include "led_controller.h"
    #include "network_controller.h"
    #include "app_logic.h"
}
#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(init_led_controller);
FAKE_VOID_FUNC(init_network_controller);

TEST(app_init, calls_init_led_controller) {
    app_init();
    EXPECT_EQ(init_led_controller_fake.call_count, 1);
    EXPECT_EQ(init_network_controller_fake.call_count, 1);
    RESET_FAKE(init_led_controller);
    RESET_FAKE(init_network_controller);
}