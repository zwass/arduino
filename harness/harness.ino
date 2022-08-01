#include <Adafruit_TinyUSB.h>
#include <AceRoutine.h>
using namespace ace_routine;

#include <Adafruit_NeoPixel.h>


#include <PDM.h>

#include <FastLED.h>

#include "pins.h"
#include "render.h"
#include "shooting_star.h"

COROUTINE(blinkLed) {
  COROUTINE_LOOP() {
    digitalWrite(LED_BUILTIN, HIGH);
    COROUTINE_DELAY(10);
    digitalWrite(LED_BUILTIN, LOW);
    COROUTINE_DELAY(2000);
  }
}

int frame_micros(int frame_rate) {
  return 1000000 / frame_rate;
}

#define LED_COUNT  72
#define BRIGHTNESS 128
Adafruit_NeoPixel strip(LED_COUNT, PIN_A1, NEO_GRBW + NEO_KHZ800);
Renderer renderer;
Renderer starRenderer(true);
ShootingStar star(strip, LED_COUNT, RainbowColors_p, starRenderer);



COROUTINE(pattern) {
  COROUTINE_LOOP() {
    star.render();
    COROUTINE_DELAY_MICROS(frame_micros(100));
  }
}

/*
  float ax, ay, az, acc;
  COROUTINE(accelerometer) {
  static int frame_time = frame_micros(10);
  COROUTINE_LOOP() {
    int start_time = micros();
    ax = CircuitPlayground.motionX();
    ay = CircuitPlayground.motionY();
    az = CircuitPlayground.motionZ();

    acc = sqrt(ax * ax + ay * ay + az * az);
    if (acc < 5) {
      Serial.print("X: ");
      Serial.print(ax);
      Serial.print("  Y: ");
      Serial.print(ay);
      Serial.print("  Z: ");
      Serial.print(az);
      Serial.print(" avg: ");
      Serial.println();
    }

    int frame_elapsed = coroutineMicros() - start_time;
    int delay_time = frame_time - frame_elapsed;
    /*
      Serial.print("elapsed: ");
      Serial.print(frame_elapsed);
      Serial.print(" delay: ");
      Serial.println(delay_time);
    COROUTINE_DELAY_MICROS(delay_time);
  }
  }*/

int count_right = 0;
int count_left = 0;
COROUTINE(buttons) {
  COROUTINE_LOOP() {
    static bool leftDown, rightDown;

    if (digitalRead(LEFT_BUTTON)) {
      leftDown = true;
    } else {
      if (leftDown) {
        count_left++;
        //Serial.println("left pressed");
      }
      leftDown = false;
    }

    if (digitalRead(RIGHT_BUTTON)) {
      rightDown = true;
    } else {
      if (rightDown) {
        count_right++;
        //Serial.println("right pressed");
      }
      rightDown = false;
    }

    COROUTINE_DELAY(1);
  }
}

/*
  int counter = 0;
  COROUTINE(onboard_pattern) {
  COROUTINE_LOOP() {
  counter++;

  uint8_t brightness = onboard.sine8(counter);
  Serial.print("brightness: ");
  Serial.println(brightness);
  onboard.fill(onboard.gamma32(onboard.Color(brightness,   0,   0)));
  onboard.show();
  COROUTINE_DELAY(1);

  brightness = onboard.sine8(counter);
  onboard.fill(onboard.gamma32(onboard.Color(0,   brightness,   0)));
  onboard.show();
  COROUTINE_DELAY(1);

  brightness = onboard.sine8(counter);
  onboard.fill(onboard.gamma32(onboard.Color(0,   0,   brightness)));

  //onboard.setBrightness(onboard.sine8(counter));

  onboard.show();
  COROUTINE_DELAY(1);
  }
  }*/


