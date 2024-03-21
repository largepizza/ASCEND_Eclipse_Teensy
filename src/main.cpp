#include <Arduino.h>
#include "pinout.h"
#include "system.hpp"
#include "sd_filesystem.hpp"
#include "display.hpp"
#include "sensors.hpp"
//#include <wt901c.hpp>


//Global Variables
extern status_t systemStatus;
extern boot_menu_t bootMenuStatus;
extern button_t buttonStatus;
extern uint32_t t_button;
extern WT901C IMU;

//Power Switches
extern PowerSwitch screenSwitch;
extern PowerSwitch piSwitch;

//Voltage Sensors
extern Voltage batteryVoltage;
extern Voltage main5vVoltage;
extern Voltage pi5vVoltage;

//Current Sensors
extern Current batteryCurrent;

//Thermistors
extern Thermistor tempUp;
extern Thermistor tempDown;


//Status Power On Variables
uint32_t t_powerOn = 0;
float powerOnHold = 0;

//Status Boot Menu Variables
bool buttonHold = false;
float bootMenuHold = 0;

//Status Data Logger Variables
uint32_t t_screenRefresh = 0;



void setup() {

  digitalWrite(LED_BUILTIN, HIGH);


  //Setup Serial
  Serial.begin(115200);
  setupPins();

  IMU.init();


  
  t_powerOn = millis();

  screenSwitch.enable();
  setupDisplay();
}

