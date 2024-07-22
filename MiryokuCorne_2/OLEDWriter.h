#pragma once

class OLEDWriter_ {
private:
  bool show_layout, show_output;
public:
  /**
   * Sets up the text size, rotation, etc. of the OLED screen.
   */
  void begin();
  /**
   * Enables or disables the write arrow on the OLED screen. 
   *
   * @param Booleaan representing whether the write arrow should be shown. 
   */
  void show_write_arrow(bool);
  void set_convert_layout(int);
  /**
   * Enables or disables the keyboard layout indicator on the OLED screen. 
   *
   * @param Booleaan representing whether the keyboard layout indicator should be shown. 
   */
  void show_keyboard_layout(bool);
  void set_keyboard_layout(int);
};

extern OLEDWriter_ OLEDWriter;

