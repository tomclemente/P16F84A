LIST P=16F84A, F=INHX8M
INCLUDE<P16F84.INC>
__CONFIG 3FF5H


TEMP EQU 00H

MAIN BSF STATUS,RP0
MOVLW 03H
MOVWF TRISB
MOVLW 0EH
MOVWF OPTION_REG
BCF STATUS, RP0

CHECK	SLEEP	
		BTFSC PORTB,0
		MOVLW PORTB;
		ANDLW 03H
		BTFSC


COUNTUP	



COUNTDN

END