//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_VIEW_H
#define ARDUI_VIEW_H

#include <Arduino.h>
#include "drawable.h"


class view: virtual public drawable {
public:
    view() = default;
    //TODO: add constructor from coordinates of center
    virtual ~view() = default;

    virtual void forEach(void (*predicate)(view*));
    int getId();

protected:
    static int lastViewId;
    int viewId {++lastViewId};

};

#endif //ARDUI_VIEW_H
