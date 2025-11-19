/**
 * @file HAL_FM4_gpio.h
 * @brief Cypress FM4 Funciones para acceder a los GPIO
 *
 * @details Este archivo contiene las definiciones y prototipos de funciones
 * para manipular los pines GPIO del microcontrolador Cypress FM4:
 *      - GPIO_ChannelRead
 *      - GPIO_ChannelWrite
 *      - GPIO_ChannelToggle
 *      - GPIO_ChannelMode
 *      - GPIO_ChannelDigAna
 *
 * @author Universidad de Zaragoza
 * @date 2025/07/09
 */

/**
 * @note Arduino chipkit pinout reference
 * @verbatim
 *                                    +-----+
 *         +----[PWR]-------------------| USB |----+
 *         |                            +-----+    |
 *         |         GND/RST2  [ ][ ]              |
 *         |       MOSI2/SCK2  [ ][ ]  A5/SCL[   ] |   C5
 *         |          5V/MISO2 [ ][ ]  A4/SDA[   ] |   C4
 *         |                             AREF[   ] |
 *         |                              GND[   ] |
 *         | [ ]N/C                    SCK/13[   ] |   B5
 *         | [ ]IOREF                 MISO/12[P40] |   .           // CN7
 *         | [ ]RST                   MOSI/11[P41]~|   .           // CN7
 *         | [ ]3V3    +---+               10[PF0]~|   .           // CN7
 *         | [ ]5v    -| A |-               9[PF1]~|   .           // CN7
 *         | [ ]GND   -| R |-               8[P7D] |   B0          // CN7
 *         | [ ]GND   -| D |-                      |
 *         | [ ]Vin   -| U |-               7[PF3] |   D7          // CN9
 *         |          -| I |-               6[P45]~|   .           // CN9
 *         | [ ]A0    -| N |-               5[P44]~|   .           // CN9
 *         | [ ]A1    -| O |-               4[PF4] |   .           // CN9
 *         | [ ]A2     +---+           INT1/3[P43]~|   .           // CN9
 *         | [ ]A3                     INT0/2[PF7] |   .           // CN9
 *         | [ ]A4/SDA  RST SCK MISO     TX>1[P1C] |   .   analog  // CN9
 *         | [ ]A5/SCL  [ ] [ ] [ ]      RX<0[P1B] |   D0  analog  // CN9
 *         |            [ ] [ ] [ ]                |
 *         |  UNO_R3    GND MOSI 5V  ______________/
 *          \_______________________/
 * @endverbatim
 */

#ifndef INCLUDES_HAL_FM4_GPIO_H_
#define INCLUDES_HAL_FM4_GPIO_H_

/**
 * @defgroup gpio_types Tipos de datos GPIO
 * @{
 */

/**
 * @brief Estados posibles para un pin digital de salida
 */
typedef enum GpioPinState_enu
{
  GPIO_LOW,  /**< Estado digital bajo (0V) */
  GPIO_HIGH, /**< Estado digital alto (3.3V) */
  GPIO_PIN_STATE_MAX /**< Valor máximo para el estado digital */
}GpioPinState_t;

/**
 * @brief Lista enumerada de todos los canales (pines) en el microcontrolador
 *
 * @details El valor de cada símbolo corresponde con el número de puerto (MSB),
 * y el canal (LSB). Formato: 0xPO, donde P es el puerto y O es el canal.
 */
