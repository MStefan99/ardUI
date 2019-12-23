//
// Created by MStefan99 on 19.12.19.
//

#ifndef ARDUI_TEST_SCROLLABLE_H
#define ARDUI_TEST_SCROLLABLE_H


#include "clickable.h"


class scrollable: virtual public clickable {
public:
    void setOnScrollListener(void (*onScrollListener)(view *view));

protected:
    void setScrolled(bool isScrolled);
    bool isScrolled();

private:
    bool inScrolledState {false};
};

#endif //ARDUI_TEST_SCROLLABLE_H
