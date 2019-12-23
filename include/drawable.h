//
// Created by MStefan99 on 20.12.19.
//

#ifndef ARDUI_TEST_DRAWABLE_H
#define ARDUI_TEST_DRAWABLE_H

#include <Arduino.h>


class view;


class drawable {
public:
    drawable() = default;
    drawable(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    ~drawable() = default;

    virtual void draw() const = 0;

    bool coordsInside(uint16_t x, uint16_t y);

    friend class ardUI;

protected:
    class point {
    public:
        point() = default;
        point(uint16_t x, uint16_t y);

        uint16_t getX() const;
        uint16_t getY() const;

    private:
        uint16_t x {0};
        uint16_t y {0};
    };
    class boundingBox {
    public:
        boundingBox() = default;
        boundingBox(point topLeft, point bottomRight);
        boundingBox(point center, uint16_t width, uint16_t height);

        bool pointInside(point p) const;

        point getTopLeftPoint() const;
        point getBottomRightPoint() const;

    private:
        point topLeft {};
        point bottomRight {};
    };

    void (*onClick)(view *view) {nullptr};
    void (*onLongClick)(view *view) {nullptr};
    void (*onScroll)(view *view) {nullptr};

    boundingBox viewBox {};
};

#endif //ARDUI_TEST_DRAWABLE_H
