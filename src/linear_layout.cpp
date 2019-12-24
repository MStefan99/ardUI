//
// Created by MStefan99 on 23.12.19.
//

#include "linear_layout.h"


linearLayout::linearLayout(bool vertical):
        isVertical(vertical) {}


void linearLayout::addView(view* view) {
    auto vb = view->getBounds();
    if (isVertical) {
        lastY += vb.bottom;
        vb.offset(0, lastY);
        vb.right = getBounds().right;
        view->setBounds(vb);

    } else {
        lastX += vb.right;
        vb.offset(lastX, 0);
        vb.bottom = getBounds().bottom;
        view->setBounds(vb);
    }

    viewGroup::addView(view);
}
