#include "util.h"


void _memcpy(char* source, char* dest, int nbytes) {
	for (int i = 0; i < nbytes; ++i) {
		*(dest + i) = *(source + 1);
	}
}


void _memset(uint8* dest, uint8 val, uint32 len) {
	uint8* temp = (uint8*)dest;
	for (; len != 0; --len) {
		*++temp = val;
	}
}
