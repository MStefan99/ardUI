//
// Created by MStefan99 on 11.7.21.
//

#include "ScrollLayout.h"


void ScrollLayout::onLayout(bool changed, int16_t l, int16_t t, int16_t r, int16_t b) {
	int16_t nextViewLeft {l};
	int16_t nextViewTop = t + _offset;

	for (const auto& v : _viewList) {
		v->setTop(nextViewTop);
		v->setLeft(nextViewLeft);

		if (_orientation == Orientation::HORIZONTAL) {
			v->layout(nextViewLeft, nextViewTop, static_cast<int16_t>(nextViewLeft + v->getMeasuredWidth()), b);
			nextViewLeft += v->getMeasuredWidth();
		} else {
			v->layout(nextViewLeft, nextViewTop, r, static_cast<int16_t>(nextViewTop + v->getMeasuredHeight()));
			nextViewTop += v->getMeasuredHeight();
		}
	}
}


void ScrollLayout::draw() {
	for (const auto& v : _viewList) {
		if (v->getBounds().intersects(_viewBox)) {
			v->draw();
		}
	}
	_valid = true;
}


View* ScrollLayout::handleEvent(const Event& event) {
	if (event.currentAction == Event::SCROLL) {
		_offset += event.deltaY;
		invalidate();
		return this;
	} else {
		for (auto view: _viewList) {
			if (view->getBounds().contains(event.targetX, event.targetY)) {
				return view->handleEvent(event);
			}
		}
		return nullptr;
	}
}
