   /*
 ====================================================================================================
 * File:        HMS_DRV26XX_Config.h
 * Author:      Hamas Saeed
 * Version:     Rev_1.0.0
 * Date:        Sep 23 2025
 * Brief:       This Package Provide DRV26XX Haptic Driver Selection
 * Note:        For Now Only DRV2605 Supported
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

#ifndef HMS_DRV26XX_CONFIG_H
#define HMS_DRV26XX_CONFIG_H

#define HMS_DRV26XX_DRV2605                                     // Define the DRV26XX device to be used
// #define HMS_DRV26XX_DRV2625                                     // Define the DRV26XX device to be used





#if defined(HMS_DRV26XX_DRV2605)
    #define HMS_DRV26XX_DEVICE_NAME             "DRV2605"
    #define HMS_DRV26XX_DEVICE_ADDR             0x5A            // Device I2C address

    #define HMS_DRV26XX_REG_MODE                0x01            // Mode register
    #define HMS_DRV26XX_REG_STATUS              0x00            // Status register
    
    #define HMS_DRV26XX_MODE_DIAGNOS            0x06            // Diagnostics mode
    #define HMS_DRV26XX_MODE_AUTOCAL            0x07            // Auto calibration mode
    #define HMS_DRV26XX_MODE_INTTRIG            0x00            // Internal trigger mode
    #define HMS_DRV26XX_MODE_REALTIME           0x05            // Real-time playback (RTP) mode
    #define HMS_DRV26XX_MODE_PWMANALOG          0x03            // PWM/Analog input mode
    #define HMS_DRV26XX_MODE_AUDIOVIBE          0x04            // Audio-to-vibe mode
    #define HMS_DRV26XX_MODE_EXTTRIGLVL         0x02            // External level trigger mode
    #define HMS_DRV26XX_MODE_EXTTRIGEDGE        0x01            // External edge trigger mode


    #define HMS_DRV26XX_REG_RTPIN               0x02            // Real-time playback input register
    #define HMS_DRV26XX_REG_LIBRARY             0x03            // Waveform library selection register
    #define HMS_DRV26XX_REG_WAVESEQ1            0x04            // Waveform sequence register 1
    #define HMS_DRV26XX_REG_WAVESEQ2            0x05            // Waveform sequence register 2
    #define HMS_DRV26XX_REG_WAVESEQ3            0x06            // Waveform sequence register 3
    #define HMS_DRV26XX_REG_WAVESEQ4            0x07            // Waveform sequence register 4
    #define HMS_DRV26XX_REG_WAVESEQ5            0x08            // Waveform sequence register 5
    #define HMS_DRV26XX_REG_WAVESEQ6            0x09            // Waveform sequence register 6
    #define HMS_DRV26XX_REG_WAVESEQ7            0x0A            // Waveform sequence register 7
    #define HMS_DRV26XX_REG_WAVESEQ8            0x0B            // Waveform sequence register 8

    #define HMS_DRV26XX_REG_GO                  0x0C            // Go register
    #define HMS_DRV26XX_REG_VBAT                0x21            // Vbat voltage-monitor register
    #define HMS_DRV26XX_REG_BREAK               0x10            // Brake time offset register
    #define HMS_DRV26XX_REG_RATEDV              0x16            // Rated voltage register
    #define HMS_DRV26XX_REG_CLAMPV              0x17            // Overdrive clamp voltage register     
    #define HMS_DRV26XX_REG_AUDIOLVL            0x12            // Audio-to-vibe minimum input level register
    #define HMS_DRV26XX_REG_AUDIOMAX            0x13            // Audio-to-vibe maximum input level register
    #define HMS_DRV26XX_REG_FEEDBACK            0x1A            // Feedback control register
    #define HMS_DRV26XX_REG_CONTROL1            0x1B            // Control1 Register
    #define HMS_DRV26XX_REG_CONTROL2            0x1C            // Control2 Register
    #define HMS_DRV26XX_REG_CONTROL3            0x1D            // Control3 Register
    #define HMS_DRV26XX_REG_CONTROL4            0x1E            // Control4 Register
    #define HMS_DRV26XX_REG_LRARESON            0x22            // LRA resonance-period register
    #define HMS_DRV26XX_REG_AUDIOCTRL           0x11            // Audio-to-vibe control register
    #define HMS_DRV26XX_REG_OVERDRIVE           0x0D            // Overdrive time offset register
    #define HMS_DRV26XX_REG_SUSTAINPOS          0x0E            // Sustain time offset, positive register
    #define HMS_DRV26XX_REG_SUSTAINNEG          0x0F            // Sustain time offset, negative register
    #define HMS_DRV26XX_REG_AUTOCALEMP          0x19            // Auto-calibration back-EMF result register
    #define HMS_DRV26XX_REG_AUDIOOUTMIN         0x14            // Audio-to-vibe minimum output drive register
    #define HMS_DRV26XX_REG_AUDIOOUTMAX         0x15            // Audio-to-vibe maximum output drive register
    #define HMS_DRV26XX_REG_AUTOCALCOMP         0x18            // Auto-calibration compensation result register
#else if defined(HMS_DRV26XX_DRV2625)
    #error "DRV2625 is not supported yet, please use DRV2605"
#endif 

#endif // HMS_DRV26XX_CONFIG_H