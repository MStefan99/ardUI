//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_VIEW_H
#define ARDUI_VIEW_H

#include "platform.h"
#include DISPLAY_H

#include "Event.h"
#include "Drawable.h"


class View: public Drawable {
public:
	class MeasureSpec {
	public:
		enum Sizing {
			AT_MOST,
			EXACTLY,
			UNSPECIFIED
		};

		explicit MeasureSpec(int16_t size, Sizing mode = UNSPECIFIED);

		int16_t getSize() const;
		int16_t getMode() const;

	protected:
		int16_t _size {};
		Sizing _mode {};
	};

	View();
	~View() override = default;

	virtual View* findViewById(int id);
	int getId() const;

	void measure(MeasureSpec widthMeasureSpec, MeasureSpec heightMeasureSpec);
	void layout(int16_t left, int16_t top, int16_t right, int16_t bottom);
	void layout(const Rect& rect);
	void draw() override;
	void invalidate() override;
	virtual View* handleEvent(const Event& event);

	void setLeft(int16_t left);
	void setTop(int16_t top);
	void setRight(int16_t right);
	void setBottom(int16_t bottom);

	uint16_t getMeasuredWidth() const;
	uint16_t getMeasuredHeight() const;

	uint16_t getWidth();
	uint16_t getHeight();

	void setOnClickListener(void (* onClickListener)(View*));
	void setOnLongClickListener(void (* onLongClickListener)(View*));

	friend class Activity;

	friend class EmscriptenBindingInitializer_BuilderInterface;

protected:
	// Measure contents of the current view
	virtual void onMeasure(MeasureSpec widthMeasureSpec, MeasureSpec heightMeasureSpec);
	// Assign size and position to children
	virtual void onLayout(bool changed, int16_t left, int16_t top, int16_t right, int16_t bottom);
	// Draw current view
	virtual void onDraw();

	void setMeasuredDimensions(uint16_t measuredWidth, uint16_t measuredHeight);

	static uint16_t getDefaultSize(uint16_t size, MeasureSpec measureSpec);

private:
	void (* _onClick)(View* view) {nullptr};
	void (* _onLongClick)(View* view) {nullptr};
	void (* _onScroll)(View* view) {nullptr};

	static int _lastViewId;
	int _viewId {++_lastViewId};
	uint16_t _measuredHeight {0};
	uint16_t _measuredWidth {0};
};

#endif //ARDUI_VIEW_H
