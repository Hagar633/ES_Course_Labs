
_Button_ISR:

;MyProject.c,15 :: 		void Button_ISR(void) {
;MyProject.c,16 :: 		current_level = (current_level + 1) % 4;
	MOVF       _current_level+0, 0
	ADDLW      1
	MOVWF      R0+0
	CLRF       R0+1
	BTFSC      STATUS+0, 0
	INCF       R0+1, 1
	MOVLW      4
	MOVWF      R4+0
	MOVLW      0
	MOVWF      R4+1
	CALL       _Div_16x16_S+0
	MOVF       R8+0, 0
	MOVWF      R0+0
	MOVF       R8+1, 0
	MOVWF      R0+1
	MOVF       R0+0, 0
	MOVWF      _current_level+0
;MyProject.c,17 :: 		CCPR1L = duty_levels[current_level]; // Update duty cycle
	MOVF       R0+0, 0
	ADDLW      _duty_levels+0
	MOVWF      FSR
	MOVF       INDF+0, 0
	MOVWF      CCPR1L+0
;MyProject.c,18 :: 		}
L_end_Button_ISR:
	RETURN
; end of _Button_ISR

_main:

;MyProject.c,20 :: 		void main() {
;MyProject.c,22 :: 		GPIO_SetPinDirection(PWM_PORT, PWM_PIN, GPIO_OUTPUT);
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVLW      2
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	CLRF       FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;MyProject.c,25 :: 		GPIO_SetPinDirection(BTN_PORT, BTN_PIN, GPIO_INPUT);
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	CLRF       FARG_GPIO_SetPinDirection_Pin+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;MyProject.c,28 :: 		PR2 = 249; // Set PWM period for desired frequency
	MOVLW      249
	MOVWF      PR2+0
;MyProject.c,29 :: 		CCP1CON = 0b00001100; // PWM mode
	MOVLW      12
	MOVWF      CCP1CON+0
;MyProject.c,30 :: 		CCPR1L = duty_levels[0]; // Start at 25%
	MOVF       _duty_levels+0, 0
	MOVWF      CCPR1L+0
;MyProject.c,31 :: 		T2CON = 0b00000100; // Timer2 on, prescaler 1:1
	MOVLW      4
	MOVWF      T2CON+0
;MyProject.c,34 :: 		EXT_INT0_Init(BTN_PORT, BTN_PIN);         // Set RB0 as input for INT0
	MOVLW      1
	MOVWF      FARG_EXT_INT0_Init_port+0
	CLRF       FARG_EXT_INT0_Init_pin+0
	CALL       _EXT_INT0_Init+0
;MyProject.c,35 :: 		EXT_INT0_SetEdge(1);                      // Rising edge
	MOVLW      1
	MOVWF      FARG_EXT_INT0_SetEdge_edge_type+0
	CALL       _EXT_INT0_SetEdge+0
;MyProject.c,36 :: 		EXT_INT0_SetCallback(Button_ISR);         // Set ISR callback
	MOVLW      _Button_ISR+0
	MOVWF      FARG_EXT_INT0_SetCallback_ptr+0
	MOVLW      hi_addr(_Button_ISR+0)
	MOVWF      FARG_EXT_INT0_SetCallback_ptr+1
	MOVLW      0
	MOVWF      FARG_EXT_INT0_SetCallback_ptr+2
	MOVLW      0
	CALL       _EXT_INT0_SetCallback+0
;MyProject.c,37 :: 		EXT_INT0_Enable();                        // Enable INT0 and global interrupt
	CALL       _EXT_INT0_Enable+0
;MyProject.c,39 :: 		while(1) {
L_main0:
;MyProject.c,41 :: 		}
	GOTO       L_main0
;MyProject.c,42 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
