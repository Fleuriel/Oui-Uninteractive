#ifndef KEYDEFINITION_H
#define KEYDEFINITION_H

/*------------------------------------------------------------
|                         ALPHABETS                          |
------------------------------------------------------------*/
#define INPUT_A					'A' - 'A'				// 00
#define INPUT_B					'B' - 'A'				// 01
#define INPUT_C					'C' - 'A'				// 02
#define INPUT_D					'D' - 'A'				// 03
#define INPUT_E					'E' - 'A'				// 04
#define INPUT_F					'F' - 'A'				// 05
#define INPUT_G					'G' - 'A'				// 06
#define INPUT_H					'H' - 'A'				// 07
#define INPUT_I					'I' - 'A'				// 08
#define INPUT_J					'J' - 'A'				// 09
#define INPUT_K					'K' - 'A'				// 10
#define INPUT_L					'L' - 'A'				// 11
#define INPUT_M					'M' - 'A'				// 12
#define INPUT_N					'N' - 'A'				// 13
#define INPUT_O					'O' - 'A'				// 14
#define INPUT_P					'P' - 'A'				// 15
#define INPUT_Q					'Q' - 'A'				// 16
#define INPUT_R					'R' - 'A'				// 17
#define INPUT_S					'S' - 'A'				// 18
#define INPUT_T					'T' - 'A'				// 19
#define INPUT_U					'U' - 'A'				// 20
#define INPUT_V					'V' - 'A'				// 21
#define INPUT_W					'W' - 'A'				// 22
#define INPUT_X					'X' - 'A'				// 23
#define INPUT_Y					'Y' - 'A'				// 24
#define INPUT_Z					'Z' - 'A'				// 25

/*------------------------------------------------------------
|                          NUMBERS                           |
------------------------------------------------------------*/
#define INPUT_0					1  + INPUT_Z			// 26
#define INPUT_1					2  + INPUT_Z			// 27
#define INPUT_2					3  + INPUT_Z			// 28
#define INPUT_3					4  + INPUT_Z			// 29
#define INPUT_4					5  + INPUT_Z			// 30
#define INPUT_5					6  + INPUT_Z			// 31
#define INPUT_6					7  + INPUT_Z			// 32
#define INPUT_7					8  + INPUT_Z			// 33
#define INPUT_8					9  + INPUT_Z			// 34
#define INPUT_9					10 + INPUT_Z			// 35

/*------------------------------------------------------------
|                           OTHERS                           |
------------------------------------------------------------*/
#define INPUT_SPACE				1  + INPUT_9			// 36
#define INPUT_ALT				2  + INPUT_9			// 37
#define INPUT_CTRL				3  + INPUT_9			// 38
#define INPUT_SHIFT				4  + INPUT_9			// 39
#define INPUT_CAPS				5  + INPUT_9			// 40
#define INPUT_TAB				6  + INPUT_9			// 41
#define INPUT_ESC				7  + INPUT_9			// 42
#define INPUT_ENTER				8  + INPUT_9			// 43

/*------------------------------------------------------------
|                          COMMANDS                          |
------------------------------------------------------------*/
#define INPUT_COPY				1  + INPUT_ENTER		// 44
#define INPUT_PASTE				2  + INPUT_ENTER		// 45
#define INPUT_CUT				3  + INPUT_ENTER		// 46
#define INPUT_UNDO				4  + INPUT_ENTER		// 47

/*------------------------------------------------------------
|                           MOUSE                            |
------------------------------------------------------------*/
#define INPUT_LCLICK			1  + INPUT_UNDO			// 48
#define INPUT_RCLICK			2  + INPUT_UNDO			// 49

/*------------------------------------------------------------
|                           SCROLL                           |
------------------------------------------------------------*/
#define INPUT_SCROLLUP			1 + INPUT_RCLICK		// 50
#define INPUT_SCROLLDOWN		2 + INPUT_RCLICK		// 51



#define NUMBER_OF_INPUT_STATES	1 + INPUT_SCROLLDOWN	// TOTAL NUMBER OF INPUT STATES TO BE TRACKED


#endif // KEY_DEFINITION_H