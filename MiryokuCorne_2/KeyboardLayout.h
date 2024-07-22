#pragma once

#include "Config.h"

class KeyboardLayout_ {
public:
	KeyboardKeycode convert(Keycode, int);
	Keycode get_tap_keycode(int, int, int, int, int);
	bool is_shift_mod_key(Keycode);
	bool is_hold_key(int, int);
	Keycode get_hold_keycode(int, int);
};

extern KeyboardLayout_ KeyboardLayout;
