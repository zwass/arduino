#pragma once

#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

#include "render.h"

class ShootingStar {
  public:
    ShootingStar(Adafruit_NeoPixel& strip, int strip_length, CRGBPalette16 palette, const Renderer& renderer)
      : strip(strip),
        strip_length(strip_length),
        palette(palette) {
      pixels = new CRGB[strip_length]();
      counter = 0;
    }

    ~ShootingStar() {
      delete[] pixels;
    }

    void render() {
      int counterInt = counter;
      for (int i = 0; i < strip_length; i++) {
        pixels[i].subtractFromRGB(max(1, 255 / strip_length));
      }
      pixels[int(abs(counter)) % strip_length] = ColorFromPalette(palette, int(abs(counter)) % 255, 255, LINEARBLEND);
      //pixels[counterInt] = CRGB::Red;
      
      renderer.renderLEDs(strip, pixels, strip_length);

      counter += 1;
//      if (counter > strip_length) {
//        counter = 0;
//      } else if (counter < 0) {
//        counter = strip_length - 1;
//      }
    }

  protected:
    Adafruit_NeoPixel& strip;
    int strip_length;
    CRGB *pixels;
    CRGBPalette16 palette;
    float counter;
    Renderer renderer;
};
