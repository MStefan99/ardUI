//
// Created by MStefan99 on 24.12.19.
//

#include "Rect.h"


Rect::Rect(int16_t l, int16_t t, int16_t r, int16_t b):
		left {l},
		top {t},
		right {r},
		bottom {b} {}


bool Rect::contains(const Rect& r) const {
	return contains(r.left, r.top) && contains(r.right, r.bottom);
}


bool Rect::contains(int16_t l, int16_t t, int16_t r, int16_t b) const {
	return contains(l, t) && contains(r, b);
}


bool Rect::contains(int16_t x, int16_t y) const {
	return x >= left && x <= right && y >= top && y <= bottom;
}


bool Rect::intersects(int16_t l, int16_t t, int16_t r, int16_t b) const {
	return !(r < left || l > right || b < top || t > bottom);
}


bool Rect::intersects(const Rect& r) const {
	return !(r.right < left || r.left > right || r.bottom < top || r.top > bottom);
}


int16_t Rect::centerX() const {
	return (left + right) / 2;
}


int16_t Rect::centerY() const {
	return (top + bottom) / 2;
}


uint16_t Rect::height() const {
	return static_cast<uint16_t>(bottom - top);
}


uint16_t Rect::width() const {
	return static_cast<uint16_t>(right - left);
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


void Rect::offset(int16_t dx, int16_t dy) {
	left += dx;
	right += dx;
	top += dy;
	bottom += dy;
}


void Rect::offsetTo(int16_t newLeft, int16_t newTop) {
	offset(newLeft - left, newTop - top);
}


void Rect::inset(int16_t dx, int16_t dy) {
	left += dx;
	top += dy;
	right -= dx;
	bottom -= dy;
}


void Rect::inset(int16_t l, int16_t t, int16_t r, int16_t b) {
	left += l;
	top += t;
	right -= r;
	bottom -= b;
}


void Rect::inset(const Rect& r) {
	left += r.left;
	top += r.top;
	right -= r.right;
	bottom -= r.bottom;
}


void Rect::set(int16_t l, int16_t t, int16_t r, int16_t b) {
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


Rect& Rect::operator=(const Rect& r) {
	if (this != &r) {
		set(r);
	}
	return *this;
}


Rect::operator bool() const {
	return isEmpty();
}


bool Rect::operator==(const Rect& r) const {
	return r.left == left && r.top == top && r.right == right && r.bottom == bottom;
}
