#include "../../SERVICES/BIT_MATH.h"
#include "../../SERVICES/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../MCAL/ADC/ADC.h"
#include "../../MCAL/UART/UART.h"

#define _XTAL_FREQ 8000000

void UART_SendString(char *str)
{
    while(*str)
    {
        UART_Write(*str++);
    }
}

void UART_SendNumber(u16 num)
{
    char buffer[6];
    int i = 0;

    if(num == 0)
    {
        UART_Write('0');
        return;
    }

    while(num > 0)
    {
        buffer[i++] = (num % 10) + '0';
        num /= 10;
    }

    while(i--)
    {
        UART_Write(buffer[i]);
    }
}

void main(void)
{
    u16 adc_value;
    u16 temperature;

    /* Init */
    ADC_Init();
    UART_TX_Init();

    while(1)
    {
        /* Read from AN0 */
        adc_value = ADC_Read(ADC_CHANNEL_0);

        /* Convert to temperature */
        temperature = (adc_value * 5 * 100) / 1023;

        /* Send ??? UART */
        UART_SendString("Temp = ");
        UART_SendNumber(temperature);
        UART_SendString(" C\r\n");

        delay_ms(500);
    }
}
