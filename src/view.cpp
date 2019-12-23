//
// Created by MStefan99 on 16.12.19.
//

#include "view.h"


view::view(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2): drawable(x1, y1, x2, y2) {}


int view::lastViewId {0};


void view::forEach(void (*predicate)(view *)) {
    predicate(this);
}


int view::getId() {
    return viewId;
}


