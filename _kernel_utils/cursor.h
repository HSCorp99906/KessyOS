#ifndef CURSOR_H
#define CURSOR_H

#include "../system.h"


#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15


void fb_move_cursor(unsigned short pos);
void disable_cursor();

#endif
