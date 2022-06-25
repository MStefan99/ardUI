//
// Created by MStefan99 on 20.12.19.
//

#ifndef ARDUI_DRAWABLE_HPP
#define ARDUI_DRAWABLE_HPP

#include "defaults.hpp"
#include "platform.hpp"
#include DISPLAY_H

#include "Rect.hpp"
#include "Event.hpp"


class Drawable {
S_PUBLIC:
	Drawable() = default;
	virtual ~Drawable();

	virtual void draw() = 0;
	virtual void invalidate() = 0;

	Rect getBounds() const;
	void setBounds(int16_t left, int16_t top, int16_t right, int16_t bottom);
	void setBounds(const Rect& bounds);

	Rect getPadding() const;
	void setPadding(int16_t left, int16_t top, int16_t right, int16_t bottom);
	void setPadding(const Rect& padding);

	int getLevel() const;
	bool setLevel(int16_t level);

	uint16_t getMinimumHeight() const;
	void setMinimumHeight(uint16_t minimumHeight);

	uint16_t getMinimumWidth() const;
	void setMinimumWidth(uint16_t minimumWidth);

	bool isVisible() const;
	bool setVisible(bool visible);

	bool isValid() const;

S_PROTECTED:
	bool _valid {false};
	bool _visible {true};

	void invalidateSelf();

	Rect _viewBox {};
	Rect _padding {};
	uint16_t _minWidth {DEFAULT_MIN_WIDTH};
	uint16_t _minHeight {DEFAULT_MIN_HEIGHT};
	int16_t _level {DEFAULT_LEVEL};
};

#endif //ARDUI_DRAWABLE_HPP
