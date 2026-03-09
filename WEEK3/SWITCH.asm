
_SWITCH_Init:

;SWITCH.c,3 :: 		void SWITCH_Init(u8 port, u8 pin) {
;SWITCH.c,5 :: 		GPIO_SetPinDirection(port, pin, GPIO_INPUT);
	MOVF       FARG_SWITCH_Init_port+0, 0
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVF       FARG_SWITCH_Init_pin+0, 0
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;SWITCH.c,8 :: 		}
L_end_SWITCH_Init:
	RETURN
; end of _SWITCH_Init
