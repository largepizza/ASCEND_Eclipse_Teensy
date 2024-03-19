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
    File logFile;

    void createDirectory() {
        // Directory creation logic goes here
    }



public:

    void addVariable(std::shared_ptr<DataVariable> variable) {
        dataVariables.push_back(variable);
    }


    void logData() {
        if (!logFile) {
            return; // Log file not opened properly
        }

        String logLine;
        for (auto& var : dataVariables) {
            if (logLine.length() > 0) logLine += ",";
            logLine += var->print();
        }
        logFile.println(logLine);
    }

    void end() {
        if (logFile) {
            logFile.close();
        }
        // Additional cleanup logic if needed
    }
};

#endif // SD_FILESYSTEM_H