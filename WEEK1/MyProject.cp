#line 1 "C:/Users/hager/Downloads/WEEK1/MyProject.c"
#line 1 "c:/users/hager/downloads/week1/gpio_interface.h"
#line 1 "c:/users/hager/downloads/week1/services/std_types.h"




typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;


typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;


typedef float f32;
typedef double f64;
typedef long double f128;
#line 31 "c:/users/hager/downloads/week1/gpio_interface.h"
void GPIO_SetPinDirection(u8 Port, u8 Pin, u8 Direction);
void GPIO_SetPinValue(u8 Port, u8 Pin, u8 Value);
u8 GPIO_GetPinValue(u8 Port, u8 Pin);
void GPIO_Init(void);
#line 1 "c:/users/hager/downloads/week1/led_interface.h"
#line 1 "c:/users/hager/downloads/week1/services/std_types.h"
#line 10 "c:/users/hager/downloads/week1/led_interface.h"
void LED_Init(u8 Port, u8 Pin);
void LED_On(u8 Port, u8 Pin);
void LED_Off(u8 Port, u8 Pin);
void LED_Toggle(u8 Port, u8 Pin);
#line 1 "c:/users/hager/downloads/week1/switch.h"
void SWITCH_Init(u8 port,u8 pin);
#line 1 "c:/users/hager/downloads/week1/in.h"
void EXT_INT0_Init(u8 port, u8 pin);
void EXT_INT0_Enable(void);
void EXT_INT0_Disable(void);
void EXT_INT0_SetEdge(u8 edge_type);
void EXT_INT0_SetCallback(void (*ptr)(void));
#line 12 "C:/Users/hager/Downloads/WEEK1/MyProject.c"
void ToggleLED(void) {
 LED_Toggle( 1 ,  1 );
}


void main() {

 LED_Init( 1 ,  1 );
 SWITCH_Init( 1 ,  0 );


 EXT_INT0_Init( 1 ,  0 );
 EXT_INT0_SetEdge(1);
 EXT_INT0_SetCallback(ToggleLED);
 EXT_INT0_Enable();

 while(1) {

 }
}
