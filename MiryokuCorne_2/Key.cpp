
#include "Config.h"
#include "Hardware.h"
#include "HardwareReader.h"
#include "Key.h"
#include "KeyboardLayout.h"
#include "KeyboardWriter.h"

Key::Key() {}

Key::Key(int r, int c, unsigned long t) {
	row = r;
	col = c;
	press_time = t;
	exhausted = false;
}

void Key::update(unsigned long t) {
  if(HardwareReader.key_pressed(row, col)) {
    release_time = t;
  }
}

void Key::send_key_press() {
	if (!exhausted) {
		KeyboardWriter.tap_key(row, col);
		exhausted = true;
	}
}

void Key::leader_action(unsigned long t, const Key &k) {
	if (
		KeyboardLayout.is_hold_key(row, col) && 
		(t - press_time > HOLD_DELAY[row][col]) && 
		!k.exhausted
		) {
		KeyboardWriter.hold_key(row, col);
		exhausted = true;
	} else {
		send_key_press();
	}
}

bool Key::head_action() {
	if (!KeyboardLayout.is_hold_key(row, col)) {
		send_key_press();
		return true;
	}
	return false;
}

bool Key::is_pressed(unsigned long t) {
	return t - release_time < RELEASE_DELAY || HardwareReader.key_pressed(row, col);
}

void Key::release() {
	KeyboardWriter.release_key(row, col);
	exhausted = false;
}

unsigned long Key::get_press_time() {
	return press_time;
}

bool Key::is_at(int r, int c) {
	return row == r && col == c;
}
