//
// Created by MStefan99 on 31.5.21.
//

#ifndef ARDUI_LISTVIEW_H
#define ARDUI_LISTVIEW_H

#include "View.h"
#include "AdapterView.h"


template <class T>
class ListView: public AdapterView<T> {
public:
	ListView() = default;

protected:
	void onMeasure(uint16_t width, uint16_t height) override;
	void onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) override;
	void onDraw() override;

	void handleEvent(const Event& event) override;

	void updateElements();
};


template <class T>
void ListView<T>::onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) {
	uint16_t size = 0;
	updateElements();
	for (const auto& v : this->_viewList) {
		v->measure(View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::AT_MOST,
				View::MeasureSpec::getSize(widthMeasureSpec)),
				View::MeasureSpec::makeMeasureSpec(View::MeasureSpec::UNSPECIFIED,
						View::MeasureSpec::getSize(heightMeasureSpec)));
		size += v->getMeasuredHeight();
	}
	this->setMeasuredDimensions(this->getDefaultSize(this->getMinimumWidth() + this->_padding.width(), widthMeasureSpec),
			this->getDefaultSize(size + this->_padding.height(), heightMeasureSpec));
}


template <class T>
void ListView<T>::onLayout(bool changed, uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
	uint16_t nextViewLeft {l};
	uint16_t nextViewTop {t};

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
void ListView<T>::handleEvent(const Event& event) {
	for (auto view: this->_viewList) {
		if (view->getBounds().contains(event._targetX, event._targetY)) {
			view->handleEvent(event);
		}
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
