
#include "Config.h"
#include "Hardware.h"

const Keycode DEFAULT_DVK[][2 * NUM_COLS] PROGMEM = {
	{ K_APOS, K_COMMA, K_DOT, K_P, K_Y, K_TAB, K_ENTER, K_F, K_G, K_C, K_R, K_L }, 
	{ K_A, K_O, K_E, K_U, K_I, K_SPACE, K_BKSP, K_D, K_H, K_T, K_N, K_S },
	{ K_SEMICOLON, K_Q, K_J, K_K, K_X, K_ESC, K_DEL, K_B, K_M, K_W, K_V, K_Z }
};
const Keycode DEFAULT_QWT[][2 * NUM_COLS] PROGMEM = {
	{ K_Q, K_W, K_E, K_R, K_T, K_TAB, K_ENTER, K_Y, K_U, K_I, K_O, K_P },
	{ K_A, K_S, K_D, K_F, K_G, K_SPACE, K_BKSP, K_H, K_J, K_K, K_L, K_SEMICOLON },
	{ K_Z, K_X, K_C, K_V, K_B, K_ESC, K_DEL, K_N, K_M, K_COMMA, K_DOT, K_SLASH }
};
const Keycode HOLD[NUM_ROWS][2 * NUM_COLS] PROGMEM = {
	{ K_NULL, K_NULL, K_NULL, K_NULL, K_NULL, K_MOUSEL, K_SYMBL, K_NULL, K_NULL, K_NULL, K_NULL, K_NULL },
	{ K_LWIN, K_LALT, K_LCTRL, K_LSHIFT, K_NULL, K_NAVIL, K_NUMBL, K_NULL, K_RSHIFT, K_RCTRL, K_RALT, K_RWIN},
	{ K_NULL, K_NULL, K_NULL, K_NULL, K_NULL, K_SETTL, K_FUNCL, K_NULL, K_NULL, K_NULL, K_NULL, K_NULL }
};
const unsigned long HOLD_DELAY[NUM_ROWS][2 * NUM_COLS] = {
	{ 0, 0, 0, 0, 0, SHORT_DELAY, SHORT_DELAY, 0, 0, 0, 0, 0 },
	{ LONG_DELAY, LONG_DELAY, LONG_DELAY, SHORT_DELAY, 0, SHORT_DELAY, SHORT_DELAY, 0, SHORT_DELAY, LONG_DELAY, LONG_DELAY, LONG_DELAY },
	{ 0, 0, 0, 0, 0, SHORT_DELAY, SHORT_DELAY, 0, 0, 0, 0, 0 }
};
const extern Keycode FUNCTION[NUM_ROWS][NUM_COLS] PROGMEM = {
	{ K_F12, K_F7, K_F8, K_F9, K_PRTSC, K_TAB },
	{ K_F11, K_F4, K_F5, K_F6, K_SCROLL, K_SPACE },
	{ K_F10, K_F1, K_F2, K_F3, K_PAUSE, K_MENU }
};
const extern Keycode NUMBER_DVK[NUM_ROWS][NUM_COLS] PROGMEM = {
	{ K_LSQUARE, K_7, K_8, K_9, K_RSQUARE, K_DASH },
	{ K_SLASH, K_4, K_5, K_6, K_EQUAL, K_0 },
	{ K_TICK, K_1, K_2, K_3, K_BSLASH, K_DOT }
};
const extern Keycode SYMBOL_DVK[NUM_ROWS][NUM_COLS] PROGMEM = {
	{ K_LCURLY, K_AND, K_STAR, K_LPAREN, K_RCURLY, K_UNDER },
	{ K_QUES, K_DOLLAR, K_PERCENT, K_CARROT, K_PLUS, K_RPAREN },
	{ K_TILDE, K_EXCLAM, K_AT, K_NUMB, K_PIPE, K_LPAREN }
};
const extern Keycode NUMBER_QWT[NUM_ROWS][NUM_COLS] PROGMEM = {
	{ K_LSQUARE, K_7, K_8, K_9, K_RSQUARE, K_DASH },
	{ K_APOS, K_4, K_5, K_6, K_EQUAL, K_0 },
	{ K_TICK, K_1, K_2, K_3, K_BSLASH, K_DOT }
};
const extern Keycode SYMBOL_QWT[NUM_ROWS][NUM_COLS] PROGMEM = {
	{ K_LCURLY, K_AND, K_STAR, K_LPAREN, K_RCURLY, K_UNDER },
	{ K_QUOTE, K_DOLLAR, K_PERCENT, K_CARROT, K_PLUS, K_RPAREN },
	{ K_TILDE, K_EXCLAM, K_AT, K_NUMB, K_PIPE, K_LPAREN }
};
const extern Keycode SETTINGS[NUM_ROWS][NUM_COLS] PROGMEM = {
	{ K_LENABLE, K_NULL, K_NULL, K_NULL, K_NULL, K_NULL },
	{ K_BENABLE, K_NULL, K_LCONVERT, K_LAYOUT, K_RCONVERT, K_NULL },
	{ K_RENABLE, K_NULL, K_NULL, K_NULL, K_NULL, K_NULL }
};
const extern Keycode NAVIGATION[NUM_ROWS][NUM_COLS] PROGMEM = {
	{ K_VOLDOWN, K_REDO, K_PASTE, K_COPY, K_CUT, K_UNDO },
	{ K_MUTE, K_CAPS, K_LEFT, K_DOWN, K_UP, K_RIGHT },
	{ K_VOLUP, K_INSERT, K_HOME, K_PAGEDOWN, K_PAGEUP, K_END }
};
const extern Keycode MOUSE[NUM_ROWS][NUM_COLS] PROGMEM = {
	{ K_RMOUSE, K_REDO, K_PASTE, K_COPY, K_CUT, K_UNDO },
	{ K_LMOUSE, K_NULL, K_MFLEFT, K_MFDOWN, K_MFUP, K_MFRIGHT },
	{ K_MMOUSE, K_NULL, K_MSLEFT, K_MSDOWN, K_MSUP, K_MSRIGHT }
};

const unsigned char ROW_MASK[] = { 0b00100000, 0b01000000, 0b10000000 };
const unsigned char COL_MASK[] = { 0b00010000, 0b00100000, 0b01000000, 0b00000100, 0b00001000, 0b00000010 };

Config_::Config_() {
	row_mask = 0b00000000;
	for (int r = 0; r < NUM_ROWS; ++r) {
		row_mask |= ROW_MASK[r];
	}

	col_mask = 0b00000000;
	for (int c = 0; c < NUM_COLS; ++c) {
		col_mask |= COL_MASK[c];
	}
}

void Config_::begin() {
	side = Hardware.read_side_indicator() ? 1 : 0;
}

int Config_::get_side() {
	return side;
}

unsigned char Config_::get_row_mask() {
	return row_mask;
}

unsigned char Config_::get_col_mask() {
	return col_mask;
}

Config_ Config;
