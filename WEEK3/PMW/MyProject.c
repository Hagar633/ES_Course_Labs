#include "GPIO_interface.h"
#include "LED_interface.h"
#include "IN.h"


#define PWM_PORT   GPIO_PORTC
#define PWM_PIN    2
#define BTN_PORT   GPIO_PORTB
#define BTN_PIN    0

unsigned char duty_levels[] = {64, 128, 192, 255};
unsigned char current_level = 0;


void Button_ISR(void) {
    current_level = (current_level + 1) % 4;
    CCPR1L = duty_levels[current_level];
}

void main() {

    GPIO_SetPinDirection(PWM_PORT, PWM_PIN, GPIO_OUTPUT);


    GPIO_SetPinDirection(BTN_PORT, BTN_PIN, GPIO_INPUT);


    PR2 = 249;
    CCP1CON = 0b00001100;
    CCPR1L = duty_levels[0];
    T2CON = 0b00000100;


    EXT_INT0_Init(BTN_PORT, BTN_PIN);
    EXT_INT0_SetEdge(1);
    EXT_INT0_SetCallback(Button_ISR);
    EXT_INT0_Enable();

    while(1) {

    }
}