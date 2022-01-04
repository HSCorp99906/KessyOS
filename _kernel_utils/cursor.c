#include "cursor.h"


void fb_move_cursor(unsigned short pos) {
	outportb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outportb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
	outportb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outportb(FB_DATA_PORT, pos & 0x00FF);
}


void disable_cursor() {
	outportb(FB_COMMAND_PORT, 0x0A);
	outportb(FB_DATA_PORT, 0x20);
}
