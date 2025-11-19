# 30319 Laboratorio 5: Demodulación FSK, modem v.23

Este proyecto implementa un sistema de demodulación FSK (Frequency Shift Keying)para microcontroladores FM4, utilizando un codec de audio WM8731.

## Descripción General

El proyecto consiste en un sistema embebido que:
- Genera señales FSK moduladas controladas por pulsaciones de botón.
- Demodula señales FSK recibidas a través del codec WM8731.
- Utiliza interrupciones para la transmisión y recepción de la señal analógica a través de I2S con buffer circular.
- Implementa control visual mediante LEDs RGB
- Utiliza un ejecutivo cíclico para la gestión de tareas en tiempo real

### Hardware Utilizado
- Placa FM4 con codec de audio WM8731
- LED RGB para indicación visual del estado
- LED ETH con efecto breathing
- Pulsador SW2 para control de usuario
- Comunicación I2S para transmisión de audio



## Estructura del Proyecto

```
.
├── bsp/                    # Board Support Package
│   ├── include/           # Cabeceras BSP
│   │   ├── FM4_leds_sw.h # Control de LEDs y switches
│   │   └── FM4_WM8731.h  # Driver códec audio
│   └── src/              # Implementaciones BSP
├── build_keil/           # Archivos proyecto Keil µVision
├── hal/                  # Hardware Abstraction Layer
├── shared/              # Código compartido
├── src/                 # Código fuente principal
│   ├── main.c          # Programa principal
│   ├── ejercicios.c    # Implementación ejercicios
│   ├── ejercicios.h    # Cabeceras ejercicios
│   └── isr.c           # Rutinas de interrupción
└── test/               # Pruebas unitarias
    ├── test_lab5.c
    └── test_filtro.c
```

## Requisitos
- Keil µVision 5 o superior
- FM4 Pioneer Kit
- Cable USB para programación/depuración

## Configuración del Entorno
1. Abrir el proyecto en Keil µVision (`build_keil/lab5.uvprojx`)
2. Verificar configuración del depurador
3. Compilar el proyecto

## Ejercicios Implementados
1. Diseño y test de un filtro digital IIR (test por simulación)
2. Demodulador FSK v.23 (test por simulación).
3. Verificación en la placa de desarrollo del demodulador FSK.
