/**
 * FM4_leds_sw.c
 * Cypress FM4 Funciones para acceder a los leds y al pulsador
 *  Created on: 13 jul. 2017
 *  Last modified: 2025/07/23 11:41:26
 *  @todo reescribir comentarios en doxygen
 */


#include <assert.h>
#include "mcu.h"
#include "HAL_FM4_gpio.h"
#include "FM4_leds_sw.h"


/*------------------------------------------------- LedSwsInit -----
 *
 * Funcion: LedsSwInit(void)
 *
 * Proposito:  Esta funcion configura los GPIOs P18, PB2, P1A como salida,
 *             y escribe un '1' en todos ellos (leds apagados).
 *             También configura GPIO P20 como entrada (sw2)
 *
 * Parametros: void
 *
 * Returns:    void
 *
 *-------------------------------------------------------------------*/

 void LedsSwInit()
 {
    // FM4 - Pioneeer
    // P18 LED RGB(Azul)
    bFM4_GPIO_ADE_AN08 = 0; // Pin digital
    bFM4_GPIO_PFR1_P8 = 0;  // GPIO
    bFM4_GPIO_PDOR1_P8 = 0; // Salida=0 (Encendido)
    bFM4_GPIO_DDR1_P8 = 1;  // Salida

    // PB2 LED RGB(Verde)
    bFM4_GPIO_ADE_AN18 = 0; // Pin digital
    bFM4_GPIO_PFRB_P2 = 0;  // GPIO
    bFM4_GPIO_PDORB_P2 = 0; // Salida=0 (Encendido)
    bFM4_GPIO_DDRB_P2 = 1;  // Salida

    // P1A LED RGB(Rojo)
    bFM4_GPIO_ADE_AN10 = 0; // Pin digital
    bFM4_GPIO_PFR1_PA = 0;  // GPIO
    bFM4_GPIO_PDOR1_PA = 0; // Salida=0 (Encendido)
    bFM4_GPIO_DDR1_PA = 1;  // Salida

    // P6E LED Ethernet
    bFM4_GPIO_PFR6_PE = 0;  // GPIO
    bFM4_GPIO_PDOR6_PE = 0; // Salida=0 (Encendido)
    bFM4_GPIO_DDR6_PE = 1;  // Salida

    // P20 SW2
    bFM4_GPIO_PFR2_P0 = 0;   // GPIO
    bFM4_GPIO_DDR2_P0 = 0;   // Entrada
    bFM4_GPIO_PDOR6_PE =  !bFM4_GPIO_PDIR2_P0 ;

     // Leds apagados
    GPIO_ChannelWrite(P18,LED_OFF);  // Azul
    GPIO_ChannelWrite(PB2,LED_OFF);  // Verde
    GPIO_ChannelWrite(P1A,LED_OFF);  // Rojo
    GPIO_ChannelWrite(P6E,LED_OFF);  // Ethernet
 }


/**
 * brief   Esta funcion apaga (OFF) o enciende el led RGB con el color
 *              que se le pasa como argumento
 * param [in]  leds3  (IN): Puede tomar uno de los siguientes valores:
 *                           OFF, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE
 *
 * note    Los 3 bits menos significativos de leds, codifican el estado ON/OFF (1/0)
 *                     de los leds:
 *                           bit->     2     1    0
 *                           led->    ROJO VERDE AZUL
 */
void LedRGB(const rgb_color_t leds3)
{   GpioPinState_t led;

    // Led Azul P18
    led=(leds3&(1<<0))?LED_ON:LED_OFF;
    GPIO_ChannelWrite(P18,led);  // Azul
    // Led Verde PB2
    led=(leds3&(1<<1))?LED_ON:LED_OFF;
    GPIO_ChannelWrite(PB2,led);  // Verde
    // Led Rojo P1A
    led=(leds3&(1<<2))?LED_ON:LED_OFF;
    GPIO_ChannelWrite(P1A,led);  // Rojo
}

/*------------------------------------------------- LedONOFF -----
 *
 * Funcion: LedONOFF (led, encendido)
 *
 * Proposito: Esta funcion controla 1 led (led RGB) de la placa
 *
 * Parametros: led       (IN): Led a controlar (LED_AZUL, LED_VERDE, LED_ROJO, LED_ETH)
 *             encendido (in): 1/0 encendido/apagado del led
 *
 * Returns:    void
 *
 *-------------------------------------------------------------------*/
