//
// Created by MStefan99 on 20.12.19.
//

#ifndef ARDUI_DRAWABLE_H
#define ARDUI_DRAWABLE_H

#include "platform.h"
#include DISPLAY_H

#include "Rect.h"
#include "Event.h"


class Drawable {
public:
	Drawable() = default;
	virtual ~Drawable();

	virtual void draw() = 0;
	virtual void invalidate() = 0;

	Rect getBounds() const;
	void setBounds(int16_t left, int16_t top, int16_t right, int16_t bottom);
	void setBounds(const Rect& bounds);

	int getLevel() const;
	bool setLevel(int16_t level);

	void setPadding(int16_t left, int16_t top, int16_t right, int16_t bottom);
	bool getPadding(Rect& padding) const;

	uint16_t getMinimumHeight() const;
	void setMinimumHeight(uint16_t minimumHeight);

	uint16_t getMinimumWidth() const;
	void setMinimumWidth(uint16_t minimumWidth);

	bool isVisible() const;
	bool setVisible(bool visible);

	bool isValid() const;

	#ifdef __EMSCRIPTEN__
	friend class EmscriptenBindingInitializer_BuilderInterface;
	#endif

protected:
	bool _valid {false};
	bool _visible {true};

	void invalidateSelf();

	Rect _viewBox {};
	Rect _padding {};
	uint16_t _minHeight {20};
	uint16_t _minWidth {20};
	int16_t _level {0};
};

#endif //ARDUI_DRAWABLE_H
