#ifndef SD_FILESYSTEM_H
#define SD_FILESYSTEM_H

#include <Arduino.h>
#include "pinout.h"
#include <SD.h>
#include <memory>
#include <vector>
#include <sstream>
#include <EEPROM.h>


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
    DataUnion data;
    DataType type;
    String name;

public:

    DataVariable(String name, DataType type) : name(name), type(type) { }
    

    String getName() const {
        return name;
    }

    String print() const {
        switch (type) {
            case FLOAT: return String(data.fData);
            case INT:   return String(data.iData);
            default:    return "";
        }
    }

    void setValue(float value) {
        data.fData = value;
    }

    void setValue(int value) {
        data.iData = value;
    }


};

// DataComposite class definition
class DataComposite {
private:
    std::vector<std::shared_ptr<DataVariable>> dataVariables;
    String directoryPath;
    String logFileName;

    char filePath[128];
    File logFile;


public:

    void addVariable(std::shared_ptr<DataVariable> variable) {
        dataVariables.push_back(variable);
    }

    void begin(String directoryPath, String logFileName) {
        this->directoryPath = directoryPath;
        this->logFileName = logFileName;
        createDirectory();
        sprintf(filePath, "%s/%s", directoryPath.c_str(), logFileName.c_str());
        writeHeader();
    }


    void logData() {

        logFile = SD.open(filePath, FILE_WRITE);
        if (!logFile) {
            return; // Log file not opened properly
        }

        String logLine;
        for (auto& var : dataVariables) {
            if (logLine.length() > 0) logLine += ",";
            logLine += var->print();
        }
        logFile.println(logLine);

        logFile.close();
    }

    void writeHeader() {

        logFile = SD.open(filePath, FILE_WRITE);

        if (!logFile) {
            return; // Log file not opened properly
        }

        String header;
        for (auto& var : dataVariables) {
            if (header.length() > 0) header += ",";
            header += var->getName();
        }
        logFile.println(header);

        logFile.close();
    }



    void end() {
        if (logFile) {
            logFile.close();
        }
        // Additional cleanup logic if needed
    }
};

void setupSD();
void setupDataLog();
void setupImuLog();
void createDirectory();
uint32_t findNextDirectoryIndex();


#endif // SD_FILESYSTEM_H