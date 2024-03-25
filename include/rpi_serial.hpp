#ifndef RPI_SERIAL_H
#define RPI_SERIAL_H


#include <Arduino.h>
#include "pinout.h"
#include "system.hpp"
#include "sensors.hpp"
#include <SerialTransfer.h>

#define RPI_TIMEOUT 3000

typedef enum : uint32_t {
    RPI_STATE_POWER_OFF,
    RPI_STATE_POWER_WAITING,
    RPI_STATE_DATA_GOOD,
    RPI_STATE_DATA_ERROR,
    RPI_STATE_LOST_CONNECTION,
} rpi_state_t;

typedef enum : uint32_t {
    RPI_STATUS_IDLE = 0,            //The system is idle
    RPI_STATUS_OK = 1,              //The system heartbeat
    RPI_STATUS_ERROR = 2,           //The system has encountered an error
    RPI_STATUS_PHOTO_SUCCESS = 3,   //The system has taken a photo
    RPI_STATUS_PHOTO_ERROR = 4,     //The system has encountered an error while taking a photo
    RPI_STATUS_RTL_SUCCESS = 5,    //The system has recorded data from RTL-SDR
    RPI_STATUS_RTL_ERROR = 6,      //The system has encountered an error while recording data from RTL-SDR
    RPI_STATUS_RTL_RESET = 7,      //The system has reset the RTL-SDR
} rpi_status_t;

typedef struct __attribute__((packed)) STRUCT {
  rpi_status_t status;
} piStruct;

typedef struct {
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  rpi_status_t status;
  char message[128];
} rpiMessage;


//Global Variables
extern rpi_state_t rpiState;
extern rpiMessage rxMessage;
extern uint32_t t_lastMsg;

//Function Prototypes
void enableRPI();
void disableRPI();

//Serial Transfer
void rpiSerialSetup();
void rpiSerialLoop();

#endif // RPI_SERIAL_H