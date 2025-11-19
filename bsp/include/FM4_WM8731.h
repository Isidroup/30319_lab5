/**
 * @file FM4_WM8731.h
 * @brief Definiciones y funciones para el manejo del codec WM8731 en FM4-pioneer.
 *
 * Proporciona macros y funciones para la configuración y uso del codec WM8731,
 * incluyendo selección de entrada, ganancia y comunicación por I2C/I2S.
 */

#ifndef __FM4_WM8731__
#define __FM4_WM8731__

#include "HAL_FM4_i2s.h"
#include <stdint.h>

/** @name Dirección I2C del codec WM8731 */
#define WM8731_I2C_ADDRESS 0x1A /**< Dirección I2C: 0011010 */

/** @name Registros del codec WM8731 */
#define WM8731_LINE_IN_LEFT   ((uint8_t)0x00) /**< Registro entrada línea izquierda */
#define WM8731_LINE_IN_RIGHT  ((uint8_t)0x01) /**< Registro entrada línea derecha */
#define WM8731_HP_OUT_LEFT    ((uint8_t)0x02) /**< Registro salida auriculares izquierda */
#define WM8731_HP_OUT_RIGHT   ((uint8_t)0x03) /**< Registro salida auriculares derecha */
#define WM8731_ANALOG_PATH    ((uint8_t)0x04) /**< Registro ruta analógica */
#define WM8731_DIGITAL_PATH   ((uint8_t)0x05) /**< Registro ruta digital */
#define WM8731_POWER_DOWN     ((uint8_t)0x06) /**< Registro apagado */
#define WM8731_INTERFACE      ((uint8_t)0x07) /**< Registro interfaz */
#define WM8731_SAMPLING_RATE  ((uint8_t)0x08) /**< Registro frecuencia de muestreo */
#define WM8731_CONTROL        ((uint8_t)0x09) /**< Registro control */
#define WM8731_RESET          ((uint8_t)0x0F) /**< Registro reset */

/** @name Selección de entrada analógica */
#define WM8731_MIC_IN         ((uint8_t)0x14) /**< Entrada de micrófono */
#define WM8731_MIC_IN_BOOST   ((uint8_t)0x15) /**< Entrada de micrófono con ganancia */
#define WM8731_LINE_IN        ((uint8_t)0x11) /**< Entrada de línea */

/** @name Métodos de entrada/salida */
#define IO_METHOD_INTR        ((uint8_t)0x00) /**< Método por interrupción */
#define IO_METHOD_DMA         ((uint8_t)0x01) /**< Método por DMA */

/** @name Ganancias y atenuaciones de entrada de línea */
#define WM8731_LINE_IN_GAIN_0_DB   ((uint8_t)0x17) /**< Ganancia 0 dB */
#define WM8731_LINE_IN_GAIN_3_DB   ((uint8_t)0x19) /**< Ganancia 3 dB */
#define WM8731_LINE_IN_GAIN_6_DB   ((uint8_t)0x1B) /**< Ganancia 6 dB */
#define WM8731_LINE_IN_GAIN_9_DB   ((uint8_t)0x1D) /**< Ganancia 9 dB */
#define WM8731_LINE_IN_GAIN_12_DB  ((uint8_t)0x1F) /**< Ganancia 12 dB */
#define WM8731_LINE_IN_ATTEN_3_DB  ((uint8_t)0x15) /**< Atenuación -3 dB */
#define WM8731_LINE_IN_ATTEN_6_DB  ((uint8_t)0x13) /**< Atenuación -6 dB */
#define WM8731_LINE_IN_ATTEN_9_DB  ((uint8_t)0x11) /**< Atenuación -9 dB */

/** @name Ganancias y atenuaciones de salida de auriculares */
#define WM8731_HP_OUT_GAIN_0_DB    ((uint8_t)0x79) /**< Ganancia 0 dB */
#define WM8731_HP_OUT_GAIN_3_DB    ((uint8_t)0x7C) /**< Ganancia 3 dB */
#define WM8731_HP_OUT_GAIN_6_DB    ((uint8_t)0x7F) /**< Ganancia 6 dB */
#define WM8731_HP_OUT_ATTEN_3_DB   ((uint8_t)0x76) /**< Atenuación -3 dB */
#define WM8731_HP_OUT_ATTEN_6_DB   ((uint8_t)0x73) /**< Atenuación -6 dB */

/** @name Identificadores de canal */
#define LEFT  1 /**< Canal izquierdo */
#define RIGHT 0 /**< Canal derecho */

/**
 * @union WM8731_data
 * @brief Unión para acceso a datos de 32 y 16 bits.
 */
typedef union WM8731_data
{
  int32_t uint32bit;    /**< Acceso a 32 bits */
  int16_t uint16bit[2]; /**< Acceso a dos canales de 16 bits */
} WM8731_data_t;

/**
 * @brief Inicializa el codec WM8731.
 *
 * Configura el codec WM8731 de la placa FM4-pioneer, incluyendo frecuencia de muestreo,
 * selección de entrada analógica y ganancias de entrada/salida.
 *
 * @param fs Frecuencia de muestreo. Valores posibles:
 *           FS_8000_HZ, FS_16000_HZ, FS_24000_HZ, FS_32000_HZ, FS_48000_HZ, FS_96000_HZ.
 * @param select_input Selección de entrada analógica: WM8731_MIC_IN, WM8731_LINE_IN.
 * @param hp_out_gain Ganancia de salida de auriculares. Valores posibles:
 *           WM8731_HP_OUT_GAIN_0_DB, WM8731_HP_OUT_GAIN_3_DB, WM8731_HP_OUT_GAIN_6_DB,
 *           WM8731_HP_OUT_ATTEN_3_DB, WM8731_HP_OUT_ATTEN_6_DB.
 * @param line_in_gain Ganancia de entrada de línea. Valores posibles:
 *           WM8731_LINE_IN_GAIN_0_DB, WM8731_LINE_IN_GAIN_3_DB, WM8731_LINE_IN_GAIN_6_DB,
 *           WM8731_LINE_IN_GAIN_9_DB, WM8731_LINE_IN_GAIN_12_DB,
 *           WM8731_LINE_IN_ATTEN_3_DB, WM8731_LINE_IN_ATTEN_6_DB, WM8731_LINE_IN_ATTEN_9_DB.
 *
 * @note Esta función inicia el bus I2C, el codec y el bus I2S.
 */
void FM4_WM8731_init(uint8_t fs, uint8_t select_input, uint8_t hp_out_gain, uint8_t line_in_gain);

/**
 * @brief Escribe datos en el codec WM8731.
 *
 * Escribe los datos de los canales izquierdo y derecho en el codec.
 *
 * @param datoL Dato para el canal izquierdo.
 * @param datoR Dato para el canal derecho.
 */
void FM4_WM8731_wr(int16_t datoL, int16_t datoR);


/**
 * @brief Lee datos del codec WM8731.
 *
 * Lee los datos de los canales izquierdo y derecho desde el codec.
 *
 * @param datoL Puntero donde se almacenará el dato del canal izquierdo.
 * @param datoR Puntero donde se almacenará el dato del canal derecho.
 */
void FM4_WM8731_rd(int16_t *datoL, int16_t *datoR);


#endif
