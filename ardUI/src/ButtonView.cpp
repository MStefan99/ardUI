//
// Created by MStefan99 on 19.12.19.
//

#include "ButtonView.h"


ButtonView::ButtonView(const String& text):
		TextView {text} {
	// Nothing to do
}


void ButtonView::onDraw() {
	arduiDisplayFillRect(_viewBox._left, _viewBox._top, _viewBox._right - 1, _viewBox._bottom - 1, _backgroundColor);
	arduiDisplayDrawRect(_viewBox._left, _viewBox._top, _viewBox._right - 1, _viewBox._bottom - 1, _borderColor);

	uint16_t line {0};
	for (const auto& l : getLines(_viewBox.width())) {
		arduiDisplayDrawText(_viewBox._left + _padding._top, _viewBox._top + _padding._bottom + _textSize * line++,
				l, _textSize, _textColor);
	}
}
