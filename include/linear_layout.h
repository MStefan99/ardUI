//
// Created by MStefan99 on 23.12.19.
//

#ifndef ARDUI_TEST_LINEAR_LAYOUT_H
#define ARDUI_TEST_LINEAR_LAYOUT_H

#include "view_group.h"


class linearLayout: public viewGroup {
public:
    explicit linearLayout(bool vertical = true);

    void onMeasure(uint16_t w, uint16_t h) override;
    void onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) override;
    void onDraw() override;

protected:
    bool isVertical {true};
};

#endif //ARDUI_TEST_LINEAR_LAYOUT_H