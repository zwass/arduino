#pragma once

#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#include "pins.h"

using neo = Adafruit_NeoPixel;

#define WHITE 1

class Renderer {
  public:
    Renderer() : useWhite(false) {}
    Renderer(bool white) : useWhite(white) {}
  
    // renderLEDs writes FastLED colors through the Neopixel library.
    const void renderLEDs(Adafruit_NeoPixel &strip, const CRGB pixels[], int length) {
      if (isOff) {
        strip.fill(0);
        strip.show();
        return;
      }

      for (int i = 0; i < length; i++) {
        CRGB color = pixels[i];

        if (useWhite) {
          strip.setPixelColor(i, 0, 0, 0, (color.red + color.green + color.blue) / 3);
        } else {
          strip.setPixelColor(i, neo::gamma8(color.red), neo::gamma8(color.green), neo::gamma8(color.blue));
        }
      }
      strip.show();
    }

    void setWhite(bool white) {
      useWhite = white;
    }

    void setOff(bool off) {
      isOff = off;
    }

  protected:
    bool useWhite, isOff;
};
