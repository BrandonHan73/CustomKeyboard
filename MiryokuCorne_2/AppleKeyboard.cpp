
#include <Arduino.h>

#include "AppleKeyboard.h"
#include "HardwareReader.h"

void AppleKeyboard_::press_released_keys(unsigned long t) {

	for (int i = order_	- 1; i >= 0; --i) {
		if (!order[i].is_pressed(t)) {
			for (int l = 0; l < i; ++l) {
				order[l].leader_action(order[i].get_press_time(), order[i]);
			}
			order[i].send_key_press();
		}
	}

}

void AppleKeyboard_::press_head_keys() {
	for (int i = 0; i < order_ && order[i].head_action(); ++i);
}

void AppleKeyboard_::clear_order(unsigned long t) {
	int save = 0;
	for (int i = 0; i < order_; ++i) {
		if (order[i].is_pressed(t)) {
			order[save++] = order[i];
		} else {
			order[i].release();
		}
	}
	order_ = save;
}

void AppleKeyboard_::populate_order(unsigned long t) {
	int temp;
	for (int r = 0; r < NUM_ROWS; ++r) {
		for (int c = 0; c < 2 * NUM_COLS; ++c) {
			if (HardwareReader.key_pressed(r, c)) {
				for (temp = 0; temp < order_; ++temp) {
					if (order[temp].is_at(r, c)) {
						break;
					}
				}
				if (temp == order_) {
					order[order_++] = Key(r, c, t);
				}
			}
		}
	}
}

void AppleKeyboard_::update(unsigned long t) {

  for(int i = 0; i < order_; ++i) {
    order[i].update(t);
  }

	press_released_keys(t);
	clear_order(t);

	populate_order(t);
	press_head_keys();

}

AppleKeyboard_ AppleKeyboard;
