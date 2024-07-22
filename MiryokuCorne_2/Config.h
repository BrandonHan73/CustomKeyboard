#pragma once

#include <Arduino.h>
#include <HID-Project.h>

// Hardware constants.
// Cannot handle more than 64 keys per side. 
#define NUM_ROWS 3
#define NUM_COLS 6
#define RELEASE_DELAY 10

// Keyboard constants
// Cannot handle more than 8 layers per side, including default layer.
#define DVORAK 0
#define QWERTY 1
#define NUM_LAYOUTS 2
#define SHORT_DELAY 25
#define LONG_DELAY 250
#define SHIFT_MOD_SHIFT 100U
#define LETTER_KEY_SHIFT 160U
enum Keycode : uint8_t {
	K_NULL = KEY_RESERVED,

	// Layer keys
	K_FUNCL, K_NUMBL, K_SYMBL, K_SETTL, K_NAVIL, K_MOUSEL,

	CONSTANT_KEYS_BEGIN = 30U,

	// Constant keys
	K_1 = KEY_1, K_2, K_3, K_4, K_5, K_6, K_7, K_8, K_9, K_0,
	K_ENTER, K_ESC, K_BKSP, K_TAB, K_SPACE,
	K_BSLASH = KEY_BACKSLASH, K_TICK = KEY_TILDE,
	K_CAPS = KEY_CAPS_LOCK, K_F1, K_F2, K_F3, K_F4, K_F5, K_F6,
	K_F7, K_F8, K_F9, K_F10, K_F11, K_F12, K_PRTSC, K_SCROLL,
	K_PAUSE, K_INSERT, K_HOME, K_PAGEUP, K_DEL, K_END,
	K_PAGEDOWN, K_RIGHT, K_LEFT, K_DOWN, K_UP,
	K_MENU = KEY_MENU,
	K_REDO = KEY_AGAIN, K_UNDO, K_COPY, K_CUT, K_PASTE,
	K_MUTE = KEY_MUTE, K_VOLUP, K_VOLDOWN,

	SHIFT_MOD_KEYS_BEGIN = CONSTANT_KEYS_BEGIN + SHIFT_MOD_SHIFT,

	// Constant shfit-mod keys
	K_EXCLAM = K_1 + SHIFT_MOD_SHIFT,
	K_AT, K_NUMB, K_DOLLAR, K_PERCENT, K_CARROT, K_AND, K_STAR, K_LPAREN, K_RPAREN,
	K_PIPE = K_BSLASH + SHIFT_MOD_SHIFT, K_TILDE = KEY_TILDE + SHIFT_MOD_SHIFT,

	CONSTANT_KEYS_END,

	// Layout-dependent shift-mod keys
	K_COLON, K_UNDER, K_PLUS, K_LCURLY, K_RCURLY, K_QUOTE, K_LCARROT, K_RCARROT, K_QUES,

	SHIFT_MOD_KEYS_END,

	LETTER_KEYS_BEGIN = 4U + LETTER_KEY_SHIFT,

	// Letter keys
	K_A = KEY_A + LETTER_KEY_SHIFT, K_B, K_C, K_D, K_E, K_F, K_G, K_H, K_I, K_J, K_K, K_L, K_M,
	K_N, K_O, K_P, K_Q, K_R, K_S, K_T, K_U, K_V, K_W, K_X, K_Y, K_Z,

	LETTER_KEYS_END,

	// Layout-dependent keys
	K_SEMICOLON, K_COMMA, K_DOT, K_SLASH, K_DASH, K_EQUAL, K_APOS,
	K_LSQUARE, K_RSQUARE,

	// Settings
	K_RENABLE, K_LENABLE, K_BENABLE, K_LAYOUT, K_RCONVERT, K_LCONVERT,

	// Mouse keys
	K_LMOUSE, K_RMOUSE, K_MMOUSE,
	K_MSUP, K_MSDOWN, K_MSLEFT, K_MSRIGHT, K_MFUP, K_MFDOWN, K_MFLEFT, K_MFRIGHT,

	HOLD_KEYS_BEGIN = 224U,

	// Hold keys
	K_LCTRL = KEY_LEFT_CTRL, K_LSHIFT, K_LALT, K_LWIN,
	K_RCTRL, K_RSHIFT, K_RALT, K_RWIN,

	HOLD_KEYS_END
};
const extern Keycode DEFAULT_DVK[NUM_ROWS][2 * NUM_COLS];
const extern Keycode DEFAULT_QWT[NUM_ROWS][2 * NUM_COLS];
const extern Keycode HOLD[NUM_ROWS][2 * NUM_COLS];
const extern unsigned long HOLD_DELAY[NUM_ROWS][2 * NUM_COLS];
const extern Keycode FUNCTION[NUM_ROWS][NUM_COLS];
const extern Keycode NUMBER_DVK[NUM_ROWS][NUM_COLS];
const extern Keycode SYMBOL_DVK[NUM_ROWS][NUM_COLS];
const extern Keycode NUMBER_QWT[NUM_ROWS][NUM_COLS];
const extern Keycode SYMBOL_QWT[NUM_ROWS][NUM_COLS];
const extern Keycode SETTINGS[NUM_ROWS][NUM_COLS];
const extern Keycode NAVIGATION[NUM_ROWS][NUM_COLS];
const extern Keycode MOUSE[NUM_ROWS][NUM_COLS];

// Screen constants.
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET_PIN -1
#define SCREEN_ADDR 0x3C

// Serial constants.
#define BAUD_RATE 74880
#define DEBUG_BAUD_RATE 9600

// Port constants
#define DDR_SIDE_INDICATOR DDRF
#define PIN_SIDE_INDICATOR PINF
#define SIDE_INDICATOR_MASK 0b00010000

#define DDR_ROW DDRF
#define PORT_ROW PORTF
#define PIN_ROW PINF
const extern unsigned char ROW_MASK[NUM_ROWS];

#define DDR_COL DDRB
#define PORT_COL PORTB
#define PIN_COL PINB
const extern unsigned char COL_MASK[NUM_COLS];

// Debug constants
#define DEBUG_ACTIVE true
#define DEBUG_ABNORMAL_DT_THRESHOLD 10

class Config_ {
private:
	unsigned char side;
	unsigned char row_mask, col_mask;
public:
  /**
   * Defoult constructor, able to be run as soon as the program starts.
   */
	Config_();
  /**
   * Setup function, to be run after hardware has been set up. 
   */
	void begin();
  /**
   * Accessor for which side this code is running on. 
   *
   * @return 0 is this is the left half of the keyboard, 1 if this is the right half.
   */
	int get_side();
  /**
   * Provides a bitwise mask to be used when manipulating the row ports. 
   *
   * @return The bitwise or operation performed on all the individual row mask values. 
   */
	unsigned char get_row_mask();
  /**
   * Provides a bitwise mask to be used when manipulating the column ports. 
   *
   * @return The bitwise or operation performed on all the individual column mask values. 
   */
	unsigned char get_col_mask();
};

extern Config_ Config;
