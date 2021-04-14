//
// Created by MStefan99 on 17.12.19.
//

#include "ViewGroup.h"


ViewGroup::~ViewGroup() {
	for (auto e : _viewList) {
		delete e;
	}
}


void ViewGroup::addView(View* view) {
	_viewList.push_back(view);
}


View* ViewGroup::findViewById(int id) {
	for (const auto& view : _viewList) {
		if (view->findViewById(id)) {
			return view->findViewById(id);
		}
	}
	return nullptr;
}


void ViewGroup::invalidate() {
	invalidateSelf();
	for (auto view : _viewList) {
		view->invalidate();
	}
}


void ViewGroup::draw() {
	_valid = true;
	for (auto view: _viewList) {
		if (!view->isValid() && view->isVisible()) {
			view->draw();
		}
	}
}
