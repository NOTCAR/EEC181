#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void VGA_text(int x, int y, char * text_ptr){
	int offset;
	
	volatile char * character_buffer = (char *) 0xC4004000;
	
	offset = (y << 7) + x;
	while ( *(text_ptr) ) {
			*(character_buffer + offset) = *(text_ptr);
			++text_ptr;
			++offset;
	}
}

void VGA_box(int x1, int y1, int x2, int y2, short pixel_color){
	int offset, row, col;
	
	volatile short * pixel_buffer = (short *) 0xC0000000;
	
	for(row = y1; row <= y2; row++){
		for(col = x1; col <= x2; ++col){
			offset = (row << 9) + col;
			*(pixel_buffer + offset) = pixel_color;
		}
	}
}

int main(void){
	volatile int * hex5_0busaddr = (int *) 0xFF200010; //red LED addres
	volatile int * switches = (int *) 0xFF200020; //red LED addres
	volatile int * pushptr = (int *) 0xFF200000;
	volatile int * led = (int *) 0xFF200030;
	
	char box1[20] = "Red = Box 1\0";
	char box2[20] = "Blue = Box 2\0";
	char box3[50] = "KEY3:LEFT  KEY2:DOWN  KEY1:UP  KEY0:RIGHT\0";
	int x = 0;
	int y = 0;
	int i, j;
	int p1time, p2time;
	int flagx = 1;
	int flagy = 1;
	int button;
	int leds;
	int switchy;
	int push;
	int temptime = 0x0;
	int temp=1;
	int rx, ry, bx, by, rxi, ryi, bxi, byi;
	int flag = 0;
	int pushflag=0;
	int done = 0;
	int pushhold;
	int p1done=0; 
	int p2done=0;
	int count = 0;
	int count1=0;
	int count2=0;
	int count3=0;
	int temptime1=0;
	int temptime2=0;
	int randomflag = 1;
	time_t t;
	srand((unsigned)time(&t));

	switchy = *(switches);
	*(hex5_0busaddr) = temptime;
	rxi = 60;//rand()%300;
	ryi = 60;//rand()%200;
	bxi = 35;
	byi = 60;
	while (randomflag){
	rxi= rand() % (300 - 10) + 10;
	bxi= rand() % (300 - 10) + 10;
	ryi= rand() % (210 - 10) + 10;
	byi= rand() % (210 - 10) + 10;
	if (((rx >= bx-20 && rx <= bx+20) && (ry >= by-20 && ry <= by+20))==0){
	randomflag=0;}
	}
	rx = rxi;
	ry = ryi;
	bx = bxi;
	by = byi;
	VGA_box(0*4-2, 0*4, 80*4+1, 80*4, 0x0000);
	VGA_text(0, 1, box1);
	VGA_text(0, 3, box2);
	VGA_text(0, 5, box3);
	VGA_box(rx, ry, rx+20, ry+20, 0x7800);
	VGA_box(bx, by, bx+20, by+20, 0x000F);

	while(1){
	switchy = *(switches);
	if (switchy==0x1 && p2done != 1){ //redbox is moving
		while (p1done == 0 || p2done == 0){
			i++;
			if (i==425000 && p1done==0){
			  if (count3!=9 || count2!=9 || count1!=9){
			  count1++;
			  if (count1 == 10){
			  count2++;
			  count1=0;}
			  if (count2==10){
			  count3++;
			  count2=0;}
			  temptime1=(count3*256 + count2*16 + count1);

			  *(hex5_0busaddr) = temptime1 +temptime2;
			}
			}
			if (i==425000 && p1done==1){

			 if (count3!=9 || count2!=9 || count1!=9){
			  count1++;
			  if (count1 == 10){
			  count2++;
			  count1=0;}
			  if (count2==10){
			  count3++;
			  count2=0;}
			  temptime2=(count3*1048576 + count2*65536 +count1*4096);
			  *(hex5_0busaddr) = temptime1 + temptime2;
			}
			}
			
			push = *pushptr; // < v ^ >
			if (push == 0x8 && pushflag==0){ //move left
				VGA_box(rx, ry, rx+20, ry+20, 0x0000);
				if (rx >0){
				rx = rx -3;
				}
				VGA_box(rx, ry, rx+20, ry+20, 0x7800);
				pushflag=1;
			}
			else if (push == 0x4 && pushflag==0){ //move down
				VGA_box(rx, ry, rx+20, ry+20, 0x0000);
				if (ry < 240){
				ry = ry + 3;
				}
				VGA_box(rx, ry, rx+20, ry+20, 0x7800);
				pushflag=1;
			}
			else if (push == 0x2 && pushflag==0){ //move up
				VGA_box(rx, ry, rx+20, ry+20, 0x0000);
				if (ry > 0){
				ry = ry - 3;
				}
				VGA_box(rx, ry, rx+20, ry+20, 0x7800);
				pushflag=1;
			}
			else if (push == 0x1 && pushflag==0){ //move right
				VGA_box(rx, ry, rx+20, ry+20, 0x0000);
				if (rx < 320){
				rx = rx + 3;
				}
				VGA_box(rx, ry, rx+20, ry+20, 0x7800);
				pushflag=1;
			}
			if (pushflag=1){
			 if (push==0){
			   pushflag=0;
			 }
			}
			if (p1done==0 && (rx >= bx-20 && rx <= bx+20) && (ry >= by-20 && ry <= by+20)){
			  p1done = 1;
			  rx = rxi;
			  ry = ryi;
			  bx = bxi;
			  by = byi;
			  count1=0;
			  count2=0;
			  count3=0;
			  VGA_box(0*4-2, 0*4, 80*4+1, 80*4, 0x0000);
			  VGA_box(rx, ry, rx+20, ry+20, 0x7800);
			  VGA_box(bx, by, bx+20, by+20, 0x000F);
			}
			  if(p1done == 1 && ((rx >= bx-20 && rx <= bx+20) && (ry >= by-20 && ry <= by+20))){
			    p2done = 1;
			    rx = rxi;
			    ry = ryi;
			    bx = bxi;
			    by = byi;
			    VGA_box(0*4-2, 0*4, 80*4+1, 80*4, 0x0000);
			    VGA_box(rx, ry, rx+20, ry+20, 0x7800);
			    VGA_box(bx, by, bx+20, by+20, 0x000F);
			  }
			
		if(i == 425000)
		{
		  i = 0;}
		}
		p1time = temptime1;
		p2time = temptime2;
		p2time = p2time / 4096;
		if (p1time < p2time) {
		*led=0x3C;  
		}
		if (p2time < p1time) {
		*led=0x3C0;  
		}
		if (p1time == p2time) {
		*led=0x3FF;  
		}
	}
	
	else if (switchy == 0x2 && p2done != 1){ //bluebox is moving
	while (p1done == 0 || p2done == 0){
			i++;
			if (i==425000 && p1done==0){
			  if (count3!=9 || count2!=9 || count1!=9){
			  count1++;
			  if (count1 == 10){
			  count2++;
			  count1=0;}
			  if (count2==10){
			  count3++;
			  count2=0;}
			  temptime1=(count3*256 + count2*16 + count1);

			  *(hex5_0busaddr) = temptime1 +temptime2;
			}
			}
			if (i==425000 && p1done==1){

			 if (count3!=9 || count2!=9 || count1!=9){
			  count1++;
			  if (count1 == 10){
			  count2++;
			  count1=0;}
			  if (count2==10){
			  count3++;
			  count2=0;}
			  temptime2=(count3*1048576 + count2*65536 +count1*4096);
			  *(hex5_0busaddr) = temptime1 + temptime2;
			}
			}
			push = *pushptr; // < v ^ >
			if (push == 0x8 && pushflag==0){ //move left
				VGA_box(bx, by, bx+20, by+20, 0x0000);
				if (bx >0){
				bx = bx - 3;
				}
				VGA_box(bx, by, bx+20, by+20, 0x000F);
				pushflag=1;
			}
			else if (push == 0x4 && pushflag==0){ //move down
				VGA_box(bx, by, bx+20, by+20, 0x0000);
				if (by < 240){
				by = by + 3;
				}
				VGA_box(bx, by, bx+20, by+20, 0x000F);
				pushflag=1;
			}
			else if (push == 0x2 && pushflag==0){ //move up
				VGA_box(bx, by, bx+20, by+20, 0x0000);
				if (by > 0){
				by = by - 3;
				}
				VGA_box(bx, by, bx+20, by+20, 0x000F);;
				pushflag=1;
			}
			else if (push == 0x1 && pushflag==0){ //move right
				VGA_box(bx, by, bx+20, by+20, 0x0000);
				if (bx < 320){
				bx = bx + 3;
				}
				VGA_box(bx, by, bx+20, by+20, 0x000F);
				pushflag=1;
			}
			if (pushflag=1){
			 if (push==0){
			   pushflag=0;
			 }
			}
			if (p1done==0 && (rx >= bx-20 && rx <= bx+20) && (ry >= by-20 && ry <= by+20)){
			  p1done = 1;
			  rx = rxi;
			  ry = ryi;
			  bx = bxi;
			  by = byi;
			  count1=0;
			  count2=0;
			  count3=0;
			  VGA_box(0*4-2, 0*4, 80*4+1, 80*4, 0x0000);
			  VGA_box(rx, ry, rx+20, ry+20, 0x7800);
			  VGA_box(bx, by, bx+20, by+20, 0x000F);
			}
			  if(p1done == 1 && ((rx >= bx-20 && rx <= bx+20) && (ry >= by-20 && ry <= by+20))){
			    p2done = 1;
			    rx = rxi;
			    ry = ryi;
			    bx = bxi;
			    by = byi;
			    VGA_box(0*4-2, 0*4, 80*4+1, 80*4, 0x0000);
			    VGA_box(rx, ry, rx+20, ry+20, 0x7800);
			    VGA_box(bx, by, bx+20, by+20, 0x000F);
			  }
			
		if(i == 425000)
		{
		  i = 0;}
		}
		p1time = temptime1;
		p2time = temptime2;
		p2time = p2time / 4096;
		if (p1time < p2time) {
		*led=0x3C;}
		if (p2time < p1time) {
		*led=0x3C0;}
		if (p1time == p2time) {
		*led=0x3FF;}
		}
	}
}