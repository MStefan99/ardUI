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
	void onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) override;
	void onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) override;
	void onDraw() override;

	void handleEvent(const Event& event) override;

	Orientation _orientation {Orientation::HORIZONTAL};
};

#endif //ARDUI_LINEARLAYOUT_H
