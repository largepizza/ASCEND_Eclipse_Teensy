#include "rpi_serial.hpp"


//RPI Variables
rpi_state_t rpiState = RPI_STATE_POWER_OFF;


//Global Variables
extern PowerSwitch piSwitch;

//Serial Transfer Object
SerialTransfer myTransfer;



piStruct rxStruct;
rpiMessage rxMessage;

uint32_t t_lastMsg = 0;

void enableRPI() {
    piSwitch.enable();
    rpiState = RPI_STATE_POWER_WAITING;
}

void disableRPI() {
    piSwitch.disable();
    rpiState = RPI_STATE_POWER_OFF;
}

void rpiSerialSetup() {
    //Serial7
    Serial7.begin(115200);
    myTransfer.begin(Serial7);
}

void rpiSerialLoop() {
    //Check for new data
    if (myTransfer.available()) {
        t_lastMsg = millis();

        uint32_t recSize = 0;

        //Extract the received data
        recSize = myTransfer.rxObj(rxStruct, recSize);


        //Get string data
        char buffer[256];
        recSize = myTransfer.rxObj(buffer, recSize);

        // Convert the buffer to a stringstream for easy parsing
        std::stringstream ss(buffer);

        // Variables to hold the parsed values
        int hour, minute, second;
        std::string message;

        // Temporary variable to hold the pieces as we split them
        std::string segment;

        // Get the hour
        std::getline(ss, segment, ',');
        hour = std::stoi(segment);

        // Get the minute
        std::getline(ss, segment, ',');
        minute = std::stoi(segment);

        // Get the second
        std::getline(ss, segment, ',');
        second = std::stoi(segment);

        // The rest of the line is the message
        std::getline(ss, message);

        // Assign the parsed values to the rxMessage struct
        rxMessage.hour = hour;
        rxMessage.minute = minute;
        rxMessage.second = second;
        rxMessage.status = rxStruct.status;
        strncpy(rxMessage.message, message.c_str(), 128);
        
            






        //Print out the received data
        Serial.print("T: ");
        Serial.print(rxMessage.hour);
        Serial.print(":");
        Serial.print(rxMessage.minute);
        Serial.print(":");
        Serial.print(rxMessage.second);
        Serial.print(" S: ");
        Serial.print(rxMessage.status);
        Serial.print(" M: ");
        Serial.println(message.c_str());


        if (rxMessage.status == RPI_STATUS_IDLE) {
            RPI_STATE_DATA_ERROR;
        }
        else {
            rpiState = RPI_STATE_DATA_GOOD;
        }

    }

    //Check for timeout
    if (millis() - t_lastMsg > RPI_TIMEOUT && rpiState != RPI_STATE_POWER_WAITING && rpiState != RPI_STATE_POWER_OFF) {
        rpiState = RPI_STATE_LOST_CONNECTION;
    }

}
