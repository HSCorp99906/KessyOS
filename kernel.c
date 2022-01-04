#include "types.h"
#include "keyboard.h"
#include "system.h"
#include <stdio.h>


int cursorX = 0, cursorY = 0;
const uint8 SW = 80, SH = 25,SD = 2;
int vgaBufferSize = 0;
char* vga = (char*)0xB8000;

int abs (int i)
{
  return i < 0 ? -i : i;
}

void swap(char *x, char *y) {
    char t = *x; *x = *y; *y = t;
}
 
// Function to reverse `buffer[i…j]`
char* reverse(char *buffer, int i, int j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }
 
    return buffer;
}
 
// Iterative function to implement `itoa()` function in C
char* itoa(int value, char* buffer, int base)
{
    // invalid input
    if (base < 2 || base > 32) {
        return buffer;
    }
 
    // consider the absolute value of the number
    int n = abs(value);
 
    int i = 0;
    while (n)
    {
        int r = n % base;
 
        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }
 
        n = n / base;
    }
 
    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }
 
    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }
 
    buffer[i] = '\0'; // null terminate string
 
    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}


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


void disco() {
	vga = (char*)0xB8000;
	while (1) {
		for (int i = 0; i < 20000; ++i) {
			*vga = 0x0e;
			++vga;
			*vga = 4;
			++vga;
		}


		for (int i = 0; i < 20000; ++i) {
			*vga = 0x0e;
			++vga;
			*vga = 2;
			++vga;
		}

		for (int i = 0; i < 20000; ++i) {
			*vga = 0x0e;
			++vga;
			*vga = 1;
			++vga;
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
	kprint("Hello from the kernel.", 0);
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
			unsigned short isequalZero = 0;

			for (int i = 0; i < strlen(buffer); ++i) {
				if (buffer[i] == '0') {
					isequalZero = 1;
				}
			}

			if (isequalZero) {
				asm("cli");
				outportb(0x64, 0xFE);
			} else if (strcmp(buffer, "1")) {
				kclear();
				disco();
			}
		} else {
			if (bufferSize < 4) {
				kprint(&*key, 1);
				++cursorX;
				updateCursor();
				buffer[bufferIdx] = *key;
				++bufferIdx;
				++bufferSize;
				buffer[bufferIdx] = '\0';
			}
	   }
}

	return;
}
