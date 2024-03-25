#include "display.hpp"

//OLED Display
OLED Display(PIN_SCREEN_SDA, PIN_SCREEN_SCL, NO_RESET_PIN, OLED::W_128, OLED::H_64, OLED::CTRL_SH1106, 0x3C);

displayStatus_t displayStatus = DISPLAY_OFF;

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

//IMU
extern WT901C IMU;

//Pi
extern rpi_state_t rpiState;
extern rpiMessage rxMessage;

//Pi status strings
String rpiStateStrings[] = {"OFF", "WAITING", "DATA GOOD", "DATA ERROR", "LOST COMMS"};
String rpiStatusStrings[] = {"IDLE", "OK", "ERROR", "PHOTO SUCCESS", "PHOTO ERROR", "RTL SUCCESS", "RTL ERROR", "RTL RESET"};




void setupDisplay() {
  Display.begin();
  Display.clear();
  Display.display();
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

//Board status screen
void drawBoardStatusScreen() {

  //Battery Voltage
  Display.setCursor(4, 0);
  Display.print("BATT(V): ");
  Display.setCursor(SCREEN_WIDTH / 2, 0);
  Display.print(batteryVoltage.getVoltage());

  //Battery Current
  Display.setCursor(4, 8);
  Display.print("BATT(A): ");
  Display.setCursor(SCREEN_WIDTH / 2, 8);
  Display.print(batteryCurrent.getCurrent());

  //Main 5V Voltage
  Display.setCursor(4, 16);
  Display.print("5V(V): ");
  Display.setCursor(SCREEN_WIDTH / 2, 16);
  Display.print(main5vVoltage.getVoltage());

  //Pi 5V Voltage
  Display.setCursor(4, 24);
  Display.print("PI(V): ");
  Display.setCursor(SCREEN_WIDTH / 2, 24);
  Display.print(pi5vVoltage.getVoltage());

  //Temperature Up
  Display.setCursor(4, 32);
  Display.print("T_UP(C): ");
  Display.setCursor(SCREEN_WIDTH / 2, 32);
  Display.print(tempUp.getTempCelcius());

  //Temperature Down
  Display.setCursor(4, 40);
  Display.print("T_DN(C): ");
  Display.setCursor(SCREEN_WIDTH / 2, 40);
  Display.print(tempDown.getTempCelcius());

  //Raspberry Pi Status
  Display.setCursor(4, 48);
  Display.print("RPI: ");
  Display.setCursor(SCREEN_WIDTH * 0.3, 48);
  if (rpiState == RPI_STATE_DATA_GOOD) {
    Display.print(rpiStatusStrings[rxMessage.status]);
  } else {
    Display.print(rpiStateStrings[rpiState]);
  }

  //Raspberry Pi Message
  Display.setCursor(4, 56);
  Display.print(rxMessage.message);


  Display.display();
}

