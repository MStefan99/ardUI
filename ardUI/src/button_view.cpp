//
// Created by MStefan99 on 19.12.19.
//

#include "button_view.h"


ButtonView::ButtonView(const String& text):
		TextView(text) {}


void ButtonView::onDraw() {
	auto b {getBounds()};

	arduiDisplayDrawLine(b.left, b.top, b.right, b.top, borderColor);  // top
	arduiDisplayDrawLine(b.left, b.top, b.left, b.bottom, borderColor);  // left
	arduiDisplayDrawLine(b.right, b.top, b.right, b.bottom, borderColor);  // right
	arduiDisplayDrawLine(b.left, b.bottom, b.right, b.bottom, borderColor);  // bottom
	arduiDisplayDrawText(b.left, b.top, getTextSize(), getText(), getTextColor());
}
