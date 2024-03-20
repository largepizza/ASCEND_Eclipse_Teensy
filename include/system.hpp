#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include "pinout.h"
#include "sd_filesystem.hpp"
#include "wt901c.hpp"


#define EEPROM_POWER_CYCLE_ADDRESS 0xAE
#define BUTTON_HYSTERISIS 50


//Overall System Status
typedef enum : uint32_t {
    STATUS_POWER_ON,
    STATUS_BOOT_MENU,
    STATUS_DATA_LOGGER,
    STATUS_IMU_DATA,
    STATUS_IMU_CALIBRATION,
    STATUS_PI_STANDBY
} status_t;

//Boot Menu Status
typedef enum : uint32_t {
    BOOT_MENU_DATA_LOGGER,
    BOOT_IMU_DATA,
    BOOT_IMU_CALIBRATION,
    BOOT_PI_STANDBY
} boot_menu_t;

//Button Status
typedef enum : uint32_t {
    BUTTON_UNPRESSED,
    BUTTON_PRESSED,
} button_t;




//Global Variables
extern status_t systemStatus;
extern boot_menu_t bootMenuStatus;
extern button_t buttonStatus;
extern WT901C IMU;


//Function Prototypes
void setupPins();
void buttonHandler();
void getButton();
void printButtonStatus();









#endif // SYSTEM_H