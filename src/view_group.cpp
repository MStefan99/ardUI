//
// Created by MStefan99 on 17.12.19.
//

#include "view_group.h"


viewGroup::~viewGroup() {
    for (auto e : viewList) {
        delete e;
    }
}


void viewGroup::addView(view* view) {
    viewList.append(view);
}


void viewGroup::draw() const {
    for (auto v : viewList) {
        v->draw();
    }
}

