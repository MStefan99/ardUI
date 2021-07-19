//
// Created by MStefan99 on 16.12.19.
//

#include "View.h"


View::MeasureSpec::MeasureSpec(uint16_t size, Sizing mode): _size {size}, _mode {mode} {
	// Nothing to do
}


uint16_t View::MeasureSpec::getSize() const {
	return _size;
}


View::MeasureSpec::Sizing View::MeasureSpec::getMode() const {
	return _mode;
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


void View::measure(MeasureSpec widthMeasureSpec, MeasureSpec heightMeasureSpec) {
	if (!_valid) {
		onMeasure(widthMeasureSpec, heightMeasureSpec);
	}
}


void View::layout(const Rect& r) {
	layout(r.left, r.top, r.right, r.bottom);
}


void View::layout(int16_t left, int16_t top, int16_t right, int16_t bottom) {
	if (!_valid) {
		auto b = getBounds();
		bool changed = left != b.left || top != b.top || bottom != b.bottom || right != b.right;
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


View* View::handleEvent(const Event& event) {
	// TODO: check if visible
	switch (event._currentAction) {
		case Event::Action::NO_ACTION:
		case Event::Action::TOUCH:
			// Nothing to do
			return nullptr;
		case Event::Action::CLICK:
			if (_onClick) {
				_onClick(this);
			}
			return this;
		case Event::Action::LONG_CLICK:
			if (_onLongClick) {
				_onLongClick(this);
			}
			return this;
		case Event::Action::SCROLL:
			if (_onScroll) {
				_onScroll(this);
			}
			return this;
	}
}


void View::invalidate() {
	invalidateSelf();
}


void View::setLeft(int16_t left) {
	_viewBox.left = left;
}


void View::setTop(int16_t top) {
	_viewBox.top = top;
}


void View::setRight(int16_t right) {
	_viewBox.right = right;
}


void View::setBottom(int16_t bottom) {
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


void View::setOnScrollListener(void (* l)(View*)) {
	_onScroll = l;
}


void View::onMeasure(MeasureSpec widthMeasureSpec, MeasureSpec heightMeasureSpec) {
	setMeasuredDimensions(getDefaultSize(getMinimumWidth() + _padding.width(), widthMeasureSpec),
			getDefaultSize(getMinimumHeight() + _padding.height(), heightMeasureSpec));
}


void View::onLayout(bool changed, int16_t left, int16_t top, int16_t right, int16_t bottom) {
	// Nothing to do
}


void View::onDraw() {
	// Nothing to do
}


uint16_t View::getDefaultSize(uint16_t size, MeasureSpec measureSpec) {
	switch (measureSpec.getMode()) {
		case View::MeasureSpec::Sizing::UNSPECIFIED:
			return size;
		case View::MeasureSpec::Sizing::AT_MOST:
			return MIN(size, measureSpec.getSize());
		case View::MeasureSpec::Sizing::EXACTLY:
			return measureSpec.getSize();
	}
}
