#include "sd_filesystem.hpp"

;
DataComposite dataLog;
DataComposite imuLog;



///Data Variables

//Timestamp
std::shared_ptr<DataVariable> timestampDataVar = std::make_shared<DataVariable>("Timestamp", INT);
std::shared_ptr<DataVariable> piHourVar = std::make_shared<DataVariable>("Hour", INT);
std::shared_ptr<DataVariable> piMinuteVar = std::make_shared<DataVariable>("Minute", INT);
std::shared_ptr<DataVariable> piSecondVar = std::make_shared<DataVariable>("Second", INT);

//System Status
std::shared_ptr<DataVariable> systemStatusVar = std::make_shared<DataVariable>("System Status", INT);
std::shared_ptr<DataVariable> rpiStateVar = std::make_shared<DataVariable>("Raspberry Pi State", INT);
std::shared_ptr<DataVariable> rpiSystemStateVar = std::make_shared<DataVariable>("Raspberry Pi System State", INT);
std::shared_ptr<DataVariable> rpiCameraStateVar = std::make_shared<DataVariable>("Raspberry Pi Camera State", INT);
std::shared_ptr<DataVariable> rpiRTLStateVar = std::make_shared<DataVariable>("Raspberry Pi RTL State", INT);

//Voltage Sensors
std::shared_ptr<DataVariable> batteryVoltageVar = std::make_shared<DataVariable>("Battery Voltage (V)", FLOAT);
std::shared_ptr<DataVariable> main5vVoltageVar = std::make_shared<DataVariable>("Main 5V Voltage (V)", FLOAT);
std::shared_ptr<DataVariable> pi5vVoltageVar = std::make_shared<DataVariable>("Raspberry Pi 5V Voltage (V)", FLOAT);

//Current Sensors
std::shared_ptr<DataVariable> batteryCurrentVar = std::make_shared<DataVariable>("Battery Current (A)", FLOAT);

//Thermistors
std::shared_ptr<DataVariable> tempUpVar = std::make_shared<DataVariable>("PCB Top Temp (C)", FLOAT);
std::shared_ptr<DataVariable> tempDownVar = std::make_shared<DataVariable>("PCB Bottom Temp (C)", FLOAT);

//External Thermistors
std::shared_ptr<DataVariable> tempRTLVar = std::make_shared<DataVariable>("RTL Temp (C)", FLOAT);
std::shared_ptr<DataVariable> tempExternalVar = std::make_shared<DataVariable>("External Temp (C)", FLOAT);
std::shared_ptr<DataVariable> tempAntennaVar = std::make_shared<DataVariable>("Antenna Temp (C)", FLOAT);
std::shared_ptr<DataVariable> tempBattDownVar = std::make_shared<DataVariable>("Battery Down Temp (C)", FLOAT);
std::shared_ptr<DataVariable> tempBattUpVar = std::make_shared<DataVariable>("Battery Up Temp (C)", FLOAT);


//IMU

std::shared_ptr<DataVariable> timestampIMUVar = std::make_shared<DataVariable>("IMU Timestamp", INT);
std::shared_ptr<DataVariable> imuAccelXVar = std::make_shared<DataVariable>("IMU Accel X (m/s^2)", FLOAT);
std::shared_ptr<DataVariable> imuAccelYVar = std::make_shared<DataVariable>("IMU Accel Y (m/s^2)", FLOAT);
std::shared_ptr<DataVariable> imuAccelZVar = std::make_shared<DataVariable>("IMU Accel Z (m/s^2)", FLOAT);
std::shared_ptr<DataVariable> imuGyroXVar = std::make_shared<DataVariable>("IMU Gyro X (deg/s)", FLOAT);
std::shared_ptr<DataVariable> imuGyroYVar = std::make_shared<DataVariable>("IMU Gyro Y (deg/s)", FLOAT);
std::shared_ptr<DataVariable> imuGyroZVar = std::make_shared<DataVariable>("IMU Gyro Z (deg/s)", FLOAT);
std::shared_ptr<DataVariable> imuMagXVar = std::make_shared<DataVariable>("IMU Mag X (uT)", FLOAT);
std::shared_ptr<DataVariable> imuMagYVar = std::make_shared<DataVariable>("IMU Mag Y (uT)", FLOAT);
std::shared_ptr<DataVariable> imuMagZVar = std::make_shared<DataVariable>("IMU Mag Z (uT)", FLOAT);
std::shared_ptr<DataVariable> imuAngleXVar = std::make_shared<DataVariable>("IMU Angle X (deg)", FLOAT);
std::shared_ptr<DataVariable> imuAngleYVar = std::make_shared<DataVariable>("IMU Angle Y (deg)", FLOAT);
std::shared_ptr<DataVariable> imuAngleZVar = std::make_shared<DataVariable>("IMU Angle Z (deg)", FLOAT);

//directory counter
uint32_t dirCount = 0;
char dirName[32] = "DIR_0000";


void setupSDLogger() {
        //Initialize dataVariables
        setupDataLog();
        setupIMULog();

        //Set log intervals
        dataLog.setInterval(DATA_LOG_INTERVAL);
        imuLog.setInterval(IMU_LOG_INTERVAL);

        //Initialize directories
        setupDirectory();

        //Begin log files
        dataLog.begin(dirName, "data");
        imuLog.begin(dirName, "imu");
}


void setupDirectory() {

    sprintf(dirName, "DIR_%04d", dirCount);
    Serial.println(dirName);

    //Create directory
    if (!SD.exists(dirName)) {
        SD.mkdir(dirName);
    }
    else {
        Serial.println("Directory already exists");
        dirCount++;
        setupDirectory();
    }

}




//Setup
void setupDataLog() {
    //Add variables to dataLog

    //Timestamp
    dataLog.addVariable((timestampDataVar));
    dataLog.addVariable((piHourVar));
    dataLog.addVariable((piMinuteVar));
    dataLog.addVariable((piSecondVar));

    //System Status
    dataLog.addVariable((systemStatusVar));
    dataLog.addVariable((rpiStateVar));
    dataLog.addVariable((rpiSystemStateVar));
    dataLog.addVariable((rpiCameraStateVar));
    dataLog.addVariable((rpiRTLStateVar));

    //Voltage Sensors
    dataLog.addVariable((batteryVoltageVar));
    dataLog.addVariable((main5vVoltageVar));
    dataLog.addVariable((pi5vVoltageVar));

    //Current Sensors
    dataLog.addVariable((batteryCurrentVar));

    //Thermistors
    dataLog.addVariable((tempUpVar));
    dataLog.addVariable((tempDownVar));

    //External Thermistors
    dataLog.addVariable((tempRTLVar));
    dataLog.addVariable((tempExternalVar));
    dataLog.addVariable((tempAntennaVar));
    dataLog.addVariable((tempBattDownVar));
    dataLog.addVariable((tempBattUpVar));


}

void setupIMULog() {
    //Add variables to imuLog

    //Timestamp
    imuLog.addVariable((timestampIMUVar));

    //IMU
    imuLog.addVariable((imuAccelXVar));
    imuLog.addVariable((imuAccelYVar));
    imuLog.addVariable((imuAccelZVar));
    imuLog.addVariable((imuGyroXVar));
    imuLog.addVariable((imuGyroYVar));
    imuLog.addVariable((imuGyroZVar));
    imuLog.addVariable((imuMagXVar));
    imuLog.addVariable((imuMagYVar));
    imuLog.addVariable((imuMagZVar));
    imuLog.addVariable((imuAngleXVar));
    imuLog.addVariable((imuAngleYVar));
    imuLog.addVariable((imuAngleZVar));


}






