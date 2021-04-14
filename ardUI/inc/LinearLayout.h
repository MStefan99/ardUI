//
// Created by MStefan99 on 23.12.19.
//

#ifndef ARDUI_LINEARLAYOUT_H
#define ARDUI_LINEARLAYOUT_H

#include "Event.h"
#include "ViewGroup.h"


class LinearLayout: public ViewGroup {
public:
	explicit LinearLayout(bool vertical = true);

protected:
	void onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) override;
	void onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) override;
	void onDraw() override;

	void handleEvent(const Event& event) override;

	bool _isVertical {true};
};

#endif //ARDUI_LINEARLAYOUT_H
