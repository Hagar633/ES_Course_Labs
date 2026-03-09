
_interrupt:
	MOVWF      R15+0
	SWAPF      STATUS+0, 0
	CLRF       STATUS+0
	MOVWF      ___saveSTATUS+0
	MOVF       PCLATH+0, 0
	MOVWF      ___savePCLATH+0
	CLRF       PCLATH+0

;MyProject.c,15 :: 		void interrupt() {
;MyProject.c,16 :: 		if (T0IF_bit) {
	BTFSS      T0IF_bit+0, BitPos(T0IF_bit+0)
	GOTO       L_interrupt0
;MyProject.c,17 :: 		T0IF_bit = 0; // Clear Timer0 interrupt flag
	BCF        T0IF_bit+0, BitPos(T0IF_bit+0)
;MyProject.c,18 :: 		TMR0 = 125;   // Preload for 1-second timing as per calculations
	MOVLW      125
	MOVWF      TMR0+0
;MyProject.c,19 :: 		led1_count++;
	INCF       _led1_count+0, 0
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      _led1_count+0
;MyProject.c,20 :: 		led2_count++;
	INCF       _led2_count+0, 0
	MOVWF      R0+0
	MOVF       R0+0, 0
	MOVWF      _led2_count+0
;MyProject.c,22 :: 		if (led2_count >= 30) { // 1 second
	MOVLW      30
	SUBWF      _led2_count+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_interrupt1
;MyProject.c,23 :: 		led2_toggle_flag = 1;
	BSF        _led2_toggle_flag+0, BitPos(_led2_toggle_flag+0)
;MyProject.c,24 :: 		led2_count = 0;
	CLRF       _led2_count+0
;MyProject.c,25 :: 		}
L_interrupt1:
;MyProject.c,26 :: 		if (led1_count >= 60) { // 2 seconds
	MOVLW      60
	SUBWF      _led1_count+0, 0
	BTFSS      STATUS+0, 0
	GOTO       L_interrupt2
;MyProject.c,27 :: 		led1_toggle_flag = 1;
	BSF        _led1_toggle_flag+0, BitPos(_led1_toggle_flag+0)
;MyProject.c,28 :: 		led1_count = 0;
	CLRF       _led1_count+0
;MyProject.c,29 :: 		}
L_interrupt2:
;MyProject.c,30 :: 		}
L_interrupt0:
;MyProject.c,31 :: 		}
L_end_interrupt:
L__interrupt8:
	MOVF       ___savePCLATH+0, 0
	MOVWF      PCLATH+0
	SWAPF      ___saveSTATUS+0, 0
	MOVWF      STATUS+0
	SWAPF      R15+0, 1
	SWAPF      R15+0, 0
	RETFIE
; end of _interrupt

_main:

;MyProject.c,33 :: 		void main() {
;MyProject.c,35 :: 		LED_Init(LED1_PORT, LED1_PIN);
	MOVLW      1
	MOVWF      FARG_LED_Init_Port+0
	CLRF       FARG_LED_Init_Pin+0
	CALL       _LED_Init+0
;MyProject.c,36 :: 		LED_Init(LED2_PORT, LED2_PIN);
	MOVLW      1
	MOVWF      FARG_LED_Init_Port+0
	MOVLW      1
	MOVWF      FARG_LED_Init_Pin+0
	CALL       _LED_Init+0
;MyProject.c,39 :: 		LED_Off(LED1_PORT, LED1_PIN);
	MOVLW      1
	MOVWF      FARG_LED_Off_Port+0
	CLRF       FARG_LED_Off_Pin+0
	CALL       _LED_Off+0
;MyProject.c,40 :: 		LED_Off(LED2_PORT, LED2_PIN);
	MOVLW      1
	MOVWF      FARG_LED_Off_Port+0
	MOVLW      1
	MOVWF      FARG_LED_Off_Pin+0
	CALL       _LED_Off+0
;MyProject.c,43 :: 		led1_toggle_flag = 0;
	BCF        _led1_toggle_flag+0, BitPos(_led1_toggle_flag+0)
;MyProject.c,44 :: 		led2_toggle_flag = 0;
	BCF        _led2_toggle_flag+0, BitPos(_led2_toggle_flag+0)
;MyProject.c,47 :: 		OPTION_REG = 0b00000111; // Prescaler 1:256, assign to TMR0
	MOVLW      7
	MOVWF      OPTION_REG+0
;MyProject.c,48 :: 		TMR0 = 125; // Preload value
	MOVLW      125
	MOVWF      TMR0+0
;MyProject.c,49 :: 		T0IE_bit = 1; // Enable Timer0 interrupt
	BSF        T0IE_bit+0, BitPos(T0IE_bit+0)
;MyProject.c,50 :: 		GIE_bit = 1;  // Enable global interrupts
	BSF        GIE_bit+0, BitPos(GIE_bit+0)
;MyProject.c,52 :: 		while(1) {
L_main3:
;MyProject.c,53 :: 		if (led1_toggle_flag) {
	BTFSS      _led1_toggle_flag+0, BitPos(_led1_toggle_flag+0)
	GOTO       L_main5
;MyProject.c,54 :: 		LED_Toggle(LED1_PORT, LED1_PIN);
	MOVLW      1
	MOVWF      FARG_LED_Toggle_Port+0
	CLRF       FARG_LED_Toggle_Pin+0
	CALL       _LED_Toggle+0
;MyProject.c,55 :: 		led1_toggle_flag = 0;
	BCF        _led1_toggle_flag+0, BitPos(_led1_toggle_flag+0)
;MyProject.c,56 :: 		}
L_main5:
;MyProject.c,57 :: 		if (led2_toggle_flag) {
	BTFSS      _led2_toggle_flag+0, BitPos(_led2_toggle_flag+0)
	GOTO       L_main6
;MyProject.c,58 :: 		LED_Toggle(LED2_PORT, LED2_PIN);
	MOVLW      1
	MOVWF      FARG_LED_Toggle_Port+0
	MOVLW      1
	MOVWF      FARG_LED_Toggle_Pin+0
	CALL       _LED_Toggle+0
;MyProject.c,59 :: 		led2_toggle_flag = 0;
	BCF        _led2_toggle_flag+0, BitPos(_led2_toggle_flag+0)
;MyProject.c,60 :: 		}
L_main6:
;MyProject.c,61 :: 		}
	GOTO       L_main3
;MyProject.c,62 :: 		}
L_end_main:
	GOTO       $+0
; end of _main
