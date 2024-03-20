#include <system.hpp>



//Global Variables
status_t systemStatus = STATUS_POWER_ON;
boot_menu_t bootMenuStatus = BOOT_MENU_DATA_LOGGER;
button_t buttonStatus = BUTTON_UNPRESSED;

//Button Hysterisis
uint32_t t_button = 0;

//IMU
WT901C IMU;

void setupPins() {

  //Board Buttons
  pinMode(PIN_BUTTON, INPUT);

  //Board Thermistors
  pinMode(PIN_TEMP_UP, INPUT);
  pinMode(PIN_TEMP_DOWN, INPUT);

  //External Thermistors
  pinMode(PIN_TEMP1, INPUT);
  pinMode(PIN_TEMP2, INPUT);
  pinMode(PIN_TEMP3, INPUT);
  pinMode(PIN_TEMP4, INPUT);
  pinMode(PIN_TEMP5, INPUT);

  //OLED Screen
  pinMode(PIN_SCREEN_EN, OUTPUT);
  pinMode(PIN_SCREEN_FAULT, INPUT);
  //pinMode(PIN_SCREEN_SDA, OUTPUT);
  //pinMode(PIN_SCREEN_SCL, OUTPUT);

  //Raspberry Pi - Serial7
  pinMode(PIN_RPI_EN, OUTPUT);
  pinMode(PIN_RPI_FAULT, INPUT);
  //pinMode(PIN_RPI_TX, OUTPUT);
  //pinMode(PIN_RPI_RX, INPUT);

  //IMU - Serial4
  //pinMode(PIN_IMU_TX, OUTPUT);
  //pinMode(PIN_IMU_RX, INPUT);

  //IMU - I2C


  //Button ISR
  attachInterrupt(PIN_BUTTON, buttonHandler, CHANGE);

}

button_t lastStatus;

void buttonHandler() {

  button_t buttonStatusTemp;
  
  if (digitalRead(PIN_BUTTON) == LOW) {
    buttonStatusTemp = BUTTON_PRESSED;
  }
  else {
    buttonStatusTemp = BUTTON_UNPRESSED;
  }


  if (millis() - t_button > BUTTON_HYSTERISIS && buttonStatusTemp != lastStatus) {
    t_button = millis();
    buttonStatus = buttonStatusTemp;
    printButtonStatus();
  }
  
  lastStatus = buttonStatusTemp;
}


void printButtonStatus() {
  if (buttonStatus == BUTTON_PRESSED) {
    Serial.println("Button Pressed");
  }
  else {
    Serial.println("Button Unpressed");
  }
}

