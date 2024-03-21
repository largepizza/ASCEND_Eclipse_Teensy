#include "sensors.hpp"

//Voltage Sensors
Voltage batteryVoltage(PIN_BATTERY_VOLTAGE, 20000, 4700);
Voltage main5vVoltage(PIN_5V_MAIN_VOLTAGE, 10000, 10000);
Voltage pi5vVoltage(PIN_5V_PI_VOLTAGE, 10000, 10000);

//Current Sensors
Current batteryCurrent(PIN_BATTERY_CURRENT, 0.0015, 100.0);

//Thermistors
Thermistor tempUp(PIN_TEMP_UP, 10000, 10000, 25, 3380);
Thermistor tempDown(PIN_TEMP_DOWN, 10000, 10000, 25, 3380);

//External Thermistors