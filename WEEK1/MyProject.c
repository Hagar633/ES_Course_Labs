#include "GPIO_interface.h"
#include "LED_interface.h"
#include "SWITCH.h"
#include "IN.h"

// Define the port and pin for LED and Switch
#define LED_PORT GPIO_PORTB
#define LED_PIN  GPIO_PIN1
#define SW_PORT  GPIO_PORTB
#define SW_PIN   GPIO_PIN0

void ToggleLED(void) {
    LED_Toggle(LED_PORT, LED_PIN);
}


void main() {
    // Initialize LED and Switch
    LED_Init(LED_PORT, LED_PIN);
    SWITCH_Init(SW_PORT, SW_PIN); // Only pin for switch

    // Initialize INT0 (external interrupt on RB0)
    EXT_INT0_Init(SW_PORT, SW_PIN);      // Configure INT0 pin as input and setup interrupt
    EXT_INT0_SetEdge(1);                 // 1 for rising edge, 0 for falling edge (adjust as needed)
    EXT_INT0_SetCallback(ToggleLED);     // Register the callback function
    EXT_INT0_Enable();                   // Enable INT0

    while(1) {
        // Main loop does nothing, all handled by interrupt
    }
}