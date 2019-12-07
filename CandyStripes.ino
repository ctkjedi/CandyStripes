#include <FastLED.h>

#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    300
#define NUM_LEDS_PER_STRIP  60
#define BRIGHTNESS  50
#define FRAMES_PER_SECOND 30

int stripCount = 5;
int x=0;

uint16_t serpentineArray[] = {
  0,  60, 120, 180, 240,
  1,  61, 121, 181, 241,
  2,  62, 122, 182, 242,
  3,  63, 123, 183, 243,
  4,  64, 124, 184, 244,
  5,  65, 125, 185, 245,
  6,  66, 126, 186, 246,
  7,  67, 127, 187, 247,
  8,  68, 128, 188, 248,
  9,  69, 129, 189, 249,
  10,  70, 130, 190, 250,
  11,  71, 131, 191, 251,
  12,  72, 132, 192, 252,
  13,  73, 133, 193, 253,
  14,  74, 134, 194, 254,
  15,  75, 135, 195, 255,
  16,  76, 136, 196, 256,
  17,  77, 137, 197, 257,
  18,  78, 138, 198, 258,
  19,  79, 139, 199, 259,
  20,  80, 140, 200, 260,
  21,  81, 141, 201, 261,
  22,  82, 142, 202, 262,
  23,  83, 143, 203, 263,
  24,  84, 144, 204, 264,
  25,  85, 145, 205, 265,
  26,  86, 146, 206, 266,
  27,  87, 147, 207, 267,
  28,  88, 148, 208, 268,
  29,  89, 149, 209, 269,
  30,  90, 150, 210, 270,
  31,  91, 151, 211, 271,
  32,  92, 152, 212, 272,
  33,  93, 153, 213, 273,
  34,  94, 154, 214, 274,
  35,  95, 155, 215, 275,
  36,  96, 156, 216, 276,
  37,  97, 157, 217, 277,
  38,  98, 158, 218, 278,
  39,  99, 159, 219, 279,
  40, 100, 160, 220, 280,
  41, 101, 161, 221, 281,
  42, 102, 162, 222, 282,
  43, 103, 163, 223, 283,
  44, 104, 164, 224, 284,
  45, 105, 165, 225, 285,
  46, 106, 166, 226, 286,
  47, 107, 167, 227, 287,
  48, 108, 168, 228, 288,
  49, 109, 169, 229, 289,
  50, 110, 170, 230, 290,
  51, 111, 171, 231, 291,
  52, 112, 172, 232, 292,
  53, 113, 173, 233, 293,
  54, 114, 174, 234, 294,
  55, 115, 175, 235, 295,
  56, 116, 176, 236, 296,
  57, 117, 177, 237, 297,
  58, 118, 178, 238, 298,
  59, 119, 179, 239, 299
};

CRGB leds[NUM_LEDS];



void setup() {
  // put your setup code here, to run once:
  delay(3000); // sanity delay
  Serial.begin(9600);
  FastLED.setBrightness(BRIGHTNESS);

  FastLED.addLeds<WS2812, 21, GRB>(leds, 0, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 19, GRB>(leds, NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 17, GRB>(leds, 2 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 14, GRB>(leds, 3 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);
  FastLED.addLeds<WS2812, 13, GRB>(leds, 4 * NUM_LEDS_PER_STRIP, NUM_LEDS_PER_STRIP);

  fill_solid(leds, NUM_LEDS, CRGB::Black);

  FastLED.show();
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 1500);
}

void loop() {
  // put your main code here, to run repeatedly:
  candyStripes(CRGB::Red , CRGB::White, 3, 500);

}



void candyStripes(CRGB color1, CRGB color2, int stripeWidth, int speed) {
  EVERY_N_MILLIS(speed) {
    uint16_t i, j, pos;
    for (j = 0; j < round(NUM_LEDS_PER_STRIP / stripeWidth); j++) { //calculate rows based on stripe size

      for (i = 0; i < stripCount * stripeWidth; i++) {
        pos = i + (j * stripeWidth * stripCount);
        if ((j+x) % 2 == 0) {
          leds[serpentineArray[pos]] = color1;
        } else {
          leds[serpentineArray[pos]] = color2;
        }
      }
    }
    FastLED.show();
      x++;
      if(x>=NUM_LEDS) x=0;
  }
}
