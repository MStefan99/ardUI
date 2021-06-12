//
// Created by MStefan99 on 6.6.21.
//

#ifndef ARDUI_CONSTRAINTLAYOUT_H
#define ARDUI_CONSTRAINTLAYOUT_H


#include "View.h"
#include "ViewGroup.h"
#include LIST_H
#include MAP_H


class ConstraintLayout: public ViewGroup {
public:
	enum Side {
		LEFT = 0,
		TOP = 1,
		RIGHT = 2,
		BOTTOM = 3
	};

	class ConstraintSet {
	protected:
		struct Constraint {
			View* startView {nullptr};
			Side startSide {LEFT};
			View* endView {nullptr};
			Side endSide {LEFT};
			uint16_t margin {0};

			Constraint(View* startView, Side startSide, View* endView, Side endSide, uint16_t margin);
		};

		struct ViewLayout {
			uint16_t width {};
			uint16_t height {};
			Rect rect {};
		};

	public:
		ConstraintSet() = default;

		void connect(View* startView, Side startSide, View* endView, Side endSide, uint16_t margin);

		friend class ConstraintLayout;

	protected:
		MAP<View*, PAIR<Rect, LIST<Constraint>>> _constraints {};
	};

	ConstraintLayout() = default;

	ConstraintSet* getConstraints();

protected:
	void onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) override;
	void onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) override;
	void onDraw() override;

	void handleEvent(const Event& event) override;

	uint16_t getPos(View* view, Side side);
	void applyConstraints(PAIR<Rect, LIST<ConstraintSet::Constraint>>* constraints);

	ConstraintSet* _constraintSet {new ConstraintSet({})};
};

#endif //ARDUI_CONSTRAINTLAYOUT_H
