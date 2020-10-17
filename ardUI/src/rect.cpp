//
// Created by MStefan99 on 24.12.19.
//

#include "rect.h"


Rect::Rect(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom):
		left(left),
		top(top),
		right(right),
		bottom {bottom} {}


bool Rect::contains(const Rect& r) const {
	return contains(r.left, r.top) && contains(r.right, r.bottom);
}


bool Rect::contains(uint16_t l, uint16_t t, uint16_t r, uint16_t b) const {
	return contains(l, t) && contains(r, b);
}


bool Rect::contains(uint16_t x, uint16_t y) const {
	return x >= left && x <= right && y >= top && y <= bottom;
}


uint16_t Rect::centerX() const {
	return (left + right) / 2;
}


uint16_t Rect::centerY() const {
	return (top + bottom) / 2;
}


uint16_t Rect::height() const {
	return bottom - top;
}


uint16_t Rect::width() const {
	return right - left;
}


bool Rect::isEmpty() const {
	return top == bottom || right == left;
}


void Rect::setEmpty() {
	left = 0;
	top = 0;
	right = 0;
	bottom = 0;
}


void Rect::offset(uint16_t dx, uint16_t dy) {
	left += dx;
	right += dx;
	top += dy;
	bottom += dy;
}


void Rect::offsetTo(uint16_t newLeft, uint16_t newTop) {
	offset(newLeft - left, newTop - top);
}


void Rect::inset(uint16_t dx, uint16_t dy) {
	left -= dx / 2;
	right -= dx / 2;
	top -= dy / 2;
	bottom -= dy / 2;
}


void Rect::inset(uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
	left -= l;
	top -= t;
	right -= r;
	bottom -= b;
}


void Rect::inset(const Rect& r) {
	left -= r.left;
	top -= r.top;
	right -= r.right;
	bottom -= r.bottom;
}


void Rect::set(uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
	left = l;
	top = t;
	right = r;
	bottom = b;
}


void Rect::set(const Rect& r) {
	left = r.left;
	top = r.top;
	right = r.right;
	bottom = r.bottom;
}


Rect& Rect::operator =(const Rect& r) {
	if (this != &r) {
		set(r);
	}
	return *this;
}


Rect::operator bool() const {
	return isEmpty();
}



