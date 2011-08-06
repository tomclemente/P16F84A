#include<pic.h>

void delay(int num);
void interrupt INT_rtn();
void CW(int step);
void CCW(int step);
static bit flag;

void interrupt INT_rtn(){
GIE = 0;
	if(INTF){
	INTF=0;
	flag=1;

	}

}

void CW(int step){
unsigned char CWval[4]={0x03,0x06,0x0C,0x11};
int x;
	for(x=step;x>=0;x--){
	PORTB=CWval[x%4];
	delay(1);

	}

}

void CCW(int step){
unsigned char CCWval[4]={0x11,0x0C,0x06,0x03};
int x;
	for(x=step;x>=0;x--){
	PORTB=CCWval[x%4];
	delay(1);
	}


}

void delay(int num){
int x,y;
	for(x=num;x>=0;x--){
		for(y=1;y>=0;y--) {}

	}


}

void main(){
__CONFIG(0x3FF9);
OPTION=0x10;

TRISB=0x01;
INTE=1;
GIE=1;
flag=0;

	while(1){
		if(flag){
		flag=0;
		CW(200);
		delay(100);
		CCW(200);
		delay(100);

		}

	}

}