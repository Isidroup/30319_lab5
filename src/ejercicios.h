/**
 * @file ejercicios.h
 * @brief Declaraciones de funciones para los ejercicios de laboratorio 5
 *
 * Este fichero de cabecera contiene las declaraciones de las funciones principales
 * utilizadas en el laboratorio 5, incluyendo:
 * - Filtro IIR en formato Direct Form II Transpose
 * - Demodulador FSK
 * - Decodificador UART
 *
 * @note Todas las funciones operan con señales en formato Q15 (punto fijo)
 * @note Frecuencia de muestreo asumida: Fs = 48 kHz
 *
 * @author [Tu nombre]
 * @date October 2025
 * @course 30319 - Sistemas Empotrados y de Tiempo Real
 * @version 1.0
 */

#ifndef EJERCICIOS_L5_H
#define EJERCICIOS_L5_H

#include <stdint.h>

// Evitar el uso de tipos de punto flotante
#pragma clang diagnostic error "-Wdouble-promotion"
#pragma clang diagnostic error "-Wfloat-conversion"
#pragma clang diagnostic error "-Wimplicit-float-conversion"

// =============================================================================
// FUNCIONES DE PROCESADO DIGITAL DE SEÑAL
// =============================================================================

/**
 * @brief Filtro elíptico IIR de 2º orden (DF2T).
 *
 * @param entrada Señal de entrada en Q15 (<16,15>).
 * @return Señal filtrada en Q15 (<16,15>).
 *
 * @details
 * - Estructura: Forma directa II transpuesta.
 * - Coeficientes escalados para operar en enteros (comentados en el código).
 * - Estados internos en 32 bits, con desplazamientos para mantener rango.
 *
 * Diseño (Matlab):
 * @code
 * fs=48000;
 * [b,a] = ellip(2,1,30,600/(fs/2));
 * @endcode
  *
 * @see https://en.wikipedia.org/wiki/Digital_biquad_filter
 */
int16_t iir_filtro_df2t(int16_t entrada);

// =============================================================================
// FUNCIONES DE COMUNICACIÓN FSK
// =============================================================================

/**
 * @brief Demodulación FSK por autocorrelación y filtrado.
 *
 * @details
 * Realiza:
 *  1) Línea de retardo (22 muestras) y producto entrada·retardo (autocorrelación).
 *  2) Filtrado IIR de 2º orden (DF2T) sobre el producto.
 *  3) Decisión binaria con umbral fijo.
 *
 * @param FSK_in Muestra de entrada (Q15, rango int16_t).
 * @return Bit demodulado: 1 o 0.
 *
 * @pre Llamar por cada nueva muestra recibida (p.ej., por I2S).
 * @note Umbral ajustado empíricamente .
 */
uint8_t lab5(int16_t FSK_in);


#endif // EJERCICIOS_L5_H
