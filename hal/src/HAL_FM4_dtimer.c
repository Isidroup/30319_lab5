
#include "stdint.h"
#include "HAL_FM4_dtimer.h"

void delay_us (uint32_t us)
{
    // Number of ticks per microsecond
    uint32_t ticks = (SystemCoreClock / 2000000) * us;
    FM4_DTIM[DTIM_delay].TIMERXLOAD = ticks - 1;
    FM4_DTIM[DTIM_delay].TIMERXBGLOAD = ticks - 1;

    // Habilitacion del timer, noInt, 32bits, one-shot,
    FM4_DTIM[DTIM_delay].TIMERXCONTROL = (1<<7)|(1<<1)|(1<<0);

    // Espera fin de la cuenta
    while(FM4_DTIM[DTIM_delay].TIMERXRIS == 0)
    {
        // Empty loop
    }

    // Limpia interrupciones y detiene el timer
    FM4_DTIM[DTIM_delay].TIMERXINTCLR = 0xFE05;
    FM4_DTIM[DTIM_delay].TIMERXCONTROL = 0x20; //Reset value
}

void delay_ms (uint32_t ms)
{
    // Number of ticks per microsecond
    uint32_t ticks = (SystemCoreClock / 2000) * ms;
    FM4_DTIM[DTIM_delay].TIMERXLOAD = ticks - 1;
    FM4_DTIM[DTIM_delay].TIMERXBGLOAD = ticks - 1;

    // Habilitacion del timer, noInt, 32bits, one-shot,
    FM4_DTIM[DTIM_delay].TIMERXCONTROL = (1<<7)|(1<<1)|(1<<0);

    // Espera fin de la cuenta
    while(FM4_DTIM[DTIM_delay].TIMERXRIS == 0)
    {
        // Empty loop
    }

    // Limpia interrupciones y detiene el timer
    FM4_DTIM[DTIM_delay].TIMERXINTCLR = 0xFE05;
    FM4_DTIM[DTIM_delay].TIMERXCONTROL = 0x20; //Reset value
}
