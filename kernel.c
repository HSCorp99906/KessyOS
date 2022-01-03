#include "types.h"
#include "keyboard.h"
#include "system.h"


int cursorX = 0, cursorY = 0;
const uint8 SW = 80, SH = 25,SD = 2;
int vgaBufferSize = 0;
char* vga = (char*)0xB8000;


int strlen(const char* str) {
	int i = 0;

	while (str[++i]);
	return i;
}


void updateCursor() {
	unsigned int temp = cursorY * SW + cursorX;

	outportb(0x3D4, 14);
	outportb(0x3D5, temp >> 8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
}


int strcmp(const char* const STR, const char* const STR1) {
	unsigned int idx = 0;

	for (int i = 0; i < strlen(STR); ++i) {
		if (STR[i] != STR1[idx]) {
			return 0;
		} else {
			++idx;
			continue;
		}
	}

	return 1;
}


void kprint(const char* str, unsigned short oneline) {	 
	for (int i = 0; i < strlen(str); ++i) {
		*vga = str[i];
		vga += 2;
		++vgaBufferSize;
	}

	if (!(oneline)) {
		for (int i = 0; i < SW - strlen(str); ++i) {
			*vga = ' ';
			vga += 2;
		}
		
	}
}


void kclear() {
	vga = (char*)0xB8000;
	for (int i = 0; i < 599 + vgaBufferSize; ++i) {
		*vga = ' ';
		vga += 2;
	}

	vga = (char*)0xB8000;
}


void greet() {
	kprint("Hello from the kernel!", 0);
	kprint("Press ESC to reset screen.", 0);
	kprint("root@kessOS~$ ", 1);
}


void kmain() {
	greet();
	cursorY += 2;
	cursorX += 15;
	updateCursor();

	unsigned short bufferIdx = 0;
	unsigned short bufferSize = 0;
	char buffer[5];
	
	while (1) {
		const char* key = readStr();

		if (strcmp(key, "ESC")) {
			kclear();
			cursorX = 15;
			cursorY = 2;
			updateCursor();
			bufferIdx = 0;
			bufferSize = 0;
			greet();
		} else if (strcmp(key, "Enter")) {
			unsigned short isequal = 0;

			for (int i = 0; i < strlen(buffer); ++i) {
				if (buffer[i] == '0') {
					isequal = 1;
				}
			}

			if (isequal) {
				asm("cli");
				outportb(0x64, 0xFE);
			}
		} else {
			if (bufferSize < 4) {
				kprint(&*key, 1);
				++cursorX;
				updateCursor();
				buffer[bufferIdx] = *key;
				++bufferIdx;
				++bufferSize;
			}
	   }
}

	return;
}
