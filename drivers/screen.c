#include "screen.h"
#include "ports.h"

unsigned int get_cursor_position(){

	unsigned int cursor_position;

	port_byte_out(COMMAND_PORT,HIGH_BYTE);
	cursor_position = port_byte_in(DATA_PORT) << 8;

	port_byte_out(COMMAND_PORT,LOW_BYTE);
	cursor_position += port_byte_in(DATA_PORT);

	cursor_position *= 2;

	return cursor_position;
}

void set_cursor_position(unsigned int cursor_position){

	cursor_position /= 2;

	port_byte_out(COMMAND_PORT,HIGH_BYTE);
	port_byte_out(DATA_PORT,(unsigned char)((cursor_position >> 8) & 0xff));

	port_byte_out(COMMAND_PORT,LOW_BYTE);
	port_byte_out(DATA_PORT,(unsigned char)(cursor_position & 0xff));

}

unsigned int cursor_offset(unsigned int row,unsigned int column){

	return 2 * (row * MAX_COLS + column);

}

unsigned int get_row(unsigned int offset,unsigned int col){

	offset /= 2;
	return (offset - col) / MAX_COLS;
}

void frame_buffer_copy(unsigned char *to,unsigned char *from,int no_of_bytes){

	while(no_of_bytes--)
		*to++ = *from++;
}

unsigned int scroll(unsigned int cursor_position){

	//scroll only if the cursor position is greater than the last cell in the vga array
	if(cursor_position < (MAX_ROWS * MAX_COLS * 2))
		return cursor_position;

	unsigned char *vga_address = (unsigned char *)VGA_ADDRESS;

	//copy the each row's bytes to the row below
	//i.e copy row 1 to row 0,row 2 to row 1,row 3 to row 2
	//this means that the upper most row is lost
	int i,j;
	unsigned int current,next;

	for(i = 0;i < MAX_ROWS;i++){
		for(j = 0;j < MAX_COLS;j++){

			if(i == (MAX_ROWS - 1))
				break;

			current = cursor_offset(i,j);
			next = cursor_offset(i + 1,j);

			frame_buffer_copy(vga_address + current,vga_address + next,2);
		}
	}

	//blank out the last line
	unsigned int last_line_address = cursor_offset(MAX_ROWS - 1,0);
	j = last_line_address;

	for(i = 0;i < MAX_COLS;i++,j++)
		vga_address[j] = '\0';


	return last_line_address;

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

	cursor = scroll(cursor);
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
