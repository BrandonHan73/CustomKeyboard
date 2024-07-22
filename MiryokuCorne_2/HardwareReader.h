#pragma once

class HardwareReader_ {
private: 
	unsigned long self_keys, partner_keys;
	void update_self_keys();
	void update_partner_keys();
	void send_to_partner();
	void read_from_partner();
public:
	void update();
	bool key_pressed(int, int);
};

extern HardwareReader_ HardwareReader;

