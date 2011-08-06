LIST P=16F84, F=INHX8M
INCLUDE<P16F84.INC>
__CONFIG 3FF5H

FLAG EQU 0CH
TEMP EQU 0DH
CNTR EQU 0EH

ORG 0000H
GOTO INIT
GOTO MAIN
ORG 0004H
GOTO INT_ROUTINE

INIT	CLRF STATUS
		BSF STATUS, RP0
		MOVLW 0BH
		MOVWF OPTION_REG
		MOVLW 01H
		MOVWF TRISB
		BSF INTCON, GIE
		BSF INTCON, INTE
		BCF STATUS, RP0
		MOVLW 00H
		MOVWF TEMP
		MOVLW 00H
		MOVWF FLAG
		MOVLW D'200'
		MOVWF CNTR

MAIN	
		
		;BTFSS INTCON, 1
		BTFSS FLAG, 0
		GOTO MAIN
		BCF FLAG, 0
LOOP1	MOVLW 04H	
		XORWF TEMP, W
		BTFSS STATUS, Z
		GOTO LOOP
		MOVLW 00H
		MOVWF TEMP
LOOP	INCF TEMP, F
		MOVF TEMP, W
		CALL STEP
		MOVWF PORTB
		SLEEP
		;BSF INTCON, 7
		DECFSZ CNTR, F
		GOTO LOOP1
		MOVLW D'200'
		MOVWF CNTR
		MOVLW 00H
		MOVWF TEMP
		

		BSF STATUS, RP0
		MOVLW 0FH
		MOVWF OPTION_REG
		BCF STATUS, RP0
		SLEEP
		SLEEP
		SLEEP
		BSF STATUS, RP0
		MOVLW 0CH
		MOVWF OPTION_REG
		BCF STATUS, RP0



LOOP4	MOVLW 04H
		XORWF TEMP, W
		BTFSS STATUS, Z
		GOTO LOOP3
		MOVLW 00H
		MOVWF TEMP
LOOP3	INCF TEMP, F
		MOVF TEMP, W
		CALL STEP2
		MOVWF PORTB
		SLEEP
		DECFSZ CNTR, F
		GOTO LOOP4
		MOVLW D'200'
		MOVWF CNTR

		BSF INTCON, INTE
		BSF INTCON, GIE
		GOTO MAIN
		
		

STEP	ADDWF PCL, F
		NOP
		RETLW 12H
		RETLW 06H
		RETLW 0CH
		RETLW 18H
		RETURN
STEP2	ADDWF PCL, F
		NOP
		RETLW 18H
		RETLW 0CH
		RETLW 06H
		RETLW 12H
		RETURN
		
		

INT_ROUTINE
	BCF INTCON, GIE
	BTFSS INTCON, INTF
	RETFIE
	BCF INTCON, INTF
	BSF FLAG, 0
	GOTO MAIN


	
END