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

*TODO*: link to section explaining how to wire the LED for boards lacking an on-board LED.

*TODO*: Do we need any of the following?
# ESP32 Starter
Using ESP-IDF<sup> [link](https://github.com/espressif/esp-idf)</sup> to be able to flash to an ESP32
and googletest<sup> [link](https://github.com/google/googletest)</sup> to run tests.
 FFF<sup> [link](https://github.com/meekrosoft/fff)</sup> was used to mock files for testing.
<br/>

Additional Links:
 - [Tool Chain Installation and Setup](docs/setup.md)
 - [Semantic Versioning](https://github.com/PillarTechnology/embedded-craftsmanship/blob/master/docs/semverQuickStart.md)
Note:  This link takes you out of the project

### Using Docker for development

This script (in the project root) will start docker in a mode that DOES NOT allow access to the ESP-32 via USB Serial:

```
./dockerDev.sh
```

To start docker development using the virtual box so you can access the ESP-32 via USB Serial, run the script:

```
./vmDockerDev.sh
```

### **Run Tests**

to run the tests run `bash runTests.sh`

**NOTE** if you see the error

```
CMake Error: The current CMakeCache.txt directory /workdir/test/build/CMakeCache.txt is different 
than the directory <PROJECTFOLDER>/embedded-craftsmanship/getting-started-esp32/test/build where 
CMakeCache.txt was created. This may result in binaries being created in the wrong place.
```

then run `rm -rf test/build` then try running the command again


**NOTE:** If you are developing using docker without added capacitor you will need to hold the boot button as it is trying to connect for more details see <sup>[link](https://randomnerdtutorials.com/solved-failed-to-connect-to-esp32-timed-out-waiting-for-packet-header/)</sup>.

**NOTE:** if you have a non-standard partition table you will need to adjust the memory offsets provided in the examples here. see the build's `flasher_args.json` for the correct offsets


## Components

Components are the basic makeup of an ESP-IDF project. Components are standalone code compiled to static libraries.
Each component needs its own `CMakeLists.txt` file in order to compile correctly.
 Added custom components require a blank `component.mk` file to be added correctly.
 MORE COMING SOON
 
