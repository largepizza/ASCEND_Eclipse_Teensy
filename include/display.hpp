#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "pinout.h"
#include <oled.h>
#include <system.hpp>

typedef enum  {
    DISPLAY_OFF,
    DISPLAY_ON
} displayStatus_t;

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


extern OLED Display;
extern displayStatus_t displayStatus;


//Function Prototypes
void setupDisplay();
void turnDisplayOn();
void turnDisplayOff();

//draw functions
void drawProgressBar(uint8_t x, uint8_t y, uint8_t width, uint8_t height, float progress);
void drawCenteredText(uint8_t x, uint8_t y, String text);

void displayPowerOnScreen();
void displayBootMenuScreen();


#endif // DISPLAY_H