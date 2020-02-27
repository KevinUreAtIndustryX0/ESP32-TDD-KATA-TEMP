
# Setup

## Installation Option One: Native

Install everything you need on your Mac workstation for C development in general, and ESP-IDF development specifically.

## Installation Option Two: Docker

We can code, build, test, flash, and monitor using Docker.  Flashing and monitoring requires docker to be run in privileged mode in order to access the serial port in the ESP-32 via USB 2.0.  Refer to the document [Using USB with Docker for Mac](https://dev.to/rubberduck/using-usb-with-docker-for-mac-3fdd), or just follow the instructions below:

### Install VirtualBox
- [Virtual Box Downloads Page](https://www.virtualbox.org/wiki/Downloads)
- [direct link to .dmg file](https://download.virtualbox.org/virtualbox/6.1.4/VirtualBox-6.1.4-136177-OSX.dmg)
- When installing the dmg there may be a security popup that does not allow the installation until allowed from Security & Privacy from System Preferences. The install will still say it couldn't complete, but should have completed and the VirtualBox application will appear in the Applications folder if installed in the default location.

### Install the VirtualBox Extension
You need the VirtualBox extension in order to tell your virtual machine to use USB 2.0.

- [Virtual Box Downloads Page](https://www.virtualbox.org/wiki/Downloads)
- [Direct link to the virtualbox extension](https://download.virtualbox.org/virtualbox/6.1.4/Oracle_VM_VirtualBox_Extension_Pack-6.1.4.vbox-extpack)

### Install DockerMachine
- follow install https://docs.docker.com/machine/install-machine/
  
  Or, just run this block in a terminal window:
  
  ```
  base=https://github.com/docker/machine/releases/download/v0.16.0 &&
  curl -L $base/docker-machine-$(uname -s)-$(uname -m) >/usr/local/bin/docker-machine &&
  chmod +x /usr/local/bin/docker-machine
  ```
This command curls the appropriate release based on what the `uname` command determines for your OS and software.
### Create virtual machine for running docker

```
docker-machine create -d virtualbox default
docker-machine stop
vboxmanage modifyvm default --usbehci on
```

If host-only adapter error is encountered you will be unable to continue. To fix this problem run `docker-machine rm default` and rerun the previous command string.

### Plug in your ESP-32

If you've never used and ESP-32 on your Mac workstation before, you need to install the [Silicon Labs CP210x USB to UART Bridge VCP Driver](https://www.silabs.com/products/development-tools/software/usb-to-uart-bridge-vcp-drivers).  Scroll down to the section `Download for Macintosh OSX`

Plug in your ESP-32 into a micro USB cable attached to your Mac workstation.  Verify the device is mounted

```
> ls -l /dev/cu.S*
crw-rw-rw-  1 root  wheel    9,   5 Feb 20 14:51 /dev/cu.SLAB_USBtoUART
```

If you don't see `/dev/cu.SLAB_USBtoUART`, then your device is not mounted.  Unplug the usb cable, plug it back in, wait a few seconds, and try again.

At this point, the ESP-32 is available on your mac hardware, but it's not available to the virtual box that is running under docker.  Let's fix that.

### Configure the USB driver in VirtualBox

 - verify your virtualbox image is stopped:
 
 ```
 docker-machine stop
 ```
 
 Run the virtual box application.  Verify the image `default` is stopped
 
![](media/vboxStopped.png)
 
- Click `Settings`, then `ports`, then USB
- Verify you see this screen:

![](media/configureUsb.png)

Add your device by clicking the `edit plus` icon to the right of the `USB Device Filters` box:

![](media/selectSiLab.png)

- Select `Silicon Labs CP2102 USB to UART Bridge Controller`
- Click `OK` to save the filter
- Start docker-machine:

```
docker-machine start
eval $(docker-machine env default)
```

Let's verify that docker-machine is running and active:

```
> docker-machine ls
NAME      ACTIVE   DRIVER       STATE     URL                         SWARM   DOCKER     ERRORS
default   *        virtualbox   Running   tcp://192.168.99.102:2376           v19.03.5   
```

- Verify the `STATE` is `Running`, and `ACTIVE` is starred.

Now that we have the SiLabs driver configured to VirtualBox, it is no longer available to the Mac's bare metal:

```
> ll /dev/cu.S*
ls: /dev/cu.S*: No such file or directory
```

Note also that stopping the VirtualBox using `docker-machine stop` makes the driver once-again available to the Mac's bare metal.

At this point you are all set to use the build tools under docker for coding, testing, building, flashing, and monitoring the ESP-32.

Proceed to [Step 1:  Getting Started](../step1-getting-started/step%20one.md)
