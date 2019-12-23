//
// Created by MStefan99 on 16.12.19.
//

#include "llpi.h"
#include "text_view.h"


textView::textView(const String& text):
        drawable(0, 0, ardUiDisplayGetFontWidth() * text.length(), ardUiDisplayGetFontHeight()),
        text(text) {}


textView::textView(const String &text, uint16_t x, uint16_t y):
        drawable(x, y, ardUiDisplayGetFontWidth() * text.length(), ardUiDisplayGetFontHeight()),
        text(text) {}


textView::textView(const String &text, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2):
        drawable(x1, y1, x2, y2),
        text(text) {}


void textView::setText(const String &textToSet) {
    text = textToSet;
}


void textView::append(const String &textToAppend) {
    text += textToAppend;
}


void textView::setTextSize(uint16_t size) {
    textSize = size;
}


void textView::setTextColor(uint32_t color) {
    textColor = color;
}


String textView::getText() const {
    return text;
}


uint16_t textView::getTextSize() const {
    return textSize;
}


uint32_t textView::getTextColor() const {
    return textColor;
}


void textView::draw() const {
    ardUiDisplayDrawText(viewBox.getTopLeftPoint().getX(), viewBox.getTopLeftPoint().getY(),
                         textSize, text, textColor);
}
