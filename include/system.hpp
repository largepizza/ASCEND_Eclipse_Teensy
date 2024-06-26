#ifndef SYSTEM_H
#define SYSTEM_H

#include <Arduino.h>
#include "pinout.h"
#include "sd_filesystem.hpp"
#include "wt901c.hpp"


#define EEPROM_POWER_CYCLE_ADDRESS 0xAE
#define BUTTON_HYSTERISIS 50
#define LOW_POWER_VOLTAGE 10.5
#define BATTERY_CRITICAL_VOLTAGE 10.0


//Overall System Status
typedef enum : uint32_t {
    STATUS_POWER_ON,
    STATUS_BOOT_MENU,
    STATUS_DATA_LOGGER,
    STATUS_IMU_DATA,
    STATUS_IMU_CALIBRATION,
    STATUS_PI_STANDBY,
    STATUS_FILE_BROWSER,
    STATUS_THERMISTOR_TEST
} status_t;

//Boot Menu Status
typedef enum : uint32_t {
    BOOT_MENU_DATA_LOGGER,
    BOOT_IMU_DATA,
    BOOT_IMU_CALIBRATION,
    BOOT_PI_STANDBY,
    BOOT_FILE_BROWSER,
    BOOT_THERMISTOR_TEST
} boot_menu_t;

//SD Data Logger Status
typedef enum : uint32_t {
    SD_LOGGER_OFF,
    SD_LOGGER_ON,
    SD_LOGGER_RECORDING,
    SD_LOGGER_ERROR
} sd_logger_t;

//Button Status
typedef enum : uint32_t {
    BUTTON_UNPRESSED,
    BUTTON_PRESSED,
} button_t;

//Power switch class
class PowerSwitch {
    public:
        PowerSwitch(uint8_t enablePin, uint8_t faultPin) {
            _enablePin = enablePin;
            _faultPin = faultPin;
        }
        void enable() {
            //Fault pin is pulled high when no fault is present
            getStatus();
            if (_fault) {
                digitalWrite(_enablePin, LOW);
                _enabled = false;
            }
            else {
                digitalWrite(_enablePin, HIGH);
                _enabled = true;
            }
        }
        void disable() {
            digitalWrite(_enablePin, LOW);
            _enabled = false;
            
        }
        bool getStatus() {
            return _enabled;
        }
        bool getFault() {
            _fault = !digitalRead(_faultPin);
            return _fault;
        }
    private:
        uint8_t _enablePin;
        uint8_t _faultPin;
        bool _enabled;
        bool _fault;

};


//Global Variables
extern status_t systemStatus;
extern boot_menu_t bootMenuStatus;
extern button_t buttonStatus;
extern WT901C IMU;
extern sd_logger_t sdLoggerStatus;


//Function Prototypes
void setupPins();
void getButton();
void printButtonStatus();

//Button ISR
void buttonHandler();

//Power switch fault ISR
void piFaultHandler();
void screenFaultHandler();











#endif // SYSTEM_H