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

    void addView(view* view);
    view* findViewById(int id) override;

    int getChildCount();
    view& getChildAt(int index);

protected:
    void onMeasure(uint16_t width, uint16_t height) override = 0;
    void onLayout(bool changed, uint16_t left, uint16_t top, uint16_t right, uint16_t bottom) override = 0;
    void onDraw() override = 0;
    list<view*> viewList {};

};

#endif //ARDUI_VIEW_GROUP_H
