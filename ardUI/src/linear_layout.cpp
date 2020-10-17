//
// Created by MStefan99 on 23.12.19.
//

#include "linear_layout.h"


LinearLayout::LinearLayout(bool vertical):
		isVertical(vertical) {}


void LinearLayout::onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) {
	for (const auto& v : viewList) {
		v->measure(View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::AT_MOST,
													  View::MeasureSpec::getSize(widthMeasureSpec)),
				   View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::UNSPECIFIED,
													  View::MeasureSpec::getSize(heightMeasureSpec)));
	}
}


void LinearLayout::onLayout(bool changed, uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
	int viewLeft {0};
	int viewTop {0};
	int layoutRight {arduiDisplayGetWidth()};
	int layoutBottom {arduiDisplayGetHeight()};

	for (const auto& v : viewList) {
		v->setTop(viewTop);
		v->setLeft(viewLeft);

		if (isVertical) {
			viewTop += v->getMeasuredHeight();
			v->setBottom(viewTop);
			v->setRight(layoutRight);
		} else {
			viewLeft += v->getMeasuredWidth();
			v->setRight(viewLeft);
			v->setBottom(layoutBottom);
		}
	}
}


void LinearLayout::onDraw() {
	for (const auto& v : viewList) {
		v->draw();
	}
}


void LinearLayout::handleEvent(const Event& event) {
	for (auto view: viewList) {
		if (view->getBounds().contains(event.targetX, event.targetY)) {
			view->handleEvent(event);
		}
	}
}
