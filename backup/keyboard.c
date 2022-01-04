#include "keyboard.h"

const char* readStr() {
	char buff;
	const char* buffstr;
	uint8 i = 0;
	uint8 reading = 1;

	while (reading) {
		if (inportb(0x64) & 0x1) {
			switch (inportb(0x60)) {
				case 1:
					return "ESC";
				case 2:
					return "1";
				case 3:
					return "2";
				case 4:
					return "3";
				case 5:
					return "4";
				case 6:
					return "5";
				case 7:
					return "6";
				case 8:
					return "7";
				case 9:
					return "8";
				case 10:
					return "9";
				case 11:
					return "0";
				case 12:
					return "-";
				case 53:
					return "/";
				case 55:
					return "*";
				case 13:
					return "+";
				case 28:
					return "Enter";
			}
		}
	}
}
