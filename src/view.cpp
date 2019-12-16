//
// Created by MStefan99 on 16.12.19.
//

#include "view.h"


view::view() :
        onClickHandler(nullptr),
        onLongClickHandler(nullptr),
        x1(0),
        y1(0),
        x2(0),
        y2(0) {}


void view::setOnClickListener(void (*l)(view*)) {
    onClickHandler = l;
}


void view::setOnLongClickListener(void (*l)(view*)) {
    onLongClickHandler = l;
}


void view::setOnScrollListener(void (*l)(view*)) {
    onScrollHandler = l;
}
