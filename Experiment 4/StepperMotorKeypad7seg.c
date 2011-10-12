#include<pic.h>

void delay(int num);
void interrupt INT_rtn();
unsigned char keypad[16]={0x01,0x02,0x03,0x00,0x04,0x05,0x06,0x00,0x07,0x08,0x09,0x00,0x00,0x00,0x00,0x00};
unsigned char step2[4]={0x30,0x60,0xC0,0x90};
void initPIC();
static bit Tflag;
int x;
int value,dummy,count;
void stepper(int num);

void interrupt INT_rtn(){

	if(T0IF){
		T0IF=0;
		Tflag=1;
	}
}
void initPIC(){
__CONFIG(0x3FF9);

OPTION=0x04;
GIE=1;
T0IE=1;
TRISA=0X00;
TRISB=0X1F;
PORTB=0X00;


}

void main(){
	initPIC();

	while(1) {
		TRISB=0x1F;	
		PORTA=0;
		if((RB4==1) && (PORTB==0x1E)) {
		PORTB=0;
		TRISB=0X00;
		PORTA=0X01;
		stepper(value);

		}	
			
		else if(RB4) {
			value=keypad[PORTB&0x0F];
			delay(15);
			PORTB=value;
			PORTA=0X03;
			TRISB=0X00;
			PORTA=0X01;
		}
		

	}


}

void stepper(int num){
		PORTA=0x05;
		count=0;
		PORTB=count;
		RA1=1;
		dummy=num;
			while(num) {
			num--;
			RA1=0;
				if((dummy%2)==0){					
						for(x=0;x<=100;x++)	{
						PORTB=step2[x%4];
						delay(15);	}
				}
				else {
					for(x=100;x>=0;x--){
					PORTB=step2[x%4];
					delay(15);	}
				}
			
				if(count<=dummy+1) {
				count++;
				PORTB=count;
				RA1=1;
				}
				RA1=0;
			}
	
	

}


void delay(int num){
	while(num) {
		if(Tflag){
		num--;
		Tflag=0;
		}

	}
	
}
