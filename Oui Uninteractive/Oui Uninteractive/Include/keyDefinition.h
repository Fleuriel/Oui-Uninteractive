#ifndef KEYDEFINITION_H
#define KEYDEFINITION_H

/*---------------------------------------
|              ALPHABETS                |
---------------------------------------*/
#define KEY_A		'A' - 'A'		// 00
#define KEY_B		'B' - 'A'		// 01
#define KEY_C		'C' - 'A'		// 02
#define KEY_D		'D' - 'A'		// 03
#define KEY_E		'E' - 'A'		// 04
#define KEY_F		'F' - 'A'		// 05
#define KEY_G		'G' - 'A'		// 06
#define KEY_H		'H' - 'A'		// 07
#define KEY_I		'I' - 'A'		// 08
#define KEY_J		'J' - 'A'		// 09
#define KEY_K		'K' - 'A'		// 10
#define KEY_L		'L' - 'A'		// 11
#define KEY_M		'M' - 'A'		// 12
#define KEY_N		'N' - 'A'		// 13
#define KEY_O		'O' - 'A'		// 14
#define KEY_P		'P' - 'A'		// 15
#define KEY_Q		'Q' - 'A'		// 16
#define KEY_R		'R' - 'A'		// 17
#define KEY_S		'S' - 'A'		// 18
#define KEY_T		'T' - 'A'		// 19
#define KEY_U		'U' - 'A'		// 20
#define KEY_V		'V' - 'A'		// 21
#define KEY_W		'W' - 'A'		// 22
#define KEY_X		'X' - 'A'		// 23
#define KEY_Y		'Y' - 'A'		// 24
#define KEY_Z		'Z' - 'A'		// 25

/*---------------------------------------
|               NUMBERS                 |
---------------------------------------*/
#define KEY_0		1  + KEY_Z		// 26
#define KEY_1		2  + KEY_Z		// 27
#define KEY_2		3  + KEY_Z		// 28
#define KEY_3		4  + KEY_Z		// 29
#define KEY_4		5  + KEY_Z		// 30
#define KEY_5		6  + KEY_Z		// 31
#define KEY_6		7  + KEY_Z		// 32
#define KEY_7		8  + KEY_Z		// 33
#define KEY_8		9  + KEY_Z		// 34
#define KEY_9		10 + KEY_Z		// 35

/*---------------------------------------
|                OTHERS                 |
---------------------------------------*/
#define KEY_SPACE	1  + KEY_9		// 36
#define KEY_ALT		2  + KEY_9		// 37
#define KEY_CTRL	3  + KEY_9		// 38
#define KEY_SHIFT	4  + KEY_9		// 39
#define KEY_CAPS	5  + KEY_9		// 40
#define KEY_TAB		6  + KEY_9		// 41
#define KEY_ESC		7  + KEY_9		// 42
#define KEY_ENTER   8  + KEY_9		// 43

/*---------------------------------------
|               COMMANDS                |
---------------------------------------*/
#define KEY_COPY	1  + KEY_ENTER	// 44
#define KEY_PASTE	2  + KEY_ENTER	// 45
#define KEY_CUT		3  + KEY_ENTER	// 46
#define KEY_UNDO	4  + KEY_ENTER	// 47

/*---------------------------------------
|                MOUSE                  |
---------------------------------------*/
#define KEY_LCLICK  1  + KEY_UNDO	// 48
#define KEY_RCLICK  2  + KEY_UNDO	// 49

#define Number_of_working_keys 1 + KEY_RCLICK // 50
#endif // KEY_DEFINITION_H