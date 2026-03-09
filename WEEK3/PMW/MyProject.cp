#line 1 "C:/Users/hager/Downloads/WEEK3/MyProject.c"
#line 1 "c:/users/hager/downloads/week3/gpio_interface.h"
#line 1 "c:/users/hager/downloads/week3/services/std_types.h"




typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;


typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;


typedef float f32;
typedef double f64;
typedef long double f128;
#line 31 "c:/users/hager/downloads/week3/gpio_interface.h"
void GPIO_SetPinDirection(u8 Port, u8 Pin, u8 Direction);
void GPIO_SetPinValue(u8 Port, u8 Pin, u8 Value);
u8 GPIO_GetPinValue(u8 Port, u8 Pin);
void GPIO_Init(void);
#line 1 "c:/users/hager/downloads/week3/led_interface.h"
#line 1 "c:/users/hager/downloads/week3/services/std_types.h"
#line 10 "c:/users/hager/downloads/week3/led_interface.h"
void LED_Init(u8 Port, u8 Pin);
void LED_On(u8 Port, u8 Pin);
void LED_Off(u8 Port, u8 Pin);
void LED_Toggle(u8 Port, u8 Pin);
#line 1 "c:/users/hager/downloads/week3/in.h"
void EXT_INT0_Init(u8 port, u8 pin);
void EXT_INT0_Enable(void);
void EXT_INT0_Disable(void);
void EXT_INT0_SetEdge(u8 edge_type);
void EXT_INT0_SetCallback(void (*ptr)(void));
#line 11 "C:/Users/hager/Downloads/WEEK3/MyProject.c"
unsigned char duty_levels[] = {64, 128, 192, 255};
unsigned char current_level = 0;


void Button_ISR(void) {
 current_level = (current_level + 1) % 4;
 CCPR1L = duty_levels[current_level];
}

void main() {

 GPIO_SetPinDirection( 2 ,  2 ,  0 );


 GPIO_SetPinDirection( 1 ,  0 ,  1 );


 PR2 = 249;
 CCP1CON = 0b00001100;
 CCPR1L = duty_levels[0];
 T2CON = 0b00000100;


 EXT_INT0_Init( 1 ,  0 );
 EXT_INT0_SetEdge(1);
 EXT_INT0_SetCallback(Button_ISR);
 EXT_INT0_Enable();

 while(1) {

 }
}
