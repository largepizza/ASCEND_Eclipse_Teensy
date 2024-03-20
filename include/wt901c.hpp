#ifndef WT901C_HPP
#define WT901_HPP

#include <REG.h>
#include <wit_c_sdk.h>
#include <Arduino.h>


#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80

static void CmdProcess(void);
static void AutoScanSensor(void);
static void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
static void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
static void Delayms(uint16_t ucMs);


class WT901C {
    public:
        void init();
        void getDataBasic();


        
        float fAcc[3];
        float fGyro[3];
        float fAngle[3];
        float fMag[3];


    private:
        int i;


};




#endif