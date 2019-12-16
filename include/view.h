//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_VIEW_H
#define ARDUI_VIEW_H

#include <Arduino.h>

class view {
public:
    view();

    void setOnClickListener(void (*onClickListener)(view* view));
    void setOnLongClickListener(void (*onLongClickListener)(view* view));
    void setOnScrollListener(void (*onScrollListener)(view* view));
private:
    void (*onClickHandler) (view* view) = nullptr;
    void (*onLongClickHandler) (view* view) = nullptr;
    void (*onScrollHandler) (view* view) = nullptr;
    uint16_t x1 = 0;
    uint16_t y1 = 0;
    uint16_t x2 = 0;
    uint16_t y2 = 0;
};

#endif //ARDUI_VIEW_H
