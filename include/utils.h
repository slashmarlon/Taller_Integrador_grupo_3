/* 
Funciones variadas a utilizar:
- char* getMaidenheadLocator(double lat, double lon, uint8_t size);
Convierte la latitud y longitud en un locator Maidenhead.
- String createDateString(time_t t);
Genera un string con la fecha formateada.
- String createTimeString(time_t t);
Genera un string con la hora formateada.
- void checkStatus();
Revisa el estado general del dispositivo: GPS, LoRa, batería, sensores o flags internos 
para actualizar indicadores o tomar decisiones.
- void checkDisplayEcoMode();
Controla el modo de ahorro de pantalla.
- String getSmartBeaconState();
Devuelve un texto que indica el estado actual del SmartBeaconing, como velocidad, 
ajustes activos, o si está habilitado/deshabilitado.
- void i2cScannerForPeripherals();
Escanea el bus I2C para detectar qué periféricos están conectados (sensores, pantalla, etc.)
y muestra las direcciones encontradas.
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <Arduino.h>
#include <TimeLib.h>

namespace Utils {

    char    *getMaidenheadLocator(double lat, double lon, uint8_t size);
    String  createDateString(time_t t);
    String  createTimeString(time_t t);
    void    checkStatus();
    void    checkDisplayEcoMode();
    String  getSmartBeaconState();
    void    checkFlashlight();
    void    i2cScannerForPeripherals();

}

#endif
