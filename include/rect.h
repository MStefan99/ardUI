//
// Created by MStefan99 on 24.12.19.
//

#ifndef ARDUI_TEST_RECT_H
#define ARDUI_TEST_RECT_H

#include "platform.h"


class rect {
public:
    rect() = default;
    rect(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);

    bool contains(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) const;
    bool contains(const rect& r) const;
    bool contains(uint16_t x, uint16_t y) const;

    uint16_t centerX() const;
    uint16_t centerY() const;

    uint16_t height() const;
    uint16_t width() const;

    bool isEmpty() const;
    void setEmpty();

    void offset(uint16_t dx, uint16_t dy);
    void offsetTo(uint16_t newLeft, uint16_t newTop);

    void inset(uint16_t dx, uint16_t dy);
    void inset(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
    void inset(const rect& r);

    void set(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
    void set(const rect& r);

    rect& operator=(const rect& r);
    operator bool() const;

    uint16_t left {0};
    uint16_t top {0};
    uint16_t right {0};
    uint16_t bottom {0};
};

#endif //ARDUI_TEST_RECT_H
