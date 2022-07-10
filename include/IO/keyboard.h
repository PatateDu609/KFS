#ifndef IO_KEYBOARD_H
#define IO_KEYBOARD_H

#define ESC 0x1b
#define BACKSPACE '\b'

#define CTRL_L 170
#define CTRL_R 171
#define SHIFT_L 173
#define SHIFT_R 174
#define ALT_L 175
#define ALT_R 176
#define CAPS_LOCK 179
#define NUM_LOCK 183
#define SCROLL_LOCK 184

#define F1 200
#define F2 201
#define F3 202
#define F4 203
#define F5 204
#define F6 205
#define F7 206
#define F8 207
#define F9 208
#define F10 209
#define F11 210
#define F12 211
#define IS_F(key) (key >= F1 && key <= F12)
#define GET_F(key) (key - F1) // Get the number of the function key.

#define UP 150
#define DOWN 151
#define LEFT 152
#define RIGHT 153

#define EXT 129
#define NOT_FOUND 255

unsigned char getch(int scancode);

#endif
