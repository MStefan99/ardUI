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
    viewList.push_back(view);
}


view* viewGroup::findViewById(int id) {
    int count = getChildCount();
    for (int i = 0; i < count; ++i) {
        view& v = getChildAt(i);
        if (v.findViewById(id)) {
            return v.findViewById(id);
        }
    }
    return nullptr;
}


int viewGroup::getChildCount() {
    return viewList.size();
}


view& viewGroup::getChildAt(int i) {
    return *viewList[i];
}

