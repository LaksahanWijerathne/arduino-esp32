#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "Arduino.h"
#include "Wire.h"

class LED_Driver {
public:
    LED_Driver(int sda, int scl);
    void init();
    void setLed(int channel, bool state);
    void setOutputCurrent(int channel, int current);
    void setAudioGain(int gain);
    void setChipCascadeMode(bool mode);
    void setAudioModulatedEnable(bool enable);
    void setFrameDelayTime(int time);
    void setFrameStart(int frame);
    void setFrameDelayRegister();
    void setFrameStartRegister();
    void updateRegisters();
    void setAllLeds(bool state);

private:
    int _sda;
    int _scl;
    uint8_t _address;
    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);
};

#endif
