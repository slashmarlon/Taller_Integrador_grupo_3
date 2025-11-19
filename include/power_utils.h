/* 
Control del consumo energético: modos de bajo consumo, apagado de periféricos, gestión de energía.
LoRa, GPS y frecuencia de CPU.
 */

#ifndef POWER_UTILS_H_
#define POWER_UTILS_H_

#include <Arduino.h>
#include "board_pinout.h"
#if defined(HAS_AXP2101) || defined(HAS_AXP192)
    #include "XPowersLib.h"
#else
    #include <Wire.h>
#endif

namespace POWER_Utils {

    #ifdef ADC_CTRL
        void    adc_ctrl_ON();
        void    adc_ctrl_OFF();
    #endif

    #if defined(HAS_AXP192) || defined(HAS_AXP2101)
        String  getBatteryInfoCurrent();
        float   getBatteryChargeDischargeCurrent();
        void    handleChargingLed();
    #endif

    bool isCharging();    

    void activateGPS();
    void deactivateGPS();

    void activateLoRa();
    void deactivateLoRa();

    void externalPinSetup();

    bool begin(TwoWire &port);
    void setup();

    void lowerCpuFrequency();
    void shutdown();
  
}

#endif
