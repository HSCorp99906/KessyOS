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
				case  30:
					return "A";
				case 48:
					return "B";
				case 46:
					return "C";
				case 32:
					return "D";
				case 18:
					return "E";
				case 33:
					return "F";
				case 34:
					return "G";
				case 35:
					return "H";
				case 23:
					return "I";
				case 36:
					return "J";
				case 37:
					return "K";
				case 38:
					return "L";
				case 50:
					return "M";
				case 49:
					return "N";
				case 24:
					return "O";
				case 25:
					return "P";
				case 16:
					return "Q";
				case 19:
					return "R";
				case 31:
					return "S";
				case 20:
					return "T";
				case 22:
					return "U";
				case 47:
					return "V";
				case 17:
					return "W";
				case 45:
					return "X";
				case 21:
					return "Y";
				case 44:
					return "Z";
			}
		}
	}
}
