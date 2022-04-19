//
// Created by MStefan99 on 24.12.19.
//

#ifndef ARDUI_RECT_HPP
#define ARDUI_RECT_HPP

#include "platform.hpp"


class Rect {
public:
	Rect() = default;
	Rect(int16_t left, int16_t top, int16_t right, int16_t bottom);
	Rect(const Rect& r) = default;

	bool contains(int16_t left, int16_t top, int16_t right, int16_t bottom) const;
	bool contains(const Rect& r) const;
	bool contains(int16_t x, int16_t y) const;

	bool intersects(int16_t left, int16_t top, int16_t right, int16_t bottom) const;
	bool intersects(const Rect& r) const;

	int16_t centerX() const;
	int16_t centerY() const;

	uint16_t height() const;
	uint16_t width() const;

	bool isEmpty() const;
	void setEmpty();

	void offset(int16_t dx, int16_t dy);
	void offsetTo(int16_t newLeft, int16_t newTop);

	void inset(int16_t dx, int16_t dy);
	void inset(int16_t left, int16_t top, int16_t right, int16_t bottom);
	void inset(const Rect& r);

	void set(int16_t left, int16_t top, int16_t right, int16_t bottom);
	void set(const Rect& r);

	Rect& operator=(const Rect& r);
	explicit operator bool() const;
	bool operator==(const Rect& r) const;

	int16_t left {0};
	int16_t top {0};
	int16_t right {0};
	int16_t bottom {0};
};

#endif //ARDUI_RECT_HPP
