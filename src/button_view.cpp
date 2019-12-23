//
// Created by MStefan99 on 19.12.19.
//

#include "button_view.h"


buttonView::buttonView(const String &text, uint32_t backgroundColor):
        backgroundColor(backgroundColor) {}


void buttonView::draw() const {
    auto tl {viewBox.getTopLeftPoint()};
    auto br {viewBox.getBottomRightPoint()};

    ardUiDisplayDrawLine(tl.getX(), tl.getY(), br.getX(), tl.getY(), bevel_color);  // top
    ardUiDisplayDrawLine(tl.getX(), tl.getY(), tl.getX(), br.getY(), bevel_color);  // left
    ardUiDisplayDrawLine(br.getX(), tl.getY(), br.getX(), br.getY(), bevel_color);  // right
    ardUiDisplayDrawLine(tl.getX(), br.getY(), br.getX(), br.getY(), bevel_color);  // bottom
    ardUiDisplayDrawText(tl.getX(), tl.getY(), getTextSize(), getText(), getTextColor());
}
