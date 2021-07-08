//
// Created by MStefan99 on 16.12.19.
//

#include "TextView.h"


TextView::TextView(const String& text):
		_text {text} {
	// Nothing to do
}


void TextView::setText(const String& textToSet) {
	_text = textToSet;
	invalidate();
}


void TextView::append(const String& textToAppend) {
	_text += textToAppend;
	invalidate();
}


void TextView::setTextSize(uint16_t size) {
	_textSize = size;
	invalidate();
}


void TextView::setTextColor(uint32_t color) {
	_textColor = color;
	invalidate();
}


String TextView::getText() const {
	return _text;
}


uint16_t TextView::getTextSize() const {
	return _textSize;
}


uint32_t TextView::getTextColor() const {
	return _textColor;
}


void TextView::onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) {
	auto width = getDefaultSize(getMaxWidth(), widthMeasureSpec);
	setMeasuredDimensions(width + _padding.left + _padding.right,
			getDefaultSize(_textSize * (uint16_t)getLines(width).size() +
			               _padding.top + _padding.bottom, heightMeasureSpec));
}


void TextView::onDraw() {
	ardui::display::FillRect(_viewBox.left, _viewBox.top, _viewBox.right - 1, _viewBox.bottom - 1, _backgroundColor);

	uint16_t line {0};
	for (const auto& l : getLines(_viewBox.width())) {
		ardui::display::DrawText(_viewBox.left + _padding.left, _viewBox.top + _padding.top + _textSize * line++,
				l, _textSize, _textColor);
	}
}


LIST<String> TextView::getLines(uint16_t maxWidth) const {
	LIST<String> lines {};
	auto s {_text.c_str()};
	uint16_t lineStart {0};
	uint16_t lastSpace {0};
	uint16_t currentWidth {0};

	for (uint16_t i {0}; s[i]; ++i) {
		currentWidth += ardui::display::GetCharWidth(s[i], _textSize);
		if (s[i] == ' ') {
			lastSpace = i + 1;
		}
		if (currentWidth > maxWidth) {
			if (lineStart == lastSpace) {
				lastSpace = i;
			}
			#ifdef Arduino_h
			lines.push_back(_text.substring(lineStart, lastSpace));
			#else
			lines.push_back(_text.substr(lineStart, lastSpace - lineStart));
			#endif
			i = lineStart = lastSpace;
			currentWidth = 0;
		}
	}

	if (lineStart != _text.length()) {
		#ifdef Arduino_h
		lines.push_back(_text.substring(lineStart, text.length()));
		#else
		lines.push_back(_text.substr(lineStart, _text.length() - lineStart));
		#endif
	}
	return lines;
}


uint16_t TextView::getMaxWidth() {
	uint16_t width {};
	auto s {_text.c_str()};

	for (uint16_t i {0}; s[i]; ++i) {
		width += ardui::display::GetCharWidth(s[i], _textSize);
	}

	return width;
}
