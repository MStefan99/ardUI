//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_TEXTVIEW_H
#define ARDUI_TEXTVIEW_H


#include "platform.h"
#include "View.h"


class TextView: public View {
public:
	TextView() = default;
	explicit TextView(const String& text);
	~TextView() override = default;

	void setText(const String& textToSet);
	void append(const String& textToAppend);
	void setTextSize(uint16_t textSize);
	void setTextColor(uint32_t textColor);

	String getText() const;
	uint16_t getTextSize() const;
	uint32_t getTextColor() const;

protected:
	// TODO: add onMeasure
	void onDraw() override;

	String text;
	uint16_t textSize {20};
	uint32_t textColor {0x0};
	uint32_t backgroundColor {0xffffff};
};

#endif //ARDUI_TEXTVIEW_H
