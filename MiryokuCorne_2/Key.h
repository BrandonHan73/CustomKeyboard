#pragma once

#include <HID-Project.h>

#include "Config.h"

class Key {
private:
	int row, col;
	unsigned long press_time, release_time, update_time;
	bool exhausted;
public:
	/**
	 * Default constructor. 
	 */
	Key();
	/**
	 * Constructor for the Key class. Stores data for the row and column of the key, along with the keycodes corresponding with this key at any given layer. 
	 * 
	 * @param The row of the key in the matrix.
	 * @param The column of the key in the matrix.
	 * @param The current time in milliseconds.
	 */
	Key(int, int, unsigned long);
	/**
	 * Executes any continuous-time operations needed by the key. 
	 * 
	 * @param The current time in milliseconds. 
	 */
	void update(unsigned long);
	/**
	 * Taps and exhausts the key. 
	 */
	void send_key_press();
	/**
	 * Performs any needed actions when the key is held while another key is tapped. 
	 * 
	 * @param The press time of the tapped key. 
	 */
	void leader_action(unsigned long, const Key&);
  /**
   * Performs any needed action when the key is the longest-held key. 
   * 
   * @return true if the next-longest held key should also perform its head action, false otherwise. 
   */
	bool head_action();
	/**
	 * Determines whether this key is currently held or not.
	 * 
   * @param The current time.
	 * @return true if the key is held, false otherwise.
	 */
	bool is_pressed(unsigned long);
	/**
	 * Stops all actions related to this key.
	 */
	void release();
	/**
	 * Returns the time this key was pressed in milliseconds.
	 * 
	 * @return the time in milliseconds.
	 */
	unsigned long get_press_time();
	/**
	 * Returns whether the key is at the given position.
	 * 
	 * @param The row to check.
	 * @param The column to check.
	 * @return true if this key is at the row and column, false otherwise. 
	 */
	bool is_at(int, int);
};
