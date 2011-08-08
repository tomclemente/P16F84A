#include<pic.h>
void interrupt INT_rtn();
void left(int num);
void right(int num);
static bit flag;
unsigned char val[7]={0x02,0x04,0x08,0x10,0x20,0x40,0x80};
int x;

void interrupt INT_rtn(){
GIE = 0;
	if(INTF){
	INTF=0;
	flag=1;
	}
}

main() {
__CONFIG(0x3FF5);
OPTION=0x4D;
TRISB=0x01;
INTE=1;
GIE=1;
flag=0;
PORTB=0x00;
int a=0;
	while(1){
				if(flag){
				flag=0;
				a++;
				if((a%2)==0){
				right(6);
				}
				else {
			    left(6);
	
				}
				flag=0;
			}
		}
}
void left(int num){
	for(x=0;x<=num;x++){
	PORTB=val[x];
 	asm("sleep");
	}
}

void right(int num){
	for(x=num;x>=0;x--){
	PORTB=val[x];
 	asm("sleep");
	}
}