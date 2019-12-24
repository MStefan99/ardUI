//
// Created by MStefan99 on 19.12.19.
//

#include "button_view.h"


buttonView::buttonView(const String &text):
        textView(text) {}


void buttonView::draw() const {
    auto b {getBounds()};

    ardUiDisplayDrawLine(b.left, b.top, b.right, b.top, borderColor);  // top
    ardUiDisplayDrawLine(b.left, b.top, b.left, b.bottom, borderColor);  // left
    ardUiDisplayDrawLine(b.right, b.top, b.right, b.bottom, borderColor);  // right
    ardUiDisplayDrawLine(b.left, b.bottom, b.right, b.bottom, borderColor);  // bottom
    ardUiDisplayDrawText(b.left, b.top, getTextSize(), getText(), getTextColor());
}
