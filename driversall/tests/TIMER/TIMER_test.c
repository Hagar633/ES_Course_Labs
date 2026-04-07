#include "../../MCAL/GPIO/GPIO_interface.h"
#include "../../HAL/LED/LED_interface.h"
#include "../../MCAL/TIMER0/TIMER0.h"

// Define LED pins and ports
#define LED1_PORT GPIO_PORTB
#define LED1_PIN  0
#define LED2_PORT GPIO_PORTB
#define LED2_PIN  1

volatile unsigned char led1_count = 0;
volatile unsigned char led2_count = 0;

volatile bit led1_toggle_flag;
volatile bit led2_toggle_flag;

/* Callback function for Timer0 */
void Timer0_Task(void)
{
    // Reload preload value
    TIMER0_SetPreload(125);

    led1_count++;
    led2_count++;

    if (led2_count >= 30) { // ~1 second
        led2_toggle_flag = 1;
        led2_count = 0;
    }

    if (led1_count >= 60) { // ~2 seconds
        led1_toggle_flag = 1;
        led1_count = 0;
    }
}

void main()
{
    // Initialize LEDs
    LED_Init(LED1_PORT, LED1_PIN);
    LED_Init(LED2_PORT, LED2_PIN);

    LED_Off(LED1_PORT, LED1_PIN);
    LED_Off(LED2_PORT, LED2_PIN);

    // Initialize flags
    led1_toggle_flag = 0;
    led2_toggle_flag = 0;

    // Initialize Timer0 using driver
    TIMER0_Init(0, 0b111);   // Internal clock, prescaler 1:256
    TIMER0_SetCallback(Timer0_Task);

    while(1)
    {
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
