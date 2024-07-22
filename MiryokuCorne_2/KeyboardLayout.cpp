
#include <Arduino.h>
#include <HID-Project.h>

#include "KeyboardLayout.h"

KeyboardKeycode KeyboardLayout_::convert(Keycode kc, int output_layout) {

	if (kc >= CONSTANT_KEYS_BEGIN && kc < CONSTANT_KEYS_END) {
		if (kc >= SHIFT_MOD_KEYS_BEGIN && kc < SHIFT_MOD_KEYS_END) {
			kc = (Keycode)(kc - SHIFT_MOD_SHIFT);
		}
		return (KeyboardKeycode)kc;
	}
	if (kc >= HOLD_KEYS_BEGIN && kc < HOLD_KEYS_END) {
		return (KeyboardKeycode)kc;
	}

	switch (output_layout) {
	case DVORAK:
		switch (kc) {
		case K_Q:
			return KEY_X;
		case K_W:
			return KEY_COMMA;
		case K_E:
			return KEY_D;
		case K_R:
			return KEY_O;
		case K_T:
			return KEY_K;
		case K_Y:
			return KEY_T;
		case K_U:
			return KEY_F;
		case K_I:
			return KEY_G;
		case K_O:
			return KEY_S;
		case K_P:
			return KEY_R;
		case K_A:
			return KEY_A;
		case K_S:
			return KEY_SEMICOLON;
		case K_D:
			return KEY_H;
		case K_F:
			return KEY_Y;
		case K_G:
			return KEY_U;
		case K_H:
			return KEY_J;
		case K_J:
			return KEY_C;
		case K_K:
			return KEY_V;
		case K_L:
			return KEY_P;
		case K_COLON: case K_SEMICOLON:
			return KEY_Z;
		case K_Z:
			return KEY_SLASH;
		case K_X:
			return KEY_B;
		case K_C:
			return KEY_I;
		case K_V:
			return KEY_PERIOD;
		case K_B:
			return KEY_N;
		case K_N:
			return KEY_L;
		case K_M:
			return KEY_M;
		case K_LCARROT: case K_COMMA:
			return KEY_W;
		case K_RCARROT: case K_DOT:
			return KEY_E;
		case K_QUES: case K_SLASH:
			return KEY_LEFT_BRACE;
		case K_UNDER: case K_DASH:
			return KEY_QUOTE;
		case K_PLUS: case K_EQUAL:
			return KEY_RIGHT_BRACE;
		case K_LCURLY: case K_LSQUARE:
			return KEY_MINUS;
		case K_RCURLY: case K_RSQUARE:
			return KEY_EQUAL;
		case K_QUOTE: case K_APOS:
			return KEY_Q;
		default:
			break;
		}
	case QWERTY:
		if (kc >= LETTER_KEYS_BEGIN && kc < LETTER_KEYS_END) {
			return (KeyboardKeycode)(kc - LETTER_KEY_SHIFT);
		}
		switch (kc) {
		case K_COLON: case K_SEMICOLON:
			return KEY_SEMICOLON;
		case K_LCARROT: case K_COMMA:
			return KEY_COMMA;
		case K_RCARROT: case K_DOT:
			return KEY_PERIOD;
		case K_QUES: case K_SLASH:
			return KEY_SLASH;
		case K_UNDER: case K_DASH:
			return KEY_MINUS;
		case K_PLUS: case K_EQUAL:
			return KEY_EQUAL;
		case K_LCURLY: case K_LSQUARE:
			return KEY_LEFT_BRACE;
		case K_RCURLY: case K_RSQUARE:
			return KEY_RIGHT_BRACE;
		case K_QUOTE: case K_APOS:
			return KEY_QUOTE;
		default:
			break;
		}
	}
	return KEY_RESERVED;

}

Keycode KeyboardLayout_::get_tap_keycode(int r, int c, int l_layer, int r_layer, int layout) {

	Keycode default_layer, symbol_layer, number_layer;

	switch (layout) {
	case DVORAK:
		default_layer = (Keycode)pgm_read_byte_near(&(DEFAULT_DVK[r][c]));
		symbol_layer = (Keycode)pgm_read_byte_near(&(SYMBOL_DVK[r][c % NUM_COLS]));
		number_layer = (Keycode)pgm_read_byte_near(&(NUMBER_DVK[r][c % NUM_COLS]));
		break;
	case QWERTY:
		default_layer = (Keycode)pgm_read_byte_near(&(DEFAULT_QWT[r][c]));
		symbol_layer = (Keycode)pgm_read_byte_near(&(SYMBOL_QWT[r][c % NUM_COLS]));
		number_layer = (Keycode)pgm_read_byte_near(&(NUMBER_QWT[r][c % NUM_COLS]));
		break;
	}

	int layer = (c < NUM_COLS) ? l_layer : r_layer;

	switch (layer) {
	case K_SYMBL:
		return symbol_layer;
	case K_NUMBL:
		return number_layer;
	case K_FUNCL:
		return (Keycode)pgm_read_byte_near(&(FUNCTION[r][c % NUM_COLS]));
	case K_MOUSEL:
		return (Keycode)pgm_read_byte_near(&(MOUSE[r][c % NUM_COLS]));
	case K_SETTL:
		return (Keycode)pgm_read_byte_near(&(SETTINGS[r][c % NUM_COLS]));
	case K_NAVIL:
		return (Keycode)pgm_read_byte_near(&(NAVIGATION[r][c % NUM_COLS]));
	default:
		return default_layer;
	}
}

bool KeyboardLayout_::is_shift_mod_key(Keycode kc) {
	return kc >= SHIFT_MOD_KEYS_BEGIN && kc < SHIFT_MOD_KEYS_END;
}

bool KeyboardLayout_::is_hold_key(int r, int c) {
	return get_hold_keycode(r, c) != K_NULL;
}

Keycode KeyboardLayout_::get_hold_keycode(int r, int c) {
	return (Keycode)pgm_read_byte_near(&(HOLD[r][c]));
}

KeyboardLayout_ KeyboardLayout;
