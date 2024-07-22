
#include <Arduino.h>
#include <HID-Project.h>

#include "Hardware.h"
#include "KeyboardLayout.h"
#include "KeyboardWriter.h"

void KeyboardWriter_::tap_key(int row, int col) {
	bool shift_held;
	unsigned char mask = 0b00001111;
	Keycode kc = KeyboardLayout.get_tap_keycode(
		row, col,
		layer_stack_left & mask, layer_stack_right & mask,
		layout
	);

	switch (kc) {
	case K_RENABLE:
		if (Config.get_side() == 1) {
			enabled == !enabled;
		}
		break;
	case K_LENABLE:
		if (Config.get_side() == 0) {
			enabled == !enabled;
		}
		break;
	case K_BENABLE:
		enabled == !enabled;
		break;
	case K_LAYOUT:
		layout = (layout + 1) % NUM_LAYOUTS;
		break;
	case K_RCONVERT:
		if (Config.get_side() == 1) {
			convert_layout = (convert_layout + 1) % NUM_LAYOUTS;
		}
		break;
	case K_LCONVERT:
		if (Config.get_side() == 0) {
			convert_layout = (convert_layout + 1) % NUM_LAYOUTS;
		}
		break;
	case K_LMOUSE:
		Hardware.tap_mouse(MOUSE_LEFT);
		break;
	case K_RMOUSE:
		Hardware.tap_mouse(MOUSE_RIGHT);
		break;
	case K_MMOUSE:
		Hardware.tap_mouse(MOUSE_MIDDLE);
		break;
	default:
		if (enabled) {
			shift_held = Hardware.is_pressed(KEY_RIGHT_SHIFT) || Hardware.is_pressed(KEY_LEFT_SHIFT);
			if (KeyboardLayout.is_shift_mod_key(kc) && !shift_held) {
				Hardware.hold_key(KEY_LEFT_SHIFT);
			}
			Hardware.tap_key(KeyboardLayout.convert(kc, convert_layout));
			if (!shift_held) {
				Hardware.release_key(KEY_LEFT_SHIFT);
			}
		}
	}
}

void KeyboardWriter_::hold_key(int row, int col) {
	Keycode kc = KeyboardLayout.get_hold_keycode(row, col);
	unsigned long* layer_stack;
	switch (kc) {
	case K_FUNCL: case K_NUMBL: case K_SYMBL:
		layer_stack = &layer_stack_left;
		break;
	case K_SETTL: case K_NAVIL: case K_MOUSEL:
		layer_stack = &layer_stack_right;
		break;
	default:
		if (enabled) {
			Hardware.hold_key(KeyboardLayout.convert(kc, convert_layout));
		}
		return;
	}

	*layer_stack = *layer_stack << 4;
	switch (kc) {
	case K_FUNCL: case K_NUMBL: case K_SYMBL: case K_SETTL: case K_NAVIL: case K_MOUSEL:
		*layer_stack |= kc;
		break;
	}

	unsigned long mask = 0b00001111UL;
	for (int i = 1; i < 8; ++i) {
		if (((*layer_stack & (mask << i)) >> i) == (*layer_stack & mask)) {
			*layer_stack = *layer_stack >> 4;
			break;
		}
	}
}

void KeyboardWriter_::release_key(int row, int col) {
	Keycode kc = KeyboardLayout.get_hold_keycode(row, col);
	unsigned char remove = 0;
	unsigned long mask = 0b00001111UL;
	unsigned long black_mask = 0xFFFFFFFFUL;
	switch (kc) {
	case K_FUNCL: case K_NUMBL: case K_SYMBL: case K_SETTL: case K_NAVIL: case K_MOUSEL:
		remove = kc;
		break;
	default:
		if (enabled) {
			Hardware.release_key(KeyboardLayout.convert(kc, convert_layout));
		}
		return;
	}

	unsigned long* layer_stack;
	switch (kc) {
	case K_FUNCL: case K_NUMBL: case K_SYMBL:
		layer_stack = &layer_stack_left;
		break;
	case K_SETTL: case K_NAVIL: case K_MOUSEL:
		layer_stack = &layer_stack_right;
		break;
	}

	for (int i = 0; i < 8; ++i) {

		if (((*layer_stack & mask) >> (4 * i)) == remove) {
			*layer_stack = (*layer_stack >> 4 & black_mask) | (*layer_stack & ~black_mask);
			break;
		}

		black_mask = black_mask << 4;
		mask = mask << 4;
	}
}

bool KeyboardWriter_::is_enabled() {
	return enabled;
}

KeyboardWriter_ KeyboardWriter;
