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


uint16_t ConstraintLayout::getPos(View* view, Side side) {
	auto viewBox = &_constraintSet->_constraints[view].first;

	switch (side) {
		case LEFT:
			return viewBox->left;
		case TOP:
			return viewBox->top;
		case RIGHT:
			return viewBox->right;
		case BOTTOM:
			return viewBox->bottom;
	}
}


void ConstraintLayout::applyConstraints(std::pair<Rect, std::list<ConstraintSet::Constraint>>* constraints) {
	auto& viewPos = constraints->first;
	for (auto constraint: constraints->second) {
		switch (constraint.startSide) {
			case LEFT:
				viewPos.offsetTo(getPos(constraint.endView, constraint.endSide) + constraint.margin, viewPos.top);
				break;
			case TOP:
				viewPos.offsetTo(viewPos.left, getPos(constraint.endView, constraint.endSide) + constraint.margin);
				break;
			case RIGHT:
				viewPos.offsetTo(getPos(constraint.endView, constraint.endSide)
				                 - constraint.margin - viewPos.width(), viewPos.top);
				break;
			case BOTTOM:
				viewPos.offsetTo(viewPos.left, getPos(constraint.endView, constraint.endSide)
				                               - constraint.margin - viewPos.height());
				break;
		}
	}
}


ConstraintLayout::ConstraintSet* ConstraintLayout::getConstraints() {
	return _constraintSet;
}


void ConstraintLayout::onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) {
	setMeasuredDimensions(getDefaultSize(getMinimumWidth() + _padding.width(), widthMeasureSpec),
			getDefaultSize(getMinimumHeight() + _padding.height(), heightMeasureSpec));
	_constraintSet->_constraints[this] = {{0, 0, getMeasuredWidth(), getMeasuredHeight()}, {}};

	for (auto view: _viewList) {
		view->measure(
				View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::AT_MOST, getMeasuredWidth()),
				View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::AT_MOST, getMeasuredHeight()));

		_constraintSet->_constraints[view].first = Rect(0, 0, view->getMeasuredWidth(), view->getMeasuredHeight());
		applyConstraints(&_constraintSet->_constraints[view]);
	}
}


void ConstraintLayout::onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
	for (auto view: _viewList) {
		auto r {_constraintSet->_constraints[view].first};
		r.offset(_viewBox.left, _viewBox.top);
		view->layout(r);
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
