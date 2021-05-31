//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_VIEW_H
#define ARDUI_VIEW_H

#include "platform.h"
#include "ardUI_config.h"
#include "Event.h"
#include "Drawable.h"


class View: public Drawable {
public:
	class MeasureSpec {
	public:
		enum Sizing {
			AT_MOST = 0x8000,
			EXACTLY = 0x4000,
			UNSPECIFIED = 0
		};

		static uint16_t getMode(uint16_t measureSpec);
		static uint16_t getSize(uint16_t measureSpec);

		static uint16_t makeMeasureSpec(uint16_t mode, uint16_t size);
	};

	View();
	~View() override = default;

	virtual View* findViewById(int id);
	int getId() const;

	void measure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) final;
	void layout(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) final;
	void layout(const Rect& rect) final;
	void draw() override;
	void invalidate() override;
	void handleEvent(const Event& event) override;

	void setLeft(uint16_t left);
	void setTop(uint16_t top);
	void setRight(uint16_t right);
	void setBottom(uint16_t bottom);

	uint16_t getMeasuredWidth() const;
	uint16_t getMeasuredHeight() const;

	uint16_t getWidth();
	uint16_t getHeight();

	void setOnClickListener(void (* onClickListener)(View*));
	void setOnLongClickListener(void (* onLongClickListener)(View*));

	friend class Activity;

protected:
	virtual void onMeasure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec);
	virtual void onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
	virtual void onDraw();

	void setMeasuredDimensions(uint16_t measuredWidth, uint16_t measuredHeight);

	uint16_t getDefaultSize(uint16_t size, uint16_t measureSpec);
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
