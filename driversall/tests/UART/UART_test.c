#include "../../MCAL/UART/UART.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

u8 Destination = 0;

void main(void) {

    UART_TX_Init();
    UART_RX_Init();
    UART_Write('!');

    GPIO_SetPinDirection(GPIO_PORTD, GPIO_PIN0, GPIO_OUTPUT);
    GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN0, GPIO_LOW);

    while (1) {
        if (Destination != 0) {
            UART_Write(Destination);

            GPIO_SetPinValue(GPIO_PORTD, GPIO_PIN0, GPIO_HIGH);

            Destination = 0;
        }
    }
}

void interrupt() {
    if (RCIF) {
        Destination = RCREG;
    }
}
