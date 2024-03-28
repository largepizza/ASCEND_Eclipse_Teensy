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
Thermistor tempRTL(PIN_TEMP1, 100000, 100000, 25, 3950);
Thermistor tempExternal(PIN_TEMP2, 100000, 100000, 25, 3950);
Thermistor tempAntenna(PIN_TEMP3, 100000, 100000, 25, 3950);
Thermistor tempBattDown(PIN_TEMP4, 100000, 100000, 25, 3950);
Thermistor tempBattUp(PIN_TEMP5, 100000, 100000, 25, 3950);