typedef enum GpioChannel_enu
{
  P00 = 0x00,    /**< Puerto:0, Canal:0 */
  P01 = 0x01,    /**< Puerto:0, Canal:1 */
  P02 = 0x02,    /**< Puerto:0, Canal:2 */
  P03 = 0x03,    /**< Puerto:0, Canal:3 */
  P04 = 0x04,    /**< Puerto:0, Canal:4 */
  P08 = 0x08,    /**< Puerto:0, Canal:8 */
  P09 = 0x09,    /**< Puerto:0, Canal:9 */
  P0A = 0x0A,    /**< Puerto:0, Canal:A */
  P10 = 0x10,    /**< Puerto:1, Canal:0 */
  P11 = 0x11,    /**< Puerto:1, Canal:1 */
  P12 = 0x12,    /**< Puerto:1, Canal:2 */
  P13 = 0x13,    /**< Puerto:1, Canal:3 */
  P14 = 0x14,    /**< Puerto:1, Canal:4 */
  P15 = 0x15,    /**< Puerto:1, Canal:5 */
  P16 = 0x16,    /**< Puerto:1, Canal:6 */
  P17 = 0x17,    /**< Puerto:1, Canal:7 */
  P18 = 0x18,    /**< Puerto:1, Canal:8 */
  P19 = 0x19,    /**< Puerto:1, Canal:9 */
  P1A = 0x1A,    /**< Puerto:1, Canal:A */
  P1B = 0x1B,    /**< Puerto:1, Canal:B */
  P1C = 0x1C,    /**< Puerto:1, Canal:C */
  P1D = 0x1D,    /**< Puerto:1, Canal:D */
  P1E = 0x1E,    /**< Puerto:1, Canal:E */
  P1F = 0x1F,    /**< Puerto:1, Canal:F */
  P20 = 0x20,    /**< Puerto:2, Canal:0 */
  P21 = 0x21,    /**< Puerto:2, Canal:1 */
  P22 = 0x22,    /**< Puerto:2, Canal:2 */
  P23 = 0x23,    /**< Puerto:2, Canal:3 */
  P24 = 0x24,    /**< Puerto:2, Canal:4 */
  P25 = 0x25,    /**< Puerto:2, Canal:5 */
  P26 = 0x26,    /**< Puerto:2, Canal:6 */
  P27 = 0x27,    /**< Puerto:2, Canal:7 */
  P28 = 0x28,    /**< Puerto:2, Canal:8 */
  P29 = 0x29,    /**< Puerto:2, Canal:9 */
  P2A = 0x2A,    /**< Puerto:2, Canal:A */
  P30 = 0x30,    /**< Puerto:3, Canal:0 */
  P31 = 0x31,    /**< Puerto:3, Canal:1 */
  P32 = 0x32,    /**< Puerto:3, Canal:2 */
  P33 = 0x33,    /**< Puerto:3, Canal:3 */
  P34 = 0x34,    /**< Puerto:3, Canal:4 */
  P35 = 0x35,    /**< Puerto:3, Canal:5 */
  P36 = 0x36,    /**< Puerto:3, Canal:6 */
  P37 = 0x37,    /**< Puerto:3, Canal:7 */
  P38 = 0x38,    /**< Puerto:3, Canal:8 */
  P39 = 0x39,    /**< Puerto:3, Canal:9 */
  P3A = 0x3A,    /**< Puerto:3, Canal:A */
  P3B = 0x3B,    /**< Puerto:3, Canal:B */
  P3C = 0x3C,    /**< Puerto:3, Canal:C */
  P3D = 0x3D,    /**< Puerto:3, Canal:D */
  P3E = 0x3E,    /**< Puerto:3, Canal:E */
  P40 = 0x40,    /**< Puerto:4, Canal:0 */
  P41 = 0x41,    /**< Puerto:4, Canal:1 */
  P42 = 0x42,    /**< Puerto:4, Canal:2 */
  P43 = 0x43,    /**< Puerto:4, Canal:3 */
  P44 = 0x44,    /**< Puerto:4, Canal:4 */
  P45 = 0x45,    /**< Puerto:4, Canal:5 */
  P46 = 0x46,    /**< Puerto:4, Canal:6 */
  P47 = 0x47,    /**< Puerto:4, Canal:7 */
  P48 = 0x48,    /**< Puerto:4, Canal:8 */
  P49 = 0x49,    /**< Puerto:4, Canal:9 */
  P50 = 0x50,    /**< Puerto:5, Canal:0 */
  P51 = 0x51,    /**< Puerto:5, Canal:1 */
  P52 = 0x52,    /**< Puerto:5, Canal:2 */
  P5D = 0x5D,    /**< Puerto:5, Canal:D */
  P5E = 0x5E,    /**< Puerto:5, Canal:E */
  P5F = 0x5F,    /**< Puerto:5, Canal:F */
  P60 = 0x60,    /**< Puerto:6, Canal:0 */
  P61 = 0x61,    /**< Puerto:6, Canal:1 */
  P62 = 0x62,    /**< Puerto:6, Canal:2 */
  P63 = 0x63,    /**< Puerto:6, Canal:3 */
  P64 = 0x64,    /**< Puerto:6, Canal:4 */
  P65 = 0x65,    /**< Puerto:6, Canal:5 */
  P6E = 0x6E,    /**< Puerto:6, Canal:E */
  P70 = 0x70,    /**< Puerto:7, Canal:0 */
  P71 = 0x71,    /**< Puerto:7, Canal:1 */
  P72 = 0x72,    /**< Puerto:7, Canal:2 */
  P73 = 0x73,    /**< Puerto:7, Canal:3 */
  P74 = 0x74,    /**< Puerto:7, Canal:4 */
  P75 = 0x75,    /**< Puerto:7, Canal:5 */
  P76 = 0x76,    /**< Puerto:7, Canal:6 */
  P77 = 0x77,    /**< Puerto:7, Canal:7 */
  P78 = 0x78,    /**< Puerto:7, Canal:8 */
  P79 = 0x79,    /**< Puerto:7, Canal:9 */
  P7A = 0x7A,    /**< Puerto:7, Canal:A */
  P7B = 0x7B,    /**< Puerto:7, Canal:B */
  P7C = 0x7C,    /**< Puerto:7, Canal:C */
  P7D = 0x7D,    /**< Puerto:7, Canal:D */
  P7E = 0x7E,    /**< Puerto:7, Canal:E */
  P80 = 0x80,    /**< Puerto:8, Canal:0 */
  P81 = 0x81,    /**< Puerto:8, Canal:1 */
  P82 = 0x82,    /**< Puerto:8, Canal:2 */
  P83 = 0x83,    /**< Puerto:8, Canal:3 */
  P90 = 0x90,    /**< Puerto:9, Canal:0 */
  P91 = 0x91,    /**< Puerto:9, Canal:1 */
  P92 = 0x92,    /**< Puerto:9, Canal:2 */
  P93 = 0x93,    /**< Puerto:9, Canal:3 */
  P94 = 0x94,    /**< Puerto:9, Canal:4 */
  P95 = 0x95,    /**< Puerto:9, Canal:5 */
  PA0 = 0xA0,    /**< Puerto:A, Canal:0 */
  PA1 = 0xA1,    /**< Puerto:A, Canal:1 */
  PA2 = 0xA2,    /**< Puerto:A, Canal:2 */
  PA3 = 0xA3,    /**< Puerto:A, Canal:3 */
  PA4 = 0xA4,    /**< Puerto:A, Canal:4 */
  PA5 = 0xA5,    /**< Puerto:A, Canal:5 */
  PA6 = 0xA6,    /**< Puerto:A, Canal:6 */
  PA7 = 0xA7,    /**< Puerto:A, Canal:7 */
  PA8 = 0xA8,    /**< Puerto:A, Canal:8 */
  PA9 = 0xA9,    /**< Puerto:A, Canal:9 */
  PAA = 0xAA,    /**< Puerto:A, Canal:A */
  PAB = 0xAB,    /**< Puerto:A, Canal:B */
  PAC = 0xAC,    /**< Puerto:A, Canal:C */
  PAD = 0xAD,    /**< Puerto:A, Canal:D */
  PAE = 0xAE,    /**< Puerto:A, Canal:E */
  PAF = 0xAF,    /**< Puerto:A, Canal:F */
  PB0 = 0xB0,    /**< Puerto:B, Canal:0 */
  PB1 = 0xB1,    /**< Puerto:B, Canal:1 */
  PB2 = 0xB2,    /**< Puerto:B, Canal:2 */
  PB3 = 0xB3,    /**< Puerto:B, Canal:3 */
  PB4 = 0xB4,    /**< Puerto:B, Canal:4 */
  PB5 = 0xB5,    /**< Puerto:B, Canal:5 */
  PB6 = 0xB6,    /**< Puerto:B, Canal:6 */
  PB7 = 0xB7,    /**< Puerto:B, Canal:7 */
  PC0 = 0xC0,    /**< Puerto:C, Canal:0 */
  PC1 = 0xC1,    /**< Puerto:C, Canal:1 */
  PC2 = 0xC2,    /**< Puerto:C, Canal:2 */
  PC3 = 0xC3,    /**< Puerto:C, Canal:3 */
  PC4 = 0xC4,    /**< Puerto:C, Canal:4 */
  PC5 = 0xC5,    /**< Puerto:C, Canal:5 */
  PC6 = 0xC6,    /**< Puerto:C, Canal:6 */
  PC7 = 0xC7,    /**< Puerto:C, Canal:7 */
  PC8 = 0xC8,    /**< Puerto:C, Canal:8 */
  PC9 = 0xC9,    /**< Puerto:C, Canal:9 */
  PCA = 0xCA,    /**< Puerto:C, Canal:A */
  PCB = 0xCB,    /**< Puerto:C, Canal:B */
  PCC = 0xCC,    /**< Puerto:C, Canal:C */
  PCD = 0xCD,    /**< Puerto:C, Canal:D */
  PCE = 0xCE,    /**< Puerto:C, Canal:E */
  PCF = 0xCF,    /**< Puerto:C, Canal:F */
  PD0 = 0xD0,    /**< Puerto:D, Canal:0 */
  PD1 = 0xD1,    /**< Puerto:D, Canal:1 */
  PD2 = 0xD2,    /**< Puerto:D, Canal:2 */
  PE0 = 0xE0,    /**< Puerto:E, Canal:0 */
  PE2 = 0xE2,    /**< Puerto:E, Canal:2 */
  PE3 = 0xE3,    /**< Puerto:E, Canal:3 */
  PF0 = 0xF0,    /**< Puerto:F, Canal:0 */
  PF1 = 0xF1,    /**< Puerto:F, Canal:1 */
  PF2 = 0xF2,    /**< Puerto:F, Canal:2 */
  PF3 = 0xF3,    /**< Puerto:F, Canal:3 */
  PF4 = 0xF4,    /**< Puerto:F, Canal:4 */
  PF5 = 0xF5,    /**< Puerto:F, Canal:5 */
  PF6 = 0xF6,    /**< Puerto:F, Canal:6 */
  PF7 = 0xF7,    /**< Puerto:F, Canal:7 */
  MAXCHANNEL = 0x100
} GpioChannel_t; /**< Identificador de canal GPIO */


