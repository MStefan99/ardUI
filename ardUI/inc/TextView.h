//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_TEXTVIEW_H
#define ARDUI_TEXTVIEW_H

#include "platform.h"
#include "View.h"
#include LIST_H


class TextView: public View {
public:
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

	friend class EmscriptenBindingInitializer_BuilderInterface;

protected:
	void onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) override;
	void onDraw() override;

	LIST<String> getLines(uint16_t maxWidth) const;
	uint16_t getMaxWidth();

	String _text;
	uint16_t _textSize {20};
	Color _textColor {0x0};
	Color _backgroundColor {0xffffff};
};

#endif //ARDUI_TEXTVIEW_H
