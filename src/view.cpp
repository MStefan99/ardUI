//
// Created by MStefan99 on 16.12.19.
//

#include "view.h"


int view::lastViewId {0};


void view::forEach(void (*predicate)(view *)) {
    predicate(this);
}


int view::getId() {
    return viewId;
}
