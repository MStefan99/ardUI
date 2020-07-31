//
// Created by MStefan99 on 23.12.19.
//

#include "linear_layout.h"


linearLayout::linearLayout(bool vertical):
        isVertical(vertical) {}


void linearLayout::onMeasure(uint16_t w, uint16_t h) {
    for (const auto &v : viewList) {
        v->measure(view::measureSpec::makeMeasureSpec(view::measureSpec::AT_MOST, w),
                   view::measureSpec::makeMeasureSpec(view::measureSpec::AT_MOST, h));
    }
}

void linearLayout::onLayout(bool changed, uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
    int viewLeft {0};
    int viewTop {0};
    int layoutRight {ardUiDisplayGetWidth()};
    int layoutBottom {ardUiDisplayGetHeight()};

    for (const auto& v : viewList) {
        v->setTop(viewTop);
        v->setLeft(viewLeft);

        if (isVertical) {
            viewTop += v->getMeasuredHeight();
            v->setBottom(viewTop);
            v->setRight(layoutRight);

        } else {
            viewLeft += v->getMeasuredWidth();
            v->setRight(viewLeft);
            v->setBottom(layoutBottom);
        }
    }
}


void linearLayout::onDraw() {
    for (const auto& v : viewList) {
        v->draw();
    }
}
