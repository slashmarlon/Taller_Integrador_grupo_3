#ifndef SENSORS_UTILS_H_
#define SENSORS_UTILS_H_

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>   // Para sensor de temperatura DS18B20.
// Para el sensor de turbidez y nivel de agua se usa lectura analógica.

namespace SENSORS_Utils {

    // Pines de sensores.
    const int TEMP_PIN = 32;       // Pin de datos del DS18B20.
    const int WATER_PIN = 33;     // Entrada analógica nivel de agua.
    // const int TURB_PIN = A1;        // Entrada analógica sensor de turbidez.

    // Inicialización del bus OneWire para el sensor de temperatura.
    extern OneWire oneWire;
    extern DallasTemperature tempSensor;

    // Funciones.
    void initSensors();   // Inicializa sensores.
    String readTemperature(); // Devuelve temperatura en °C como String.
    String readWaterLevel();  // Devuelve nivel de agua como String.
    // String readTurbidity();   // Devuelve valor de turbidez como String.
    String getAllReadings(); // Une todas las lecturas en un solo String.

    }

#endif
