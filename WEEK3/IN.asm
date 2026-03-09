
_EXT_INT0_Init:

;IN.c,6 :: 		void EXT_INT0_Init(u8 port, u8 pin) {
;IN.c,7 :: 		GPIO_SetPinDirection(port, pin, GPIO_INPUT);
	MOVF       FARG_EXT_INT0_Init_port+0, 0
	MOVWF      FARG_GPIO_SetPinDirection_Port+0
	MOVF       FARG_EXT_INT0_Init_pin+0, 0
	MOVWF      FARG_GPIO_SetPinDirection_Pin+0
	MOVLW      1
	MOVWF      FARG_GPIO_SetPinDirection_Direction+0
	CALL       _GPIO_SetPinDirection+0
;IN.c,8 :: 		}
L_end_EXT_INT0_Init:
	RETURN
; end of _EXT_INT0_Init

_EXT_INT0_Enable:

;IN.c,10 :: 		void EXT_INT0_Enable(void) {
;IN.c,11 :: 		INTE_bit = 1; // Enable INT0
	BSF        INTE_bit+0, BitPos(INTE_bit+0)
;IN.c,12 :: 		GIE_bit  = 1; // Enable global interrupt
	BSF        GIE_bit+0, BitPos(GIE_bit+0)
;IN.c,13 :: 		}
L_end_EXT_INT0_Enable:
	RETURN
; end of _EXT_INT0_Enable

_EXT_INT0_Disable:

;IN.c,15 :: 		void EXT_INT0_Disable(void) {
;IN.c,16 :: 		INTE_bit = 0;
	BCF        INTE_bit+0, BitPos(INTE_bit+0)
;IN.c,17 :: 		}
L_end_EXT_INT0_Disable:
	RETURN
; end of _EXT_INT0_Disable

_EXT_INT0_SetEdge:

;IN.c,19 :: 		void EXT_INT0_SetEdge(u8 edge_type) {
;IN.c,20 :: 		INTEDG_bit = edge_type; // 1 = rising, 0 = falling
	BTFSC      FARG_EXT_INT0_SetEdge_edge_type+0, 0
	GOTO       L__EXT_INT0_SetEdge4
	BCF        INTEDG_bit+0, BitPos(INTEDG_bit+0)
	GOTO       L__EXT_INT0_SetEdge5
L__EXT_INT0_SetEdge4:
	BSF        INTEDG_bit+0, BitPos(INTEDG_bit+0)
L__EXT_INT0_SetEdge5:
;IN.c,21 :: 		}
L_end_EXT_INT0_SetEdge:
	RETURN
; end of _EXT_INT0_SetEdge

_EXT_INT0_SetCallback:

;IN.c,23 :: 		void EXT_INT0_SetCallback(void (*ptr)(void)) {
;IN.c,24 :: 		EXT_INT0_Callback = ptr;
	MOVF       FARG_EXT_INT0_SetCallback_ptr+0, 0
	MOVWF      IN_EXT_INT0_Callback+0
	MOVF       FARG_EXT_INT0_SetCallback_ptr+1, 0
	MOVWF      IN_EXT_INT0_Callback+1
	MOVF       FARG_EXT_INT0_SetCallback_ptr+2, 0
	MOVWF      IN_EXT_INT0_Callback+2
	MOVF       FARG_EXT_INT0_SetCallback_ptr+3, 0
;IN.c,25 :: 		}
L_end_EXT_INT0_SetCallback:
	RETURN
; end of _EXT_INT0_SetCallback
