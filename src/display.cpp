#include "display.hpp"

//OLED Display
OLED Display(PIN_SCREEN_SDA, PIN_SCREEN_SCL, NO_RESET_PIN, OLED::W_128, OLED::H_64, OLED::CTRL_SH1106, 0x3C);

displayStatus_t displayStatus = DISPLAY_OFF;

extern WT901C IMU;

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

void drawCenteredText(uint8_t x, uint8_t y, String text) {
  Display.setCursor(x - text.length() * 6 / 2, y);
  Display.print(text);
}

void displayPowerOnScreen() {
  Display.setCursor(20, 8);
  Display.print("-VLF ECLIPSE-");
  Display.setCursor(16,32);
  Display.print("Hold button for");
  Display.setCursor(24,40);
  Display.print("boot menu");
}

//Dot product
float dotProduct(float a[3], float b[3]) {
  return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

//Magnitude
float magnitude(float a[3]) {
  return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

void drawCompass(uint8_t x, uint8_t y, uint8_t radius) {
  float mag = magnitude(IMU.fMag);

  float magXNormalized = IMU.fMag[0] / mag;
  float magYNormalized = IMU.fMag[1] / mag;
  float magZNormalized = IMU.fMag[2] / mag;

  //Draw Compass
  Display.draw_circle(x, y, radius, OLED::tFillmode::HOLLOW, OLED::tColor::WHITE);


  Display.draw_line(x, y, (float)x + (float)radius * magXNormalized, (float)y + (float)radius * magYNormalized, OLED::tColor::WHITE);

  
}

