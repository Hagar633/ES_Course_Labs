#ifndef PWM_H
#define PWM_H

#include "../../SERVICES/STD_TYPES.h"

void PWM_Init(void);
void PWM_SetDuty(u8 duty); // 0 → 100 %

#endif