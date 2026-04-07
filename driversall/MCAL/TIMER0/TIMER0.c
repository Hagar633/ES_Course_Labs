#include "../../SERVICES/BIT_MATH.h"
#include "../../SERVICES/STD_TYPES.h"
#include "TIMER0.h"

static void (*Timer0_Callback)(void) = 0;

void TIMER0_Init(u8 clk_source, u8 prescaler)
{
    T0CS_bit = clk_source;   // clock source
    PSA_bit  = 0;            // prescaler assigned to timer

    // Set prescaler bits manually
    PS0_bit = (prescaler >> 0) & 1;
    PS1_bit = (prescaler >> 1) & 1;
    PS2_bit = (prescaler >> 2) & 1;

    TMR0 = 0;

    T0IE_bit = 1;   // enable Timer0 interrupt
    T0IF_bit = 0;
    GIE_bit  = 1;   // global interrupt
}


void TIMER0_SetPreload(u8 value)
{
    TMR0 = value;
}

void TIMER0_SetCallback(void (*ptr)(void))
{
    Timer0_Callback = ptr;
}

/* ISR */
void interrupt()
{
    if (T0IF_bit)
    {
        T0IF_bit = 0;

        if (Timer0_Callback != 0)
        {
            Timer0_Callback();
        }
    }
}
