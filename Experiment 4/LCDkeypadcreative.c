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
unsigned char name[] = {"Hello World!"};
void shift(); 
int x,y=5;
unsigned char count; 
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
	sendInst(0x01); //clear display
	sendInst(0x0c); //cursor display shift
	sendInst(0x06); //entry mode
}
 
 
void sendData(unsigned char data) {

	PORTB=data;	 
	PORTA=0X0F;
	delay(2);
	PORTA=0x0B; 
	delay(2);
	PORTA=0X0A;

} 
 
 
void sendInst(unsigned char inst) {

	PORTB=inst;	 
	PORTA=0X0D;
	delay(2);
	PORTA=0x09;
	delay(2);
	PORTA=0X08;

}
 
 
void main() {
	initPC(); 
	initlcd();
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
			
	

		 if(value=='1') {
			sendInst(0x01); 
			sendInst(0x0C);
  			sendInst(0x82);
			for(x = 0; x <=11; x++)
     		sendData(name[x]);
			   while(y) {
				  y--;
				  	if(y==3) {
					sendInst(0x01);
					sendInst(0xC2);
					for(x = 0; x <=11; x++)
     				sendData(name[x]);
			    	}
				
					if(y==1) {
						sendInst(0x01);
					sendInst(0x96);
					for(x = 0; x <=11; x++)
     				sendData(name[x]);
			    	}

				

					  	
				  sendInst(0x0B);
			      delay(20);
			      sendInst(0x0F);
			      delay(20);
			   }
			  y=5;
		}
		
		if(value=='2') {
		 sendInst(0x01);
  		 sendInst(0x95);
  		 for(x = 0; x < 12; x++)
  		   	sendData(name[x]);
		   for(x = 0; x < 30; x++)
		   {     
		      if( x < 15)
		      sendInst(0x1F);
		      else
		      sendInst(0x1B);
		      delay(10);
		   }
		
	

		}
		if(value=='3') {
		sendInst(0x01);
		sendInst(0x03);
		

		}

		if(value=='4') {	
		delay(20);
		sendInst(0x0F);
		sendInst(0x13);
	
		}
		if(value=='5') {
		 sendInst(0x01);
		   if(count == 4)
		     count = 0;
		   if(count == 0)
		     sendInst(0x87);
		   else if(count == 1)
		     sendInst(0xC7);
		   else if(count == 2)
		     sendInst(0x9B);
		   else if(count == 3)
		     sendInst(0xDB);
		   for(x = 0; x < 5; x++)
		     sendData(name[x]);
		   count++;

		}

		if(value=='6') {
		delay(20);
		sendInst(0x0F);
		sendInst(0x17);

		}
		if(value=='7' || value=='8' || value=='9') {
		delay(15);
		sendData(value);

		}
	

		
		
		 
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
