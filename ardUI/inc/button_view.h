//
// Created by MStefan99 on 19.12.19.
//

#ifndef ARDUI_BUTTON_VIEW_H
#define ARDUI_BUTTON_VIEW_H


#include "platform.h"
#include "text_view.h"
#include "llpi.h"


class ButtonView: public TextView {
public:
	ButtonView() = default;
	explicit ButtonView(const String& text);
	~ButtonView() override = default;

protected:
	// TODO: add onMeasure
	void onDraw() override;

private:
	uint32_t backgroundColor {0xFFFFFFFF};
	uint32_t borderColor {0};
};

#endif //ARDUI_BUTTON_VIEW_H
