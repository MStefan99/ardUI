//
// Created by MStefan99 on 17.12.19.
//

#ifndef ARDUI_VIEW_GROUP_H
#define ARDUI_VIEW_GROUP_H

#include "slist.h"
#include "view.h"

class viewGroup: public view {
public:
    void addView(view* view);

    void draw() const override;

private:
    list<view*> viewList;
};

#endif //ARDUI_VIEW_GROUP_H
