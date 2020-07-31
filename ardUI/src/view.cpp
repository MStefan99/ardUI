//
// Created by MStefan99 on 16.12.19.
//

#include "view.h"


uint16_t View::MeasureSpec::makeMeasureSpec(uint16_t mode, uint16_t size) {
	return mode | size;
}


uint16_t View::MeasureSpec::getMode(uint16_t measureSpec) {
	return measureSpec & 0xC000u;
}


uint16_t View::MeasureSpec::getSize(uint16_t measureSpec) {
	return measureSpec & 0x3FFFu;
}


int View::lastViewId {0};


View::View(): viewId(++lastViewId) {}


View* View::findViewById(int id) {
	if (id == viewId) {
		return this;
	} else {
		return nullptr;
	}
}


int View::getId() {
	return viewId;
}


void View::draw() {
	if (!valid && visible) {
		onDraw();
		valid = true;
	}
}


void View::measure(uint16_t width, uint16_t height) {
	onMeasure(width, height);
}


void View::layout(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
	auto b = getBounds();
	bool changed = left == b.left && top == b.top && bottom == b.bottom && right == b.right;
	if (changed) {
		invalidate();
	}
	onLayout(changed, left, top, right, bottom);
}


void View::layout(const Rect &r) {
	layout(r.left, r.top, r.right, r.bottom);
}


void View::onDraw() {}


void View::invalidate() {
	invalidateSelf();
}


void View::setLeft(uint16_t left) {
	viewBox.left = left;
}


void View::setTop(uint16_t top) {
	viewBox.top = top;
}


void View::setRight(uint16_t right) {
	viewBox.right = right;
}


void View::setBottom(uint16_t bottom) {
	viewBox.bottom = bottom;
}


uint16_t View::getMeasuredHeight() {
	return measuredHeight;
}


uint16_t View::getMeasuredWidth() {
	return measuredWidth;
}


uint16_t View::getHeight() {
	return viewBox.height();
}


uint16_t View::getWidth() {
	return viewBox.width();
}


void View::setMeasuredDimensions(uint16_t w, uint16_t h) {
	measuredWidth = w;
	measuredHeight = h;
}


void View::setOnClickListener(void (*l)(View&)) {
	onClick = l;
}


void View::setOnLongClickListener(void (*l)(View&)) {
	onLongClick = l;
}


void View::onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) {
	setMeasuredDimensions(getDefaultSize(getMinimumWidth(), widthMeasureSpec),
						  getDefaultSize(getMinimumHeight(), heightMeasureSpec));
}


void View::onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
}


void View::setClicked(bool b) {
	invalidate();
	if (b) {
		inClickedState = true;
		++timesClicked;
	} else {
		inClickedState = false;
		inLongClickedState = false;
		timesClicked = 0;
	}

	if (timesClicked > LONG_CLICK_TIME / UPDATE_FREQUENCY) {
		inLongClickedState = true;
	}
}


bool View::isClicked() {
	return inClickedState;
}


bool View::isLongClicked() {
	return inLongClickedState;
}


uint16_t View::getDefaultSize(uint16_t size, uint16_t measureSpec) {
	uint16_t result {0};

	if (visible) {
		uint16_t specMode = View::MeasureSpec::getMode(measureSpec);

		switch (specMode) {
			case View::MeasureSpec::UNSPECIFIED:
			default:
				result = size;
				break;
			case View::MeasureSpec::AT_MOST:
			case View::MeasureSpec::EXACTLY:
				result = View::MeasureSpec::getSize(measureSpec);
				break;
		}
	}
	return result;
}

