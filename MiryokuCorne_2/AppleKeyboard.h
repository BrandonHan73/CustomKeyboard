#pragma once

#include "Config.h"
#include "Key.h"

class AppleKeyboard_ {
private:
	Key order[2 * NUM_ROWS * NUM_COLS];
	int order_;
	void press_released_keys(unsigned long);
	void press_head_keys();
	void clear_order(unsigned long);
	void populate_order(unsigned long);
public:
	void update(unsigned long);
};

extern AppleKeyboard_ AppleKeyboard;