void loop() {

  //State Machine
  switch (systemStatus) {
    case STATUS_POWER_ON:
    {
      /*
      
      ██████   ██████  ██     ██ ███████ ██████       ██████  ███    ██ 
      ██   ██ ██    ██ ██     ██ ██      ██   ██     ██    ██ ████   ██ 
      ██████  ██    ██ ██  █  ██ █████   ██████      ██    ██ ██ ██  ██ 
      ██      ██    ██ ██ ███ ██ ██      ██   ██     ██    ██ ██  ██ ██ 
      ██       ██████   ███ ███  ███████ ██   ██      ██████  ██   ████ 
                                                                                                                              
      */
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
        digitalWrite(LED_BUILTIN, LOW);
        systemStatus = STATUS_BOOT_MENU;
      }
      if (millis() - t_powerOn > 3000) {
        //Data Logger if button is not held
        digitalWrite(LED_BUILTIN, LOW);
        systemStatus = STATUS_DATA_LOGGER;
      }
      
      break;
    }
    case STATUS_BOOT_MENU:
    {
    /*
        
    ██████   ██████   ██████  ████████     ███    ███ ███████ ███    ██ ██    ██ 
    ██   ██ ██    ██ ██    ██    ██        ████  ████ ██      ████   ██ ██    ██ 
    ██████  ██    ██ ██    ██    ██        ██ ████ ██ █████   ██ ██  ██ ██    ██ 
    ██   ██ ██    ██ ██    ██    ██        ██  ██  ██ ██      ██  ██ ██ ██    ██ 
    ██████   ██████   ██████     ██        ██      ██ ███████ ██   ████  ██████  
                                                                                                                                                    
    */
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
    }
    case STATUS_DATA_LOGGER:
    {
    /*
    
    ██████   █████  ████████  █████      ██       ██████   ██████   ██████  ███████ ██████  
    ██   ██ ██   ██    ██    ██   ██     ██      ██    ██ ██       ██       ██      ██   ██ 
    ██   ██ ███████    ██    ███████     ██      ██    ██ ██   ███ ██   ███ █████   ██████  
    ██   ██ ██   ██    ██    ██   ██     ██      ██    ██ ██    ██ ██    ██ ██      ██   ██ 
    ██████  ██   ██    ██    ██   ██     ███████  ██████   ██████   ██████  ███████ ██   ██ 
                                                                                                                                                                        
    */

      //Sensor Data Reads
      //Voltage
      batteryVoltage.read();
      main5vVoltage.read();
      pi5vVoltage.read();
      
      //Current
      batteryCurrent.read();

      //Thermistors
      tempUp.read();
      tempDown.read();






      //RPI Communication

      //Remove before flight, button to enable RPI
      if (buttonStatus == BUTTON_PRESSED) {
        enableRPI();
      }


      //Save to SD Card


      //Display Data Logger Screen
      if (screenSwitch.getStatus()) {
        if (millis() - t_screenRefresh > REFRESH_RATE) {
          t_screenRefresh = millis();

          Display.clear();
          drawBoardStatusScreen();
          Display.display();

        }
      }




      break;
    }
    case STATUS_IMU_DATA:
    {
      /*
      
      ██ ███    ███ ██    ██     ██████   █████  ████████  █████  
      ██ ████  ████ ██    ██     ██   ██ ██   ██    ██    ██   ██ 
      ██ ██ ████ ██ ██    ██     ██   ██ ███████    ██    ███████ 
      ██ ██  ██  ██ ██    ██     ██   ██ ██   ██    ██    ██   ██ 
      ██ ██      ██  ██████      ██████  ██   ██    ██    ██   ██ 
                                                                                      
      */
      //IMU Data
      IMU.getDataBasic();
      float accelX = IMU.fAcc[0]; /* get accelerometer X value */
      float accelY = IMU.fAcc[1];/* get accelerometer Y value */
      float accelZ = IMU.fAcc[2];/* get accelerometer Z value */

      float angleX = IMU.fAngle[0]; /* get mag X value */
      float angleY = IMU.fAngle[1];/* get mag Y value */
      float angleZ = IMU.fAngle[2];/* get mag Z value */


      Display.clear();
      //Display Accelerometer Data
      Display.setCursor(4, 0);
      Display.print("Accel");
      Display.setCursor(0, 8);
      Display.print("X: ");
      Display.print(accelX);
      Display.setCursor(0, 16);
      Display.print("Y: ");
      Display.print(accelY);
      Display.setCursor(0, 24);
      Display.print("Z: ");
      Display.print(accelZ);

      //Display Magnetometer Data
      Display.setCursor(4, 32);
      Display.print("Angles");
      Display.setCursor(0, 40);
      Display.print("X: ");
      Display.print(angleX);
      Display.setCursor(0, 48);
      Display.print("Y: ");
      Display.print(angleY);
      Display.setCursor(0, 56);
      Display.print("Z: ");
      Display.print(angleZ);

      //Compass
      drawCompass(SCREEN_WIDTH / 2 + SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2, 30);

      
      Display.display();

      break;
    }
    case STATUS_IMU_CALIBRATION:
    {
    
      /*
      ██ ███    ███ ██    ██      ██████  █████  ██      ██ ██████  ██████   █████  ████████ ██  ██████  ███    ██ 
      ██ ████  ████ ██    ██     ██      ██   ██ ██      ██ ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ████   ██ 
      ██ ██ ████ ██ ██    ██     ██      ███████ ██      ██ ██████  ██████  ███████    ██    ██ ██    ██ ██ ██  ██ 
      ██ ██  ██  ██ ██    ██     ██      ██   ██ ██      ██ ██   ██ ██   ██ ██   ██    ██    ██ ██    ██ ██  ██ ██ 
      ██ ██      ██  ██████       ██████ ██   ██ ███████ ██ ██████  ██   ██ ██   ██    ██    ██  ██████  ██   ████ 
      */



      //IMU Calibration
      Display.clear();
      Display.setCursor(0, 0);
      Display.print("IMU Calibration");
      Display.display();

      break;
    }
    case STATUS_PI_STANDBY:
    {
      /*
      
      ██████  ██     ███████ ████████  █████  ███    ██ ██████  ██████  ██    ██ 
      ██   ██ ██     ██         ██    ██   ██ ████   ██ ██   ██ ██   ██  ██  ██  
      ██████  ██     ███████    ██    ███████ ██ ██  ██ ██   ██ ██████    ████   
      ██      ██          ██    ██    ██   ██ ██  ██ ██ ██   ██ ██   ██    ██    
      ██      ██     ███████    ██    ██   ██ ██   ████ ██████  ██████     ██    
                                                                              
      */
      //Pi Standby
      Display.clear();
      Display.setCursor(0, 0);
      Display.print("Pi Standby");
      Display.display();
      
      break;
    }
      
  }

  

}

