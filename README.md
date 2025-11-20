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

<img width="4750" height="900" alt="Flujo de Datos" src="Flujo_datos.PNG" />


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

<img width="240" height="297" alt="image" src="https://github.com/user-attachments/assets/83827a62-7137-4371-906c-f3ccd2a47ea3" />

<img width="240" height="246" alt="image" src="https://github.com/user-attachments/assets/fd5d3554-f433-42c0-a590-64cb389f79c9" />

<img width="240" height="241" alt="image" src="https://github.com/user-attachments/assets/98b33edd-3e3e-4a0e-9c2a-876f26df9bb1" />








