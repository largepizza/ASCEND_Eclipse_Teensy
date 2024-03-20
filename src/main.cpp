#include <Arduino.h>
#include "pinout.h"
#include "system.hpp"
#include "sd_filesystem.hpp"
#include "display.hpp"

#


//Global Variables
extern status_t systemStatus;
extern boot_menu_t bootMenuStatus;
extern button_t buttonStatus;
extern uint32_t t_button;

//Status Power On Variables
uint32_t t_powerOn = 0;
float powerOnHold = 0;

//Status Boot Menu Variables
bool buttonHold = false;
float bootMenuHold = 0;

void setup() {


  //Setup Serial
  Serial.begin(115200);
  setupPins();


  digitalWrite(LED_BUILTIN, HIGH);
  t_powerOn = millis();

  turnDisplayOn();
  setupDisplay();
}

void loop() {

  //State Machine
  switch (systemStatus) {
    case STATUS_POWER_ON:
      //Display Power On Screen
      
;

      if (buttonStatus == BUTTON_PRESSED) {
        //Button hysterisis to avoid false positives
        powerOnHold += 5;
        t_powerOn += 40;
        delay(5);
      }

      //Display block
      Display.clear();
      drawProgressBar(SCREEN_WIDTH / 2, 55, SCREEN_WIDTH / 2, 8, powerOnHold);
      displayPowerOnScreen();
      Display.display();


      //State Transition
      if (powerOnHold > 100) {
        //Boot Menu if button is held
        systemStatus = STATUS_BOOT_MENU;
      }
      if (millis() - t_powerOn > 3000) {
        //Data Logger if button is not held
        systemStatus = STATUS_DATA_LOGGER;
      }
      
      break;
    case STATUS_BOOT_MENU:
      //Display Boot Menu bar
      Display.clear();
      Display.setCursor(8, 0);
      Display.print("Boot Menu");
      Display.draw_line(0, 12, SCREEN_WIDTH, 12, OLED::tColor::WHITE);

      //Display Boot Menu Options

      if (buttonStatus == BUTTON_PRESSED) {
        buttonHold = true;
        bootMenuHold += 2;
        delay(5);
        if (bootMenuHold > 10) {
          drawCenteredText(SCREEN_WIDTH / 2, 40, "Running");
          drawProgressBar(SCREEN_WIDTH / 2, 55, SCREEN_WIDTH / 2, 8, bootMenuHold);
        }

        if (bootMenuHold > 100) {
          //Boot Menu
          switch (bootMenuStatus) {
            case BOOT_MENU_DATA_LOGGER:
              systemStatus = STATUS_DATA_LOGGER;
              break;
            case BOOT_IMU_DATA:
              systemStatus = STATUS_IMU_DATA;
              break;
            case BOOT_IMU_CALIBRATION:
              systemStatus = STATUS_IMU_CALIBRATION;
              break;
            case BOOT_PI_STANDBY:
              systemStatus = STATUS_PI_STANDBY;
              break;
          }
        }
        
      }

      if (buttonStatus == BUTTON_UNPRESSED && buttonHold) {
        buttonHold = false;
        bootMenuHold = 0;
        bootMenuStatus = (boot_menu_t)((uint32_t)bootMenuStatus + 1);
        if (bootMenuStatus > BOOT_PI_STANDBY) {
          bootMenuStatus = BOOT_MENU_DATA_LOGGER;
        }
      }



      switch (bootMenuStatus) {
        case BOOT_MENU_DATA_LOGGER:
          drawCenteredText(SCREEN_WIDTH / 2, 24, "Data Logger");
          break;
        case BOOT_IMU_DATA:
          drawCenteredText(SCREEN_WIDTH / 2, 24, "IMU Data");
          break;
        case BOOT_IMU_CALIBRATION:
          drawCenteredText(SCREEN_WIDTH / 2, 24, "IMU Calibration");
          break;
        case BOOT_PI_STANDBY:
          drawCenteredText(SCREEN_WIDTH / 2, 24, "Pi Standby");
          break;
      }

      Display.display();

      break;
    case STATUS_DATA_LOGGER:
      //Data Logger
      Display.clear();
      Display.setCursor(0, 0);
      Display.print("Data Logger");
      Display.display();

      delay(100);

      break;
    case STATUS_IMU_DATA:
      //IMU Data
      Display.clear();
      Display.setCursor(0, 0);
      Display.print("IMU Data");
      Display.display();

      delay(100);

      break;
    case STATUS_IMU_CALIBRATION:
      //IMU Calibration
      Display.clear();
      Display.setCursor(0, 0);
      Display.print("IMU Calibration");
      Display.display();

      delay(100);

      break;
    case STATUS_PI_STANDBY:
      //Pi Standby
      Display.clear();
      Display.setCursor(0, 0);
      Display.print("Pi Standby");
      Display.display();

      delay(100);

      break;
      
  }

  

}

