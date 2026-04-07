#ifndef TIMER0_H
#define TIMER0_H

#include "../../SERVICES/STD_TYPES.h"

/* Clock Source */
#define TIMER0_INTERNAL_CLK   0
#define TIMER0_EXTERNAL_CLK   1

/* Prescaler */
#define TIMER0_PRESCALER_2     0
#define TIMER0_PRESCALER_4     1
#define TIMER0_PRESCALER_8     2
#define TIMER0_PRESCALER_16    3
#define TIMER0_PRESCALER_32    4
#define TIMER0_PRESCALER_64    5
#define TIMER0_PRESCALER_128   6
#define TIMER0_PRESCALER_256   7

/* APIs */
void TIMER0_Init(u8 clk_source, u8 prescaler);
void TIMER0_SetPreload(u8 value);
void TIMER0_SetCallback(void (*ptr)(void));


#endif