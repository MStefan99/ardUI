//
// Created by MStefan99 on 16.12.19.
//

/* This is the low-level platform interface. You'll need to implement the following functions to work on your
 * hardware to use the ardUI library.
 */

#include "llpi.h"


uint16_t arduiDisplayGetHeight() {
	// Has to be implemented by the user
	return 360;
}


uint16_t arduiDisplayGetWidth() {
	// Has to be implemented by the user
	return 480;
}


uint16_t arduiDisplayGetFontHeight() {
	// Has to be implemented by the user
	return 8;
}


uint16_t arduiDisplayGetFontWidth() {
	// Has to be implemented by the user
	return 5;
}


bool arduiDisplayIsClicked() {
	// Has to be implemented by the user
	return false;
}


void arduiDisplayGetClickLocation(uint16_t& x, uint16_t& y) {
	// Has to be implemented by the user
	x = 0;
	y = 0;
}


ReturnCode arduiDisplayInit() {
#ifdef DEBUG
	Serial.println("Display init");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayOn() {
#ifdef DEBUG
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayOff() {
#ifdef DEBUG
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplaySetBrightness(uint8_t brightness) {
#ifdef DEBUG
	Serial.println("Display brigthness set to " + std::to_string(brightness));
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayFill(uint16_t color) {
#ifdef DEBUG
	Serial.println("Display filled");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawPixel(uint16_t x, uint16_t y, uint32_t color) {
#ifdef DEBUG
	Serial.println("Drawn pixel at (" + std::to_string(x) + ", "
				   + std::to_string(y) + ")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color) {
#ifdef DEBUG
	Serial.println("Drawn line from (" + std::to_string(x1) + ", " + std::to_string(y1) + ") to ("
				   + std::to_string(x2) + ", " + std::to_string(y2) + ")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawChar(uint16_t x, uint16_t y, uint16_t height, char text, uint32_t color) {
#ifdef DEBUG
	Serial.println("Drawn char " + std::to_string(text) + " at ("
				   + std::to_string(x) + ", " + std::to_string(y) + ")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawText(uint16_t x, uint16_t y, uint16_t height, const String& text, uint32_t color) {
#ifdef DEBUG
	Serial.println("Drawn text \"" + text + "\" at (" + std::to_string(x) + ", " + std::to_string(y) + ")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
#ifdef DEBUG
	Serial.println("Drawn circle at (" + std::to_string(x) + ", " + std::to_string(y)
				   + ") with radius " + std::to_string(radius));
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayFillCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
#ifdef DEBUG
	Serial.println("Filled circle at (" + std::to_string(x) + ", " + std::to_string(y)
				   + ") with radius " + std::to_string(radius));
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
								uint32_t color) {
#ifdef DEBUG
	Serial.println("Drawn rect from (" + std::to_string(x1) + ", " + std::to_string(y1) + ") to ("
				   + std::to_string(x2) + ", " + std::to_string(y2) + ")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayFillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
								uint32_t color) {
#ifdef DEBUG
	Serial.println("Filled rect from (" + std::to_string(x1) + ", " + std::to_string(y1) + ") to ("
				   + std::to_string(x2) + ", " + std::to_string(y2) + ")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
									uint16_t x3, uint16_t y3, uint32_t color) {
	// Has to be implemented by the user
#ifdef DEBUG
	Serial.println("Drawn triangle between (" + std::to_string(x1) + ", " + std::to_string(y1) + "), ("
				   + std::to_string(x2) + ", " + std::to_string(y2) + ") and ("
				   + std::to_string(x3) + ", " + std::to_string(y3));
#endif
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayFillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
									uint16_t x3, uint16_t y3, uint32_t color) {
	// Has to be implemented by the user
#ifdef DEBUG
	Serial.println("Filled triangle between (" + std::to_string(x1) + ", " + std::to_string(y1) + "), ("
				   + std::to_string(x2) + ", " + std::to_string(y2) + ") and ("
				   + std::to_string(x3) + ", " + std::to_string(y3));
#endif
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawBitmap(uint16_t x, uint16_t y, uint16_t* bitmap) {
	// Has to be implemented by the user
#ifdef DEBUG
	Serial.println("Drawn bitmap at (" + std::to_string(x) + ", " + std::to_string(y));
#endif
	return NOT_IMPLEMENTED;
}

