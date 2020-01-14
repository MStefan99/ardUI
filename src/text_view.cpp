//
// Created by MStefan99 on 16.12.19.
//

#include "llpi.h"
#include "text_view.h"


textView::textView(const String& text):
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


void textView::onDraw() {
    ardUiDisplayDrawText(getBounds().top, getBounds().left,
                         textSize, text, textColor);
}
