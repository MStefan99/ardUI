//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_LLPI_H
#define ARDUI_LLPI_H

#include "platform.h"
#include <time.h>

enum returnCode {
    Ok,
    Fail,
    NotImplemented
};


uint16_t ardUiDisplayGetHeight();
uint16_t ardUiDisplayGetWidth();
uint16_t ardUiDisplayGetFontHeight();
uint16_t ardUiDisplayGetFontWidth();

bool ardUiDisplayIsClicked();
void ardUiDisplayClickLocation(uint16_t& x, uint16_t& y);

tm ardUiGetRealTime();

returnCode ardUiDisplayInit();
returnCode ardUiDisplayOn();
returnCode ardUiDisplayOff();
returnCode ardUiDisplaySetBrightness(uint8_t brightness);
returnCode ardUiDisplayFill(uint16_t color);
returnCode ardUiDisplayDrawPixel(uint16_t x, uint16_t y, uint32_t color);
returnCode ardUiDisplayDrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
returnCode ardUiDisplayDrawChar(uint16_t x, uint16_t y, uint16_t height, char text, uint32_t color);
returnCode ardUiDisplayDrawText(uint16_t x, uint16_t y, uint16_t height, const String& tex, uint32_t color);
returnCode ardUiDisplayDrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color);
returnCode ardUiDisplayFillCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color);
returnCode ardUiDisplayDrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
returnCode ardUiDisplayFillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
returnCode ardUiDisplayDrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
        uint16_t x3, uint16_t y3, uint32_t color);
returnCode ardUiDisplayFillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
        uint16_t x3, uint16_t y3, uint32_t color);
returnCode ardUiDisplayDrawBitmap(uint16_t x, uint16_t y, uint16_t* bitmap);


#endif //ARDUI_LLPI_H
