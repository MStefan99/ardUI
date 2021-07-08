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


uint16_t ardui::display::GetHeight() {
	return (uint16_t)EM_ASM_INT(
		return display.getHeight();
	);
}


uint16_t ardui::display::GetWidth() {
	return (uint16_t)EM_ASM_INT(
		return display.getWidth();
	);
}


uint16_t ardui::display::GetFontHeight() {
	// Has to be implemented by the user
	return 8;
}


uint16_t ardui::display::GetCharWidth(char c, uint16_t height) {
	char s[2] = {c};
	return (uint16_t)EM_ASM_INT({
																return display.getTextWidth(UTF8ToString($0), $1);
															}, s, height);
}


bool ardui::display::IsClicked() {
	return EM_ASM_INT(
		return display.isClicked();
	);
}


uint16_t ardui::display::GetClickX() {
	return (uint16_t)EM_ASM_INT(
		return display.getClickX();
	);
}


uint16_t ardui::display::GetClickY() {
	return (uint16_t)EM_ASM_INT(
		return display.getClickY();
	);
}


ReturnCode ardui::display::Init() {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display init");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode ardui::display::On() {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode ardui::display::Off() {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode ardui::display::SetBrightness(uint8_t brightness) {
#if LOG_LEVEL >= LOG_DRAW
	Serial.print("Display brightness set to ");
	Serial.println(brightness);
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ReturnCode ardui::display::Fill(uint32_t color) {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display filled");
#endif
	EM_ASM({
					 display.fill($0);
				 }, color);
	return OK;
}


ReturnCode ardui::display::DrawPixel(uint16_t x, uint16_t y, uint32_t color) {
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


ReturnCode ardui::display::DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color) {
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
				 }, x1, y1, x2, y2, color);
	return OK;
}


ReturnCode ardui::display::DrawChar(uint16_t x, uint16_t y, char c, uint16_t height, uint32_t color) {
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


ReturnCode ardui::display::DrawText(uint16_t x, uint16_t y, const String& text, uint16_t height, uint32_t color) {
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
				 }, x, y, text.c_str(), height, color);
	return OK;
}


ReturnCode ardui::display::DrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
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


ReturnCode ardui::display::FillCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
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


ReturnCode ardui::display::DrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
																uint32_t color) {
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
				 }, x1, y1, x2, y2, color);
	return OK;
}


ReturnCode ardui::display::FillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
																uint32_t color) {
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
				 }, x1, y1, x2, y2, color);
	return OK;
}


ReturnCode ardui::display::DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
																		uint16_t x3, uint16_t y3, uint32_t color) {
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


ReturnCode ardui::display::FillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
																		uint16_t x3, uint16_t y3, uint32_t color) {
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


ReturnCode ardui::display::DrawBitmap(uint16_t x, uint16_t y, uint16_t* bitmap) {
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
