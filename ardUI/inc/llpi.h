//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_LLPI_H
#define ARDUI_LLPI_H


#include "platform.h"


enum ReturnCode {
	OK,
	FAIL,
	NOT_IMPLEMENTED
};


uint16_t arduiDisplayGetHeight();

uint16_t arduiDisplayGetWidth();

uint16_t arduiDisplayGetFontHeight();

uint16_t arduiDisplayGetFontWidth();

bool arduiDisplayIsClicked();

void arduiDisplayGetClickLocation(uint16_t& x, uint16_t& y);

ReturnCode arduiDisplayInit();

ReturnCode arduiDisplayOn();

ReturnCode arduiDisplayOff();

ReturnCode arduiDisplaySetBrightness(uint8_t brightness);

ReturnCode arduiDisplayFill(uint16_t color);

ReturnCode arduiDisplayDrawPixel(uint16_t x, uint16_t y,
								 uint32_t color);

ReturnCode arduiDisplayDrawLine(uint16_t x1, uint16_t y1,
								uint16_t x2, uint16_t y2,
								uint32_t color);

ReturnCode arduiDisplayDrawChar(uint16_t x, uint16_t y,
								uint16_t height, char c,
								uint32_t color);

ReturnCode arduiDisplayDrawText(uint16_t x, uint16_t y,
								uint16_t height, const String& text,
								uint32_t color);

ReturnCode arduiDisplayDrawCircle(uint16_t x, uint16_t y,
								  uint16_t radius,
								  uint32_t color);

ReturnCode arduiDisplayFillCircle(uint16_t x, uint16_t y,
								  uint16_t radius,
								  uint32_t color);

ReturnCode arduiDisplayDrawRect(uint16_t x1, uint16_t y1,
								uint16_t x2, uint16_t y2,
								uint32_t color);

ReturnCode arduiDisplayFillRect(uint16_t x1, uint16_t y1,
								uint16_t x2, uint16_t y2,
								uint32_t color);

ReturnCode arduiDisplayDrawTriangle(uint16_t x1, uint16_t y1,
									uint16_t x2, uint16_t y2,
									uint16_t x3, uint16_t y3,
									uint32_t color);

ReturnCode arduiDisplayFillTriangle(uint16_t x1, uint16_t y1,
									uint16_t x2, uint16_t y2,
									uint16_t x3, uint16_t y3,
									uint32_t color);

ReturnCode arduiDisplayDrawBitmap(uint16_t x, uint16_t y,
								  uint16_t* bitmap);

#endif //ARDUI_LLPI_H
