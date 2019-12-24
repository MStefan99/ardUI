//
// Created by MStefan99 on 24.12.19.
//

#include "rect.h"


rect::rect(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom):
        left(left),
        top(top),
        right(right),
        bottom{bottom} {}


bool rect::contains(const rect &r) const {
    return contains(r.left, r.top) && contains(r.right, r.bottom);
}


bool rect::contains(uint16_t l, uint16_t t, uint16_t r, uint16_t b) const {
    return contains(l, t) && contains(r, b);
}


bool rect::contains(uint16_t x, uint16_t y) const {
    return x > left && x < right && y > top && y < bottom;
}


uint16_t rect::centerX() const {
    return (left + right) / 2;
}


uint16_t rect::centerY() const {
    return (top + bottom) / 2;
}


uint16_t rect::height() const {
    return bottom - top;
}


uint16_t rect::width() const {
    return right - left;
}


bool rect::isEmpty() const {
    return top == bottom || right == left;
}


void rect::setEmpty() {
    left = 0;
    top = 0;
    right = 0;
    bottom = 0;
}


void rect::offset(uint16_t dx, uint16_t dy) {
    left += dx;
    right += dx;
    top += dy;
    bottom += dy;
}


void rect::offsetTo(uint16_t newLeft, uint16_t newTop) {
    offset(newLeft - left, newTop - top);
}


void rect::set(uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
    left = l;
    top = t;
    right = r;
    bottom = b;
}


void rect::set(const rect &r) {
    left = r.left;
    top = r.top;
    right = r.right;
    bottom = r.bottom;
}


rect &rect::operator=(const rect &r) {
    if (this != &r) {
        set(r);
    }
    return *this;
}


rect::operator bool() const {
    return isEmpty();
}