/**
 * @brief Modos posibles de configuración para un canal (entrada/salida)
 */
typedef enum GpioDir_enu
{
  GPIO_INPUT,  /**< Configura el canal como entrada */
  GPIO_OUTPUT, /**< Configura el canal como salida */
} GpioDir_t;

/**
 * @brief Configuración de un GPIO como analógico o digital
 */
typedef enum GpioDigAna_enu
{
  GPIO_DIG,  /**< Configura el canal como digital */
  GPIO_ANA,  /**< Configura el canal como analógico */
} GpioDigAna_t;

/**
 * @brief Estados posibles para las resistencias de pull-up internas
 */
typedef enum GpioResistor_enu
{
  GPIO_PULLUP_DISABLED, /**< Desactiva las resistencias pull-up internas */
  GPIO_PULLUP_ENABLED,  /**< Activa las resistencias pull-up internas */
  GPIO_MAX_RESISTOR     /**< Valor máximo para los estados de resistencia */
} GpioResistor_t;

/** @} */

/**
 * @defgroup gpio_functions Funciones GPIO
 * @{
 */

/**
 * @brief Configura un pin GPIO como analógico o digital
 *
 * @param[in] channel Canal GPIO a configurar
 * @param[in] mode Modo del canal (GPIO_DIG/GPIO_ANA)
 *
 * @return void
 */
