//
// Created by MStefan99 on 19.12.19.
//

#ifndef ARDUI_BUTTONVIEW_H
#define ARDUI_BUTTONVIEW_H

#include "config/defaults.h"
#include "platform.h"

#include "TextView.h"


class ButtonView: public TextView {
public:
	ButtonView() = default;
	explicit ButtonView(const String& text);
	~ButtonView() override = default;

	Color getBorderColor() const;
	void setBorderColor(Color borderColor);

	#ifdef __EMSCRIPTEN__
	friend class EmscriptenBindingInitializer_BuilderInterface;
	#endif

protected:
	void onDraw() override;

	Color _borderColor {DEFAULT_BORDER_COLOR};
};

#endif //ARDUI_BUTTONVIEW_H
