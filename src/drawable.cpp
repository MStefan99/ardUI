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
    draw();
}


bool drawable::onLevelChange(uint16_t l) {
    auto changed {l != level};
    if (changed) {
        draw();
    }
    return changed;
}


