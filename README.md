![](https://github.com/PillarTechnology/getting-started-esp32/workflows/CI-getting-started-esp32/badge.svg)

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

### Hardware
In order to be able use this example effectively there are several components required to start:
 - an ESP32
 - a common cathode RGB LED(a common anode can work but on/off signal will be reversed)
 - for gpio pins for LED red is pin 25, blue is pin 26, green is pin 27.
If you need assistance understanding how the tests work refer to getting-started-tdd-in-c <sup> [link](https://github.com/PillarTechnology/getting-started-tdd-in-c/tree/91f6d074f2b8bb1a70ae56ad790f2f246d701ca4)</sup>

### **Run Tests**

to run the tests run `bash runTests.sh`

**NOTE** if you see the error

```
CMake Error: The current CMakeCache.txt directory /workdir/test/build/CMakeCache.txt is different 
than the directory <PROJECTFOLDER>/embedded-craftsmanship/getting-started-esp32/test/build where 
CMakeCache.txt was created. This may result in binaries being created in the wrong place.
```

then run `rm -rf test/build` then try running the command again

### **Build Locally**

In order to build the project run `idf.py build` from project directory

### **Flash from Local Build**

to flash code to the chip run `idf.py flash` from project directory, if further commands are needed see link <sup>[link](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html)</sup> 

### **Flash from a CI artifact**

CI builds contain four files
```
partition-table.bin
bootloader.bin
YOURAPP.bin
flasher_args.json
```
to flash from a CI build artifact:
```
esptool.py --port /dev/cu.SLAB_USBtoUART write_flash 0x8000 partition-table.bin
esptool.py --port /dev/cu.SLAB_USBtoUART write_flash 0x1000 bootloader.bin
esptool.py --port /dev/cu.SLAB_USBtoUART write_flash 0x10000 hello-world.bin
```
to view the device logs do `screen /dev/cu.SLAB_USBtoUART 115200`

**NOTE:** If you are not developing using docker, realize that `esptool.py` does not come with ESP IDF and must be acquired separately <sup>[link](https://raw.githubusercontent.com/espressif/esptool/master/esptool.py)</sup> 

**NOTE:** If you are developing using docker without added capacitor you will need to hold the boot button as it is trying to connect for more details see <sup>[link](https://randomnerdtutorials.com/solved-failed-to-connect-to-esp32-timed-out-waiting-for-packet-header/)</sup>.

**NOTE:** if you have a non-standard partition table you will need to adjust the memory offsets provided in the examples here. see the build's `flasher_args.json` for the correct offsets


## Components

Components are the basic makeup of an ESP-IDF project. Components are standalone code compiled to static libraries.
Each component needs its own `CMakeLists.txt` file in order to compile correctly.
 Added custom components require a blank `component.mk` file to be added correctly.
 MORE COMING SOON
 
## Things to watch out for:

 - Need to be using googletest 1.10.0 or greater
 - Must have a main directory rather than a src directory
 - app_main function must remain in the main directory
 - requires cmake 3.5 or greater
 
 
 [back to embedded-craftsmanship repo](https://github.com/PillarTechnology/embedded-craftsmanship)



