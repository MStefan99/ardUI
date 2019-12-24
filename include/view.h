//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_VIEW_H
#define ARDUI_VIEW_H

#include <Arduino.h>
#include "ardUI_config.h"
#include "drawable.h"


class view: virtual public drawable {
public:
    view();
    virtual ~view() = default;

    virtual void forEach(void (*predicate)(view&));
    int getId();

    void setOnClickListener(void (*onClickListener)(view&));
    void setOnLongClickListener(void (*onLongClickListener)(view&));

    friend class ardUI;

protected:
    view& getParent() const;
    void setParent(view* parent);

private:
    void (*onClick)(view& view) {nullptr};
    void (*onLongClick)(view& view) {nullptr};
    void (*onScroll)(view& view) {nullptr};

    void setClicked(bool isClicked);
    bool isClicked();
    bool isLongClicked();
    bool inClickedState {false};
    bool inLongClickedState {false};

    int timesClicked {0};

    static int lastViewId;
    int viewId {++lastViewId};
    view* parent {nullptr};
};

#endif //ARDUI_VIEW_H
