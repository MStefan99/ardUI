//
// Created by MStefan99 on 16.12.19.
//

/* This is the low-level platform interface. You'll need to implement the following functions to work on your
 * hardware to use the ardUI library.
 */

#include "display.h"


int16_t ardui::display::getHeight() {
	// Has to be implemented by the user
	return 480;
}


int16_t ardui::display::getWidth() {
	// Has to be implemented by the user
	return 320;
}


uint16_t ardui::display::getCharWidth(char c, uint16_t height) {
	// Has to be implemented by the user
	return 5;
}


bool ardui::display::isClicked() {
	// Has to be implemented by the user
	return false;
}


int16_t ardui::display::getClickX() {
	// Has to be implemented by the user
	return 0;
}


int16_t ardui::display::getClickY() {
	// Has to be implemented by the user
	return 0;
}


ardui::display::ReturnCode ardui::display::init() {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display init");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::on() {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::off() {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::setBrightness(uint8_t brightness) {
#if LOG_LEVEL >= LOG_DRAW
	Serial.print("Display brightness set to ");
	Serial.println(brightness);
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::fill(Color color) {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display filled");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::drawPixel(int16_t x, int16_t y, Color color) {
#if LOG_LEVEL >= LOG_DRAW
	Serial.print("Drawn pixel at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.print(y);
	Serial.println(")");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::drawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, Color color) {
#if LOG_LEVEL >= LOG_DRAW
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


ardui::display::ReturnCode ardui::display::drawChar(int16_t x, int16_t y, char c, uint16_t height, Color color) {
#if LOG_LEVEL >= LOG_DRAW
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


ardui::display::ReturnCode ardui::display::drawText(int16_t x, int16_t y, const String& text, uint16_t textSize, Color color) {
#if LOG_LEVEL >= LOG_DRAW
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


ardui::display::ReturnCode ardui::display::drawCircle(int16_t x, int16_t y, int16_t radius, Color color) {
#if LOG_LEVEL >= LOG_DRAW
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


ardui::display::ReturnCode ardui::display::fillCircle(int16_t x, int16_t y, int16_t radius, Color color) {
#if LOG_LEVEL >= LOG_DRAW
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


ardui::display::ReturnCode ardui::display::drawRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
		Color color) {
#if LOG_LEVEL >= LOG_DRAW
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


ardui::display::ReturnCode ardui::display::fillRect(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
		Color color) {
#if LOG_LEVEL >= LOG_DRAW
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


ardui::display::ReturnCode ardui::display::drawTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
		int16_t x3, int16_t y3, Color color) {
	// Has to be implemented by the user
#if LOG_LEVEL >= LOG_DRAW
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


ardui::display::ReturnCode ardui::display::fillTriangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
		int16_t x3, int16_t y3, Color color) {
	// Has to be implemented by the user
#if LOG_LEVEL >= LOG_DRAW
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


ardui::display::ReturnCode ardui::display::drawBitmap(int16_t x, int16_t y, int16_t* bitmap) {
	// Has to be implemented by the user
#if LOG_LEVEL >= LOG_DRAW
	Serial.print("Drawn bitmap at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.print(y);
	Serial.println(")");
#endif
	return NOT_IMPLEMENTED;
}

