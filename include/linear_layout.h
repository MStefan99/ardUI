//
// Created by MStefan99 on 23.12.19.
//

#ifndef ARDUI_TEST_LINEAR_LAYOUT_H
#define ARDUI_TEST_LINEAR_LAYOUT_H

#include "view_group.h"


class linearLayout: public viewGroup {
public:
    linearLayout();
    linearLayout(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

    void addView(view *view) override;

private:
    bool isVertical {true};
    uint16_t lastX {0};
    uint16_t lastY {0};
};

#endif //ARDUI_TEST_LINEAR_LAYOUT_H
