//
// Created by MStefan99 on 19.12.19.
//

#include "scrollable.h"


void scrollable::setOnScrollListener(void (*l)(view*)) {
    onScroll = l;
}


void scrollable::setScrolled(bool b) {
    inScrolledState = b;
}


bool scrollable::isScrolled() {
    return inScrolledState;
}
