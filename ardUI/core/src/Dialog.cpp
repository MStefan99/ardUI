//
// Created by MStefan99 on 28.7.21.
//

#include "Dialog.hpp"


Activity* Dialog::getOwnerActivity() {
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
		_rootView->measure(View::MeasureSpec {
						static_cast<uint16_t>(widthMeasureSpec.getSize() * 4 / 5),
						View::MeasureSpec::AT_MOST},
				View::MeasureSpec {static_cast<uint16_t>(heightMeasureSpec.getSize() * 3 / 5),
						View::MeasureSpec::AT_MOST});
	}
}


void Dialog::layout(int16_t left, int16_t top, int16_t right, int16_t bottom) {
	if (_rootView) {
		int16_t l {static_cast<int16_t>((left + right - _rootView->getMeasuredWidth()) / 2)};
		int16_t t {static_cast<int16_t>((top + bottom - _rootView->getMeasuredHeight()) / 2)};

		_rootView->layout({
				static_cast<int16_t>(l),
				static_cast<int16_t>(t),
				static_cast<int16_t>(l + _rootView->getMeasuredWidth()),
				static_cast<int16_t>(t + _rootView->getMeasuredHeight())
		});
	}
}


void Dialog::draw() const {
	if (_rootView) {
		if (!_rootView->isValid()) {
			DISPLAY_UTIL::fill({DEFAULT_DIALOG_BACKGROUND_COLOR});
		}
		_rootView->draw();
	}
}


View* Dialog::handleEvent(const Event& event) {
	if (_rootView && _rootView->getBounds().contains(event.targetX, event.targetY)) {
		return _rootView->handleEvent(event);
	}
	return nullptr;
}
