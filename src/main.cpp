#include <Arduino.h>
#include <oled.h>
#include "pinout.h"


OLED Display(PIN_SCREEN_SDA, PIN_SCREEN_SCL, NO_RESET_PIN, OLED::W_128, OLED::H_64, OLED::CTRL_SH1106, 0x3C);

void setup() {

  setupPins();

  digitalWrite(PIN_SCREEN_EN, HIGH);
  Display.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  // Method 1: pixel position
  
  Display.clear();
  
  Display.setCursor(6,8);
  Display.printf("Hello World");

  if (digitalRead(PIN_BUTTON) == LOW) {
    Display.setCursor(6,16);
    Display.printf("Button Pressed");
  }

  Display.display();

  delay(10);
}

