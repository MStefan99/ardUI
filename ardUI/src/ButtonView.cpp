//
// Created by MStefan99 on 19.12.19.
//

#include "ButtonView.h"


ButtonView::ButtonView(const String& text):
		TextView {text} {
	// Nothing to do
}


Color ButtonView::getBorderColor() const {
	return _borderColor;
}


void ButtonView::setBorderColor(Color borderColor) {
	_borderColor = borderColor;
}


void ButtonView::onDraw() {
	DISPLAY_UTIL::fillRect(_viewBox.left, _viewBox.top, _viewBox.right - 1, _viewBox.bottom - 1, _backgroundColor);
	DISPLAY_UTIL::drawRect(_viewBox.left, _viewBox.top, _viewBox.right - 1, _viewBox.bottom - 1, _borderColor);

	uint16_t line {0};
	for (const auto& l : getLines(_viewBox.width())) {
		DISPLAY_UTIL::drawText(_viewBox.left + _padding.left,
				static_cast<int16_t>(_viewBox.top + _padding.top + _textSize * line++),
				l, _textSize, _textColor);
	}
}
