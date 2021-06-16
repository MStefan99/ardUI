//
// Created by MStefan99 on 19.12.19.
//

#ifndef ARDUI_BUTTONVIEW_H
#define ARDUI_BUTTONVIEW_H

#include "platform.h"
#include "llpi.h"
#include "TextView.h"


class ButtonView: public TextView {
public:
	ButtonView() = default;
	explicit ButtonView(const String& text);
	~ButtonView() override = default;

protected:
	void onDraw() override;

	uint32_t _borderColor {0x0};
};

#endif //ARDUI_BUTTONVIEW_H
