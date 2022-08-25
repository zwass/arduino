#pragma once

#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#include "render.h"
#include "pattern.h"

class Alternating : Pattern {
  public:
    Alternating(int strip_length, CRGBPalette16 palette)
      : strip_length(strip_length),
        palette(palette) {
      pixels = new CRGB[strip_length]();
      counter = 0;
    }

    ~Alternating() {
      delete[] pixels;
    }

    void render(Renderer &renderer, Adafruit_NeoPixel &strip) {
      for (int i = 0; i < strip_length; i++) {
        if ((i + int(counter)) % 4 == 0) {
          pixels[i] = ColorFromPalette(palette, int(2 * i + abs(counter)) % 255, 255, LINEARBLEND);
        } else {
          pixels[i] = 0;
        }
      }
      
      
      renderer.renderLEDs(strip, pixels, strip_length);

      counter += 0.1;
//      if (counter > strip_length) {
//        counter = 0;
//      } else if (counter < 0) {
//        counter = strip_length - 1;
//      }
    }

  protected:
    int strip_length;
    CRGB *pixels;
    CRGBPalette16 palette;
    float counter;
};
