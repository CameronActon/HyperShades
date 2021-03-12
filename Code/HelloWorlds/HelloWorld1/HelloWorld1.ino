#include <Adafruit_NeoPixel.h>

int r = 2;
int g = 3;
int b = 4;

bool ifPushR;
bool ifPushG;
bool ifPushB;

int rC = 0;
int gC = 0;
int bC = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, 5);

void setup() {
  strip.begin();
  strip.clear();
  strip.setBrightness(255);

  pinMode(r, INPUT);
  pinMode(g, INPUT);
  pinMode(b, INPUT);

  ifPushR = false;
  ifPushG = false;
  ifPushB = false;
}

void loop() {
  if ((digitalRead(r)) == true) {
    rC = 255;
  } else {
    rC = 0;
  }

  if ((digitalRead(g)) == true) {
    gC = 255;
  } else {
    gC = 0;
  }

  if ((digitalRead(b)) == true) {
    bC = 255;
  } else {
    bC = 0;
  }

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, rC, gC, bC);
  }
  strip.show();
}
