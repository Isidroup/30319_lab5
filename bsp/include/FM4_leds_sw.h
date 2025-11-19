/**
 * @file FM4_leds_sw.h
 * @brief Cypress FM4 Funciones para acceder a los leds y al pulsador
 * @details Este archivo contiene las definiciones y prototipos de funciones
 * para manipular los LEDs RGB y el pulsador SW2 del microcontrolador Cypress FM4
 * @author Universidad de Zaragoza
 * @date 2022/10/10
 */

#ifndef FM4_LEDS_SW_H_
#define FM4_LEDS_SW_H_

#include "HAL_FM4_gpio.h"
#include "stdint.h" /**< Definiciones de tipos enteros con tamaño específico */


/**
 * @defgroup leds_types Tipos de LEDs
 * @{
 */

/**
 * @brief Define los leds disponibles en la placa
 */
typedef enum Leds_enu {
            LED_AZUL=0x18,   /**< Led AZUL  GPIO pin 18  */
            LED_VERDE=0xB2,  /**< Led VERDE GPIO pin B2  */
            LED_ROJO=0x1A,   /**< Led ROJO  GPIO pin 1A  */
            LED_ETH=0x6E,    /**< Led conector Ethernet  */
            MAX_LEDS=4       /**< Número de leds  */
} Leds_t;

/**
 * @brief Define los estados de los LEDs
 */
#define LED_ON  (GPIO_LOW)   /**< LED encendido (nivel bajo) */
#define LED_OFF (GPIO_HIGH)  /**< LED apagado (nivel alto) */

/**
 * @brief Define los colores RGB disponibles
 *
 * @details Los 3 bits menos significativos de cada valor codifican el estado ON/OFF (1/0)
 *          de los leds:
 *          - bit 2: LED ROJO
 *          - bit 1: LED VERDE
 *          - bit 0: LED AZUL
 */
typedef enum rgb_color {
            OFF=0,     /**< Apagado  */
            BLUE=1,    /**< Azul */
            GREEN=2,   /**< Verde  */
            CYAN=3,    /**< Cian */
            RED=4,     /**< Rojo  */
            MAGENTA=5, /**< Magenta */
            YELLOW=6,  /**< Amarillo */
            WHITE=7,   /**< Blanco */
            MAX_COLORS=8   /**< Número de colores  */
} rgb_color_t;

/** @} */ /* end of leds_types group */

/**
 * @defgroup leds_functions Funciones de manejo de LEDs y pulsadores
 * @{
 */

/**
 * @brief Inicializa los LEDs y pulsadores
 *
 * @details Esta función configura los GPIOs P18, PB2, P1A como salida,
 *          y escribe un '1' en todos ellos (leds apagados).
 *          También configura GPIO P20 como entrada (sw2)
 *
 * @return void
 */
void LedsSwInit(void);

/**
 * @brief Controla el LED RGB con un color específico
 *
 * @details Esta función apaga (OFF) o enciende el LED RGB con el color
 *          que se le pasa como argumento
 *
 * @param[in] leds3 Color a establecer en el LED RGB: OFF, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE
 *
 * @note Los 3 bits menos significativos de leds, codifican el estado ON/OFF (1/0)
 *       de los leds:
 *       - bit 2: LED ROJO
 *       - bit 1: LED VERDE
 *       - bit 0: LED AZUL
 *
 * @return void
 */
void LedRGB(const rgb_color_t leds3);

/**
 * @brief Controla un LED específico
 *
 * @details Esta función controla un LED individual de la placa
 *
 * @param[in] led LED a controlar: LED_AZUL, LED_VERDE, LED_ROJO, LED_ETH
 * @param[in] encendido Estado del LED: LED_ON para encender, LED_OFF para apagar
 *
 * @return void
 */
void LedONOFF(const Leds_t led, const GpioPinState_t encendido);

/**
 * @brief Enciende un LED específico
 *
 * @param led LED a encender: LED_AZUL, LED_VERDE, LED_ROJO, LED_ETH
 *
 * @return void
 */
void LedON(const Leds_t led);

/**
 * @brief Apaga un LED específico
 *
 * @param led LED a apagar: LED_AZUL, LED_VERDE, LED_ROJO, LED_ETH
 *
 * @return void
 */
void LedOFF(const Leds_t led);

/**
 * @brief Invierte el estado actual de un LED específico
 *
 * @details Esta función cambia el estado de un LED individual de la placa,
 *          si estaba encendido lo apaga y si estaba apagado lo enciende.
 *          La operación se realiza de forma atómica usando GPIO_ChannelToggle.
 *
 * @param[in] led LED a invertir: LED_AZUL, LED_VERDE, LED_ROJO, LED_ETH
 *
 * @pre El LED debe estar configurado previamente con LedsSwInit()
 *
 * @return void
 *
 * @note Esta función utiliza un switch para seleccionar el pin GPIO correcto
 *       según el LED especificado
 *
 * @see LedsSwInit()
 * @see GPIO_ChannelToggle()
 */
void LedToggle(const Leds_t led);

/**
 * @brief Lee el estado del pulsador SW2
 *
 * @details Esta función lee el estado del pulsador SW2 y devuelve su estado
 *          como un valor booleano (1 si está presionado, 0 si no lo está)
 *
 * @return uint8_t Estado del pulsador: 1 si presionado, 0 si no presionado
 */
uint8_t Sw2Read(void);

/** @} */ /* end of leds_functions group */



/**
 * @brief Controla un LED específico con un efecto de respiración
 *
 * @details Esta función implementa un efecto de respiración en el LED especificado,
 *          haciendo que el LED se encienda y apague suavemente.
 *
 * @param led LED a controlar: LED_AZUL, LED_VERDE, LED_ROJO, LED_ETH
 *
 * @return void
 */
void breath_led(const Leds_t led);

/**
 * @brief Controla un LED RGB específico con un efecto de respiración
 *
 * @details Esta función implementa un efecto de respiración en el LED RGB especificado,
 *          haciendo que el LED cambie su intensidad suavemente.
 *
 * @param color Color del LED RGB a controlar: OFF, BLUE, GREEN, CYAN, RED, MAGENTA, YELLOW, WHITE
 *
 * @return void
 */
void breath_rgb(const rgb_color_t color);

#endif /* LEDS_H_ */