void GPIO_ChannelDigAna(const GpioChannel_t channel, const GpioDigAna_t mode);

/**
 * @brief Configura un pin GPIO como entrada o salida
 *
 * @param[in] channel Canal GPIO a configurar
 * @param[in] mode Modo del canal (GPIO_INPUT/GPIO_OUTPUT)
 *
 * @return void
 */
void GPIO_ChannelMode(const GpioChannel_t channel, const GpioDir_t mode);

/**
 * @brief Lee el estado de un pin GPIO
 *
 * @param[in] channel Canal GPIO a leer
 *
 * @pre El canal debe estar configurado previamente
 *
 * @return GpioPinState_t Estado lógico del canal (GPIO_LOW o GPIO_HIGH)
 */
GpioPinState_t GPIO_ChannelRead(const GpioChannel_t channel);

/**
 * @brief Escribe un valor en un pin GPIO
 *
 * @param[in] channel Canal GPIO a escribir
 * @param[in] pin Valor lógico a escribir (GPIO_LOW o GPIO_HIGH)
 *
 * @pre El canal debe estar configurado como salida
 *
 * @return void
 */
void GPIO_ChannelWrite(const GpioChannel_t channel, const GpioPinState_t pin);


/**
 * @brief Invierte el estado actual de un pin GPIO
 *
 * @param[in] channel Canal GPIO a modificar
 *
 * @pre El canal debe estar configurado como salida
 *
 * @return void
 */
void GPIO_ChannelToggle(const GpioChannel_t channel);

/** @} */

#endif /* INCLUDES_HAL_FM4_GPIO_H_*/
