//
// Created by MStefan99 on 19.12.19.
//

#include "button_view.h"


buttonView::buttonView() {
    clickable = true;
    longClickable = true;
}


buttonView::buttonView(const String &text, uint32_t backgroundColor):
        backgroundColor(backgroundColor) {
    clickable = true;
    longClickable = true;
}

//TODO: implement draw()
