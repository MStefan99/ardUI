//
// Created by MStefan99 on 16.12.19.
//

#include "view.h"


int view::lastViewId {0};


view::view(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) :
        viewBox(point(x1, y1), point(x2, y2)) {}


void view::setOnClickListener(void (*l)(view *)) {
    onClickHandler = l;
}


void view::setOnLongClickListener(void (*l)(view*)) {
    onLongClickHandler = l;
}


void view::setOnScrollListener(void (*l)(view*)) {
    onScrollHandler = l;
}


