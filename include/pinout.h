#ifndef PINOUT_H
#define PINOUT_H

#include <Arduino.h>

#define PIN_BUTTON 23


#define PIN_SCREEN_EN 11
#define PIN_SCREEN_FAULT 12
#define PIN_SCREEN_SDA 25
#define PIN_SCREEN_SCL 24


void setupPins() {
  pinMode(PIN_BUTTON, INPUT);

  pinMode(PIN_SCREEN_EN, OUTPUT);
  //pinMode(PIN_OLED_SDA, OUTPUT);
  //pinMode(PIN_OLED_SCL, OUTPUT);
}


#endif