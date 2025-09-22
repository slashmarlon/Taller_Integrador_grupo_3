#include "SENSORS_UTILS.h"

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
        return "Temp:" + String(tempC, 1) + "C";
    }

    // Lectura de nivel de agua analógico.
    String readWaterLevel() {
        int rawValue = analogRead(WATER_PIN);
        // Normalizamos a un porcentaje, valores de 0 a 520.
        float percentage = (rawValue / 520.0) * 100.0;
        return "Nivel:" + String(percentage, 1) + "%";
    }

    // Lectura de pH analógico.
    String readPH() {
        int rawValue = analogRead(PH_PIN);
        // Conversión simplificada: mapear voltaje a rango de pH (0-14)
        float voltage = (rawValue / 1023.0) * 5.0;  // Suponiendo Vref = 5V
        float phValue = 3.5 * voltage;              // Factor típico aproximado
        return "pH:" + String(phValue, 2);
    }

    // Unir todas las lecturas en un solo String.
    String getAllReadings() {
        String data = readTemperature() + "; " + readWaterLevel() + "; " + readPH();
        return data;
    }

}