CRGBPalette16 getPalette() {
  switch (count_left % 3) {
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

#define ONBOARD_LEDS 10
Adafruit_NeoPixel onboard(ONBOARD_LEDS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
CRGB pixels[ONBOARD_LEDS];
TBlendType    currentBlending = LINEARBLEND;

/*
  float counter = 0;
  int paletteIndex = 0;
  int frames = 0;
  #define TARGET_FRAME_RATE 30
  COROUTINE(onboard_pattern) {
  static int last_time = coroutineMicros();
  static int frame_time = frame_micros(TARGET_FRAME_RATE);
  // delay_fudge_factor is used to try to align the actual frame rate with the target
  static int delay_fudge_factor = 0;
  COROUTINE_LOOP() {
    static int start_time = coroutineMicros();
    start_time = coroutineMicros();
    frames++;

    int counterInt = counter;
    paletteIndex += 1;
    for (int i = 0; i < ONBOARD_LEDS; i++) {
      pixels[i].subtractFromRGB(max(1, 255 / ONBOARD_LEDS));
    }
    //fadeToBlackBy(pixels, ONBOARD_LEDS, 64);
    pixels[counterInt] = ColorFromPalette(getPalette(), paletteIndex, 255, currentBlending);
    //pixels[counterInt] = CRGB::FairyLight;
    renderLEDs(onboard, pixels, ONBOARD_LEDS);


    counter += 1;
    if (counter > ONBOARD_LEDS) {
      counter = 0;
    } else if (counter < 0) {
      counter = ONBOARD_LEDS;
    }

    int frame_elapsed = coroutineMicros() - start_time;
    int delay_time = frame_time - frame_elapsed + delay_fudge_factor;

    int current = micros();
    int elapsed = current - last_time;
    if (elapsed > 1000000 * 3) {

      int frame_rate = frames / 3;

      // adjust fudge factor to achieve target frame rate
      if (frame_rate < TARGET_FRAME_RATE) {
        delay_fudge_factor -= 100;
      } else if (frame_rate > TARGET_FRAME_RATE) {
        delay_fudge_factor += 100;
      }

      /*
            Serial.print("frame rate: ");
            Serial.print(frame_rate);
            Serial.print(" fudge factor: ");
            Serial.print(delay_fudge_factor);
            Serial.print(" delay: ");
            Serial.print(delay_time);
            Serial.println();


      frames = 0;
      last_time = current;
    }

    //Serial.println(delay_time);
    // Use millis delay because of 32767 limit on wait functions (see aceroutine docs)
    do {
      COROUTINE_DELAY_MICROS(delay_time);
      delay_time -= 32767;
    } while (delay_time > 0);
  }
  }*/

// buffer to read samples into, each sample is 16-bits
short sampleBuffer[256];
volatile int samplesRead;
void onPDMdata() {
  // query the number of bytes available
  int bytesToRead = max(sizeof(sampleBuffer), PDM.available());

  // read into the sample buffer
  PDM.read(sampleBuffer, bytesToRead);

  // 16-bit, 2 bytes per sample
  samplesRead = bytesToRead / 2;
}

#define LOG_SOUND
#define LEVELS_HISTORY 144
int level, level_avg;
int levels[LEVELS_HISTORY];
int levelsI;
COROUTINE(sound) {
  COROUTINE_LOOP() {
    COROUTINE_AWAIT(samplesRead > 0);
    float total;
    for (int i = 0; i < samplesRead; i++) {
      total += sampleBuffer[i] * sampleBuffer[i];
    }

    level = sqrt(total);
    levels[levelsI] = level;
    levelsI++;
    if (levelsI >= LEVELS_HISTORY) {
      levelsI = 0;
    }
    float sum = 0;
    for (int i = 0; i < LEVELS_HISTORY; i++) {
      sum += levels[i];
    }
    level_avg = 1.25 * (sum / LEVELS_HISTORY);

#ifdef LOG_SOUND
    Serial.print("avg: ");
    Serial.print(level_avg);
    Serial.print(" level: ");
    Serial.print(level);
    Serial.println();
#endif

    // clear the read count
    samplesRead = 0;
  }
}



int paletteIndex = 0;
int frames = 0;
#define TARGET_FRAME_RATE 30
COROUTINE(onboard_pattern) {
  static int last_time = coroutineMicros();
  static int frame_time = frame_micros(TARGET_FRAME_RATE);
  // delay_fudge_factor is used to try to align the actual frame rate with the target
  static int delay_fudge_factor = 0;

  COROUTINE_LOOP() {
    static int start_time = coroutineMicros();
    start_time = coroutineMicros();
    frames++;

    paletteIndex += 1;
    for (int i = 0; i < ONBOARD_LEDS; i++) {
      if (level > level_avg) {
        pixels[i] = ColorFromPalette(getPalette(), paletteIndex, 255, currentBlending);
      } else {
        pixels[i].subtractFromRGB(10);
      }

    }
    //pixels[counterInt] = CRGB::FairyLight;
    renderer.renderLEDs(onboard, pixels, ONBOARD_LEDS);

    int frame_elapsed = coroutineMicros() - start_time;
    int delay_time = frame_time - frame_elapsed + delay_fudge_factor;

    int current = micros();
    int elapsed = current - last_time;
    if (elapsed > 1000000 * 3) {

      int frame_rate = frames / 3;

      // adjust fudge factor to achieve target frame rate
      if (frame_rate < TARGET_FRAME_RATE) {
        delay_fudge_factor -= 100;
      } else if (frame_rate > TARGET_FRAME_RATE) {
        delay_fudge_factor += 100;
      }

      /*
            Serial.print("frame rate: ");
            Serial.print(frame_rate);
            Serial.print(" fudge factor: ");
            Serial.print(delay_fudge_factor);
            Serial.print(" delay: ");
            Serial.print(delay_time);
            Serial.println();
      */

      frames = 0;
      last_time = current;
    }

    //Serial.println(delay_time);
    // Use millis delay because of 32767 limit on wait functions (see aceroutine docs)
    do {
      COROUTINE_DELAY_MICROS(delay_time);
      delay_time -= 32767;
    } while (delay_time > 0);
  }
}

void setup() {
  Serial.begin(9600);
  
  // initialize PDM with:
  // - one channel (mono mode)
  // - a 16 kHz sample rate
  PDM.onReceive(onPDMdata);
  if (!PDM.begin(1, 16000)) {
    Serial.println("Failed to start PDM!");
  }

  // Enables more accurate clock (possibly at the expense of power consumption? But that's probably only when using low power mode?)
  // See https://github.com/adafruit/Adafruit_nRF52_Arduino/pull/551
  dwt_enable();

  pinMode(LEFT_BUTTON, INPUT_PULLDOWN);
  pinMode(RIGHT_BUTTON, INPUT_PULLDOWN);
  pinMode(SLIDE_SWITCH, INPUT_PULLUP);

  CoroutineScheduler::setup();
  LogBinProfiler::createProfilers();

  pinMode(LED_BUILTIN, OUTPUT);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);

  onboard.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  onboard.show();            // Turn OFF all pixels ASAP
  onboard.setBrightness(32);

  //renderer.setWhite(true);
}

void loop() {
  CoroutineScheduler::loop();
}
