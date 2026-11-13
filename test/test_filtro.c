/**
 * @file test_filtro.c
 * @date :2026/11/13 07:44:03
 * @brief Programa de test para verificar el comportamiento del filtro IIR
 *
 * Este fichero contiene una serie de tests diseñados para caracterizar
 * y verificar el correcto funcionamiento de un filtro IIR implementado
 * en formato Direct Form II Transpose (DF2T).
 *
 * Los tests incluidos son:
 * - Test 1: Respuesta impulsional del filtro
 * - Test 2: Respuesta al escalón del filtro
 * - Test 3: Respuesta en frecuencia a 300 Hz (banda de paso)
 * - Test 4: Respuesta en frecuencia a 3326 Hz (banda de rechazo)
 *
 * @note El formato numérico utilizado es Q15 (punto fijo con 15 bits fraccionarios)
 * @note Se asume una frecuencia de muestreo de Fs = 48 kHz.
 *       El incremento de fase del DDS se calcula como:
 *
 *           phase_inc = (2^16 · fo) / Fs
 *
 *       donde fo es la frecuencia de salida deseada.
 *
 *       Para la simulación se utiliza el simulador del Cortex-M4, cuyo reloj
 *       funciona a 12 MHz. Debido a esta limitación, el periodo de muestreo
 *       empleado es de 208,33 µs, lo que equivale a una frecuencia de
 *       muestreo de Fs = 4,8 kHz.
 *
 *       La señal obtenida es la esperada, aunque su frecuencia aparece
 *       escalada por un factor 10 respecto al sistema real, como consecuencia
 *       de la diferencia entre la frecuencia de muestreo de la simulación
 *       (4,8 kHz) y la frecuencia de diseño (48 kHz).
 */

 #include "dds.h"
 #include "ejercicios.h"
 #include <stdint.h>

 #include "ARMCM4.h"

// Variables globales para el test, se representaran en logic analyzer
__attribute__((section(".bss.noinit")))
int16_t g_outputsample;
int16_t g_inputsample = 0;

/**
 * @brief Inicializa el contador SysTick para generar una base de tiempos.
 */
void SysTick_Init__sample_period(void);

/**
 * @brief Espera a que SysTick complete un periodo.
 */
static inline void SysTick_Wait_sample_period(void);


int main(void) {

  SysTick_Init__sample_period(); // Inicializa SysTick para generar una base de tiempos de 208

  // Test 1: Respuesta impulsional del filtro
  // Permite analizar la respuesta temporal del filtro ante un impulso unitario
  for (int n = 0; n < 512; n++) {
    if (n == 0) {
      g_inputsample = 16384; // Impulso unitario en formato Q15 (0.5 en valor real)
    } else {
      g_inputsample = 0;
    }
    g_outputsample = iir_filtro_df2t(g_inputsample);
    // La variable g_outputsample contiene la respuesta impulsional del filtro
    SysTick_Wait_sample_period(); // Espera 208.33 µs
  }
  __BKPT(1); // Punto de interrupción para inspeccionar la respuesta impulsional

  // Test 2: Respuesta al escalón del filtro
  // Permite analizar la estabilidad y ganancia en régimen permanente
  for (int n = 0; n < 512; n++) {
    g_inputsample = 16384; // Escalón unitario en formato Q15 (0.5 en valor real)
    g_outputsample = iir_filtro_df2t(g_inputsample);
    // La variable g_outputsample converge al valor de ganancia DC del filtro
    SysTick_Wait_sample_period(); // Espera 208.33 µs
  }
  __BKPT(1); // Punto de interrupción para inspeccionar la respuesta al escalón

  // Test 3: Respuesta en frecuencia - Tono de 300 Hz
  // Permite medir la ganancia del filtro a 300 Hz
  {
    dds_16_bits_t dds = {
        .phase_accumulator = 0,
        .phase_increment = 410}; // Incremento de fase para generar 300 Hz a Fs=48 kHz
    for (int n = 0; n < 1024; n++) {
      g_inputsample = dds_16_bits_get_next_sample(&dds); // Genera muestra de señal senoidal
      g_outputsample = iir_filtro_df2t(g_inputsample);
      // Comparar amplitud de g_outputsample con g_inputsample para obtener ganancia
      SysTick_Wait_sample_period(); // Espera 208.33 µs
    }
  }
  __BKPT(1); // Punto de interrupción para analizar respuesta a 300 Hz

  // Test 4: Respuesta en frecuencia - Tono de 3326 Hz
  // Permite medir la atenuación del filtro a 3326 Hz
  dds_16_bits_t dds = {
      .phase_accumulator = 0,
      .phase_increment = 4541}; // Incremento de fase para generar 3326 Hz a Fs=48 kHz
  for (int n = 0; n < 1024; n++) {
    g_inputsample = dds_16_bits_get_next_sample(&dds); // Genera muestra de señal senoidal
    g_outputsample = iir_filtro_df2t(g_inputsample);
    // Comparar amplitud de g_outputsample con g_inputsample para obtener atenuación
    SysTick_Wait_sample_period(); // Espera 208.33 µs
  }

  __BKPT(1); // Punto de interrupción para analizar respuesta a 3326 Hz
}






/**
 * @section systick_base_tiempo Base de tiempos con SysTick
 * Configuración y espera del contador SysTick.
 */

#include "ARMCM4.h"
#include "core_cm4.h"   // o core_cm0.h, core_cm3.h, etc.

/**
 * @brief Configura e inicia el contador SysTick.
 * @details Carga el valor 2499 y habilita el contador con el reloj del procesador.
 *          No habilita la generación de interrupciones.
 */
void SysTick_Init__sample_period(void)
{
    SysTick->LOAD = 2500 - 1;    // 208.33 µs @ 12 MHz
    SysTick->VAL  = 0;           // Reinicia el contador

    SysTick->CTRL =
          SysTick_CTRL_CLKSOURCE_Msk  // Reloj del procesador
        | SysTick_CTRL_ENABLE_Msk;    // Habilita SysTick

    // TICKINT no se activa -> no hay interrupciones
}

/**
 * @brief Espera hasta que SysTick termine un periodo.
 * @details La función bloquea la ejecución hasta que el contador llega a cero.
 */
static inline void SysTick_Wait_sample_period(void)
{
    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0)
    {
        // Espera hasta que el contador llegue a cero
    }
}
