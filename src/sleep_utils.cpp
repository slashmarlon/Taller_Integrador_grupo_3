#include "board_pinout.h"
#include "sleep_utils.h"
#include "power_utils.h"
#include "configuration.h"
#include "sensor_utils.h"
#include <esp_sleep.h>

extern Configuration    Config;
extern Beacon           *currentBeacon;
extern uint32_t         lastGPSTime;
extern bool             gpsIsActive;

bool gpsShouldSleep     = false;


namespace SLEEP_Utils {

    void gpsSleep() {
        #ifdef HAS_GPS_CTRL
            if (gpsIsActive) {
                POWER_Utils::deactivateGPS();
                lastGPSTime = millis();
                Serial.println("GPS SLEEPING");
            }
        #endif
    }

    void gpsWakeUp() {
        #ifdef HAS_GPS_CTRL
            if (!gpsIsActive) {
                POWER_Utils::activateGPS();
                gpsShouldSleep = false;
                Serial.println("GPS WAKEUP");
            }
        #endif
    }

    void checkIfGPSShouldSleep() {
        if (gpsShouldSleep) {
            gpsSleep();
        }
    }
    
    void prepareForDeepSleep() {
        Serial.println("[SLEEP] Preparando para DeepSleep...");
        
        SENSORS_Utils::powerOffSensors();
        Serial.println("[SLEEP] Sensores apagados");
        
        #ifdef HAS_GPS_CTRL
            POWER_Utils::deactivateGPS();
            Serial.println("[SLEEP] GPS apagado");
        #endif
        
        Serial.flush();
        delay(100);
    }
    
    void enterDeepSleep(uint64_t sleepTimeSeconds) {
        Serial.print("[SLEEP] Entrando en DeepSleep por ");
        Serial.print(sleepTimeSeconds);
        Serial.println(" segundos");
        Serial.flush();
        
        esp_sleep_enable_timer_wakeup(sleepTimeSeconds * 1000000ULL);
        
        esp_deep_sleep_start();
    }
    
    void checkAndEnterDeepSleep() {
        if (!Config.deepSleep.enabled) {
            Serial.println("[SLEEP] DeepSleep desactivado en configuracion");
            return;
        }
        
        if (!currentBeacon->staticMode) {
            Serial.println("[SLEEP] DeepSleep solo disponible en modo estatico");
            return;
        }
        
        Serial.println("[SLEEP] Verificando condiciones para DeepSleep");
        
        prepareForDeepSleep();
        
        uint64_t sleepTimeSeconds = Config.deepSleep.sleepTimeMinutes * 60;
        
        enterDeepSleep(sleepTimeSeconds);
    }

}