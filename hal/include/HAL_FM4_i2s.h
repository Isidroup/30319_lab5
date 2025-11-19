/**
 * @file HAL_FM4_i2s.h
 * @brief Interfaz HAL para el periférico I2S en FM4.
 * @date :2025/10/08 12:05:47
 *
 * Proporciona funciones para inicializar, transmitir, recibir y controlar el periférico I2S.
 * Permite la configuración de la frecuencia de muestreo y el manejo de buffers de transmisión y recepción.
 *
 * Valores posibles para la frecuencia de muestreo (fs) en I2S_init():
 *   - FS_48000_HZ
 *   - FS_8000_HZ
 *   - FS_16000_HZ
 *   - FS_24000_HZ
 *   - FS_32000_HZ
 *   - FS_96000_HZ
 */

#ifndef __HAL_FM4_I2S__
#define __HAL_FM4_I2S__

#include <stdint.h>

/** @name Frecuencias de muestreo soportadas */
#define FS_8000_HZ  ((uint8_t)0x0C)
#define FS_16000_HZ ((uint8_t)0x58)
#define FS_24000_HZ ((uint8_t)0x40)
#define FS_32000_HZ ((uint8_t)0x18)
#define FS_48000_HZ ((uint8_t)0x00)
#define FS_96000_HZ ((uint8_t)0x1C)

/**
 * @brief Inicializa el periférico I2S.
 * @param fs Frecuencia de muestreo. Utilizar las constantes FS_xxx_HZ.
 */
void I2S_init(char fs);

/**
 * @brief Recibe un dato desde el periférico I2S.
 * @return Dato recibido de 32 bits.
 */
uint32_t I2S_rx(void);

/**
 * @brief Transmite un dato a través del periférico I2S.
 * @param c Dato de 32 bits a transmitir.
 */
void I2S_tx(uint32_t c);

/**
 * @brief Inicia la transmisión/recepción en el periférico I2S.
 */
void I2S_start(void);

/**
 * @brief Indica si el buffer de transmisión está libre.
 * @return 1 si el buffer está libre, 0 en caso contrario.
 */
uint8_t I2S_isTxBufferFree(void);

/**
 * @brief Indica si el buffer de recepción no está vacío.
 * Comprueba si el buffer FIFO de recepción contiene datos disponibles para leer.
 * @return 1 si el buffer contiene datos, 0 si está vacío.
 */
uint8_t I2S_isRxBufferNotEmpty(void);

#endif
