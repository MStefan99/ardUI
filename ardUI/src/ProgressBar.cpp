//
// Created by MStefan99 on 14.4.21.
//

#include "ProgressBar.h"


int16_t ProgressBar::getProgress() const {
	return mapScale(_level, 0, 10000, _min, _max);
}


void ProgressBar::setProgress(int16_t progress) {
	_level = mapScale(progress, _min, _max, 0, 10000);
	invalidate();
}


int16_t ProgressBar::getMin() const {
	return _min;
}


void ProgressBar::setMin(int16_t min) {
	_min = min;
}


int16_t ProgressBar::getMax() const {
	return _max;
}


void ProgressBar::setMax(int16_t max) {
	_max = max;
}


Color ProgressBar::getBarColor() const {
	return _barColor;
}


void ProgressBar::setBarColor(Color barColor) {
	_barColor = barColor;
}


Color ProgressBar::getBackgroundColor() const {
	return _backgroundColor;
}


void ProgressBar::setBackgroundColor(Color backgroundColor) {
	_backgroundColor = backgroundColor;
}


int16_t ProgressBar::mapScale(int16_t value, int16_t oldMin, int16_t oldMax,
		int16_t newMin, int16_t newMax) {
	// TODO: fix overflow
	return (newMax - newMin) * (value - oldMin) / (oldMax - oldMin) + newMin;
}


void ProgressBar::onDraw() {
	DISPLAY_UTIL::fillRect(_viewBox.left, _viewBox.top, _viewBox.right - 1, _viewBox.bottom - 1, _backgroundColor);
	DISPLAY_UTIL::drawRect(_viewBox.left, _viewBox.top, _viewBox.right - 1, _viewBox.bottom - 1, _barColor);

	DISPLAY_UTIL::fillRect(_viewBox.left, _viewBox.top,
			_viewBox.left + mapScale(_level, 0, 10000, _viewBox.left, _viewBox.right), _viewBox.bottom, _barColor);
}
