# Laboratorio 5 - Sistemas Empotrados (2024-2025)

## Descripción
Firmware para placa de desarrollo FM4 Pioneer Kit. Incluye ejemplos de manejo de periféricos, 
interrupciones y códec de audio WM8731.

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
1. Diseño y test de un filtro digital IIR
2. Demodulador FSK v.23


## Notas de Implementación
- El BSP abstrae el acceso al hardware
- Las interrupciones se gestionan en `src/isr.c`
- Los ejercicios usan la HAL para portabilidad

