#include<pic.h>

void delay(int num);
void interrupt INT_rtn();
unsigned char keypad[16]={0x01,0x02,0x03,0x00,0x04,0x05,0x06,0x00,0x07,0x08,0x09,0x00,0x00,0x00,0x00,0x00};

static bit Tflag;

void interrupt INT_rtn(){
	GIE=0;
	if(T0IF){
		T0IF=0;
		Tflag=1;
	}
}

void delay(int num){

	while(num>0) {
		if(Tflag){
		num--;
		Tflag=0;
		}

	}
	
}
void main(){
__CONFIG(0x3FF9);

OPTION=0x04;
GIE=1;
T0IE=1;
TRISA=0X00;

TRISB=0X1F;
PORTB=0X00;
int value,dummy;

	while(1) {
		TRISB=0x1F;
		TRISA=0x00;
		PORTA=0;
		PORTA=0X00;
		if(RB4==1) {
		
	
			dummy=(PORTB&0x0F);
			value=keypad[dummy];
	
			PORTB=value;
			PORTA=0X05;
			delay(20);
			TRISB=0X00;
			PORTA=0X01;
			delay(10);
		}

	}


}