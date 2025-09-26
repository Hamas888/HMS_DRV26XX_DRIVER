#include "HMS_DRV26XX_DRIVER.h"

#if defined(HMS_DRV26XX_LOGGER_ENABLED)
    #include "ChronoLog.h"
  ChronoLogger drvLogger("HMS_DRV26XX", CHRONOLOG_LEVEL_DEBUG);
#endif

HMS_DRV26XX::HMS_DRV26XX() {
    // Constructor implementation
}

HMS_DRV26XX::~HMS_DRV26XX() {
    // Destructor implementation
}

#if defined(HMS_DRV26XX_PLATFORM_ARDUINO)
HMS_DRV26XX_StatusTypeDef HMS_DRV26XX::begin(TwoWire *wire, uint8_t address) {
    drv6xx_wire = wire;
    deviceAddress = address;
    drv6xx_wire->begin();
    drv6xx_wire->beginTransmission(deviceAddress);
    if (drv6xx_wire->endTransmission() != 0) {
        #ifdef HMS_DRV26XX_LOGGER_ENABLED
            drvLogger.error("Device not found at address 0x%02X", deviceAddress);
        #endif
        return HMS_DRV26XX_NOT_FOUND;                                                       // Device not found
    }

    init();
    #ifdef HMS_DRV26XX_LOGGER_ENABLED
        drvLogger.debug("Device initialized at address 0x%02X", deviceAddress);
    #endif
    return HMS_DRV26XX_OK;
}

uint8_t HMS_DRV26XX::readRegister(uint8_t registerAddr) {
    drv6xx_wire->beginTransmission(deviceAddress);
    drv6xx_wire->write(registerAddr);
    drv6xx_wire->endTransmission(false);                                                    // Send repeated start
    drv6xx_wire->requestFrom(deviceAddress, 1);
    if (drv6xx_wire->available()) {
        return drv6xx_wire->read();
    }
    return 0;                                                                               // Return 0 if no data available
}

void HMS_DRV26XX::writeRegister(uint8_t registerAddr, uint8_t value) {
    uint8_t buffer[2] = {registerAddr, value};
    drv6xx_wire->beginTransmission(deviceAddress);
    drv6xx_wire->write(buffer, sizeof(buffer));
    drv6xx_wire->endTransmission();
}   

#elif defined(HMS_DRV26XX_PLATFORM_ZEPHYR)
HMS_DRV26XX_StatusTypeDef HMS_DRV26XX::begin(const struct device *i2c_dev, uint8_t address) {
    if (i2c_dev == NULL) {
        #ifdef HMS_DRV26XX_LOGGER_ENABLED
            drvLogger.error("I2C device is NULL");
        #endif
        return HMS_DRV26XX_ERROR;
    }
    
    drv6xx_i2c_dev = (struct device *)i2c_dev;
    deviceAddress = address;

    if (!device_is_ready(drv6xx_i2c_dev)) {
        #ifdef HMS_DRV26XX_LOGGER_ENABLED
            drvLogger.error("Device not found at address 0x%02X", deviceAddress);
        #endif
        return HMS_DRV26XX_ERROR;
    }

    uint8_t dummy = 0;
    struct i2c_msg msg = {
        .buf = &dummy,
        .len = 1,
        .flags = I2C_MSG_WRITE | I2C_MSG_STOP
    };

    int ret = i2c_transfer(i2c_dev, &msg, 1, HMS_DRV26XX_DEVICE_ADDR);

    if (ret != 0) {
        return HMS_DRV26XX_NOT_FOUND;                                                       // Device not found
    }

    init();
    #ifdef HMS_DRV26XX_LOGGER_ENABLED
        drvLogger.debug("Device initialized at address 0x%02X", deviceAddress);
    #endif

    return HMS_DRV26XX_OK;
}

uint8_t HMS_DRV26XX::readRegister(uint8_t registerAddr) {
    uint8_t value = 0;
    int ret = i2c_reg_read_byte(drv6xx_i2c_dev, deviceAddress, registerAddr, &value);
    if (ret != 0) {
        return 0; // Return 0 if read failed
    }
    return value;
}

void HMS_DRV26XX::writeRegister(uint8_t registerAddr, uint8_t value) {
    i2c_reg_write_byte(drv6xx_i2c_dev, deviceAddress, registerAddr, value);
}

#elif defined(HMS_DRV26XX_PLATFORM_ESP_IDF)
HMS_DRV26XX_StatusTypeDef HMS_DRV26XX::begin(i2c_port_t i2c_port, uint8_t address) {
    // ESP-IDF-specific initialization code here
    return HMS_DRV26XX_OK;
}

uint8_t HMS_DRV26XX::readRegister(uint8_t registerAddr) {
    // ESP-IDF implementation - placeholder
    return 0;
}

