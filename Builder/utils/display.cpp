//
// Created by MStefan99 on 7.4.21.
//

//
// Created by MStefan99 on 16.12.19.
//

/* This is the low-level platform interface. You'll need to implement the following functions to work on your
 * hardware to use the ardUI library.
 */

#include "display.h"


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#pragma clang diagnostic ignored "-Wgnu-statement-expression"
#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
#ifdef __EMSCRIPTEN__

#include <emscripten.h>


uint16_t ardui::display::getHeight() {
	return (uint16_t)EM_ASM_INT(
		return display.getHeight();
	);
}


uint16_t ardui::display::getWidth() {
	return (uint16_t)EM_ASM_INT(
		return display.getWidth();
	);
}


uint16_t ardui::display::getFontHeight() {
	// Has to be implemented by the user
	return 8;
}


uint16_t ardui::display::getCharWidth(char c, uint16_t height) {
	char s[2] = {c};
	return (uint16_t)EM_ASM_INT({
																return display.getTextWidth(UTF8ToString($0), $1);
															}, s, height);
}


bool ardui::display::isClicked() {
	return EM_ASM_INT(
		return display.isClicked();
	);
}


uint16_t ardui::display::getClickX() {
	return (uint16_t)EM_ASM_INT(
		return display.getClickX();
	);
}


uint16_t ardui::display::getClickY() {
	return (uint16_t)EM_ASM_INT(
		return display.getClickY();
	);
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
	EM_ASM({
					 display.fill($0);
				 }, color.to888());
	return OK;
}


ardui::display::ReturnCode ardui::display::drawPixel(uint16_t x, uint16_t y, Color color) {
#if LOG_LEVEL >= LOG_DRAW
	Serial.print("Drawn pixel at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.print(y);
	Serial.println(")");
#endif
	// Has to be implemented by the user
	EM_ASM({
		display.drawPixel($0, $1, $2);
	}, x, y, color.to888());
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::drawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, Color color) {
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
	EM_ASM({
					 display.drawLine($0, $1, $2, $3, $4);
				 }, x1, y1, x2, y2, color.to888());
	return OK;
}


ardui::display::ReturnCode ardui::display::drawChar(uint16_t x, uint16_t y, char c, uint16_t height, Color color) {
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


ardui::display::ReturnCode ardui::display::drawText(uint16_t x, uint16_t y, const String& text, uint16_t height, Color color) {
#if LOG_LEVEL >= LOG_DRAW
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
				 }, x, y, text.c_str(), height, color.to888());
	return OK;
}


ardui::display::ReturnCode ardui::display::drawCircle(uint16_t x, uint16_t y, uint16_t radius, Color color) {
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


ardui::display::ReturnCode ardui::display::fillCircle(uint16_t x, uint16_t y, uint16_t radius, Color color) {
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


ardui::display::ReturnCode ardui::display::drawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
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
	EM_ASM({
					 display.drawRect($0, $1, $2, $3, $4);
				 }, x1, y1, x2, y2, color.to888());
	return OK;
}


ardui::display::ReturnCode ardui::display::fillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
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
	EM_ASM({
					 display.fillRect($0, $1, $2, $3, $4);
				 }, x1, y1, x2, y2, color.to888());
	return OK;
}


ardui::display::ReturnCode ardui::display::drawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
																		uint16_t x3, uint16_t y3, Color color) {
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
	Serial.println(y3);
#endif
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::fillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
																		uint16_t x3, uint16_t y3, Color color) {
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
	Serial.println(y3);
#endif
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::drawBitmap(uint16_t x, uint16_t y, uint16_t* bitmap) {
	// Has to be implemented by the user
#if LOG_LEVEL >= LOG_DRAW
	Serial.print("Drawn bitmap at (");
	Serial.print(x);
	Serial.print(", ");
	Serial.println(y);
#endif
	return NOT_IMPLEMENTED;
}


#endif

#pragma clang diagnostic pop
