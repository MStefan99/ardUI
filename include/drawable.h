//
// Created by MStefan99 on 20.12.19.
//

#ifndef ARDUI_TEST_DRAWABLE_H
#define ARDUI_TEST_DRAWABLE_H

#include <Arduino.h>
#include "rect.h"
#include "llpi.h"


class view;


class drawable {
public:
    drawable() = default;
    ~drawable() = default;

    virtual void draw() const = 0;

    rect copyBounds() const;
    void copyBounds(rect& r) const;
    rect getBounds() const;
    void setBounds(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);
    void setBounds(const rect& bounds);

    int getLevel();
    bool setLevel(uint16_t level);

    bool getPadding(rect& padding) const;

    //TODO: add inflaters

    bool isVisible() const;
    bool setVisible(bool visible);

protected:
    virtual void onBoundsChange(const rect& bounds);
    virtual bool onLevelChange(uint16_t level);

private:
    bool valid {false};
    bool visible {true};

    rect viewBox {};
    rect padding {};
    uint16_t level {0};
};

#endif //ARDUI_TEST_DRAWABLE_H
