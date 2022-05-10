# WebUSB RGB Matrix

A [Raspberry Pi Pico](https://www.raspberrypi.com/products/raspberry-pi-pico/) powered Neopixel RGB matrix that can be controlled via [WebUSB](https://developer.mozilla.org/en-US/docs/Web/API/USB).

This Arduino sketch uses the [Adafruit_TinyUSB library](https://github.com/adafruit/Adafruit_TinyUSB_Arduino) to make the device WebUSB compatible and receives data from the web application which is then converted into colour values of the RGB LEDs.

## Frontend Demo
[https://webusb-rgb-matrix.nico.dev/](https://webusb-rgb-matrix.nico.dev/)  
[https://github.com/nico-martin/webusb-rgb-matrix-ui](https://github.com/nico-martin/webusb-rgb-matrix-ui)

## Circuit
![WebUSB RGB Matrix circuit](https://uploads.nico.dev/webusb-rgb-matrix-circuit.jpg)

## change USB product name

One small problem I encountered is that I could not change the USB product name (which is displayed in the browser notification) via the sketch. I have found two ways to do this:

### TinyUSB

```c++
// \Arduino\libraries\Adafruit_TinyUSB_Library\src\arduino\Adafruit_USBD_Device.cpp#67

#ifndef USB_PRODUCT
#define USB_PRODUCT "My cool name"
#endif
```

### boards.txt

The boards.txt is a file that contains informations about the installed devices.
For the Raspberry Pi Pico for example we can change the `rpipico.build.usb_product` value:

```txt
// \ArduinoData\packages\rp2040\hardware\rp2040\2.0.0\boards.txt#42

rpipico.build.usb_product="My cool name"
```