//
// Created by MStefan99 on 16.12.19.
//

#include "llpi.h"
#include "text_view.h"


textView::textView(const String& text): textString(text) {}


textView::textView(const String& text, uint16_t size): textString(text), textSize(size) {}


textView::textView(const String& text, uint16_t size, uint32_t color):
        textString(text),
        textSize(size),
        textColor(color) {}


void textView::setText(const String& text) {
    textString = text;
}


void textView::append(const String &text) {
    textString += text;
}


void textView::setTextSize(uint16_t size) {
    textSize = size;
}


void textView::setTextColor(uint32_t color) {
    textColor = color;
}


String& textView::getText() {
    return textString;
}


uint16_t textView::getTextSize() {
    return textSize;
}


uint32_t textView::getCurrentTextColor() {
    return textColor;
}


void textView::draw() const {
    ardUiDisplayDrawText(viewBox.getTopLeftPoint().getX(), viewBox.getTopLeftPoint().getY(),
                         textSize, textString, textColor);
}