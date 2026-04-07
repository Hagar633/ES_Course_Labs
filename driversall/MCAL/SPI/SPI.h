#ifndef SPI_H_
#define SPI_H_
#include "../../SERVICES/STD_TYPES.h"

#define SPI_MODE_0    0
#define SPI_MODE_1    1
#define SPI_MODE_2    2
#define SPI_MODE_3    3

void SPI_InitMaster(u8 mode);

void SPI_InitSlave(u8 mode);

void SPI_MasterSelectSlave(void);

void SPI_MasterDeselectSlave(void);

u8 SPI_Transfer(u8 data_);

void SPI_Send(u8 data_);

u8 SPI_Receive(void);

#endif 