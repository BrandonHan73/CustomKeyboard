#pragma once

#include <Adafruit_SSD1306.h>
#include <HID-Project.h>

#include "Config.h"

class Hardware_ {
private:
	Adafruit_SSD1306 oled_display;
	KeyboardKeycode pressed[4 * NUM_ROWS * NUM_COLS];
	int pressed_;
public:
	/**
	 * Sets port directions and initializes keyboard, mouse, and OLED libraries.
	 */
	void begin();
	/**
	 * Reads input from the designated column port. Any bits not assigned to a column will be set to zero.
	 *
	 * @return The value of the column port.
	 */
	unsigned char read_column_port();
	/**
	 * Sets the row port to the given value. Disregards any bits not assigned to a row
	 * 
	 * @param The value to set the row port to. 
	 */
	void set_row_port(unsigned char);
	/**
	 * Returns the value of the pin used to determine which side the current Arduino exists on.
	 *
	 * @return true if the indicator pin reads high, false otherwise.
	 */
	bool read_side_indicator();
	/**
	 * Sends a message through Serial1.
	 *
	 * @param The array containing the message to send.
	 * @param The size of the message
	 */
	void send_to_partner(unsigned char* msg, int s);
	/**
	 * Reads a message through Serial1.
	 * 
	 * @param The array to write the message to. 
	 * @param The amount of bytes to read. 
	 */
	void read_from_partner(unsigned char*, int);
  /**
   * Provides the availability of the Serial1 write buffer. 
   *
   * @return The number of available bytes in the Serial1 write buffer.
   */
	int serial_write_availability();
  /**
   * Provides the availability of the Serial1 read buffer. 
   *
   * @return The number of available bytes in the Serial1 read buffer.
   */
	int serial_read_availability();
	/**
	 * Holds down a key using the HID-Project library.
	 *
	 * @param The key to hold down.
	 */
	void hold_key(KeyboardKeycode);
	/**
	 * Releases a key using the HID-Project library.
	 *
	 * @param The key to release.
	 */
	void release_key(KeyboardKeycode);
	/**
	 * Holds down a key using the HID-Project library, releasing it immediately afterwards. If the key was being held when this method was called, it will release the key, then start holding it again. 
	 *
	 * @param The key to press.
	 */
	void tap_key(KeyboardKeycode);
	/**
	 * Holds down a mouse button using the HID-Project library.
	 *
	 * @param The key to hold down.
	 */
	void hold_mouse(unsigned char);
	/**
	 * Releases a mouse button using the HID-Project library.
	 *
	 * @param The key to release.
	 */
	void release_mouse(unsigned char);
	/**
	 * Holds down a mouse button using the HID-Project library, releasing it immediately afterwards. If the key was being held when this method was called, it will release the key, then start holding it again.
	 *
	 * @param The key to press.
	 */
	void tap_mouse(unsigned char);
	/**
	 * Holds down a key using the HID-Project library, releasing it immediately afterwards.
	 *
	 * @param The key to press.
	 */
	void tap_key(Keycode);
	/**
	 * Determines whether a key is currently being held by the HID-Project library.
	 * 
	 * @return true if the key is being held, false otherwise.
	 */
	bool is_pressed(KeyboardKeycode);
};

extern Hardware_ Hardware;
