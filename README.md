# 30319 Laboratorio 5: Demodulación FSK, módem V.23

## Descripción

Este proyecto amplía el sistema de modulación FSK del laboratorio 4 con el procesamiento de la señal recibida. La práctica se desarrolla para la placa **FM4-176L-S6E2CC-ETH** y utiliza el códec de audio WM8731 para transmitir y recibir muestras mediante I2S.

## Características principales

- **Modulación y demodulación**: transmisión y recepción de señales FSK del módem V.23.
- **Procesamiento digital**: filtro IIR de segundo orden en formato Direct Form II Transposed (DF2T) y demodulación por autocorrelación.
- **Audio**: muestras estéreo en formato Q15, con una frecuencia de muestreo de 48 kHz.
- **Buffers**: buffers circulares para desacoplar el procesamiento de audio de la atención de las interrupciones I2S.
- **Control**: pulsador SW2 y LED RGB para la interacción y la indicación del estado.
- **Ejecución**: ejecutivo cíclico para las tareas periódicas y el procesamiento de muestras.

## Hardware utilizado

- Placa FM4-176L-S6E2CC-ETH con códec de audio WM8731.
- Pulsador SW2.
- LED RGB.
- Entrada y salida de audio conectadas al códec.

## Estructura del proyecto

```
lab5/
├── _doc/                  # Documentación del laboratorio
├── bsp/                   # Soporte específico de la placa
│   ├── include/           # Cabeceras del BSP
│   └── src/               # Implementaciones del BSP
├── build_keil/            # Proyecto Keil µVision
├── hal/                   # Capa de abstracción de hardware
│   ├── include/           # Cabeceras del HAL
│   └── src/               # Implementaciones del HAL
├── shared/                # Módulos compartidos
├── src/                   # Código fuente principal
│   ├── ejercicios.c       # Filtro IIR y demodulador FSK
│   ├── ejercicios.h       # Declaraciones de los ejercicios
│   ├── isr.c              # Rutina de interrupción I2S
│   └── main.c             # Inicialización y ejecutivo cíclico
└── test/                  # Programas de prueba
    ├── test_filtro.c      # Pruebas del filtro IIR
    └── test_lab5.c        # Prueba integrada de los laboratorios 4 y 5
```

### Carpeta `src/` - Código principal

- **`main.c`**: inicializa los periféricos y ejecuta el ciclo principal de la aplicación.
- **`ejercicios.c/h`**: contiene las funciones del filtro IIR y del demodulador FSK que se desarrollan en la práctica.
- **`isr.c`**: gestiona la transmisión y recepción de muestras mediante interrupciones I2S y buffers circulares.

### Carpetas `hal/` y `bsp/` - Acceso al hardware

- **`hal/`**: abstracción de los periféricos GPIO, I2C, I2S, temporizadores y SysTick.
- **`bsp/`**: control de los LEDs y pulsadores de la placa, y configuración del códec WM8731.

### Carpeta `test/` - Pruebas

- **`test_filtro.c`**: permite observar la respuesta del filtro ante distintas señales de prueba.
- **`test_lab5.c`**: integra la generación FSK del laboratorio 4 con las funciones de recepción del laboratorio 5.

## Actividades del laboratorio

1. Diseñar e implementar un filtro IIR de segundo orden en formato DF2T y analizar su respuesta.
2. Desarrollar un demodulador FSK basado en autocorrelación, filtrado y decisión binaria.
3. Integrar la recepción de audio mediante I2S y comprobar el sistema con pruebas de simulación y en la placa.

## Compilación

1. Abrir `build_keil/lab5.uvprojx` en Keil µVision.
2. Seleccionar la configuración de compilación deseada.
3. Compilar el proyecto y, para las pruebas en placa, programar la FM4.

keywords: FSK, módem V.23, demodulación, IIR, DF2T, I2S, WM8731, Q15, buffers circulares, FM4
