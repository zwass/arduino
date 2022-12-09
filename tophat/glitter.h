#pragma once

#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#include "render.h"

class Glitter : Pattern {
  public:
    Glitter(int strip_length) : strip_length(strip_length) {
      pixels = new CRGB[strip_length]();
    }

    ~Glitter() {
      delete[] pixels;
    }

    void render(Renderer &renderer, Adafruit_NeoPixel &strip, CRGBPalette16 &palette) {
      // Fade
      for (int i = 0; i < strip_length; i++) {
        pixels[i].subtractFromRGB(15);
      }

      // Draw new
      pixels[random(strip_length)] = ColorFromPalette(palette, random(255), 255, LINEARBLEND);
      pixels[random(strip_length)] = ColorFromPalette(palette, random(255), 255, LINEARBLEND);
      pixels[random(strip_length)] = ColorFromPalette(palette, random(255), 255, LINEARBLEND);
      
      renderer.renderLEDs(strip, pixels, strip_length);
    }

  protected:
    int strip_length;
    CRGB *pixels;
};
