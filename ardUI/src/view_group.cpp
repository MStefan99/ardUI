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
	for (const auto& view : viewList) {
		if (view->findViewById(id)) {
			return view->findViewById(id);
		}
	}
	return nullptr;
}


void ViewGroup::invalidate() {
	invalidateSelf();
	for (auto view : viewList) {
		view->invalidate();
	}
}


void ViewGroup::draw() {
	for (auto view: viewList) {
		if (!view->isValid() && view->isVisible()) {
			view->draw();
		}
	}
}
