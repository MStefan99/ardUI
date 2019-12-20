//
// Created by MStefan99 on 20.12.19.
//

#include "drawable.h"


drawable::point::point(uint16_t x, uint16_t y): x(x), y(y) {}


uint16_t drawable::point::getX() const {
    return x;
}


uint16_t drawable::point::getY() const {
    return y;
}


drawable::boundingBox::boundingBox(drawable::point topLeft, drawable::point bottomRight):
        topLeft(topLeft),
        bottomRight(bottomRight) {}


drawable::boundingBox::boundingBox(point center, uint16_t width, uint16_t height):
        topLeft(center.getX() - width / 2, center.getY() - height / 2),
        bottomRight(center.getX() + width / 2, center.getY() + height / 2) {}


bool drawable::boundingBox::pointInside(point p) const {
    return p.getX() >= topLeft.getX() && p.getY() >= topLeft.getY() &&
           p.getX() <= bottomRight.getX() && p.getY() <= bottomRight.getY();
}


drawable::point drawable::boundingBox::getTopLeftPoint() const {
    return topLeft;
}


drawable::point drawable::boundingBox::getBottomRightPoint() const {
    return bottomRight;
}


drawable::drawable(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2):
        viewBox(point(x1, y1), point(x2, y2)) {}


bool drawable::coordsInside(uint16_t x, uint16_t y) {
    return viewBox.pointInside(point(x, y));
}

