//
// Created by MStefan99 on 23.12.19.
//

#ifndef ARDUI_LINEARLAYOUT_H
#define ARDUI_LINEARLAYOUT_H

#include "Event.hpp"
#include "ViewGroup.hpp"


class LinearLayout: S_PUBLIC ViewGroup {
S_PUBLIC:
	enum Orientation {
		HORIZONTAL,
		VERTICAL
	};

	LinearLayout() = default;

	Orientation getOrientation() const;
	void setOrientation(Orientation orientation);

S_PROTECTED:
	void onMeasure(MeasureSpec widthMeasureSpec, MeasureSpec heightMeasureSpec) override;
	void onLayout(bool changed, int16_t left, int16_t top, int16_t right, int16_t bottom) override;
	void onDraw() override;

	Orientation _orientation {Orientation::HORIZONTAL};
};

#endif //ARDUI_LINEARLAYOUT_H
