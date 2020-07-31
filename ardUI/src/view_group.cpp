//
// Created by MStefan99 on 17.12.19.
//

#include "view_group.h"


ViewGroup::~ViewGroup() {
	for (auto e : viewList) {
		delete e;
	}
}


void ViewGroup::addView(View* view) {
	viewList.push_back(view);
}


View* ViewGroup::findViewById(int id) {
	int count = getChildCount();
	for (int i = 0; i < count; ++i) {
		View& v = getChildAt(i);
		if (v.findViewById(id)) {
			return v.findViewById(id);
		}
	}
	return nullptr;
}


int ViewGroup::getChildCount() {
	return viewList.size();
}


View& ViewGroup::getChildAt(int i) {
	return *viewList[i];
}

