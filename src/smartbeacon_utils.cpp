#include "smartbeacon_utils.h"
#include "configuration.h"
#include "sensor_utils.h"

extern Configuration    Config;
extern Beacon           *currentBeacon;
extern bool             smartBeaconActive;
extern uint32_t         txInterval;
extern uint32_t         lastTxTime;
extern bool             sendUpdate;


SmartBeaconValues   currentSmartBeaconValues;
byte                smartBeaconSettingsIndex    = 10;
bool                wxRequestStatus             = false;
uint32_t            wxRequestTime               = 0;
uint32_t            lastStaticBeaconTime        = 0;


SmartBeaconValues   smartBeaconSettings[3] = {
    {120,  3, 60, 15,  50, 20, 12, 60},
    {120,  5, 60, 40, 100, 12, 12, 60},
    {120, 10, 60, 70, 100, 12, 10, 80}
};


namespace SMARTBEACON_Utils {

    void checkSettings(byte index) {
        if (smartBeaconSettingsIndex != index) {
            currentSmartBeaconValues = smartBeaconSettings[index];
            smartBeaconSettingsIndex = index;
        }
    }

    void checkInterval(int speed) {
        if (smartBeaconActive) {
            if (speed < currentSmartBeaconValues.slowSpeed) {
                txInterval = currentSmartBeaconValues.slowRate * 1000;
            } else if (speed > currentSmartBeaconValues.fastSpeed) {
                txInterval = currentSmartBeaconValues.fastRate * 1000;
            } else {
                txInterval = min(currentSmartBeaconValues.slowRate, currentSmartBeaconValues.fastSpeed * currentSmartBeaconValues.fastRate / speed) * 1000;
            }
        }
    }

    void checkFixedBeaconTime() {
        if (!smartBeaconActive) {
            uint32_t lastTxSmartBeacon = millis() - lastTxTime;
            if (lastTxSmartBeacon >= Config.nonSmartBeaconRate * 60 * 1000) sendUpdate = true;
        }
    }

    void checkState() {
        if (wxRequestStatus && (millis() - wxRequestTime) > 20000) wxRequestStatus = false;
        smartBeaconActive = (!wxRequestStatus) ? currentBeacon->smartBeaconActive : false;
    }
    
    void checkStaticMode() {
        if (!currentBeacon->staticMode) return;
        
        uint32_t elapsedTime = millis() - lastStaticBeaconTime;
        uint32_t intervalMillis = currentBeacon->staticBeaconInterval * 60 * 1000;
        
        if (lastStaticBeaconTime == 0) {
            Serial.println("[STATIC] Primera transmision");
            sendUpdate = true;
            lastStaticBeaconTime = millis();
            return;
        }
        
        if (checkSensorThresholds()) {
            Serial.println("[STATIC] Umbral critico detectado - TX inmediata");
            sendUpdate = true;
            lastStaticBeaconTime = millis();
            return;
        }
        
        if (elapsedTime >= intervalMillis) {
            Serial.print("[STATIC] Intervalo cumplido (");
            Serial.print(currentBeacon->staticBeaconInterval);
            Serial.println(" min) - Transmitiendo");
            sendUpdate = true;
            lastStaticBeaconTime = millis();
        }
    }
    
    bool checkSensorThresholds() {
        if (!currentBeacon->staticMode) return false;
        
        float currentTemp = SENSORS_Utils::getTemperatureValue();
        float currentLevel = SENSORS_Utils::getWaterLevelValue();
        
        if (currentTemp > Config.deepSleep.tempThresholdHigh) {
            Serial.print("[ALERTA] Temperatura alta: ");
            Serial.print(currentTemp);
            Serial.print("C (umbral: ");
            Serial.print(Config.deepSleep.tempThresholdHigh);
            Serial.println("C)");
            return true;
        }
        
        if (currentTemp < Config.deepSleep.tempThresholdLow) {
            Serial.print("[ALERTA] Temperatura baja: ");
            Serial.print(currentTemp);
            Serial.print("C (umbral: ");
            Serial.print(Config.deepSleep.tempThresholdLow);
            Serial.println("C)");
            return true;
        }
        
        if (currentLevel < Config.deepSleep.waterLevelThreshold) {
            Serial.print("[ALERTA] Nivel de agua bajo: ");
            Serial.print(currentLevel);
            Serial.print("% (umbral: ");
            Serial.print(Config.deepSleep.waterLevelThreshold);
            Serial.println("%)");
            return true;
        }
        
        return false;
    }
    
}