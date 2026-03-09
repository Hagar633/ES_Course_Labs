#include "GPIO_interface.h"
#include "LED_interface.h"

// Define LED pins and ports
#define LED1_PORT GPIO_PORTB
#define LED1_PIN  0
#define LED2_PORT GPIO_PORTB
#define LED2_PIN  1

volatile unsigned char led1_count = 0;
volatile unsigned char led2_count = 0;
volatile bit led1_toggle_flag; // Do NOT initialize here!
volatile bit led2_toggle_flag; // Do NOT initialize here!

void interrupt() {
    if (T0IF_bit) {
        T0IF_bit = 0; // Clear Timer0 interrupt flag
        TMR0 = 125;   // Preload for 1-second timing as per calculations
        led1_count++;
        led2_count++;

        if (led2_count >= 30) { // 1 second
            led2_toggle_flag = 1;
            led2_count = 0;
        }
        if (led1_count >= 60) { // 2 seconds
            led1_toggle_flag = 1;
            led1_count = 0;
        }
    }
}

void main() {
    // Initialize LEDs using driver
    LED_Init(LED1_PORT, LED1_PIN);
    LED_Init(LED2_PORT, LED2_PIN);

    // Optionally turn off both LEDs at start
    LED_Off(LED1_PORT, LED1_PIN);
    LED_Off(LED2_PORT, LED2_PIN);

    // Initialize flags (do this in main, not at declaration)
    led1_toggle_flag = 0;
    led2_toggle_flag = 0;

    // Timer0 setup
    OPTION_REG = 0b00000111; // Prescaler 1:256, assign to TMR0
    TMR0 = 125; // Preload value
    T0IE_bit = 1; // Enable Timer0 interrupt
    GIE_bit = 1;  // Enable global interrupts

    while(1) {
        if (led1_toggle_flag) {
            LED_Toggle(LED1_PORT, LED1_PIN);
            led1_toggle_flag = 0;
        }
        if (led2_toggle_flag) {
            LED_Toggle(LED2_PORT, LED2_PIN);
            led2_toggle_flag = 0;
        }
    }
}