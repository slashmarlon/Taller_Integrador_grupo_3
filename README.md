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

## Firmware

El código base de control del tracker es el firmware libre establecido por Ricardo Guzman (richonguzman) [Aqui](https://github.com/richonguzman/LoRa_APRS_Tracker/tree/main).

El siguiente paso es agregar código de control de los sensores, la idea es hacer lectura de cada uno, conectado a un pin distinto del ESP32 y obtener como salida un unico string como salida. Este luego es agregado al paquete de APRS como "comment" al final de la trama del protocolo. Paso a paso sigue:\

1. Inicializar pines, sensores y modulo LoRa.
2. Medir temperatura, nivel de agua y pH con sensores conectados a sus entradas digitales/analógicas (GPIO/ADC).
3. Convertir cada lectura en dato tipo string.
4. Concatenar los valores en un solo mensaje de telemetría.
5. Empaquetar ese mensaje en el formato APRS al final de la trama, considerándose como un "comentario".
6. Transmitirlo mediante un módulo LoRa hacia un gateway APRS a una frecuencia de 433.775 Mhz.

## Resultados

<img width="1222" height="273" alt="image" src="https://github.com/user-attachments/assets/83827a62-7137-4371-906c-f3ccd2a47ea3" />

<img width="1222" height="273" alt="image" src="https://github.com/user-attachments/assets/fd5d3554-f433-42c0-a590-64cb389f79c9" />

<img width="1222" height="273" alt="image" src="https://github.com/user-attachments/assets/98b33edd-3e3e-4a0e-9c2a-876f26df9bb1" />

