#pragma once

#include "Config.h"

class KeyboardWriter_ {
private:
	bool enabled = true;
	unsigned long layer_stack_left, layer_stack_right;
	int layout = DVORAK, convert_layout = DVORAK;
public:
	void tap_key(int, int);
	void hold_key(int, int);
	void release_key(int, int);
	bool is_enabled();
};

extern KeyboardWriter_ KeyboardWriter;
