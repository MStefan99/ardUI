//
// Created by MStefan99 on 16.12.19.
//

#include "view.h"


int view::lastViewId {0};


view::view(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) :
        viewBox(point(x1, y1), point(x2, y2)) {}


void view::forEach(void (*predicate)(view *)) {
    predicate(this);
}


int view::getId() {
    return viewId;
}


bool view::coordsInside(uint16_t x, uint16_t y) {
    return viewBox.pointInside(point(x, y));
}
