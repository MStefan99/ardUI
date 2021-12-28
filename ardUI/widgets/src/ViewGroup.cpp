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


View* ViewGroup::getChildAt(int index) const {
	auto it = _viewList.begin();
	for (int i {0}; i < index; ++i) {
		++it;
	}
	return *it;
}


int ViewGroup::getChildCount() const {
	return static_cast<int>(_viewList.size());
}


void ViewGroup::removeView(View* view) {
	_viewList.remove(view);
}


void ViewGroup::removeViewAt(int index) {
	auto it = _viewList.begin();
	for (int i {0}; i < index; ++i) {
		++it;
	}
	_viewList.erase(it);
}


void ViewGroup::removeViews(int start, int count) {
	auto it = _viewList.begin();
	for (int i {0}; i < start; ++i) {
		++it;
	}
	for (int i {0}; i < start; ++i) {
		it = _viewList.erase(it);
	}
}


void ViewGroup::removeAllViews() {
	_viewList.clear();
}


View* ViewGroup::findViewById(int id) {
	for (auto view : _viewList) {
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
	onDraw();
	for (auto view: _viewList) {
		view->draw();
	}
	_valid = true;
}


View* ViewGroup::handleEvent(const Event& event) {
	// TODO: fix event handling (listeners not called)
	for (auto view: _viewList) {
		if (view->getBounds().contains(event.targetX, event.targetY)) {
			return view->handleEvent(event);
		}
	}
	return nullptr;
}
