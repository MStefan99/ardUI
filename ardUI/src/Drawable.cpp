//
// Created by MStefan99 on 20.12.19.
//

#include "Drawable.h"


Rect Drawable::getBounds() const {
	return _viewBox;
}


void Drawable::setBounds(uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
	_viewBox.set(l, t, r, b);
}


void Drawable::setBounds(const Rect& bounds) {
	_viewBox.set(bounds);
}


int Drawable::getLevel() const {
	return _level;
}


bool Drawable::setLevel(uint16_t l) {
	bool changed {l != _level};
	_level = l;
	return changed;
}


bool Drawable::getPadding(Rect& p) const {
	bool paddingExists {(bool)p};
	if (paddingExists) {
		p = _padding;
	} else {
		p.setEmpty();
	}
	return paddingExists;
}


void Drawable::setPadding(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
	_padding = Rect(left, top, right, bottom);
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
