//
// Created by MStefan99 on 19.12.19.
//

#ifndef ARDUI_TEST_CLICKABLE_H
#define ARDUI_TEST_CLICKABLE_H

#include "view.h"

class clickable {
public:
    void setOnClickListener(void (*onClickListener)(view *view));
    void setOnLongClickListener(void (*onLongClickListener)(view *view));

    friend class ardUI;

protected:
    void setClicked(bool isClicked);
    void setLongClicked(bool isLongClicked);
    bool isClicked();
    bool isLongClicked();

private:
    void (*onClick)(view *view) {nullptr};
    void (*onLongClick)(view *view) {nullptr};

    bool inClickedState {false};
    bool inLongClickedState {false};
};

#endif //ARDUI_TEST_CLICKABLE_H
