#include <Adafruit_NeoPixel.h>

#define LEDPIN 6
#define MICPIN 2
#define POTENTIOMETER A0

uint32_t ledColorArray[8];
uint32_t color;
int potentiometer;
float brightness = 0.25;

Adafruit_NeoPixel leds = Adafruit_NeoPixel(32, LEDPIN, NEO_GRB + NEO_KHZ800);

void turnOn() {
  for (int i = 0; i < 8; i++) {
    ledColorArray[i] = color;
  }
}

void turnOff() {
  bool complete = false;
  for (int i = 7; i >= 0 && !complete; i--) {
    if (ledColorArray[i] != 0) {
      delay(15); //Pause so they do not turn off all at once
      ledColorArray[i] = 0;
      complete = true;
    }
  }
}

void setup() {
  leds.begin();
  leds.show();
  pinMode(MICPIN, INPUT);
  pinMode(POTENTIOMETER, INPUT);
  attachInterrupt(digitalPinToInterrupt(MICPIN), turnOn, RISING);
}

void loop() {
  for (int i = 0; i < 8; i++) {
    leds.setPixelColor(4 * i  , ledColorArray[i]);
    leds.setPixelColor(4 * i + 1, ledColorArray[i]);
    leds.setPixelColor(4 * i + 2, ledColorArray[i]);
    leds.setPixelColor(4 * i + 3, ledColorArray[i]);
  }
  leds.setPixelColor(0, color);
  leds.show();
  turnOff();
  potentiometer = analogRead(POTENTIOMETER);
  if (potentiometer < 341) {
    color = leds.Color(map(potentiometer, 0, 340, 255, 0) * brightness, map(potentiometer, 0, 340, 0, 255) * brightness, 0);
  }
  if (potentiometer >= 341 && potentiometer < 682) {
    color = leds.Color(0, map(potentiometer, 341, 681, 255, 0) * brightness, 0, map(potentiometer, 341, 681, 0, 255) * brightness);
  }
  if (potentiometer >= 682) {
    color = leds.Color(map(potentiometer, 682, 1023, 0, 255) * brightness, 0, map(potentiometer, 682, 1023, 255, 0) * brightness);
  }
}
