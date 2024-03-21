#include "rpi_serial.hpp"


//RPI Variables
rpi_status_t rpiStatus = RPI_STATUS_POWER_OFF;


//Global Variables
extern PowerSwitch piSwitch;


void enableRPI() {
    piSwitch.enable();
    rpiStatus = RPI_STATUS_POWER_WAITING;
}

void disableRPI() {
    piSwitch.disable();
    rpiStatus = RPI_STATUS_POWER_OFF;
}
