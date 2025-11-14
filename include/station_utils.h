/* 
Administración de los datos de la estación APRS: callsign, símbolo, estado, telemetría básica.
 */

#ifndef STATION_UTILS_H_
#define STATION_UTILS_H_

#include <Arduino.h>

namespace STATION_Utils {

    void    nearStationInit();
    String  getNearStation(uint8_t position);

    void    deleteListenedStationsByTime();
    void    checkListenedStationsByTimeAndDelete();
    void    orderListenedStationsByDistance(const String& callsign, float distance, float course);
    
    void    checkStandingUpdateTime();
    void    sendBeacon();
    void    saveIndex(uint8_t type, uint8_t index);
    void    loadIndex(uint8_t type);

}

#endif
