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

	#ifdef __EMSCRIPTEN__
	friend class EmscriptenBindingInitializer_BuilderInterface;
	#endif

protected:
	void onMeasure(MeasureSpec widthMeasureSpec, MeasureSpec heightMeasureSpec) override = 0;
	void onLayout(bool changed, int16_t left, int16_t top, int16_t right, int16_t bottom) override = 0;
	void onDraw() override = 0;

	View* handleEvent(const Event& event) override;

	LIST<View*> _viewList {};
};

#endif //ARDUI_VIEWGROUP_H
