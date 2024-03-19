#ifndef PINOUT_H
#define PINOUT_H

#include <Arduino.h>

//Board Buttons
#define PIN_BUTTON 23

//Board Thermistors
#define PIN_TEMP_UP 15
#define PIN_TEMP_DOWN 14

//External Thermistors
#define PIN_TEMP1 20
#define PIN_TEMP2 21
#define PIN_TEMP3 22
#define PIN_TEMP4 26
#define PIN_TEMP5 41

//OLED Screen
#define PIN_SCREEN_EN 11
#define PIN_SCREEN_FAULT 12
#define PIN_SCREEN_SDA 25
#define PIN_SCREEN_SCL 24

//Raspberry Pi - Serial7
#define PIN_RPI_EN 31
#define PIN_RPI_FAULT 30
#define PIN_RPI_TX 28
#define PIN_RPI_RX 29

//IMU - Serial4
#define PIN_IMU_TX 16 
#define PIN_IMU_RX 17

//IMU - I2C
#define PIN_IMU_SDA 18
#define PIN_IMU_SCL 19



#endif