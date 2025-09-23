#include "HMS_DRV26XX_DRIVER.h"



HMS_DRV26XX::HMS_DRV26XX() {
    // Constructor implementation
}

HMS_DRV26XX::~HMS_DRV26XX() {
    // Destructor implementation
}

#if defined(HMS_DRV26XX_PLATFORM_ARDUINO)
HMS_DRV26XX_StatusTypeDef HMS_DRV26XX::begin(TwoWire *wire) {
    drv6xx_wire = wire;
    drv6xx_wire->begin();
    drv6xx_wire->beginTransmission(HMS_DRV26XX_DEVICE_ADDR);
    if (drv6xx_wire->endTransmission() != 0) {
        return HMS_DRV26XX_NOT_FOUND; // Device not found
    }

    writeRegister(HMS_DRV26XX_REG_MODE, 0x00); // out of standby

    writeRegister(HMS_DRV26XX_REG_RTPIN, 0x00); // no real-time-playback

    writeRegister(HMS_DRV26XX_REG_WAVESEQ1, 1); // strong click
    writeRegister(HMS_DRV26XX_REG_WAVESEQ2, 0); // end sequence

    writeRegister(HMS_DRV26XX_REG_OVERDRIVE, 0); // no overdrive

    writeRegister(HMS_DRV26XX_REG_SUSTAINPOS, 0);
    writeRegister(HMS_DRV26XX_REG_SUSTAINNEG, 0);
    writeRegister(HMS_DRV26XX_REG_BREAK, 0);
    writeRegister(HMS_DRV26XX_REG_AUDIOMAX, 0x64);

    // ERM open loop

    // turn off N_ERM_LRA
    writeRegister(HMS_DRV26XX_REG_FEEDBACK, readRegister(HMS_DRV26XX_REG_FEEDBACK) & 0x7F);
    // turn on ERM_OPEN_LOOP
    writeRegister(HMS_DRV26XX_REG_CONTROL3, readRegister(HMS_DRV26XX_REG_CONTROL3) | 0x20);
    return HMS_DRV26XX_OK;
}

uint8_t HMS_DRV26XX::readRegister(uint8_t registerAddr) {
    drv6xx_wire->beginTransmission(HMS_DRV26XX_DEVICE_ADDR);
    drv6xx_wire->write(registerAddr);
    drv6xx_wire->endTransmission(false); // Send repeated start
    drv6xx_wire->requestFrom(HMS_DRV26XX_DEVICE_ADDR, 1);
    if (drv6xx_wire->available()) {
        return drv6xx_wire->read();
    }
    return 0; // Return 0 if no data available
}

void HMS_DRV26XX::writeRegister(uint8_t registerAddr, uint8_t value) {
    uint8_t buffer[2] = {registerAddr, value};
    drv6xx_wire->beginTransmission(HMS_DRV26XX_DEVICE_ADDR);
    drv6xx_wire->write(buffer, sizeof(buffer));
    drv6xx_wire->endTransmission();
}   

#elif defined(HMS_DRV26XX_PLATFORM_ESP_IDF)
HMS_DRV26XX_StatusTypeDef HMS_DRV26XX::begin(i2c_port_t i2c_port) {
    // ESP-IDF-specific initialization code here
    return HMS_DRV26XX_OK;
}
#elif defined(HMS_DRV26XX_PLATFORM_ZEPHYR)
HMS_DRV26XX_StatusTypeDef HMS_DRV26XX::begin(struct device *i2c_dev) {
    // Zephyr-specific initialization code here
    return HMS_DRV26XX_OK;
}
#elif defined(HMS_DRV26XX_PLATFORM_STM32_HAL)
HMS_DRV26XX_StatusTypeDef HMS_DRV26XX::begin(I2C_HandleTypeDef *hi2c) {
    // STM32 HAL-specific initialization code here
    return HMS_DRV26XX_OK;
}
#endif

void HMS_DRV26XX::stop() {
    writeRegister(HMS_DRV26XX_REG_GO, 0);
}

void HMS_DRV26XX::start() {
    writeRegister(HMS_DRV26XX_REG_GO, 1);
}

void HMS_DRV26XX::useERM() {
  writeRegister(HMS_DRV26XX_REG_FEEDBACK, readRegister(HMS_DRV26XX_REG_FEEDBACK) & 0x7F);
}

void HMS_DRV26XX::useLRA() {
  writeRegister(HMS_DRV26XX_REG_FEEDBACK, readRegister(HMS_DRV26XX_REG_FEEDBACK) | 0x80);
}

void HMS_DRV26XX::setMode(uint8_t mode) {
  writeRegister(HMS_DRV26XX_REG_MODE, mode);
}

void HMS_DRV26XX::setRealtimeValue(uint8_t rtp) {
  writeRegister(HMS_DRV26XX_REG_RTPIN, rtp);
}

void HMS_DRV26XX::selectLibrary(uint8_t library) {
    writeRegister(HMS_DRV26XX_REG_LIBRARY, library);
}

void HMS_DRV26XX::setWaveform(uint8_t slot, uint8_t waveform) {
  writeRegister(HMS_DRV26XX_REG_WAVESEQ1 + slot, waveform);
}
