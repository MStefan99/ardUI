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

    int getId();
    void draw() const override;
    void measure(uint16_t width, uint16_t height);
    void layout(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);

    void invalidate();

    void setOnClickListener(void (*onClickListener)(view&));
    void setOnLongClickListener(void (*onLongClickListener)(view&));

    friend class ardUI;

protected:
    view& getParent() const;
    void setParent(view* parent);
    virtual void onDraw() const;
    virtual void onMeasure(uint16_t width, uint16_t height);
    virtual void onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom);

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
    uint16_t measuredHeight {0};
    uint16_t measuredWidth {0};
    view* parent {nullptr};
};

#endif //ARDUI_VIEW_H
