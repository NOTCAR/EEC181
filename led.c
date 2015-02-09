int main (void)
{
volatile int * led = (int *) 0xFF200040; //red LED address
volatile int * switchptr = (int *) 0xFF200030; //SW slider switch address
volatile int * hex3_hex0addr = (int *) 0xFF200020; //red LED addres
volatile int * hex5_hex4addr = (int *) 0xFF200010; //red LED addres
volatile int * push = (int *) 0xFF200000;

int custom=0;
int switch_value;
int hex5_hex4, hex3_hex0;
int button;
int stallvalue = 100000;
int mode=0;

enum states {
	S0,
	S1,
	S2,
	S3,
	S4,
	S5,
	S6,
	S7,
	S8,
	S9,
	S10,S11,S12,S13,S14,S15,S16,S17, Z0, Z1, Z2, Z3,Z4,Z5};
enum states state = S0;

while(1)
{

	button = *(push);
	switch_value = *(switchptr); //load values from switches to switch_value
	*(led) = switch_value; //put values from switches to led address
	if(button == 0x8){
		while(button == 0x8){
		button=*(push);}
		while(1){
		if (mode==0){ //switches between helloworld and custom
			mode = 1; //hello world to custom
			state= Z0;
			break;
		}
		if (mode==1){
			mode =0; //custom mode to hello
			state =S0;
			break;
		}}
}
	

	*(hex3_hex0addr) = hex3_hex0;
	*(hex5_hex4addr) = hex5_hex4;
	//int x = 1;
	switch(state){
case S0: 
	hex5_hex4 = 0x0000;
	hex3_hex0 = 0x00000000;
	state = S1;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S1: 
	hex5_hex4 = 0x0000;
	hex3_hex0 = 0x00000076;
	state = S2;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S2: 	
	hex5_hex4 = 0x0000;
	hex3_hex0 = 0x00007679;
	state = S3;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S3: 	
	hex5_hex4 = 0x0000;
	hex3_hex0 = 0x00767938;
	state = S4;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S4: 	
	hex5_hex4 = 0x0000;
	hex3_hex0 = 0x76793838;
	state = S5;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S5:	
	hex5_hex4 = 0x0076;
	hex3_hex0 = 0x7938383f;
	state = S6;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S6: 	
	hex5_hex4 = 0x7679;
	hex3_hex0 = 0x38383f00;
	state = S7;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S7: 	
	hex5_hex4 = 0x7938;
	hex3_hex0 = 0x383f003e;
	state = S8;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S8: 	
	hex5_hex4 = 0x3838;
	hex3_hex0 = 0x3f003e3e;
	state = S9;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S9: 	
	hex5_hex4 = 0x383f;
	hex3_hex0 = 0x003e3e3f;
	state = S10;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S10: 	
	hex5_hex4 = 0x3f00;
	hex3_hex0 = 0x3e3e3f31;
	state = S11;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S11: 	
	hex5_hex4 = 0x003e;
	hex3_hex0 = 0x3e3f3138;
	state = S12;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S12: 	
	hex5_hex4 = 0x3e3e;
	hex3_hex0 = 0x3f31385e;
	state = S13;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S13: 	
	hex5_hex4 = 0x3e3f;
	hex3_hex0 = 0x31385e00;
	state = S14;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S14: 	
	hex5_hex4 = 0x3f31;
	hex3_hex0 = 0x385e0000;
	state = S15;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S15: 	
	hex5_hex4 = 0x3138;
	hex3_hex0 = 0x5e000000;
	state = S16;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S16: 	
	hex5_hex4 = 0x385e;
	hex3_hex0 = 0x00000000;
	state = S17;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case S17: 	
	hex5_hex4 = 0x3800;
	hex3_hex0 = 0x00000000;
	state = S0;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case Z0: 	
	hex5_hex4 = 0x0000;
	hex3_hex0 = custom;
	state = Z1;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case Z1: 	
	hex5_hex4 = 0x0000;
	hex3_hex0 = custom*16*16;
	state = Z2;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case Z2: 	
	hex3_hex0 = custom*16*16*16*16;
	state = Z3;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case Z3: 	
	hex5_hex4 = custom/(16*16);
	hex3_hex0 = custom*16*16*16*16*16*16;
	state = Z4;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case Z4: 	
	hex5_hex4 = custom;
	hex3_hex0 = 0x0;
	state = Z5;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
case Z5: 	
	hex5_hex4 = custom*16*16;
	hex3_hex0 = custom/(16*16);
	state = Z0;
	stallvalue=stall(button, stallvalue, &(custom));
	break;
	}
}}


int stall(int button, int stallvalue,  int * custom2){
	int i;
	int pauseflag = 0;
	int derp;
	int custom1;
	int pausepush;
	int switch_value;
	int *cusptr = custom2;
	volatile int * led = (int *) 0xFF200040; //red LED address
	volatile int * switchptr = (int *) 0xFF200030; //SW slider switch address
	volatile int * push = (int *) 0xFF200000;
	derp = stallvalue;
	if(button == 0x0){
		for(i = 0; i < derp; i++){}}
	else{
	for(i = 0; i < (derp); i++){
	if(button == 0x4){
		while (button==0x4){
		button= *(push);}
		stallvalue = stallvalue/2;}
	if(button == 0x2){
		while (button==0x2){
		button = *(push);}

		stallvalue = stallvalue*2;
		}
	if(pauseflag == 0){
		if(button == 0x1){
		pauseflag= 1;}}
	while (pauseflag){
		button = *(push);
		if (button == 0x0){
			while (button==0x0){
			button = *(push);
			switch_value = *(switchptr); //load values from switches to switch_value
			*(led) = switch_value; //put values from switches to led address			
			if (button == 0x1){
			while (button == 0x1){
			button = *(push);}
			pauseflag = 0;
		int temp = switch_value;
		custom1 = 0;
		if(switch_value > 0x1FF){
		temp =temp- 0x200;
		custom1 = custom1 + 0x200;
		
		}
		if(temp > 0xFF){
		temp = temp - 0x100;
		custom1 = custom1 + 0x100;
		
		}
		if(temp > 0x7F){
		temp = temp - 0x80;
		custom1 = custom1 + 0x80;
		
		}
		custom1 = 2*(custom1) +temp;
		//custom1 = 0xFF;
		*(cusptr)= custom1;
			break;
			
			}}}}
	}
	}
	return stallvalue;
}
