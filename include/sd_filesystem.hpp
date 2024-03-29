#ifndef SD_FILESYSTEM_H
#define SD_FILESYSTEM_H

#include <Arduino.h>
#include "pinout.h"
#include <SD.h>
#include <memory>
#include <vector>
#include <sstream>
#include <EEPROM.h>

#define IMU_LOG_INTERVAL 50
#define DATA_LOG_INTERVAL 200

#define NAME_MAX_LENGTH 32
#define PRINT_BUFFER_SIZE 32 // Adjust as needed based on expected data size

#define LINE_BUFFER_SIZE 1024


// DataUnion can hold either a float or an int in the same memory location
union DataUnion {
    float fData;
    int iData;
};

// Enum for data type
enum DataType { FLOAT, INT };

// DataVariable class definition
class DataVariable {
private:
    union DataUnion data;
    DataType type;
    char name[NAME_MAX_LENGTH];

public:

    // Constructor with name initialization
    DataVariable(const char* initName, DataType initType) : type(initType) {
        // Safely copy the name to the internal character array
        strncpy(name, initName, NAME_MAX_LENGTH);
        // Ensure null termination
        name[NAME_MAX_LENGTH - 1] = '\0';
    }

    // Returns the name of the data variable
    const char* getName() const {
        return name;
    }

    void print(char * buffer) {
        switch (type) {
            case FLOAT:
                dtostrf((float)data.fData, 0 , 4, buffer);
                Serial.print(data.fData);
                Serial.print(" ");
                break;
            case INT:
                // Format int
                snprintf(buffer, PRINT_BUFFER_SIZE, "%d", (int)data.iData);
                Serial.print(data.iData);
                Serial.print(" ");
                break;
            default:
                // Handle unknown type
                strncpy(buffer, "ERROR", PRINT_BUFFER_SIZE);
        }
        Serial.println(buffer);
    }

    void setValue(float value) {
        data.fData = value;
    }

    void setValue(int value) {
        data.iData = value;
    }

    float getFloat() const {
        return data.fData;
    }

    int getInt() const {
        return data.iData;
    }


};

// DataComposite class definition
class DataComposite {
private:
    std::vector<std::shared_ptr<DataVariable>> dataVariables;
    char directoryPath[32];
    char logFileName[32];

    char filePath[128];
    char lineBuffer[LINE_BUFFER_SIZE];
    char buffer[PRINT_BUFFER_SIZE];
    File logFile;

    uint32_t logInterval = 1000;
    uint32_t t_lastLog = 0;



public:

    void addVariable(std::shared_ptr<DataVariable> variable) {
        dataVariables.push_back(variable);
    }

    void begin(char * directoryPath_in, char * logFileName_in) {
        strncpy(this->directoryPath, directoryPath_in, sizeof(this->directoryPath));
        strncpy(this->logFileName, logFileName_in, sizeof(this->logFileName));
        sprintf(filePath, "%s/%s.csv", directoryPath, logFileName);
        Serial.println(filePath);
        writeHeader();
    }

    void setInterval(uint32_t interval) {
        logInterval = interval;
    }


    void logData() {

        logFile = SD.open(filePath, FILE_WRITE);
        if (!logFile) {
            return; // Log file not opened properly
        }

        //Clear line buffer
        memset(lineBuffer, ' ', LINE_BUFFER_SIZE);
        //Set null terminator
        lineBuffer[0] = '\0';

        uint16_t count = 0;
        for (std::shared_ptr<DataVariable> var : dataVariables) {
            if (count > 0) {
                strcat(lineBuffer, ",");
            }
            var->print(buffer);
            strcat(lineBuffer, buffer);
            count++;
        }
        logFile.println(lineBuffer);

        logFile.close();
    }

    void writeHeader() {

        logFile = SD.open(filePath, FILE_WRITE);

        if (!logFile) {
            return; // Log file not opened properly
        }

        //Clear line buffer
        memset(lineBuffer, ' ', LINE_BUFFER_SIZE);
        //Set null terminator
        lineBuffer[0] = '\0';

        uint16_t count = 0;
        for (std::shared_ptr<DataVariable> var : dataVariables) {
            if (count > 0) {
                strcat(lineBuffer, ",");
            }
            strcat(lineBuffer, var->getName());
            count++;
        }
        logFile.println(lineBuffer);

        logFile.close();
    }

    bool ready() {
        if (millis() - t_lastLog > logInterval) {
            return true;
            t_lastLog = millis();
        }
        return false;
    }



    void end() {
        if (logFile) {
            logFile.close();
        }
        // Additional cleanup logic if needed
    }
};

void setupSDLogger();
void setupDataLog();
void setupIMULog();
void setupDirectory();
uint32_t findNextDirectoryIndex();


// Extern Data Variables

// Declare extern shared pointers for all DataVariables
extern std::shared_ptr<DataVariable> timestampDataVar;
extern std::shared_ptr<DataVariable> piHourVar;
extern std::shared_ptr<DataVariable> piMinuteVar;
extern std::shared_ptr<DataVariable> piSecondVar;

extern std::shared_ptr<DataVariable> systemStatusVar;
extern std::shared_ptr<DataVariable> rpiStateVar;
extern std::shared_ptr<DataVariable> rpiSystemStateVar;
extern std::shared_ptr<DataVariable> rpiCameraStateVar;
extern std::shared_ptr<DataVariable> rpiRTLStateVar;

extern std::shared_ptr<DataVariable> batteryVoltageVar;
extern std::shared_ptr<DataVariable> main5vVoltageVar;
extern std::shared_ptr<DataVariable> pi5vVoltageVar;

extern std::shared_ptr<DataVariable> batteryCurrentVar;

extern std::shared_ptr<DataVariable> tempUpVar;
extern std::shared_ptr<DataVariable> tempDownVar;

extern std::shared_ptr<DataVariable> tempRTLVar;
extern std::shared_ptr<DataVariable> tempExternalVar;
extern std::shared_ptr<DataVariable> tempAntennaVar;
extern std::shared_ptr<DataVariable> tempBattDownVar;
extern std::shared_ptr<DataVariable> tempBattUpVar;

extern std::shared_ptr<DataVariable> timestampIMUVar;
extern std::shared_ptr<DataVariable> imuAccelXVar;
extern std::shared_ptr<DataVariable> imuAccelYVar;
extern std::shared_ptr<DataVariable> imuAccelZVar;
extern std::shared_ptr<DataVariable> imuGyroXVar;
extern std::shared_ptr<DataVariable> imuGyroYVar;
extern std::shared_ptr<DataVariable> imuGyroZVar;
extern std::shared_ptr<DataVariable> imuMagXVar;
extern std::shared_ptr<DataVariable> imuMagYVar;
extern std::shared_ptr<DataVariable> imuMagZVar;
extern std::shared_ptr<DataVariable> imuAngleXVar;
extern std::shared_ptr<DataVariable> imuAngleYVar;
extern std::shared_ptr<DataVariable> imuAngleZVar;



#endif // SD_FILESYSTEM_H