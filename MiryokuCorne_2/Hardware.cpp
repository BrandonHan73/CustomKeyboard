
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <HID-Project.h>

#include "Config.h"
#include "Hardware.h"

void Hardware_::begin() {

	DDR_ROW = 0b00000000;
	DDR_COL = 0b00000000;
	DDR_SIDE_INDICATOR = 0b00000000;

	PORT_COL = 0b00000000;
	PORT_ROW = 0b00000000;

	DDR_COL |= 0b00000000 & Config.get_col_mask();
	PORT_COL |= Config.get_col_mask();

	DDR_ROW |= Config.get_row_mask();
	PORT_ROW |= Config.get_row_mask();

	DDR_SIDE_INDICATOR |= 0b00000000 & SIDE_INDICATOR_MASK;

	Serial1.begin(BAUD_RATE);

	oled_display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);
	oled_display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDR);
	oled_display.clearDisplay();
	oled_display.display();

	Keyboard.begin();
	Mouse.begin();

}

unsigned char Hardware_::read_column_port() {
	return PIN_COL & Config.get_col_mask();
}

void Hardware_::set_row_port(unsigned char val) {
	PORT_ROW = val & Config.get_row_mask();
	while((PIN_ROW & Config.get_row_mask()) != (PORT_ROW & Config.get_row_mask()));
}

bool Hardware_::read_side_indicator() {
	return PIN_SIDE_INDICATOR & SIDE_INDICATOR_MASK;
}

void Hardware_::send_to_partner(unsigned char* msg, int size) {
	Serial1.write(msg, size);
}

void Hardware_::read_from_partner(unsigned char* msg, int size) {
	Serial1.readBytes(msg, size);
}

int Hardware_::serial_write_availability() {
	return Serial1.availableForWrite();
}

int Hardware_::serial_read_availability() {
	return Serial1.available();
}

void Hardware_::hold_key(KeyboardKeycode kc) {
	if (!is_pressed(kc)) {
		Keyboard.press(kc);
		pressed[pressed_++] = kc;
	}
}

void Hardware_::release_key(KeyboardKeycode kc) {
	if (is_pressed(kc)) {
		Keyboard.release(kc);
		bool temp = false;
		for (int i = 0; i < pressed_; ++i) {
			if (temp) {
				pressed[i - 1] = pressed[i];
			} else {
				temp = pressed[i] == kc;
			}
		}
		--pressed_;
	}
}

void Hardware_::tap_key(KeyboardKeycode kc) {
	if (is_pressed(kc)) {
		Keyboard.release(kc);
		Keyboard.press(kc);
	} else {
		Keyboard.press(kc);
		Keyboard.release(kc);
	}
}

void Hardware_::hold_mouse(unsigned char mc) {
	Mouse.press(mc);
}

void Hardware_::release_mouse(unsigned char mc) {
	Mouse.release(mc);
}

void Hardware_::tap_mouse(unsigned char mc) {
	if (Mouse.isPressed(mc)) {
		Mouse.release(mc);
		Mouse.press(mc);
	} else {
		Mouse.press(mc);
		Mouse.release(mc);
	}
}

bool Hardware_::is_pressed(KeyboardKeycode kc) {
	for (int i = 0; i < pressed_; ++i) {
		if (pressed[i] == kc) {
			return true;
		}
	}
	return false;
}

Hardware_ Hardware;
