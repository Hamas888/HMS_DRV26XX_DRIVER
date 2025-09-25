   /*
 ====================================================================================================
 * File:        HMS_DRV26XX_DRIVER.h
 * Author:      Hamas Saeed
 * Version:     Rev_1.0.0
 * Date:        Sep 23 2025
 * Brief:       This Package Provide DRV26XX Haptic Driver Library for Cross Platform (STM/ESP/nRF)
 * 
 ====================================================================================================
 * License: 
 * MIT License
 * 
 * Copyright (c) 2025 Hamas Saeed
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * For any inquiries, contact Hamas Saeed at hamasaeed@gmail.com
 *
 ====================================================================================================
 */

#ifndef HMS_DRV26XX_DRIVER_H
#define HMS_DRV26XX_DRIVER_H

#if defined(ARDUINO)                                                                                       // Platform detection
  #define HMS_DRV26XX_PLATFORM_ARDUINO
#elif defined(ESP_PLATFORM)
  #define HMS_DRV26XX_PLATFORM_ESP_IDF
#elif defined(__ZEPHYR__)
  #define HMS_DRV26XX_PLATFORM_ZEPHYR
#elif defined(STM32F0) || defined(STM32F1) || defined(STM32F3) || defined(STM32F4) || \
      defined(STM32F7) || defined(STM32G0) || defined(STM32G4) || defined(STM32H7) || \
      defined(STM32L0) || defined(STM32L1) || defined(STM32L4) || defined(STM32L5) || \
      defined(STM32WB) || defined(STM32WL)
  #define HMS_DRV26XX_PLATFORM_STM32_HAL
#endif

#if defined(HMS_DRV26XX_PLATFORM_ARDUINO)
  #include <Wire.h>
  #include <Arduino.h>
#elif defined(HMS_DRV26XX_PLATFORM_ESP_IDF)
#elif defined(HMS_DRV26XX_PLATFORM_ZEPHYR)
#elif defined(HMS_DRV26XX_PLATFORM_STM32_HAL)
#endif

#endif // HMS_DRV26XX_DRIVER_H

#include "HMS_DRV26XX_Config.h"

typedef enum {
    HMS_DRV26XX_OK       = 0x00,
    HMS_DRV26XX_ERROR    = 0x01,
    HMS_DRV26XX_BUSY     = 0x02,
    HMS_DRV26XX_TIMEOUT  = 0x03,
    HMS_DRV26XX_NOT_FOUND= 0x04
} HMS_DRV26XX_StatusTypeDef;


class HMS_DRV26XX {
public:
    HMS_DRV26XX();
    ~HMS_DRV26XX();

    #if defined(HMS_DRV26XX_PLATFORM_ARDUINO)
    HMS_DRV26XX_StatusTypeDef begin(TwoWire *theWire = &Wire);
    #elif defined(HMS_DRV26XX_PLATFORM_ESP_IDF)
    HMS_DRV26XX_StatusTypeDef begin(i2c_port_t i2c_port = I2C_NUM_0);
    #elif defined(HMS_DRV26XX_PLATFORM_ZEPHYR)
    HMS_DRV26XX_StatusTypeDef begin(struct device *i2c_dev);
    #elif defined(HMS_DRV26XX_PLATFORM_STM32_HAL)
    HMS_DRV26XX_StatusTypeDef begin(I2C_HandleTypeDef *hi2c);
    #endif
    
    void stop();
    void start();
    void useERM();
    void useLRA();
    void setMode(uint8_t mode);
    void setRealtimeValue(uint8_t rtp);
    void selectLibrary(uint8_t library);
    void setWaveform(uint8_t slot, uint8_t waveform);

    bool isERMDriver() const            { return isERM;                   }
    bool isLRADriver() const            { return isLRA;                   }
    const char* getDeviceName() const   { return HMS_DRV26XX_DEVICE_NAME; }
    uint8_t getDeviceAddress() const    { return HMS_DRV26XX_DEVICE_ADDR; }

private:
  bool isERM        = true;
  bool isLRA        = false;
  bool initialized  = false;
  #if defined(HMS_DRV26XX_PLATFORM_ARDUINO)
    TwoWire *drv6xx_wire = NULL;
  #elif defined(HMS_DRV26XX_PLATFORM_ESP_IDF)
    i2c_port_t drv6xx_i2c_port;
  #elif defined(HMS_DRV26XX_PLATFORM_ZEPHYR)
    struct device *drv6xx_i2c_dev;
  #elif defined(HMS_DRV26XX_PLATFORM_STM32_HAL)
    I2C_HandleTypeDef *drv6xx_hi2c;
  #endif

  uint8_t readRegister(uint8_t reg);
  void writeRegister(uint8_t reg, uint8_t val);

};