/**
 * @file FM4_WM8731.c
 * @date 2025/10/23
 * @brief Driver para el códec de audio WM8731 en placa FM4.
 *
 * Este módulo proporciona funciones para inicializar y controlar el códec
 * de audio WM8731 mediante I2C (configuración) e I2S (datos de audio).
 */

#include <stdint.h>
#include "mcu.h"
#include "FM4_WM8731.h"
#include "HAL_FM4_i2c.h"
#include "HAL_FM4_i2s.h"

/**
 * @brief Retardo por software.
 * @param nCount Número de iteraciones del bucle de retardo.
 */
static void DonaldDelay(volatile uint32_t nCount)
{
    for (; nCount > 0; nCount--)
        ;
}

/**
 * @brief Escribe un valor en un registro del códec WM8731.
 * @param RegisterAddr Dirección del registro (0-15).
 * @param RegisterValue Valor a escribir en el registro.
 */
static void Codec_WriteRegister(uint8_t RegisterAddr, uint8_t RegisterValue)
{
    I2C_write(WM8731_I2C_ADDRESS, ((RegisterAddr << 1) & 0xFF), ((RegisterValue)&0xFF));
}

/**
 * @brief Inicializa el códec WM8731 y el periférico I2S.
 * @param fs Frecuencia de muestreo (según registros del WM8731).
 * @param select_input Selección de entrada (LINE_IN o MIC).
 * @param hp_out_gain Ganancia de salida de auriculares.
 * @param line_in_gain Ganancia de entrada de línea.
 */
void FM4_WM8731_init(uint8_t fs, uint8_t select_input, uint8_t hp_out_gain, uint8_t line_in_gain)
{
    I2C_init();                                              // initialise I2C peripheral
    DonaldDelay(1000);                                       // before writing to codec registers
    Codec_WriteRegister(WM8731_RESET, 0x00);                 // reset codec
    Codec_WriteRegister(WM8731_LINE_IN_LEFT, line_in_gain);  // set left line in gain
    Codec_WriteRegister(WM8731_LINE_IN_RIGHT, line_in_gain); // set right line in gain
    Codec_WriteRegister(WM8731_HP_OUT_LEFT, hp_out_gain);    // set left headphone out gain
    Codec_WriteRegister(WM8731_HP_OUT_RIGHT, hp_out_gain);   // set right headphone out gain
    Codec_WriteRegister(WM8731_ANALOG_PATH, select_input);   // select line in or microphone input
    Codec_WriteRegister(WM8731_DIGITAL_PATH, 0x00);          // can select de-emphasis, HPF and mute here
    Codec_WriteRegister(WM8731_POWER_DOWN, 0x00);            // disable power down on all parts of codec
    Codec_WriteRegister(WM8731_INTERFACE, 0x53);             // select digital audio interface (I2S) format
    Codec_WriteRegister(WM8731_SAMPLING_RATE, fs);           // sample rate control
    Codec_WriteRegister(WM8731_CONTROL, 0x01);               // activate codec

    I2S_init(fs);
    FM4_I2S0->OPRREG_f.RXENB = 1;
    FM4_I2S0->CNTREG_f.RXDIS = 0;
    FM4_I2S0->OPRREG_f.TXENB = 1;
    FM4_I2S0->CNTREG_f.TXDIS = 0;
    FM4_I2S0->INTCNT_f.RFTH = 0x0F & (0x00);
    FM4_I2S0->INTCNT_f.TFTH = 0x0F & (0x00);
}

/**
 * @brief Escribe una muestra estéreo al códec WM8731 vía I2S.
 * @param datoL Muestra del canal izquierdo (16 bits con signo).
 * @param datoR Muestra del canal derecho (16 bits con signo).
 */
void FM4_WM8731_wr(int16_t datoL, int16_t datoR)
{
    WM8731_data_t dato;
    dato.uint16bit[LEFT]=datoL;
    dato.uint16bit[RIGHT]=datoR;
    I2S_tx(dato.uint32bit);
}

/**
 * @brief Lee una muestra estéreo del códec WM8731 vía I2S.
 * @param datoL Puntero donde se almacena la muestra del canal izquierdo.
 * @param datoR Puntero donde se almacena la muestra del canal derecho.
 */
void FM4_WM8731_rd(int16_t *datoL, int16_t *datoR)
{
    WM8731_data_t dato;
    dato.uint32bit=I2S_rx();
    *datoL=dato.uint16bit[LEFT];
    *datoR=dato.uint16bit[RIGHT];
}
