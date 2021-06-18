//
// Created by MStefan99 on 6.6.21.
//

#include "ConstraintLayout.h"


void ConstraintLayout::ConstraintSet::connect(View* startView, ConstraintLayout::Side startSide,
		View* endView, ConstraintLayout::Side endSide,
		uint16_t margin) {
	if ((startSide + endSide) % 2) {
		Serial.println("Side mismatch");
	} else {
		_constraints[startView].second.push_back({startView, startSide, endView, endSide, margin});
	}
}


ConstraintLayout::ConstraintSet::Constraint::Constraint(View* startView, Side startSide,
		View* endView, Side endSide, uint16_t margin):
		startView {startView}, startSide {startSide}, endView {endView}, endSide {endSide}, margin {margin} {
	// Nothing to do
}


void ConstraintLayout::ConstraintSet::LayoutInfo::reset() {
	constrained = leftConstrained = topConstrained = rightConstrained = leftConstrained = false;
}


uint16_t ConstraintLayout::getPos(View* view, Side side) {
	auto layoutInfo = _constraintSet->_constraints[view].first;

	switch (side) {
		case LEFT:
			return layoutInfo.viewBox.left;
		case TOP:
			return layoutInfo.viewBox.top;
		case RIGHT:
			return layoutInfo.viewBox.right;
		case BOTTOM:
			return layoutInfo.viewBox.bottom;
	}
}


void ConstraintLayout::applyConstraints(
		std::pair<ConstraintSet::LayoutInfo, std::list<ConstraintSet::Constraint>>* constraints) {
	auto& layoutInfo = constraints->first;

	for (auto constraint: constraints->second) {
		auto& endConstraints = _constraintSet->_constraints[constraint.endView];
		if (!endConstraints.first.constrained) {
			applyConstraints(&endConstraints);
		}

		// TODO: fix this mess
		switch (constraint.startSide) {
			case LEFT:
				if (layoutInfo.rightConstrained) {
					layoutInfo.viewBox.left = getPos(constraint.endView, constraint.endSide) + constraint.margin;
				} else {
					layoutInfo.viewBox.offsetTo(getPos(constraint.endView, constraint.endSide) + constraint.margin,
							layoutInfo.viewBox.top);
				}
				layoutInfo.leftConstrained = true;
				break;
			case TOP:
				if (layoutInfo.bottomConstrained) {
					layoutInfo.viewBox.bottom = getPos(constraint.endView, constraint.endSide) + constraint.margin;
				} else {
					layoutInfo.viewBox.offsetTo(layoutInfo.viewBox.left, getPos(constraint.endView, constraint.endSide)
							+ constraint.margin);
				}
				layoutInfo.topConstrained = true;
				break;
			case RIGHT:
				if (layoutInfo.leftConstrained) {
					layoutInfo.viewBox.right = getPos(constraint.endView, constraint.endSide) - constraint.margin;
				} else {
					layoutInfo.viewBox.offsetTo(getPos(constraint.endView, constraint.endSide)
							- constraint.margin - layoutInfo.viewBox.width(), layoutInfo.viewBox.top);
				}
				layoutInfo.rightConstrained = true;
				break;
			case BOTTOM:
				if (layoutInfo.topConstrained) {
					layoutInfo.viewBox.bottom = getPos(constraint.endView, constraint.endSide) - constraint.margin;
				} else {
					layoutInfo.viewBox.offsetTo(layoutInfo.viewBox.left, getPos(constraint.endView, constraint.endSide)
							- constraint.margin - layoutInfo.viewBox.height());
				}
				layoutInfo.bottomConstrained = true;
				break;
		}
	}
	layoutInfo.constrained = true;
}


ConstraintLayout::ConstraintSet* ConstraintLayout::getConstraints() {
	return _constraintSet;
}


void ConstraintLayout::onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) {
	setMeasuredDimensions(getDefaultSize(getMinimumWidth() + _padding.width(), widthMeasureSpec),
			getDefaultSize(getMinimumHeight() + _padding.height(), heightMeasureSpec));
	_constraintSet->_constraints[this].first.viewBox.set(0, 0, getMeasuredWidth(), getMeasuredHeight());
	_constraintSet->_constraints[this].first.constrained = true;

	for (auto view: _viewList) {
		view->measure(
				View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::AT_MOST, getMeasuredWidth()),
				View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::AT_MOST, getMeasuredHeight()));

		_constraintSet->_constraints[view].first.viewBox = Rect(0, 0, view->getMeasuredWidth(), view->getMeasuredHeight());
	}
}


void ConstraintLayout::onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
	for (auto& c : _constraintSet->_constraints) {
		c.second.first.reset();
	}

	for (auto view: _viewList) {
		auto constraints {_constraintSet->_constraints[view]};
		applyConstraints(&constraints);

		view->layout(constraints.first.viewBox);
	}
}


void ConstraintLayout::onDraw() {
	for (auto view: _viewList) {
		view->draw();
	}
}


void ConstraintLayout::handleEvent(const Event& event) {
	for (auto view: _viewList) {
		if (view->getBounds().contains(event._targetX, event._targetY)) {
			view->handleEvent(event);
		}
	}
}
