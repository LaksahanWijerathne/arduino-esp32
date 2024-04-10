#include "ESP32_LyraTD_MSC.h"

ESP32_LyraTD_MSC::ESP32_LyraTD_MSC() : _ledDriver(18, 23) {
    // Initialize the LED driver with the SDA and SCL pin numbers
}

void ESP32_LyraTD_MSC::init() {
    _ledDriver.init();
}

void ESP32_LyraTD_MSC::setLed(int channel, bool state) {
    _ledDriver.setLed(channel, state);
}

void ESP32_LyraTD_MSC::setOutputCurrent(int channel, int current) {
    _ledDriver.setOutputCurrent(channel, current);
}

void ESP32_LyraTD_MSC::setAudioGain(int gain) {
    _ledDriver.setAudioGain(gain);
}

void ESP32_LyraTD_MSC::setChipCascadeMode(bool mode) {
    _ledDriver.setChipCascadeMode(mode);
}

void ESP32_LyraTD_MSC::setAudioModulatedEnable(bool enable) {
    _ledDriver.setAudioModulatedEnable(enable);
}

void ESP32_LyraTD_MSC::setFrameDelayTime(int time) {
    _ledDriver.setFrameDelayTime(time);
}

void ESP32_LyraTD_MSC::setFrameStart(int frame) {
    _ledDriver.setFrameStart(frame);
}

void ESP32_LyraTD_MSC::setAllLeds(bool state) {
    _ledDriver.setAllLeds(state);
}
