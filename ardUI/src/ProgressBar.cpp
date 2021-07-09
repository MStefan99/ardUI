//
// Created by MStefan99 on 14.4.21.
//

#include "ProgressBar.h"


uint16_t ProgressBar::getProgress() const {
	return mapScale(_level, 0, 10000, _min, _max);
}


void ProgressBar::setProgress(uint16_t progress) {
	_level = mapScale(progress, _min, _max, 0, 10000);
	invalidate();
}


uint16_t ProgressBar::getMin() const {
	return _min;
}


void ProgressBar::setMin(uint16_t min) {
	_min = min;
}


uint16_t ProgressBar::getMax() const {
	return _max;
}


void ProgressBar::setMax(uint16_t max) {
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


uint16_t ProgressBar::mapScale(uint16_t value, uint16_t oldMin, uint16_t oldMax,
		uint16_t newMin, uint16_t newMax) {
	// TODO: fix overflow
	return (newMax - newMin) * (value - oldMin) / (oldMax - oldMin) + newMin;
}


void ProgressBar::onDraw() {
	ardui::display::FillRect(_viewBox.left, _viewBox.top, _viewBox.right - 1, _viewBox.bottom - 1, _backgroundColor);
	ardui::display::DrawRect(_viewBox.left, _viewBox.top, _viewBox.right - 1, _viewBox.bottom - 1, _barColor);

	ardui::display::FillRect(_viewBox.left, _viewBox.top,
			_viewBox.left + mapScale(_level, 0, 10000, _viewBox.left, _viewBox.right), _viewBox.bottom, _barColor);
}
