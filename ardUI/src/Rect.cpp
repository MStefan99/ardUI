//
// Created by MStefan99 on 24.12.19.
//

#include "Rect.h"


Rect::Rect(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom):
	_left {left},
	_top {top},
	_right {right},
	_bottom {bottom} {}


bool Rect::contains(const Rect& r) const {
	return contains(r._left, r._top) && contains(r._right, r._bottom);
}


bool Rect::contains(uint16_t l, uint16_t t, uint16_t r, uint16_t b) const {
	return contains(l, t) && contains(r, b);
}


bool Rect::contains(uint16_t x, uint16_t y) const {
	return x >= _left && x <= _right && y >= _top && y <= _bottom;
}


uint16_t Rect::centerX() const {
	return (_left + _right) / 2;
}


uint16_t Rect::centerY() const {
	return (_top + _bottom) / 2;
}


uint16_t Rect::height() const {
	return _bottom - _top;
}


uint16_t Rect::width() const {
	return _right - _left;
}


bool Rect::isEmpty() const {
	return _top == _bottom || _right == _left;
}


void Rect::setEmpty() {
	_left = 0;
	_top = 0;
	_right = 0;
	_bottom = 0;
}


void Rect::offset(uint16_t dx, uint16_t dy) {
	_left += dx;
	_right += dx;
	_top += dy;
	_bottom += dy;
}


void Rect::offsetTo(uint16_t newLeft, uint16_t newTop) {
	offset(newLeft - _left, newTop - _top);
}


void Rect::inset(uint16_t dx, uint16_t dy) {
	_left -= dx / 2;
	_right -= dx / 2;
	_top -= dy / 2;
	_bottom -= dy / 2;
}


void Rect::inset(uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
	_left -= l;
	_top -= t;
	_right -= r;
	_bottom -= b;
}


void Rect::inset(const Rect& r) {
	_left -= r._left;
	_top -= r._top;
	_right -= r._right;
	_bottom -= r._bottom;
}


void Rect::set(uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
	_left = l;
	_top = t;
	_right = r;
	_bottom = b;
}


void Rect::set(const Rect& r) {
	_left = r._left;
	_top = r._top;
	_right = r._right;
	_bottom = r._bottom;
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
