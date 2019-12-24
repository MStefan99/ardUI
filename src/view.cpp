//
// Created by MStefan99 on 16.12.19.
//

#include "view.h"


int view::lastViewId {0};


view::view():
        viewId(++lastViewId) {}


void view::forEach(void (*predicate)(view&)) {
    predicate(*this);
}


int view::getId() {
    return viewId;
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
