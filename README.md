# Taller_Integrador_grupo_3

# Tracker 2

## Integrantes
Marlon Daniel Ramírez Cruz\
Heiner Esteban Rivera Víquez\
Gabriel Ignacio Miranda Lopez

## Resumen

El presente proyecto propone el diseño e implementación de un sistema de monitoreo remoto para ecosistemas acuáticos, orientado a garantizar la adecuada calidad del agua y prevenir condiciones adversas que afecten la salud de sus peces. El sistema integra sensores de temperatura, turbidez y nivel de agua, conectados a un microcontrolador con módulo LoRa, encargado de adquirir, procesar y empaquetar los datos en formato APRS. Posteriormente, la información haciendo función de Tracker es transmitida mediante tecnología LoRa, que ofrece bajo consumo energético y gran alcance en la comunicación inalámbrica.

## Objetivo general
1. Diseñar e implementar un sistema de monitoreo remoto para peceras domésticas que integre sensores de temperatura, turbidez y nivel de agua, con comunicación de datos mediante protocolo LoRa-APRS.

## Objetivos especificos
1. Integrar sensores de temperatura, turbidez y nivel de agua a un microcontrolador con módulo LoRa, para la adquisición continua de parámetros críticos de la pecera.
2. Desarrollar el firmware del modulo basado en LoRa-APRS, que permita enviar datos de telemetría de manera eficiente y confiable hacia un nodo receptor o gateway.
3. Validar el funcionamiento del sistema en condiciones reales de operación, evaluando precisión de sensores, cobertura de transmisión y confiabilidad de la comunicación.

## Componentes

- ESP32 TTGO T-Beam V1.2.
- Sensor de temperatura digital tipo tubular DS18B20.
- Sensor de nivel de agua MH analógico.
- Sensor de turbidez analógico.
- Sistema de alimentacion: Bateria recargable y/o panel solar.
- Carcasa: Proteccion para agua y caídas.

## Diagrama de primer nivel

<img width="1222" height="273" alt="image" src="https://github.com/user-attachments/assets/7b5fdaaa-5dd2-4227-8c7f-71955ac1f349" />

## Máquina de estados

<img width="952" height="450" alt="image" src="https://github.com/user-attachments/assets/b1f98b5d-17e0-489e-8370-48cb0d509219" />

## Diagrama de tercer nivel

<img width="952" height="450" alt="image" src="https://github.com/user-attachments/assets/a9d826a2-f5dc-45d7-9c53-69feeafbd41c" />

### Diagrama de Flujo de Datos

<img width="1819" height="2113" alt="Flujo_datos" src="https://github.com/user-attachments/assets/0cbff524-dfe9-4bf4-af72-669e3ea09013" />


## Firmware

