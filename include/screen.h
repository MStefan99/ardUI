//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_SCREEN_H
#define ARDUI_SCREEN_H

#include "slist.h"
#include "view.h"
#include "layout_inflater.h"

class screen {
public:
    screen() = default;

    template <class compiledLayout>
    void setContentView(compiledLayout layoutClass);
    void setContentView(const String& xmlData);
    void setRootView(view* view);

    virtual void onCreate() = 0;
    virtual void onStart();
    virtual void onRestart();
    virtual void onResume();
    virtual void onPause();
    virtual void onStop();
    virtual void onDestroy();

    void draw() const;

private:
    view* rootView {};
};

#endif //ARDUI_SCREEN_H
