#include <Adafruit_NeoPixel.h>
#include <Bounce2.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(11, 0);
//Adafruit_NeoPixel preview = Adafruit_NeoPixel(3, 9);


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

//Timer Variables
int shortTime = 10000;
unsigned long longTime = 45000;

//timer execution buttons
int s = 0;
Bounce l = Bounce();

//delay variables
unsigned long delayTime;

//Case Variable
int shouldShow = 0;

void setup() {
  Serial.begin(9600);

  strip.begin();
  strip.clear();

  //preview.begin();
  //preview.clear();

  //debounce things
  r.attach(1);
  g.attach(2);
  b.attach(3);
  l.attach(4);

  //buffer time
  r.interval(5);
  g.interval(5);
  b.interval(5);
  l.interval(5);

}

void loop() {

  r.update();
  g.update();
  b.update();
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
  if (analogRead(s) < 1000) {
    shouldShow = 1;
    delayTime = shortTime;
  }


  if (l.rose()) {
    shouldShow = 1;
    delayTime = longTime;
  }
  ////////////////////////////////////////////////////////////////////
  //state machine for the lights
  switch (shouldShow) {
    case 0:
      //writes to preview board
      strip.setPixelColor(0, rC, 0, 0);
      strip.setPixelColor(1, 0, gC, 0);
      strip.setPixelColor(2, 0, 0, bC);
      strip.show();
      break;

    ////////////////////////////
    case 1:
      //clears and turns off preview board
      strip.clear();
      strip.show();
      //writes data to glasses strip
      for (int i = 3; i < strip.numPixels(); i++) {
        //writes the neopixel strip
        strip.setPixelColor(i, gC, rC, bC); //swapped green and red bc SMD NeoPixels are GRB
      }
      //shows lights on glasses for a period of time
      strip.show();
      delay(delayTime);
      delayTime = 0;
      strip.clear();
      strip.show();
      shouldShow = 0;

      //clears stored colors
      isR = false;
      isG = false;
      isB = false;

      break;
  }

}
