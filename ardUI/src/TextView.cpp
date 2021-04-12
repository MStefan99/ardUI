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
	auto width = getDefaultSize(minWidth, widthMeasureSpec);
	setMeasuredDimensions(width, getDefaultSize(textSize, heightMeasureSpec)
															 * (uint16_t)getLines(width).size());
}


void TextView::onDraw() {
	arduiDisplayFillRect(viewBox.left, viewBox.top, viewBox.right - 1, viewBox.bottom - 1, backgroundColor);

	uint16_t line {0};
	for (const auto& l : getLines(viewBox.width())) {
		arduiDisplayDrawText(viewBox.left, viewBox.top + textSize * line++, l, textSize, textColor);
	}
}


LIST<String> TextView::getLines(uint16_t maxWidth) const {
	LIST<String> lines {};
	auto s {text.c_str()};
	uint16_t lineStart {0};
	uint16_t lastSpace {0};
	uint16_t currentWidth {0};

	for (uint16_t i {0}; s[i]; ++i) {
		currentWidth += arduiDisplayGetCharWidth(s[i], textSize);
		if (s[i] == ' ') {
			lastSpace = i + 1;
		}
		if (currentWidth > maxWidth) {
			if (lineStart == lastSpace) {
				lastSpace = i;
			}
			#ifdef Arduino_h
			lines.push_back(text.substring(lineStart, lastSpace));
			#else
			lines.push_back(text.substr(lineStart, lastSpace - lineStart));
			#endif
			i = lineStart = lastSpace;
			currentWidth = 0;
		}
	}

	if (lineStart != text.length()) {
		#ifdef Arduino_h
		lines.push_back(text.substring(lineStart, text.length()));
		#else
		lines.push_back(text.substr(lineStart, text.length() - lineStart));
		#endif
	}
	return lines;
}
