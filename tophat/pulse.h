#pragma once

#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#include "render.h"
#include "pattern.h"

class Pulse : Pattern {
  public:
    Pulse(int strip_length, const int& level, const int& level_avg)
      : strip_length(strip_length),
        level(level),
        level_avg(level_avg) {
      pixels = new CRGB[strip_length]();
      counter = 0;
    }

    ~Pulse() {
      delete[] pixels;
    }

    void render(Renderer &renderer, Adafruit_NeoPixel &strip, CRGBPalette16 &palette) {
      for (int i = 0; i < strip_length; i++) {
        if (level > level_avg) {
          pixels[i] = ColorFromPalette(palette, int(abs(counter)) % 255, 255, LINEARBLEND);
        } else {
          pixels[i].subtractFromRGB(10);
        }
      }

      renderer.renderLEDs(strip, pixels, strip_length);
      counter += 1;
    }

  protected:
    int strip_length;
    CRGB *pixels;
    float counter;
    const int& level;
    const int& level_avg;
};
