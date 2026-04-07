#include "../../SERVICES/STD_TYPES.h"
#include "../../MCAL/SPI/SPI.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

void main(void)
{
    u8 received;

    /* Init SPI as Slave */
    SPI_InitSlave(SPI_MODE_0);

    while(1)
    {
        /* Wait for data */
        if (PIR1.SSPIF)
        {
            received = SSPBUF;   // Read received data

            /* Send response */
            SSPBUF = 0xAA;

            PIR1.SSPIF = 0;
        }
    }
}