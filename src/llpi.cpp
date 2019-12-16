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


returnCode ardUiDisplaySetBrightness(const uint8_t brightness) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayFill(const uint16_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawPixel(const uint16_t x, const uint16_t y, const uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawLine(const uint16_t x, const uint16_t y, const uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawChar(const uint16_t x, const uint16_t y, const uint16_t height, const char text) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawText(const uint16_t x, const uint16_t y, const uint16_t height, const String& text) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawCircle(const uint16_t x, const uint16_t y, const uint16_t radius) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayFillCircle(const uint16_t x, const uint16_t y, const uint16_t radius) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawRect(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2,
        const uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayFillRect(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2,
        const uint32_t color) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawTriangle(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2,
        const uint16_t x3, const uint16_t y3) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayFillTriangle(const uint16_t x1, const uint16_t y1, const uint16_t x2, const uint16_t y2,
        const uint16_t x3, const uint16_t y3) {
    //TODO: Implement.
    return NotImplemented;
}


returnCode ardUiDisplayDrawBitmap(const uint16_t x, const uint16_t y, const uint16_t* bitmap) {
    //TODO: Implement.
    return NotImplemented;
}

