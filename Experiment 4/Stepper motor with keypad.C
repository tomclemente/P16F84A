#include<pic.h>

void delay();
void halfdelay();
void latch();
void interrupt INT_rtn();
void CW(int step);
void CCW(int step);
static bit flag;
unsigned char keypad[16]={0x01,0x02,0x03,0x00,0x04,0x05,0x06,0x00,0x07,0x08,0x09,0x00,0x00,0x00,0x00,0x00};
unsigned char CCWval[4]={0x30,0x60,0xC0,0x90};
unsigned char CWval[4]={0x90,0xC0,0x60,0x30};

void interrupt INT_rtn(){
	GIE=0;
	if(T0IF){
		T0IF=0;
		flag=1;
	}
}

void CW(int step){


	TRISB=0x0F;
	int x;
	for(x=step;x>=0;x--){
	PORTA=0x03;
	PORTB=CWval[x%4];

	halfdelay();
	PORTA=0x01;

	}
}
void latch(){


}
void CCW(int step){

	TRISB=0x0F;
	int x;
	for(x=step;x>=0;x--){
	PORTA=0x03;
	PORTB=CCWval[x%4];

	halfdelay();
	PORTA=0x01;
	}
}


void delay(){
	int x=122;
	
//	TMR0 = 0;
	for(;;){
		if(flag==1){
			while(x>0){ //122 ni hap	
				x--;
				flag=0;
				break;	
			}
		}
		if(x==0)
			break;
	}
	
}

void halfdelay(){
	int x=19;


	for(;;){
		if(flag==1){
			while(x>0){ //122 ni hap	
				x--;
				flag=0;
				break;	
			}
		}
		if(x==0)
			break;
	}

}

void main(){
__CONFIG(0x3FF9);

OPTION=0x04;
TRISB=0x1F;
TRISA=0X00;
T0IE=1;
GIE=1;
flag=0;

PORTB=0;
PORTA=0;
int dummy,c,value;
//unsigned char keypad[16]={0x01,0x02,0x03,0xff,0x04,0x05,0x06,0xff,0x08,0x09,0x0A,0xff,0x0C,0x0D,0x0E,0xff};
	while(1) {
	RA0=0;

	TRISB=0x1F;
	
		if(RB4==1) {
		dummy=(PORTB&0x0F);
		value=keypad[dummy];
		delay();
		RA0=1;
	
		delay();
	
			if((value%2)==0){
				value=value*100;
			CCW(value);
			}
			else {
				value=value*100;
			CW(value);
			}
		}	
	}
}


