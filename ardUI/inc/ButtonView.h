//
// Created by MStefan99 on 19.12.19.
//

#ifndef ARDUI_BUTTONVIEW_H
#define ARDUI_BUTTONVIEW_H

#include "platform.h"
#include "display.h"
#include "TextView.h"


class ButtonView: public TextView {
public:
	ButtonView() = default;
	explicit ButtonView(const String& text);
	~ButtonView() override = default;

	friend class EmscriptenBindingInitializer_BuilderInterface;

protected:
	void onDraw() override;

	Color _borderColor {0x0};
};

#endif //ARDUI_BUTTONVIEW_H
