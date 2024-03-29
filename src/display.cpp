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
extern piStruct rxMessage;

//Pi status strings
String rpiStateStrings[] = {"OFF", "WAITING", "DATA GOOD", "DATA ERROR", "LOST COMMS", "SHUTDOWN"};

extern sd_logger_t sdLoggerStatus;





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

  //Divide the screen into 3 sections, two on the top half and one on the bottom half
  //Top left: Battery section: voltage, current, temp.
  //Top right: PCB section: 5v voltage, temp up
  //Bottom: Pi section: rpi status, system status, camera status, rtl status, pi voltage, temp down

  //Draw dividing horizontal line
  Display.draw_line(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, OLED::tColor::WHITE);
  //Draw dividing vertical line
  Display.draw_line(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, OLED::tColor::WHITE);

  //Draw rectangle top fill
  Display.draw_rectangle(0, 0, SCREEN_WIDTH, 8, OLED::tFillmode::HOLLOW, OLED::tColor::WHITE);
  Display.draw_rectangle(0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2 + 8, OLED::tFillmode::HOLLOW, OLED::tColor::WHITE);

  //Battery Section Top left
  Display.setCursor(SCREEN_MARGIN, TEXT_ALIGN);
  Display.print("Battery");
  Display.setCursor(SCREEN_MARGIN, TEXT_ALIGN + TEXT_SPACING);
  Display.print("V: ");
  Display.print(batteryVoltage.getVoltage(), 2);
  Display.setCursor(SCREEN_MARGIN, TEXT_ALIGN + 2 * TEXT_SPACING);
  Display.print("I: ");
  Display.print(batteryCurrent.getCurrent(), 2);
  Display.setCursor(SCREEN_MARGIN, TEXT_ALIGN + 3 * TEXT_SPACING);
  Display.print("T: ");
  Display.print(tempDown.getTempCelcius(), 2);

  //PCB Section Top right
  Display.setCursor(SCREEN_WIDTH / 2 + SCREEN_MARGIN, TEXT_ALIGN);
  Display.print("PCB");
  Display.setCursor(SCREEN_WIDTH / 2 + SCREEN_MARGIN, TEXT_ALIGN + TEXT_SPACING);
  Display.print("V: ");
  Display.print(main5vVoltage.getVoltage(), 2);
  Display.setCursor(SCREEN_WIDTH / 2 + SCREEN_MARGIN, TEXT_ALIGN + 2 * TEXT_SPACING);
  Display.print("T: ");
  Display.print(tempUp.getTempCelcius(), 2);
  Display.setCursor(SCREEN_WIDTH / 2 + SCREEN_MARGIN, TEXT_ALIGN + 3 * TEXT_SPACING);
  Display.print("SD: ");
  switch (sdLoggerStatus) {
    case SD_LOGGER_OFF:
      Display.print("OFF");
      break;
    case SD_LOGGER_ON:
      Display.print("ON");
      break;
    case SD_LOGGER_RECORDING:
      Display.print("REC");
      break;
    case SD_LOGGER_ERROR:
      Display.print("ERR");
      break;
  }
  
  

  //Pi Section Bottom
  Display.setCursor(SCREEN_MARGIN, SCREEN_HEIGHT / 2 + TEXT_ALIGN);
  Display.print("RPI: ");
  Display.print(rpiStateStrings[rpiState]);
  Display.setCursor(SCREEN_MARGIN, SCREEN_HEIGHT / 2 + TEXT_ALIGN + TEXT_SPACING);
  Display.print("SYS: ");
  switch (rxMessage.status) {
    case SYS_STATE_IDLE:
      Display.print("OFF");
      break;
    case SYS_STATE_OK:
      Display.print("OK");
      break;
    case SYS_STATE_ERROR:
      Display.print("ERR");
      break;
    case SYS_STATE_SHUTDOWN:
      Display.print("BYE :)");
      break;
  }
  Display.setCursor(SCREEN_MARGIN, SCREEN_HEIGHT / 2 + TEXT_ALIGN + 2 * TEXT_SPACING);
  Display.print("CAM: ");
  switch (rxMessage.camera) {
    case PHOTO_OFF:
      Display.print("OFF");
      break;
    case PHOTO_SUCCESS:
      Display.print("OK");
      break;
    case PHOTO_ERROR:
      Display.print("ERR");
      break;
  }
  Display.setCursor(SCREEN_MARGIN, SCREEN_HEIGHT / 2 + TEXT_ALIGN + 3 * TEXT_SPACING);
  Display.print("RTL: ");
  switch (rxMessage.rtl) {
    case RTL_INACTIVE:
      Display.print("OFF");
      break;
    case RTL_ACTIVE:
      Display.print("OK");
      break;
    case RTL_FAIL:
      Display.print("ERR");
      break;
  }

  //Bottom right side
  Display.setCursor(SCREEN_WIDTH / 2 + SCREEN_MARGIN, SCREEN_HEIGHT / 2 + TEXT_ALIGN + TEXT_SPACING);
  Display.print("V: ");
  Display.print(pi5vVoltage.getVoltage(), 2);
  Display.setCursor(SCREEN_WIDTH / 2 + SCREEN_MARGIN, SCREEN_HEIGHT / 2 + TEXT_ALIGN + 2 * TEXT_SPACING);
  Display.print("T: ");
  Display.print(tempDown.getTempCelcius(), 2);
  //Print time
  Display.setCursor(SCREEN_WIDTH / 2 + SCREEN_MARGIN, SCREEN_HEIGHT / 2 + TEXT_ALIGN + 3 * TEXT_SPACING);
  Display.print(rxMessage.hour);
  Display.print(":");
  Display.print(rxMessage.minute);
  Display.print(":");
  Display.print(rxMessage.second);

  

  


  
}

