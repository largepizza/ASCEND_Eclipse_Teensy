#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "pinout.h"

#define ADC_RESOLUTION 1023.0F

//Voltage Measurement Class
class Voltage {
    public:
        Voltage(uint8_t pin, float R1, float R2) {
            _pin = pin;
            _R1 = R1;
            _R2 = R2;
            pinMode(_pin, INPUT);
        }
        uint32_t readADC() {
            ADCValue = analogRead(_pin);
            return ADCValue;
        }
        float readVoltage() {
            voltage = ((float)readADC() * 3.3) / ADC_RESOLUTION * (_R1 + _R2) / _R2;
            return voltage;
        }
        float read() {
            return readVoltage();
        }
        float getVoltage() {
            return voltage;
        }
    private:
        uint32_t ADCValue;
        float voltage;
        uint8_t _pin;
        float _R1;
        float _R2;
};


//Thermistor Measurement Class
class Thermistor {
    public:
        Thermistor(uint8_t pin, float R1, float R0, float T0, float Beta) {
            _pin = pin;
            _R1 = R1; //Pullup resistor, usually 10k
            _R0 = R0; //Resistance at T0
            _T0 = T0; //Temperature at R0
            _Beta = Beta; //Beta value
            pinMode(_pin, INPUT);
        }
        uint32_t readADC() {
            ADCValue = analogRead(_pin);
            return ADCValue;
        }
        float readVoltage() {
            readADC();
            voltage = ((float)ADCValue * 3.3) / ADC_RESOLUTION;
            return voltage;
        }
        float readResistance() {
            readVoltage();
            //Assuming a voltage divider configuration with a pullup resistor R1
            resistance = _R1 / (3.3 / voltage - 1.0);
            return resistance;
        }
        float readTempKelvin() {
            readResistance();
            float T0_K = _T0 + 273.15;
            tempKelvin = 1.0 / (1.0 / T0_K + 1.0 / _Beta * log(resistance / _R0));
            return tempKelvin;
        }
        float readTempCelcius() {
            readTempKelvin();
            tempCelcius = tempKelvin - 273.15;
            return tempCelcius;
        }
        float read() {
            return readTempCelcius();
        }
        float getTempCelcius() {
            return tempCelcius;
        }
    private:
        uint32_t ADCValue;
        float resistance;
        float voltage;
        float tempKelvin;
        float tempCelcius;
        uint8_t _pin;
        float _R0;
        float _R1;
        float _T0;
        float _Beta;
};


// Current Measurement Class
class Current {
    public:
        Current(uint8_t pin, float Rsense, float gain) {
            _pin = pin;
            _Rsense = Rsense;
            _gain = gain;
            pinMode(_pin, INPUT);
        }
        uint32_t readADC() {
            ADCValue = analogRead(_pin);
            return ADCValue;
        }
        float readVoltage() {
            readADC();
            voltage = ((float)ADCValue * 3.3) / ADC_RESOLUTION;
            return voltage;
        }
        float readCurrent() {
            readVoltage();
            current = ((voltage ) / _gain) / _Rsense;
            return current;
        }
        float read() {
            return readCurrent();
        }
        float getCurrent() {
            return current;
        }
    private:
        uint32_t ADCValue;
        float voltage;
        float current;
        uint8_t _pin;
        float _Rsense;
        float _gain;
};


#endif // SENSORS_H