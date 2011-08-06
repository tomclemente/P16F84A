#include<pic.h>
void sendData(unsigned char data);
void sendInst(unsigned char inst);
void delay(int num);

void initPC() {
__CONFIG(0x3FF5);
OPTION=0x0E;
TRISB=0X00;
TRISA=0X03;
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
	PORTB=data;
	asm("sleep");
	PORTA=0X0C;
	asm("sleep");
	PORTA=0X08;
} 

void sendInst(unsigned char inst) {
	PORTB=inst;
	asm("sleep");
	PORTA=0X04;
	asm("sleep");
	PORTA=0X00;
}

 main() {
int m;
	initPC();
	initlcd();

	if(RA0==0) {
		
		sendInst(0x01);
		sendInst(0x0C);
		//sendInst(0x0f);
		for(m=0; m<=5; m++) {
			sendInst(0x06);	//increment cursor, display shift
			sendInst(0xC0); //address
			sendInst(0x18); //shift ryt
			sendData('t');
			sendData('o');
			sendData('m');
			
		}
		for(m=0; m<=6; m++) {
			sendInst(0x06);	//increment cursor, display shift
			sendInst(0xC0); //address
			sendInst(0x1F); //shift ryt
			sendData('t');
			sendData('o');
			sendData('m');
			
		}

		


		
		mana();
	}
		



}

void delay(int num) {
int x,y;
for(x=num; x>=0; x--){
	for(y=2; y>=0; y--) {}}

}

mana() {
for(;;) 
{}


}