void HMS_DRV26XX::writeRegister(uint8_t registerAddr, uint8_t value) {
    // ESP-IDF implementation - placeholder
}

#elif defined(HMS_DRV26XX_PLATFORM_STM32_HAL)
HMS_DRV26XX_StatusTypeDef HMS_DRV26XX::begin(I2C_HandleTypeDef *hi2c, uint8_t address) {
    // STM32 HAL-specific initialization code here
    return HMS_DRV26XX_OK;
}

uint8_t HMS_DRV26XX::readRegister(uint8_t registerAddr) {
    // STM32 HAL implementation - placeholder
    return 0;
}

void HMS_DRV26XX::writeRegister(uint8_t registerAddr, uint8_t value) {
    // STM32 HAL implementation - placeholder
}
#endif

void HMS_DRV26XX::init() {
    writeRegister(HMS_DRV26XX_REG_MODE, 0x00);                                              // out of standby

    writeRegister(HMS_DRV26XX_REG_RTPIN, 0x00);                                             // no real-time-playback

    writeRegister(HMS_DRV26XX_REG_WAVESEQ1, 1);                                             // strong click
    writeRegister(HMS_DRV26XX_REG_WAVESEQ2, 0);                                             // end sequence

    writeRegister(HMS_DRV26XX_REG_OVERDRIVE, 0);                                            // no overdrive

    writeRegister(HMS_DRV26XX_REG_SUSTAINPOS, 0);
    writeRegister(HMS_DRV26XX_REG_SUSTAINNEG, 0);
    writeRegister(HMS_DRV26XX_REG_BREAK, 0);
    writeRegister(HMS_DRV26XX_REG_AUDIOMAX, 0x64);

    /* ERM open loop */
    writeRegister(HMS_DRV26XX_REG_FEEDBACK, readRegister(HMS_DRV26XX_REG_FEEDBACK) & 0x7F); // turn off N_ERM_LRA
    writeRegister(HMS_DRV26XX_REG_CONTROL3, readRegister(HMS_DRV26XX_REG_CONTROL3) | 0x20); // turn on ERM_OPEN_LOOP
    
    initialized = true;
    #ifdef HMS_DRV26XX_LOGGER_ENABLED
        drvLogger.debug("Default configuration set");
    #endif
}

void HMS_DRV26XX::stop() {
    writeRegister(HMS_DRV26XX_REG_GO, 0);
    #ifdef HMS_DRV26XX_LOGGER_ENABLED
        drvLogger.debug("Playback stopped");
    #endif
}

void HMS_DRV26XX::start() {
    writeRegister(HMS_DRV26XX_REG_GO, 1);
    #ifdef HMS_DRV26XX_LOGGER_ENABLED
        drvLogger.debug("Playback started");
    #endif
}

void HMS_DRV26XX::useERM() {
    writeRegister(HMS_DRV26XX_REG_FEEDBACK, readRegister(HMS_DRV26XX_REG_FEEDBACK) & 0x7F);
    #ifdef HMS_DRV26XX_LOGGER_ENABLED
        drvLogger.debug("Switched to ERM mode");
    #endif
}

void HMS_DRV26XX::useLRA() {
    writeRegister(HMS_DRV26XX_REG_FEEDBACK, readRegister(HMS_DRV26XX_REG_FEEDBACK) | 0x80);
    #ifdef HMS_DRV26XX_LOGGER_ENABLED
        drvLogger.debug("Switched to LRA mode");
    #endif
}

void HMS_DRV26XX::setMode(uint8_t mode) {
    writeRegister(HMS_DRV26XX_REG_MODE, mode);
    #ifdef HMS_DRV26XX_LOGGER_ENABLED
        drvLogger.debug("Mode set to 0x%02X", mode);
    #endif
}

void HMS_DRV26XX::setRealtimeValue(uint8_t rtp) {
    writeRegister(HMS_DRV26XX_REG_RTPIN, rtp);
    #ifdef HMS_DRV26XX_LOGGER_ENABLED
        drvLogger.debug("Realtime value set to %d", rtp);
    #endif
}

void HMS_DRV26XX::selectLibrary(uint8_t library) {
    writeRegister(HMS_DRV26XX_REG_LIBRARY, library);
    #ifdef HMS_DRV26XX_LOGGER_ENABLED
        drvLogger.debug("Library %d selected", library);
    #endif
}

void HMS_DRV26XX::setWaveform(uint8_t slot, uint8_t waveform) {
    writeRegister(HMS_DRV26XX_REG_WAVESEQ1 + slot, waveform);
    #ifdef HMS_DRV26XX_LOGGER_ENABLED
        drvLogger.debug("Waveform %d set in slot %d", waveform, slot);
    #endif
}