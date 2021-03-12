#include <Adafruit_NeoPixel.h>

int r = 2;
int g = 3;
int b = 4;

bool redCur;
bool redPrev;
bool greenCur;
bool greenPrev;
bool blueCur;
bool bluePrev;

bool buzzStart;
bool timer;

long sT;
long sTBuzz;

int buzz = 6;

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
}

void loop() {
  redCur = digitalRead(r);
  greenCur = digitalRead(g);
  blueCur = digitalRead(b);

  if ((digitalRead(r)) == true) {
    rC = 255;
    timer = true;
  } else {
    rC = 0;
  }

  if ((digitalRead(g)) == true) {
    gC = 255;
    timer = true;
  } else {
    gC = 0;
  }

  if ((digitalRead(b)) == true) {
    bC = 255;
    timer = true;
  } else {
    bC = 0;
  }

  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, rC, gC, bC);
  }
  strip.show();

  if (redCur == true && redPrev == false) {
    sT = millis();
  }
  if (greenCur == true && greenPrev == false) {
    sT = millis();
  }
  if (blueCur == true && bluePrev == false) {
    sT = millis();
  }

  if (timer) {
    if (millis() - sT > 30000) {
      analogWrite(buzz, 5);
      sTBuzz = millis();
      buzzStart = true;
      timer = false;
    }
  }

  if (buzzStart) {
    if (millis() - sTBuzz > 1000) {
      analogWrite(buzz, 0);
      buzzStart = false;
    }
  }

  redPrev = redCur;
  greenPrev = greenCur;
  bluePrev = blueCur;
}
