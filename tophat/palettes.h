
DEFINE_GRADIENT_PALETTE( christmas_gp ) {
  0,     255,  0,  0,   //red
127,   255,  0,  0,   //red
129,   0,255,  0,   //green
255,   0,255,0}; //green

CRGBPalette16 getPalette(int index) {
  switch (index % 4) {
    case 3:
      return RainbowColors_p;
    case 1:
      return CRGBPalette16(
               CRGB::Indigo,  CRGB::Yellow,  CRGB::HotPink,  CRGB::Yellow,
               CRGB::Indigo,  CRGB::Yellow,  CRGB::HotPink,  CRGB::Yellow,
               CRGB::Indigo,  CRGB::Yellow,  CRGB::HotPink,  CRGB::Yellow,
               CRGB::Indigo,  CRGB::Yellow,  CRGB::HotPink,  CRGB::Yellow
             );

    case 2:
      return CRGBPalette16(
               CRGB(0x7f009e),  CRGB::Red,  CRGB::Indigo,  CRGB::Red,
               CRGB(0x7f009e),  CRGB::Red,  CRGB::Indigo,  CRGB::Red,
               CRGB(0x7f009e),  CRGB::Red,  CRGB::Indigo,  CRGB::Red,
               CRGB(0x7f009e),  CRGB::Red,  CRGB::Indigo,  CRGB::Red
             );

    // CHRISTMAS
    case 0:
    return christmas_gp;
  }
  return CRGBPalette16();
}
