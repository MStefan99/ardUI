//
// Created by MStefan99 on 23.12.19.
//

#include "LinearLayout.h"


LinearLayout::Orientation LinearLayout::getOrientation() const {
	return _orientation;
}


void LinearLayout::setOrientation(Orientation orientation) {
	_orientation = orientation;
}


void LinearLayout::onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) {
	if (_orientation == Orientation::HORIZONTAL) {
		for (const auto& v : _viewList) {
			v->measure(View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::UNSPECIFIED,
					View::MeasureSpec::getSize(widthMeasureSpec)),
					View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::AT_MOST,
							View::MeasureSpec::getSize(heightMeasureSpec)));
		}
	} else {
		for (const auto& v : _viewList) {
			v->measure(View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::AT_MOST,
					View::MeasureSpec::getSize(widthMeasureSpec)),
					View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::UNSPECIFIED,
							View::MeasureSpec::getSize(heightMeasureSpec)));
		}
	}
}


void LinearLayout::onLayout(bool changed, uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
	uint16_t nextViewLeft {l};
	uint16_t nextViewTop {t};

	for (const auto& v : _viewList) {
		v->setTop(nextViewTop);
		v->setLeft(nextViewLeft);

		if (_orientation == Orientation::HORIZONTAL) {
			nextViewLeft += v->getMeasuredWidth();
			v->setRight(nextViewLeft);
			v->setBottom(b);
		} else {
			nextViewTop += v->getMeasuredHeight();
			v->setBottom(nextViewTop);
			v->setRight(r);
		}
	}
}


void LinearLayout::onDraw() {
	for (const auto& v : _viewList) {
		v->draw();
	}
}


void LinearLayout::handleEvent(const Event& event) {
	for (auto view: _viewList) {
		if (view->getBounds().contains(event._targetX, event._targetY)) {
			view->handleEvent(event);
		}
	}
}
