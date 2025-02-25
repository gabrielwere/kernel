#include "screen.h"
#include "ports.h"

unsigned int get_cursor_position(){

	unsigned int cursor_position;

	port_byte_out(SCREEN_REG_CTRL,HIGH_BYTE);
	cursor_position = port_byte_in(SCREEN_REG_DATA) << 8;

	port_byte_out(SCREEN_REG_CTRL,LOW_BYTE);
	cursor_position += port_byte_in(SCREEN_REG_DATA);

	cursor_position *= 2;

	return cursor_position;
}

void set_cursor_position(unsigned int cursor_position){

	cursor_position /= 2;

	port_byte_out(SCREEN_REG_CTRL,HIGH_BYTE);
	port_byte_out(SCREEN_REG_DATA,(unsigned char)((cursor_position >> 8) & 0xff));

	port_byte_out(SCREEN_REG_CTRL,LOW_BYTE);
	port_byte_out(SCREEN_REG_DATA,(unsigned char)(cursor_position & 0xff));

}

unsigned int cursor_offset(unsigned int row,unsigned int column){

	return 2 * (row * MAX_COLS + column);

}

unsigned int get_row(unsigned int offset,unsigned int col){

	offset /= 2;
	return (offset - col) / MAX_COLS;
}

unsigned int print_char(unsigned char character){

	unsigned int cursor;

	cursor = get_cursor_position();

	unsigned char *vga_address = (unsigned char *)VGA_ADDRESS;
  
	if(character == '\n'){

		unsigned int row = get_row(cursor,0);
		cursor = cursor_offset(row + 1,0);

	}else{

		vga_address[cursor] = character;
		vga_address[cursor + 1] = WHITE_ON_BLACK;
		cursor += 2;
	}

	set_cursor_position(cursor);
	return cursor;

}

void print(unsigned char *word){

	int i = 0;

	while(word[i] != '\0'){
		print_char(word[i]);
		i++;
	}

}
