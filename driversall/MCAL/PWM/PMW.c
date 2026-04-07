#include "../../SERVICES/BIT_MATH.h"
#include "../../SERVICES/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_INTERFACE.h"
#include "PMW.h"

void PWM_Init(void)
{
    // RC2 → CCP1 pin
    GPIO_SetPinDirection(GPIO_PORTC, GPIO_PIN2, GPIO_OUTPUT);

    // Timer2 configuration
    T2CON = 0b00000111;   // prescaler = 16
    PR2 = 249;                 // PWM frequency

    // PWM mode
    CCP1CON = 0b00001100;

    // Start Timer2
    T2CON.TMR2ON = 1;
}

void PWM_SetDuty(u8 duty)
{
    u16 duty_val;

    // Convert percentage → 10-bit value
    duty_val = ((u16)duty * 1023) / 100;

    CCPR1L = duty_val >> 2;
    CCP1CON = (CCP1CON & 0xCF) | ((duty_val & 0x03) << 4);

}