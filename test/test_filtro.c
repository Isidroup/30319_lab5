/**
 * @file test_filtro.c
 * @date :2025/10/28 09:22:32
 * @brief Programa de test para verificar el comportamiento del filtro IIR
 *
 * Este fichero contiene una serie de tests diseñados para caracterizar
 * y verificar el correcto funcionamiento de un filtro IIR implementado
 * en formato Direct Form II Transpose (DF2T).
 *
 * Los tests incluidos son:
 * - Test 1: Respuesta impulsional del filtro
 * - Test 2: Respuesta al escalón del filtro
 * - Test 3: Respuesta en frecuencia a 600 Hz (banda de paso)
 * - Test 4: Respuesta en frecuencia a 3326 Hz (banda de rechazo)
 *
 * @note El formato numérico utilizado es Q15 (punto fijo con 15 bits fraccionarios)
 * @note La frecuencia de muestreo asumida es Fs = 48 kHz
 *
 */

#include "ARMCM4.h"
#include "dds.h"
#include "ejercicios.h"
#include <stdint.h>


// Variables globales para el test, se representaran en logic analyzer
__attribute__((section(".bss.noinit")))
int16_t g_outputsample;
int16_t g_inputsample = 0;

int main() {

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
  }
  __BKPT(1); // Punto de interrupción para inspeccionar la respuesta impulsional

  // Test 2: Respuesta al escalón del filtro
  // Permite analizar la estabilidad y ganancia en régimen permanente
  for (int n = 0; n < 512; n++) {
    g_inputsample = 16384; // Escalón unitario en formato Q15 (0.5 en valor real)
    g_outputsample = iir_filtro_df2t(g_inputsample);
    // La variable g_outputsample converge al valor de ganancia DC del filtro
  }
  __BKPT(1); // Punto de interrupción para inspeccionar la respuesta al escalón

  // Test 3: Respuesta en frecuencia - Tono de 600 Hz
  // Permite medir la ganancia del filtro a 600 Hz
  {
    dds16bits_t dds = {
        .phaseAccumulator = 0,
        .phaseIncrement = 439}; // Incremento de fase para generar 600 Hz a Fs=48 kHz
    for (int n = 0; n < 1024; n++) {
      g_inputsample = DDS16Bits_getNextSample(&dds); // Genera muestra de señal senoidal
      g_outputsample = iir_filtro_df2t(g_inputsample);
      // Comparar amplitud de g_outputsample con g_inputsample para obtener ganancia
    }
  }
  __BKPT(1); // Punto de interrupción para analizar respuesta a 500 Hz

  // Test 4: Respuesta en frecuencia - Tono de 3326 Hz
  // Permite medir la atenuación del filtro a 3326 Hz
  dds16bits_t dds = {
      .phaseAccumulator = 0,
      .phaseIncrement = 2431}; // Incremento de fase para generar 3326 Hz a Fs=48 kHz
  for (int n = 0; n < 1024; n++) {
    g_inputsample = DDS16Bits_getNextSample(&dds); // Genera muestra de señal senoidal
    g_outputsample = iir_filtro_df2t(g_inputsample);
    // Comparar amplitud de g_outputsample con g_inputsample para obtener atenuación
  }

  __BKPT(1); // Punto de interrupción para analizar respuesta a 3326 Hz
}
