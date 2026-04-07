#ifndef UART_H
#define UART_H

#include "../../SERVICES/STD_TYPES.h"


void UART_TX_Init(void);
void UART_Write(u8 data_);
u8 UART_TX_Empty(void);
void UART_RX_Init(void);
u8 UART_Read(void);
extern u8 Destination;

#endif 