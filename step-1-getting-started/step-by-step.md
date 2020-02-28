# Step-By-Step Tasks

- Open a terminal window to the folder `step-1-getting-started/starter`
- Run `vmDockerDev.sh` to put you in a docker container with all the tools
- From the docker `workdir` folder (default folder), run the `ll` command
- Verify the files `CMakeLists.txt  CmakeConfig.h.in  dockerDev.sh  runTests.sh  test  vmDockerDev.sh` exist.

*TODO*: Redo the above steps after `a cleanup script in esp32 repo` is done

- Create the following test in the test folder:

```
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

    FAIL() << "TODO: Delete this line, uncomment the following lines, and runWe shouldn't get here.";
    // EXPECT_EQ(app_init_fake.call_count, 1);
    // EXPECT_EQ(app_do_work_fake.call_count, 1);
    // RESET_FAKE(app_init);
    // RESET_FAKE(app_do_work);
}
```

- Run the test using the script `./runTests.sh`
- verify the error:
```
/workdir/test/main_tests.cpp:14:5: error: 'app_main' was not declared in this scope
     app_main();
     ^~~~~~~~
```
- Declare this function in `main.h` *TODO*: should we assume they know what this means?  Provide hint link?
- Re-run the tests
- Verify the error:
```
/workdir/test/main_tests.cpp:16: Failure
Failed
TODO: Delete this line, uncomment the following lines, and re-run the tests
[  FAILED  ] app_main.calls_logic_init_and_logic_do_work (0 ms)
[----------] 1 test from app_main (0 ms total)
```
- Re-run the tests
- Verify the error:
```
/workdir/test/main_tests.cpp:18: Failure
Expected equality of these values:
  app_do_work_fake.call_count
    Which is: 0
  1
[  FAILED  ] app_main.calls_logic_init_and_logic_do_work (1 ms)
[----------] 1 test from app_main (1 ms total)
```

This test intends to verify that we implemented a separation of concerns via the [Single Responsibility Principle (SRP)](https://blog.cleancoder.com/uncle-bob/2014/05/08/SingleReponsibilityPrinciple.html) for the following functionality:
    - Showing [semantic versioning](https://semver.org) information.
    - running any initilization code for the application via `app_init()`
    - running the business logic via `app_do_work()`

 - Declare these two functions in `components/app_logic.h`
 - Define these two functions in `components/app_logic.c` (with empty body)
 - Call these two functions in `main.c`.  First `app_init()` then `app_do_work()`

 Note that the tests do not cover the requirement that we call `app_init()` before `app_do_work()`

- Re-run the tests
- Verify tests pass

Since tests are green, we should be able to build and run the project.

- Execute the command `idf.py build`
- verify successful build

Now, let's flash the code to the ESP-32 and see what it does.

- Connect the ESP-32 your workstate using a micro-usb cable.
- Verify the red power light comes on.
- Execute the command `idf.py flash monitor`

The `flash` target will flash the code to the ESP-32 through the USB cable.

If flash fails, try *TODO*: copy from starter readme

The `monitor` target will relay the output from the program to the terminal through the USB cable.

- Verify the output:

```
I (289) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
Hello World (v0.0.0) (<build timestamp>)
```

Congratulations!  Now, let's log some information from our `app_init()` and `app_do_work()`

- Press `control-]` to exit the monitor and go back to your docker workdir.
- Add logging in `in app_logic.c`:
  - Add the include for `"esp_log.h"`
  - Add `ESP_LOGI("Example", "in app_init()");` to `app_init()`
  - Add `ESP_LOGI("Example", "in app_do_work()");` to `app_do_work()`
- Re-build and run using the command `idf.py flash monitor`

Note that the `flash` target depends on the `build` target. The build system will see that `app_logic.c` is modified, so it will re-compile and link the change.

- Verify the output:

```
I (289) cpu_start: Starting scheduler on PRO CPU.
I (0) cpu_start: Starting scheduler on APP CPU.
Hello World (v0.0.0) (Feb 27 2020 21:36:27)
I (303) Example: in app_init()
I (313) Example: in app_do_work()
```

- Press `control-]` to exit the monitor and go back to your docker workdir.
- Execute `exit` to leave docker and go back to your native terminal.

That's it!  Well done.  Continue to [Step2: Led Controller](../step-2-led-controller/step%20two.md)
