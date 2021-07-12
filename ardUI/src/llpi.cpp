//
// Created by MStefan99 on 16.12.19.
//

/* This is the low-level platform interface. You'll need to implement the following functions to work on your
 * hardware to use the ardUI library.
 */

#include "llpi.h"


uint16_t arduiDisplayGetHeight() {
	// Has to be implemented by the user
	return 480;
}


uint16_t arduiDisplayGetWidth() {
	// Has to be implemented by the user
	return 320;
}


uint16_t arduiDisplayGetFontHeight() {
	// Has to be implemented by the user
	return 8;
}


uint16_t arduiDisplayGetCharWidth(char c, uint16_t height) {
	// Has to be implemented by the user
	return 5;
}


bool arduiDisplayIsClicked() {
	// Has to be implemented by the user
	return false;
}


uint16_t arduiDisplayGetClickX() {
	// Has to be implemented by the user
	return 0;
}


uint16_t arduiDisplayGetClickY() {
	// Has to be implemented by the user
	return 0;
}


ReturnCode arduiDisplayInit() {
#if defined(VERBOSE_MODE) && defined(DEBUG_MODE)
	Serial.println("Display init");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayOn() {
#if VERBOSE_MODE
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayOff() {
#if VERBOSE_MODE
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplaySetBrightness(uint8_t brightness) {
#if VERBOSE_MODE
	Serial.print("Display brightness set to ");
	Serial.println(brightness);
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayFill(uint32_t color) {
#if VERBOSE_MODE
	Serial.println("Display filled");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawPixel(uint16_t x, uint16_t y, uint32_t color) {
#if VERBOSE_MODE
	Serial.print("Drawn pixel at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.print(y);
	Serial.println(")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color) {
#if VERBOSE_MODE
	Serial.print("Drawn line from (");
	Serial.print(x1);
	Serial.print(", ");
	Serial.print(y1);
	Serial.print(") to (");
	Serial.print(x2);
	Serial.print(", ");
	Serial.print(y2);
	Serial.println(")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawChar(uint16_t x, uint16_t y, char c, uint16_t height, uint32_t color) {
#if VERBOSE_MODE
	Serial.print("Drawn char ");
	Serial.print(c);
	Serial.print(" at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.print(y);
	Serial.println(")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawText(uint16_t x, uint16_t y, const String& text, uint16_t textSize, uint32_t color) {
#if VERBOSE_MODE
	Serial.print("Drawn text \"");
	Serial.print(text);
	Serial.print("\" at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.print(y);
	Serial.println(")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
#if VERBOSE_MODE
	Serial.print("Drawn circle at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.print(y);
	Serial.print(") with radius ");
	Serial.println(radius);
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayFillCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
#if VERBOSE_MODE
	Serial.print("Filled circle at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.print(y);
	Serial.print(") with radius ");
	Serial.println(radius);
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint32_t color) {
#if VERBOSE_MODE
	Serial.print("Drawn rect from (");
	Serial.print(x1);
	Serial.print(", ");
	Serial.print(y1);
	Serial.print(") to (");
	Serial.print(x2);
	Serial.print(", ");
	Serial.print(y2);
	Serial.println(")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayFillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint32_t color) {
#if VERBOSE_MODE
	Serial.print("Filled rect from (");
	Serial.print(x1);
	Serial.print(", ");
	Serial.print(y1);
	Serial.print(") to (");
	Serial.print(x2);
	Serial.print(", ");
	Serial.print(y2);
	Serial.println(")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t x3, uint16_t y3, uint32_t color) {
	// Has to be implemented by the user
#if VERBOSE_MODE
	Serial.print("Drawn triangle between (");
	Serial.print(x1);
	Serial.print(", ");
	Serial.print(y1);
	Serial.print("), (");
	Serial.print(x2);
	Serial.print(", ");
	Serial.print(y2);
	Serial.print(") and (");
	Serial.print(x3);
	Serial.print(", ");
	Serial.print(y3);
	Serial.println(")");
#endif
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayFillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
		uint16_t x3, uint16_t y3, uint32_t color) {
	// Has to be implemented by the user
#if VERBOSE_MODE
	Serial.print("Filled triangle between (");
	Serial.print(x1);
	Serial.print(", ");
	Serial.print(y1);
	Serial.print("), (");
	Serial.print(x2);
	Serial.print(", ");
	Serial.print(y2);
	Serial.print(") and (");
	Serial.print(x3);
	Serial.print(", ");
	Serial.print(y3);
	Serial.println(")");
#endif
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawBitmap(uint16_t x, uint16_t y, uint16_t* bitmap) {
	// Has to be implemented by the user
#if VERBOSE_MODE
	Serial.print("Drawn bitmap at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.print(y);
	Serial.println(")");
#endif
	return NOT_IMPLEMENTED;
}

