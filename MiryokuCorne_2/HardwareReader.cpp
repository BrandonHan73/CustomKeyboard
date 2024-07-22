
#include <Arduino.h>

#include "Debug.h"
#include "Hardware.h"
#include "Config.h"
#include "HardwareReader.h"

void HardwareReader_::update_self_keys() {

	self_keys = 0x00000000ULL;

	unsigned long long high_mask = 0xFFFFFFFFFFFFFFFFULL, low_mask = 0x0000000000000000ULL;
	unsigned long long mask;

	unsigned char read;
	for (int r = 0; r < NUM_ROWS; ++r) {
		Hardware.set_row_port(~ROW_MASK[r]);
		read = ~Hardware.read_column_port();

		for (int c = 0; c < NUM_COLS; ++c) {

			mask = 0x00000001ULL << (r * NUM_COLS + c);

			self_keys |= (read & COL_MASK[c] ? high_mask : low_mask) & mask;

		}
	}

}

void HardwareReader_::update_partner_keys() {
	send_to_partner();
	read_from_partner();
}

void HardwareReader_::send_to_partner() {
	unsigned char msg[16];
	unsigned char mask = 0b00001111;
	for (int i = 0; i < 16; ++i) {
		msg[i] = (i << 4) | ((self_keys >> (i * 4)) & mask);
	}
	int available = min(Hardware.serial_write_availability(), 16);
	Hardware.send_to_partner(msg, available);
}

void HardwareReader_::read_from_partner() {
	unsigned char msg[16];
	unsigned char mask = 0b00001111;
	unsigned long long ull_mask = 0x000000000000000FULL;
	int available = min(Hardware.serial_read_availability(), 16);

	Hardware.read_from_partner(msg, available);
	for (int i = 0; i < available; ++i) {
		partner_keys &= ~(ull_mask << ((msg[i] >> 4) * 4));
		partner_keys |= (unsigned long long) (msg[i] & mask) << ((msg[i] >> 4) * 4);
	}

}

void HardwareReader_::update() {
	update_self_keys();
	update_partner_keys();
}

bool HardwareReader_::key_pressed(int r, int c) {
	unsigned long long data = (Config.get_side() == 0) == (c < NUM_COLS) ? self_keys : partner_keys;
	c = c < NUM_COLS ? NUM_COLS - 1 - c : c - NUM_COLS;
	unsigned long long mask = 0x00000001ULL << (r * NUM_COLS + c);
	return data & mask;
}

HardwareReader_ HardwareReader;