El código base de control del tracker es el firmware libre establecido por Ricardo Guzman (richonguzman) [Aqui](https://github.com/richonguzman/LoRa_APRS_Tracker/tree/main).

### Modificaciones Implementadas

#### 1. Integración de Sensores
Se agregó el módulo `sensor_utils.cpp/h` con las siguientes funcionalidades:
- Lectura de temperatura mediante sensor DS18B20 (OneWire)
- Lectura de nivel de agua mediante ADC analógico (GPIO33)
- Control de alimentación mediante GPIOs (25, 26) para ahorro energético
- Validación de lecturas y manejo de errores
- Concatenación de datos en formato string para transmisión

**Pines utilizados:**
- GPIO32: Datos DS18B20 (temperatura)
- GPIO33: ADC nivel de agua
- GPIO25: Control alimentación sensor turbidez (reservado)
- GPIO26: Control alimentación sensor nivel

#### 2. Modo Estático con SmartBeaconing Adaptado
Se modificó `smartbeacon_utils.cpp` para soportar operación estática:
- **Modo Estático**: Intervalos fijos de transmisión (configurable, por defecto 5 minutos)
- **Transmisión por Umbrales**: TX inmediata si se detectan condiciones críticas:
  - Temperatura alta: > 30°C
  - Temperatura baja: < 18°C
  - Nivel de agua bajo: < 30%
- Deshabilitación de cálculos GPS innecesarios en modo estático

#### 3. DeepSleep ESP32
Se implementó `sleep_utils.cpp` con gestión completa de DeepSleep:
- **Preparación**: Apagado de sensores y GPS antes de dormir
- **Timer Wake Up**: Despertar automático cada X minutos (configurable)
- **Ahorro Energético**: Consumo reducido de 240mA a 0.01mA en sleep
- **Autonomía**: ~15-30 días con batería de 2500mAh

#### 4. Configuración Extendida
Se actualizó `configuration.cpp/h` y `tracker_conf.json`:
```json
{
  "beacons": [{
    "staticMode": true,
    "staticBeaconInterval": 5
  }],
  "deepSleep": {
    "enabled": true,
    "sleepTimeMinutes": 5,
    "tempThresholdHigh": 30.0,
    "tempThresholdLow": 18.0,
    "waterLevelThreshold": 30.0
  }
}
```

## Resultados

Inicialmente se tiene la comprobación de la correcta conexión y envio de datos del tracker mediante protocolo LoRa APRS validada mediante el seguimiento en el sitio web aprs.fi

<img width="240" height="297" alt="image" src="https://github.com/user-attachments/assets/83827a62-7137-4371-906c-f3ccd2a47ea3" />

<img width="240" height="246" alt="image" src="https://github.com/user-attachments/assets/fd5d3554-f433-42c0-a590-64cb389f79c9" />

<img width="240" height="241" alt="image" src="https://github.com/user-attachments/assets/98b33edd-3e3e-4a0e-9c2a-876f26df9bb1" />

Luego, se muestra un ejemplo de implementación del sistema para el monitoreo de ecosistemas acuáticos con ambos sensores integrados.
<img width="240" height="241" alt="image" src="https://github.com/user-attachments/assets/ca4e1870-7ceb-441d-b962-dbfc44508834" />

Por último, se muestra el módulo enviando datos y realizando mediciones
<img width="240" height="241" alt="image" src="https://github.com/user-attachments/assets/71e15f6b-6eef-4ede-a6e6-9f9ecc2c0b78" />

## Limitaciones 
Escasez de disponibilidad inmediata de sensores de PH y Turbidez accesibles: Se pudo observar una escasez en la disponibilidad de sensores medidores de PH accesibles en el periodo necesario para desarrollar el proyecto, se buscaron soluciones, no obstante, las de disponibilidad inmediata se salían del presupuesto con mucha diferencia o los plazos de entrega se excedía del período de realización del proyecto.
Resistencia y calidad de sensores: para una implementación real se debe de buscar sensores de alto nivel con resistencia IP67 debido a que los mismos deben de estar sumergidos en el ambiente acuático por tiempos prolongados y expuestos a climas adversos
Dificultades para conectar el dispositivo al igate: se logró la conexión con el igate del ITCR, no obstante desde ubicaciones como Heredia o Tierra Blanca de Cartago no fue posible conectar el dispositivo a algún igate cercano, además en interiores demostró dificultades para mantener una conexión y envío de datos activa

## Conclusiones

-Se logró implementar un prototipo de un sistema de monitoreo remoto para ecosistemas acuáticos con comunicación de datos mediante el protocolo LoRa-APRS
-Se lograron integrar dos de los tres sensores propuestos de manera funcional enviando datos al ESP32, en específico el sensor de nivel y el de temperatura
-Se desarrolló un firmware correcto para el envío de telemetría, no obstante, parte de las limitaciones del proyecto fue la dificultad para conectarse al igate y poder ver los datos enviados
-Se validó el funcionamiento del sistema mediante el tracking web y la medición de los sensores implementados
            
## Recomendaciones 

-Se logró implementar un prototipo de un sistema de monitoreo remoto para ecosistemas acuáticos con comunicación de datos mediante el protocolo LoRa-APRS
-Se lograron integrar dos de los tres sensores propuestos de manera funcional enviando datos al ESP32
-Se desarrolló un firmware correcto para el envío de telemetría 
-Se validó el funcionamiento del sistema mediante el tracking web y la medición de los sensores implementados








