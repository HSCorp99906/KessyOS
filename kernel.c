#include "types.h"
#include "keyboard.h"
#include "system.h"
#include "_kernel_utils/ISR.h"


void __stack_chk_fail_local() {
}


int cursorX = 0, cursorY = 0;
const uint8 SW = 80, SH = 25,SD = 2;
int vgaBufferSize = 0;
char* vga = (char*)0xB8000;
static unsigned long next = 1;
static unsigned short seed_set = 0;

int rand() {
	next = next * 1103515245 + 12345;
	next *= 2;
	return (unsigned int)(next/65536) % 65536;
}


void srand(unsigned int seed) {
	if (!(seed_set)) {
		seed_set = 1;
	}

	next = seed;
}


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


long atoi(const char* S)
{
    long num = 0;
 
    int i = 0;
 
    // run till the end of the string is reached, or the
    // current character is non-numeric
    while (S[i] && (S[i] >= '0' && S[i] <= '9'))
    {
        num = num * 10 + (S[i] - '0');
        i++;
    }
 
    return num;
}


int strlen(const char* str) {
	int i = 0;

	while (str[++i]);
	return i;
}

unsigned short is_digit(const char* str) {
	for (int i = 0; i < strlen(str); ++i) {
		switch (str[i]) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				break;
			default:
				return 0;
		}
	}

	return 1;
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
	kprint("Hello from the kernel.", 0);
	kprint("Press ESC to reset screen.", 0);
	kprint("root@kessOS~$ ", 1);
}


void kmain() {
	isr_install();
	greet();
	cursorY += 2;
	cursorX += 15;
	updateCursor();

	unsigned short bufferIdx = 0;
	unsigned short bufferSize = 0;
	char buffer[5];

	unsigned int skip = 1;
	
	while (1) {
		const char* key = readStr();

		if (strcmp(key, "ESC") && !(strcmp(key, "E"))) {
			kclear();
			cursorX = 15;
			cursorY = 2;
			updateCursor();
			bufferIdx = 0;
			bufferSize = 0;
			greet();
		} else if (strcmp(key, "Enter") && !(strcmp(key, "E"))) {	
			if (strcmp(buffer, "RESTART")) {
				asm("cli");
				outportb(0x64, 0xFE);
			} else if (strcmp(buffer, "SEED")) {
				kclear();
				cursorY = 1;
				cursorX = 6;
				updateCursor();
				kprint("Press ESC to quit.", 0);
				kprint("seed> ", 1);
				unsigned short skip = 0;

				while (1) {
					const char* seedstr = readStr();
					if (bufferSize < 7) {
						kprint(seedstr, 1);
						buffer[bufferIdx] = *seedstr;
						++bufferIdx;
						++bufferSize;
						++cursorX;
						updateCursor();
					}

					if (strcmp(seedstr, "Enter")) {
						kclear();
						bufferIdx = 0;
						bufferSize = 0;
						cursorX = 15;
						cursorY = 2;
						updateCursor();
						greet();
						break;
					} else if (strcmp(seedstr, "ESC")) {
						kclear();

						bufferIdx = 0;
						bufferSize = 0;

						cursorY = 2;
						cursorX = 15;
						updateCursor();

						greet();
						skip = 1;
						break;
					}
				}

				if (skip) {
					continue;
				}

				srand(atoi(buffer));
				bufferIdx = 0;
				bufferSize = 0;
				cursorX = 15;
				updateCursor();
				kclear();
				greet();
			} else if (strcmp(buffer, "RAND")) {
				kclear();
				kprint("Press ESC to quit.", 0);
				cursorX = 0;
				updateCursor();
				if (seed_set) {
					kprint("rand => ", 1);
					char dummyBuf[255];
					kprint(itoa(rand(), dummyBuf, 10), 0);
				} else {
					kprint("*** SEED NOT SET ***", 0);
				}

				while (1) {
					const char* key = readStr();

					if (strcmp(key, "ESC")) {
						kclear();
						bufferIdx = 0;
						bufferSize = 0;
						cursorX = 15;
						cursorY = 2;
						updateCursor();
						greet();
						break;
					}
				}
			} else if (strcmp(buffer, "CREDITS")) {
				cursorX = 0;
				cursorY = 6;
				updateCursor();	
				kclear();
				kprint("Press ESC to quit.", 0);
				kprint(" ", 0);
				kprint(" ", 0);
				kprint("Creator: Ian Moffett.", 0);
				kprint(" ", 0);
				kprint("Creator's Friends: Kizana, Skyde, Sadan, LilyScarlet, Pickle, Liquid44 & Neo9000", 0);
			} else {
				kclear();
				kprint("**Invalid Command.**", 0);
				greet();
				cursorX = 15;
				cursorY = 3;
				bufferIdx = 0;
				bufferSize = 0;
				updateCursor();
				continue;
			}
		} else {
			if (bufferSize < 10) {
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
