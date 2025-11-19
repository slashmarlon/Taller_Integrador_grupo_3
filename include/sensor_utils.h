/*
Lectura y normalización de sensores adicionales (ej. temperatura, turbidez y nivel de agua).
ACTUALIZADO: Incluye control de alimentación y funciones para obtener valores numéricos.
*/

#ifndef SENSORS_UTILS_H_
#define SENSORS_UTILS_H_

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>   // Para sensor de temperatura DS18B20.
// Para el sensor de turbidez y nivel de agua se usa lectura analógica.

namespace SENSORS_Utils {

    // Pines de sensores.
    const int TEMP_PIN = 32;       // Pin de datos del DS18B20.
    const int WATER_PIN = 33;      // Entrada analógica nivel de agua.
    // const int TURB_PIN = A1;    // Entrada analógica sensor de turbidez.
    
    // NUEVOS PINES DE CONTROL DE ALIMENTACIÓN (opcional, comentar si no se usan)
    #define TURB_VCC_PIN 25        // Pin para controlar alimentación de turbidez
    #define WATER_VCC_PIN 26       // Pin para controlar alimentación de nivel

    // Inicialización del bus OneWire para el sensor de temperatura.
    extern OneWire oneWire;
    extern DallasTemperature tempSensor;

    // Funciones originales
    void initSensors();              // Inicializa sensores.
    String readTemperature();        // Devuelve temperatura en °C como String.
    String readWaterLevel();         // Devuelve nivel de agua como String.
    // String readTurbidity();       // Devuelve valor de turbidez como String.
    String getAllReadings();         // Une todas las lecturas en un solo String.
    
    // NUEVAS FUNCIONES
    void powerOnSensors();           // Enciende alimentación de sensores
    void powerOffSensors();          // Apaga alimentación de sensores
    float getTemperatureValue();     // Devuelve temperatura como float
    float getWaterLevelValue();      // Devuelve nivel de agua como float

}

#endif