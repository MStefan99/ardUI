//
// Created by MStefan99 on 16.12.19.
//

/* This is the low-level platform interface. You'll need to implement the following functions to work on your
 * hardware to use the ardUI library.
 */

#include "display.h"


uint16_t ardui::display::GetHeight() {
	// Has to be implemented by the user
	return 480;
}


uint16_t ardui::display::GetWidth() {
	// Has to be implemented by the user
	return 320;
}


uint16_t ardui::display::GetFontHeight() {
	// Has to be implemented by the user
	return 8;
}


uint16_t ardui::display::GetCharWidth(char c, uint16_t height) {
	// Has to be implemented by the user
	return 5;
}


bool ardui::display::IsClicked() {
	// Has to be implemented by the user
	return false;
}


uint16_t ardui::display::GetClickX() {
	// Has to be implemented by the user
	return 0;
}


uint16_t ardui::display::GetClickY() {
	// Has to be implemented by the user
	return 0;
}


ardui::display::ReturnCode ardui::display::Init() {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display init");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::On() {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::Off() {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display on");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::SetBrightness(uint8_t brightness) {
#if LOG_LEVEL >= LOG_DRAW
	Serial.print("Display brightness set to ");
	Serial.println(brightness);
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::Fill(uint32_t color) {
#if LOG_LEVEL >= LOG_DRAW
	Serial.println("Display filled");
#endif
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::DrawPixel(uint16_t x, uint16_t y, uint32_t color) {
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


ardui::display::ReturnCode ardui::display::DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color) {
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


ardui::display::ReturnCode ardui::display::DrawChar(uint16_t x, uint16_t y, char c, uint16_t height, uint32_t color) {
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


ardui::display::ReturnCode ardui::display::DrawText(uint16_t x, uint16_t y, const String& text, uint16_t textSize, uint32_t color) {
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


ardui::display::ReturnCode ardui::display::DrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
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


ardui::display::ReturnCode ardui::display::FillCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
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


ardui::display::ReturnCode ardui::display::DrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
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
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::FillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
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
	// Has to be implemented by the user
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::DrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
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
	Serial.print(y3);
	Serial.println(")");
#endif
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::FillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
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
	Serial.print(y3);
	Serial.println(")");
#endif
	return NOT_IMPLEMENTED;
}


ardui::display::ReturnCode ardui::display::DrawBitmap(uint16_t x, uint16_t y, uint16_t* bitmap) {
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

