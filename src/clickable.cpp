//
// Created by MStefan99 on 19.12.19.
//

#include "clickable.h"


void clickable::setOnClickListener(void (*l)(view *)) {
    onClick = l;
}


void clickable::setOnLongClickListener(void (*l)(view*)) {
    onLongClick = l;
}


void clickable::setClicked(bool b) {
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


bool clickable::isClicked() {
    return inClickedState;
}


bool clickable::isLongClicked() {
    return inLongClickedState;
}
