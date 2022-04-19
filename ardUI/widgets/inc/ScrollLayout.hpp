//
// Created by MStefan99 on 11.7.21.
//

#ifndef ARDUI_SCROLLLAYOUT_H
#define ARDUI_SCROLLLAYOUT_H

#include "platform.hpp"

#include "Event.hpp"
#include "LinearLayout.hpp"


class ScrollLayout: public LinearLayout {
protected:
	void onLayout(bool changed, int16_t left, int16_t top, int16_t right, int16_t bottom) override;

	void draw() override;
	View* handleEvent(const Event& event) override;

	int16_t _offset {0};
};

#endif //ARDUI_SCROLLLAYOUT_H
