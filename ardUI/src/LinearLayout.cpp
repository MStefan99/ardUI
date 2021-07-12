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


void LinearLayout::onMeasure(MeasureSpec widthMeasureSpec, MeasureSpec heightMeasureSpec) {
	uint16_t size = 0;

	if (_orientation == Orientation::HORIZONTAL) {
		for (const auto& v : _viewList) {
			v->measure(MeasureSpec {widthMeasureSpec.getSize()},
					MeasureSpec {heightMeasureSpec.getSize(), MeasureSpec::AT_MOST});
			size += v->getMeasuredWidth();
		}
		setMeasuredDimensions(getDefaultSize(size + _padding.width(), widthMeasureSpec),
				getDefaultSize(getMinimumHeight() + _padding.height(), heightMeasureSpec));
	} else {
		for (const auto& v : _viewList) {
			v->measure(MeasureSpec {widthMeasureSpec.getSize(), MeasureSpec::AT_MOST},
					MeasureSpec {heightMeasureSpec.getSize()});
			size += v->getMeasuredHeight();
		}
		setMeasuredDimensions(getDefaultSize(getMinimumWidth() + _padding.width(), widthMeasureSpec),
				getDefaultSize(size + _padding.height(), heightMeasureSpec));
	}
}


void LinearLayout::onLayout(bool changed, int16_t l, int16_t t, int16_t r, int16_t b) {
	int16_t nextViewLeft {l};
	int16_t nextViewTop {t};

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
