//
// Created by MStefan99 on 20.12.19.
//

#include "drawable.h"


rect drawable::copyBounds() const {
    return rect(viewBox);
}


void drawable::copyBounds(rect &r) const {
    r = viewBox;
}


rect drawable::getBounds() const {
    return rect(viewBox);
}


void drawable::setBounds(uint16_t l, uint16_t t, uint16_t r, uint16_t b) {
    viewBox.set(l, t, r, b);
    onBoundsChange(rect(l, t, r, b));
}


void drawable::setBounds(const rect &bounds) {
    onBoundsChange(bounds);
    viewBox.set(bounds);
}


int drawable::getLevel() {
    return level;
}


bool drawable::setLevel(uint16_t l) {
    if (l > 10000) {
        l = 10000;
    }
    auto changed {onLevelChange(l)};
    if (changed) {
        level = l;
    }
    return changed;
}


bool drawable::getPadding(rect &p) const {
    bool paddingExists {p};
    if (paddingExists) {
        p = padding;
    } else {
        p.setEmpty();
    }
    return paddingExists;
}


void drawable::setPadding(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) {
    padding = rect(left, top, right, bottom);
}


bool drawable::isVisible() const {
    return visible;
}


bool drawable::setVisible(bool v) {
    auto changed {v != visible};
    if (changed) {
        visible = v;
    }
    return changed;
}


void drawable::invalidateSelf() {
    valid = false;
}


void drawable::onBoundsChange(const rect &bounds) {
    invalidateSelf();
}


bool drawable::onLevelChange(uint16_t l) {
    auto changed {l != level};
    if (changed) {
        draw();
    }
    return changed;
}


uint16_t drawable::getMinimumHeight() const {
    return minHeight;
}


uint16_t drawable::getMinimumWidth() const {
    return minWidth;
}


void drawable::setMinimumWidth(uint16_t w) {
    minWidth = w;
}


void drawable::setMinimumHeight(uint16_t h) {
    minHeight = h;
}