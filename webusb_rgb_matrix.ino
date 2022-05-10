#include "Adafruit_TinyUSB.h"
#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL 6
#define NEOPIXEL_NUM 16*16
#define NEOPIXEL_WEBUSB_LENGTH NEOPIXEL_NUM * 3

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NEOPIXEL_NUM, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

Adafruit_USBD_WebUSB webUSB;
WEBUSB_URL_DEF(landingPage, 1, "webusb-rgb-matrix.nico.dev");

void setup() {

#if defined(ARDUINO_ARCH_MBED) && defined(ARDUINO_ARCH_RP2040)
  TinyUSB_Device_Init(0);
#endif

  webUSB.setStringDescriptor("Neopixel WebUSB");
  webUSB.setLandingPage(&landingPage);
  webUSB.begin();

  Serial.begin(115200);

  strip.begin();
  strip.setBrightness(50);
  //strip.fill(0x000000);
  strip.show();

  while ( !TinyUSBDevice.mounted() ) delay(1);
}

void sendString(String str) {
  int strLen = str.length() + 1;
  char charArray[strLen];
  str.toCharArray(charArray, strLen);
  webUSB.write(charArray, strLen);
}

void loop() {
  if (!webUSB.available()) return;

  uint8_t input[NEOPIXEL_WEBUSB_LENGTH];
  int inputLength = 0;
  while (inputLength < NEOPIXEL_WEBUSB_LENGTH) {
    int readLength = webUSB.readBytes(input + inputLength, NEOPIXEL_WEBUSB_LENGTH - inputLength);
    inputLength += readLength;
  }

  for (int i = 0; i < strip.numPixels(); i++) {
    int pI = 3 * i;
    strip.setPixelColor(i, strip.Color(input[pI], input[pI + 1], input[pI + 2]));
  }
  strip.show();
}
