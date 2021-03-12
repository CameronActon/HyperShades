#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(7, 8);
Adafruit_NeoPixel preview = Adafruit_NeoPixel(3, 9);


//light buttons
Bounce r = Bounce();
Bounce g = Bounce();
Bounce b = Bounce();

//Neopixel Variables
int rC = 0;
int gC = 0;
int bC = 0;



//display booleans
bool isR = false;
bool isG = false;
bool isB = false;

//timer execution buttons
Bounce s = Bounce();
Bounce l = Bounce();

//delay variables
unsigned long delayTime;

//Case Variable
int shouldShow = 0;

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.clear();

  preview.begin();
  preview.clear();

  //debounce things
  r.attach(5);
  g.attach(6);
  b.attach(7);
  s.attach(3);
  l.attach(4);

  //buffer time
  r.interval(5);
  g.interval(5);
  b.interval(5);
  s.interval(5);
  l.interval(5);

}

void loop() {

  r.update();
  g.update();
  b.update();
  s.update();
  l.update();


  //toggles lights being displayed
  if (r.rose()) {
    isR = !isR;
  }
  if (g.rose()) {
    isG = !isG;
  }
  if (b.rose()) {
    isB = !isB;
  }


  //sets colors to be written
  //red
  if (isR) {
    rC = 255;
  }
  else {
    rC = 0;
  }
  //green
  if (isG) {
    gC = 255;
  }
  else {
    gC = 0;
  }
  //blue
  if (isB) {
    bC = 255;
  }
  else {
    bC = 0;
  }

  //checks for timer buttons
  if (s.rose()) {
    shouldShow = 1;
    delayTime = 5000;
  }
  if (l.rose()) {
    shouldShow = 1;
    delayTime = 60000;
  }
  ////////////////////////////////////////////////////////////////////
  //state machine for the lights
  switch (shouldShow) {
    case 0:
    //clears glasses lights
      strip.clear();
      strip.show();
      //writes to preview board
      for (int i = 0; i < preview.numPixels(); i++) {
        preview.setPixelColor(0, rC, 0, 0);
        preview.setPixelColor(1, 0, gC, 0);
        preview.setPixelColor(2, 0, 0, bC);
      }
      preview.show();
      break;
    case 1:
      //clears and turns off preview board
      preview.clear();
      preview.show();
      //writes data to glasses strip
      for (int i = 0; i < strip.numPixels(); i++) {
        //writes the neopixel strip
        strip.setPixelColor(i, rC, gC, bC);
      }
      //shows lights on glasses for a period of time
      strip.show();
      delay(delayTime);
      delayTime = 0;
      strip.clear();
      strip.show();
      shouldShow = 0;

      //clears stores colors
      isR = false;
      isG = false;
      isB = false;

      break;
  }

}
