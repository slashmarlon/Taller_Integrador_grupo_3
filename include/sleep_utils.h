/* 
Funciones para poner el sistema en modo sleep/deepsleep y retomarlo.
ACTUALIZADO: Incluye DeepSleep completo del ESP32 con control de sensores.
 */

#ifndef SLEEP_UTILS_H_
#define SLEEP_UTILS_H_

#include <Arduino.h>

namespace SLEEP_Utils {

    // Funciones originales para GPS
    void gpsSleep();
    void gpsWakeUp();
    void checkIfGPSShouldSleep();
    
    // NUEVAS FUNCIONES PARA DEEPSLEEP DEL ESP32
    void enterDeepSleep(uint64_t sleepTimeSeconds);     // Pone el ESP32 en deep sleep
    void prepareForDeepSleep();                         // Preparación antes de dormir
    void checkAndEnterDeepSleep();                      // Verifica si debe entrar en deep sleep

}

#endif