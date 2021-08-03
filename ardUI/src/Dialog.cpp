//
// Created by MStefan99 on 28.7.21.
//

#include "Dialog.h"


Dialog::Dialog(Activity* activity):
		_ownerActivity {activity} {
	// Nothing to do
}


Activity* Dialog::getOwnerActivity() const {
	return _ownerActivity;
}


void Dialog::setRootView(View* view) {
	_rootView = view;
}


void Dialog::onCreate() {
	// Nothing to do
}


void Dialog::onStop() {
	// Nothing to do
}


void Dialog::measure(View::MeasureSpec widthMeasureSpec, View::MeasureSpec heightMeasureSpec) {
	if (_rootView) {
		_rootView->measure(widthMeasureSpec, heightMeasureSpec);
	}
}


void Dialog::layout(int16_t left, int16_t top, int16_t right, int16_t bottom) {
	if (_rootView) {
		_rootView->layout(left, top, right, bottom);
	}
}


void Dialog::draw() const {
	if (_rootView) {
		_rootView->draw();
	}
}


View* Dialog::handleEvent(const Event& event) {
	if (_rootView) {
		return _rootView->handleEvent(event);
	}
	return nullptr;
}
