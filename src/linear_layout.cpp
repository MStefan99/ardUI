//
// Created by MStefan99 on 23.12.19.
//

#include "linear_layout.h"


linearLayout::linearLayout(): drawable(0, 0, ardUiDisplayGetWidth(), ardUiDisplayGetHeight()) {}


linearLayout::linearLayout(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2): drawable(x1, y1, x2, y2) {}


void linearLayout::addView(view *view) {
    auto vb = view->getViewBox();
    if (isVertical) {
        vb += point(0, lastY);
        lastY = vb.getBottomRightPoint().getY();
        view->viewBox = vb;
        view->viewBox.bottomRight.setX(viewBox.bottomRight.getX());

    } else {
        vb += point(lastX, 0);
        lastX = vb.getBottomRightPoint().getX();
        view->viewBox = vb;
        view->viewBox.bottomRight.setY(viewBox.bottomRight.getY());
    }

    viewGroup::addView(view);
}
