//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_VIEW_H
#define ARDUI_VIEW_H


#include "platform.h"
#include "ardUI_config.h"
#include "drawable.h"


class View: virtual public Drawable {
public:
	class MeasureSpec {
	public:
		static const uint16_t AT_MOST {0x8000};
		static const uint16_t EXACTLY {0x4000};
		static const uint16_t UNSPECIFIED {0};

		static uint16_t getMode(uint16_t measureSpec);
		static uint16_t getSize(uint16_t measureSpec);

		static uint16_t makeMeasureSpec(uint16_t mode, uint16_t size);

	private:
		uint16_t size;
	};

	View();
	virtual ~View() = default;

	virtual View* findViewById(int id);
	int getId();

	void measure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec);
	void layout(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
	void layout(const Rect& rect);
	void draw() final;
	void invalidate();

	void setLeft(uint16_t left);
	void setTop(uint16_t top);
	void setRight(uint16_t right);
	void setBottom(uint16_t bottom);

	uint16_t getMeasuredWidth();
	uint16_t getMeasuredHeight();

	uint16_t getWidth();
	uint16_t getHeight();

	void setOnClickListener(void (* onClickListener)(View&));
	void setOnLongClickListener(void (* onLongClickListener)(View&));

protected:
	virtual void onMeasure(uint16_t width, uint16_t height);
	virtual void onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
	virtual void onDraw();

	void setMeasuredDimensions(uint16_t measuredWidth, uint16_t measuredHeight);

private:
	void (* onClick)(View& view) {nullptr};
	void (* onLongClick)(View& view) {nullptr};
	void (* onScroll)(View& view) {nullptr};

	void setClicked(bool isClicked);
	bool isClicked();
	bool isLongClicked();
	bool inClickedState {false};
	bool inLongClickedState {false};

	uint16_t getDefaultSize(uint16_t size, uint16_t measureSpec);

	int timesClicked {0};

	static int lastViewId;
	int viewId {++lastViewId};
	uint16_t measuredHeight {0};
	uint16_t measuredWidth {0};
};

#endif //ARDUI_VIEW_H