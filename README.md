# ESP-32 / ESP-IDF4 Programming Tutorial

This tutorial will lead you step-by-step in creating an embedded application for the ESP-32 using the ESP-IDF version 4 toolkit.

The embedded appication will perform the following tasks:
  - Light an LED to indicate the ESP-32 is about to connect as a network station
  - Connect to your router as a network station using the ssid and password you supplied
  - Upon successful connection, turn the LED off
  - Upon failed connection, flash the LED and stop executing
  - Assuming successful connection to the router, display JSON from a remote REST endpoint through the serial monitor of the ESP-32 connected to your dev workstation.

## Learning Goals:

After this tutorial you will:
 - Understand the ESP-IDF4 component model, and know how to design and create new components.
 - Test-drive components using GoogleTest (GTest).
 - Mock test boundries using the Fake Function Framework (FFF)
 - Feel a rush of empowerment, since you now can create embedded devices that are limited only by your imagination.

## Materials needed:

- Dev workstation capable of running Docker (Windows 10, Mac, or Linux)
- An ESP-32 dev board, preferably one with on on-board LED on pin 2
- A micro-usb cable
- Access to a wifi-router via ssid and password

If your ESP-32 does not have an on-board LED on GPIO2, you will also need a prototype board, an LED of your favorite color, and a resister somewhere in the neighborhood of 100-220 ohms.

Note:  As of this writing, the kata is not tested with the newer ESP-32s boards (should work?).

## For ESP-32 boards with no on-board LED:

*TODO*: link to section explaining how to wire the LED for boards lacking an on-board LED.

## Reference
 - [Espressif IoT Development Framework](https://github.com/espressif/esp-idf)
 - [Google Test](https://github.com/google/googletest)
 - [Fake Function Framework (fff)](https://github.com/meekrosoft/fff)

Proceed to [Step 0: Setup](../step-0-setup/README.md)
