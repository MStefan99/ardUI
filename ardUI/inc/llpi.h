//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_LLPI_H
#define ARDUI_LLPI_H


#include "platform.h"
#include <ctime>


enum returnCode {
	Ok,
	Fail,
	NotImplemented
};


uint16_t arduiDisplayGetHeight();
uint16_t arduiDisplayGetWidth();
uint16_t arduiDisplayGetFontHeight();
uint16_t arduiDisplayGetFontWidth();

bool arduiDisplayIsClicked();
void arduiDisplayClickLocation(uint16_t& x, uint16_t& y);

tm arduiGetRealTime();

returnCode arduiDisplayInit();
returnCode arduiDisplayOn();
returnCode arduiDisplayOff();
returnCode arduiDisplaySetBrightness(uint8_t brightness);
returnCode arduiDisplayFill(uint16_t color);
returnCode arduiDisplayDrawPixel(uint16_t x, uint16_t y, uint32_t color);
returnCode arduiDisplayDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
returnCode arduiDisplayDrawChar(uint16_t x, uint16_t y, uint16_t height, char text, uint32_t color);
returnCode arduiDisplayDrawText(uint16_t x, uint16_t y, uint16_t height, const String& tex, uint32_t color);
returnCode arduiDisplayDrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color);
returnCode arduiDisplayFillCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color);
returnCode arduiDisplayDrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
returnCode arduiDisplayFillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
returnCode arduiDisplayDrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
									uint16_t x3, uint16_t y3, uint32_t color);
returnCode arduiDisplayFillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
									uint16_t x3, uint16_t y3, uint32_t color);
returnCode arduiDisplayDrawBitmap(uint16_t x, uint16_t y, uint16_t* bitmap);

#endif //ARDUI_LLPI_H
