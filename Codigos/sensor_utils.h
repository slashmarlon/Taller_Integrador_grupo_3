#ifndef SENSORS_UTILS_H_
#define SENSORS_UTILS_H_

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>   // Para sensor de temperatura DS18B20.
// Para el sensor de pH y nivel de agua se usa lectura analógica.

namespace SENSORS_Utils {

    // Pines de sensores.
    const int TEMP_PIN = 2;       // Pin de datos del DS18B20.
    const int WATER_PIN = A0;     // Entrada analógica nivel de agua.
    const int PH_PIN = A1;        // Entrada analógica sensor de pH.

    // Inicialización del bus OneWire para el sensor de temperatura.
    extern OneWire oneWire;
    extern DallasTemperature tempSensor;

    // Funciones.
    void initSensors();   // Inicializa sensores.
    String readTemperature(); // Devuelve temperatura en °C como String.
    String readWaterLevel();  // Devuelve nivel de agua como String.
    String readPH();          // Devuelve valor de pH como String.
    String getAllReadings(); // Une todas las lecturas en un solo String.

}

#endif
