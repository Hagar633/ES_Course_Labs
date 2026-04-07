#include "../../SERVICES/BIT_MATH.h"
#include "../../SERVICES/STD_TYPES.h"
#include "ADC.h"

/* Registers (for PIC16F877A) */
#define ADCON0  (*((volatile u8*)0x1F))
#define ADCON1  (*((volatile u8*)0x9F))
#define ADRESH  (*((volatile u8*)0x1E))
#define ADRESL  (*((volatile u8*)0x9E))

/* Bit definitions */
#define GO_DONE 2
#define ADON    0

void ADC_Init(void)
{
    /* Configure AN0 as analog, rest digital */
    ADCON1 = 0x80;  
    // Right justified, Vref = Vdd

    /* ADC Clock = Fosc/32 (for 8MHz safe) */
    ADCON0 = 0x81;  
    // Channel 0 + ADC ON
}

u16 ADC_Read(u8 channel)
{
    /* Clear channel bits */
    ADCON0 &= 0b11000101;

    /* Select channel */
    ADCON0 |= (channel << 3);

    /* Acquisition delay */
    delay_ms(2);

    /* Start conversion */
    SET_BIT(ADCON0, GO_DONE);

    /* Wait until conversion finishes */
    while(GET_BIT(ADCON0, GO_DONE));

    /* Return result */
    return ((ADRESH << 8) + ADRESL);
}