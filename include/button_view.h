//
// Created by MStefan99 on 19.12.19.
//

#ifndef ARDUI_TEST_BUTTON_VIEW_H
#define ARDUI_TEST_BUTTON_VIEW_H


#include <Arduino.h>
#include "text_view.h"
#include "clickable.h"


class buttonView: public textView, virtual public clickable {
public:
    buttonView() = default;
    buttonView(const String& text, uint32_t backgroundColor);
    ~buttonView() override = default;

    void draw() const override;

private:
    uint32_t backgroundColor {0xFFFFFFFF};
    uint32_t bevel_color {0};
};

#endif //ARDUI_TEST_BUTTON_VIEW_H
