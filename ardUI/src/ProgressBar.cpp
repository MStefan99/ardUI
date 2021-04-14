//
// Created by MStefan99 on 14.4.21.
//

#include "ProgressBar.h"


uint16_t ProgressBar::getProgress() const {
	return mapScale(_level, 0, 10000, _min, _max);
}


void ProgressBar::setProgress(uint16_t progress) {
	_level = mapScale(progress, _min, _max, 0, 10000);
	onLevelChange(_level);
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


uint16_t ProgressBar::mapScale(uint16_t value, uint16_t oldMin, uint16_t oldMax,
		uint16_t newMin, uint16_t newMax) {
	return (newMax - newMin) * (value - oldMin) / (oldMax - oldMin) + newMin;
}


void ProgressBar::onDraw() {
	arduiDisplayFillRect(_viewBox._left, _viewBox._top, _viewBox._right - 1, _viewBox._bottom - 1, _backgroundColor);
	arduiDisplayDrawRect(_viewBox._left, _viewBox._top, _viewBox._right - 1, _viewBox._bottom - 1, _barColor);

	arduiDisplayFillRect(_viewBox._left, _viewBox._top,
			_viewBox._left + mapScale(_level, 0, 10000, _viewBox._left, _viewBox._right), _viewBox._bottom, _barColor);
}
