/*
 Name:		MiryokuCorne_2.ino
 Created:	10/27/23 14:25:08
 Author:	tdapp
*/ 

#include <HID-Project.h>

#include "AppleKeyboard.h"
#include "Hardware.h"
#include "Config.h"
#include "HardwareReader.h"
#include "KeyboardWriter.h"

void setup() {

	Hardware.begin();

	Config.begin();

}

void loop() {

	HardwareReader.update();
	AppleKeyboard.update(millis());

}
