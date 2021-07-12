//
// Created by MStefan99 on 23.12.19.
//

#ifndef ARDUI_LINEARLAYOUT_H
#define ARDUI_LINEARLAYOUT_H

#include "Event.h"
#include "ViewGroup.h"


class LinearLayout: public ViewGroup {
public:
	enum Orientation {
		HORIZONTAL,
		VERTICAL
	};

	LinearLayout() = default;

	Orientation getOrientation() const;
	void setOrientation(Orientation orientation);

	friend class EmscriptenBindingInitializer_BuilderInterface;

protected:
	void onMeasure(MeasureSpec widthMeasureSpec, MeasureSpec heightMeasureSpec) override;
	void onLayout(bool changed, int16_t left, int16_t top, int16_t right, int16_t bottom) override;
	void onDraw() override;

	Orientation _orientation {Orientation::HORIZONTAL};
};

#endif //ARDUI_LINEARLAYOUT_H
