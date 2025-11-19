/**
 * @file HAL_FM4_i2c.c
 * @brief Capa HAL para interfaz I2C sobre FM4 (MFS2).
 *
 * @details
 * Proporciona:
 *  - Inicialización del bus I2C en modo maestro.
 *  - Escritura de un byte en un registro de un dispositivo esclavo.
 *
 * Características:
 *  - Implementación bloqueante.
 *  - Sin gestión de errores (NACK) ni temporizadores (timeout).
 *  - Velocidad objetivo: 400 kbit/s con reloj de sistema de 100 MHz.
 *
 * Configuración de pines:
 *  - SCK: P3B (SCK2B1).
 *  - SDA: P3A (SOT2B1) en pseudo open-drain.
 *
 * @pre Llamar a I2C_init() antes de realizar transferencias.
 * @note Requiere resistencias de pull-up en SDA y SCL a nivel de placa.
 */

#include "mcu.h"
#include "HAL_FM4_i2c.h"

/**
 * @brief Retardo por espera activa.
 *
 * @param nCount Número de iteraciones del bucle (dependiente de la frecuencia de CPU).
 *
 * @warning Precisión no garantizada; no usar para temporización crítica.
 * @note Función interna de ayuda para espaciar eventos del bus.
 */
static void DonaldDelay( volatile uint32_t nCount)
{
  for (; nCount > 0; nCount--);
}

/**
 * @brief Inicializa el periférico MFS2 en modo I2C a 400 kbit/s.
 *
 * Configura la multiplexación de pines para SCL y SDA, establece SDA en
 * pseudo open-drain, ajusta el baud rate e inicializa el periférico.
 *
 * @post Bus I2C listo para iniciar transferencias en modo maestro.
 */
void I2C_init(void)
{
  bFM4_GPIO_EPFR07_SCK2B1 = 1u;                  // GPIO pin P3B used for I2C clock
  bFM4_GPIO_PFR3_PB = 1u;
  bFM4_GPIO_EPFR07_SOT2B1 = 1u;                  // GPIO pin P3A used for I2C data
  bFM4_GPIO_PFR3_PA = 1u;
  FM4_GPIO->PZR3_f.PA = 1u;                      // I2C data pin pseudo open drain
  FM4_MFS2->BGR  = 100000000ul / 400000ul - 1ul; // I2C mode 400k Bit/s @ 100 MHz
  FM4_MFS2->SMR |= 0x80u;                        // operate MFS2 in mode 4 (I2C)
  bFM4_MFS2_I2C_SMR_RIE = 0u;                    // disable receive interrupts
  bFM4_MFS2_I2C_SMR_TIE = 0u;                    // disable transmit interrupts
  FM4_MFS2->SCR |= 0x80u;                        // reset MFS2 (UPCL = 1)
}

/**
 * @brief Escribe un byte en un registro de un dispositivo I2C.
 *
 * Realiza la transacción:
 *  [START] [ADDR | W] [REGISTER] [DATA] [STOP]
 *
 * @param device_address Dirección de 7 bits del dispositivo (sin el bit R/W).
 * @param register_address Dirección del registro interno del dispositivo.
 * @param cmd Byte de datos a escribir en el registro.
 *
 * @pre Haber llamado previamente a I2C_init().
 * @note Función bloqueante sin comprobación de NACK ni timeout.
 */
void I2C_write(uint8_t device_address, uint8_t register_address, uint8_t cmd)
{
  FM4_MFS2->ISBA = 0x00u;                        // disable slave address detection
  FM4_MFS2->ISMK = 0x00;                         // clear slave mask
  bFM4_MFS2_I2C_ISMK_EN = 0x01;
  FM4_MFS2->TDR = (device_address << 1)|0x00;    // load codec device address into transmit data register
  FM4_MFS2->IBCR = 0x80u;                        // select master mode
  while(!(bFM4_MFS2_I2C_IBCR_INT)) {}            // wait for interrupt flag, i.e. transmission complete
  FM4_MFS2->TDR = (register_address);            // load codec register address into transmit data register
  bFM4_MFS2_I2C_IBCR_ACKE = 1u;                  // enable acknowledgment
  bFM4_MFS2_I2C_IBCR_WSEL = 1u;                  // set wait selection bit
  bFM4_MFS2_I2C_IBCR_INT = 0u;                   // clear interrupt flag
  while(!(FM4_MFS2->IBCR & 0x01u)) {}            // wait for interrupt flag, i.e. transmission complete
  FM4_MFS2->TDR = (cmd);                         // load codec register command into transmit data register
  bFM4_MFS2_I2C_IBCR_ACKE = 1u;                  // enable acknowledgment
  bFM4_MFS2_I2C_IBCR_WSEL = 1u;                  // set wait selection bit
  bFM4_MFS2_I2C_IBCR_INT = 0u;                   // clear interrupt flag
  while(!(FM4_MFS2->IBCR & 0x01u)) {}            // wait for interrupt flag, i.e. transmission complete
  FM4_MFS2->IBCR = 0x20u;                        // enable acknowledge
  DonaldDelay(10000);                            // delay
}
