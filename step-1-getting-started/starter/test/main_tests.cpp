#include "gtest/gtest.h"
extern "C" {
    #include "main.h"
    #include "app_logic.h"
}
#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(app_init);
FAKE_VOID_FUNC(app_do_work);

TEST(app_main, calls_logic_init_and_logic_do_work) {
    app_main();

    // FAIL() << "TODO: Delete this line, uncomment the following lines, and re-run the tests";
    EXPECT_EQ(app_init_fake.call_count, 1);
    EXPECT_EQ(app_do_work_fake.call_count, 1);
    RESET_FAKE(app_init);
    RESET_FAKE(app_do_work);
}