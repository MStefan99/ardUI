//
// Created by MStefan99 on 16.12.19.
//

#include "TextView.h"


TextView::TextView(const String& text):
	text {text} {
	// Nothing to do
}


void TextView::setText(const String& textToSet) {
	text = textToSet;
	invalidate();
}


void TextView::append(const String& textToAppend) {
	text += textToAppend;
	invalidate();
}


void TextView::setTextSize(uint16_t size) {
	textSize = size;
	invalidate();
}


void TextView::setTextColor(uint32_t color) {
	textColor = color;
	invalidate();
}


String TextView::getText() const {
	return text;
}


uint16_t TextView::getTextSize() const {
	return textSize;
}


uint32_t TextView::getTextColor() const {
	return textColor;
}


void TextView::onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) {
	//TODO: add line breaks
	setMeasuredDimensions(getDefaultSize(minWidth, widthMeasureSpec),
											 getDefaultSize(textSize, heightMeasureSpec));
}


void TextView::onDraw() {
	arduiDisplayFillRect(viewBox.left, viewBox.top, viewBox.right - 1, viewBox.bottom - 1, backgroundColor);
	arduiDisplayDrawText(viewBox.left, viewBox.top, text, textSize, textColor);
}
