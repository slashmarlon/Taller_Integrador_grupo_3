/*
 */

#ifndef BATTERY_UTILS_H_
#define BATTERY_UTILS_H_

#include <Arduino.h>


namespace BATTERY_Utils {

    String  getPercentVoltageBattery(float voltage);
    String  getBatteryInfoVoltage();
    float   readBatteryVoltage();
    void    monitor();
    
}

#endif
