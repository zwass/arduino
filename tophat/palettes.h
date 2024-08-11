
/* Christmas palette
DEFINE_GRADIENT_PALETTE( christmas_gp ) {
  0,     255,  0,  0,   //red
127,   255,  0,  0,   //red
129,   0,255,  0,   //green
255,   0,255,0}; //green
*/

#define PALETTE_COUNT 8

CRGBPalette16 getPalette() {
  int index =  map(analogRead(A3), 0, 1023, 0, PALETTE_COUNT); 
  switch (index) {
    case 0: return RainbowColors_p;
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
    case 3: return CloudColors_p;
    case 4: return LavaColors_p;
    case 5: return OceanColors_p;
    case 6: return PartyColors_p;
    case 7: return ForestColors_p;
    default: return RainbowColors_p;
  }
  return CRGBPalette16();
}
