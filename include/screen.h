//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_SCREEN_H
#define ARDUI_SCREEN_H

#include "slist.h"
#include "view.h"

class screen {
public:
    void setContentView();
    void addView(view* view);

    virtual void onCreate() = 0;
    virtual void onStart();
    virtual void onRestart();
    virtual void onResume();
    virtual void onPause();
    virtual void onStop();
    virtual void onDestroy();

    void draw() const;

private:
list<view*> viewList;
};

#endif //ARDUI_SCREEN_H
