#include "../../SERVICES/STD_TYPES.h"
#include "../../MCAL/SPI/SPI.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
void main(void)
{
    u8 received;

    /* Init SPI as Master */
    SPI_InitMaster(SPI_MODE_0);

    while(1)
    {
        /* Select slave */
        SPI_MasterSelectSlave();

        /* Send data and receive response */
        received = SPI_Transfer(0x55);

        /* Deselect slave */
        SPI_MasterDeselectSlave();

        /* Simple delay */
        Delay_ms(100);


    }
}