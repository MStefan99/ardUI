//
// Created by MStefan99 on 19.12.19.
//

#include "button_view.h"


buttonView::buttonView(const String &text):
        drawable(0, 0, ardUiDisplayGetFontWidth() * text.length(), ardUiDisplayGetFontHeight()),
        textView(text) {}


buttonView::buttonView(const String &text, uint16_t x, uint16_t y):
        drawable(x, y, ardUiDisplayGetFontWidth() * text.length(), ardUiDisplayGetFontHeight()),
        textView(text) {}


buttonView::buttonView(const String &text, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2):
        drawable(x1, y1, x2, y2),
        textView(text) {}


void buttonView::draw() const {
    auto tl {viewBox.getTopLeftPoint()};
    auto br {viewBox.getBottomRightPoint()};

    ardUiDisplayDrawLine(tl.getX(), tl.getY(), br.getX(), tl.getY(), borderColor);  // top
    ardUiDisplayDrawLine(tl.getX(), tl.getY(), tl.getX(), br.getY(), borderColor);  // left
    ardUiDisplayDrawLine(br.getX(), tl.getY(), br.getX(), br.getY(), borderColor);  // right
    ardUiDisplayDrawLine(tl.getX(), br.getY(), br.getX(), br.getY(), borderColor);  // bottom
    ardUiDisplayDrawText(tl.getX(), tl.getY(), getTextSize(), getText(), getTextColor());
}
