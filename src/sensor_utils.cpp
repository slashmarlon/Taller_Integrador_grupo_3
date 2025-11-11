#include "sensor_utils.h"

namespace SENSORS_Utils {

    // Objetos globales para sensores.
    OneWire oneWire(TEMP_PIN);
    DallasTemperature tempSensor(&oneWire);

    // Inicialización de sensores.
    void initSensors() {
        tempSensor.begin();
    }

   // Lectura de temperatura (DS18B20).
    String readTemperature() {
        tempSensor.requestTemperatures();
        float tempC = tempSensor.getTempCByIndex(0);
        if (tempC == DEVICE_DISCONNECTED_C) {
            return "Temp:Error";
        }
        return "T:" + String(tempC, 1) + "C";
    }

    // Lectura de nivel de agua analógico.
    String readWaterLevel() {
        int rawValue = analogRead(WATER_PIN);
        // Normalizamos a un porcentaje, valores de 0 a 520.
        float percentage = (rawValue / 520.0) * 100.0;
        return "N:" + String(percentage, 1) + "%";
    }

    // Lectura de turbidez analógico.
    //String readTurbidity() {
    //    int rawValue = analogRead(TURB_PIN);
        // Conversión simplificada: mapear voltaje a rango de pH (0-14)
    //    float voltage = (rawValue / 4095.0) * 3.3;  // Suponiendo Vref = 3.3V
    //    return "Turbidez:" + String(voltage, 2) + "V";
    //}

    // Unir todas las lecturas en un solo String.
    String getAllReadings() {
        // String data = readTemperature() + "; " + readWaterLevel() + "; " + readTurbidity();
        String data = readTemperature() + "; " + readWaterLevel();
        return data;
    }

}
