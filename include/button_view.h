//
// Created by MStefan99 on 19.12.19.
//

#ifndef ARDUI_TEST_BUTTON_VIEW_H
#define ARDUI_TEST_BUTTON_VIEW_H


#include <Arduino.h>
#include "text_view.h"
#include "clickable.h"
#include "llpi.h"


class buttonView: public textView, virtual public clickable {
public:
    buttonView() = default;
    explicit buttonView(const String& text);
    buttonView(const String& text, uint16_t x, uint16_t y);
    buttonView(const String& text, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    ~buttonView() override = default;

    void draw() const override;

private:
    uint32_t backgroundColor {0xFFFFFFFF};
    uint32_t borderColor {0};
};

#endif //ARDUI_TEST_BUTTON_VIEW_H
