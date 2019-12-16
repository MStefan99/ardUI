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
    void (*onClickHandler) (view* view);
    void (*onLongClickHandler) (view* view);
    void (*onScrollHandler) (view* view);
    uint16_t x1;
    uint16_t y1;
    uint16_t x2;
    uint16_t y2;
};

#endif //ARDUI_VIEW_H
