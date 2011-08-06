#include<pic.h>

void delay(int num);

void main() {
int a;
__CONFIG(0x3FF9);

OPTION=0x10;
TRISB=0X00;

while(1){
	for(a=0;a<=9;a++) {
		PORTB=a;
		delay(20);
	}

}

}

void delay(int num){
int x, y;
for(x=num; x>=0;x--) {
for(y=1000;y>=0;y--) {}
}

}