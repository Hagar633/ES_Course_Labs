#include "../../SERVICES/BIT_MATH.h"
#include "../../SERVICES/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "UART.h"

void UART_TX_Init(void)
{
    /* 1. Baud Rate Configuration: 9600 bps @ 8MHz Clock */
    TXSTA.BRGH = 1;   // High Speed Baud Rate Select bit
    SPBRG = 51;       // Load value for 9600 baud

    /* 2. Mode Configuration */
    TXSTA.SYNC = 0;   // Asynchronous mode
    RCSTA.SPEN = 1;   // Serial Port Enable (configures RX/TX pins as serial)

    /* 3. GPIO Configuration using Driver Functions */
    // RC6 is the TX pin. Setting as Input/High-Z is recommended for UART
    GPIO_SetPinDirection(2, 6, 1);

    /* 4. Enable Transmission */
    TXSTA.TXEN = 1;
}

void UART_RX_Init(void)
{
    /* 1. Baud Rate Configuration (Matches TX) */
    TXSTA.BRGH = 1;
    SPBRG = 51;

    /* 2. Mode Configuration */
    TXSTA.SYNC = 0;
    RCSTA.SPEN = 1;

    /* 3. GPIO Configuration using Driver Functions */
    // RC7 is the RX pin. Must be set as Input.
    GPIO_SetPinDirection(2, 7, 1);

    /* 4. Interrupt Configuration */
    PIE1.RCIE = 1;    // UART Receive Interrupt Enable
    INTCON.PEIE = 1;  // Peripheral Interrupt Enable
    INTCON.GIE  = 1;  // Global Interrupt Enable

    /* 5. Enable Continuous Reception */
    RCSTA.CREN = 1;
}

void UART_Write(u8 data_)
{
    /* Wait for Transmit Shift Register to be empty (TRMT is bit 1 of TXSTA) */
    while(TXSTA.TRMT == 0);

    /* Load data into transmit register */
    TXREG = data_;
}

u8 UART_Read(void)
{
    /* Wait until data is received (RCIF flag is in PIR1) */
    while(PIR1.RCIF == 0);

    /* Error Handling: Check for Overrun Error (OERR) */
    if (RCSTA.OERR)
    {
        RCSTA.CREN = 0; // Clear error by toggling CREN
        RCSTA.CREN = 1;
    }

    return RCREG;
}

u8 UART_TX_Empty(void)
{
    /* Returns the status of the Transmit Shift Register */
    return TXSTA.TRMT;
}