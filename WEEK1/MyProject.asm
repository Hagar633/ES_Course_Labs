
_ToggleLED:

;MyProject.c,12 :: 		void ToggleLED(void) {
;MyProject.c,13 :: 		LED_Toggle(LED_PORT, LED_PIN);
	MOVLW      1
	MOVWF      FARG_LED_Toggle_Port+0
	MOVLW      1
	MOVWF      FARG_LED_Toggle_Pin+0
	CALL       _LED_Toggle+0
;MyProject.c,14 :: 		}
L_end_ToggleLED:
	RETURN
; end of _ToggleLED

_main:

;MyProject.c,17 :: 		void main() {
;MyProject.c,19 :: 		LED_Init(LED_PORT, LED_PIN);
	MOVLW      1
	MOVWF      FARG_LED_Init_Port+0
	MOVLW      1
	MOVWF      FARG_LED_Init_Pin+0
	CALL       _LED_Init+0
;MyProject.c,20 :: 		SWITCH_Init(SW_PORT, SW_PIN); // Only pin for switch
	MOVLW      1
	MOVWF      FARG_SWITCH_Init_port+0
	CLRF       FARG_SWITCH_Init_pin+0
	CALL       _SWITCH_Init+0
;MyProject.c,23 :: 		EXT_INT0_Init(SW_PORT, SW_PIN);      // Configure INT0 pin as input and setup interrupt
	MOVLW      1
	MOVWF      FARG_EXT_INT0_Init_port+0
	CLRF       FARG_EXT_INT0_Init_pin+0
	CALL       _EXT_INT0_Init+0
;MyProject.c,24 :: 		EXT_INT0_SetEdge(1);                 // 1 for rising edge, 0 for falling edge (adjust as needed)
	MOVLW      1
	MOVWF      FARG_EXT_INT0_SetEdge_edge_type+0
	CALL       _EXT_INT0_SetEdge+0
;MyProject.c,25 :: 		EXT_INT0_SetCallback(ToggleLED);     // Register the callback function
	MOVLW      _ToggleLED+0
	MOVWF      FARG_EXT_INT0_SetCallback_ptr+0
	MOVLW      hi_addr(_ToggleLED+0)
	MOVWF      FARG_EXT_INT0_SetCallback_ptr+1
	MOVLW      0
	MOVWF      FARG_EXT_INT0_SetCallback_ptr+2
	MOVLW      0
	CALL       _EXT_INT0_SetCallback+0
;MyProject.c,26 :: 		EXT_INT0_Enable();                   // Enable INT0
	CALL       _EXT_INT0_Enable+0
;MyProject.c,28 :: 		while(1) {
L_main0:
;MyProject.c,30 :: 		}
	GOTO       L_main0
;MyProject.c,31 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
