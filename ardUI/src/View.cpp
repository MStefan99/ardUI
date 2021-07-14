//
// Created by MStefan99 on 16.12.19.
//

#include "View.h"


uint16_t View::MeasureSpec::makeMeasureSpec(uint16_t mode, uint16_t size) {
	return mode | size;
}


uint16_t View::MeasureSpec::getMode(uint16_t measureSpec) {
	return measureSpec & 0xC000u;
}


uint16_t View::MeasureSpec::getSize(uint16_t measureSpec) {
	return measureSpec & 0x3FFFu;
}


int View::_lastViewId {0};


View::View(): _viewId {++_lastViewId} {
	// Nothing to do
}


View* View::findViewById(int id) {
	if (id == _viewId) {
		return this;
	} else {
		return nullptr;
	}
}


int View::getId() const {
	return _viewId;
}


void View::measure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) {
	if (!_valid) {
		onMeasure(widthMeasureSpec, heightMeasureSpec);
	}
}


void View::layout(const Rect& r) {
	layout(r.left, r.top, r.right, r.bottom);
}


void View::layout(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
	if (!_valid) {
		auto b = getBounds();
		bool changed = left == b.left && top == b.top && bottom == b.bottom && right == b.right;
		if (changed) {
			invalidate();
		}
		_viewBox.set(left, top, right, bottom);
		onLayout(changed, left, top, right, bottom);
	}
}


void View::draw() {
	if (!_valid && _visible) {
		onDraw();
		_valid = true;
	}
}


void View::handleEvent(const Event& event) {
	// TODO: check if visible
	switch (event._currentAction) {
		case Event::Action::NO_ACTION:
		case Event::Action::TOUCH:
			// Nothing to do
			break;
		case Event::Action::CLICK:
			if (_onClick) {
				_onClick(this);
			}
			break;
		case Event::Action::LONG_CLICK:
			if (_onLongClick) {
				_onLongClick(this);
			}
			break;
		case Event::Action::SCROLL:
			if (_onScroll) {
				_onScroll(this);
			}
			break;
	}
}


void View::invalidate() {
	invalidateSelf();
}


void View::setLeft(uint16_t left) {
	_viewBox.left = left;
}


void View::setTop(uint16_t top) {
	_viewBox.top = top;
}


void View::setRight(uint16_t right) {
	_viewBox.right = right;
}


void View::setBottom(uint16_t bottom) {
	_viewBox.bottom = bottom;
}


uint16_t View::getMeasuredHeight() const {
	return _measuredHeight;
}


uint16_t View::getMeasuredWidth() const {
	return _measuredWidth;
}


uint16_t View::getHeight() {
	return _viewBox.height();
}


uint16_t View::getWidth() {
	return _viewBox.width();
}


void View::setMeasuredDimensions(uint16_t w, uint16_t h) {
	_measuredWidth = w;
	_measuredHeight = h;
}


void View::setOnClickListener(void (* l)(View*)) {
	_onClick = l;
}


void View::setOnLongClickListener(void (* l)(View*)) {
	_onLongClick = l;
}


void View::onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) {
	setMeasuredDimensions(getDefaultSize(getMinimumWidth() + _padding.width(), widthMeasureSpec),
			getDefaultSize(getMinimumHeight() + _padding.height(), heightMeasureSpec));
}


void View::onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
	// Nothing to do
}


void View::onDraw() {
	// Nothing to do
}


uint16_t View::getDefaultSize(uint16_t size, uint16_t measureSpec) {
	switch (View::MeasureSpec::getMode(measureSpec)) {
		case View::MeasureSpec::Sizing::UNSPECIFIED:
		default:
			return size;
		case View::MeasureSpec::Sizing::AT_MOST:
			return MIN(size, View::MeasureSpec::getSize(measureSpec));
		case View::MeasureSpec::Sizing::EXACTLY:
			return View::MeasureSpec::getSize(measureSpec);
	}
}
