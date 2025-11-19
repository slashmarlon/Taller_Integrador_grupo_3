#include "sensor_utils.h"

namespace SENSORS_Utils {

    // Objetos globales para sensores.
    OneWire oneWire(TEMP_PIN);
    DallasTemperature tempSensor(&oneWire);

    // Variables para almacenar últimas lecturas
    float lastTempReading = 0.0;
    float lastLevelReading = 0.0;

    // ============================================
    // NUEVA FUNCIÓN: ENCENDER SENSORES
    // ============================================
    void powerOnSensors() {
        // Encender sensor de turbidez (si está conectado a GPIO25)
        #ifdef TURB_VCC_PIN
            pinMode(TURB_VCC_PIN, OUTPUT);
            digitalWrite(TURB_VCC_PIN, HIGH);
        #endif
        
        // Encender sensor de nivel (si está conectado a GPIO26)
        #ifdef WATER_VCC_PIN
            pinMode(WATER_VCC_PIN, OUTPUT);
            digitalWrite(WATER_VCC_PIN, HIGH);
        #endif
        
        // Esperar a que los sensores se estabilicen
        delay(500);
        
        Serial.println("[SENSORES] Alimentación activada");
    }
    
    // ============================================
    // NUEVA FUNCIÓN: APAGAR SENSORES
    // ============================================
    void powerOffSensors() {
        #ifdef TURB_VCC_PIN
            digitalWrite(TURB_VCC_PIN, LOW);
        #endif
        
        #ifdef WATER_VCC_PIN
            digitalWrite(WATER_VCC_PIN, LOW);
        #endif
        
        Serial.println("[SENSORES] Alimentación desactivada");
    }

    // ============================================
    // INICIALIZACIÓN DE SENSORES
    // ============================================
    void initSensors() {
        // Configurar pines de control de alimentación
        powerOnSensors();
        
        // Inicializar sensor de temperatura DS18B20
        tempSensor.begin();
        
        Serial.println("[SENSORES] Inicializados correctamente");
    }

    // ============================================
    // LECTURA DE TEMPERATURA (DS18B20)
    // ============================================
    String readTemperature() {
        tempSensor.requestTemperatures();
        float tempC = tempSensor.getTempCByIndex(0);
        
        if (tempC == DEVICE_DISCONNECTED_C || tempC < -50 || tempC > 100) {
            Serial.println("[ERROR] Sensor de temperatura desconectado o fuera de rango");
            return "T:ERR";
        }
        
        lastTempReading = tempC;
        return "T:" + String(tempC, 1) + "C";
    }
    
    // ============================================
    // NUEVA FUNCIÓN: OBTENER VALOR DE TEMPERATURA
    // ============================================
    float getTemperatureValue() {
        tempSensor.requestTemperatures();
        float tempC = tempSensor.getTempCByIndex(0);
        
        if (tempC == DEVICE_DISCONNECTED_C || tempC < -50 || tempC > 100) {
            return lastTempReading; // Devolver última lectura válida
        }
        
        lastTempReading = tempC;
        return tempC;
    }

    // ============================================
    // LECTURA DE NIVEL DE AGUA 
    // ============================================
    String readWaterLevel() {
        int rawValue = analogRead(WATER_PIN);
        
        // Normalizamos a un porcentaje, valores de 0 a 520.
        float percentage = (rawValue / 520.0) * 100.0;
        
        // Limitar entre 0 y 100%
        if (percentage > 100.0) percentage = 100.0;
        if (percentage < 0.0) percentage = 0.0;
        
        lastLevelReading = percentage;
        return "N:" + String(percentage, 0);
    }
    
    // ============================================
    // NUEVA FUNCIÓN: OBTENER VALOR NUMÉRICO DE NIVEL
    // ============================================
    float getWaterLevelValue() {
        int rawValue = analogRead(WATER_PIN);
        float percentage = (rawValue / 520.0) * 100.0;
        
        if (percentage > 100.0) percentage = 100.0;
        if (percentage < 0.0) percentage = 0.0;
        
        lastLevelReading = percentage;
        return percentage;
    }

    // Lectura de turbidez analógico ( no está en uso )
    /*
    String readTurbidity() {
        int rawValue = analogRead(TURB_PIN);
        float voltage = (rawValue / 4095.0) * 3.3;  // Suponiendo Vref = 3.3V
        return "Tu:" + String(voltage, 2) + "V";
    }
    */

    // ============================================
    // UNIR TODAS LAS LECTURAS EN UN SOLO STRING
    // ============================================
    String getAllReadings() {
        // Encender sensores antes de leer
        powerOnSensors();
        
        // Leer todos los sensores
        String temp = readTemperature();
        String level = readWaterLevel();
        
        // Concatenar datos
        String data = " " + temp + " " + level;
        
        // Apagar sensores después de leer (ahorro de energía)
        powerOffSensors();
        
        return data;
    }

}