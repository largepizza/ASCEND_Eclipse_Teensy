#include "rpi_serial.hpp"


//RPI Variables
rpi_state_t rpiState = RPI_STATE_POWER_OFF;


//Global Variables
extern PowerSwitch piSwitch;

//Serial Transfer Object
SerialTransfer myTransfer;




piStruct rxMessage;

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
        recSize = myTransfer.rxObj(rxMessage, recSize);




        //Print out the received data
        Serial.print("T: ");
        Serial.print(rxMessage.hour);
        Serial.print(":");
        Serial.print(rxMessage.minute);
        Serial.print(":");
        Serial.print(rxMessage.second);
        Serial.print(" S: ");
        Serial.print(rxMessage.status);



        if (rxMessage.status == SYS_STATE_IDLE) {
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
