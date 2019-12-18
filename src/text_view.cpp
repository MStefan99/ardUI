//
// Created by MStefan99 on 16.12.19.
//

#include "llpi.h"
#include "text_view.h"


textView::textView(const String& text): stringContent(text) {}


textView::textView(const String& text, uint16_t size): stringContent(text), textSize(size) {}


textView::textView(const String& text, uint16_t size, uint32_t color):
        stringContent(text),
        textSize(size),
        textColor(color) {}


void textView::setText(const String& text) {
    stringContent = text;
}


void textView::append(const String &text) {
    stringContent += text;
}


void textView::setTextSize(uint16_t size) {
    textSize = size;
}


void textView::setCurrentTextColor(uint32_t color) {
    textColor = color;
}


String& textView::getText() {
    return stringContent;
}


uint16_t textView::getTextSize() {
    return textSize;
}


uint32_t textView::getCurrentTextColor() {
    return textColor;
}


void textView::draw() const {
    ardUiDisplayDrawText(box.getTopLeftPoint().getX(), box.getTopLeftPoint().getY(),
            textSize, stringContent, textColor);
}