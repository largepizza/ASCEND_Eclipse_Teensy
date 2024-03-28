#include "sd_filesystem.hpp"

;
DataComposite dataLog;
DataComposite imuLog;



///Data Variables

//Timestamp
DataVariable timestampDataVar("Time (mS)", INT);
DataVariable piHourVar("Hour", INT);
DataVariable piMinuteVar("Minute", INT);
DataVariable piSecondVar("Second", INT);

//System Status
DataVariable systemStatusVar("System Status", INT);
DataVariable rpiStateVar("Raspberry Pi State", INT);
DataVariable rpiSystemStateVar("Raspberry Pi System State", INT);
DataVariable rpiCameraStateVar("Raspberry Pi Camera State", INT);
DataVariable rpiRTLStateVar("Raspberry Pi RTL State", INT);

//Voltage Sensors
DataVariable batteryVoltageVar("Battery Voltage (V)", FLOAT);
DataVariable main5vVoltageVar("Main 5V Voltage (V)", FLOAT);
DataVariable pi5vVoltageVar("Pi 5V Voltage (V)", FLOAT);

//Current Sensors
DataVariable batteryCurrentVar("Battery Current (A)", FLOAT);

//Thermistors
DataVariable tempUpVar("PCB Top Temp (C)", FLOAT);
DataVariable tempDownVar("PCB Bottom Temp (C)", FLOAT);

//External Thermistors
DataVariable tempRTLVar("RTL Temp (C)", FLOAT);
DataVariable tempExternalVar("External Temp (C)", FLOAT);
DataVariable tempAntennaVar("Antenna Temp (C)", FLOAT);
DataVariable tempBattDownVar("Battery Down Temp (C)", FLOAT);
DataVariable tempBattUpVar("Battery Up Temp (C)", FLOAT);

//IMU

DataVariable timestampIMUVar("IMU Time (mS)", INT);
DataVariable imuAccelXVar("IMU Accel X (m/s^2)", FLOAT);
DataVariable imuAccelYVar("IMU Accel Y (m/s^2)", FLOAT);
DataVariable imuAccelZVar("IMU Accel Z (m/s^2)", FLOAT);
DataVariable imuGyroXVar("IMU Gyro X (deg/s)", FLOAT);
DataVariable imuGyroYVar("IMU Gyro Y (deg/s)", FLOAT);
DataVariable imuGyroZVar("IMU Gyro Z (deg/s)", FLOAT);
DataVariable imuMagXVar("IMU Mag X (uT)", FLOAT);
DataVariable imuMagYVar("IMU Mag Y (uT)", FLOAT);
DataVariable imuMagZVar("IMU Mag Z (uT)", FLOAT);
DataVariable imuAngleXVar("IMU Angle X (deg)", FLOAT);
DataVariable imuAngleYVar("IMU Angle Y (deg)", FLOAT);
DataVariable imuAngleZVar("IMU Angle Z (deg)", FLOAT);

//Setup
void setupDataLog() {
    //Add variables to dataLog

    //Timestamp
    dataLog.addVariable(std::make_shared<DataVariable>(timestampDataVar));
    dataLog.addVariable(std::make_shared<DataVariable>(piHourVar));
    dataLog.addVariable(std::make_shared<DataVariable>(piMinuteVar));
    dataLog.addVariable(std::make_shared<DataVariable>(piSecondVar));

    //System Status
    dataLog.addVariable(std::make_shared<DataVariable>(systemStatusVar));
    dataLog.addVariable(std::make_shared<DataVariable>(rpiStateVar));
    dataLog.addVariable(std::make_shared<DataVariable>(rpiSystemStateVar));
    dataLog.addVariable(std::make_shared<DataVariable>(rpiCameraStateVar));
    dataLog.addVariable(std::make_shared<DataVariable>(rpiRTLStateVar));

    //Voltage Sensors
    dataLog.addVariable(std::make_shared<DataVariable>(batteryVoltageVar));
    dataLog.addVariable(std::make_shared<DataVariable>(main5vVoltageVar));
    dataLog.addVariable(std::make_shared<DataVariable>(pi5vVoltageVar));

    //Current Sensors
    dataLog.addVariable(std::make_shared<DataVariable>(batteryCurrentVar));

    //Thermistors
    dataLog.addVariable(std::make_shared<DataVariable>(tempUpVar));
    dataLog.addVariable(std::make_shared<DataVariable>(tempDownVar));

    //External Thermistors
    dataLog.addVariable(std::make_shared<DataVariable>(tempRTLVar));
    dataLog.addVariable(std::make_shared<DataVariable>(tempExternalVar));
    dataLog.addVariable(std::make_shared<DataVariable>(tempAntennaVar));
    dataLog.addVariable(std::make_shared<DataVariable>(tempBattDownVar));
    dataLog.addVariable(std::make_shared<DataVariable>(tempBattUpVar));


}

void setupIMULog() {
    //Add variables to imuLog

    //Timestamp
    imuLog.addVariable(std::make_shared<DataVariable>(timestampIMUVar));

    //IMU
    imuLog.addVariable(std::make_shared<DataVariable>(imuAccelXVar));
    imuLog.addVariable(std::make_shared<DataVariable>(imuAccelYVar));
    imuLog.addVariable(std::make_shared<DataVariable>(imuAccelZVar));
    imuLog.addVariable(std::make_shared<DataVariable>(imuGyroXVar));
    imuLog.addVariable(std::make_shared<DataVariable>(imuGyroYVar));
    imuLog.addVariable(std::make_shared<DataVariable>(imuGyroZVar));
    imuLog.addVariable(std::make_shared<DataVariable>(imuMagXVar));
    imuLog.addVariable(std::make_shared<DataVariable>(imuMagYVar));
    imuLog.addVariable(std::make_shared<DataVariable>(imuMagZVar));
    imuLog.addVariable(std::make_shared<DataVariable>(imuAngleXVar));
    imuLog.addVariable(std::make_shared<DataVariable>(imuAngleYVar));
    imuLog.addVariable(std::make_shared<DataVariable>(imuAngleZVar));


}






