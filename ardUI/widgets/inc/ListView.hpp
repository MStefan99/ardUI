//
// Created by MStefan99 on 31.5.21.
//

#ifndef ARDUI_LISTVIEW_H
#define ARDUI_LISTVIEW_H

#include "View.hpp"
#include "AdapterView.hpp"


template <class T>
class ListView: S_PUBLIC AdapterView<T> {
S_PUBLIC:
	ListView() = default;

S_PROTECTED:
	void onMeasure(View::MeasureSpec width, View::MeasureSpec height) override;
	void onLayout(bool changed, int16_t left, int16_t top, int16_t right, int16_t bottom) override;
	void onDraw() override;

	void updateElements();
};


template <class T>
void ListView<T>::onMeasure(View::MeasureSpec widthMeasureSpec, View::MeasureSpec heightMeasureSpec) {
	int16_t size = 0;
	updateElements();
	for (const auto& v : this->_viewList) {
		v->measure(
				View::MeasureSpec {widthMeasureSpec.getSize(), View::MeasureSpec::AT_MOST},
				View::MeasureSpec {heightMeasureSpec.getSize()});
		size += v->getMeasuredHeight();
	}
	this->setMeasuredDimensions(this->getDefaultSize(this->getMinimumWidth() + this->_padding.width(), widthMeasureSpec),
			this->getDefaultSize(size + this->_padding.height(), heightMeasureSpec));
}


template <class T>
void ListView<T>::onLayout(bool changed, int16_t l, int16_t t, int16_t r, int16_t b) {
	int16_t nextViewLeft {l};
	int16_t nextViewTop {t};

	for (const auto& v : this->_viewList) {
		v->setTop(nextViewTop);
		v->setLeft(nextViewLeft);

		v->layout(nextViewLeft, nextViewTop, r, nextViewTop + v->getMeasuredHeight());
		nextViewTop += v->getMeasuredHeight();
		v->setBottom(nextViewTop);
		v->setRight(r);
	}
}


template <class T>
void ListView<T>::onDraw() {
	for (const auto& v : this->_viewList) {
		v->draw();
	}
}


template <class T>
void ListView<T>::updateElements() {
	this->removeAllViews();
	for (int i {0}; i < AdapterView<T>::_adapter->getCount(); ++i) {
		ViewGroup::addView(AdapterView<T>::_adapter->getView(i));
	}
}


#endif //ARDUI_LISTVIEW_H
