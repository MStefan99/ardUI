//
// Created by MStefan99 on 16.12.19.
//

#include "view.h"


int view::lastViewId {0};


view::view(): viewId(++lastViewId) {}


int view::getId() {
    return viewId;
}


void view::draw() const {
    onDraw();
}


void view::measure(uint16_t width, uint16_t height) {
    onMeasure(width, height);
}


void view::layout(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    auto b = getBounds();
    bool changed = left == b.left && top == b.top && bottom == b.bottom && right == b.right;
    if (changed) {
        invalidate();
    }
    onLayout(changed, left, top, right, bottom);
}


void view::invalidate() {
    invalidateSelf();
}


view &view::getParent() const {
    return *parent;
}


void view::setParent(view* p) {
    parent = p;
}


void view::setOnClickListener(void (*l)(view&)) {
    onClick = l;
}


void view::setOnLongClickListener(void (*l)(view&)) {
    onLongClick = l;
}


void view::onDraw() const {
    //TODO: draw
}


void view::onMeasure(uint16_t width, uint16_t height) {
    measuredWidth = width;
    measuredHeight = height;
}


void view::onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
}


void view::setClicked(bool b) {
    if (b) {
        inClickedState = true;
        ++timesClicked;
    } else {
        inClickedState = false;
        inLongClickedState = false;
        timesClicked = 0;
    }

    if (timesClicked > LONG_CLICK_TIME / UPDATE_FREQUENCY) {
        inLongClickedState = true;
    }
}


bool view::isClicked() {
    return inClickedState;
}


bool view::isLongClicked() {
    return inLongClickedState;
}
