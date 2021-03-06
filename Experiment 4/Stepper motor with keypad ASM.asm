LIST P=16F84A, F=INHX8M
INCLUDE<P16F84.INC>
__CONFIG 3FF9H



DUMMY EQU 11H
COUNTER EQU 12H
IHAP EQU 13H
LOOP EQU 14H
COUNTCW EQU 15H
COUNTCCW EQU 16H


ORG 0
GOTO INIT
ORG 4
GOTO INT_ROUTINE


INIT
BSF STATUS, RP0
MOVLW 1FH
MOVWF TRISB
CLRF TRISA
BSF INTCON, GIE
BSF INTCON, T0IE
MOVLW 04H
MOVWF OPTION_REG
BCF STATUS, RP0
MOVLW 00H
MOVWF PORTB
MAIN
BCF PORTA, 0
BTFSS PORTB, 4
GOTO MAIN
MOVLW 0FH
ANDWF PORTB, W
CALL KEYPAD
MOVWF DUMMY
MOVLW D'15'
CALL DELAY
MOVLW 00H
XORWF DUMMY
BTFSC STATUS, Z
GOTO MAIN
BSF PORTA, 0
MOVLW D'25'
MOVWF LOOP
BTFSS DUMMY, 0
GOTO CCW
GOTO CW



CCW MOVLW D'25'
MOVWF LOOP
BSF STATUS, RP0
MOVLW 0FH
MOVWF TRISB
BCF STATUS, RP0
MOVLW 03H
MOVWF PORTA
CCW2

MOVLW D'5'
MOVWF IHAP
AB	DECF IHAP
MOVFW IHAP
CALL STEP
MOVWF PORTB
MOVLW D'10'
CALL DELAY
MOVLW 01H
XORWF IHAP, W
BTFSS STATUS, Z
GOTO AB
MOVLW D'5'
MOVWF IHAP
DECFSZ LOOP, F
GOTO AB
MOVLW D'62'
CALL DELAY
DECFSZ DUMMY, F
GOTO CCW
GOTO INIT


CW	MOVLW D'25'
MOVWF LOOP
BSF STATUS, RP0
MOVLW 0FH
MOVWF TRISB
BCF STATUS, RP0
MOVLW 03H
MOVWF PORTA
CW2	MOVLW D'0'
MOVWF IHAP
CD	INCF IHAP
MOVFW IHAP
CALL STEP
MOVWF PORTB
MOVLW D'10'
CALL DELAY
MOVLW 04H
XORWF IHAP, W
BTFSS STATUS, Z
GOTO CD
CLRF IHAP
DECFSZ LOOP, F
GOTO CD
MOVLW D'62'
CALL DELAY
DECFSZ DUMMY, F
GOTO CW
GOTO INIT




STEP	ADDWF PCL, F
NOP
RETLW 30H
RETLW 60H
RETLW 0C0H
RETLW 90H
RETURN


KEYPAD	ADDWF PCL, F
RETLW 01H
RETLW 02H
RETLW 03H
RETLW 00H
RETLW 04H
RETLW 05H
RETLW 06H
RETLW 00H
RETLW 07H
RETLW 08H
RETLW 09H
RETLW 00H
RETLW 00H
RETLW 00H
RETLW 00H
RETLW 00H
RETURN



DELAY: MOVWF COUNTER
DELAY2 MOVLW 00H
  XORWF COUNTER, W
  BTFSS STATUS, Z
  GOTO DELAY2
  RETURN




INT_ROUTINE
BCF INTCON, T0IF
DECF COUNTER, F


RETFIE


END