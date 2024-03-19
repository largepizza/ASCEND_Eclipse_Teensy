#include <Arduino.h>
#include "pinout.h"
#include "system.hpp"
#include "sd_filesystem.hpp"
#include "display.hpp"

#


//Global Variables


//Status Power On Variables
uint32_t t_powerOn = 0;
float powerOnHold = 0;


void setup() {

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
        powerOnHold++;
        t_powerOn += 20;
        delay(5);
      }
      getButton();

      Display.clear();
      drawProgressBar(SCREEN_WIDTH / 2, 55, SCREEN_WIDTH / 2, 8, powerOnHold);
      displayPowerOnScreen();


      if (powerOnHold > 100) {
        systemStatus = STATUS_BOOT_MENU;
      }
      if (millis() - t_powerOn > 3000) {
        systemStatus = STATUS_DATA_LOGGER;
      }
      
      break;
    case STATUS_BOOT_MENU:
      //Display Boot Menu
      Display.clear();
      Display.setCursor(0, 0);
      Display.print("Boot Menu");
      Display.display();

      delay(100);

      break;
    case STATUS_DATA_LOGGER:
      //Data Logger
      Display.clear();
      Display.setCursor(0, 0);
      Display.print("Data Logger");
      Display.display();

      delay(100);

      break;
      
  }

  

}

