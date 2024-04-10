#ifndef ESP32_LYRATD_MSC_H
#define ESP32_LYRATD_MSC_H

#include "LED_Driver.h"

class ESP32_LyraTD_MSC {
public:
    ESP32_LyraTD_MSC();
    void init();
    void setLed(int channel, bool state);
    void setOutputCurrent(int channel, int current);
    void setAudioGain(int gain);
    void setChipCascadeMode(bool mode);
    void setAudioModulatedEnable(bool enable);
    void setFrameDelayTime(int time);
    void setFrameStart(int frame);
    void setAllLeds(bool state);

private:
    LED_Driver _ledDriver;
};

#endif
