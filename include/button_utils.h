/* 
Manejo de botones físicos: detección de pulsos, debounce, acciones de corto/largo toque.
 */

#ifndef BUTTON_UTILS_H_
#define BUTTON_UTILS_H_

#include <Arduino.h>

namespace BUTTON_Utils {

    void longPress1();
    void doublePress1();

    void loop();
    void setup();

}

#endif
