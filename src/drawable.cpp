//
// Created by MStefan99 on 20.12.19.
//

#include "drawable.h"


point::point(uint16_t x, uint16_t y): x(x), y(y) {}


uint16_t point::getX() const {
    return x;
}


uint16_t point::getY() const {
    return y;
}


void point::setX(uint16_t c) {
    x = c;
}


void point::setY(uint16_t c) {
    y = c;
}


point point::operator+(const point &p) const {
    return point(this->x + p.x, this->y + p.y);
}


point& point::operator=(const point &p) {
    if (this != &p) {
        this->x = p.x;
        this->y = p.y;
    }
    return *this;
}


point& point::operator+=(const point &p) {
    this->x += p.x;
    this->y += p.y;
    return *this;
}


boundingBox::boundingBox(point topLeft, point bottomRight):
        topLeft(topLeft),
        bottomRight(bottomRight) {}


boundingBox::boundingBox(point center, uint16_t width, uint16_t height):
        topLeft(center.getX() - width / 2, center.getY() - height / 2),
        bottomRight(center.getX() + width / 2, center.getY() + height / 2) {}


bool boundingBox::pointInside(point p) const {
    return p.getX() >= topLeft.getX() && p.getY() >= topLeft.getY() &&
           p.getX() <= bottomRight.getX() && p.getY() <= bottomRight.getY();
}


point boundingBox::getTopLeftPoint() const {
    return topLeft;
}


point boundingBox::getBottomRightPoint() const {
    return bottomRight;
}


void boundingBox::setTopLeftPoint(const point& p) {
    topLeft = p;
}


void boundingBox::setBottomRightPoint(const point& p) {
    bottomRight = p;
}


boundingBox& boundingBox::operator+=(const point &p) {
    topLeft += p;
    bottomRight += p;
    return *this;
}


drawable::drawable(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2):
        viewBox(point(x1, y1), point(x2, y2)) {}


bool drawable::coordsInside(uint16_t x, uint16_t y) const {
    return viewBox.pointInside(point(x, y));
}


boundingBox drawable::getViewBox() const {
    return viewBox;
}
