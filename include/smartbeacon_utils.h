/* 
Lógica SmartBeaconing: determina cuándo enviar tramas APRS según velocidad, dirección y movimiento.
ACTUALIZADO: Incluye modo estático para monitoreo de peceras sin GPS.
 */

#ifndef SMARTBEACON_UTILS_H_
#define SMARTBEACON_UTILS_H_

#include <Arduino.h>

struct SmartBeaconValues {
    int     slowRate;
    int     slowSpeed;
    int     fastRate;
    int     fastSpeed;
    int     minTxDist;
    int     minDeltaBeacon;
    int     turnMinDeg;
    int     turnSlope;
};


namespace SMARTBEACON_Utils {

    void checkSettings(byte index);
    void checkInterval(int speed);
    void checkFixedBeaconTime();
    void checkState();
    
    // NUEVAS FUNCIONES PARA MODO ESTÁTICO
    void checkStaticMode();              // Verifica si debe transmitir en modo estático
    bool checkSensorThresholds();        // Verifica umbrales críticos de sensores
    
}

#endif