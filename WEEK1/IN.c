#include "GPIO_interface.h"
#include "IN.h"

static void (*EXT_INT0_Callback)(void) = 0;

void EXT_INT0_Init(u8 port, u8 pin) {
    GPIO_SetPinDirection(port, pin, GPIO_INPUT);
}

void EXT_INT0_Enable(void) {
    INTE_bit = 1; // Enable INT0
    GIE_bit  = 1; // Enable global interrupt
}

void EXT_INT0_Disable(void) {
    INTE_bit = 0;
}

void EXT_INT0_SetEdge(u8 edge_type) {
    INTEDG_bit = edge_type; // 1 = rising, 0 = falling
}

void EXT_INT0_SetCallback(void (*ptr)(void)) {
    EXT_INT0_Callback = ptr;
}

// ISR implementation (must be in main.c in MikroC)
void interrupt() {
    if (INTF_bit) {
        if (EXT_INT0_Callback) {
            EXT_INT0_Callback();
        }
        INTF_bit = 0; // Clear interrupt flag
    }
}
