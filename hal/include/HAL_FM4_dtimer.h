/**
 * @file HAL_FM4_dtimer.h
 * @brief Interfaz para funciones de retardo utilizando el timer del FM4
 * @details Este archivo proporciona funciones para generar retardos precisos
 * utilizando los temporizadores del microcontrolador Cypress FM4
 *
 * @author Universidad de Zaragoza
 * @date Created on: 2025/07/14
 * @date Last modified: 2025/07/14 10:48:29
 */

#ifndef _HAL_FM4_DTIMER_H_
#define _HAL_FM4_DTIMER_H_

#include "stdint.h"
#include "mcu.h"

/**
 * @brief Timer utilizado para la función de retardo
 * @note Este valor define qué temporizador se utilizará para implementar los
 *        retardos. Valores posibles: 0->DTIM1, 1->DTIM2.
 */
#define DTIM_delay 0 // Define the timer to be used for delay

/**
 * @brief Genera un retardo en microsegundos
 *
 * @details Esta función bloquea la ejecución durante el número especificado
 * de microsegundos utilizando un timer de hardware para mayor precisión
 *
 * @param[in] us Tiempo de retardo en microsegundos
 *
 * @pre El sistema debe estar inicializado correctamente
 * @pre El reloj del sistema debe estar configurado
 *
 * @return void
 *
 * @note La precisión puede variar según la frecuencia del reloj del sistema
 * @warning Esta función es bloqueante y no debe usarse en contextos críticos de tiempo
 */
void delay_us (uint32_t us);

/**
 * @brief Genera un retardo en milisegundos
 *
 * @details Esta función bloquea la ejecución durante el número especificado
 * de milisegundos utilizando un timer de hardware para mayor precisión
 *
 * @param[in] ms Tiempo de retardo en milisegundos
 *
 * @pre El sistema debe estar inicializado correctamente
 * @pre El reloj del sistema debe estar configurado
 *
 * @return void
 *
 * @note La precisión puede variar según la frecuencia del reloj del sistema
 * @warning Esta función es bloqueante y no debe usarse en contextos críticos de tiempo
 */
void delay_ms (uint32_t ms);

#endif  /* _HAL_FM4_DTIMER_H_ */
