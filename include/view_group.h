//
// Created by MStefan99 on 17.12.19.
//

#ifndef ARDUI_VIEW_GROUP_H
#define ARDUI_VIEW_GROUP_H

#include "list.h"
#include "view.h"

class viewGroup: public view {
public:
    viewGroup() = default;
    ~viewGroup() override;

    virtual void addView(view* view);

    void draw() const override;

private:
    list<view*> viewList {};
};

#endif //ARDUI_VIEW_GROUP_H
