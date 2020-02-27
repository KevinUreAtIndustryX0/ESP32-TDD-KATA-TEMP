make led init the led to off

make a network controller

define an init

test drive app_init calling network init
 - dont forget the cmakelists

mock for err and nvs

tdd app init should flash nvs
 - if flash returns 1 of 2 error codes it should erase and call again
 - switch tests to a fixture so your mocks get reset
 - dont forget the cmake!

mocks for netif and event

tdd net_init should init netif and then create event loop
 - switch tests to a fixture so your mocks get reset
 - dont forget the cmake!

mock for example_connect in protocol_examples_common.h

tdd network controller to call exampleconnect
 - root cmake needs edit

tdd led controller set function

tdd for network controller to set led on after connection

menuconfig
build and flash