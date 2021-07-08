//
// Created by MStefan99 on 20.12.19.
//

#ifndef ARDUI_DRAWABLE_H
#define ARDUI_DRAWABLE_H

#include "platform.h"
#include "llpi.h"
#include "Event.h"
#include "Rect.h"


class Drawable {
public:
	Drawable() = default;
	virtual ~Drawable();

	virtual void measure(uint16_t widthMeasureSpec, uint16_t heightMeasureSpec) = 0;
	virtual void layout(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) = 0;
	virtual void layout(const Rect& rect) = 0;
	virtual void draw() = 0;
	virtual void invalidate() = 0;
	virtual void handleEvent(const Event& event) = 0;

	Rect getBounds() const;
	void setBounds(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
	void setBounds(const Rect& bounds);

	int getLevel() const;
	bool setLevel(uint16_t level);

	void setPadding(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
	bool getPadding(Rect& padding) const;

	uint16_t getMinimumHeight() const;
	void setMinimumHeight(uint16_t minimumHeight);

	uint16_t getMinimumWidth() const;
	void setMinimumWidth(uint16_t minimumWidth);

	bool isVisible() const;
	bool setVisible(bool visible);

	bool isValid() const;

	friend class EmscriptenBindingInitializer_BuilderInterface;

protected:
	bool _valid {false};
	bool _visible {true};

	void invalidateSelf();

	Rect _viewBox {};
	Rect _padding {};
	uint16_t _minHeight {20};
	uint16_t _minWidth {20};
	uint16_t _level {0};
};

#endif //ARDUI_DRAWABLE_H
