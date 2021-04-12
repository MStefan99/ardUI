//
// Created by MStefan99 on 19.12.19.
//

#include "ButtonView.h"


ButtonView::ButtonView(const String& text):
	TextView {text} {
	// Nothing to do
}


void ButtonView::onDraw() {
	arduiDisplayFillRect(viewBox.left, viewBox.top, viewBox.right - 1, viewBox.bottom - 1, backgroundColor);

	arduiDisplayDrawRect(viewBox.left, viewBox.top, viewBox.right - 1, viewBox.bottom - 1, borderColor);

	uint16_t line {0};
	for (const auto& l : getLines(viewBox.width())) {
		arduiDisplayDrawText(viewBox.left, viewBox.top + textSize * line++, l, textSize, textColor);
	}
}
