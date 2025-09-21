#ifndef SS_UTILS_H_
#define SS_UTILS_H_

#include <Arduino.h> 

namespace SS_Utils {

    // Inicializa el pin del sensor.
    void setup(uint8_t analogPin);

    // Lee el nivel de agua y lo asigna a un string.
    String readWaterLevel();

}

#endif
