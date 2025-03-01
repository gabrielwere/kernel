#ifndef SCANCODES_H
#define SCANCODES_H


#define LEFT_SHIFT_KEY_PRESS 42
#define RIGHT_SHIFT_KEY_PRESS 54
#define LEFT_SHIFT_KEY_RELEASE 42 + 0x80
#define RIGHT_SHIFT_KEY_RELEASE 54 + 0x80

#define DASH "-"
#define EQUALS "="
#define LEFT_SQUARE_BRACKET "["
#define RIGHT_SQUARE_BRACKET "]"
#define SEMICOLON ";"
#define SINGLE_QUOTATION "'"
#define BACKTICK "`"
#define BACKSLASH "\\"
#define COMMA ","
#define DOT "."
#define SLASH "/"
#define SPACE " "

//a lookup table for the character without shift key
char *no_shift_scancode_lut[] = {

	"\0","\0","1","2","3","4","5","6","7","8","9","0",DASH,EQUALS,"\b",
	"\t","q","w","e","r","t","y","u","i","o","p",LEFT_SQUARE_BRACKET,RIGHT_SQUARE_BRACKET,"\r","\0",
	"a","s","d","f","g","h","j","k","l",SEMICOLON,SINGLE_QUOTATION,BACKTICK,"\0",BACKSLASH,
	"z","x","c","v","b","n","m",COMMA,DOT,SLASH,"\0","\0","\0",SPACE

};

#define UNDERSCORE "_"
#define PLUS "+"
#define LEFT_BRACE "{"
#define RIGHT_BRACE "}"
#define COLON ":"
#define DOUBLE_QUOTATION "\""
#define TILDE "~"
#define VERTICAL_BAR "|"
#define LESS_THAN "<"
#define GREATER_THAN ">"
#define QUESTION_MARK "?"

//a lookup table for the character with shift key
//e.g shift + 1 = !,shift + 2 = @,shift + A = A
char *shift_scancode_lut[] = {

	"\0","\0","!","@","#","$","%","^","&","*","(",")",UNDERSCORE,PLUS,"\b",
	"\0","Q","W","E","R","T","Y","U","I","O","P",LEFT_BRACE,RIGHT_BRACE,"\0","\0",
	"A","S","D","F","G","H","J","K","L",COLON,DOUBLE_QUOTATION,TILDE,"\0",VERTICAL_BAR,
	"Z","X","C","V","B","N","M",LESS_THAN,GREATER_THAN,QUESTION_MARK,"\0","\0","\0","\0"
};


#endif
