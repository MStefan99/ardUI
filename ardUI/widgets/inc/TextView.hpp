//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_TEXTVIEW_H
#define ARDUI_TEXTVIEW_H

#include "defaults.hpp"
#include "platform.hpp"
#include LIST_H

#include "View.hpp"


class TextView: S_PUBLIC View {
S_PUBLIC:
	TextView() = default;
	explicit TextView(const String& text);
	~TextView() override = default;

	void setText(const String& textToSet);
	void append(const String& textToAppend);
	void setTextSize(uint16_t textSize);
	void setTextColor(Color textColor);

	String getText() const;
	uint16_t getTextSize() const;
	Color getTextColor() const;

	// TODO: add alignment options
	// TODO: add background toggle

	#ifdef TEST

	friend class TestWrapper;

	#endif

S_PROTECTED:
	void onMeasure(MeasureSpec widthMeasureSpec, MeasureSpec heightMeasureSpec) override;
	void onDraw() override;

	TL_NS::list<String> getLines(uint16_t maxWidth) const;
	uint16_t getMaxWidth();

	String _text;
	uint16_t _textSize {DEFAULT_TEXT_SIZE};
	Color _textColor {DEFAULT_COLOR};
	Color _backgroundColor {DEFAULT_BACKGROUND_COLOR};
};

#endif //ARDUI_TEXTVIEW_H
