#pragma once

#include <Adafruit_NeoPixel.h>

#include "render.h"

class Pattern {
  virtual void render(Renderer &renderer, Adafruit_NeoPixel &strip, CRGBPalette16 &palette) = 0;
};
