//
// Created by MStefan99 on 17.12.19.
//

#ifndef ARDUI_VIEWGROUP_H
#define ARDUI_VIEWGROUP_H

#include "platform.h"
#include LIST_H
#include "View.h"


class ViewGroup: public View {
public:
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

	friend class EmscriptenBindingInitializer_BuilderInterface;

protected:
	void onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) override = 0;
	void onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) override = 0;
	void onDraw() override = 0;

	LIST<View*> _viewList {};
};

#endif //ARDUI_VIEWGROUP_H
