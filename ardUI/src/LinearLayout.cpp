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
	uint16_t size = 0;

	if (_orientation == Orientation::HORIZONTAL) {
		for (const auto& v : _viewList) {
			v->measure(View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::UNSPECIFIED,
					View::MeasureSpec::getSize(widthMeasureSpec)),
					View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::AT_MOST,
							View::MeasureSpec::getSize(heightMeasureSpec)));
			size += v->getMeasuredWidth();
		}
		setMeasuredDimensions(getDefaultSize(size + _padding.width(), widthMeasureSpec),
				getDefaultSize(getMinimumHeight() + _padding.height(), heightMeasureSpec));
	} else {
		for (const auto& v : _viewList) {
			v->measure(View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::AT_MOST,
					View::MeasureSpec::getSize(widthMeasureSpec)),
					View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::UNSPECIFIED,
							View::MeasureSpec::getSize(heightMeasureSpec)));
			size += v->getMeasuredHeight();
		}
		setMeasuredDimensions(getDefaultSize(getMinimumWidth() + _padding.width(), widthMeasureSpec),
				getDefaultSize(size + _padding.height(), heightMeasureSpec));
	}
}


void LinearLayout::onLayout(bool changed, uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
	uint16_t nextViewLeft {l};
	uint16_t nextViewTop {t};

	for (const auto& v : _viewList) {
		v->setTop(nextViewTop);
		v->setLeft(nextViewLeft);

		if (_orientation == Orientation::HORIZONTAL) {
			v->layout(nextViewLeft, nextViewTop, nextViewLeft + v->getMeasuredWidth(), b);
			nextViewLeft += v->getMeasuredWidth();
		} else {
			v->layout(nextViewLeft, nextViewTop, r, nextViewTop + v->getMeasuredHeight());
			nextViewTop += v->getMeasuredHeight();
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
