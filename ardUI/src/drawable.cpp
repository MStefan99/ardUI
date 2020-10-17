//
// Created by MStefan99 on 20.12.19.
//

#include "drawable.h"


Rect Drawable::getBounds() const {
	return Rect(viewBox);
}


void Drawable::setBounds(uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
	viewBox.set(l, t, r, b);
	onBoundsChange(Rect(l, t, r, b));
}


void Drawable::setBounds(const Rect& bounds) {
	viewBox.set(bounds);
	onBoundsChange(bounds);
}


int Drawable::getLevel() {
	return level;
}


bool Drawable::setLevel(uint16_t l) {
	if (l > 10000) {
		l = 10000;
	}
	auto changed {onLevelChange(l)};
	if (changed) {
		level = l;
	}
	return changed;
}


bool Drawable::getPadding(Rect& p) const {
	bool paddingExists {p};
	if (paddingExists) {
		p = padding;
	} else {
		p.setEmpty();
	}
	return paddingExists;
}


void Drawable::setPadding(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
	padding = Rect(left, top, right, bottom);
}


bool Drawable::isVisible() const {
	return visible;
}


bool Drawable::setVisible(bool v) {
	auto changed {v != visible};
	if (changed) {
		visible = v;
	}
	return changed;
}


bool Drawable::isValid() const {
	return valid;
}


void Drawable::invalidateSelf() {
	valid = false;
}


void Drawable::onBoundsChange(const Rect& bounds) {
	invalidateSelf();
}


bool Drawable::onLevelChange(uint16_t l) {
	auto changed {l != level};
	if (changed) {
		draw();
	}
	return changed;
}


uint16_t Drawable::getMinimumHeight() const {
	return minHeight;
}


uint16_t Drawable::getMinimumWidth() const {
	return minWidth;
}


void Drawable::setMinimumWidth(uint16_t w) {
	minWidth = w;
}


void Drawable::setMinimumHeight(uint16_t h) {
	minHeight = h;
}