//
// Created by MStefan99 on 19.12.19.
//

#ifndef ARDUI_TEST_CLICKABLE_H
#define ARDUI_TEST_CLICKABLE_H

#include "ardUI_config.h"
#include "drawable.h"
#include "view.h"


class clickable: virtual public drawable {
public:
    void setOnClickListener(void (*onClickListener)(view *view));
    void setOnLongClickListener(void (*onLongClickListener)(view *view));

protected:
    void setClicked(bool isClicked);
    bool isClicked();
    bool isLongClicked();

private:
    bool inClickedState {false};
    bool inLongClickedState {false};

    int timesClicked {0};
};

#endif //ARDUI_TEST_CLICKABLE_H
