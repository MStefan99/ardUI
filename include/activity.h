//
// Created by MStefan99 on 16.12.19.
//

#ifndef ARDUI_SCREEN_H
#define ARDUI_SCREEN_H


#include "list.h"
#include "view.h"
#include "layout_inflater.h"


class activity {
public:
    activity() = default;
    virtual ~activity();

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

    view* findViewById(int id);

    friend class ardUI;

private:
    enum state {
        Launched,
        Created,
        Restarted,
        Started,
        Resumed,
        Paused,
        Stopped,
        Destroyed
    };

    void draw() const;
    void measure();
    void layout();
    view* getRootView();

    state currentState {Launched};
    view* rootView {};
};

#endif //ARDUI_SCREEN_H
