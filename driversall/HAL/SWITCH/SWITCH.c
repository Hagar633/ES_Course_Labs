#include "../../MCAL/GPIO/GPIO_interface.h"

void SWITCH_Init(u8 port, u8 pin) {
    // Set the switch pin as input
    GPIO_SetPinDirection(port, pin, GPIO_INPUT);
    // Optionally enable pull-up if needed
    // (implement GPIO_EnablePullup if required)
}