//
// Created by MStefan99 on 6.6.21.
//

#ifndef ARDUI_CONSTRAINTLAYOUT_H
#define ARDUI_CONSTRAINTLAYOUT_H

#include "platform.h"
#include LIST_H
#include MAP_H

#include "View.h"
#include "ViewGroup.h"


class ConstraintLayout: public ViewGroup {
public:
	enum Side {
		LEFT = 0,
		TOP = 1,
		RIGHT = 2,
		BOTTOM = 3
		// TODO: rename (conflicts with UTFT library)
	};

	class ConstraintSet {
	protected:
		struct Constraint {
			View* startView {nullptr};
			Side startSide {LEFT};
			View* endView {nullptr};
			Side endSide {LEFT};
			int16_t margin {0};

			Constraint(View* startView, Side startSide, View* endView, Side endSide, int16_t margin);
		};

		struct LayoutInfo {
			Rect viewBox {};
			bool constrained {false};
			bool leftConstrained {false};
			bool topConstrained {false};
			bool rightConstrained {false};
			bool bottomConstrained {false};

			void reset();
		};

	public:
		ConstraintSet() = default;

		void connect(View* startView, Side startSide, View* endView, Side endSide, int16_t margin);

		friend class ConstraintLayout;

	protected:
		MAP<View*, PAIR<LayoutInfo, LIST<Constraint>>> _constraints {};
	};

	ConstraintLayout() = default;

	ConstraintSet* getConstraints();

protected:
	void onMeasure(MeasureSpec widthMeasureSpec, MeasureSpec heightMeasureSpec) override;
	void onLayout(bool changed, int16_t left, int16_t top, int16_t right, int16_t bottom) override;
	void onDraw() override;

	int16_t getPos(View* view, Side side);
	void applyConstraints(PAIR<ConstraintSet::LayoutInfo, LIST<ConstraintSet::Constraint>>* constraints);

	ConstraintSet* _constraintSet {new ConstraintSet({})};
};

#endif //ARDUI_CONSTRAINTLAYOUT_H
