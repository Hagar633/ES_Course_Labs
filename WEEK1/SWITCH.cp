#line 1 "C:/Users/hager/Downloads/WEEK1/SWITCH.c"
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
#line 3 "C:/Users/hager/Downloads/WEEK1/SWITCH.c"
void SWITCH_Init(u8 port, u8 pin) {

 GPIO_SetPinDirection(port, pin,  1 );


}
