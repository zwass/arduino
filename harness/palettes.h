
CRGBPalette16 getPalette(int index) {
  switch (index % 3) {
    case 0:
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
  }
  return CRGBPalette16();
}
