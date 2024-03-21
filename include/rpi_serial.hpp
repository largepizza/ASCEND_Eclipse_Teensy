#ifndef RPI_SERIAL_H
#define RPI_SERIAL_H


#include <Arduino.h>
#include "pinout.h"
#include "system.hpp"
#include "sensors.hpp"

typedef enum : uint32_t {
    RPI_STATUS_POWER_OFF,
    RPI_STATUS_POWER_WAITING,
    RPI_STATUS_DATA_GOOD,
} rpi_status_t;




//Global Variables
extern rpi_status_t rpiStatus;

//Function Prototypes
void enableRPI();
void disableRPI();


#endif // RPI_SERIAL_H