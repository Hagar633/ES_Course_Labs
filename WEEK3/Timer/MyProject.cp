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
#line 10 "C:/Users/hager/Downloads/WEEK3/MyProject.c"
volatile unsigned char led1_count = 0;
volatile unsigned char led2_count = 0;
volatile bit led1_toggle_flag;
volatile bit led2_toggle_flag;

void interrupt() {
 if (T0IF_bit) {
 T0IF_bit = 0;
 TMR0 = 125;
 led1_count++;
 led2_count++;

 if (led2_count >= 30) {
 led2_toggle_flag = 1;
 led2_count = 0;
 }
 if (led1_count >= 60) {
 led1_toggle_flag = 1;
 led1_count = 0;
 }
 }
}

void main() {

 LED_Init( 1 ,  0 );
 LED_Init( 1 ,  1 );


 LED_Off( 1 ,  0 );
 LED_Off( 1 ,  1 );


 led1_toggle_flag = 0;
 led2_toggle_flag = 0;


 OPTION_REG = 0b00000111;
 TMR0 = 125;
 T0IE_bit = 1;
 GIE_bit = 1;

 while(1) {
 if (led1_toggle_flag) {
 LED_Toggle( 1 ,  0 );
 led1_toggle_flag = 0;
 }
 if (led2_toggle_flag) {
 LED_Toggle( 1 ,  1 );
 led2_toggle_flag = 0;
 }
 }
}
