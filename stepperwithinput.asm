LIST P=16F84A, F=INHX8M
INCLUDE <P16F84.INC>
__CONFIG 3FF5H

FLAGY EQU 0CH
TEMP EQU 0DH

MAIN	BSF STATUS, RP0
		MOVLW 0FH
		MOVWF TRISB
		MOVLW 08H
		MOVWF OPTION_REG
		BCF STATUS, RP0
		

		MOVLW 10H
		MOVWF PORTB
		MOVLW 00H
		MOVWF TEMP

CW		



		MOVLW 01H
		ADDWF TEMP, F
		MOVLW D'10'
		SUBWF TEMP, W
		BTFSC STATUS, Z
		GOTO PAUSE
	;	BTFSS PORTB, 4
	;	GOTO CW2
	;	MOVLW 80H
	;	MOVWF PORTB
		;BCF PORTB, 4
		;BSF PORTB, 7
		GOTO CW2
CW2		RRF PORTB, F
		BTFSS STATUS, C
		GOTO CW
		GOTO PAUSE	
		;GOTO PAUSE


PAUSE 	BSF STATUS, RP0
		MOVLW 0FH
		MOVWF OPTION_REG
		BCF STATUS, RP0

		SLEEP

		BSF STATUS, RP0
		MOVLW 08H
		MOVWF OPTION_REG
		BCF STATUS, RP0
	
		MOVLW 00H
		MOVWF TEMP
		GOTO CW


END