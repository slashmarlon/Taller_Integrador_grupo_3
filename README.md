# Taller_Integrador_grupo_3

# Tracker 2

## Integrantes
Marlon Daniel Ramírez Cruz\
Heiner Esteban Rivera Víquez\
Gabriel Ignacio Miranda Lopez

## Resumen

El presente proyecto propone el diseño e implementación de un sistema de monitoreo remoto para peceras domésticas, orientado a garantizar la adecuada calidad del agua y prevenir condiciones adversas que afecten la salud de sus peces. El sistema integra sensores de temperatura, pH y nivel de agua, conectados a un microcontrolador con módulo LoRa, encargado de adquirir, procesar y empaquetar los datos en formato APRS. Posteriormente, la información es transmitida mediante tecnología LoRa, que ofrece bajo consumo energético y gran alcance en la comunicación inalámbrica.

## Objetivo general
1. Diseñar e implementar un sistema de monitoreo remoto para peceras domésticas que integre sensores de temperatura, pH y nivel de agua, con comunicación de datos mediante protocolo LoRa-APRS.

## Objetivos especificos
1. Integrar sensores de temperatura, pH y nivel de agua a un microcontrolador con módulo LoRa, para la adquisición continua de parámetros críticos de la pecera.
2. Desarrollar el firmware del modulo basado en LoRa-APRS, que permita enviar datos de telemetría de manera eficiente y confiable hacia un nodo receptor o gateway.
3. Validar el funcionamiento del sistema en condiciones reales de operación, evaluando precisión de sensores, cobertura de transmisión y confiabilidad de la comunicación.

## Componentes

- ESP32-LoRa.
- Sensores: Temperatura, pH y nivel del agua.
- Sistema de alimentacion: Bateria recargable y/o panel solar.
- Carcasa: Proteccion para interiores (impermeable).

## Diagrama de primer nivel

<img width="1222" height="273" alt="image" src="https://github.com/user-attachments/assets/7b5fdaaa-5dd2-4227-8c7f-71955ac1f349" />

## Firmware

El codigo base de control del tracker es el firmware libre establecido por Ricardo Guzman (richonguzman) en [Aqui](https://github.com/richonguzman/LoRa_APRS_Tracker/tree/main).
