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
    inClickedState = b;
}


void clickable::setLongClicked(bool b) {
    inLongClickedState = b;
}


bool clickable::isClicked() {
    return inClickedState;
}


bool clickable::isLongClicked() {
    return inLongClickedState;
}
