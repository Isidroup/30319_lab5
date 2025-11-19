/**
 * @file HAL_FM4_i2c.h
 * @brief Interfaz HAL para bus I2C (FM4 MFS2).
 *
 * @details
 * Prototipos para:
 *  - Inicialización del periférico I2C en modo maestro.
 *  - Escritura de un byte en un registro de un dispositivo esclavo.
 *
 * Notas:
 *  - API bloqueante, sin gestión de NACK ni temporizadores (timeout).
 *  - Velocidad objetivo: 400 kbit/s (según configuración en la implementación).
 */

#ifndef __HAL_FM4_I2C__
#define __HAL_FM4_I2C__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inicializa el periférico I2C (MFS2) y configura los pines SDA/SCL.
 * @pre Debe llamarse una vez antes de cualquier transferencia I2C.
 * @post Bus I2C listo para operar en modo maestro.
 */
void I2C_init(void);

/**
 * @brief Escribe un byte en un registro de un dispositivo I2C.
 *
 * Transacción realizada:
 *  [START] [ADDR | W] [REGISTER] [DATA] [STOP]
 *
 * @param device_address Dirección de 7 bits del esclavo (sin el bit R/W).
 * @param register_address Dirección del registro interno del dispositivo.
 * @param cmd Byte de datos a escribir.
 *
 * @pre Haber llamado previamente a I2C_init().
 * @note Función bloqueante sin comprobación de NACK ni timeout.
 */
void I2C_write(uint8_t device_address, uint8_t register_address, uint8_t cmd);

#ifdef __cplusplus
}
#endif

#endif /* __HAL_FM4_I2C__ */
