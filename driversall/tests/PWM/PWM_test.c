#include "../../SERVICES/BIT_MATH.h"
#include "../../SERVICES/STD_TYPES.h"
#include "../../MCAL/GPIO/GPIO_INTERFACE.h"
#include "../../MCAL/PWM/PMW.h"
#include "../../MCAL/INTERRUPT/IN.h"

#define BTN_PORT   GPIO_PORTB
#define BTN_PIN    GPIO_PIN0

// Duty cycle in percentage ??? values ??????
unsigned char duty_levels[] = {25, 50, 75, 100};
unsigned char current_level = 0;

void Button_ISR(void) {
    current_level = (current_level + 1) % 4;

    // ?????? ?????? ??? PWM
    PWM_SetDuty(duty_levels[current_level]);
}

void main() {

    // ???? input
    GPIO_SetPinDirection(BTN_PORT, BTN_PIN, GPIO_INPUT);

    // Initialize PWM ???????? ????????
    PWM_Init();

    // Start ???? duty
    PWM_SetDuty(duty_levels[0]);

    // External interrupt setup
    EXT_INT0_Init(BTN_PORT, BTN_PIN);
    EXT_INT0_SetEdge(1); // Rising edge
    EXT_INT0_SetCallback(Button_ISR);
    EXT_INT0_Enable();

    while(1) {
        // ???? ??? ?? ????? ?? ISR
    }
}
