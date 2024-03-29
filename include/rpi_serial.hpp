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
    RPI_STATE_SHUTDOWN
} rpi_state_t;


//Raspberry Pi Python script status
typedef enum : uint32_t {
    SYS_STATE_IDLE = 0,            //The system is idle
    SYS_STATE_OK = 1,              //The system heartbeat
    SYS_STATE_ERROR = 2,           //The system has encountered an error
    SYS_STATE_SHUTDOWN = 3        //The system is shutting down
} SystemState_t;

//Raspberry Pi camera status
typedef enum : uint32_t {
  PHOTO_OFF = 0,                  //The camera is off
  PHOTO_SUCCESS = 1,              //The camera has taken a photo successfully
  PHOTO_ERROR = 2,                //The camera has encountered an error
} CameraState_t;

//Raspberry Pi RTL status
typedef enum : uint32_t {
  RTL_INACTIVE = 0,               //The RTL is inactive
  RTL_ACTIVE = 1,                 //The RTL is active
  RTL_FAIL = 2,                   //The RTL has failed
} RTLState_t;

//Commands
typedef enum : uint8_t {
  CMD_ACK = 0,                   //The system is idle
  CMD_SHUTDOWN = 1,              //Shutdown the system
} Command_t;




//Structure for the Raspberry Pi to send data to the Teensy
typedef struct __attribute__((packed)) STRUCT {
  SystemState_t status;
  CameraState_t camera;
  RTLState_t rtl;
  int hour;
  int minute;
  int second;
} piStruct;

//Struct for the Teensy to send commands to the Raspberry Pi
typedef struct __attribute__((packed)) COMMAND {
  Command_t command;
} piCommand;



//Global Variables
extern rpi_state_t rpiState;
extern piStruct rxMessage;
extern uint32_t t_lastMsg;

//Function Prototypes
void enableRPI();
void disableRPI();

//Serial Transfer
void rpiSerialSetup();
void rpiSerialLoop();
void rpiSerialSend(Command_t txCommand);

#endif // RPI_SERIAL_H