void LedONOFF(const Leds_t led, const GpioPinState_t encendido)
{
    switch (led){
    // Led Azul P18
        case LED_AZUL : GPIO_ChannelWrite(P18,encendido);  // Azul;
        break;
    // Led Verde PB2
        case LED_VERDE : GPIO_ChannelWrite(PB2,encendido);  // Verde;
        break;
    // Led Rojo P1A
        case LED_ROJO : GPIO_ChannelWrite(P1A,encendido);  // Rojo;
        break;
    // Led Ethernet P6E
        case LED_ETH : GPIO_ChannelWrite(P6E,encendido);  // Eth;
        break;
        default: assert(0);
    }
}

/**
 * @brief Enciende un LED específico
 *
 * @param led LED a encender (LED_AZUL, LED_VERDE, LED_ROJO, LED_ETH)
 *
 * @return void
 */
void LedON(const Leds_t led)
{
    switch (led){
    // Led Azul P18
        case LED_AZUL : GPIO_ChannelWrite(P18, LED_ON);  // Azul;
        break;
    // Led Verde PB2
        case LED_VERDE : GPIO_ChannelWrite(PB2, LED_ON);  // Verde;
        break;
    // Led Rojo P1A
        case LED_ROJO : GPIO_ChannelWrite(P1A, LED_ON);  // Rojo;
        break;
    // Led Ethernet P6E
        case LED_ETH : GPIO_ChannelWrite(P6E, LED_ON);  // Eth;
        break;
        default: assert(0);
    }
}

/**
 * @brief Apaga un LED específico
 *
 * @param led LED a apagar (LED_AZUL, LED_VERDE, LED_ROJO, LED_ETH)
 *
 * @return void
 */
void LedOFF(const Leds_t led)
{
    switch (led){
    // Led Azul P18
        case LED_AZUL : GPIO_ChannelWrite(P18, LED_OFF);  // Azul;
        break;
    // Led Verde PB2
        case LED_VERDE : GPIO_ChannelWrite(PB2, LED_OFF);  // Verde;
        break;
    // Led Rojo P1A
        case LED_ROJO : GPIO_ChannelWrite(P1A, LED_OFF);  // Rojo;
        break;
    // Led Ethernet P6E
        case LED_ETH : GPIO_ChannelWrite(P6E, LED_OFF);  // Eth;
        break;
        default: assert(0);
    }
}


void LedToggle(const Leds_t led)
{
    switch (led){
    // Led Azul P18
        case LED_AZUL : GPIO_ChannelToggle(P18);  // Azul;
        break;
    // Led Verde PB2
        case LED_VERDE : GPIO_ChannelToggle(PB2);  // Verde;
        break;
    // Led Rojo P1A
        case LED_ROJO : GPIO_ChannelToggle(P1A);  // Rojo;
        break;
    // Led Ethernet P6E
        case LED_ETH : GPIO_ChannelToggle(P6E);  // Eth;
        break;
        default: assert(0);
    }
}

/**
 * @brief Lee el estado del pulsador SW2
 *
 * @details Esta función lee el estado del pulsador SW2 y devuelve su estado
 *          como un valor booleano (1 si está presionado, 0 si no lo está)
 *
 * @return uint8_t Estado del pulsador: 1 si presionado, 0 si no presionado
 */
uint8_t Sw2Read(void)
{
    // Lee el estado del pulsador SW2 (P20)
    return bFM4_GPIO_PDIR2_P0 ? 0 : 1; // Devuelve 1 si está presionado, 0 si no
}

#define TOP (0x03FF)

void breath_led(const Leds_t led) 
	{
    static uint32_t time_counter = 0;
    static uint16_t pwm_counter = 0;

    time_counter++;
    uint16_t sawtooth = (time_counter >> 10) & TOP;
    uint16_t triangle = (sawtooth < (TOP >> 1)) ? sawtooth : (TOP - sawtooth);
    uint16_t brightness = triangle >> 2;

    LedONOFF(led,(brightness >= pwm_counter) ? LED_ON : LED_OFF);

    pwm_counter = (pwm_counter + 1) & TOP;
}

void breath_rgb(const rgb_color_t color) {
    static uint32_t time_counter = 0;
    static uint16_t pwm_counter = 0;

    time_counter++;
    uint16_t sawtooth = (time_counter >> 10) & TOP;
    uint16_t triangle = (sawtooth < (TOP >> 1)) ? sawtooth : (TOP - sawtooth);
    uint16_t brightness = triangle >> 2;

    LedRGB((brightness >= pwm_counter) ? color : OFF);

    pwm_counter = (pwm_counter + 1) & TOP;
}



