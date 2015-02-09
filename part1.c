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

	char text_top_row[50] = "Julian Lin\0";
	char text_bottom_row[50] = "Matthew Song\0";
	char moving[50] = "Hello\0";
	char blank[50] ="       ";
	int x = 0;
	int y = 0;
	int i, j;
	int flagx = 1;
	int flagy = 1;
	
	VGA_text(30, 29, text_top_row);
	VGA_text(30, 30, text_bottom_row);
	VGA_box(0*4-2, 0*4, 80*4+1, 80*4, 0xf800);
	VGA_box(25*4-2, 24*4, 50*4+1, 36*4, 0x07E0);
	while(1){
	VGA_text(x, y, blank);
	if(x == 0 || (x == 50 && y < 36 && y > 23 )){
		flagx = 1;}
	if(y == 0 || (y == 36 && x < 52 && x > 19 )){
		flagy = 1;}
	if(x ==  (600/8) || (x == 19 && y < 36 && y > 23 )){
		flagx = 0;}
	if(y == (480/8) || (y == 23 && x < 52 && x > 19 )){
		flagy = 0;}
	if(flagx == 0){
		x--;}
	if(flagx == 1){
		x++;}
	if(flagy == 0){
		y--;}
	if(flagy == 1){
		y++;}
	VGA_text(x, y, moving);
	for(j = 0; j < 100000; j++){}
	}
	while(1)
	return 0;
}