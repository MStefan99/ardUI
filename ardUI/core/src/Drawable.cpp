//
// Created by MStefan99 on 20.12.19.
//

#include "Drawable.hpp"


Drawable::~Drawable() = default;


Rect Drawable::getBounds() const {
	return _viewBox;
}


void Drawable::setBounds(int16_t l, int16_t t, int16_t r, int16_t b) {
	_viewBox.set(l, t, r, b);
}


void Drawable::setBounds(const Rect& bounds) {
	_viewBox.set(bounds);
}


int Drawable::getLevel() const {
	return _level;
}


bool Drawable::setLevel(int16_t l) {
	bool changed {l != _level};
	_level = l;
	return changed;
}


Rect Drawable::getPadding() const {
	return _padding;
}


void Drawable::setPadding(int16_t left, int16_t top, int16_t right, int16_t bottom) {
	_padding.set(left, top, right, bottom);
}


void Drawable::setPadding(const Rect& padding) {
	_padding = padding;
}


bool Drawable::isVisible() const {
	return _visible;
}


bool Drawable::setVisible(bool v) {
	auto changed {v != _visible};
	_visible = v;
	return changed;
}


bool Drawable::isValid() const {
	return _valid;
}


void Drawable::invalidateSelf() {
	_valid = false;
}


uint16_t Drawable::getMinimumHeight() const {
	return _minHeight;
}


uint16_t Drawable::getMinimumWidth() const {
	return _minWidth;
}


void Drawable::setMinimumWidth(uint16_t w) {
	_minWidth = w;
}


void Drawable::setMinimumHeight(uint16_t h) {
	_minHeight = h;
}
