//
// Created by MStefan99 on 16.12.19.
//

#include <llpi.h>
#include "textView.h"

void textView::setText(const String& text) {
    str = text;
}


void textView::append(const String &text) {
    str += text;
}


void textView::setTextSize(uint16_t size) {
    textSize = size;
}


void textView::setCurrentTextColor(uint32_t color) {
    clr = color;
}


String& textView::getText() {
    return str;
}


uint16_t textView::getTextSize() {
    return textSize;
}


uint32_t textView::getCurrentTextColor() {
    return clr;
}


void textView::draw() const {
    // TODO: add textView drawing
}