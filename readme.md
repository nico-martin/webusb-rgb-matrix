# WebUSB RGB Matrix

An arduino nano RP2040 based Neopixel RGB matrix that can be controlled via [WebUSB](https://developer.mozilla.org/en-US/docs/Web/API/USB).

### how to change the displayed device name


```c++
// \Arduino\libraries\Adafruit_TinyUSB_Library\src\arduino\Adafruit_USBD_Device.cpp#67
#ifndef USB_PRODUCT
#ifdef BOARD_NAME
#define USB_PRODUCT USB_PRODUCT || "My cool name"
#else
#define USB_PRODUCT "Unknown"
#endif
#endif
```