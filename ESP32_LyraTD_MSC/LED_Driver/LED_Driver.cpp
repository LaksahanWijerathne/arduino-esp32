#include "LED_Driver.h"

LED_Driver::LED_Driver(int sda, int scl) : _sda(sda), _scl(scl) {
    _address = 0x30; // Default slave address for IS31FL3216
    Wire.begin(_sda, _scl);
}

void LED_Driver::init() {
    // Default settings
    writeRegister(0x00, 0x80); // Configuration Register
    writeRegister(0x01, 0xFF); // LED Control Register (OUT9~OUT16)
    writeRegister(0x02, 0xFF); // LED Control Register (OUT1~OUT8)
    writeRegister(0x03, 0x00); // Lighting Effect Register
}

void LED_Driver::setLed(int channel, bool state) {
    if (channel >= 1 && channel <= 16) {
        uint8_t reg = channel % 8 == 0 ? 0x01 : 0x02;
        uint8_t mask = 1 << (channel % 8 - 1);
        uint8_t value = readRegister(reg) & ~mask;
        if (state) {
            value |= mask;
        }
        writeRegister(reg, value);
    }
}

void LED_Driver::setOutputCurrent(int channel, int current) {
    if (channel >= 1 && channel <= 16) {
        uint8_t reg = 0x03;
        uint8_t mask = 0x07 << (channel * 3 - 3);
        uint8_t shift = channel * 3 - 3;
        uint8_t value = (readRegister(reg) & ~mask) | ((current & 0x07) << shift);
        writeRegister(reg, value);
    }
}

void LED_Driver::setAudioGain(int gain) {
    if (gain >= 0 && gain <= 7) {
        uint8_t reg = 0x03;
        uint8_t mask = 0x07 << 3;
        uint8_t shift = 3;
        uint8_t value = (readRegister(reg) & ~mask) | ((gain & 0x07) << shift);
        writeRegister(reg, value);
    }
}

void LED_Driver::setChipCascadeMode(bool mode) {
    uint8_t reg = 0x03;
    uint8_t mask = 0x80;
    uint8_t value = mode ? (readRegister(reg) | mask) : (readRegister(reg) & ~mask);
    writeRegister(reg, value);
}

void LED_Driver::setAudioModulatedEnable(bool enable) {
    uint8_t reg = 0x00;
    uint8_t mask = 0x04;
    uint8_t value = enable ? (readRegister(reg) | mask) : (readRegister(reg) & ~mask);
    writeRegister(reg, value);
}

void LED_Driver::setFrameDelayTime(int time) {
    if (time >= 0 && time <= 7) {
        uint8_t reg = 0xB6;
        uint8_t mask = 0xE0;
        uint8_t shift = 5;
        uint8_t value = (time & 0x07) << shift;
        writeRegister(reg, value);
    }
}

void LED_Driver::setFrameStart(int frame) {
    if (frame >= 1 && frame <= 8) {
        uint8_t reg = 0xB7;
        uint8_t mask = 0x07;
        uint8_t value = frame - 1;
        writeRegister(reg, value);
    }
}

void LED_Driver::setFrameDelayRegister() {
    writeRegister(0xB6, readRegister(0xB6) | 0x1F);
}

void LED_Driver::setFrameStartRegister() {
    writeRegister(0xB7, readRegister(0xB7) | 0x1F);
}

void LED_Driver::updateRegisters() {
    writeRegister(0xB0, 0x00);
}

void LED_Driver::setAllLeds(bool state) {
    for (int i = 1; i <= 16; i++) {
        setLed(i, state);
    }
}

void LED_Driver::writeRegister(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

uint8_t LED_Driver::readRegister(uint8_t reg) {
    Wire.beginTransmission(_address);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(_address, (uint8_t)1);
    return Wire.read();
}
