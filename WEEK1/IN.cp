#line 1 "C:/Users/hager/Downloads/WEEK1/IN.c"
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
#line 1 "c:/users/hager/downloads/week1/in.h"
void EXT_INT0_Init(u8 port, u8 pin);
void EXT_INT0_Enable(void);
void EXT_INT0_Disable(void);
void EXT_INT0_SetEdge(u8 edge_type);
void EXT_INT0_SetCallback(void (*ptr)(void));
#line 4 "C:/Users/hager/Downloads/WEEK1/IN.c"
static void (*EXT_INT0_Callback)(void) = 0;

void EXT_INT0_Init(u8 port, u8 pin) {
 GPIO_SetPinDirection(port, pin,  1 );
}

void EXT_INT0_Enable(void) {
 INTE_bit = 1;
 GIE_bit = 1;
}

void EXT_INT0_Disable(void) {
 INTE_bit = 0;
}

void EXT_INT0_SetEdge(u8 edge_type) {
 INTEDG_bit = edge_type;
}

void EXT_INT0_SetCallback(void (*ptr)(void)) {
 EXT_INT0_Callback = ptr;
}


void interrupt() {
 if (INTF_bit) {
 if (EXT_INT0_Callback) {
 EXT_INT0_Callback();
 }
 INTF_bit = 0;
 }
}
