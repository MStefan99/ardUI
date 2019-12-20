//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_VIEW_H
#define ARDUI_VIEW_H

#include <Arduino.h>


class view {
public:
    view() = default;
    view(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    //TODO: add constructor from coordinates of center
    virtual ~view() = default;

    virtual void draw() const = 0;

    virtual void forEach(void (*predicate)(view*));
    int getId();
    bool coordsInside(uint16_t x, uint16_t y);

protected:
    class point {
    public:
        point() = default;
        point(uint16_t x, uint16_t y): x(x), y(y) {}

        uint16_t getX() const {
            return x;
        }
        uint16_t getY() const {
            return y;
        }

    private:
        uint16_t x {0};
        uint16_t y {0};
    };
    class boundingBox {
    public:
        boundingBox(point topLeft, point bottomRight) :
                topLeft(topLeft),
                bottomRight(bottomRight) {}
        boundingBox(point center, uint16_t width, uint16_t height):
                topLeft(center.getX() - width / 2, center.getY() - height / 2),
                bottomRight(center.getX() + width / 2, center.getY() + height / 2) {}
        boundingBox(): topLeft(), bottomRight() {}

        bool pointInside(point p) {
            return p.getX() >= topLeft.getX() && p.getY() >= topLeft.getY() &&
                    p.getX() <= bottomRight.getX() && p.getY() <= bottomRight.getY();
        }

        point getTopLeftPoint() const {
            return topLeft;
        }
        point getBottomRightPoint() const {
            return bottomRight;
        }

    private:
        point topLeft {};
        point bottomRight {};
    };

    static int lastViewId;
    boundingBox viewBox {};
    int viewId {++lastViewId};
};

#endif //ARDUI_VIEW_H
