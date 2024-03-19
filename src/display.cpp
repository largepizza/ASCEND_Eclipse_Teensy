#include "display.hpp"

//OLED Display
OLED Display(PIN_SCREEN_SDA, PIN_SCREEN_SCL, NO_RESET_PIN, OLED::W_128, OLED::H_64, OLED::CTRL_SH1106, 0x3C);

displayStatus_t displayStatus = DISPLAY_OFF;

void setupDisplay() {
  Display.begin();
  Display.clear();
  Display.display();
}

void turnDisplayOn() {
  displayStatus = DISPLAY_ON;
  digitalWrite(PIN_SCREEN_EN, HIGH);
}

void turnDisplayOff() {
  displayStatus = DISPLAY_OFF;
  digitalWrite(PIN_SCREEN_EN, LOW);
}

void drawProgressBar(uint8_t x, uint8_t y, uint8_t width, uint8_t height, float progress) {

    progress = constrain(progress, 0, 100);
    //Draw Outline
    Display.draw_rectangle(x-width/2, y-height/2, x+width/2, y+height/2, OLED::tFillmode::HOLLOW, OLED::tColor::WHITE);

    //Draw Progress
    Display.draw_rectangle(x-width/2, y-height/2, x-width/2+width*progress/100.0, y+height/2, OLED::tFillmode::SOLID, OLED::tColor::WHITE);
}

void displayPowerOnScreen() {
  Display.setCursor(20, 8);
  Display.print("-VLF ECLIPSE-");
  Display.setCursor(16,32);
  Display.print("Hold button for");
  Display.setCursor(24,40);
  Display.print("boot menu");


  Display.display();
}

