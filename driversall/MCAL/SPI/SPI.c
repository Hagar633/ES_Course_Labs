#include "../../SERVICES/BIT_MATH.h"
#include "../../SERVICES/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "SPI.h"


static void SPI_SetMode(u8 mode)
{
    switch(mode)
    {
        case SPI_MODE_0:
            SSPCON.CKP = 0;
            SSPSTAT.CKE = 1;
        break;

        case SPI_MODE_1:
            SSPCON.CKP = 0;
            SSPSTAT.CKE = 0;
        break;

        case SPI_MODE_2:
            SSPCON.CKP = 1;
            SSPSTAT.CKE = 1;
        break;

        case SPI_MODE_3:
            SSPCON.CKP = 1;
            SSPSTAT.CKE = 0;
        break;
    }
}

/*MASTER INIT*/
void SPI_InitMaster(u8 mode)
{
    SPI_SetMode(mode);

    /* Step 2: Configure Sampling */
    SSPSTAT.SMP = 0;   // Middle sampling (recommended)

    /* Step 3: Set Clock Rate (Fosc/16) */
    SSPCON.SSPM0 = 0;
    SSPCON.SSPM1 = 0;
    SSPCON.SSPM2 = 0;
    SSPCON.SSPM3 = 0;

    /* Step 4: Configure Pins using GPIO */
    GPIO_SetPinDirection(GPIO_PORTC, 5, GPIO_OUTPUT); // SDO
    GPIO_SetPinDirection(GPIO_PORTC, 4, GPIO_INPUT);  // SDI
    GPIO_SetPinDirection(GPIO_PORTC, 3, GPIO_OUTPUT); // SCK

    /* Optional SS (manual control) */
    GPIO_SetPinDirection(GPIO_PORTA, 5, GPIO_OUTPUT);
    GPIO_SetPinValue(GPIO_PORTA, 5, GPIO_HIGH); // idle HIGH

    /* Step 5: Enable SPI */
    SSPCON.SSPEN = 1;
}

/* ================== SLAVE INIT ================== */
void SPI_InitSlave(u8 mode)
{
    
    SPI_SetMode(mode);

    SSPSTAT.SMP = 0;

    /*  Slave Mode + SS */
    SSPCON.SSPM0 = 0;
    SSPCON.SSPM1 = 0;
    SSPCON.SSPM2 = 1;
    SSPCON.SSPM3 = 0;

    /* Configure Pins */
    GPIO_SetPinDirection(GPIO_PORTC, 5, GPIO_OUTPUT); // SDO
    GPIO_SetPinDirection(GPIO_PORTC, 4, GPIO_INPUT);  // SDI
    GPIO_SetPinDirection(GPIO_PORTC, 3, GPIO_INPUT);  // SCK
    GPIO_SetPinDirection(GPIO_PORTA, 5, GPIO_INPUT);  // SS

    /*  digital  */
    ADCON1.PCFG0 = 0;
    ADCON1.PCFG1 = 0;
    ADCON1.PCFG2 = 1;
    ADCON1.PCFG3 = 0;

    /* Enable SPI */
    SSPCON.SSPEN = 1;
        
        // interrupt
    PIE1.SSPIE = 1;
    INTCON.PEIE = 1;
    INTCON.GIE  = 1;
}

/* SS CONTROL (MASTER)*/
void SPI_MasterSelectSlave(void)
{
    GPIO_SetPinValue(GPIO_PORTA, 5, GPIO_LOW); // SS = 0
}

void SPI_MasterDeselectSlave(void)
{
    GPIO_SetPinValue(GPIO_PORTA, 5, GPIO_HIGH); // SS = 1
}

/*TRANSFER or write as written in lab*/
u8 SPI_Transfer(u8 data_)
{
    SSPBUF = data_;
    while (!PIR1.SSPIF);
    PIR1.SSPIF = 0;
    return SSPBUF;
}


void SPI_Send(u8 data_)
{
    SPI_Transfer(data_);
}

u8 SPI_Receive(void)
{
        /* clock start */
    return SPI_Transfer(0xFF);
}

void __interrupt()
{
    if (PIR1.SSPIF)
    {
        u8 data_ = SSPBUF;
        PIR1.SSPIF = 0;
    }
}