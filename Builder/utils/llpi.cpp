//
// Created by MStefan99 on 7.4.21.
//

//
// Created by MStefan99 on 16.12.19.
//

/* This is the low-level platform interface. You'll need to implement the following functions to work on your
 * hardware to use the ardUI library.
 */

#include "llpi.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#pragma clang diagnostic ignored "-Wgnu-statement-expression"
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#ifdef __EMSCRIPTEN__

#include <emscripten.h>


uint16_t arduiDisplayGetHeight() {
	return (uint16_t)EM_ASM_INT(
		return display.getHeight();
	);
}


uint16_t arduiDisplayGetWidth() {
	return (uint16_t)EM_ASM_INT(
		return display.getWidth();
	);
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
	return EM_ASM_INT(
		return display.isClicked();
	);
}


uint16_t arduiDisplayGetClickX() {
	return (uint16_t)EM_ASM_INT(
		return display.getClickX();
	);
}


uint16_t arduiDisplayGetClickY() {
	return (uint16_t)EM_ASM_INT(
		return display.getClickY();
	);
}


ReturnCode arduiDisplayInit() {
#if defined(VERBOSE) && defined(DEBUG)
	Serial.println("Display init");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayOn() {
#ifdef VERBOSE
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayOff() {
#ifdef VERBOSE
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplaySetBrightness(uint8_t brightness) {
#ifdef VERBOSE
	Serial.print("Display brightness set to ");
	Serial.println(brightness);
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayFill(uint16_t color) {
#ifdef VERBOSE
	Serial.println("Display filled");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawPixel(uint16_t x, uint16_t y, uint32_t color) {
#ifdef VERBOSE
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
#ifdef VERBOSE
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
	EM_ASM({
					 display.drawLine($0, $1, $2, $3, $4);
				 }, x1, y1, x2, y2, color);
	return OK;
}


ReturnCode arduiDisplayDrawChar(uint16_t x, uint16_t y, uint16_t height, char c, uint32_t color) {
#ifdef VERBOSE
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


ReturnCode arduiDisplayDrawText(uint16_t x, uint16_t y, const String& text, uint16_t height, uint32_t color) {
#ifdef VERBOSE
	Serial.print("Drawn text \"");
	Serial.print(text);
	Serial.print("\" at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.print(y);
	Serial.println(")");
#endif
	EM_ASM({
					 display.drawText($0, $1, UTF8ToString($2), $3, $4);
				 }, x, y, text.c_str(), height, color);
	return OK;
}


ReturnCode arduiDisplayDrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
#ifdef VERBOSE
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
#ifdef VERBOSE
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
#ifdef VERBOSE
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
	EM_ASM({
					 display.drawRect($0, $1, $2, $3, $4);
				 }, x1, y1, x2, y2, color);
	return OK;
}


ReturnCode arduiDisplayFillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
																uint32_t color) {
#ifdef VERBOSE
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
	EM_ASM({
					 display.fillRect($0, $1, $2, $3, $4);
				 }, x1, y1, x2, y2, color);
	return OK;
}


ReturnCode arduiDisplayDrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
																		uint16_t x3, uint16_t y3, uint32_t color) {
	// Has to be implemented by the user
#ifdef VERBOSE
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
	Serial.println(y3);
#endif
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayFillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
																		uint16_t x3, uint16_t y3, uint32_t color) {
	// Has to be implemented by the user
#ifdef VERBOSE
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
	Serial.println(y3);
#endif
	return NOT_IMPLEMENTED;
}


ReturnCode arduiDisplayDrawBitmap(uint16_t x, uint16_t y, uint16_t* bitmap) {
	// Has to be implemented by the user
#ifdef VERBOSE
	Serial.print("Drawn bitmap at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.println(y);
#endif
	return NOT_IMPLEMENTED;
}


#endif

#pragma clang diagnostic pop
