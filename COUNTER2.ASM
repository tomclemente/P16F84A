LIST P=16F84A, F=INHX8M
INCLUDE <P16F84.INC>
__CONFIG 3FF5H

TEMP EQU 0CH

MAIN	BSF STATUS, RP0
		MOVLW 03H
		MOVWF TRISB

		MOVLW 0EH
		MOVWF OPTION_REG
		BCF STATUS, RP0
		BCF PORTB, 7
		BCF PORTB, 6
		BCF PORTB, 5
		BCF PORTB, 4
		MOVLW 00H
		MOVWF TEMP
	

		
CHECK	
		MOVLW 00H
		MOVWF TEMP
		MOVLW 00H
		
		BTFSC PORTB, 0	;SKIP IF SWITCH1 IS OFF	
		MOVLW 01H
		ADDWF TEMP, F		

		MOVLW 00H	
	
		BTFSC PORTB, 1 ;SWITCH1 IS SET, CHECKS SWITCH2
		MOVLW 02H
		ADDWF TEMP, F

		MOVLW 00H
		XORWF TEMP
		BTFSS STATUS, Z
		GOTO CHECK2
		GOTO CHECK
	
CHECK2	;CHECKS IF TWO SWITCHES ARE ON
		MOVLW 03H
		XORWF TEMP
		BTFSC STATUS, Z
		GOTO CHECK
		GOTO CHECK3
CHECK3	;DETERMINES WHICH OF THE SWITCHES ARE ON
		BTFSS PORTB,0
		BTFSS PORTB,1
		GOTO COUNTUP
		GOTO COUNTDN
		GOTO CHECK

COUNTUP 
	 	SLEEP
		MOVLW 10H
		ADDWF PORTB, F
		MOVFW PORTB
		XORLW 0A1H
		BTFSS STATUS, Z
		GOTO CHECK
		CLRF PORTB
		SLEEP
		GOTO CHECK
		
		
COUNTDN	SLEEP
		MOVLW 10H
		SUBWF PORTB, F
		MOVFW PORTB
		XORLW 02H
		BTFSS STATUS, Z
		GOTO CHECK
		SLEEP
		MOVLW 092H
		MOVWF PORTB
		SLEEP
		
		GOTO CHECK

CYCLE	MOVLW 03H
		MOVWF PORTB
		GOTO CHECK


END