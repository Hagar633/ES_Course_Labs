#include "../../SERVICES/BIT_MATH.h"
#include "../../SERVICES/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_interface.h"
#include "I2C.h"

/**
 * @brief Initializes the I2C module as Master at 100kHz
 * Based on Lab 5 Presentation: Uses SSPADD, SSPCON1, and SSPSTAT
 */
void I2C_Init(void) {
    /* 1. Configure SDA and SCL pins as Inputs */
    /* Note: Per presentation, typically Port B (RB0/RB1) or Port C (RC3/RC4) 
       depending on PIC model. Using RB0/RB1 as per Slave example in PPT */
    GPIO_SetPinDirection(GPIO_PORTB, GPIO_PIN0, GPIO_INPUT);
    GPIO_SetPinDirection(GPIO_PORTB, GPIO_PIN1, GPIO_INPUT);

    /* 2. Set I2C Master Mode, Clock = FOSC / (4 * (SSPADD + 1)) */
    /* For 100kHz with 8MHz Clock: SSPADD = (8,000,000 / (4 * 100,000)) - 1 = 19 */
    SSPCON = 0x28;    // 0b00101000 -> Enable SSP, Master Mode
    SSPSTAT = 0x80;    // Slew rate control disabled for standard speed (100kHz)
    SSPADD  = 19;      // Baud rate generator value
}

/**
 * @brief Internal helper to wait for the I2C bus to become idle
 */
static void I2C_Wait(void) {
    // Wait for (Start, Repeated Start, Stop, Receive, or Acknowledge) and Read/Write bit
    while ((SSPSTAT & 0x04) || (SSPCON2 & 0x1F));
}

void I2C_Start(void) {
    I2C_Wait();
    SEN_bit = 1;       // Initiate Start condition
    while (SEN_bit);   // Wait for Start to complete
}

void I2C_RepeatedStart(void) {
    I2C_Wait();
    RSEN_bit = 1;      // Initiate Repeated Start condition
    while (RSEN_bit);
}

void I2C_Stop(void) {
    I2C_Wait();
    PEN_bit = 1;       // Initiate Stop condition
    while (PEN_bit);
}

void I2C_Write(u8 _data) {
    I2C_Wait();
    SSPBUF = _data;    // Load data into buffer
    while (BF_bit);    // Wait until transmit is complete (Buffer Full bit cleared)
    I2C_Wait();        // Ensure completion
}

u8 I2C_Read(u8 ack) {
    u8 temp_data;
    I2C_Wait();
    RCEN_bit = 1;      // Enable Receive mode
    
    while (!BF_bit);   // Wait for Buffer Full (Data received)
    temp_data = SSPBUF;
    
    I2C_Wait();
    /* Send ACK (0) or NACK (1) */
    ACKDT_bit = (ack ? 0 : 1); 
    ACKEN_bit = 1;     // Initiate Acknowledge sequence
    
    return temp_data;
}