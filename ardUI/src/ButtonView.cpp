//
// Created by MStefan99 on 19.12.19.
//

#include "ButtonView.h"


ButtonView::ButtonView(const String& text):
	TextView {text} {
	// Nothing to do
}


void ButtonView::onDraw() {
	auto b {getBounds()};

	arduiDisplayDrawLine(b.left, b.top, b.right - 1, b.top, borderColor);  // top
	arduiDisplayDrawLine(b.left, b.top, b.left, b.bottom - 1, borderColor);  // left
	arduiDisplayDrawLine(b.right - 1, b.top, b.right - 1, b.bottom - 1, borderColor);  // right
	arduiDisplayDrawLine(b.left, b.bottom - 1, b.right - 1, b.bottom - 1, borderColor);  // bottom
	arduiDisplayDrawText(b.left, b.top, getTextSize(), getText(), getTextColor());
}
