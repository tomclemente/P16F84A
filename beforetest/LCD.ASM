LIST P=16F84A, F=INHX8M
INCLUDE<P16F84.INC>
__CONFIG 3FF5H

ORG 0
TEMP EQU 0CH
GOTO MAIN

SENDDATA 	MOVWF PORTB
			BSF PORTA, 3
			BSF PORTA, 2
			SLEEP
			BCF PORTA, 2
			RETURN

SENDINST	MOVWF PORTB
			BCF PORTA, 3
			BSF PORTA, 2
			SLEEP
			BCF PORTA, 2
			RETURN


NAME	ADDWF PCL, F
		NOP
		RETLW 'M'
		RETLW 'O'
		RETLW 'T'



MAIN	BSF STATUS, RP0
		CLRF TRISB
		MOVLW 03H
		MOVWF TRISA
		MOVLW 0EH
		MOVWF OPTION_REG
		BCF STATUS, RP0
		
LCDINIT	MOVLW 38H
		CALL SENDINST
	

CLEAR 	MOVLW 01H
		CALL SENDINST
		MOVLW 0FH
		CALL SENDINST
		GOTO CHECK
		MOVLW 01H
		CALL SENDINST

CHECK 	BTFSS PORTA, 0
		GOTO CHECK
		GOTO TARONG

TARONG	MOVLW 01H
		CALL SENDINST
		MOVLW D'138'
		CALL SENDINST
		MOVLW 03H
		MOVWF TEMP
LOOP	MOVF TEMP, W
		CALL NAME
		CALL SENDDATA
		DECFSZ TEMP, F
		GOTO LOOP
		GOTO WANA

WANA SLEEP
	 GOTO WANA
END	
			
			
