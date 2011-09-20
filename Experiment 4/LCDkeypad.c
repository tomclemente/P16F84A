#include<pic.h>


unsigned char keypad[16]={'1','2','3',0x00,'4','5','6',0x00,'7',
'8','9',0x00,'*','0','#',0x00};
void sendData(unsigned char data);
void initPC();
void initlcd();
void sendInst(unsigned char inst);
void delay(int num);
static bit Tflag, flag1=0, flag2=0, flag3=0, flag4=0;
void interrupt INT_rtn();


int dummy, value, counter=0;
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


PORTA=0X0F;
delay(2);
PORTA=0x0B;
delay(2);
PORTA=0X0A;
//TRISB=0X1F;
} 


void sendInst(unsigned char inst) {
//TRISB=0X00;
PORTB=inst;


PORTA=0X0D;
delay(2);
PORTA=0x09;
delay(2);
PORTA=0X08;
//TRISB=0X1F;
}


void main() {


__CONFIG(0x3FF9);
OPTION=0x04;
GIE=1;
T0IE=1;	delay(15);
PORTB=0;
PORTA=0;	delay(15);
TRISB=0X00; delay(15);
TRISA=0X00;delay(15);



sendInst(0x38); // function set
delay(15);
PORTB=0;
 	delay(15);


while(1) {

TRISB=0x1F;
PORTB=0;
PORTA=0;


if(RB4) {


dummy=(PORTB&0x0F);
value=keypad[(PORTB&0x0F)];


PORTA=0X08;

TRISB=0X00;
//	sendInst(0x01);
sendInst(0x0C);
sendInst(0x0F);
sendInst(0x06);	//increment cursor, display shift

//	sendInst(0xC0); //address
//	sendInst(0x18); //shift ryt

sendData(value);
counter=counter+1;
if(counter==20 && flag3==0) {
sendInst(0xC0);
counter=0;
flag1=1;
flag3=1;

}
if(counter==20 && flag1==1){
sendInst(0x94);
flag1=0;
flag2=1;
counter=0;
}
if(counter==20 && flag2==1){
sendInst(0xD4);
flag2=0;
flag3=1;
counter=0;
flag4=1;
}
if(counter==21 && flag4==1) {
sendInst(0x01);
flag4=0;
flag3=0;
counter=0;
}
//PORTA=0X05;
//delay(20);
//TRISB=0X00;
//PORTA=0X01;


PORTA=0x00;
TRISB=0x1F;
PORTB=0;
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


while(num) {
if(Tflag){
num--;
Tflag=0;
}


}
GIE=1;

}