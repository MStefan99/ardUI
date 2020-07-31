//
// Created by MStefan99 on 16.12.19.
//

#include "view.h"


uint16_t view::measureSpec::makeMeasureSpec(uint16_t mode, uint16_t size) {
	return mode | size;
}


uint16_t view::measureSpec::getMode(uint16_t measureSpec) {
	return measureSpec & 0xC000u;
}


uint16_t view::measureSpec::getSize(uint16_t measureSpec) {
	return measureSpec & 0x3FFFu;
}


int view::lastViewId {0};


view::view(): viewId(++lastViewId) {}


view* view::findViewById(int id) {
	if (id == viewId) {
		return this;
	} else {
		return nullptr;
	}
}


int view::getId() {
	return viewId;
}


void view::draw() {
	if (!valid && visible) {
		onDraw();
		valid = true;
	}
}


void view::measure(uint16_t width, uint16_t height) {
	onMeasure(width, height);
}


void view::layout(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
	auto b = getBounds();
	bool changed = left == b.left && top == b.top && bottom == b.bottom && right == b.right;
	if (changed) {
		invalidate();
	}
	onLayout(changed, left, top, right, bottom);
}


void view::layout(const rect &r) {
	layout(r.left, r.top, r.right, r.bottom);
}


void view::onDraw() {}


void view::invalidate() {
	invalidateSelf();
}


void view::setLeft(uint16_t left) {
	viewBox.left = left;
}


void view::setTop(uint16_t top) {
	viewBox.top = top;
}


void view::setRight(uint16_t right) {
	viewBox.right = right;
}


void view::setBottom(uint16_t bottom) {
	viewBox.bottom = bottom;
}


uint16_t view::getMeasuredHeight() {
	return measuredHeight;
}


uint16_t view::getMeasuredWidth() {
	return measuredWidth;
}


uint16_t view::getHeight() {
	return viewBox.height();
}


uint16_t view::getWidth() {
	return viewBox.width();
}


void view::setMeasuredDimensions(uint16_t w, uint16_t h) {
	measuredWidth = w;
	measuredHeight = h;
}


void view::setOnClickListener(void (*l)(view&)) {
	onClick = l;
}


void view::setOnLongClickListener(void (*l)(view&)) {
	onLongClick = l;
}


void view::onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) {
	setMeasuredDimensions(getDefaultSize(getMinimumWidth(), widthMeasureSpec),
						  getDefaultSize(getMinimumHeight(), heightMeasureSpec));
}


void view::onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
}


void view::setClicked(bool b) {
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


bool view::isClicked() {
	return inClickedState;
}


bool view::isLongClicked() {
	return inLongClickedState;
}


uint16_t view::getDefaultSize(uint16_t size, uint16_t measureSpec) {
	uint16_t result {0};

	if (visible) {
		uint16_t specMode = view::measureSpec::getMode(measureSpec);

		switch (specMode) {
			case view::measureSpec::UNSPECIFIED:
			default:
				result = size;
				break;
			case view::measureSpec::AT_MOST:
			case view::measureSpec::EXACTLY:
				result = view::measureSpec::getSize(measureSpec);
				break;
		}
	}
	return result;
}

