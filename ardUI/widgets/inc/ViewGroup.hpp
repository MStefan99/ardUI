//
// Created by MStefan99 on 17.12.19.
//

#ifndef ARDUI_VIEWGROUP_H
#define ARDUI_VIEWGROUP_H

#include "platform.hpp"
#include LIST_H

#include "View.hpp"


class ViewGroup: S_PUBLIC View {
S_PUBLIC:
	ViewGroup() = default;
	~ViewGroup() override;

	void addView(View* view);
	View* findViewById(int id) override;

	View* getChildAt(int index) const;
	int getChildCount() const;

	void removeView(View* view);
	void removeViewAt(int index);
	void removeViews(int start, int count);
	void removeAllViews();

	void draw() override;
	void invalidate() override;

S_PROTECTED:
	void onMeasure(MeasureSpec widthMeasureSpec, MeasureSpec heightMeasureSpec) override = 0;
	void onLayout(bool changed, int16_t left, int16_t top, int16_t right, int16_t bottom) override = 0;
	void onDraw() override = 0;

	View* handleEvent(const Event& event) override;

	TL_NS::list<View*> _viewList {};
};

#endif //ARDUI_VIEWGROUP_H
