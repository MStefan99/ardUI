//
// Created by MStefan99 on 16.12.19.
//

/* This is the low-level platform interface. You'll need to implement the following functions to work on your
 * hardware to use the ardUI library. */

#include "llpi.h"
//TODO: replace enum with custom exception

uint16_t ardUiDisplayGetHeight() {
    //TODO: Implement.
    return NotImplemented;
}


uint16_t ardUiDisplayGetWidth() {
    //TODO: Implement.
    return NotImplemented;
}


bool ardUiDisplayIsClicked() {
    //TODO: Implement.
    return true;
}


void ardUiDisplayClickLocation(uint16_t& x, uint16_t& y) {
    //TODO: Implement.
    x = 0;
    y = 0;
}


tm ardUiGetRealTime() {
    //TODO: Implement.
    return {};
}


returnCode ardUiDisplayInit() {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayOn() {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayOff() {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplaySetBrightness(uint8_t brightness) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayFill(uint16_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawPixel(uint16_t x, uint16_t y, uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawLine(uint16_t x, uint16_t y, uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawChar(uint16_t x, uint16_t y, uint16_t height, char text, uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawText(uint16_t x, uint16_t y, uint16_t height, const String& text, uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayFillCircle(uint16_t x, uint16_t y, uint16_t radius, uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
        uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayFillRect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
        uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
        uint16_t x3, uint16_t y3, uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayFillTriangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,
        uint16_t x3, uint16_t y3, uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawBitmap(uint16_t x, uint16_t y, uint16_t* bitmap) {
    //TODO: Implement.
    return NotImplemented;
}

