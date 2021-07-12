//
// Created by MStefan99 on 19.12.19.
//

#include "ButtonView.h"


ButtonView::ButtonView(const String& text):
		TextView {text} {
	// Nothing to do
}


void ButtonView::onDraw() {
	DISPLAY::fillRect(_viewBox.left, _viewBox.top, _viewBox.right - 1, _viewBox.bottom - 1, _backgroundColor);
	DISPLAY::drawRect(_viewBox.left, _viewBox.top, _viewBox.right - 1, _viewBox.bottom - 1, _borderColor);

	uint16_t line {0};
	for (const auto& l : getLines(_viewBox.width())) {
		DISPLAY::drawText(_viewBox.left + _padding.left,
				static_cast<int16_t>(_viewBox.top + _padding.top + _textSize * line++),
				l, _textSize, _textColor);
	}
}
