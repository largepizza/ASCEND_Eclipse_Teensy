#include <system.hpp>


//Global Variables
status_t systemStatus = STATUS_POWER_ON;
boot_menu_t bootMenuStatus = BOOT_MENU_DATA_LOGGER;
button_t buttonStatus = BUTTON_UNPRESSED;

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
  //pinMode(PIN_IMU_SDA, OUTPUT);
  //pinMode(PIN_IMU_SCL, OUTPUT);

  //Button ISR
  attachInterrupt(digitalPinToInterrupt(PIN_BUTTON), buttonHandler, FALLING);

}

void buttonHandler() {
  getButton();
}

void getButton() {
  if (digitalRead(PIN_BUTTON) == LOW) {
    buttonStatus = BUTTON_PRESSED;
  }
  else {
    buttonStatus = BUTTON_UNPRESSED;
  }
}

