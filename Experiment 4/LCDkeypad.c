#include<pic.h>
void sendData(unsigned char data);
void initPC();
void initlcd();
void sendInst(unsigned char inst);
void delay(int num);
static bit Tflag;
void interrupt INT_rtn();
unsigned char keypad[16]={0x01,0x02,0x03,0x00,0x04,0x05,0x06,0x00,0x07,0x08,0x09,0x00,0x00,0x00,0x00,0x00};

void initPC() {
__CONFIG(0x3FF9);
OPTION=0x04;
GIE=1;
T0IE=1;
TRISB=0X00;
TRISA=0X00;
PORTB=0;


}
void initlcd() {
	PORTB=0;
	sendInst(0x38); // function set	
//	sendInst(0x01); //clear display
//	sendInst(0x0f); //cursor display shift
//	sendInst(0x06); //entry mode
}

void sendData(unsigned char data) {
	//TRISB=0X00;
	PORTB=data;
//	delay(35);
	PORTA=0X0F;
	delay(35);
	PORTA=0X0A;
	//TRISB=0X1F;
} 

void sendInst(unsigned char inst) {
	//TRISB=0X00;
	PORTB=inst;
//	delay(35);
	PORTA=0X0D;
	delay(35);
	PORTA=0X08;
	//TRISB=0X1F;
}

main() {
	int dummy, value;
	initPC();

	initlcd();
	PORTA=0x00;
		while(1) {
		PORTA=0x00;
		delay(10);
		PORTB=0;
		TRISB=0x1F;
		
		
		if(RB4==1) {
			
			delay(15);
			dummy=(PORTB&0x0F);
			value=keypad[dummy];
			delay(25);
			PORTA=0X08;
			delay(10);
			TRISB=0X00;
			delay(10);
			sendInst(0x01);
			sendInst(0x0C);

			sendInst(0x06);	//increment cursor, display shift
			sendInst(0xC0); //address
			sendInst(0x18); //shift ryt
			delay(15);
			sendData(value);
		
			//PORTA=0X05;
			//delay(20);
			//TRISB=0X00;
			//PORTA=0X01;
			delay(20);
		}

	}



}



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